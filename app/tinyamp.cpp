#include "tinylib_utils.h"
#include "hal.h"
#include <cstdint>
#include <util/delay.h>
#undef SERIAL_DBG
#define INTERRUPTS

// #include <avr/io.h>
// #include <avr/interrupt.h>

// used in interrupt_vectors, so defined here
constexpr std::uint16_t start_time = UINT16_C(0xFFAD);
constexpr std::uint8_t clock_scaling = 16;
constexpr std::uint8_t spi_idx = 0;
constexpr std::uint8_t spi_mode = 0;
constexpr std::uint8_t spi_cs_port = 0;
constexpr std::uint8_t spi_cs_pin = 2;
using ad_cs_digital_pin_t = utils::DigitalPin<std::uint8_t, std::uint8_t, spi_cs_port, spi_cs_pin>;
using spi_static_t = utils::SpiComStatic<std::uint8_t, std::uint8_t, spi_idx, clock_scaling, spi_mode, ad_cs_digital_pin_t>;
using Mpc3202_t = utils::Mpc3202<std::uint8_t, std::uint8_t, spi_static_t, ad_cs_digital_pin_t>;
using AdIcStatic_t = ifc::AdIcStaticIf<Mpc3202_t, std::uint8_t, std::uint8_t, spi_static_t, ad_cs_digital_pin_t>;
using timer_1_t = hal::TimerT<std::uint8_t, std::uint8_t, std::uint16_t, 0>;
static volatile std::uint8_t spi0_state = 0;
static volatile std::uint16_t ad_raw_val_0 = 0;

#ifdef INTERRUPTS

#include "../include/interrupt_vectors.h"
#endif

int main()
{
  utils::DigitalPin<std::uint8_t, std::uint8_t, 0, 1> led;
  led.set_to_out_pin();
  led.set_pin(true);
#ifdef INTERRUPTS
  utils::Interrupts::enable_all_interrupts();

  utils::TimerIf<timer_1_t, std::uint8_t, std::uint8_t, std::uint16_t, 0>::init(start_time);
#endif
  constexpr std::uint32_t i2c_freq = UINT32_C(100000);
  constexpr std::uint8_t I2C_BUS_IDX = 0;
  constexpr std::uint8_t MPC4442_1_CHIP_SELECT_ADDRESS = 0;
  constexpr std::uint8_t POTI_ID_0 = 0;
  constexpr std::uint8_t POTI_ID_3 = 3;
  constexpr std::uint8_t MPC4442_1_ADDRESS = 88;

  using I2C_t = utils::I2cCom<std::uint8_t, std::uint8_t, I2C_BUS_IDX, i2c_freq>;
  using Mp44xx_t = utils::Mp44xx<I2C_t *, std::uint8_t, std::uint8_t>;
  using PotiIcIf_t = ifs::PotiIcIf<Mp44xx_t, I2C_t *, std::uint8_t, std::uint8_t>;
  I2C_t i2c;
  PotiIcIf_t poti_ic_1(MPC4442_1_ADDRESS, MPC4442_1_CHIP_SELECT_ADDRESS, &i2c);
  utils::DigiPoti<PotiIcIf_t, std::uint8_t, std::uint8_t> poti_1(poti_ic_1, POTI_ID_0);
  utils::DigiPoti<PotiIcIf_t, std::uint8_t, std::uint8_t> poti_2(poti_ic_1, POTI_ID_3);
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

  spi_static_t::init();
#ifdef INTERRUPTS
  spi_static_t::enable_interrupt();
#endif

  // AdIcStatic_t mp3202;
  // std::uint16_t t = mp3202.get_raw_value();

  std::uint8_t i = 0;
  for (;;)
  {
    i++;
// #define ADMAN
#ifdef ADMAN
    AdIcStatic_t::enable();
    _delay_us(10);
    AdIcStatic_t::template send<0>();
    AdIcStatic_t::bus_transmission_wait_blocking();
    AdIcStatic_t::read();

    AdIcStatic_t::template send<1>();
    AdIcStatic_t::bus_transmission_wait_blocking();
    std::uint8_t d2 = AdIcStatic_t::read();

    AdIcStatic_t::template send<2>();
    AdIcStatic_t::bus_transmission_wait_blocking();
    std::uint8_t d3 = AdIcStatic_t::read();

    AdIcStatic_t::disable();
#ifdef SERIAL_DBG
    dbg.print_hex_byte(d2);
    dbg.print_hex_byte(d3);

    // dbg.print_ascii('A');
    dbg.print_ascii(10);
    dbg.usart_dbg_flush();
#endif
#endif
    i++;

    led.set_pin(true);
    poti_1.set_volatile(i);
    poti_2.set_volatile(i);
    i2c.flush_blocking();

    _delay_ms(500);
    led.set_pin(false);
    _delay_ms(500);
  }
}