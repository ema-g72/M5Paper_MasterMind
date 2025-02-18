/* Master Mind game for M5 Paper device.
 *
 * This class implements the result dialog box, shown at the end of the game. 
 */

#ifndef _RESULT_DIALOG_H_
#define _RESULT_DIALOG_H_

#include <M5EPD.h>
#include "PushButton.h"
#include "Peg.h"
#include "GraphicObject.h"

class ResultDialog: public GraphicObject
{
public:
   static const int16_t WIDTH = 360;
   static const int16_t HEIGHT = 280;
   
   typedef void (*Click_callback)(int);
   
   static const int16_t BTN_CLOSE = 1;
   
   ResultDialog();
   
   ~ResultDialog();

   void init(Click_callback cb_func);
   
   void update(m5epd_update_mode_t mode);

   void show(const char *msg, const char *txt, const int8_t *solution, m5epd_update_mode_t mode);

   bool isShow();
   
   void hide();
   
   void processEvent(int16_t x, int16_t y );
   
private:   
  
  void drawDialog(const char *msg, const char *txt, const int8_t *solution);
  
  PushButton mBtnClose;
  bool mShown;
  int16_t mScreenX;   
  int16_t mScreenY;
  Peg mSolution[4];   
  Click_callback mClickCallback; 
};

#endif
