# Student

Student ID: 403410033
Name: Chun-Hung Tseng

# Compilation
Use command `gcc -std=c99 -Wall -Wextra -o main.o main.c`, or simply `make` it.

# Program workflow

First, the program will run Floyd Warshall once to get the distance of the shortest path between YMC and the given station. Using Floyd Warshall is a good choice since there are less than 400 vertices and the code to implement it is short.

After getting the needed shortest path, simply run a DFS to explore all possible paths.

# Problems

The problem statement isn't very concise, so I have to generate my own test cases to verify my idea.

Below is the test case that I believe isn't clearly specified in the problem statement.

input:
```
4 3 3 3
1 3 2
0 1 1
1 2 1
2 3 1
```

output:
```
1 0>1>2>3 1
```

# Link to Github

[README](https://github.com/henrybear327/Data-structure/tree/master/Project%203)

# Great explanation

Credited to [Pi-You Chen](https://gist.github.com/BeMg/fc15ad1c3fdb8cbc5cde)
