#include "hal.h"

extern "C" void __vector_12(void) __attribute__((signal, used, externally_visible));

static std::uint8_t state = 0;
void __vector_12(void)
{
    hal::HalDigitalPort<std::uint8_t, std::uint8_t, 0>::reg_xor(1U << 5);
}
