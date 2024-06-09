/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_word_detector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:22 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:40:12 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

// funcion para printear la lista, esto va mas arriba
// void	print_word_list(t_word **list)
// {
// 	t_word	*temp;

// 	temp = *list;
// 	while (temp != NULL)
// 	{
// 		printf("Que palabra hay en la lista: -%s-\n", temp->str);
// 		temp = temp->next;
// 	}
// }

static void	add_to_list(t_word *tmp, t_word *new)
{
	char	*str_joined;

	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->quote_after)
	{
		str_joined = ft_strjoin(tmp->str, new->str);
		if (!str_joined)
			exit_error(g_error_array[0], MALLOC);
		free(tmp->str);
		tmp->str = str_joined;
		free(new->str);
		free(new);
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	put_word_list(t_word **list, char *word)
{
	t_word	*tmp;
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		exit_error(g_error_array[0], MALLOC);
	new->str = ft_strtrim(word, " ");
	if (!new->str)
		exit_error(g_error_array[0], MALLOC);
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		add_to_list(tmp, new);
	}
}
//	print_word_list(list);
