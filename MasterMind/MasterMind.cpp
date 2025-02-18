/* Master Mind game for M5 Paper device.
 *
 * This class implements the MasterMind game rules. 
 */
 
#include "MasterMind.h"
 
MasterMind::MasterMind()
{   
}

void MasterMind::init()
{
   for( int i=0; i<NUM_PEGS; ++i)
   {
      mHiddenCode[i] = random(0, NUM_COLORS);
   }
}

void MasterMind::getHiddenCode(int8_t *code)
{
   for( int i=0; i<NUM_PEGS; ++i)
   {
      code[i] = mHiddenCode[i];
   }   
}

bool MasterMind::play(const int8_t *code, int8_t *num_whites, int8_t *num_blacks)
{
   int white = 0;
   int black = 0;
   
   int blackMask = 0;
   int whiteMask = 0;

   // Search for the correct color in correct position.
   for( int i=0; i<NUM_PEGS; ++i)
   {
      if( code[i] == mHiddenCode[i] )
      {    
         blackMask |= (1 << i);
         black ++;
      }
   }
  
   // Search for the correct color in wrong position.
   for( int i=0; i<NUM_PEGS; ++i)
   {
      if(blackMask & (1 << i) )
      {
         continue;
      }
         
      for( int j=0; j<NUM_PEGS; ++j)
      {
         bool not_black = !(blackMask & (1 << j));
         bool not_white = !(whiteMask & (1 << j));

         if( not_black&& not_white && (code[i] == mHiddenCode[j]) )
         {    
            whiteMask |= (1 << j);
            white ++;
            break;
         }
      }
   }
   
   *num_whites = white;
   *num_blacks = black;
   
   return (black == NUM_PEGS);
}
