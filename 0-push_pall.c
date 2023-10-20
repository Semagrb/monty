#include "monty.h"

/**
 * push - Pushes an element onto the stack
 * @stack: Pointer to the stack
 * @value: The value to push onto the stack
 */
void push(stack_t **stack, int value)
{
stack_t *new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}
new_node->n = value;
new_node->prev = NULL;
new_node->next = *stack;

if (*stack != NULL)
(*stack)->prev = new_node;
*stack = new_node;
}

/**
 * pall - Prints all values on the stack
 * @stack: Pointer to the stack
 * @line_number: The current line number
 */
void pall(stack_t **stack, unsigned int line_number)
{
(void)line_number; /* To suppress unused parameter warning */

stack_t *current = *stack;
while (current != NULL)
{
printf("%d\n", current->n);
current = current->next;
}
}
