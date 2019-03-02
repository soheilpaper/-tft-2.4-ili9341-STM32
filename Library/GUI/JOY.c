/*-----------------------------------------------------------------------------
 * Name:    JOY.c
 * Purpose: Low level joystick functions
 * Note(s):
 *-----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2004-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "JOY.h"
#include <stdint.h>


/*-----------------------------------------------------------------------------
 *  JOY_Init:  Initialize joystick
 *----------------------------------------------------------------------------*/
void JOY_Init (void) {
  // Configure P1.20,23..26 as inputs
//  LPC_GPIO1->FIODIR &= ~((1<<20) | (1<<23) | (1<<24) | (1<<25) | (1<<26)); 
}


/*-----------------------------------------------------------------------------
 *  JOY_GetKeys:  Get joystick direction keys state
 *
 * Parameters: (none)
 * Return:     joystick directions bitmask
 *----------------------------------------------------------------------------*/
unsigned int JOY_GetKeys (void) {
  unsigned int p, val = 0;

  //p = LPC_GPIO1->FIOPIN;
  if ((p & (1 << 26)) == 0) {
    val |= JOY_LEFT;
  }
  if ((p & (1 << 24)) == 0) {
    val |= JOY_RIGHT;
  }
  if ((p & (1 << 23)) == 0) {
    val |= JOY_UP;
  }
  if ((p & (1 << 25)) == 0) {
    val |= JOY_DOWN;
  }
  if ((p & (1 << 20)) == 0) {
    val |= JOY_CENTER;
  }
  return (val);
}
