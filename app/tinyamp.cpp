#include <util/delay.h>
#include "usart_dbg.h"
#include "digital_port.h"
#include <cstdint>





int main()
{
   
    utils::UsartDbg dbg;
    dbg.usart_dbg_init();
    _delay_ms(100);
    dbg.usart_transmit_byte(64);
    for(int i=0;i<26;i++)
    {
        dbg.print_ascii(65+i);
    }
    //const utils::DigitalOut<mcal::r::port_b,5> led;
    utils::DigitalPort<std::uint8_t,std::uint8_t,0> portb;

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
        portb.set_port(1U <<5U);
        _delay_ms(500);
        portb.set_port(0U);
    
    }
}