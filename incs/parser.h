/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/02 17:46:20 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//			CHANGE_NODE			//
t_hd_val	*get_last_hd(t_cmd *cmd);
void		check_heredoc(t_word *tmp_word, t_cmd *new);
int			change_word(t_word *tmp, int i, int len, char *value);

//			CHECKER			//
int			check_syntax(char *line);

//			DELETE_QUOTES			//
void		deleting(t_pipe *list);

//			EXPAND_VARIABLE			//
void		check_dollar(t_min *tk, t_pipe *list);

//			LIST_COMMAND_UTILS			//
void		take_args(t_word *tmp_words, t_cmd *new);
int			check_path(char **split, char *word, t_cmd *new, int i);
int			take_path_env(t_env **tmp, t_min *tk, t_cmd *new, char *word);

//			LIST_COMMANDS			//
t_cmd		*get_command_list(t_min *tk, t_pipe *list);

//			LIST_WORD_DETECTOR			//
void		put_word_list(t_word **list, char *word);

//			OPEN_FILE			//
int			do_open(t_pipe *node, t_cmd *new);

//			PARSER			//
int			parser(t_min *tk, char *line);

//			PIPE_SEPARATION			//
t_pipe		*dividing_pipe(char *input, int i);
// void	print_list(t_pipe **list);

//			WORD_DETECTOR			//
void		dividing_words(t_pipe *list, char *div_str);

#endif
