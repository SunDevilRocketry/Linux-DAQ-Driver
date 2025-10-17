// #include <BaseDeviceController.hpp>
#include <stdint.h>

class NIDriver {
    public:
        NIDriver();
        void connect();
        void close();
        void read_address(uint32_t address, uint32_t data, void* output);
        void write_address(uint32_t address, uint32_t data);
};