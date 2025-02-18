/* Master Mind game for M5 Paper device.
 *
 * This class implements the peg selection area. 
 */

#ifndef _COMMAND_AREA_H_
#define _COMMAND_AREA_H_

#include <M5EPD.h>
#include "GraphicObject.h"
#include "Peg.h"

class SelectionArea: public GraphicObject
{
public:
   typedef void (*Click_callback)(int);

   static const int16_t HEIGHT = 120;
   
   SelectionArea();
   
   ~SelectionArea();

   void init(Click_callback cb_func);
   
   void update(m5epd_update_mode_t mode);

   void processEvent(int16_t x, int16_t y );

   void setSelected(int16_t peg);

   int16_t getSelected();

private:   

   Peg mPegs[6];
   int16_t mXDelta;
   int16_t mSelected;
   M5EPD_Canvas *mSelectCanvas;
   Click_callback mClickCallback;
};

#endif
