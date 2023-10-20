#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

stack_t *stack = NULL;

void push(stack_t **stack, int value) {
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack) {
        (*stack)->prev = new_node;
    }
    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number) {
    (void)line_number; // Unused parameter

    stack_t *current = *stack;
    while (current) {
        printf("%d\n", current->n);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char *token = strtok(line, " \t\n");
        if (token == NULL) {
            continue; // Empty line, move to the next one
        }

        if (strcmp(token, "push") == 0) {
            token = strtok(NULL, " \t\n");
            if (token == NULL) {
                fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
                fclose(file);
                return EXIT_FAILURE;
            }

            if (!isdigit(token[0]) && (token[0] != '-' && !isdigit(token[1]))) {
                fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
                fclose(file);
                return EXIT_FAILURE;
            }

            int value = atoi(token);
            push(&stack, value);
        } else if (strcmp(token, "pall") == 0) {
            pall(&stack, line_number);
        } else {
            fprintf(stderr, "Error: L%d: unknown opcode %s\n", line_number, token);
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
