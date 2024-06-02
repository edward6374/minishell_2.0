/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:22 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:41:40 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_syntax_pipe(int i, char *line, int q)
{
	i = i + 1;
	if( q % 2 == 0)
	{
		if(line[i] == '|' || line[i] == '\0'/* || line[i] == ' '*/)
			return (SYNTAX);
	}
	return (0);
}

static int	check_syntax_red(int i, char *line, int q)
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

static int	check_redir(char *line)
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
