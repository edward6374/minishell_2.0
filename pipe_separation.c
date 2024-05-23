/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_separation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:02 by mehernan          #+#    #+#             */
/*   Updated: 2024/04/02 19:12:09 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"

t_test	*dividing_pipe(char *input, int i)
{
	int		j;
	int		count_for_malloc;
	char	*div_str;
	t_test	*list;

	list = NULL;
	while (input[i])
	{
		count_for_malloc = i;
		while (input[count_for_malloc] != '|' && input[count_for_malloc] != '\0')//to reservate memory with malloc
			count_for_malloc++;
		div_str = malloc((count_for_malloc - i + 1) * (sizeof(char)));
		j = 0;
		while (input[i] != '|' && input[i] != '\0')//to safe every comand on strinig (not necessery to controlle space
		{
			div_str[j] = input[i];
			i++;
			j++;
		}
		printf("%s\n", div_str);
		put_list(&list, div_str);//para meterlo en la lista, ns si es necesario poner el t_test
		dividing_words(list, div_str);
		if (input[i] != '\0')
			i++;
	}
//	free(input);
	print_list(&list);
	return (list);
}
/*
int	parser(t_min *tk, char *line)//pasado main
{
	t_cmd	*cmds;
	t_test	*list;

	list = dividing_pipe(line, 0);
	check_dollar(tk, list);
	deleting(list);
	cmds = get_command_list(list);
	return (0);
}*/
//Aqui finishe todo, tienes que llamar aqui a lo del los comando s y eso
