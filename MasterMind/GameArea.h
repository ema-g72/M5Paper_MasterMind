/* Master Mind game for M5 Paper device.
 *
 * This class represents main game area as a collection of CodeArea. 
 */

#ifndef _GAME_AREA_H_
#define _GAME_AREA_H_

#include <M5EPD.h>
#include "GraphicObject.h"
#include "CodeArea.h"

class GameArea: public GraphicObject
{
public:
   typedef void (*Click_callback)(int);
   
   static const int NUM_CODES = 9;
 
   GameArea();
   
   ~GameArea();

   void init(Click_callback cb_func);
   
   void update(m5epd_update_mode_t mode);

   void processEvent(int16_t x, int16_t y );

   void setCurrentKey(int8_t blacks, int8_t whites);

   void setCodePeg(int8_t pos, int8_t color);
   
   int8_t getCurrentCodeNumber();

   void resetGame();

private:   
  
   int8_t mCurrentCodeNumber;
   CodeArea mCodes[NUM_CODES];
   Click_callback mClickCallback;
};

#endif
