
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "USART.h"

#define volatileWiper0     0x00
#define mcpAddress         44

void write(unsigned char Register, unsigned short Value)
{
  
  unsigned char firstCommandByte = 0x00;  // Prep the firstCommandByte with 00b for writes
  unsigned char secondCommandByte = 0x00; // Empty data byte
  unsigned short  tempWord = Value;
  unsigned char tempByte;
  
  // Prep the command bytes to write to the digital potentiometer
  Register *= 16;                // Shift the value of Register to the left by four bits
  firstCommandByte |= Register;  // Load the register address into the firstCommandByte
  tempWord &= 0x0100;            // Clear the top 7 bits and the lower byte of the input value to pick up the two data bits
  tempWord /= 256;               // Shift the top byte of the input value to the right by one byte
  tempByte = (unsigned char)(tempWord);     // Store the top byte of the input value in a byte sized variable
  firstCommandByte |= tempByte;  // Load the two top input data bits into the firstCommandByte
  tempWord = Value;              // Load the input value into the tempWord
  tempWord &= 0x00FF;              // Clear the top byte
  secondCommandByte = (unsigned char)(tempWord);  // Store the lower byte of the input value in the secondCommandByte

   printString("Start\r\n");
   i2cStart();
   
   printString("Adress: ");
   i2cSend(88);
   printString("Startr\n");
   
   
   printString("First: ");
   printByte(firstCommandByte);  
   i2cSend(firstCommandByte);
   printString("Second\r\n");

   printString("Second: ");  
   printByte(secondCommandByte); 
   i2cSend(secondCommandByte);
   printString("Second\r\n"); 

   printString("Stop\r\n");     
   i2cStop();
   
  // Write to the digital potentiometer
  //Wire.beginTransmission(_ChipAddress_7bit);   // Begin the I2C transmission
  //Wire.write(firstCommandByte);                // Queue up the firstCommandByte
  //Wire.write(secondCommandByte);               // Queue up the secondCommandByte
  //Wire.endTransmission();                      // Transmit the write command
 
}



int main()


{
    initUSART();
  
    printString("Hallo Kai!\r\n");  
    initI2C();
    printString("Init\r\n"); 
    unsigned int i=0;
    while (1)
    {
      write(volatileWiper0, i);
      i++;
      if (i>127)
        i=0;
      printString("Write");printByte(i);printString("\r\n");  

      _delay_ms(1000);
    }

    /* Set built-in LED pin as output
    DDRB |= (1 << DDB5);
    while (1) {
        PORTB |=  (1 << PB5);   // LED on
    
        _delay_ms(1000);
        PORTB &= ~(1 << PB5);   // LED off
        _delay_ms(1000);

    }*/
    return 0;
}
