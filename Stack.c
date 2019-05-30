/********************
 * 
 * Sentence reversal program using Linked List based Stack
 * 
 ********************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

// create the struct
struct Node_t_t
{
    char *value;
    struct Node_t_t *next;
};

// create the shortform
typedef struct Node_t_t Node_t ;

// function templates
Node_t *newNode(const char *value, Node_t *next);
Node_t *deleteNode(Node_t *current, char **value);
bool pop(Node_t **head, char **value);
bool push(Node_t **head, const char *value);

/* use void as parameters to silence the gcc warnings */
int main(void)
{
    // initialize our things
    Node_t *Stack = NULL;
    char buffer[BUFFER_SIZE] = { 0 };

    // fill our stack from the user input
    while(1 == scanf("%s", buffer))
    {
        push(&Stack, buffer);
    }

    // write out the sentence in reverse order
    while(Stack != NULL)
    {
        char *str = NULL;
        bool popped = pop(&Stack, &str);
        if( popped && NULL != str )
        {
            printf("%s ", str);
            free(str);
        }
    }

    return EXIT_SUCCESS;
}

/**************
 * TODO: Finish implementing these functions
 */

/**
 * return a NULL pointer if it failed to allocate memory
 * makes a copy of the string `value` on the heap (see strdup())
 * and stores the pointer in the newly created Node.
 * sets the next node to be the parameter `next`
 */
Node_t *newNode(const char *value, Node_t *next)
{
    Node_t * fresh_node = malloc(sizeof(Node_t));
    char *copy = strdup(value);
    fresh_node -> value = copy; 
    fresh_node -> next = next;
    if (fresh_node == NULL) {
        printf("Fresh Node not created");
        return NULL;
    } else return fresh_node;
}

/**
 * puts the current node string pointer at the `value` parameter
 * free's the `current` Node.
 * and return the next node.
 */
Node_t *deleteNode(Node_t *current, char **value)
{
    Node_t * p = current;
    if (p == NULL) {
        return p;
    }
    if ((p -> value) == *value){
        p = p -> next;
        free(current);
        return p;
    }
    Node_t * q = p -> next;
    while ((q != NULL) &&((q -> value) != *value)) {
        p = p -> next;
        q = q -> next;
    }
    if (q != NULL) {
        p->next = q->next;
        free(q);
    }
    return p;
}

/**
 * Pop the string from the top of the stack using deleteNode
 * update the top of the stack
 * puts the popped string onto `value`
 * return true on success
 */
bool pop(Node_t **Stack, char **value)
{
    Node_t *cur_node = *Stack;
    bool success = false;
    if(cur_node -> next == NULL) {
        deleteNode(cur_node, value);
        success = true;
    } else pop(&cur_node, value);   
    return success;
}

/**
 * Push the string to the top of the stack using newNode
 * update the top of the stack
 * return true if everything is successfull
 */
bool push(Node_t **Stack, const char *value)
{
    Node_t *cur_node = *Stack;
    bool success = false;
    if(cur_node -> next == NULL) {
        newNode(value, *Stack);
        success = true;
    } else push(&cur_node, value);   
    return success;
}