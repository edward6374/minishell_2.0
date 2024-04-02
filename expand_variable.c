/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/02 14:19:51 by mehernan         ###   ########.fr       */
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
void	check_dollar(t_min *tk, t_test *list)
{
	int i;
	int j;
	char var[200];

	i = 0;
	j = 0;
	printf("check_dollar\n");
	while(word[i])
	{
		if(word[i] == '$' && word[0] != '\'')
		{
			i = i + 1;
			while(word[i] != '\0' || ((word[i] > 64 && word[i] < 91) || (word[i] > 96 && word[i] < 123)) || (word[i] > 47 && word[i] < 58) || word[i] != '_')
			{
				var[j] = word[i];
				i++;
				j++;
			}
			printf("variable: %s\n", var);
		}
		i++;
	}
}
