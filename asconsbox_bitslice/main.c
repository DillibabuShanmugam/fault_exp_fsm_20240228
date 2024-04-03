/* Includes:                                                                 */
/*****************************************************************************/
#include "../shared/omsp_system.h"


// #define NMI_VECTOR          (0x0018)   // Vector 12  (0xFFF8) - Non-maskable
interrupt(13) NMI_ISR(void)  // !!! interrupt(x) = interrupt(vector + 1)
{
//  P1OUT = 0x00; // clear nmi here
  while(1);
}

#include <stdint.h>

//const uint8_t IV[8] = {0x80, 0x40, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00};
//const uint8_t K1[8] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6};
//const uint8_t K2[8] = {0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0xcc};//round constant 0xf0 is xored with last byte of Nonce(N2), 0x3c
//const uint8_t N1[8] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d};
//const uint8_t N2[8] = {0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
  
//uint8_t  x0[8] = {0x80, 0x40, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00};
//uint8_t  x1[8] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6};
//uint8_t  x2[8] = {0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0xcc};
//uint8_t  x3[8] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d};
//uint8_t  x4[8] = {0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

int main(){

  uint16_t  x0[4] = {0x8040, 0x0C06, 0x0000, 0x0000};
  uint16_t  x1[4] = {0x2b7e, 0x1516, 0x28ae, 0xd2a6};
  uint16_t  x2[4] = {0xabf7, 0x1588, 0x09cf, 0x4fcc};
  uint16_t  x3[4] = {0x3243, 0xf6a8, 0x885a, 0x308d};
  uint16_t  x4[4] = {0x3131, 0x98a2, 0xe037, 0x0734};


  while(1) {

    asm("eint");

    WDTCTL = WDTPW | WDTHOLD;
    P1DIR = 0x00;


    P1OUT = 0x80; //Tup
    
    uint8_t j;
    uint16_t q0[4],q1[4],q2[4],q3[4],q4[4],q5[4],q6[4],q7[4],q8[4],q9[4];
    uint16_t t0[4],t1[4],t2[4],t3[4],t4[4];
    uint16_t y0[4],y1[4],y2[4],y3[4],y4[4];

    //---------- Sbox -----------

     for(j = 0; j < 4; ++j)
     { 
             
             q0[j] = !(x3[j] ^ x4[j]);
             q1[j] = !x4[j];
             t0[j] = q0[j] & q1[j];
             q2[j] = x0[j] ^ x2[j] ^ x4[j];
             q3[j] = x1[j];
             t1[j] = q2[j] & q3[j];
             q4[j] = x0[j] ^ x1[j] ^ x4[j];
             q5[j] = x1[j];
             t2[j] = q4[j] & q5[j];
             q6[j] = x3[j] ^ x4[j];
             q7[j] = x0[j];
             t3[j] = q6[j] & q7[j];
             q8[j] = x3[j] ^ t1[j] ^ t2[j];
             q9[j] = x1[j] ^ x2[j];
             t4[j] = q8[j] & q9[j];
             y0[j] = x0[j] ^ x1[j] ^ x2[j] ^ x3[j] ^ t1[j];
             y1[j] = x0[j] ^ x2[j] ^ x3[j] ^ x4[j] ^ t4[j];
             y2[j] = x1[j] ^ x2[j] ^ x3[j] ^ t0[j];
             y3[j] = x0[j] ^ x1[j] ^ x2[j] ^ x3[j] ^ x4[j] ^ t3[j];
             y4[j] = x3[j] ^ x4[j] ^ t2[j];
             P2OUT = y4[j];

     } 

    P1OUT = 0x00;//trigger down
    if (P2IN != P2OUT) {
        P1OUT = 0x05;
    }

  }
}

