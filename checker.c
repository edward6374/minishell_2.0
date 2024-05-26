#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"
void	pipe(int i, char *line)
{
	i = i+ 1;
	if(line[i] == '|' || line[i] == '\0' || line[i] == ' ')
		return(SYNTAX_ERROR);
	//quizas mas cosas
}
void	red(int i, char *line)
{
	i++;
	if(line[i] == '>' || line[i] == '<')
		i++;
	if(line[i] == ' ' || line[i] == '\0' || line[i] == '<' || line[i] == '>')
		return(SYNTAX_ERROR);
}
int	corrector(char *line)
{
	int	i;
	int	dbl;
	int	sngl;

	i = 0;
	dbl = 0;
	sngl - 0;
	while(line[i] != NULL)
	{
		if(line[i] == '\"')
			dbl++;
		else if(line[i] == '\'')
			sngl++;
		else if(line[i] == '>' || line[i] == '<')
			red(i, line);
		else if(line[i] == '|')
			pipe(i, line);
		i++;
	}
	if((dbl != 0 && dbl % 2 != 0) || (sgl != 0 && sgl % 2 != 0)) 
		return(SINTAX_ERROR);
	return(0);
}
