#include "monty.h"
#include <stdio.h>
/**
 * initialize_stack - initializes the stack
 * @stack: pointer to the stack
 * @file: file
 * Return: void
*/
void initialize_stack(stack_t **stack, FILE *file)
{
	Instruction instructions[] = {
		{"push", push},
		{"pall", pall}
		};
	char *line = NULL;
	size_t len = 0;
	size_t read;
	unsigned int line_number = 0;
	int i;
	int n = 0;
	char *opcode;
	char *argument;
	int num_instructions = sizeof(instructions) / sizeof(instructions[0]);

	while ((read = _getline(&line, &len, file)) != (size_t)-1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		argument = strtok(NULL, " \t\n");
		if (opcode == NULL || strcmp(opcode, "#") == 0)
			continue;
		if (!is_valid_opcode(opcode, instructions, num_instructions))
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}
		if (strcmp(opcode, "push") == 0)
		{
			is_valid(opcode, argument);
			n = atoi(argument);
		}
		for (i = 0; i < num_instructions; i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				instructions[i].function(stack, line_number, n);
				return;
			}
		}
	}
}
/**
 * is_valid_opcode - checks if the opcode is valid
 * @opcode: opcode
 * @instructions: instructions
 * @num: number of instructions
 * Return: 1 if valid
*/
int is_valid_opcode(const char *opcode, Instruction *instructions, int num)
{
	int i;

	for (i = 0; i < num; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
			return (1);
	}
	return (0);
}
/**
 * is_valid - checks if the argument is valid
 * @opcode: opcode
 * @argument: argument
 * Return: 1 if valid
*/
int is_valid(const char *opcode, const char *argument)
{
	if (strcmp(opcode, "push") == 0 && argument == NULL)
	{
		fprintf(stderr, "Error: usage: push integer\n");
		exit(EXIT_FAILURE);
	}
	return (strcmp(opcode, "push") == 0 && argument != NULL);
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
	size_t buffer_size = 128;
	size_t line_length = 0;
	int next_char;

	if (lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}
	*lineptr = (char *)malloc(buffer_size);
	if (*lineptr == NULL)
	{
		return (-1);
	}
	while ((next_char = fgetc(stream)) != EOF)
	{
		(*lineptr)[line_length++] = (char)next_char;
		if (line_length >= buffer_size)
		{
			buffer_size *= 2;
			new_ptr = (char *)realloc(*lineptr, buffer_size);
			if (new_ptr == NULL)
			{
				return (-1);
			}
			*lineptr = new_ptr;
		}
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
	return ((ssize_t)line_length);
}
