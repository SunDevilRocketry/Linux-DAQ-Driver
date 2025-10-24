#include "LJDriver.hpp"
#include <iostream>

using namespace std;

int main() {
    LJDriver driver = LJDriver();
    std::vector<LJInfo> output;
    LJStatus status = driver.list_devices(output);
    //driver.connect(std::to_string(output.at(0).SerialNum).c_str());
    for (int i = 0; i < output.size(); i++){
            std::cout << "Connection Type: " << output.at(i).ConnectionType << std::endl;
            std::cout << "Device Type: " << output.at(i).DeviceType << std::endl;
            std::cout << "Serial Number: " << output.at(i).SerialNum << std::endl;
            std::cout << "IP: " << output.at(i).Ip << std::endl;
    };

    return 0;
}