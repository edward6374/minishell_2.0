/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_separation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:02 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:45:27 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

static char	*take_div_str(char *input, int i, int *count)
{
	int		sin;
	int		dbl;
	char	*new_str;

	sin = 0;
	dbl = 0;
	while ((input[i + *count] != '|' || (input[i + *count] == '|'
				&& (sin || dbl))) && input[i + *count] != '\0')
	{
		if (input[i + *count] == '\'' && sin == 0)
			sin++;
		else if (input[i + *count] == '\'' && sin == 1)
			sin--;
		if (input[i + *count] == '\"' && dbl == 0)
			dbl++;
		else if (input[i + *count] == '\"' && dbl == 1)
			dbl--;
		*count = *count + 1;
	}
	new_str = ft_calloc((*count + 1), sizeof(char));
	if (!new_str)
		exit_error(g_error_array[0], MALLOC);
	return (new_str);
}

static void	put_list(t_pipe **list, char *div_str)
{
	t_pipe	*tmp;
	t_pipe	*new;

	new = ft_calloc(1, sizeof(t_pipe));
	if (!new)
		exit_error(g_error_array[0], MALLOC);
	new->str = div_str;
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_pipe	*dividing_pipe(char *input, int i)
{
	int		j;
	int		count;
	char	*div_str;
	t_pipe	*list;

	list = NULL;
	while (input[i])
	{
		count = 0;
		div_str = take_div_str(input, i, &count);
		j = 0;
		while (j < count)
			div_str[j++] = input[i++];
		div_str[j] = '\0';
		put_list(&list, div_str);
		dividing_words(list, div_str);
		if (input[i] != '\0')
			i++;
	}
	return (list);
}
