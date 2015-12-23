#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//用跟stdlib一樣的宣告形式
void q_sort(void *mem_start, size_t total_member, size_t member_size,
            int (*cmp)(const void *, const void *));

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    return 0;
}

void q_sort(void *mem_start, size_t total_member, size_t member_size,
            int (*cmp)(const void *, const void *))
{
    // zd for printing size_t
    // printf("arguments : %p, %zd, %zd, %p\n", mem_start, total_member,
    // member_size, cmp);
    if (total_member > 1) {
        void *pivot = mem_start;
        void *to_compare = mem_start + (total_member - 1) * member_size;

        while (pivot != to_compare) {
            if ((cmp(pivot, to_compare) > 0 && to_compare > pivot) ||
                (cmp(to_compare, pivot) > 0 &&
                 pivot > to_compare)) { // pivot > to_compare
                // pivot <-> to_compare
                void *temp = malloc(member_size);
                memcpy(temp, pivot, member_size);
                memcpy(pivot, to_compare, member_size);
                memcpy(to_compare, temp, member_size);
                free(temp);

                temp = pivot;
                pivot = to_compare;
                to_compare = temp;

                if (pivot < to_compare)
                    to_compare -= member_size;
                else
                    to_compare += member_size;
            } else {
                if (pivot < to_compare)
                    to_compare -= member_size;
                else
                    to_compare += member_size;
            }
        }

        q_sort(mem_start, ((pivot - mem_start) / member_size), member_size, cmp);

        q_sort(pivot + member_size,
               (total_member - ((to_compare - mem_start) / member_size + 1)),
               member_size, cmp);
    } else {
        // only one or less element, no need to sort
        return;
    }
}
