#include "tinylib_utils.h"
#include <cstdint>
#include <util/delay.h>
// #include <avr/io.h>
#undef SERIAL_DBG
int main()
{
  constexpr std::uint32_t i2c_freq = UINT32_C(100000);
  utils::I2cCom<std::uint8_t, std::uint8_t, 0, i2c_freq> i2c;
  utils::PotiIc<std::uint8_t, std::uint8_t, 0, i2c_freq> poti_ic_1(88, 0, &i2c);
  utils::DigiPoti<std::uint8_t, std::uint8_t, 0, i2c_freq> poti_1(poti_ic_1, 0);
  utils::DigiPoti<std::uint8_t, std::uint8_t, 0, i2c_freq> poti_2(poti_ic_1, 3);
  i2c.init();
#ifdef SERIAL_DBG
  utils::UsartDbg dbg(9600);
  // dbg.usart_transmit_byte(64);
  // for (int i = 0; i < 26; i++)
  // {
  //   dbg.print_ascii(65 + i);
  // }
#endif

  // SPI
  constexpr std::uint8_t clock_scaling = 128;
  constexpr std::uint8_t spi_idx = 0;
  // utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 2> cs_ad;
  // cs_ad.set_pin(true);
  // utils::SpiCom<std::uint8_t, std::uint8_t, spi_idx, cs_ad, clock_scaling> spi;
  // spi.init();
  // cs_ad.set_pin(false);
  // spi.send(137U);
  // while (spi.transmission_active())
  // {
  // }
  // cs_ad.set_pin(true);
  // std::uint8_t d1 = spi.read();
  // spi.send(128U);
  // while (spi.transmission_active())
  // {
  // }
  // std::uint8_t d2 = spi.read();
  // spi.send(0U);
  // while (spi.transmission_active())
  // {
  // }
  // std::uint8_t d3  = spi.read();
  utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 5> led;
  led.set_to_out_pin();
  led.set_pin(false);
  int i = 0;
  for (;;)
  {
    i++;
    led.set_pin(true);
    poti_1.set_volatile(i);
    poti_2.set_volatile((i + 32) % 256);

    i2c.flush_blocking();

    _delay_ms(500);
    led.set_pin(false);
    _delay_ms(500);
  }
}