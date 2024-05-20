#include<avr/io.h>
#include<avr/interrupt.h>
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)
#define UART_BUFFER_SIZE (50)
#include "ring_buffer.h"

uint8_t buffer_array[UART_BUFFER_SIZE];
struct ring_buffer tx_buffer = {.buffer=&buffer_array[0],.size=UART_BUFFER_SIZE,.head=0U,.tail=0U,.full=false};

void mcu_init(){
  sei();//enable interrupts
}

void uart_clear_interrupt(){
  UCSR0A|=((1<<TXC0));
}

void uart_enable_tx_interrupt(){
  UCSR0B|=(1<<TXCIE0);
}

void uart_disable_tx_interrupt(){
  UCSR0B &=(~(1<<TXCIE0));
}

void uart_tx_start(){
  if(!ring_buffer_empty(&tx_buffer)){
    UDR0 = ring_buffer_peek(&tx_buffer); 
  }
}

ISR(USART0_TX_vect){
  if(ring_buffer_empty(&tx_buffer)){
    return;
  }
  
  ring_buffer_get(&tx_buffer);

  uart_clear_interrupt();

  if(!ring_buffer_empty(&tx_buffer)){
    uart_tx_start();
  }
}

void uart_putchar_interrupt(char c){

while(ring_buffer_full(&tx_buffer));

      uart_disable_tx_interrupt();
      bool tx_goingon = !ring_buffer_empty(&tx_buffer);
      ring_buffer_put(&tx_buffer,c);
      if(!tx_goingon){
        uart_tx_start();
      }
      uart_enable_tx_interrupt();
}

void USART_Init(unsigned int ubrr){
/* Set baud rate */
UBRR0L = (unsigned char)(ubrr>>8);
UBRR0H = (unsigned char)ubrr;

/* Enable receiver and transmitter and tx interrupt */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);

// uart_clear_interrupt();
uart_enable_tx_interrupt();
} // USART_Init

int main() {
  // put your setup code here, to run once:
  mcu_init();
  USART_Init (MYUBRR);
  while(1){
    uart_putchar_interrupt('h');
    uart_putchar_interrupt('e');
    uart_putchar_interrupt('l');
    uart_putchar_interrupt('l');
    uart_putchar_interrupt('o');
    uart_putchar_interrupt('\r');
  }

  return 0;
}

