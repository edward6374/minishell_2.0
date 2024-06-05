/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:39:50 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

void	check_heredoc(t_word *tmp_word, t_cmd *new)
{
	if (!new->hdoc)
	{
		new->hdoc = ft_calloc(1, sizeof(t_here_doc));
		if (!new->hdoc)
			exit_error(g_error_array[MALLOC], MALLOC);
		new->hdoc->stop = ft_strdup(tmp_word->next->str);
		if (!new->hdoc->stop)
			exit_error(g_error_array[MALLOC], MALLOC);
	}
	else
	{
		// close(new->hdoc->fd[0]);
		// close(new->hdoc->fd[1]);
		free(new->hdoc->stop);
		new->hdoc->stop = ft_strdup(tmp_word->next->str);
		if (!new->hdoc->stop)
			exit_error(g_error_array[MALLOC], MALLOC);
	}
	new->hdoc->yes = 1;
	new->hdoc->first = 1;
}

int	change_word(t_word *tmp, int i, int len, char *value)
{
	char	*new;
	char	*temp;

	new = ft_substr(tmp->str, 0, i - 1);
	if (!new)
		exit(1);
	temp = ft_strjoin(new, value);
	if (!temp)
		exit(1);
	free(new);
	new = ft_strjoin(temp, &tmp->str[i + len]);
	if (!new)
		exit(1);
	free(temp);
	free(tmp->str);
	tmp->str = new;
	return (ft_strlen(value) - 2);
}
