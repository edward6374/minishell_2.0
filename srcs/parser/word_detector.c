/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:10 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:36:05 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	take_quotes(char *div_str, char *word, int *i, int *j)
{
	char	car;

	car = div_str[*i];
	word[*j] = div_str[*i];
	(*j)++;
	(*i)++;
	while (div_str[*i] != car)
	{
		word[*j] = div_str[*i];
		(*j)++;
		(*i)++;
	}
	word[*j] = div_str[*i];
}

static void	take_word(t_word **list, char *div_str, char *word, int *i)
{
	int	j;

	j = 0;
	while (div_str[*i] != '\0' && div_str[*i] != ' ')
	{
		if (div_str[*i] == '\'' || div_str[*i] == '\"')
			take_quotes(div_str, word, i, &j);
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
	// printf("word detector, end_word: -%s-\n", word);
	put_word_list(list, word);
	ft_bzero(word, 20000);
}

void	dividing_words(t_pipe *list, char *div_str)
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
		take_word(&list->words, div_str, word, &i);
	}
	// print_word_list(&list->words);
}
