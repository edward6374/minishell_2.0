/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:17:00 by nmota-bu          #+#    #+#             */
/*   Updated: 2024/06/02 17:27:05 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

extern unsigned char	g_exit;

# define NO_COLOR "\033[0;0m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define BLACK "\033[0;99m"
# define ORANGE "\033[38;5;209m"
# define BROWN "\033[38;2;184;143;29m"
# define DARK_GRAY "\033[38;5;234m"
# define MID_GRAY "\033[38;5;245m"
# define DARK_GREEN "\033[38;2;75;179;82m"
# define DARK_YELLOW "\033[38;5;143m"
# define PINK "\033[38;5;200m"

# define TERROR "\xF0\x9F\x98\xB1"

enum
{
	MALLOC = 1,
	SYNTAX,
	PIPE_FIRST,
	ONLY_REDIR,
	OPEN_FAILED,
	CMD_NOT_FOUND,
	CMD_FOUND_NOT_EX,
	FILE_NOT_FOUND,
	FILE_NOT_READ,
	FILE_NOT_WRITE,
	NONE,
};

typedef struct s_hd_val
{
	int				fd[2];
	char			*stop;
	struct s_hd_val	*prev;
	struct s_hd_val	*next;
}						t_hd_val;

typedef struct s_here_doc
{
	int			yes;
	int			first;
	t_hd_val	*values;
}						t_here_doc;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*before;
}						t_env;

typedef struct s_word
{
	int					quote_after;
	char				*str;
	struct s_word		*prev;
	struct s_word		*next;
}						t_word;

typedef struct s_pipe
{
	char				*str;
	t_word				*words;
	struct s_pipe		*prev;
	struct s_pipe		*next;
}						t_pipe;

// Redirections (referente a la palabra siguiente AQUI❌ > AQUI✅)
// < es la redireccion del input
// > es la redireccion del output
// << es la redireccion del heredoc💀
// >> es la redireccion del output en modo append

typedef struct s_cmd
{
	int					n;
	int					ok;
	int					in_fd;
	int					out_fd;
	char				*cmd;
	char				*err_f;
	char				**args;
	t_here_doc			*hdoc;
	struct s_cmd		*next;
	struct s_cmd		*before;
}						t_cmd;

typedef struct s_min
{
	int					num_cmds;
	char				**pt_env;
	t_env				*env;
	t_cmd				*cmds;
	char				*pwd;
	char				*oldpwd;
	char				*home;
}						t_min;

#endif
