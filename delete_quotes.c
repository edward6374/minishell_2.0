/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:51:04 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/15 18:39:59 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	deleting(t_test *list)
{
	t_word *tmp;
	char str[20000];
	int i;
	int j;

	while(list != NULL)
	{
		tmp = list->words;
		while(tmp != NULL)
		{
			ft_bzero(str, j);
			i = 0;
			j = 0;
			while(tmp->str[i])
			{
				if(tmp->str[i] == '\"' || tmp->str[i] == '\'')
					i++;
				else
				{
					str[j] = tmp->str[i];
					printf("char str: %c\n", str[j]);
					j++;
					i++;
				}
			}
			str[i] = '\0';
			printf("palabra nueva: %s\n", str);
			free(tmp->str);
			tmp->str = ft_strdup(str);
			tmp = tmp->next;
		}
		list = list->next;
	}
}
