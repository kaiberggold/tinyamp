// enum portidx
DigitalPort<std::uint8_t,std::uint8_t>(idx0)  port_b;
DigitalPin(port_b) led;

UsartCom(idx0,9600) usart;
ByteBufferCom(usart,256) usart_byte_buffer;
SerialDbg(usart) dbg;

I2CCom(idx0,100) i2c;
ByteBufferCom(i2c,200) i2c_buffer;

PotiIc(MPC4x,0b01000'0100,i2c_buffer) poti_ic1;
DigiPot(poti_ic1,0) volume;
DigiPot(poti-ic2,1) gain,


