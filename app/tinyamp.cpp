#include "tinylib_utils.h"
#include <cstdint>
#include <util/delay.h>

int main()
{

  utils::I2cCom<std::uint8_t, std::uint8_t, 0> i2c(UINT32_C(100000));
  utils::PotiIc<std::uint8_t, std::uint8_t, 0> poti_ic_1(1, 2, i2c);
  utils::DigiPoti<std::uint8_t, std::uint8_t, 0> poti_1(poti_ic_1, 1);
  i2c.init();

  utils::UsartDbg dbg(9600);

  dbg.usart_transmit_byte(64);
  for (int i = 0; i < 26; i++)
  {
    dbg.print_ascii(65 + i);
  }
  utils::DigitalPort<std::uint8_t, std::uint8_t, 0> portb;
  portb.set_to_out_mask(1U << 5U);
  std::uint8_t i = 0;
  for (;;)
  {
    if (i == 10)
    {
      dbg.print_ascii(65);
      i = 0;
    }
    i++;
    _delay_ms(50);

    dbg.usart_dbg_step();
    portb.set_port(1U << 5U);
    _delay_ms(50);
    portb.set_port(0U);
    poti_1.set_volatile(44);
    _delay_ms(1000);
    poti_1.set_volatile(94);
  }
}