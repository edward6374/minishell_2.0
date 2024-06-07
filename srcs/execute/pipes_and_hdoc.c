/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:23:00 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/02 17:06:46 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	one_builtin(t_min *tk, t_cmd *tmp, pid_t *child_pid)
{
	int	out_tmp;

	out_tmp = -1;
	if (check_before_exec(&tmp, NULL, NULL) == -1)
		return ;
	if (tmp->out_fd != 1)
	{
		out_tmp = dup(1);
		dup2(tmp->out_fd, 1);
		close(tmp->out_fd);
	}
	take_exit_value(tmp);
	if (child_pid)
		free(child_pid);
	g_exit = run_builtin(tk, tmp);
	if (out_tmp != -1)
	{
		dup2(out_tmp, 1);
		close(out_tmp);
	}
}

void	close_all_pipes(t_min *tk, int *p, int fd)
{
	close_here_doc(tk);
	close(p[0]);
	close(p[1]);
	if (fd != -1)
		close(fd);
}

void	check_temp_fd(t_cmd *tmp, int *p, int *fd)
{
	if (tmp->n == 0 && tmp->next)
	{
		if (pipe(p))
			exit(1);
	}
	else if (tmp->n > 0 && tmp->next)
	{
		if (*fd != -1)
			close(*fd);
		*fd = dup(p[0]);
		close(p[0]);
		close(p[1]);
		if (pipe(p))
			exit(1);
	}
}

static void	redirect_out(t_cmd *tmp, int *p)
{
	if (tmp->out_fd != 1)
	{
		dup2(tmp->out_fd, 1);
		close(tmp->out_fd);
	}
	else if (tmp->out_fd == 1 && tmp->next)
		dup2(p[1], 1);
	close(p[1]);
}

void	redirect_pipes(t_cmd *tmp, int *p, int fd)
{
	if (tmp->in_fd != 0 && (!tmp->hdoc || (tmp->hdoc && !tmp->hdoc->first)))
	{
		dup2(tmp->in_fd, 0);
		close(tmp->in_fd);
	}
	else
	{
		if (tmp->hdoc && tmp->hdoc->first)
		{
			dup2(get_last_hd(tmp)->fd[0], 0);
			close(get_last_hd(tmp)->fd[0]);
			close(get_last_hd(tmp)->fd[1]);
		}
		else if (tmp->before && tmp->next)
		{
			dup2(fd, 0);
			close(fd);
		}
		else if (tmp->before && !tmp->next)
			dup2(p[0], 0);
	}
	close(p[0]);
	redirect_out(tmp, p);
}
