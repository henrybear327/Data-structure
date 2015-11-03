main: main.c
	clang-format-3.7 -style=LLVM -i main.c
	astyle --style=linux main.c
	gcc -Wall -Wextra -o main.o main.c 

#https://www.gnu.org/software/make/manual/html_node/Cleanup.html
.PHONY: clean
clean:
	-rm *.o *.c.orig *.h.gch *.h.orig
