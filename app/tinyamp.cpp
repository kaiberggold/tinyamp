#include "tinylib_utils.h"
#include <cstdint>
#include <util/delay.h>
// #include <avr/io.h>
#undef SERIAL_DBG
int main()
{

  utils::I2cCom<std::uint8_t, std::uint8_t, 0> i2c(UINT32_C(100000));
  utils::PotiIc<std::uint8_t, std::uint8_t, 0> poti_ic_1(88, 0, &i2c);
  utils::DigiPoti<std::uint8_t, std::uint8_t, 0> poti_1(poti_ic_1, 0);
  utils::DigiPoti<std::uint8_t, std::uint8_t, 0> poti_2(poti_ic_1, 3);
  i2c.init();
#ifdef SERIAL_DBG
  utils::UsartDbg dbg(9600);
  // dbg.usart_transmit_byte(64);
  // for (int i = 0; i < 26; i++)
  // {
  //   dbg.print_ascii(65 + i);
  // }
#endif
  utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 5> led;
  led.set_to_out_pin();
  led.set_pin(false);
  int i = 0;
  for (;;)
  {
    i++;
    led.set_pin(true);
    poti_1.set_volatile(i);
    poti_2.set_volatile(i % 100);

    i2c.flush_blocking();

    // i2c.buffer_reset();

    _delay_ms(500);
    led.set_pin(false);
    _delay_ms(500);
  }
}
