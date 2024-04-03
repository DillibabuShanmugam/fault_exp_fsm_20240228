/**************************************************************************/
/*                                                                        */
/*  This file is part of FISSC.                                           */
/*                                                                        */
/*  you can redistribute it and/or modify it under the terms of the GNU   */
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

#include "interface.h"
#include "types.h"
#include "commons.h"

extern SBYTE g_ptc;
extern BOOL g_authenticated;
extern UBYTE g_userPin[PIN_SIZE];
extern UBYTE g_cardPin[PIN_SIZE];

// Hardcoded user PIN
#define USER_PIN_0 0x01
#define USER_PIN_1 0x02
#define USER_PIN_2 0x03
#define USER_PIN_3 0x04

// Hardcoded card PIN
#define CARD_PIN_0 0x01
#define CARD_PIN_1 0x02
#define CARD_PIN_2 0x03
#define CARD_PIN_3 0x04

#ifdef INLINE
__attribute__((always_inline)) inline BOOL byteArrayCompare(UBYTE* a1, UBYTE* a2, UBYTE size)
#else
BOOL byteArrayCompare(UBYTE* a1, UBYTE* a2, UBYTE size)
#endif
{
    int i;
    for(i = 0; i < size; i++) {
        if(a1[i] != a2[i]) {
            return 0;
        }
    }
    return 1;
}

BOOL verifyPIN() {
    g_authenticated = 0;
    // Hardcode the user PIN
    g_userPin[0] = USER_PIN_0;
    g_userPin[1] = USER_PIN_1;
    g_userPin[2] = USER_PIN_2;
    g_userPin[3] = USER_PIN_3;

    // Hardcode the card PIN
    g_cardPin[0] = CARD_PIN_0;
    g_cardPin[1] = CARD_PIN_1;
    g_cardPin[2] = CARD_PIN_2;
    g_cardPin[3] = CARD_PIN_3;
    if(g_ptc > 0) {
        if(byteArrayCompare(g_userPin, g_cardPin, PIN_SIZE) == 1) {
            g_ptc = 3;
            g_authenticated = 1; // Authentication();
            return 1;
        } else {
            g_ptc--;
            return 0;
        }
    }

    return 0;
}
