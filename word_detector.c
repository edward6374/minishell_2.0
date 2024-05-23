/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:10 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/23 20:40:46 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

static void	take_redirection(char *div_str, char *word, int *i, int *j)
{
	if (*j == 0)
	{
		word[*j] = div_str[*i];
		(*j)++;
		(*i)++;
		if (div_str[*i] == div_str[*i - 1])
		{
			word[*j] = div_str[*i];
			(*i)++;
			(*j)++;
		}
		word[*j] = '\0';
	}
}

void	end_word(t_word **list, char *word)
{
	printf("word detector, end_word: -%s-\n", word);
	put_word_list(list, word);//poner en la lista
	ft_bzero(word, 20000);
}

void	print_word(t_word **list, char *div_str, char *word, int *i)
{
	int	j;
	int	quote;
	int	car;

	j = 0;
	quote = 0;
	while(div_str[*i] != '\0' && div_str[*i] != ' ')
	{
		if(div_str[*i] == '\'' || div_str[*i] == '\"' )
		{
			car = div_str[*i];
			word[j] = div_str[*i];
			j++;
			(*i)++;
			while (div_str[*i] != car)
			{
				word[j] = div_str[*i];
				j++;
				(*i)++;
			}
			word[j] = div_str[*i];
		}
		else
		{
			if (div_str[*i] == '<' || div_str[*i] == '>')
			{
				take_redirection(div_str, word, i, &j);
				break ;
			}
			word[j] = div_str[*i];
		}
		j++;
		(*i)++;
	}
	word[j] = '\0';
	end_word(list, word);
}

void	dividing_words(t_test *list, char *div_str)
{
	int		i;
	char	word[20000];

	i = 0;
	while (list->next != NULL)
		list = list->next;
	while (div_str[i])
	{
		while (div_str[i] == ' ')
			i++;
		if (div_str[i] == '\0')
			break ;
		print_word(&list->words, div_str, word, &i);
	}
}
