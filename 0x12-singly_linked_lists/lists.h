#ifndef LISTS_H
#define LISTS_H

#include <stddef.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for ALX C- Singly linked list project
 */
typedef struct list_s
{
    char *str;
    struct list_s *next;
} list_t;

/* Function prototype */
size_t print_list(const list_t *h);

#endif /* LISTS_H */
