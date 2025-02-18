/* Master Mind game for M5 Paper device.
 *
 * This class represents the top area with the command buttons. 
 */

#include "CommandBar.h"
#include "StatusBar.h"
#include "ImageResource.h"

const int16_t BTN_NEW_WIDTH = 120;
const int16_t BTN_CHECK_WIDTH = 120;
const int16_t BTN_HEIGHT = 48;
const int16_t BTN_X_SPACE = 12;

CommandBar::CommandBar()
{ 
}

CommandBar::~CommandBar()
{   
}

void CommandBar::init(Click_callback cb_func)
{
   mClickCallback = cb_func;
   
   int16_t y = StatusBar::HEIGHT;
   int16_t dy = 16; // (HEIGHT-BTN_HEIGHT)/2 = 14;
   
   GraphicObject::init(0, y, 540, HEIGHT);
   
   mBtnNew.init(BTN_NEW, "New Game", BTN_X_SPACE, y+dy, BTN_NEW_WIDTH, BTN_HEIGHT);
   mBtnCheck.init(BTN_CHECK, "Check", 540-BTN_CHECK_WIDTH-BTN_X_SPACE, y+dy, BTN_CHECK_WIDTH, BTN_HEIGHT);
   
   mBtnNew.setClickCallback(cb_func);
   mBtnCheck.setClickCallback(cb_func);

   mCanvas->fillCanvas(0);

   mBtnNew.draw(BTN_X_SPACE, dy, mCanvas);
   mBtnCheck.draw(540-BTN_CHECK_WIDTH-BTN_X_SPACE, dy, mCanvas);
}
 
void CommandBar::update(m5epd_update_mode_t mode)
{   
   mCanvas->pushCanvas(mX, mY, mode);
}

void CommandBar::processEvent(int16_t x, int16_t y )
{  
   mBtnNew.processEvent(x, y);
   mBtnCheck.processEvent(x, y);
}
   
