#include "hal.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
#include <cstdint>
#include "usart_dbg.h"
// #include "rotary_decoder_if.h"

// timer1 overflow
extern "C" void __vector_13(void) __attribute__((signal, used, externally_visible));
void __vector_13(void)
{
    AdIcStatic_t::enable();
    AdIcStatic_t::template send<0>();
    utils::TimerIf<timer_1_t, std::uint8_t, std::uint8_t, std::uint16_t, 0>::irq_reset(start_time);
}

// pin change interrupt
extern "C" void __vector_4(void) __attribute__((signal, used, externally_visible));
void __vector_4(void)
{
    swi_1 = static_cast<std::uint8_t>(utils::DigitalPin<std::uint8_t, std::uint8_t, 1, 2>::get_pin());

    std::uint8_t new_state = rot_1_t::get_raw_state();
    if (new_state != rot_1_state_raw)
    {

        std::int8_t step = rot_1_t::get_step(rot_1_state_raw, new_state);
        rot_1_state_raw = new_state;
        if (step != 0)
        {
            rot_1_pos += step;
            rot_1_p[swi_1]->step(step);
            utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 0>::set_pin_toggle();
            dbg.print_hex_byte(step);
            dbg.print_ascii(10);
            dbg.usart_dbg_flush();
        }
    }
    // #ifdef SERIAL_DBG

    //     dbg.print_hex_byte(rot_1_pos);

    // #endif
}

// // spi0 finished
// extern "C" void __vector_17(void) __attribute__((signal, used, externally_visible));
// void __vector_17(void)
// {
//     spi0_state = spi0_state + 1;
//     switch (spi0_state)
//     {
//     case 1:

//         AdIcStatic_t::read();
//         AdIcStatic_t::template send<1>();
//         break;
//     case 2:
//         ad_raw_val_0 = static_cast<std ::uint16_t>(AdIcStatic_t::read()) << 8;
//         AdIcStatic_t::template send<2>();
//         break;
//     default:
//         ad_raw_val_0 |= static_cast<std ::uint16_t>(AdIcStatic_t::read());
//         spi0_state = 0;
//         AdIcStatic_t::disable();
//         break;
//     }
//}
