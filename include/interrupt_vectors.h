#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>

extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));

// static std::uint8_t state = 0;
void __vector_13(void)
{
    hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
    hal::TimerT<std::uint8_t, std::uint8_t, std::uint16_t, 0>::irq_reset(start_time);
}
