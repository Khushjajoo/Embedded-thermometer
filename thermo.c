/*****************************************************************************
* thermo.c - This program is for showing the temperature in the screen which is sensed by the given sensor
* Temperature will be shown in Fareneheit and in Celsius when the switch is pressed on the given screen.
* Revision
* Date          Author              Revision
* 03/28/2022    Khushkumar Jajoo    Writing the code
* 04/02/2022    Khushkumar Jajoo    Touching up the code and adding comments
* 03/29/2022    Khushkumar Jajoo    Running the code on arduino and testing it on the circuit

REFERENCE
* ECE 231 Spring 22, Lecture slides 11,12 13,14 from the professor, David McLaughlin
* ECE 231, Spring 22 - references od code from the in lecture slides professor, David McLaughlin
******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#define PERSISTENCE 5
#define COUNTTIME 200


void adc_init (void);
unsigned int get_adc (void);
void print_celcius (double celcius);
void print_fa (double fahrenheit);

int main(void) 
{
    double digitalValue, tempcelsius; 
    // initializing the values
    DDRD = 0xFF; 
    DDRB = 0xFF; 
    PORTB = 0xFF; 
    adc_init();

    PORTC = 1<<PORTC4;

    while(1)
    {
        digitalValue = get_adc();
        tempcelcius = (digitalValue-750)/10 + 25; // converting the digital value to celsius
        tempfarenheit = tempcelcius*9.0/5.0+32.0; // converting the celsius to farenheit
        if ((!(PINC & (1<<PINC4)))){
            print_celcius(tempcelcius); // print the celsius value when button is pressed

        }

        else{
              
            print_fa(tempfarenheit); // print the fahrenheit value when button is not pressed
        }
    }
    return 0;
}


void adc_init(void) 
{
    DDRC = 0x00; 
    ADMUX = 0xC0;
    ADCSRA = 0x87;
}

unsigned int get_adc(){
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADIF))==0);
    return ADCL|(ADCH<<8);
}

void print_celcius(double celcius){

    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67}; // array of singled leds in a digit
    unsigned char DIG1, DIG2, DIG3, DIG4; // digits of the screen
    
    // prinitng the celsius value
    for (int j = 0; j < COUNTTIME/PERSISTENCE/4; j++) {

        DIG4 = 0x39;
        PORTD = DIG4;
        PORTB = !(1<<1);
        _delay_ms(PERSISTENCE);

        celcius = celcius*10.0; // adjusting the celsius value by 10

        DIG3 =  fmod(celcius, 10);
        PORTD = ledDigits[DIG3];
        PORTB = !(1<<2);
        _delay_ms(PERSISTENCE);

        DIG2 = fmod((celcius/10), 10);
        PORTD = ledDigits[DIG2];
        PORTB = !(1<<3);
        _delay_ms(PERSISTENCE);

        PORTD = 0x80;
        PORTB = !(1<<3);
        _delay_ms(PERSISTENCE);

        DIG1 = fmod ((celcius/100),10);
        PORTD = ledDigits[DIG1];
        PORTB = !(1<<4);
        _delay_ms(PERSISTENCE);


    }
}

void print_fa(double farenheit){
    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67}; // array of singled leds in a digit
    unsigned char DIG1, DIG2, DIG3, DIG4; // digits of the screen
    // prinitng the fahrenheit value
    for (int j = 0; j < COUNTTIME/PERSISTENCE/4; j++) {
        
        DIG4 = 0x71;
        PORTD = DIG4;
        PORTB = !(1<<1);
        _delay_ms(PERSISTENCE);

        farenheit = farenheit*10.0; // adjusting the decimal value

        DIG3 = fmod(farenheit, 10);
        PORTD = ledDigits[DIG3];
        PORTB = !(1<<2);
        _delay_ms(PERSISTENCE);

        DIG2 = fmod((farenheit/10), 10);
        PORTD = ledDigits[DIG2];
        PORTB = !(1<<3);
        _delay_ms(PERSISTENCE);

        PORTD = 0x80;
        PORTB = !(1<<3);
        _delay_ms(PERSISTENCE);

        DIG1 = fmod ((farenheit/100),10); 
        PORTD = ledDigits[DIG1];
        PORTB = !(1<<4);
        _delay_ms(PERSISTENCE);
    }
    
}
