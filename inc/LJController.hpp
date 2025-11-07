// #include <BaseDeviceController.hpp>
#include <stdint.h>
#include <LJDriver.hpp>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <thread>
#include <map>

typedef struct Liquid_PT{
    float pt1;
    float pt2;
    float pt3;
    float pt4;
    float pt5;
    float pt6;
    float pt7;
} Liquid_PT;

class LJController : public LJDriver {
    private:
        std::mutex lock;
        std::atomic<bool> telemetry_flag;
        std::map<int, std::thread> thread_map;

    public:
        LJController(const char* id);
        ~LJController();
        
        void start_telemetry();
        void stop_telemetry();
        float read_pt_at_idx(int pt_number);
        Liquid_PT read_all_pts();
        void actuate_valve();
        float read_loadcell();
    
    private:
        void telemetry_thread();

};