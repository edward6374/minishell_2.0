/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:09:52 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:36:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

static char	*get_path(char *word)
{
	char	*new;
	char	*path;
	char	tmp[2048];

	if (word[0] != '/')
	{
		if (getcwd(tmp, sizeof(tmp)) == NULL)
			exit(1);
		new = ft_strjoin(tmp, "/");
		if (!new)
			exit_error(g_error_array[0], MALLOC);
		path = ft_strjoin(new, word);
		if (!path)
			exit_error(g_error_array[0], MALLOC);
		free(new);
	}
	else
	{
		path = ft_strdup(word);
		if (!path)
			exit_error(g_error_array[0], MALLOC);
	}
	return (path);
}

static int	check_input(char *path, t_cmd *new)
{
	int	i;

	i = access(path, R_OK);
	if (i == 0)
	{
		new->in_fd = open(path, O_RDONLY);
		if (!new->in_fd)
			exit(OPEN_FAILED);
		if (new->hdoc && new->hdoc->first)
			new->hdoc->first = 0;
		return (0);
	}
	else if (access(path, F_OK) == 0)
		return (FILE_NOT_READ);
	return (FILE_NOT_FOUND);
}

static int	check_file(char *path, char sign, t_cmd *new)
{
	int	i;

	i = 0;
	if (sign == '>' || sign == 'd')
	{
		i = access(path, W_OK);
		if (i == 0 || access(path, F_OK) != 0)
		{
			if (sign == '>')
				new->out_fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else
				new->out_fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (!new->out_fd)
				exit(OPEN_FAILED);
			return (0);
		}
		return (FILE_NOT_WRITE);
	}
	else
		return (check_input(path, new));
}

static int	open_file(t_word *tmp_word, t_cmd *new, char sign)
{
	char	*path;

	if (tmp_word->str[0] == '<' && tmp_word->str[1] == '<')
		return (0);
	path = get_path(tmp_word->next->str);
	new->ok = check_file(path, sign, new);
	if (new->ok != 0)
	{
		free(path);
		new->err_f = ft_strdup(tmp_word->next->str);
		if (!new->err_f)
			exit_error(g_error_array[0], MALLOC);
		return (1);
	}
	free(path);
	return (0);
}

int	do_open(t_pipe *node, t_cmd *new)
{
	char	sign;
	t_word	*tmp_word;

	tmp_word = node->words;
	while (tmp_word)
	{
		if (tmp_word->str[0] == '>' || tmp_word->str[0] == '<')
		{
			sign = tmp_word->str[0];
			if (tmp_word->str[0] == '>' && tmp_word->str[1] == '>')
				sign = 'd';
			else if (tmp_word->str[0] == '<' && tmp_word->str[1] == '<')
				check_heredoc(tmp_word, new);
			if (open_file(tmp_word, new, sign) == 1)
				return (1);
		}
		tmp_word = tmp_word->next;
	}
	return (0);
}
// recuerda que si en cuelquier momento haces retur porque algo falla
// los ok deben ser
// 1 Malloc // no se mete en el ok📦
// 2 syntax //despues 📦
// 3 pipe_first //despues📦
// 4 only_redir //despues📦
// 5 open_faiiled //despues📦
// 6 cmd_not_found
// 7 cmd_found_not_ex
// 8 file_not_found
// 9 file_not_read
// 10 file_not_write
