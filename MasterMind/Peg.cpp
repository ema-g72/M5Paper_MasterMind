/* Master Mind game for M5 Paper device.
 *
 * This class implements the peg image. 
 */

#include "Peg.h"
#include "ImageResource.h"

const int16_t RECT_RADIUS = 8;

const uint8_t *Peg::mImages[] = { ImageResource_cane_64_64x64, 
                              ImageResource_elefante_64_64x64,
                              ImageResource_papera_64_64x64,
                              ImageResource_scimmia_64_64x64,
                              ImageResource_tigre_64_64x64,
                              ImageResource_topo_64_64x64 };
   
Peg::Peg()
{
}

Peg::~Peg()
{
}

void Peg::init(int16_t x, int16_t y, int8_t color)
{
   GraphicObject::init(x, y, WIDTH, HEIGHT);

   setColor(color);
}

void Peg::setColor(int8_t color)
{
   mColor = color;

   mCanvas->fillCanvas(0);   
   
   if( color < 0 )
   {
      mCanvas->drawRoundRect(0, 0, WIDTH, HEIGHT, RECT_RADIUS, 15);
   }
   else
   {
      mCanvas->pushImage(3, 3, 64, 64, mImages[color]);
      mCanvas->drawRoundRect(0, 0, WIDTH, HEIGHT, RECT_RADIUS, 15);
   }
}

void Peg::update(m5epd_update_mode_t mode)
{
   mCanvas->pushCanvas(mX, mY, mode);
}
