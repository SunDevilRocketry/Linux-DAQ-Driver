#include <NIDriver.hpp>
#include <NIDAQmx.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

#define DAQmxErrChk(functionCall) if(DAQmxFailed(error=(functionCall))) goto Error; else

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

using namespace std;

NIDriver::NIDriver(const char* name) {
    inputTask = 0;
    outputTask = 0;
    deviceName = name;
}

NIDriver::~NIDriver() {
    close();
}

bool NIDriver::is_connected() {
    return (inputTask != 0 && outputTask != 0);
}

NIStatus NIDriver::connect() {
    int32 error = DAQmxCreateTask("InputTask", &inputTask);
    if (error != 0) {
        inputTask = 0;
        return FAIL;
    }

    error = DAQmxCreateTask("OutputTask", &outputTask);
    if (error != 0) {
        outputTask = 0;
        return FAIL;
    } 
    
    return OK;
}

NIStatus NIDriver::close() {
    if(!is_connected()) return FAIL;

    if (inputTask) {
        DAQmxStopTask(inputTask);
        DAQmxClearTask(inputTask);
        inputTask = 0;
    }

    if (outputTask) {
        DAQmxStopTask(outputTask);
        DAQmxClearTask(outputTask);
        outputTask = 0;
    }

    return OK;
}

void NIDriver::list_devices() {
    uint32_t buffer_size = DAQmxGetSysDevNames(NULL, 0);

    char buffer[256];
    DAQmxGetSysDevNames(buffer, 256);

    char *data = new char[sizeof(buffer) + 1];
    strcpy_s(data, 256, buffer);
    string data_string = data;

    stringstream stream(data);
    string word;
    while (getline(stream, word, ',')) {
        cout << word << endl;
    }
}

NIStatus NIDriver::read_pt(uint8_t pt, float64 data[1000], void* output) {
    if (!is_connected()) {
        cerr << "Device not connected \n";
    }

    uint8_t ai_channel = 0;
    switch (pt) {
        case 0: ai_channel = 0; break; // Chamber Pressure 
        case 1: ai_channel = 1; break; // Ox Tank Pressure
        case 2: ai_channel = 2; break; // Fuel Tank Pressure
        case 3: ai_channel = 3; break; // Ox Flow dP
        case 4: ai_channel = 4; break; // Fuel Flow dP
        case 5: return OK; // Backup
        case 6: return OK; // Backup
        default:
            cerr << "Invalid PT \n";
            return FAIL;
    }

    return read_address(ai_channel, data, output);
}

NIStatus NIDriver::read_address(uint8_t address, float64 data[1000], void* output) {
    if (!is_connected()) {
        cerr << "Device not connected \n";
        return FAIL;
    }

    int32 error = 0;
	int32 read;
	char errBuff[2048]={'\0'};

    string channel = string(deviceName) + "/ai" + to_string(address);

	DAQmxErrChk(DAQmxCreateAIVoltageChan(inputTask, channel.c_str(), "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
	DAQmxErrChk(DAQmxCfgSampClkTiming(inputTask, "", 1000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, 1000));

	DAQmxErrChk(DAQmxStartTask(inputTask));

	DAQmxErrChk(DAQmxReadAnalogF64(inputTask, -1, 10.0, DAQmx_Val_GroupByChannel, data, 1000, &read, NULL));

	if(read > 0) {
		printf("Acquired %d samples\n",(int)read);
    }

    Error:
        if (DAQmxFailed(error)) DAQmxGetExtendedErrorInfo(errBuff,2048);

        if(inputTask != 0) {
            DAQmxStopTask(inputTask);
        }

        if(DAQmxFailed(error)) {
            printf("DAQmx Error: %s\n", errBuff);
            return FAIL;
        }

    return OK;
}

NIStatus NIDriver::write_address(uint8_t address, float64 data[1000]) {
    if (!is_connected()) {
        cerr << "Device not connected \n";
        return FAIL;
    }

    int32 error = 0;
	char errBuff[2048] = {'\0'};

    string channel = string(deviceName) + "/ao" + to_string(address);

	DAQmxErrChk(DAQmxCreateAOVoltageChan(outputTask, channel.c_str(), "", -10.0, 10.0, DAQmx_Val_Volts, NULL));
	DAQmxErrChk(DAQmxCfgSampClkTiming(outputTask, "/Dev1/PFI0", 1000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 1000));

	DAQmxErrChk(DAQmxRegisterDoneEvent(outputTask, 0, DoneCallback, NULL));

	DAQmxErrChk(DAQmxWriteAnalogF64(outputTask, 1000, 0, 10.0, DAQmx_Val_GroupByChannel, data, NULL, NULL));

	DAQmxErrChk(DAQmxStartTask(outputTask));

	printf("Generating voltage continuously. Press Enter to interrupt\n");
	getchar();

    Error:
        if (DAQmxFailed(error)) DAQmxGetExtendedErrorInfo(errBuff,2048);
        
        if (outputTask != 0) {
            DAQmxStopTask(outputTask);
        }

        if(DAQmxFailed(error)) {
            printf("DAQmx Error: %s\n", errBuff);
            return FAIL;
        }

    return OK;
}

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
	int32 error = 0;
	char errBuff[2048] = {'\0'};

	// Check to see if an error stopped the task.
	DAQmxErrChk(status);

Error:
	if (DAQmxFailed(error)) {
		DAQmxGetExtendedErrorInfo(errBuff,2048);
		DAQmxClearTask(taskHandle);
		printf("DAQmx Error: %s\n", errBuff);
	}

	return 0;
}