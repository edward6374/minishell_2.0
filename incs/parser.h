/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/04/02 20:21:42 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
typedef struct s_word // lo usaremos para separar palabrras
{
    char *str;
    struct s_word *prev;
    struct s_word *next;
} t_word;

typedef struct s_test
{
    char			*str;
	t_word			*words;
	struct s_test	*prev;
    struct s_test	*next;
} t_test;

void	put_list(t_test **list, char *div_str);
void	print_list(t_test **list);
void	dividing_words(t_test *list, char *div_str);//pot ser no cal
void	print_word(t_word **list, char *div_str, char *word, int *i);
void	end_word(t_word **list, char *div_str, char *word, int *i);
void	print_word_double_quotes(t_word **list, char *div_str, char *word, int *i);
void	print_word_simple_quotes(t_word **list, char *div_str, char *word, int *i);
void	print_redirection(t_word **list, char *div_str, char *word, int *i);
void	check_quotes(t_word **list, char *div_str, char *word, int *i);
void	put_word_list(t_word **list, char *word);
void	print_word_list(t_word **list);
int	parser(t_min *tk, char *line);
void	check_dollar(t_min *tk, t_test *list);
int	dollar_found(t_word *tmp, int *i);
int	find_dollar(t_word *tmp, int *i);
void	check_dollar(t_min *tk, t_test *list);
#endif
