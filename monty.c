#include "monty.h"
/**
 * push - pushes an element to the stack
 * @stack: pointer to the stack
 * @line_number: line number
 * @n: number
 * Return: void
*/
void push(stack_t **stack, unsigned int line_number, int n)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	(void)line_number;
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}
/**
 * pall - prints all the elements of the stack
 * @stack: pointer to the stack
 * @line_number: line number
 * @n: number
 * Return: void
*/
void pall(stack_t **stack, unsigned int line_number, int n)
{
	stack_t *current = *stack;

	(void)n;
	(void)line_number;
	if (stack == NULL)
	{
		fprintf(stderr, "Error: Stack is NULL\n");
		exit(EXIT_FAILURE);
	}
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0
*/
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	stack_t *stack = NULL;
	char filename[100];

	strcpy(filename, argv[1]);
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	if (strlen(filename) >= 2)
	{
		if (strcmp(filename + strlen(filename) - 2, ".m") == 0)
		{
			file = fopen(argv[1], "r");
			if (file == NULL)
			{
				fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
				return (EXIT_FAILURE);
			}
		}
	}
	else
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", filename);
		return (EXIT_FAILURE);
	}
	initialize_stack(&stack, file);
	free(line);
	fclose(file);
	return (EXIT_SUCCESS);
}

