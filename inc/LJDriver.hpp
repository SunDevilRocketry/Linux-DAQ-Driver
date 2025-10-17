// #include <BaseDeviceController.hpp>
#include <stdint.h>
#include <LabJackM.h>

class LJDriver {
    private:
        int handle;

    public:
        LJDriver();
        void connect();
        void close();
        void read_address(uint32_t address, uint32_t data, void* output);
        void write_address(uint32_t address, uint32_t data);
};