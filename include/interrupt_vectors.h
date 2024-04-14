#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>

extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));

// static std::uint8_t state = 0;
void __vector_13(void)
{
    hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);

    std::uint8_t sreg = hal::HalRegAccess<std::uint8_t, std::uint8_t, hal::SREG>::get_reg();
    hal::disable_all_interrupts();
    hal::HalRegAccess<std::uint16_t, std::uint16_t, hal::TCNT134[0]>::reg_set(UINT16_C(0xEE00));
    hal::HalRegAccess<std::uint8_t, std::uint8_t, hal::SREG>::reg_set(sreg);
}
