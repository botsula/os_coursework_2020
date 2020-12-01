#include <malloc.h>
#include <zconf.h>

typedef struct block {
    size_t size;
    struct block *next;
    struct block *prev;
} block_t;


static block_t *head = NULL;

/* stats prints some debug information regarding the
 * current program break and the blocks on the free list */
void stats(char *prefix) {
    printf("[%s] program break: %10p\n", prefix, sbrk(0));
    block_t *ptr = head;
    printf("[%s] free list: \n", prefix);
    int c = 0;
    while (ptr) {
        printf("(%d) <%10p> (size: %ld)\n", c, ptr, ptr->size);
        ptr = ptr->next;
        c++;
    }
}



//int
//main(int argc, char const *argv[])
//{
//    int i;
//    int n = 5;
////    atexit(_cleanup);
////    printf("mem page size: %ld bytes\n", sysconf(_SC_PAGESIZE));
////    printf("bytes allocated per malloc: %ld\n", ALLOC_UNIT);
////    stats("begin main");
//    int           *str, *str2;
//    str = (int *)malloc(n * sizeof(int));
//    str2 = (int *)malloc(n * sizeof(int));
//    free(str);
//
//    printf("Memoryyyy successfully allocated using malloc.\n");
//
//        // Get the elements of the array
//        for (i = 0; i < n; ++i) {
//            str2[i] = i + 1;
//        }
//
//        // Print the elements of the array
//        printf("The elements of the array are: ");
//        for (i = 0; i < n; ++i) {
//            printf("%d, ", str2[i]);
//        }
//
//
//
//
////    stats("1");
////    str = (char *)malloc(2);
////    stats("2");
////    free(str2);
////    free(str);
//    stats("end main");
//    return (0);
//}

int main()
{

    // This pointer will hold the
    // base address of the block created
    int *ptr;
    int n, i;

    // Get the number of elements for the array
    n = 5;
    printf("Enter number of elements: %d\n", n);

    // Dynamically allocate memory using malloc()
    ptr = (int*)malloc(n * sizeof(int));
//    stats((char *) (n * sizeof(int)));
//     Check if the memory has been successfully
//     allocated by malloc or not
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        return 0;
    }
    else {

        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;
        }

        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d, ", ptr[i]);
        }
    }

    return 0;
}