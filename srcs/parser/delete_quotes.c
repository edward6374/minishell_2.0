/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:51:04 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:42:15 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

static void	take_out_quotes(t_word *tmp, char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (tmp->str[i])
	{
		if ((tmp->str[i] == '\"' || tmp->str[i] == '\'') && c == 0)
		{
			c = tmp->str[i];
			i++;
		}
		else if (c != 0 && c == tmp->str[i])
		{
			c = 0;
			i++;
		}
		else
			str[j++] = tmp->str[i++];
	}
	str[i] = '\0';
}

void	deleting(t_pipe *list)
{
	t_word	*tmp;
	char	str[20000];

	while (list != NULL)
	{
		tmp = list->words;
		while (tmp != NULL)
		{
			ft_bzero(str, 20000);
			take_out_quotes(tmp, str);
			free(tmp->str);
			tmp->str = ft_strdup(str);
			if (!tmp->str)
				exit_error(g_error_array[0], MALLOC);
			tmp = tmp->next;
		}
		list = list->next;
	}
}
