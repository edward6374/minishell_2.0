/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pipe_separation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:04:56 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/08 20:59:42 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	*put_list(char *div_str)//a ver
{
    t_test	*list;
	t_test	*new;
	t_test	pos;

	list = NULL;
	pos = .
	if(div_str!)
		break;
	while(pos !< 1)
	{
		list->str = div_str
	}
/*    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }*/
}
void	pos_num(char *input)//to know how many positions will be
{
	int i;
	t_test pos;

	pos = 1;
	i = 0;
	while(input[i]!)
	{
		if(input[i] == '|')
			pos++;
		i++;
	}
}
