# Preface....
cmake_minimum_required(VERSION 3.13)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# This project uses the Raspberry Pi Pico SDK which has to be initialized prior to the project() command
set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs/prgb-pico/external/pico-sdk)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(prgb-hello-pico C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

add_compile_options(-Wno-psabi)

#add_definitions(-DnoDEBUG )

add_executable(${PROJECT_NAME} 
    prgb-hello-pico.cpp
)

message("======================= Adding extra output ====================")
#enable STDIO via USB (cat << /dev/ttyACM0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})

# trying to handle all kinds of warnings
target_compile_options(${PROJECT_NAME} PUBLIC -Wall)


target_include_directories(${PROJECT_NAME}
PUBLIC
    .
PRIVATE
    libs/prgb-pico/include # the pico-speicific implementations for TimerBase, LightArray and LoudnessBase
    libs/prgb/include # the PRGB core
    include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        prgb
        prgb-pico
        WS2812B        
)               

# include folders for libraries and the apps
add_subdirectory(libs)
