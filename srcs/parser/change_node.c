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

t_hd_val	*get_last_hd(t_cmd *cmd)
{
	t_hd_val	*tmp;

	tmp = cmd->hdoc->values;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	add_heredoc_to_list(t_cmd *new, t_hd_val *new_val)
{
	t_hd_val	*tmp;

	tmp = new->hdoc->values;
	if (!tmp)
		new->hdoc->values = new_val;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_val;
		new_val->prev = tmp;
	}
}

void	check_heredoc(t_word *tmp_word, t_cmd *new)
{
	t_hd_val	*tmp;

	tmp = ft_calloc(1, sizeof(t_hd_val));
	if (!tmp)
		exit_error(g_error_array[0], MALLOC);
	tmp->stop = ft_strdup(tmp_word->next->str);
	if (!tmp->stop)
		exit_error(g_error_array[0], MALLOC);
	add_heredoc_to_list(new, tmp);
	new->hdoc->yes = 1;
	new->hdoc->first = 1;
}

int	change_word(t_word *tmp, int i, int len, char *value)
{
	char	*new;
	char	*temp;

	new = ft_substr(tmp->str, 0, i - 1);
	if (!new)
		exit_error(g_error_array[0], MALLOC);
	temp = ft_strjoin(new, value);
	if (!temp)
		exit_error(g_error_array[0], MALLOC);
	free(new);
	new = ft_strjoin(temp, &tmp->str[i + len]);
	if (!new)
		exit_error(g_error_array[0], MALLOC);
	free(temp);
	free(tmp->str);
	tmp->str = new;
	return (ft_strlen(value) - 2);
}
