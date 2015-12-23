# How to compile

Simply make it.

The source file is actually compiled and formatted using the following command"
```
main: main.c
	clang-format-3.6 -i -style=LLVM main.c
	astyle --style=linux main.c
	clang-3.6 -Wall -Wextra -o main.o main.c

#https://www.gnu.org/software/make/manual/html_node/Cleanup.html
.PHONY: clean
clean:
	-rm *.o *.c.orig *.h.gch *.h.orig
```

# Sorting algorithm implemented

The `-1` sorting algorithm is quick sort. The `-2` algorithm is bubble sort.

The implementation is very simple. Let's assume the program is required to sort column A by the first algorithm, and B column by the second algorithm. The program will call sorting algorithm one to sort column A, and then call sorting algorithm two to sort both column A and column B. (Because A is already sorted, so the second sorting algorithm will only affect those rows where column A is the same)

After doing the procedure above, the sorting function will sort according to the ID.

So the compare function is written as followed for all 6 data types:
```
if(column As are the same) {
    if(need to sort column B) {
        if(column Bs are the same) {
            sort by ID
        } else {
            sort by column B
        }
    } else {
        sort by ID
    }
} else {
    sort by column A
}
```

# Parsing

The parsing part is pretty tedious.

It's not hard, but it requires some work. Also, because I have implemented some error handling features, such as repeating core command (select, from , order by), mismatch in column names, etc. So the code is awfully long.
