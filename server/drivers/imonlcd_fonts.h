// -*- coding:utf-8 -*-
/** \file server/drivers/imonlcd_font.h
 * This is a definition of a font for use with the iMON LCD.
 *
 * The iMON LCD doesn't have a "text mode" - everthing is pixel-based.
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


typedef struct _imon_font {
    const unsigned int charWidth;
    const unsigned int charHeight;
    char* (* getCharPixels) (unsigned const char idx);
    short* (* getBigCharPixels) (unsigned const char idx);
} imonlcd_font;

extern imonlcd_font imonlcd_font_8x6;
extern imonlcd_font font_5x4;
extern imonlcd_font font_4x4;

#endif /* IMONLCD_FONTS_H_ */

