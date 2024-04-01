/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_word_detector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:22 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/28 19:03:42 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
void	check_dollar(char *word)
{
	int i;
	int j;
	char var[200];

	i = 0;
	j = 0;
	while(word[i])
	{
		if(word[i] == '$' && word[0] != '\'')
		{
			i = i + 1;
			while(word[i] != '\0' || ((word[i] > 64 && word[i] < 91)
			|| (word[i] > 96 && word[i] < 123)) || (word[i] > 47 &&
		       	word[i] < 58) || word[i] != '_')
			{
				var[j] = word[i];
				i++;
				j++;
			}
			//nombre de la funcion que hara algo con la variable
		}
	}
}
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
	check_dollar(word);
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
