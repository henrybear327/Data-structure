# Source code

Only `main.c` in the `Project 2` root directory is the latest version.

Other `main.c` is just the copy of it for, say, turn-in purpose.

# Things to know

* The output of this program is colorful!
    * Valid input responses and answer outputs are in `green`.
    * Invalid input responses and error messages are in `red`.

# Compilation

Simply use `make` to build it.

**Notice**: You can change the `#define DEBUG 0` to `#define DEBUG 1`. By doing so, you can get a whole lot of debugging information!

# Starting the program

Use `./main.o` to start the program.

## Main menu

You will be presented with the main menu upon starting the program:
```
Please make a choice:
(B)inary Search Tree.
(T)reasure Hunter
(E)xit
```
**Notice**: The program takes both the upper and lower letters as valid command input.

## Part (I): Binary Search Tree.

If you choose (B), then you will be presented with this menu:
```
Please make a choice:
(I)nsert a number.
(D)elete a number.
(S)earch a number.
(P)rint in infix & level order.
(R)eturn
```

Type commands and just follow the instructions!

## Part (II): Treasure Hunter

If you choose (T), then you will be prompted to enter the filename first:
```
Please input the name of the map file without spaces:
```

If the file is loaded successfully, then you will be prompted to enter two numbers,
namely key and treasure locations:
```
Please input the key location:
Please input the treasure location:
```

Also, if the shortest path exists, the shortest path will be printed, e.g.:
```
The shortest path is: 7->4->2->3->2->4->7->12->8->9
```

Otherwise, the error message will pop out, e.g.:
```
Key is not found.
Treasure is not found.
```

After getting through all these questions, you will be redirected back to the main menu.
