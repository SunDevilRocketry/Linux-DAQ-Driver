#include <cstdint>

class BaseDeviceController {
    public:
        float virtual get_voltage();
        float virtual get_current();
        float virtual get_pressure();
        float virtual get_flow_pressure();

        void virtual command_poll_loop();
        void virtual command_execute(uint8_t command);
};