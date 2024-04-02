/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_word_detector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:22 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/02 14:19:51 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	put_word_list(t_word **list, char *word)//a ver
{
//	printf("entro en la lista d palabras\n");
	t_word	*tmp;
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	new->str = ft_strtrim(word, " ");
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
	print_word_list(list);
}

// funcion para printear la lista, esto va mas arriba
void	print_word_list(t_word **list)
{
	t_word *temp;

	temp = *list;
	while (temp != NULL)
    {
        printf("Que palabra hay en la lista: -%s-\n", temp->str);
        temp = temp->next;
    }
}
