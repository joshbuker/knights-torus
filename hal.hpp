#ifndef HAL_HPP
#define HAL_HPP
void startWatch();
void stopWatch();
long watchTime();
void playBeep();
void setCursorPos();
void printProgress(int totalMoves, int currentMove, int failedMoves);
#endif
