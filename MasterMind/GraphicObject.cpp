/* Master Mind game for M5 Paper device.
 *
 * Base class for all the graphic objects, it encapsulates a canvas. 
 */
 
#include "GraphicObject.h"

GraphicObject::GraphicObject()
{   
   mCanvas = NULL;
}

GraphicObject::~GraphicObject()
{   
   if( mCanvas != NULL )
   {
      delete mCanvas;
   }
}

void GraphicObject::init(uint16_t x, uint16_t y, int16_t width, int16_t height)
{
   mCanvas = new M5EPD_Canvas(&M5.EPD);
    
   mCanvas->createCanvas(width, height);
 
   mX = x;
   mY = y;
   mWidth = width;
   mHeight = height;   
}

void GraphicObject::draw(int16_t x, int16_t y, M5EPD_Canvas* canvas)
{
   mCanvas->pushToCanvas(x, y, canvas);
}

bool GraphicObject::isInBox(int16_t x, int16_t y)
{
    if (x == -1 || y == -1)
    {
        return false;
    }

    if ((x > mX) && (x < mX+mWidth) && (y > mY) && (y < mY+mHeight))
    {
        //_issel = true;
        return true;
    }
    //_issel = false;
    return false;
}

