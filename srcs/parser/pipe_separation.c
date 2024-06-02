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

// void	print_list(t_pipe **list)
// {
// 	t_pipe	*temp;

// 	temp = *list;
// 	while (temp != NULL)
//     {
//         printf("Que hay en la lista: -%s-\n", temp->str);
//         temp = temp->next;
//     }
// }

static void	put_list(t_pipe **list, char *div_str)
{
	t_pipe	*tmp;
	t_pipe	*new;

	new = ft_calloc(1, sizeof(t_pipe));
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
		count = 1;
		while (input[count] != '|' && input[count] != '\0')
			count++;
		div_str = malloc((count + 1) * (sizeof(char)));
		j = 0;
		while (input[i] != '|' && input[i] != '\0')
			div_str[j++] = input[i++];
		div_str[j] = '\0';
		printf("Div str: %s\n", div_str);
		put_list(&list, div_str);
		dividing_words(list, div_str);
		if (input[i] != '\0')
			i++;
	}
	// print_list(&list);
	return (list);
}
