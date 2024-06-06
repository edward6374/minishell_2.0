/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:34:31 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/31 18:54:49 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "signalm.h"

void	free_here_doc(t_here_doc *hd)
{
	t_hd_val	*tmp;
	t_hd_val	*next;

	tmp = hd->values;
	next = NULL;
	if (!tmp)
	{
		free(hd);
		return ;
	}
	if (tmp)
		next = hd->values->next;
	while (next)
	{
		free(tmp->stop);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	free(tmp->stop);
	free(tmp);
	free(hd);
}

void	close_here_doc(t_min *tk)
{
	t_cmd		*tmp;
	t_hd_val	*tmp_hd;

	tmp = tk->cmds;
	while (tmp)
	{
		if (tmp->hdoc->yes)
		{
			tmp_hd = tmp->hdoc->values;
			while (tmp_hd)
			{
				close(tmp_hd->fd[0]);
				close(tmp_hd->fd[1]);
				tmp_hd = tmp_hd->next;
			}
		}
		tmp = tmp->next;
	}
}

static void	run_loop(t_hd_val *tmp, char *line)
{
	set_signals(2);
	while (42)
	{
		line = readline("> ");
		if (!line || (line[0] != '\0' && !ft_strncmp(line, tmp->stop,
					ft_strlen(line))))
			break ;
		ft_putstr_fd(line, tmp->fd[1]);
		ft_putchar_fd('\n', tmp->fd[1]);
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	exit(0);
}

void	run_here_doc(t_cmd *cmd)
{
	int			status;
	char		*line;
	pid_t		pid;
	t_hd_val	*tmp;

	line = NULL;
	if (!cmd->hdoc->yes)
		return ;
	tmp = cmd->hdoc->values;
	while (tmp)
	{
		if (pipe(tmp->fd))
			exit(1);
		set_signals(3);
		pid = fork();
		if (pid == 0)
			run_loop(tmp, line);
		waitpid(pid, &status, 0);
		if (write(1, "", 1) == -1)
			exit(1);
		g_exit = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}
