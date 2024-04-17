#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>

extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));

static volatile std::uint8_t spi0_state = 0;
void __vector_13(void)
{
    spi0_state = 0;
    // AdIcStatic_t::enable();

    // AdIcStatic_t::template send<0>();
    //  hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
    //  hal::TimerT<std::uint8_t, std::uint8_t, std::uint16_t, 0>::irq_reset(start_time);
}
