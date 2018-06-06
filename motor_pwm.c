/*Softveres PWM
        
        timer2ben cnt pörög, 2 duty adja meg éppen mekkro a a pulzus szélesség 
        if (cnt < duty) ill (cnt > duty) adja meg mi történjen a periódus 
        "1" ill "0" - ás részei alatt
        
        leds változóba tároljuk a ledek tetszőleges kimeneti értékét 
        (itt most csak egy 1xű pl. van a progiban)
        t változó állítja be, h mien sebesen változzon a duty értéke
        dir csak az irányváltó flag szerepében tetszeleg, h folytonos legyen a pulzálás
        */

#define F_CPU (16000000UL)
#define MAX_DUTY 255
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>


void port_init();
void timer2_init();
void led_out(unsigned char led);

unsigned char leds=0x00, cnt=0, t=0;
unsigned char duty1, duty2, duty3, duty4;


int main()
{
	
  port_init();	
  timer2_init();

  sei();
  
  duty1 = 254;
  duty2 = 0;
  duty3 = 252;
  duty4 = 100;
  
  while(1)
    {
      /*if((TCNT2-1) < duty1) PORTB &= ~(1 << PB4);
      else PORTB |= (1 << PB4);*/
      
      if((TCNT2-1) < duty1) leds &= 0xFE;
      else leds |= 0x01; 
      
      if((TCNT2-1) < duty2) leds &= 0xFD;
      else leds |= 0x02; 
      
      if((TCNT2-1) < duty3) leds &= 0xFB;
      else leds |= 0x04; 
      
      if((TCNT2-1) < duty4) leds &= 0xF7;
      else leds |= 0x08; 
      
      led_out(leds); 
    }
  
  
  return 0;
}




///////////////////////////////
////////                //////
//////////////////////////////

void port_init()
{
	DDRA=0xFF;
	DDRB=0xF0;
	DDRC=0xF8;
	DDRD=0xF0;
	DDRE=0xC0;
	DDRG=0x00;
}

void timer2_init()
{
        TIMSK|=(1<<TOIE2);
        TCCR2|=(1<<CS22);

}

void led_out(unsigned char led)
{
	PORTD=led;
	PORTB=(led<<4);
}

///////

ISR(TIMER2_OVF_vect)
{
	TCNT2=0x00;
		
	
	
}

