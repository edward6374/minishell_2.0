#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"

int	check_syntax_pipe(int i, char *line, int q)
{
	i = i + 1;
	if( q % 2 == 0)
	{
		if(line[i] == '|' || line[i] == '\0'/* || line[i] == ' '*/)
			return (SYNTAX);
	}
	return (0);
}

int	check_syntax_red(int i, char *line, int q)
{
	i++;
	if(q % 2 == 0)
	{
		if(line[i] == '>' || line[i] == '<')
			i++;
		if(/*line[i] == ' ' ||*/ line[i] == '\0' || line[i] == '<' || line[i] == '>')
			return (SYNTAX);
	}
	return (0);
}

int	check_redir(char *line)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			q++;
		if ((line[i] == '>' || line[i] == '<') && check_syntax_red(i, line, q))
			return (SYNTAX);
		else if (line[i] == '|' && check_syntax_pipe(i, line, q))
			return (SYNTAX);
		i++;
	}
	return (0);
}

int	check_syntax(char *line)
{
	int	i;
	int	dbl;
	int	sngl;

	i = 0;
	dbl = 0;
	sngl = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
			dbl++;
		else if (line[i] == '\'')
			sngl++;
		i++;
	}
	if ((dbl != 0 && dbl % 2 != 0) || (sngl != 0 && sngl % 2 != 0))
		return (SYNTAX);
	return (check_redir(line));
}
