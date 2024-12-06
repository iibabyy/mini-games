#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
# define is ==
# define is_not !=

void	brainfuck(char *str) {
	unsigned char	memory[2048];
	unsigned char	*ptr;
	int				bracket;

	memset(memory, 0, 2048);
	ptr = memory;
	while (*str) {
		if (*str is '>')
			ptr++;
		else if (*str is '<')
			ptr--;
		else if (*str is '+')
			(*ptr)++;
		else if (*str is '-')
			(*ptr)--;
		else if (*str is '.')
			write(1, ptr, 1);
		else if (*ptr is 0 && *str is '[')
		{
			bracket = 1;
			while (bracket) {
				str++;
				if (*str is '[')
					bracket++;
				else if (*str is ']')
					bracket--;
			}
		}
		else if (*ptr is_not 0 && *str is ']')
		{
			bracket = 1;
			while (bracket) {
				str--;
				if (*str is '[')
					bracket--;
				else if (*str is ']')
					bracket++;
			}
		}
		str++;
	}
}

int	main(int argc, char **argv) {
	if (argc is_not 2) {
		write(1, "\n", 1);
		return (0);
	} else {
		brainfuck(argv[1]);
	}
	return (0);
}
