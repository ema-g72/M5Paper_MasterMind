/* Master Mind game for M5 Paper device.
 *
 * This class implements a row in the game area. It shows the guess code and the corresponding keys (blacks/whites). 
 */
 
#include "CodeArea.h"
#include "ImageResource.h"
#include "binaryttf.h"

const int16_t PEG_SEPARATION = 12;
const int16_t KEY_RADIUS = 14;
const int16_t KEY_SEPARATION = 12;
const int16_t MARKER_X_POS = 524;
const int16_t MARKER_WIDTH = 8;

CodeArea::CodeArea()
{   
}

CodeArea::~CodeArea()
{   
}

void CodeArea::init(int16_t x, int16_t y)
{   
   GraphicObject::init(x, y, 540, HEIGHT); 

   mCanvas->fillCanvas(0);
   mCanvas->drawFastHLine(0, 0, 540, 15);     

   int16_t xrel = PEG_SEPARATION;

   for( int8_t i=0; i<4; ++i)
   {
      mPegs[i].init( x + xrel, y+4, -1);
      mPegs[i].draw(xrel, 4, mCanvas);
      xrel = PEG_SEPARATION + (i+1)*(PEG_SEPARATION + Peg::WIDTH);
   }
      
   mCanvas->drawFastVLine(xrel, 0, HEIGHT, 15);     

   mKeyXPos = xrel + 1;

   mKeyCanvas = new M5EPD_Canvas(&M5.EPD); 
   mKeyCanvas->createCanvas(4*(2*KEY_RADIUS+KEY_SEPARATION), KEY_RADIUS*2+4);
   mKeyCanvas->fillCanvas(0);

   mMarkerCanvas = new M5EPD_Canvas(&M5.EPD); 
   mMarkerCanvas->createCanvas(MARKER_WIDTH, Peg::HEIGHT);
   mMarkerCanvas->fillCanvas(15);   
}

void CodeArea::showMarker()
{
   mMarkerCanvas->fillCanvas(15); 
   mMarkerCanvas->pushCanvas(MARKER_X_POS, mY + (HEIGHT-Peg::HEIGHT)/2, UPDATE_MODE_GL16);
}

int16_t CodeArea::getSelectedPeg(int16_t x, int16_t y)
{
   for( int i=0; i<4; ++i)
   {
      if( mPegs[i].isInBox(x, y) )
      {
         return i;
      }
   }
   return -1;
}
   
void CodeArea::setPeg(int8_t position, int8_t peg)
{
   if(position >= 0 && position <4)
   {
      mPegs[position].setColor(peg);
      mPegs[position].update(UPDATE_MODE_GL16);
   }
}

void CodeArea::setKeys( int8_t blacks, int8_t whites)
{
   int16_t ycenter = KEY_RADIUS;
   int16_t xrel = KEY_RADIUS + KEY_SEPARATION;
   
   mKeyCanvas->fillCanvas(0);
   
   for( int i=0; i<blacks; ++i)
   {
      mKeyCanvas->fillCircle(xrel, ycenter, KEY_RADIUS, 15);
      xrel += 2*KEY_RADIUS + KEY_SEPARATION;
   }
   for( int i=0; i<whites; ++i)
   {
      mKeyCanvas->fillCircle(xrel, ycenter, KEY_RADIUS, 2);
      xrel += 2*KEY_RADIUS + KEY_SEPARATION;
   }

   mKeyCanvas->pushCanvas(mKeyXPos, mY+(HEIGHT-2*KEY_RADIUS)/2, UPDATE_MODE_GL16);
   
   mMarkerCanvas->fillCanvas(0); 
   mMarkerCanvas->pushCanvas(MARKER_X_POS, mY + (HEIGHT-Peg::HEIGHT)/2, UPDATE_MODE_GL16);
}

void CodeArea::reset()
{
   int16_t xrel = PEG_SEPARATION;

   for( int8_t i=0; i<4; ++i)
   {
      mPegs[i].setColor(-1);
      mPegs[i].draw(xrel, 4, mCanvas);
      xrel = PEG_SEPARATION + (i+1)*(PEG_SEPARATION + Peg::WIDTH);
   }
      
   mCanvas->drawFastVLine(xrel, 0, HEIGHT, 15);     
}

void CodeArea::update(m5epd_update_mode_t mode)
{   
  
}
