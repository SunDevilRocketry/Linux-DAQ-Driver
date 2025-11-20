// #include "BaseDeviceController.hpp"
#include <NIDAQmx.h>
#include <cstdint>

typedef enum NIStatus {
    OK = 0,
    FAIL = 1
} NIStatus;

class NIDriver {
    private:
        TaskHandle inputTask;
        TaskHandle outputTask;
        const char* deviceName;

    public:
        NIDriver(const char* name = "Dev1");
        ~NIDriver();
        NIStatus connect();
        NIStatus close();
        void list_devices();
        NIStatus read_pt(uint8_t pt, float64 data[1000], void* output);
        NIStatus read_address(uint8_t address, float64 data[1000], void* output);
        NIStatus write_address(uint8_t address, float64 data[1000]);

    private:
        bool is_connected();
};