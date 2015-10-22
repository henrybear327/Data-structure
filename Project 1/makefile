#don't forget the test.o after -o to produce the name of the whole file
main: main.c
	clang -Wall -Wextra -o main.o main.c 

#https://www.gnu.org/software/make/manual/html_node/Cleanup.html
.PHONY: clean
clean:
	-rm *.o *.c.orig *.h.gch *.h.orig
