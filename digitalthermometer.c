#include <avr/io.h>

void uart_init (void);
void send_char (char);

int main (void)
{
    uart_init();

    while (1)
    {
        send_char('W');
        send_char('O');
        send_char('W');
        send_char(10);
        send_char(13);

    }
}

void uart_init (void)
{ 
    UCSR0B =  (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0L = 103;
}

void send_char (char c)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}