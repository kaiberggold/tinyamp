#include <util/delay.h>
#include <cstdint>
#include "utils.h"

int main()
{
   
    utils::UsartDbg dbg(9600);
    _delay_ms(100);
    dbg.usart_transmit_byte(64);
    for(int i=0;i<26;i++)
    {
        dbg.print_ascii(65+i);
    }
    utils::DigitalPort<std::uint8_t,std::uint8_t,0> portb;
    portb.set_to_out_mask(1U<<5U);
     std::uint8_t i=0;
     for (;;)
     {
        if (i==10)
        {
            dbg.print_ascii(65);
            i=0;
        }
            i++;
        _delay_ms(50);
        
        dbg.usart_dbg_step();
        portb.set_port(1U <<5U);
        _delay_ms(50);
        portb.set_port(0U);
    
    }
}