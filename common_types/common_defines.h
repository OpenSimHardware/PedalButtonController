#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H


#define OSHSTUDIOVERSION 15
#define FIRMWARERELEASE 15

//Input/output usb packet
#define BUFFSIZE 64
#define USEDPINS 32
#define MAX_AXES 6
#define MAX_SINGLE_ENCODERS 14

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8))



#endif // COMMON_DEFINES_H
