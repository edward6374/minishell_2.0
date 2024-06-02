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

static char	*get_path(char *word)
{
	char	*path;

	if (word[0] != '/')
	{
		path = getcwd(NULL, 1024);
		path[ft_strlen(path)] = '/';
		path = ft_strjoin(path, word);
		printf("Path: %s\n", path);
		if (!path)
			exit(MALLOC);
	}
	else
	{
		path = ft_strdup(word);
		if (!path)
			exit(MALLOC);
	}
	return (path);
}

static int	check_file(char *path, char sign, t_cmd *new)
{
	int i;

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
	{
		i = access(path, R_OK);
		if (i == 0)
		{
			new->in_fd = open(path, O_RDONLY);
			if (!new->in_fd)
				exit(OPEN_FAILED);
			return (0);
		}
		else if (access(path, F_OK) == 0)
			return (FILE_NOT_READ);
		return (FILE_NOT_FOUND);
	}
}

int do_open(t_pipe *node, t_cmd *new)
{
	char	*path;
	char	sign;
	t_word	*tmp_word;

	tmp_word = node->words;
	while (tmp_word)
	{
		if (tmp_word->str[0] == '>' || tmp_word->str[0] == '<')
		{
			if (tmp_word->str[0] == '>' && tmp_word->str[1] == '>')
				sign = 'd';
			else if(tmp_word->str[0] == '<' && tmp_word->str[1] == '<')
			{
				new->hdoc = ft_calloc(1, sizeof(t_here_doc));
				new->hdoc->stop = ft_strdup(tmp_word->next->str);
				new->hdoc->yes = 1;
				new->hdoc->first = 1;
			}
			else
				sign = tmp_word->str[0];
			path = get_path(tmp_word->next->str);
			new->ok = check_file(path, sign, new);
			if (new->ok != 0)
			{
				new->err_f = ft_strdup(tmp_word->next->str);
				if(!new->err_f)
					exit(MALLOC);
				return (1);
			}
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
