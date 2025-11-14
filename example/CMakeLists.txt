add_executable(lj_example lj_example.cpp)
add_executable(read_addr eReadAddress.cpp)


target_link_libraries(lj_example daq)
target_link_libraries(read_addr daq)