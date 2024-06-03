/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:15 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/03 20:34:07 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "struct.h"
# include "execute.h"
# include "parser.h"
# include "readline/history.h"
# include "readline/readline.h"

/* ---			Take_env.c			--- */
int		take_env(t_min *tk, char *env[]);

/* ---			Utils.c				--- */
void	set_term(void);
int		d_key(t_min **tk);
int		exit_error(const char *str, int i);
int		end_program(char **line, int error);
char	*ft_find_path(char *env[]);

/* ---			Free_funcs.c			--- */
void	free_err_f(char **line);
int		free_pointer(void *pt, int out);
int		free_double_int(char **old, int i);
void	free_double_void(char **old);
char	**free_double_char(char **old, int i);

/* ---			Free_structs.c			--- */
int		free_env(t_env *first);
int		free_all(t_min *tk, int out);
int		free_parser(t_pipe *pipe, int out);
int		free_commands(t_cmd **first, int out);

/* ---			init_pwd.c			--- */
void	init_pwd(t_min *tk);

#endif
