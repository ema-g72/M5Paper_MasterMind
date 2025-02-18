/* Master Mind game for M5 Paper device.
 *
 * This class implements the MasterMind game rules. 
 */
 
#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_

#include <M5EPD.h>

class MasterMind
{
public:
   static const int NUM_COLORS = 6;
   static const int NUM_PEGS = 4;
   
   MasterMind();

   void init();

   void getHiddenCode(int8_t *code);

   bool play(const int8_t *code, int8_t *num_whites, int8_t *num_blacks);
   
private:
   
   int8_t mHiddenCode[NUM_PEGS];
};

#endif 
