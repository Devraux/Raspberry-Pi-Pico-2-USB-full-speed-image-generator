cmake_minimum_required(VERSION 3.27.4)

set(PICO_BOARD pico2_w CACHE STRING "Board type")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# add_compile_definitions(SYS_CLK_MHZ=200)

set(CMAKE_C_FLAGS_RELEASE "-O3")


add_executable(${PROJECT_NAME}
    dev_lowlevel.c
    frame_generator.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}


)

pico_add_extra_outputs(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_cyw43_arch_none
    hardware_gpio
    hardware_pwm
    hardware_clocks
)

pico_enable_stdio_usb(${PROJECT_NAME}  0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

