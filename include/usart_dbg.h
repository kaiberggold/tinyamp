
#include<std>
#include <mcal.h>
namespace usart{

    class UsartDbg
    {
    private:
        constexpr std::array<std::uint8_t, std::uint8_t buffer_size> send_buffer;

    public:
        usart_dbg_init(std::uint32_t baud_rate);

        send_byte(std::uint8_t data);
        usart_dbg_step();
        
    }
}