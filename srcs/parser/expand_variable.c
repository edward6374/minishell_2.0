/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:14:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// static void print_words(t_word *word)
// {
// 	t_word	*tmp;

// 	tmp = word;
// 	while (tmp != NULL)
// 	{
// 		printf("\nWord: %p\nStr: -%s-\nPrev: %p\nNext: %p\n",
//		\ tmp, tmp->str, tmp->prev, tmp->next);
// 		tmp = tmp->next;
// 	}
// }

static void	divide_words_space(t_word *word, int is_var)
{
	int		i;
	int		quotes[2];
	char	*modified;
	t_word	*tmp;
	t_word	*next;

	i = -1;
	ft_bzero(quotes, 2);
	tmp = NULL;
	next = word->next;
	while (word->str[++i] && is_var)
	{
		if (check_quotes(word->str[i], &quotes[0], &quotes[1]) == 0)
		{
			if (!tmp)
				modified = change_first_word(word, NULL, i);
			tmp = take_another_word(word, &i);
			add_new_word(word, next, tmp);
		}
	}
	if (tmp)
	{
		add_new_word(NULL, next, tmp);
		change_first_word(word, modified, i);
	}
}
	// if (is_var)
	// 	print_words(word);

static void	send_variable(t_min *tk, char *var, char *value)
{
	int		i;
	t_env	*tmp;

	i = -1;
	tmp = tk->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			while (tmp->value[++i])
				value[i] = tmp->value[i];
			value[i] = '\0';
			break ;
		}
		tmp = tmp->next;
	}
}

static void	dollar_found(char *str, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && ((str[i] > 64 && str[i] < 91) || (str[i] > 96
				&& str[i] < 123) || (str[i] > 47 && str[i] < 58)
			|| str[i] == '_'))
		var[j++] = str[i++];
	var[j++] = '=';
	var[j] = '\0';
}

static void	find_dollar(t_min *tk, t_word *tmp, char *var, int is_var)
{
	int		i;
	int		sin;
	int		dbl;
	char	value[2000];

	i = -1;
	sin = 0;
	dbl = 0;
	while (tmp->str[++i])
	{
		check_quotes(tmp->str[i], &sin, &dbl);
		if (tmp->str[i] == '$' && sin == 0 && tmp->str[i + 1] != '?')
		{
			if (!ft_isalpha(tmp->str[i + 1]) && tmp->str[i + 1] != '_')
				continue ;
			dollar_found(&tmp->str[++i], var);
			send_variable(tk, var, value);
			i += change_word(tmp, i, ft_strlen(var) - 1, value);
			is_var = 1;
		}
	}
	divide_words_space(tmp, is_var);
}

void	check_dollar(t_min *tk, t_pipe *list)
{
	int		is_var;
	char	var[2000];
	t_word	*tmp;

	is_var = 0;
	while (list != NULL)
	{
		tmp = list->words;
		while (tmp != NULL)
		{
			find_dollar(tk, tmp, var, is_var);
			is_var = 0;
			tmp = tmp->next;
		}
		list = list->next;
	}
}
