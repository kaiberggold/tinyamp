add_avr_executable(
   tinyamp
   tinyamp.cpp
   )
avr_target_link_libraries(
   tinyamp
   utils
   )