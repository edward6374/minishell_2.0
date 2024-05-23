#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"

int	parser(t_min *tk, char *line)//pasado main
{
	t_test	*list;

	list = dividing_pipe(line, 0);
	check_dollar(tk, list);
	deleting(list);
	tk->cmds = get_command_list(list);
	return (0);
}
