/* Master Mind game for M5 Paper device.
 *
 * This class represents the top area with the command buttons. 
 */

#ifndef _COMMAND_BAR_H_
#define _COMMAND_BAR_H_

#include <M5EPD.h>
#include "GraphicObject.h"
#include "PushButton.h"

class CommandBar: public GraphicObject
{
public:
   typedef void (*Click_callback)(int);

   static const int HEIGHT = 76;//960-StatusBar::HEIGHT-GameArea::NUM_CODES*CodeArea::HEIGH-SelectionArea::HEIGHT;
   
   static const int16_t BTN_NEW = 1;
   static const int16_t BTN_CHECK = 2;
   
   CommandBar();
   
   ~CommandBar();

   void init(Click_callback cb_func);
   
   void update(m5epd_update_mode_t mode);

   void processEvent(int16_t x, int16_t y );
   
private:   
  
  PushButton mBtnNew;
  PushButton mBtnCheck;
  Click_callback mClickCallback;
  
};

#endif
