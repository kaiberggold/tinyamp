
add_avr_executable(
   tinyamp
   tinyamp.cpp
   ../include/interrupts.h
   )

avr_target_link_libraries(
   tinyamp
   utils
   )