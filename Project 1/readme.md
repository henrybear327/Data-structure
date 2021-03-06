# Project 1

### Stack and Queue -- Walking rats in a maze

Tseng, Chun-Hung 403410033

### Compilation

Using `clang -Wall -Wextra -o main.o main.c`, which have been written to a makefile. Just `make` it!

### Usage

As required, the program automatically loads a file named `maze.txt`, and outputs a file named `result.txt`

### Intro and first thought

This is a typical maze problem which can be solved by using simple DFS algorithm. Without using the stack, there is actually a way to DFS both rats in the maze and record both the paths and the timestamps. After that, we can simply run a for loop over both the recorded path and timestamps, and check whether the rats have met or not.

By using stack, the idea is just like DFS, but without using recursion. Just push every step into the stack, and pop out the top element whenever we return.

### Adversity and bugs

One stupid bug that I have stumble upon is setting the wrong direction arrays. I changed the row value when I am moving right and left, where the correct solution is to change the column value.

Another bug is that the floors are actually 0 and 1 in C language instead of 1 and 2.

Also, I designed the stack pointer pointing to the one-pass-the-last element. This led to a trivial bug, where I printed the element directly pointed by the pointer.

### Implementation

Set up two stacks initially, starting at (0, 1, 1) and (1, 99, 99) respectively. Walk both rat A and rat B in one cycle, and push the next possible step into the stack(if not out-of-bound, not visited, and not wall). However, if there isn't any possible steps, return the the previous location stored in the stack, which is the top element in it.

Repeat these steps until one rat reaches the end(which is the starting point of another rat in the maze), both rats reach the end, or they meet.

# Sidenotes

It's a good idea to try [this problem](http://140.116.249.152/e-Tutor/mod/programming/view.php?a=11600 "ITSA 38 [Problem 4] 迷宮路徑") first.
