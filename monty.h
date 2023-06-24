#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
/**
 * struct instrn - opcode and its function
 * @opcode: the opcode
 * 
 * @function: function to handle the opcode
 */
typedef struct instrn
{
	char *opcode;
	void (*function)(stack_t **stack, unsigned int line_number, int argument);
} instrn;

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void initialize_stack(stack_t **stack, FILE *file);
int is_valid_opcode(const char *opcode, instrn *instrns, int num);
int is_valid(const char *opcode, const char *argument);
void pall(stack_t **stack, unsigned int line_number, int n);
void push(stack_t **stack, unsigned int line_number, int n);
void pint(stack_t **stack, unsigned int line_number, int argument);
void printerr(char *opcode, int present, int line_n);
int prnterr(unsigned int line_n);

#endif
