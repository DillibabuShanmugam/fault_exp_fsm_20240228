asm("eint");

  WDTCTL = WDTPW | WDTHOLD;
  state = 0;
  P1DIR = 0x00;
#include "../shared/omsp_system.h"

volatile int state;

// #define NMI_VECTOR          (0x0018)   // Vector 12  (0xFFF8) - Non-maskable
interrupt(13) NMI_ISR(void)  // !!! interrupt(x) = interrupt(vector + 1)
{
//  P1OUT = 0x00; // clear nmi here
  while(1); 
}

int main() {

  asm("eint");

  WDTCTL = WDTPW | WDTHOLD;
  state = 0;
  P1DIR = 0x00;
  
  while (1) {
	P1OUT = 0x80;
	switch (state) {
	case 0:
	  P2OUT = 0x0;
	  if (P2IN == 0x1) state = 1;
	  break;
	case 1:
	  P2OUT = 0x1;
	  if (P2IN == 0x0) state = 0;
	  break;
	}
	P1OUT = 0x00;	  

    if (P2IN != P2OUT) {
        P1OUT = 0x05;
    }

  }
  
  return 0;
}
