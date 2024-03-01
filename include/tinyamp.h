// enum portidx
DigitalPort<std::uint8_t,std::uint8_t, 0>  port_b;
DigitalPin(port_b,3) led;

UsartCom(0,9600) usart;
ByteBufferCom(usart,256) usart_byte_buffer;
SerialDbg(usart) dbg;

I2CCom(0,100) i2c;
ByteBufferCom(i2c,200) i2c_buffer;

PotiIc(MPC4x,0b01000'0100,i2c_buffer) poti_ic1;
DigiPot(poti_ic1,0) poti_volume;
DigiPot(poti-ic2,1) poti_gain,

DigitalPin(port_b) r1;
DigitalPin(port_b) r2;

RotaryDecoder(r1,r2) rotary_volume;


