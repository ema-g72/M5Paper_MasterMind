/* Master Mind game for M5 Paper device.
 *
 * This class implements the result dialog box, shown at the end of the game. 
 */
 
 #include "ResultDialog.h"

const int16_t BTN_CLOSE_WIDTH = 120;
const int16_t BTN_CLOSE_HEIGHT = 48;
const int16_t PEG_SEPARATION = 8;

ResultDialog::ResultDialog()
{ 
}

ResultDialog::~ResultDialog()
{   
}

void ResultDialog::init(Click_callback cb_func)
{
   mClickCallback = cb_func;
   mShown = false;      
   mScreenX = (540-WIDTH)/2;   
   mScreenY = (960-HEIGHT)/2;   

   GraphicObject::init( mScreenX, mScreenY, WIDTH, HEIGHT);
   
   mBtnClose.init(BTN_CLOSE, "Close", mScreenX+(WIDTH-BTN_CLOSE_WIDTH)/2, mScreenY+HEIGHT-BTN_CLOSE_HEIGHT-12, BTN_CLOSE_WIDTH, BTN_CLOSE_HEIGHT);

   for( int8_t i=0; i<4; ++i)
   {
      mSolution[i].init(mScreenX + (WIDTH+4*Peg::WIDTH+3*PEG_SEPARATION)/2+i*(Peg::WIDTH+PEG_SEPARATION), mScreenY + HEIGHT/2, -1);
   }
   
   mBtnClose.setClickCallback(cb_func);

   drawDialog(NULL, NULL, NULL);
}

void ResultDialog::drawDialog(const char *msg, const char *txt, const int8_t *solution)
{
   mCanvas->fillCanvas(1);
   mCanvas->drawRect(0, 0, WIDTH, HEIGHT, 15);

   int16_t btnY = HEIGHT-BTN_CLOSE_HEIGHT-12;
   
   mBtnClose.draw((WIDTH-BTN_CLOSE_WIDTH)/2, btnY, mCanvas);

   if( !mCanvas->isRenderExist(32) )
   {
      mCanvas->createRender(32, 128);
   }

   if( !mCanvas->isRenderExist(22) )
   {
      mCanvas->createRender(22, 128);
   }

   mCanvas->setTextSize(32); 
   mCanvas->setTextColor(15);

   if( msg != NULL )
   {
      mCanvas->setTextDatum(CC_DATUM);
      mCanvas->drawString(msg,  WIDTH/2, 60);
   }

   mCanvas->setTextSize(22); 

   if( txt != NULL )
   {
      mCanvas->setTextDatum(CC_DATUM);
      mCanvas->drawString(txt,  WIDTH/2, 100);
   }

   for( int8_t i=0; i<4; ++i)
   {
      mSolution[i].setColor( (solution != NULL) ? solution[i] : -1);
      mSolution[i].draw( (WIDTH-4*Peg::WIDTH-3*PEG_SEPARATION)/2+i*(Peg::WIDTH+PEG_SEPARATION), btnY-Peg::HEIGHT-12, mCanvas);
   }
}

void ResultDialog::show(const char *msg, const char *txt, const int8_t *solution, m5epd_update_mode_t mode)
{
   mShown = true;
   drawDialog(msg, txt, solution);
   update(mode);
}

bool ResultDialog::isShow()
{
   return mShown;
}

void ResultDialog::hide()
{
   mShown = false;
}

void ResultDialog::update(m5epd_update_mode_t mode)
{   
   mCanvas->pushCanvas(mX, mY, mode);
}

void ResultDialog::processEvent(int16_t x, int16_t y )
{  
   if(mShown)
   {
      mBtnClose.processEvent(x, y);
   }
}
   
