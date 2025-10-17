#include <LJDriver.hpp>

LJDriver::LJDriver(){
    handle = -1;
}

void LJDriver::connect(){
    int err = LJM_Open(LJM_dtANY, LJM_ctANY, "LJM_idANY", &handle);
    // if err != 0 => Return FAILURE status (enum)
}

void LJDriver::close(){
    int err = LJM_Close(handle);
    // if err != 0 => Return FAILURE status (enum)
}

void LJDriver::read_address(uint32_t address, uint32_t data, void* output){
    int err = LJM_eReadAddress(handle, address, LJM_FLOAT32, (double*) output);
    // if err != 0 => Return FAILURE status (enum)
}

void LJDriver::write_address(uint32_t address, uint32_t data){
    int err = LJM_eWriteAddress(handle, address, LJM_FLOAT32, (double) data);
    // if err != 0 => Return FAILURE status (enum)
}
