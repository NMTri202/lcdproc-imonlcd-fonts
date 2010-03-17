// -*- coding:utf-8 -*-
/** \file server/drivers/imonlcd_font.h
 * This is a definition of a font for use with the iMON LCD.
 *
 * The iMON LCD doesn't have a "text mode" - everything is pixel-based.
 * So we need to define our own font, basically.
 */

/*-
 * Created March 2009 by Jonathan Kyler for inclusion in lcdproc
 * Structure based on codeka's imonlcd patch by Dean Harding
 * Font based on Toshiba T6963 based LCD display driver font by Manuel Stahl
 *
 * Copyright (c) 2009, Jonathan Kyler <jkyler (at) users (dot) sourceforge (dot) net>
 *
 * This file is released under the GNU General Public License. Refer to the
 * COPYING file distributed with this package.
 */

#ifndef IMONLCD_FONTS_H_
#define IMONLCD_FONTS_H_

#define IMONLCD_FONT_FULL_HEART		3
#define IMONLCD_FONT_SMALL_HEART	4
#define IMONLCD_FONT_FULL_BLOCK		141
#define IMONLCD_FONT_LEFT_ARROW		155
#define IMONLCD_FONT_UP_ARROW		156
#define IMONLCD_FONT_RIGHT_ARROW	157
#define IMONLCD_FONT_DOWN_ARROW		158

#define IMONLCD_FONT_STOP		19
#define IMONLCD_FONT_PLAY		16
#define IMONLCD_FONT_PAUSE		18
#define IMONLCD_FONT_REVERSE	17
#define IMONLCD_FONT_FWD		21
#define IMONLCD_FONT_RWD		22
#define IMONLCD_FONT_RECORD		15

#define IMONLCD_FONT_START_VBAR_FULL	23
#define IMONLCD_FONT_START_VBAR_NARROW	127
#define IMONLCD_FONT_START_HBAR_NARROW	135

typedef struct _imonlcd_font {
    const unsigned int charWidth;
    const unsigned int charHeight;
    char* (* getCharPixels) (unsigned const char idx);
    short* (* getBigCharPixels) (unsigned const char idx);
} imonlcd_font;

#define IMONLCD_FONT_NUM_WIDTH 12
#define IMONLCD_FONT_NUM_HEIGHT 16

const short big_numbers[12][IMONLCD_FONT_NUM_WIDTH]= {
   /*0*/{0x0000, 0x07E0, 0x1FF8, 0x3FFC, 0x7FFE, 0x4002, 0x4002, 0x4002, 0x3FFC, 0x3FFC, 0x1FF8, 0x07E0},
   /*1*/{0x0000, 0x0000, 0x0000, 0x4002, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x0002, 0x0000, 0x0000, 0x0000},
   /*2*/{0x0000, 0x1806, 0x3C2C, 0x7C7C, 0x5C5C, 0x40DE, 0x7F9E, 0x7F8E, 0x3F0E, 0x1E0C, 0x0018, 0x0000},
   /*3*/{0x0000, 0x001C, 0x3C3C, 0x7C3E, 0x7C1A, 0x0080, 0x4182, 0x7FFE, 0x7FFE, 0x3E7C, 0x1C38, 0x0000},
   /*4*/{0x0000, 0x0030, 0x0050, 0x0190, 0x0610, 0x0002, 0x1FFE, 0x3FFE, 0x7FFE, 0x7FFE, 0x0012, 0x0002},
   /*5*/{0x0000, 0x0018, 0x7FBC, 0x793E, 0x3B1A, 0x3800, 0x3B02, 0x3BFE, 0x31FE, 0x61FC, 0x00F8, 0x0000},
   /*6*/{0x0000, 0x07E0, 0x1FF8, 0x3FFC, 0x7FFE, 0x4002, 0x0180, 0x5982, 0x7DFE, 0x3DFC, 0x18FC, 0x0078},
   /*7*/{0x0000, 0x0800, 0x7000, 0x3000, 0x703C, 0x787E, 0x79FE, 0x7BFC, 0x3E00, 0x3000, 0x6000, 0x0000},
   /*8*/{0x0000, 0x1C3C, 0x3E7E, 0x7FFE, 0x7FFE, 0x4182, 0x4182, 0x7FFE, 0x7FFE, 0x3E7E, 0x1C3C, 0x0000},
   /*9*/{0x0000, 0x1E18, 0x3F3C, 0x7FBE, 0x7F9A, 0x0180, 0x4002, 0x7FFE, 0x3FFC, 0x1FF8, 0x07E0, 0x0000},
   /*:*/{0x0000, 0x030C, 0x079E, 0x079E, 0x030C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},

        /*
         * Marks the end of the array, but also serves as the character that
         * unknown inputs are mapped to (essentially, a "space")
         */
  /*\0*/{0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
};

#include "imonlcd_font_4x4.h"
#include "imonlcd_font_5x4.h"
#include "imonlcd_font_8x6.h"


#endif /* IMONLCD_FONTS_H_ */

