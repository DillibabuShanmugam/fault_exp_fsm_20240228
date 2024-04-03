#include "../shared/omsp_system.h"

volatile int i, j, k;
volatile int localcnt;

// #define NMI_VECTOR          (0x0018)   // Vector 12  (0xFFF8) - Non-maskable
interrupt(13) NMI_ISR(void)  // !!! interrupt(x) = interrupt(vector + 1)
{
//  P1OUT = 0x00; // clear nmi here
  while(1); 
}

int main() {

  asm("eint");

  WDTCTL = WDTPW | WDTHOLD;
  localcnt = 0;
  P1DIR = 0x00;

  while (1) {
    P1OUT = 0x80;  // trigger up
      for(j=0; j<3; j++) {
        for(k=0; k<3; k++) {
          localcnt++;
        }
      }
      P2OUT = localcnt;
    P1OUT = 0x00;  // trigger down

  
    if (P2IN != P2OUT) {
        P1OUT = 0x05;
    }
  }
  
  return 0;
}
