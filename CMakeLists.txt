
cmake_minimum_required( VERSION 3.20 )
include(CMakePrintHelpers)

#set( PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)

set (WITH_MCU OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set( AVR_PROGRAMMER usbtiny )
set( AVR_MCU atmega328p )
set( AVR_MCU_SPEED 16000000UL )
set(AVR_UPLOAD_SPEED 57600)
set(HAL_PATH atmega328p)
set(AVR_PROGRAMMER arduino)
        set( AVR_UPLOADTOOL_STATUS_OPTIONS -P ${AVR_UPLOADTOOL_PORT} -n -v )
set (AVR_UPLOADTOOL_PORT /dev/ttyUSB0)
set( cur_path ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(GET cur_path PARENT_PATH parent_path)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)
cmake_print_variables (CMAKE_SYSTEM_INCLUDE_PATH)
set( CMAKE_TOOLCHAIN_FILE $ENV{HOME}/git/cmake-avr-toolchain/avr-gcc-toolchain.cmake )

cmake_print_variables (CMAKE_SYSTEM_INCLUDE_PATH)
project( tinyamp )
cmake_print_variables (CMAKE_SYSTEM_INCLUDE_PATH)

enable_language( CXX )

include_directories("extern/avr-libstdcpp/include")
#include_directories("extern/tinyamp_mcal")
#include_directories("extern/tinyamp_utils")
#include_directories("app")



add_subdirectory(extern/tinylib_hal)
add_subdirectory(extern/tinylib_utils)
add_subdirectory(app)

