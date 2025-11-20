#include <iostream>
#include "NIDriver.hpp"

int main() {
    NIDriver driver("Dev1");

    driver.connect();

    uint8_t address_to_read = 0;
    float64 data[1000];
    void* output = nullptr;

    driver.read_address(address_to_read, data, output);
    std::cout << "Reading address 0 \n" << data << std::endl;

    uint8_t pt_to_read = 2;
    memset(data, 0, sizeof(data));
    output = nullptr;

    driver.read_pt(pt_to_read, data, output);
    std::cout << "Reading PT 2 \n" << data << std::endl;

    return 0;
}