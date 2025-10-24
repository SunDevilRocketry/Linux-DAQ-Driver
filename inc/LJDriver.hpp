// #include <BaseDeviceController.hpp>
#include <stdint.h>
#include <LabJackM.h>
#include <vector>
#include <string>

typedef enum LJStatus {
    OK = 0,
    FAILED
} LJStatus;

typedef struct LJInfo {
    int handle;
    int DeviceType;
    int ConnectionType;
    int SerialNum;
    int Ip;
} LJInfo;

class LJDriver {
    private:
        LJInfo* driver;

    public:
        LJDriver();
        ~LJDriver();
        LJStatus list_devices(std::vector<LJInfo> &output);
        LJStatus connect(const char* id);
        LJStatus close();
        LJStatus read_address(uint32_t address, uint32_t data, void* output);
        LJStatus write_address(uint32_t address, uint32_t data);

    private:
        bool is_connected();
};