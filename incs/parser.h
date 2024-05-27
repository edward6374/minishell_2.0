/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/05/27 10:16:20 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
typedef struct	s_word // lo usaremos para separar palabrras
{
	int				quote_after;
    char			*str;
    struct s_word	*prev;
    struct s_word	*next;
}	t_word;

typedef struct	s_test
{
    char			*str;
	t_word			*words;
	struct s_test	*prev;
    struct s_test	*next;
}	t_test;

void	put_list(t_test **list, char *div_str);
void	print_list(t_test **list);
void	dividing_words(t_test *list, char *div_str);//pot ser no cal
void	print_word(t_word **list, char *div_str, char *word, int *i);
void	end_word(t_word **list, char *word);
void	put_word_list(t_word **list, char *word);
void	print_word_list(t_word **list);
int		parser(t_min *tk, char *line);
void	check_dollar(t_min *tk, t_test *list);
int		change_word(t_word *tmp, int i, int len, char *value);
void	deleting(t_test *list);
char	*get_path(char *word);
int		do_open(t_test *node, t_cmd *new);
t_cmd	*get_command_list(t_min *tk, t_test *list);
t_test	*dividing_pipe(char *input, int i);
int	parser(t_min *tk, char *line);
int	check_syntax(char *line);
#endif
