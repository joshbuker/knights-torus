# Knight's Tour

* [What is a Knight's Tour?](#what-is-a-knights-tour)
* [How does this implementation find a solution?](#how-does-this-implementation-find-a-solution)
* [Screenshots](#screenshots)
* [Installation Requirements](#installation-requirements)
* [Usage](#usage)

## What is a Knight's Tour?

Given a chess board of an arbitrary width and height, take a single knight
starting at any position on the board and find a path such that it visits every
spot on the board exactly once.

## How does this implementation find a solution?

To solve the knight's tour, I created an implementation of Warnsdorff's rule, a
popular heuristic that relies on the following rule: Given each move that is
currently possible, calculate the number of moves that are available from the
potential new location. Move to the spot with the _fewest_ potential moves.

With this heuristic, there is the possibility for ties between moves that have
the same number of potential moves. To resolve ties, I select the first move
available and store the other moves as "critical points" that I can return to
later if the algorithm runs out of potential moves without finding a solution.
If the algorithm reaches this state, it will back the solution up to the most
recent critical point, mark the previous move as a "failed move" so that it does
not reattempt a known bad route, then begin solving with the other tied move(s).
It will repeat this process until either a solution is found, or the algorithm
runs out of critical points and exits without a solution.

I have made several optimizations to increase performance, such as caching the
board state to reduce the number of calculations, and utilizing
pass-by-reference for known performance bottlenecks. Performance will vary
depending on the machine executing the program and the size of the board, but a
MacBook Pro averages about 6.5 seconds to solve a 128x128 board starting at
(1,1).

## Screenshots

![Screenshot of Knight's Tour in progress](README-1.png?raw=true "Knight's Tour in progress")

![Screenshot of program final output](README-2.png?raw=true "Final output")

## Installation Requirements

* Any g++ compiler (c++11 needed for chrono)

## Usage

1. Clone the repo
2. Run `compile-[os].[sh|bat]` to compile the source code into an executable
3. Run executable `./bin/knights-tour.[bin|exe] [x] [y] [width] [height]`

The knight's tour solution (if one is found) will be printed as
`Tour Solution <width>x<height>.txt`.
