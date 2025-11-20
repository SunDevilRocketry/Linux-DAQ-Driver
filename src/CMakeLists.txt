add_library(daq 
    NIDriver.cpp 
    ../inc/NIDriver.hpp
    )

target_include_directories(daq PUBLIC ../inc)
target_include_directories(daq PUBLIC "C:\\Program Files (x86)\\National Instruments\\NI-DAQ\\DAQmx ANSI C Dev\\include")

target_link_libraries(daq PUBLIC "C:\\Program Files (x86)\\National Instruments\\Shared\\ExternalCompilerSupport\\C\\lib64\\msvc\\NIDAQmx.lib")