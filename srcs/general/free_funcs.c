/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/19 12:49:36 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_pt(void **pt, int out)
{
	if (*pt)
		free(*pt);
	*pt = NULL;
	return (out);
}

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

void	free_one_cmd(t_cmd *tmp)
{
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->err_f)
		free(tmp->err_f);
	if (tmp->args)
		free_double_void(tmp->args);
	if (tmp->hdoc)
		free_here_doc(tmp->hdoc);
	if (tmp->in_fd != 0)
		close(tmp->in_fd);
	if (tmp->out_fd != 1)
		close(tmp->out_fd);
}

void	free_double_void(char **old)
{
	int	i;

	i = -1;
	if (!old)
		return ;
	while (old[++i])
		free(old[i]);
	free(old);
}
