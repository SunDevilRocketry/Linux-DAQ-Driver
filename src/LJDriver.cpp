#include <LJDriver.hpp>

LJDriver::LJDriver(){
    driver = nullptr;
}

LJDriver::~LJDriver(){
    if (driver == nullptr) return;
    close();
    driver == nullptr;
    delete driver;
}

LJStatus LJDriver::connect(const char* id){
    int handle, deviceType, connectionType, serialNum, ipAddr, port = 0;
    int connect_status = LJM_Open(LJM_dtT7, LJM_ctANY, id, &handle);
    int info_status = LJM_GetHandleInfo(handle, &deviceType, &connectionType, &serialNum, &ipAddr, &port, nullptr);
    if (connect_status + info_status != OK){
        return FAILED;
    }
    driver->handle = handle;
    driver->ConnectionType = connectionType;
    driver->DeviceType = deviceType;
    driver->SerialNum = serialNum;
    return OK;
}

LJStatus LJDriver::list_devices(std::vector<LJInfo> &output){
    const int MAX_SIZE = 20;
    int numFound;
    int deviceTypes[MAX_SIZE];
    int connectionTypes[MAX_SIZE];
    int serialNum[MAX_SIZE];
    int ipAddr[MAX_SIZE];

    int err = LJM_ListAll(LJM_dtT7, LJM_ctANY, &numFound, deviceTypes, connectionTypes, serialNum, ipAddr);

    for (int i = 0; i < numFound; i++){
        output.at(i) = {
            0,
            connectionTypes[i],
            deviceTypes[i],
            serialNum[i],
            ipAddr[i]
        };
    };
    if (err == 0){
        return OK;
    } else return FAILED;
}


LJStatus LJDriver::close(){
    if (!is_connected()) return FAILED;
    
    int err = LJM_Close(driver->handle);
    if (err == 0){
        return OK;
    } else return FAILED;
}

LJStatus LJDriver::read_address(uint32_t address, uint32_t data, void* output){
    if (!is_connected()) return FAILED;
    
    int err = LJM_eReadAddress(driver->handle, address, LJM_FLOAT32, (double*) output);
    if (err == 0){
        return OK;
    } else return FAILED;
}

LJStatus LJDriver::write_address(uint32_t address, uint32_t data){
    if (!is_connected()) return FAILED;

    int err = LJM_eWriteAddress(driver->handle, address, LJM_FLOAT32, (double) data);
    if (err == 0){
        return OK;
    } else return FAILED;
}

bool LJDriver::is_connected(){
    return !(driver == nullptr);
}