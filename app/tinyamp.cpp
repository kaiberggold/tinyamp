#include "tinylib_utils.h"
#include "hal.h"
#include <cstdint>
#include <util/delay.h>
// #include <avr/interrupt.h>
constexpr std::uint16_t start_time = UINT16_C(0xFC00);
#include "../include/interrupt_vectors.h"
//  #include <avr/io.h>
//  #undef SERIAL_DBG

// ISR(TIMER1_OVF_vect)
// {
//   hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
//   hal::HalRegAccess<std::uint8_t, std::uint16_t, hal::TCNT134[0]>::reg_set(100U);
// }

int main()
{
  utils::Interrupts::enable_all_interrupts();
  hal::TimerT<std::uint8_t, std::uint8_t, std::uint16_t, 0>::init(start_time);
  constexpr std::uint32_t i2c_freq = UINT32_C(100000);
  constexpr std::uint8_t I2C_BUS_IDX = 0;
  constexpr std::uint8_t POTI_IC_1_CHIP_SELECT_ADDRESS = 0;
  constexpr std::uint8_t POTI_ID_0 = 0;
  constexpr std::uint8_t POTI_ID_3 = 3;
  constexpr std::uint8_t POTI_CHIP_ADDRESS = 88;

  utils::I2cCom<std::uint8_t, std::uint8_t, I2C_BUS_IDX, i2c_freq> i2c;
  utils::Mp44xx<std::uint8_t, std::uint8_t, I2C_BUS_IDX, i2c_freq> poti_ic_1(POTI_CHIP_ADDRESS, POTI_IC_1_CHIP_SELECT_ADDRESS, &i2c);
  utils::DigiPoti<std::uint8_t, std::uint8_t, I2C_BUS_IDX, i2c_freq> poti_1(poti_ic_1, POTI_ID_0);
  utils::DigiPoti<std::uint8_t, std::uint8_t, I2C_BUS_IDX, i2c_freq> poti_2(poti_ic_1, POTI_ID_3);
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
  // constexpr std::uint8_t clock_scaling = 16;
  // constexpr std::uint8_t spi_idx = 0;
  // utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 2> cs_ad;
  // cs_ad.set_pin(true);
  // utils::SpiCom<std::uint8_t, std::uint8_t, spi_idx, cs_ad, clock_scaling> spi;
  // spi.init();

  utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 5> led;
  led.set_to_out_pin();
  led.set_pin(false);
  std::uint8_t i = 0;
  for (;;)
  {
    i++;
    // cs_ad.set_pin(false);
    // spi.send(0x01);
    // while (spi.transmission_active())
    // {
    // }
    // spi.read();
    // spi.send(0x90);
    // while (spi.transmission_active())
    // {
    // }
    // std::uint8_t d2 = spi.read();
    // spi.send(0x00);
    // while (spi.transmission_active())
    // {
    // }
    // std::uint8_t d3 = spi.read();
    // cs_ad.set_pin(true);
    // dbg.print_hex_byte(d2);
    // dbg.print_hex_byte(d3);
    // dbg.print_ascii(10);
    // dbg.usart_dbg_flush();

    // _delay_ms(2000);
    // i++;
    // led.set_pin(true);
    // // poti_1.set_volatile(i);
    // // poti_1.set_volatile(d3);
    // // i2c.flush_blocking();

    // _delay_ms(500);
    // led.set_pin(false);
    // _delay_ms(500);
  }
}