/* Master Mind game for M5 Paper device.
 *
 * This class implements the peg selection area. 
 */

#include "SelectionArea.h"
#include "ImageResource.h"
#include "binaryttf.h"

const int16_t PEG_Y_POS = 20;
const int16_t SELECTION_Y_POS = PEG_Y_POS + Peg::HEIGHT + 4;
const int16_t SELECTION_HEIGHT = 8;

SelectionArea::SelectionArea()
{   
}

SelectionArea::~SelectionArea()
{   
}

void SelectionArea::setSelected(int16_t peg)
{
   mSelectCanvas->fillCanvas(0);

   if( peg >= 0 )
   {
      mSelectCanvas->fillRect(mXDelta + peg*(Peg::WIDTH+mXDelta), 0, Peg::WIDTH, SELECTION_HEIGHT, 15);
   }
   
   mSelected = peg;

   mSelectCanvas->pushCanvas(0, mY + SELECTION_Y_POS, UPDATE_MODE_GL16);
}

int16_t SelectionArea::getSelected()
{
   return mSelected;
}

void SelectionArea::init(Click_callback cb_func)
{
   int16_t y = 960-HEIGHT;

   mClickCallback = cb_func;
   mSelected = -1;
   
   mXDelta = 16;//(540 - Peg::WIDTH*6)/7;
   
   GraphicObject::init(0, y, 540, HEIGHT); 

   for( int8_t i=0; i<6; ++i)
   {
      mPegs[i].init( mXDelta + i*(Peg::WIDTH+mXDelta), y + PEG_Y_POS, i);
   }

   mSelectCanvas = new  M5EPD_Canvas(&M5.EPD);
   mSelectCanvas->createCanvas(540, SELECTION_HEIGHT);
   
   setSelected(-1);
}

void SelectionArea::update(m5epd_update_mode_t mode)
{   
   mCanvas->fillCanvas(0);
   mCanvas->drawFastHLine(0, 0, 540, 15);    
   mCanvas->drawFastHLine(0, 3, 540, 15);    

   for( int8_t i=0; i<6; ++i)
   {
      mPegs[i].draw( mXDelta + i*(Peg::WIDTH+mXDelta), PEG_Y_POS, mCanvas);
   }
        
   mCanvas->pushCanvas(mX, mY, mode);
}

void SelectionArea::processEvent(int16_t x, int16_t y )
{
   if( GraphicObject::isInBox(x, y) )
   {
      for( int8_t i=0; i<6; ++i)
      {
         if( mPegs[i].isInBox(x, y) )
         {
            if( mClickCallback != NULL )
            {
               mClickCallback(i);
            }
            break;
         }
      }
   }
}
   
