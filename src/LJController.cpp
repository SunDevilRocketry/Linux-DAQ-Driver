#include <LJController.hpp>

LJController::LJController(const char* id){
    LJStatus status = connect(id);
    telemetry_flag.store(false);
}

LJController::~LJController(){
    
    close();
}

float LJController::read_pt_at_idx(int pt_number){
    float output;
    read_address(pt_number, (void*) &output); // AIN# addr ranges from 0 to 255
}

Liquid_PT LJController::read_all_pts(){
    return {
        read_pt_at_idx(0),
        read_pt_at_idx(1),
        read_pt_at_idx(2),
        read_pt_at_idx(3),
        read_pt_at_idx(4),
        read_pt_at_idx(5),
        read_pt_at_idx(6)
    };
}

float LJController::read_loadcell(){
}

void LJController::actuate_valve(){
    std::lock_guard<std::mutex> guard(lock);
}

void LJController::start_telemetry(){
    telemetry_flag.store(true);
    thread_map.insert(std::make_pair(0, std::thread(telemetry_thread)));
}

void LJController::telemetry_thread(){
    while (telemetry_flag.load()){
        // Loading data
    }
}

void LJController::stop_telemetry(){
    telemetry_flag.store(false);
    thread_map[0].join();
    thread_map.erase(0);
}