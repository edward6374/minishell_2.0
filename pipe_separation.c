/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_separation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:07:02 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/16 14:01:00 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"

static void	dividing_pipe(char *input, int i)
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
		dividing_words(div_str);
		if (input[i] != '\0')
			i++;
	}
	free(input);
	print_list(&list);
}

int	main(void)
{
	char	*input;
	int		i;

	while (1)
	{
		input = readline("Enter a command: ");
		if (input == NULL)
			break ;
		else if (ft_strcmp(input, "\0") == 0)//in case you enter nothing it has to show you the promp again
		{
			free(input);
			continue ;
		}
		if (ft_strcmp(input, "exit") == 0)//check if user wnts to exit
		{
			printf("Exiting...\n");
			free(input);// Free the memory allocated by readline
			break ;
		}
		add_history(input);
		i = 0;
		dividing_pipe(input, i);
	}
	return (0);
}
