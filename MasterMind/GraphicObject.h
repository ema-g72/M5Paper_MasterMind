/* Master Mind game for M5 Paper device.
 *
 * Base class for all the graphic objects, it encapsulates a canvas. 
 */
 
#ifndef _GRAPHIC_OBJECT_H_
#define _GRAPHIC_OBJECT_H_

#include <M5EPD.h>

class GraphicObject
{
public:
   GraphicObject();
   
   virtual ~GraphicObject();

   void init(uint16_t x, uint16_t y, int16_t width, int16_t height);
   
   virtual void update(m5epd_update_mode_t mode) = 0;

   void draw(int16_t x, int16_t y, M5EPD_Canvas* canvas);

   bool isInBox(int16_t x, int16_t y);
   
protected:   

   uint16_t mX;
   uint16_t mY;
   uint16_t mWidth;
   uint16_t mHeight;
   
   M5EPD_Canvas *mCanvas;
};

#endif
