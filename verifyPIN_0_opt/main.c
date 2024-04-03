/**************************************************************************/
/*                                                                        */
/*  This file is part of FISSC.                                           */
/*                                                                        */
/*  You can redistribute it and/or modify it under the terms of the GNU   */
/*  Lesser General Public License as published by the Free Software       */
/*  Foundation, version 3.0.                                              */
/*                                                                        */
/*  It is distributed in the hope that it will be useful,                 */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*  GNU Lesser General Public License for more details.                   */
/*                                                                        */
/*  See the GNU Lesser General Public License version 3.0                 */
/*  for more details (enclosed in the file LICENSE).                      */
/*                                                                        */
/**************************************************************************/

/*$
  @name = VerifyPIN_0
  @feature = verifyPIN
  @fault-model = test-inversion
  @attack-scenario = oracle
  @countermeasure = none
  @maintainers = Etienne Boespflug, VERIMAG
  @authors = Lionel Rivière, SERTIF Consortium
  @version 2.2
*/
#include "../shared/omsp_system.h"

#include <stdio.h>

#include "interface.h"
#include "types.h"
#include "lazart.h"

//-----------------------NMI --------------
// #define NMI_VECTOR          (0x0018)   // Vector 12  (0xFFF8) - Non-maskable
interrupt(13) NMI_ISR(void)  // !!! interrupt(x) = interrupt(vector + 1)
{
//  P1OUT = 0x00; // clear nmi here
  while(1);
}
//-----------------------------------------

extern UBYTE g_countermeasure;
extern BOOL g_authenticated;
extern SBYTE g_ptc;

BOOL verifyPIN(void);

int main()
{
  asm("eint");

  WDTCTL = WDTPW | WDTHOLD;
  P1DIR = 0x00;

  initialize();
  P1OUT = 0x80;//trigger up
  BOOL pin_verified = verifyPIN();
  if(pin_verified)
	  P2OUT = 0xFF;
  else
	  P2OUT = 0x00;

  P1OUT = 0x00;//trigger down
  if (P2IN != P2OUT) {
        P1OUT = 0x05;
  }

  LAZART_ORACLE(oracle());


   // printf("[@] g_countermeasure = %i, g_authenticated = %x, g_ptc = %i\n", g_countermeasure, g_authenticated, g_ptc);
    return 0;
}
