/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/02 20:21:42 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

/*NUEVAS COSITAS UwU
 * si hay un $ significa que lo que hay escrito despues es una variable de entorno.
 * La variable acaba cuando se encuentra algo que no es una letra o un numero o un _
 * */
void	dollar_found(t_word *tmp, int *i)
{
	char var[200];
	int  j;

	j = 0;
	(*i)++;
	printf("UN DOLLAR🤑\n");
	while(tmp->str[*i] != '\0' && ((tmp->str[*i] > 64 && tmp->str[*i] < 91) ||
	(tmp->str[*i] > 96 && tmp->str[*i] < 123) ||
	(tmp->str[*i] > 47 && tmp->str[*i] < 58) || tmp->str[*i] == '_'))
	{
		var[j] = tmp->str[*i];
		printf("added✅: %c\n", var[j]);
		(*i)++;
		j++;
	}
	var[j] = '\0';
	printf("variable: %s\n", var);
	//return(*i);
}

void	find_dollar(t_word *tmp, int *i)
{ 
	int sin;

	sin = 0;
	if (tmp->str[*i] == '\'' && sin == 0)
		sin++;
	else if (tmp->str[*i] == '\'' && sin == 1)
		sin--;
	printf("que char es?: %c\n", tmp->str[*i]);
	if(tmp->str[*i] == '$' && sin == 0)
		dollar_found(tmp, i);
	//return(*i);
}

void	check_dollar(t_min *tk, t_test *list)
{
	int i;
	t_word	*tmp;
	(void)tk;

	while(list != NULL)
	{
		tmp = list->words;
		while (tmp != NULL)
		{
			i = 0;
			while (tmp->str[i])
			{
				find_dollar(tmp, &i);
				i++;
			}
			tmp = tmp->next;
		}
		list = list->next;
	}
}
