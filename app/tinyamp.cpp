#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

int main()
{
    initUSART();
  
     
    // Set built-in LED pin as output
    DDRB |= (1 << DDB5);
    while (1) {
    printString("Hallo Kai!\r\n");  
        PORTB |=  (1 << PB5);   // LED on
        _delay_ms(100);
        PORTB &= ~(1 << PB5);   // LED off
        _delay_ms(100);
        PORTB |=  (1 << PB5);   // LED on
        _delay_ms(100);
        PORTB &= ~(1 << PB5);   // LED off
        _delay_ms(100);
      
    }
    return 0;
}
