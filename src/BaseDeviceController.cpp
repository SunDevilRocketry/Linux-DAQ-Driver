#include <BaseDeviceController.hpp>

class BaseDeviceController {
    public:
        
        void virtual read_address(uint32_t address, uint32_t data, void* output) {}
        void virtual write_address(uint32_t address, uint32_t data) {}

};