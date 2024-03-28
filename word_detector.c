/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:10 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/28 19:01:23 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"

void	clean_word(char *div_str, char *word, int *i, int *j)
{
	word[*j] = div_str[*i];
//	printf("(end word) last letter added: %c\n", word[*j]);
	(*j)++;
	word[*j] = '\0';
//	printf("-%s-\n", word);
	*j = 0;
}

void	end_word(t_word **list, char *div_str, char *word, int *i)
{
	put_word_list(list, word);//poner en la lista
	printf("-%s-\n", word);
	ft_bzero(word, *i);
	(*i)++;
	if(div_str[*i] != '\0')
		check_quotes(list, div_str, word, i);
}

void	print_word(t_word **list, char *div_str, char *word, int *i)
{
	int j;
	int quote;

	j = 0;
	quote = 0;
	while(div_str[*i])
	{
		if(div_str[*i] == '\'' || div_str[*i] == '\"' )
			quote++;
		if(div_str[*i] == ' ' && quote == 0)
			(*i)++;
		if((div_str[*i] != ' ' && (div_str[*i+1] == ' ' || div_str[*i+1] == '\0' || div_str[*i+1] == '<' || div_str[*i+1] == '>'))&& quote % 2 == 0)
		{
			clean_word(div_str, word, i, &j);
			end_word(list, div_str, word, i);
		}
		else
		{
			word[j] = div_str[*i];
//			printf("(print word) word leter added: %c\n", word[j]);
			j++;
			(*i)++;
		}
	}
}

void	dividing_words(t_test *list, char *div_str)
{
	int i;
	char word[200];

	i = 0;
	while (list->next != NULL)
		list = list->next;
	while (div_str[i])
	{
		if(div_str[i] == '\"' || div_str[i] == '\'' || div_str[i] == '<' || div_str[i] == '>')
		{
			i = 0;
			check_quotes(&list->words, div_str, word, &i);
		}
		else if(div_str[i] == ' ')
			i++;
		else
			print_word(&list->words, div_str, word, &i);
	}
}
