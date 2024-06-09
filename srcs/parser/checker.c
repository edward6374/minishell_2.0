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

static int	check_syntax_pipe(int i, char *line, char c)
{
	i = i + 1;
	if (c == 0)
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] == '|' || line[i] == '\0')
			return (PIPE_FIRST);
	}
	return (0);
}

static int	check_syntax_red(int i, char *line, char c)
{
	i++;
	if (c == 0)
	{
		if (line[i] == '>' || line[i] == '<')
			i++;
		while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
			i++;
		if (line[i] == '\0' || line[i] == '<'
			|| line[i] == '>' || line[i] == '|')
			return (ONLY_REDIR);
	}
	return (0);
}

static int	check_redir(char *line)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && c == 0)
			c = line[i];
		else if (line[i] == c)
			c = 0;
		if ((line[i] == '>' || line[i] == '<') && check_syntax_red(i, line, c))
			return (ONLY_REDIR);
		else if (line[i] == '|' && check_syntax_pipe(i, line, c))
			return (PIPE_FIRST);
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
