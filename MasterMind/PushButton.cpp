/* Master Mind game for M5 Paper device.
 *
 * This class implements a push button. 
 */

#include "PushButton.h"
   
PushButton::PushButton()
{
}

PushButton::~PushButton()
{
}

void PushButton::init(int16_t id, const char *label, int16_t x, int16_t y, int16_t w, int16_t h)
{
   int i;
   for(i=0; i<MAX_LBL_LEN-1; ++i)
   {
      if( label[i] == '\0' )
      {
         break;
      }

      mLabel[i] = label[i];
   }
   mLabel[i] = '\0';
         
   mId = id;
   mClickCallback = NULL;
   mPressed = false;

   GraphicObject::init(x, y, w, h);
   
   if( !mCanvas->isRenderExist(22) )
   {
      mCanvas->createRender(22, 128);
   }

   mCanvas->fillCanvas(0);   
   mCanvas->setTextSize(22); 
   mCanvas->setTextColor(15);
   mCanvas->drawRect(0, 0, w, h, 15);
   mCanvas->setTextDatum(CC_DATUM);
   mCanvas->drawString(mLabel,  w/2, h/2);
    
   mCanvasPressed = new M5EPD_Canvas(&M5.EPD);    
   mCanvasPressed->createCanvas(w, h);
 
   mCanvasPressed->fillCanvas(15);   
   mCanvasPressed->setTextSize(22); 
   mCanvasPressed->setTextColor(0);
   mCanvasPressed->setTextDatum(CC_DATUM);
   mCanvasPressed->drawString(mLabel, w/2, h/2);
}

void PushButton::setClickCallback(Click_callback cb_func)
{
   mClickCallback = cb_func;
}

void PushButton::update(m5epd_update_mode_t mode)
{
   if( mPressed )
   {
      mCanvasPressed->pushCanvas(mX, mY, mode);
   }
   else
   {
      mCanvas->pushCanvas(mX, mY, mode);      
   }
}

void PushButton::processEvent(int16_t x, int16_t y )
{
   if( GraphicObject::isInBox(x, y) )
   {
      if( !mPressed )
      {
         mPressed = true;
         update(UPDATE_MODE_GL16);
         
         if( mClickCallback != NULL )
         {
            mClickCallback(mId);
         }
      }
   }
   else
   {
      if( mPressed )
      {
         mPressed = false;
         update(UPDATE_MODE_GL16);
      }
   }
}
   
