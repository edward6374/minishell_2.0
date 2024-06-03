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

void	put_word_list(t_word **list, char *word)
{
	char	*str_joined;
	t_word	*tmp;
	t_word	*new;

	//	printf("entro en la lista d palabras\n");
	new = ft_calloc(1, sizeof(t_word));
	//	printf("Word: -%s-\tTrimmed: -%s-\tChar after: -%c-\tInt: %d\n", word,
	// ft_strtrim(word, " "), word[(*i + 1)], *i + 1);
	//	if ((int)ft_strlen(word) >= (*i + 1) && (word[(*i + 1)] == '\''
	// || word[(*i + 1)] == '\"'))
	//	{
	//		word[*i + 1] = '\0';
	//		new->quote_after = 1;
	//	}
	new->str = ft_strtrim(word, " ");
	if (!(*list))
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->quote_after)
		{
			str_joined = ft_strjoin(tmp->str, new->str);
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
	//	print_word_list(list);
}

// funcion para printear la lista, esto va mas arriba
void	print_word_list(t_word **list)
{
	t_word	*temp;

	temp = *list;
	while (temp != NULL)
	{
		// printf("Que palabra hay en la lista: -%s-\n", temp->str);
		temp = temp->next;
	}
}
