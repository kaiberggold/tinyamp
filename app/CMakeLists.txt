
add_avr_executable(
   tinyamp
   tinyamp.cpp
   ../include/interrupt_vectors.h
   )

avr_target_link_libraries(
   tinyamp
   utils
   )