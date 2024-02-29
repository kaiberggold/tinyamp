#include <util/delay.h>
#include "usart_dbg.h"
#include "digital_out.h"

int main()
{
   
    utils::UsartDbg dbg;
    dbg.usart_dbg_init();
    _delay_ms(100);
    dbg.usart_transmit_byte(65);
    const utils::DigitalOut<mcal::r::port_b,5> led;
     std::uint8_t i=0;
     for (;;)
     {
        if (i==10)
        {
            dbg.print_ascii(65);
            i=0;
        }
            i++;
        _delay_ms(100);
        
        dbg.usart_dbg_step();
        led.set_bit(false);
        _delay_ms(100);
        led.set_bit(true);
    
    }
}