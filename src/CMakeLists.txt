add_library(daq 
    LJDriver.cpp 
    ../inc/LJDriver.hpp
    NIDriver.cpp 
    ../inc/NIDriver.hpp
    )

target_include_directories(daq PUBLIC ../inc)
target_link_libraries(daq LabJackM)