/* Master Mind game for M5 Paper device.
 *
 * This class implements a push button. 
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <M5EPD.h>
#include "GraphicObject.h"

class PushButton: public GraphicObject
{
public:
   typedef void (*Click_callback)(int);
   
   PushButton();
   
   ~PushButton();
  
   void init(int16_t id, const char *label, int16_t x, int16_t y, int16_t w, int16_t h);

   void setClickCallback(Click_callback cb_func);
  
   void update(m5epd_update_mode_t mode);

   void processEvent(int16_t x, int16_t y );
   
private:   
   
   static const uint8_t MAX_LBL_LEN = 16;
   
   int16_t mId;
   char mLabel[MAX_LBL_LEN];
   bool mPressed;
   Click_callback mClickCallback;
   M5EPD_Canvas *mCanvasPressed;
};

#endif
