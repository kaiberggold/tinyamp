#include "i2c.h"
#include "USART.h"
#include <avr/io.h>

void initI2C(void) {


  printString("initI2C\r\n");  
  TWBR = 72;                               /* set bit rate, see p. 242 */
                                     /* 16MHz / (16+2*TWBR*1) ~= 100kHz */
  TWCR |= (1 << TWEN);                                       /* enable */
}

void i2cWaitForComplete(void) {
  printString("i2cWaitForComplete\r\n");
  printString("TWCR: ");
  printByte(TWCR);
  printString("\r\n");
  loop_until_bit_is_set(TWCR, TWINT);
  printString("Complete\r\n");
}

void i2cStart(void) {
  printString("i2cstart\r\n");  
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
  i2cWaitForComplete();
}

void i2cStop(void) {
    printString("i2cstop\r\n");  
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
}

uint8_t i2cReadAck(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
  i2cWaitForComplete();
  return (TWDR);
}

uint8_t i2cReadNoAck(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN));
  i2cWaitForComplete();
  return (TWDR);
}

void i2cSend(uint8_t data) {
  printString("i2cSend (");
  printByte(data);
  printString(")\\r\n\r\nr\n");

  TWDR = data;
  TWCR = (_BV(TWINT) | _BV(TWEN));                  /* init and enable */
  i2cWaitForComplete();
}
