#ifndef HAL_HPP
#define HAL_HPP
void startWatch();
void stopWatch();
long watchTime();
void playBeep();
void setCursorPos();
void printProgress(const int & totalMoves, const int & currentMove, const int & failedMoves);
#endif
