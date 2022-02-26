#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */

struct list_head *q_new()
{
    struct list_head *new_node =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (new_node == NULL) {
        fprintf(stderr, "Error: unable to allocate required memory\n");
        return NULL;
    }
    INIT_LIST_HEAD(new_node);
    return new_node;
}
/* Free all storage used by queue */
void q_free(struct list_head *l) {}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    size_t slen = strlen(s) + 1;
    element_t *new_node;
    if (!(new_node = (element_t *) malloc(sizeof(element_t))))
        return false;


    if (!(new_node->value = (char *) malloc(sizeof(char) * slen))) {
        free(new_node);
        return false;
    }

    memcpy(new_node->value, s, slen);
    list_add(&new_node->list, head);

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    size_t slen = strlen(s) + 1;
    element_t *new_node;
    if (!(new_node = (element_t *) malloc(sizeof(element_t))))
        return false;


    if (!(new_node->value = (char *) malloc(sizeof(char) * slen))) {
        free(new_node);
        return false;
    }

    memcpy(new_node->value, s, slen);
    list_add_tail(&new_node->list, head);

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return target element.
 * Return NULL if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 *
 * NOTE: "remove" is different from "delete"
 * The space used by the list element and the string should not be freed.
 * The only thing "remove" need to do is unlink it.
 *
 * REF:
 * https://english.stackexchange.com/questions/52508/difference-between-delete-and-remove
 */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || head->next == head || head->prev == head)
        return NULL;
    element_t *temp_node = list_first_entry(head, element_t, list);
    if (sp)
        memcpy(sp, temp_node->value, bufsize);
    list_del(head->next);
    return temp_node;
}

/*
 * Attempt to remove element from tail of queue.
 * Other attribute is as same as q_remove_head.
 */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || head->next == head || head->prev == head)
        return NULL;
    element_t *temp_node = list_last_entry(head, element_t, list);
    if (sp)
        memcpy(sp, temp_node->value, bufsize);
    list_del(head->prev);
    return temp_node;
}

/*
 * WARN: This is for external usage, don't modify it
 * Attempt to release element.
 */
void q_release_element(element_t *e)
{
    free(e->value);
    free(e);
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;
    list_for_each (li, head)
        len++;
    return len;
}

/*
 * Delete the middle node in list.
 * The middle node of a linked list of size n is the
 * ⌊n / 2⌋th node from the start using 0-based indexing.
 * If there're six element, the third member should be return.
 * Return true if successful.
 * Return false if list is NULL or empty.
 */
bool q_delete_mid(struct list_head *head)
{
    if (!head || head->next == head)
        return false;

    struct list_head *slow_pointer = head;
    struct list_head *fast_pointer = head;
    do {
        fast_pointer = fast_pointer->next->next;
        slow_pointer = slow_pointer->next;
    } while (fast_pointer != head && fast_pointer->next != head);
    element_t *temp = list_entry(slow_pointer, element_t, list);
    list_del(slow_pointer);
    free(temp->value);
    free(temp);
    return true;
}

/*
 * Delete all nodes that have duplicate string,
 * leaving only distinct strings from the original list.
 * Return true if successful.
 * Return false if list is NULL.
 *
 * Note: this function always be called after sorting, in other words,
 * list is guaranteed to be sorted in ascending order.
 */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/*
 * Attempt to swap every two adjacent nodes.
 */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(struct list_head *head) {}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(struct list_head *head) {}
