/* Master Mind game for M5 Paper device.
 *
 * This class implements the top status bar (battery charge indicator). 
 */

#include "StatusBar.h"
#include "ImageResource.h"

static const int16_t UPDATE_PERIOD_MS = 5000;
   
StatusBar::StatusBar()
{ 
   mPrevMillis = 0;
}

StatusBar::~StatusBar()
{   
}

void StatusBar::init()
{
   GraphicObject::init(0, 0, 540, HEIGHT);
 
   if( !mCanvas->isRenderExist(26) )
   {
      mCanvas->createRender(26, 128);
   }

   mCanvas->setTextSize(26);   
}

void StatusBar::update(m5epd_update_mode_t mode)
{   
   uint32_t now = millis();

   boolean ret = ((now - mPrevMillis) >= UPDATE_PERIOD_MS);
      
   if( !ret )
   {
      return;
   }
   
   mPrevMillis = now;
   
   mCanvas->fillCanvas(0);
   mCanvas->drawFastHLine(0, HEIGHT-1, 540, 15);
   mCanvas->setTextDatum(CL_DATUM);
   mCanvas->drawString("Master Mind", 10, 27);

   // Battery
   mCanvas->setTextDatum(CR_DATUM);
   mCanvas->pushImage(498, 8, 32, 32, ImageResource_status_bar_battery_32x32);
   uint32_t vol = M5.getBatteryVoltage();

   if(vol < 3300)
   {
       vol = 3300;
   }
   else if(vol > 4350)
   {
       vol = 4350;
   }
   float battery = (float)(vol - 3300) / (float)(4350 - 3300);
   if(battery <= 0.01)
   {
       battery = 0.01;
   }
   if(battery > 1)
   {
       battery = 1;
   }
   uint8_t px = battery * 25;
   
   char buf[20];
   sprintf(buf, "%d%%", (int)(battery * 100));
   mCanvas->drawString(buf, 498 - 10, 27);
   mCanvas->fillRect(498 + 3, 8 + 10, px, 13, 15);
   // _bar->pushImage(498, 8, 32, 32, 2, ImageResource_status_bar_battery_charging_32x32);
   
   mCanvas->pushCanvas(mX, mY, mode);
}

void StatusBar::processEvent(int16_t x, int16_t y )
{  
}
   
