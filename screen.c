#include "avr/io.h"
#include "util/delay.h"
#define PERSISTENCE 5
#define COUNTTIME 200

int main(void)
{
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
    unsigned int i = 0;
    unsigned char DIG1, DIG2, DIG3, DIG4;
    DDRD = 0xFF;
    DDRB = 0xFF;
    PORTB = 0xFF;
    while(1){
        i++;
        if(i>9999){
            i = 0;
        }

        DIG4 = i % 10;
        DIG3 = (i / 10) % 10;
        DIG2 = (i / 100) % 10;
        DIG1 = (i / 1000);
        for (int j = 0; j < COUNTTIME/PERSISTENCE/4; j++) {
            PORTD = ledDigits[DIG4];
            PORTB = ~(1<<1);
            _delay_ms(PERSISTENCE);
            PORTD = ledDigits[DIG3];
            PORTB = ~(1<<2);
            _delay_ms(PERSISTENCE);
             PORTD = ledDigits[DIG2];
            PORTB = ~(1<<3);
            _delay_ms(PERSISTENCE);
            PORTD = ledDigits[DIG1];
            PORTB = ~(1<<4);
            _delay_ms(PERSISTENCE);
        }
    }
 }
