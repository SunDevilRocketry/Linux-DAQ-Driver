add_executable(test_list_devices
    test_list_devices.cpp
)

target_include_directories(daq PUBLIC ../inc)
target_link_libraries(test_list_devices PRIVATE daq)