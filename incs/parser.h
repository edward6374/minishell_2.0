/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/05/28 19:02:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
typedef struct	s_word
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

void	print_list(t_test **list);
void	dividing_words(t_test *list, char *div_str);
void	put_word_list(t_word **list, char *word);
void	print_word_list(t_word **list);
void	check_dollar(t_min *tk, t_test *list);
int		change_word(t_word *tmp, int i, int len, char *value);
void	deleting(t_test *list);
t_cmd	*get_command_list(t_min *tk, t_test *list);
t_test	*dividing_pipe(char *input, int i);
int		check_syntax(char *line);

//			PARSER			//
int		parser(t_min *tk, char *line);

//			OPEN_FILE			//
int		do_open(t_test *node, t_cmd *new);

//			LIST_COMMAND_UTILS			//
void	take_args(t_word *tmp_words, t_cmd *new);
int		check_path(char **split, char *word, t_cmd *new, int i);
int		take_path_env(t_env **tmp, t_min *tk, t_cmd *new, char *word);

#endif
