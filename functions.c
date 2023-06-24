#include "monty.h"
/**
 * process_line - processes a line
 * @line: line
 * @line_n: line number
 * @stack: pointer to the stack
 * Return: void
*/
void process_line(char *line, size_t line_n, stack_t **stack)
{
	instrn instrns[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
	};
	int n;
	char *opcode;
	char *argument;
	int i;
	int instrns_n;
	int present = 0;
	size_t opcode_len;

	opcode = strtok(line, " \t\n");
	argument = strtok(NULL, " \t\n");
	if (opcode == NULL || strcmp(opcode, "#") == 0)
		return;
	opcode_len = strlen(opcode);
	if (opcode[opcode_len - 1] == '$')
		opcode[opcode_len - 1] = '\0';
	instrns_n = sizeof(instrns) / sizeof(instrns[0]);
	for (i = 0; i < instrns_n; i++)
	{
		if (strcmp(opcode, instrns[i].opcode) == 0)
		{
			if (argument == NULL && strcmp(opcode, "push") == 0)
			{
				prnterr(line_n);
				return;
			}
			if (argument)
				n = atoi(argument);
			else
				n = 0;
			instrns[i].function(stack, line_n, n);
			present = 1;
			break;
		}
	}
	printerr(opcode, present, line_n);
}
/**
 * printerr - prints an error message
 * @opcode: opcode
 * @present: present
 * Return: void
*/
void printerr(char *opcode, int present, int line_n)
{
	if (!present)
		fprintf(stderr, "L%u: unknown instruction %s\n", line_n, opcode);
}
/**
 * prnterr - prints an error message
 * @line_n: line number
 * Return: void
*/
int prnterr(unsigned int line_n)
{
	fprintf(stderr, "L%u: usage: push integer\n", line_n);
	return (1);
}
/**
 * initialize_stack - initializes the stack
 * @stack: pointer to the stack
 * @file: file
 * Return: void
*/
void initialize_stack(stack_t **stack, FILE *file)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_n = 0;

	while ((read = _getline(&line, &len, file)) != -1)
	{
		line_n++;
		process_line(line, line_n, stack);
	}

	free(line);
}
/**
 * process_file - processes a file
 * @filename: file
 * Return: void
*/
void process_file(const char *filename)
{
	stack_t *stack = NULL;
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file: %s\n", filename);
		return;
	}

	initialize_stack(&stack, file);

	fclose(file);
}
