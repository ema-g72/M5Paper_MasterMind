/* Master Mind game for M5 Paper device.
 *
 * This class implements a row in the game area. It shows the guess code and the corresponding keys (blacks/whites). 
 */
 
#ifndef _CODE_AREA_H_
#define _CODE_AREA_H_

#include <M5EPD.h>
#include "GraphicObject.h"
#include "Peg.h"

class CodeArea: public GraphicObject
{
public:
   static const int HEIGHT = 80;
   
   CodeArea();
   
   ~CodeArea();

   void init(int16_t x, int16_t y);
   
   void update(m5epd_update_mode_t mode);
   
   int16_t getSelectedPeg(int16_t x, int16_t y);

   void setPeg(int8_t position, int8_t peg);
   
   void setKeys( int8_t blacks, int8_t whites);

   void showMarker();
   
   void reset();
   
private:   

   Peg mPegs[4];
   int16_t mKeyXPos;
   int16_t mMarkerYPos;
   M5EPD_Canvas *mKeyCanvas;
   M5EPD_Canvas *mMarkerCanvas;
};

#endif
