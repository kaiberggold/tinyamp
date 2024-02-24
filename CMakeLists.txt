
cmake_minimum_required( VERSION 3.20 )
include(CMakePrintHelpers)

set( AVR_PROGRAMMER usbtiny )
set( AVR_MCU atmega328p )
set( AVR_MCU_SPEED 16000000UL )

set( cur_path ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(GET cur_path PARENT_PATH parent_path)
set( CMAKE_TOOLCHAIN_FILE ${parent_path}/cmake-avr-toolchain/avr-gcc-toolchain.cmake )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


cmake_print_variables(CMAKE_TOOLCHAIN_FILE)
cmake_print_variables(parent_path)


project( tinyamp )

set( CMAKE_BUILD_TYPE Release )

#enable_language( ASM )

set( sources
    app/tinyamp.cpp
)

add_avr_library (USART src/USART.cpp)
target_include_directories (USART PUBLIC include)

add_avr_executable( tinyamp ${sources}  )
avr_target_link_libraries (tinyamp USART)