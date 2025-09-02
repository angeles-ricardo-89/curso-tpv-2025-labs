// bits_emv.c
#include <stdio.h>
#include <stdint.h>

// Helpers para flags
#define SET(mask, bit)    ((mask) |=  (bit))
#define CLEAR(mask, bit)  ((mask) &= ~(bit))
#define CHECK(mask, bit)  (((mask) & (bit)) != 0)

int main(void) {
    // Ejemplo simple con un byte (pensemos en un TVR parcial)
    uint8_t tvr = 0x00;

    const uint8_t TVR_OFFLINE_DA_FAILED = 0x80; // bit 8
    const uint8_t TVR_ARQC_REQUESTED    = 0x40; // bit 7

    SET(tvr, TVR_OFFLINE_DA_FAILED);
    if (CHECK(tvr, TVR_OFFLINE_DA_FAILED)) {
        printf("TVR: Offline Data Authentication fallida\n");
    }

    SET(tvr, TVR_ARQC_REQUESTED);
    printf("TVR=0x%02X\n", tvr);

    CLEAR(tvr, TVR_OFFLINE_DA_FAILED);
    printf("TVR tras limpiar ODA_FAILED=0x%02X\n", tvr);

    // SHIFT: empaquetado/desempaquetado de nibbles (TLV u otros)
    uint8_t high = 0xA, low = 0x5;         // 0xA5
    uint8_t packed = (high << 4) | (low);  // A5
    printf("packed=0x%02X\n", packed);

    uint8_t unpack_high = (packed >> 4) & 0x0F;
    uint8_t unpack_low  = packed & 0x0F;
    printf("high=0x%X, low=0x%X\n", unpack_high, unpack_low);
    return 0;
}
