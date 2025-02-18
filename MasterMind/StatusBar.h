/* Master Mind game for M5 Paper device.
 *
 * This class implements the top status bar (battery charge indicator). 
 */

#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_

#include <M5EPD.h>
#include "GraphicObject.h"

class StatusBar: public GraphicObject
{
public:
   static const int HEIGHT = 44;
   
   StatusBar();
   
   ~StatusBar();

   void init();
   
   void update(m5epd_update_mode_t mode);

   void processEvent(int16_t x, int16_t y );
   
private:   
   
   uint32_t mPrevMillis;   
};

#endif
