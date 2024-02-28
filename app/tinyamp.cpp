#include <util/delay.h>
#include "usart_dbg.h"
#include "digital_out.h"

int main()
{
   
    utils::UsartDbg dbg;
    
    const utils::DigitalOut<mcal::r::port_b,5> led;
    
    for (;;)
    {
        _delay_ms(500);
        led.set_bit(false);
        _delay_ms(100);
        led.set_bit(true);
    
    }
}