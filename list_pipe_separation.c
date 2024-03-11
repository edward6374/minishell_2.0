/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pipe_separation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:04:56 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/11 14:24:25 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	*put_list(t_test **list, char *div_str)//a ver
{
//    t_test	*list;
	t_test	*tmp;
	t_test	*new;
//	t_test	pos;

	list = NULL;
//	pos = .
	if(!div_str)
		break;
	new = ft_calloc(1, t_test);
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

// funcion para printear la lista, esto va mas arriba
void	print_list(t_test **temp)
{
	 while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }
}
