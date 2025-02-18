/*
MIT License

Copyright (c) 2025 ema-g72

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* Master Mind game for M5 Paper device.
 *
 * Main module. 
 */

#include <M5EPD.h>
#include "StatusBar.h"
#include "CommandBar.h"
#include "GameArea.h"
#include "SelectionArea.h"
#include "ResultDialog.h"
#include "ImageResource.h"
#include "MasterMind.h"
#include "binaryttf.h"

// Global variables.
StatusBar gStatusBar;
CommandBar gCommandBar;
GameArea gGameArea;
SelectionArea gSelectionArea;
ResultDialog gResultDialog;
MasterMind gMasterMind;

int8_t gSelectedPeg;
int8_t gPlayCode[MasterMind::NUM_PEGS];
int8_t gPlayPegNumber;
uint32_t gStartTimeMs;
uint16_t gLastPosX = 0xFFFF;
uint16_t gLastPosY = 0xFFFF;

void ManageTouchHandler(int16_t x, int16_t y)
{
   if( gResultDialog.isShow() )
   {
      gResultDialog.processEvent(x, y);
   }
   else
   {
      gStatusBar.processEvent(x, y);
      gSelectionArea.processEvent(x, y);
      gGameArea.processEvent(x, y);
      gCommandBar.processEvent(x, y);
   }
}

void selectionAreaCallback(int peg)
{
   gSelectedPeg = peg;
   gSelectionArea.setSelected(peg);   
}

void gameAreaCallback(int peg)
{
   gGameArea.setCodePeg(peg, gSelectedPeg);
   gPlayCode[peg] = gSelectedPeg;
   gPlayPegNumber ++;
   if( gPlayPegNumber > MasterMind::NUM_PEGS )
   {
      gPlayPegNumber = MasterMind::NUM_PEGS;
   }
}

void dialogResultCallback(int id)
{
   gResultDialog.hide();
   startNewGame(true);
}

void checkMove()
{
   if( gPlayPegNumber != MasterMind::NUM_PEGS)
   {
      return;
   }
   
   Serial.print("Move: ");
   printCode(gPlayCode);
   Serial.println("");
   
   int8_t whites;
   int8_t blacks;

   if( gGameArea.getCurrentCodeNumber() == 0)
   {
      gStartTimeMs = millis();
      Serial.println("start time");
   }
   
   bool win = gMasterMind.play( gPlayCode, &whites, &blacks);
   
   gGameArea.setCurrentKey( blacks, whites );
   
   if( win )
   {
      char str[64];
      uint32_t secs = (millis() - gStartTimeMs)/1000;
      sprintf(str, "moves: %d, time: %d min, %02d sec", gGameArea.getCurrentCodeNumber(), secs/60, secs%60);
      
      gResultDialog.show("You Win!", str, gPlayCode, UPDATE_MODE_GC16);
   } 
   else if( gGameArea.getCurrentCodeNumber() == GameArea::NUM_CODES )
   {
      gMasterMind.getHiddenCode(gPlayCode);
      gResultDialog.show("You Lose.", "the solution is:", gPlayCode, UPDATE_MODE_GC16);
   }   
   gPlayPegNumber = 0;
}

void commandBarCallback(int id)
{
   switch(id)
   {
   case CommandBar::BTN_NEW:
      startNewGame(true);
      break;
      
   case CommandBar::BTN_CHECK:    
      checkMove(); 
      break;
      
   default:
      break;
   }
}

void initRandomSeed()
{
   rtc_time_t tm;

   M5.RTC.getTime(&tm);
   uint32_t seed = (M5.getBatteryVoltage() % 100)*1000000 + (tm.sec*10000 + tm.min*100 + tm.hour);
   
   randomSeed(seed);
   
   Serial.print("rnd seed: ");
   Serial.println(seed);
}

void printCode(int8_t *code)
{
   for(int i=0; i<MasterMind::NUM_PEGS; ++i)
   {
      Serial.print(code[i]);
      Serial.print(" ");
   }
   Serial.println("");   
}

void startNewGame(bool reset)
{   
   if( reset )
   {
      gGameArea.resetGame();   
   }
   gMasterMind.init(); 
   gPlayPegNumber = 0;

   int8_t code[MasterMind::NUM_PEGS];
   gMasterMind.getHiddenCode(code);
   Serial.print("Code: ");
   printCode(code);
   Serial.println("");
}

void powerOffDevice()
{
   Serial.println("shutdown");

   M5EPD_Canvas offScreen(&M5.EPD); 
   
   offScreen.createCanvas(540, 960);
   offScreen.fillCanvas(0);
   offScreen.setTextSize(22); 
   offScreen.setTextColor(15);
   offScreen.setTextDatum(CC_DATUM);
   offScreen.drawString("Power off", 540/2, 900);
   
   offScreen.pushCanvas(0,0,UPDATE_MODE_GL16);
   
   delay(500);
   // Does not work if connected with USB.
   M5.disableMainPower();
}

void setup() 
{
   M5.begin();
   M5.TP.SetRotation(90);
   M5.EPD.SetRotation(90);
   M5.EPD.Clear(true);
   M5.BatteryADCBegin();  

   initRandomSeed();
   
   M5EPD_Canvas initcanvas(&M5.EPD);
   initcanvas.loadFont(binaryttf, sizeof(binaryttf));

   gStatusBar.init();
   gCommandBar.init(commandBarCallback);
   gGameArea.init(gameAreaCallback);
   gSelectionArea.init(selectionAreaCallback);
   gResultDialog.init(dialogResultCallback);
   startNewGame(false);
   
   gSelectedPeg = -1;   

   gStatusBar.update(UPDATE_MODE_NONE);
   gCommandBar.update(UPDATE_MODE_NONE);
   gSelectionArea.update(UPDATE_MODE_NONE);
   gGameArea.update(UPDATE_MODE_NONE);

   M5.EPD.UpdateFull(UPDATE_MODE_GC16);

   Serial.println("run app");
}

void loop() 
{
   if (M5.TP.available())
   {
      M5.TP.update();
      bool is_finger_up = M5.TP.isFingerUp();
      if(is_finger_up || (gLastPosX != M5.TP.readFingerX(0)) || (gLastPosY != M5.TP.readFingerY(0)))
      {
          gLastPosX = M5.TP.readFingerX(0);
          gLastPosY = M5.TP.readFingerY(0);
          if(is_finger_up)
          {
              ManageTouchHandler(-1, -1);
          }
          else
          {
              ManageTouchHandler(M5.TP.readFingerX(0), M5.TP.readFingerY(0));
          }
      }      
      
      M5.TP.flush();
   }
   
   M5.update();
   if(M5.BtnP.wasPressed())
   {
      powerOffDevice();
   }
    
   gStatusBar.update(UPDATE_MODE_A2);
}
