#include "arraylist.h"   
//#include "linkedlist.h"
#include <stdio.h>

int main()
{
    const char* input_filename = "books.txt";
    FILE *file = fopen(input_filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int number_of_books;
    fscanf(file, "%d", &number_of_books);  

    const int CAPACITY = 10;
    ArrayList list;
    init_arraylist(&list, CAPACITY);
    //LinkedList list;
    //init_linkedlist(&list);

    for (int i = 0; i < number_of_books; i++) {
        int book_id;
        fscanf(file, "%d", &book_id);
        append(&list, book_id);
    }
    print_list(&list);
    printf("\n");

    reverse(&list);                        

    printf("Reversed list: ");              
    print_list(&list);

    free_list(&list);
    fclose(file);
    return 0;
}