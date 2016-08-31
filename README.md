**Disclaimer:** Run this at your own risk. I'm not responsible for anything that happens due to this code.

Make sure you have MinGW or something else that provides g++

This is only written to run on windows, maybe I'll add unix support some day.

1. Run ```recompile_exe.bat``` to compile source code into executable
2. Run ```run tour.bat```
3. Solution (if any) will be printed as "Tour Solution <width>x<height>.txt"

Notes: Change backUp() to move to last criticalMove, if all bad, move up chain 1) if all criticalMoves are failed, exit entirely.