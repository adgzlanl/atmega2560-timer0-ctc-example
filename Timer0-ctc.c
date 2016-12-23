/*
 * timer0-ctc.c
 *
 * Created: 12/23/2016 6:55:37 PM
 * Author : aniladiguzel
 * we assume that F_CPU 16MHZ and Prescale Factor=16MHZ/1024(prescale) ==>15625KHZ ==> Timer0Tick=1/15625KHZ=0,000064 sn per tick
 * and timer0 is 8 bit it means 255 therefore, 256*0,000064=0,016384 sn per timer over flow 
 */ 

#include <avr/io.h>


int main(void)
{
  uint16_t timerOverflowCount=0;
  DDRB=0xff;         //configure PORTB as output
  TCCR0A = (1 << WGM01); //Set CTC Bit
  OCR0A = 156; //http://eleccelerator.com/avr-timer-calculator/ we calculated  above mendtioned conditions and we get Total Timer Ticks:
  TIMSK0 = (1 << OCIE0A);
  TCCR0B = (1<<CS00) | (1<<CS02);
  Serial.begin(9600);
  
  while(1)
  {
    while (!(TIFR0 & (1<<OCF0A)));
    OCR0A = 0x00;
    TIFR0=0x02; //clear timer1 overflow flag
    timerOverflowCount++;
    Serial.println(timerOverflowCount);
    if (timerOverflowCount>=2000)
    {
      PORTB ^= (0x01 << PB7);
      timerOverflowCount=0;
    }
  }
}