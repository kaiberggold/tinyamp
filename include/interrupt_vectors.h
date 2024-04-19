#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>

// timer1 overflow
extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));
void __vector_13(void)
{
    AdIcStatic_t::enable();
    AdIcStatic_t::template send<0>();
    //  hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
    hal::TimerT<std::uint8_t, std::uint8_t, std::uint16_t, 0>::irq_reset(start_time);
}

// spi0 finished
extern "C" void __vector_17(void) __attribute__((signal, used, externally_visible));
void __vector_17(void)
{
    spi0_state = spi0_state + 1;
    switch (spi0_state)
    {
    case 1:

        AdIcStatic_t::read();
        AdIcStatic_t::template send<1>();
        break;
    case 2:
        ad_raw_val_0 = static_cast<std ::uint16_t>(AdIcStatic_t::read()) << 8;
        AdIcStatic_t::template send<2>();
        break;
    default:
        ad_raw_val_0 |= static_cast<std ::uint16_t>(AdIcStatic_t::read());
        spi0_state = 0;
        AdIcStatic_t::disable();
        break;
    }
}
