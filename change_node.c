/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/09 20:21:42 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	change_word( t_word *tmp, char *value, int *i)
{
	int count;
	int j;

	count = *i;
	j = 0;
	while(tmp->str[*i] != '$')
		(*i)--;
	printf("deberia ser dollar: %c\n", tmp->str[*i]);
	while(count != -1)
	{
		tmp->str[*i] = value[j];
		printf("value added: %c\n", tmp->str[*i]);
//		pritnf("count: %d\n", count);
		(*i)++;
		j++;
		count--;
	}
}
