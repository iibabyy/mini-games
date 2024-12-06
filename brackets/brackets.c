#include <stdbool.h>
#include <unistd.h>

bool	is_open_bracket(char c) {
	return (c == '(' || c == '[' || c == '{');
}

bool	is_close_bracket(char c) {
	return (c == ')' || c == ']' || c == '}');
}

char	close_bracket_for(char c) {
	if (c == '(')
		return (')');
	else if (c == '[')
		return (']');
	else if (c == '{')
		return ('}');
	return (0);
}

bool	check_open_bracket(char *str, int *i) {
	char	bracket = str[*i];

	while (str[++*i]) {
		if (is_open_bracket(str[*i])) {
			if (check_open_bracket(str, i) == false)
				return (false);
		}
		else if (str[*i] == close_bracket_for(bracket))
			return (true);
		else if (is_close_bracket(str[*i]))
			return (false);
	}
	return (false);
}

bool	bracket(char *str) {
	int	i = -1;
	while (str[++i]) {
		if (is_open_bracket(str[i])) {
			if (check_open_bracket(str, &i) == false)
				return (false);
		}
		else if (is_close_bracket(str[i]))
			return (false);
	}
	return (true);
}

int main(int ac, char **av) {
	int i = 0;
	if (ac == 1)
		return (write(1, "\n", 1), 0);
	while (av[++i]) {
		if (bracket(av[i]) == false)
			write(1, "Error\n", 7);
		else
			write(1, "OK\n", 3);
	}
    return 0;
}