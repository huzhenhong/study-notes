
add_executable(custom_str CustomStr.h main.cpp)

target_include_directories(custom_str PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/)


