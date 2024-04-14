#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>

extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));

// static std::uint8_t state = 0;
void __vector_13(void)
{
    hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
    std::uint8_t sreg;
    sreg = hal::HalRegAccess<std::uint8_t, std::uint8_t, hal::SREGa>::get_reg();
    hal::disable_all_interrupts();
    /* Set TCNT1 to i */
    // TCNT1 = 0xEE00;
    hal::HalRegAccess<std::uint16_t, std::uint16_t, hal::TCNT134[0]>::reg_set(0xEE00);
    /* Restore global interrupt flag */
    hal::HalRegAccess<std::uint8_t, std::uint8_t, hal::SREGa>::reg_set(sreg);
}
