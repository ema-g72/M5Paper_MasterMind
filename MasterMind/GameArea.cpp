/* Master Mind game for M5 Paper device.
 *
 * This class represents main game area as a collection of CodeArea. 
 */

#include "GameArea.h"
#include "SelectionArea.h"
#include "binaryttf.h"

GameArea::GameArea()
{   
}

GameArea::~GameArea()
{   
}

void GameArea::init(Click_callback cb_func)
{
   int16_t height = CodeArea::HEIGHT * NUM_CODES;
   int16_t y = 960 - height - SelectionArea::HEIGHT - 1;
   
   mClickCallback = cb_func;
   mCurrentCodeNumber = 0;
   
   GraphicObject::init(0, y, 540, height); 

   for( int8_t i=0; i<NUM_CODES; ++i)
   {
      mCodes[NUM_CODES-1-i].init( 0, y +  i*CodeArea::HEIGHT);
   }
}

void GameArea::update(m5epd_update_mode_t mode)
{   
   mCanvas->fillCanvas(0);

   for( int8_t i=0; i<NUM_CODES; ++i)
   {
      mCodes[NUM_CODES-1-i].draw(0,  i*CodeArea::HEIGHT, mCanvas);
   }
           
   mCanvas->pushCanvas(mX, mY, mode);  
   mCodes[mCurrentCodeNumber].showMarker();  
}
   
void GameArea::processEvent(int16_t x, int16_t y )
{
   if( GraphicObject::isInBox(x, y) )
   {      
      if( mCodes[mCurrentCodeNumber].isInBox(x, y) )
      {
         int16_t peg = mCodes[mCurrentCodeNumber].getSelectedPeg(x, y);
         
         if( (peg >= 0) && (mClickCallback != NULL) )
         {
            mClickCallback(peg);
         } 
      }
   }
}

void GameArea::setCodePeg(int8_t pos, int8_t color)
{
   mCodes[mCurrentCodeNumber].setPeg(pos, color);
}

void GameArea::setCurrentKey(int8_t blacks, int8_t whites)
{
   if( mCurrentCodeNumber < NUM_CODES )
   {
      mCodes[mCurrentCodeNumber].setKeys( blacks, whites );      
      mCurrentCodeNumber ++;

      if( mCurrentCodeNumber != NUM_CODES )
      {
         mCodes[mCurrentCodeNumber].showMarker();
      }
   }
}

int8_t GameArea::getCurrentCodeNumber()
{
   return mCurrentCodeNumber;
}

void GameArea::resetGame()
{
   mCurrentCodeNumber = 0;
   
   for( int8_t i=0; i<NUM_CODES; ++i)
   {
      mCodes[i].reset();
   }
   
   update(UPDATE_MODE_GL16);
}

   
   
