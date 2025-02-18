/* Master Mind game for M5 Paper device.
 *
 * This class implements the peg image. 
 */

#ifndef _PEG_H_
#define _PEG_H_

#include <M5EPD.h>
#include "GraphicObject.h"

class Peg: public GraphicObject
{
public:
   static const int WIDTH = 72;
   static const int HEIGHT = 72;
   
   Peg();
   
   ~Peg();
  
   void init(int16_t x, int16_t y, int8_t color);
   
   void update(m5epd_update_mode_t mode);
   
   void setColor(int8_t color);
   
private:   

   static const uint8_t *mImages[];
   
   int8_t mColor;
};

#endif
