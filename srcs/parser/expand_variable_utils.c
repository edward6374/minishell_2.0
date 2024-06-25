/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:14:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

char	*change_first_word(t_word *word, char *mod, int i)
{
	int		j;
	char	*out;

	j = 0;
	if (!mod)
	{
		out = ft_calloc(i + 1, sizeof(char));
		while (j < i)
		{
			out[j] = word->str[j];
			j++;
		}
		out[j] = '\0';
		return (out);
	}
	else
	{
		free(word->str);
		word->str = mod;
		return (NULL);
	}
}

void	add_new_word(t_word *word, t_word *next, t_word *tmp)
{
	if (!word)
	{
		tmp->next = next;
		if (next)
			next->prev = tmp;
	}
	else if (word->next == next)
	{
		word->next = tmp;
		tmp->prev = word;
	}
	else
	{
		while (word->next)
			word = word->next;
		word->next = tmp;
		tmp->prev = word;
	}
}

int	check_quotes(char c, int *sin, int *dbl)
{
	if (c == '\'' && *sin == 0)
		*sin = *sin + 1;
	else if (c == '\'' && *sin == 1)
		*sin = *sin - 1;
	else if (c == '\"' && *dbl == 0)
		*dbl = *dbl + 1;
	else if (c == '\"' && *dbl == 1)
		*dbl = *dbl - 1;
	else
	{
		if ((c == ' ') && *sin == 0 && *dbl == 0)
			return (0);
	}
	return (1);
}

t_word	*take_another_word(t_word *word, int *i)
{
	int		j;
	int		sin;
	int		dbl;
	char	value[2000];
	t_word	*tmp;

	j = -1;
	sin = 0;
	dbl = 0;
	tmp = ft_calloc(1, sizeof(t_word));
	if (!tmp)
		exit_error(g_error_array[MALLOC], MALLOC);
	while (word->str[*i] == ' ')
		*i = *i + 1;
	while (word->str[*i + ++j] != '\0'
		&& check_quotes(word->str[*i + j], &sin, &dbl))
		value[j] = word->str[*i + j];
	value[j] = '\0';
	tmp->str = ft_strdup(value);
	if (!tmp->str)
		exit_error(g_error_array[MALLOC], MALLOC);
	if (word->str[*i] == ' ')
		*i = *i - 1;
	return (tmp);
}
