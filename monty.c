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
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "Error: Stack is empty\n");
		exit(EXIT_FAILURE);
	}
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
		if (current == *stack)
		{
			break;
		}
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

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	strcpy(filename, argv[1]);
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
	initialize_stack(&stack, file);
	free(line);
	fclose(file);
	return (EXIT_SUCCESS);
}

/**
 * _getline - gets a line from a file
 * @lineptr: pointer to the line
 * @n: pointer to the line length
 * @stream: file
 * Return: line length
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *new_ptr;
	size_t buffer_size = 0;
	size_t line_length = 0;
	int next_char;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	while ((next_char = fgetc(stream)) != EOF)
	{
		if (line_length >= buffer_size)
		{
			buffer_size += 128;
			new_ptr = (char *)realloc(*lineptr, buffer_size);
			if (new_ptr == NULL)
			{
				return (-1);
			}
			*lineptr = new_ptr;
		}
		(*lineptr)[line_length++] = (char)next_char;
		if (next_char == '\n')
		{
			break;
		}
	}
	(*lineptr)[line_length] = '\0';

	if (n != NULL)
	{
		*n = line_length;
	}
	if (line_length == 0)
	{
		return (-1);
	}
	else
	{
		return (line_length);
	}
}
