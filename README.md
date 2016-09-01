## **Disclaimer:** Run this at your own risk. I'm not responsible for anything that happens due to this code.

You will need g++ to compile. (Install MinGW on Windows)

This is only written to run on windows, maybe I'll add unix support some day.

1. Run ```compile.bat``` or ```compile.sh``` to compile source code into executable
2. Run ```run_tour.bat``` or ```run_tour.sh```
3. Solution (if any) will be printed as `Tour Solution <width>x<height>.txt`

Notes: Change backUp() to move to last criticalMove, if all bad, move up chain 1) if all criticalMoves are failed, exit entirely.
