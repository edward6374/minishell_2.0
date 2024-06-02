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

static void	reset(char *str, int *i, int *j)
{
	ft_bzero(str, 20000);
	*i = 0;
	*j = 0;
}

void	deleting(t_pipe *list)
{
	int		i;
	int		j;
	t_word	*tmp;
	char	str[20000];

	while (list != NULL)
	{
		tmp = list->words;
		while (tmp != NULL)
		{
			reset(str, &i, &j);
			while (tmp->str[i])
			{
				if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
					i++;
				else
					str[j++] = tmp->str[i++];
			}
			str[i] = '\0';
			free(tmp->str);
			tmp->str = ft_strdup(str);
			tmp = tmp->next;
		}
		list = list->next;
	}
}
