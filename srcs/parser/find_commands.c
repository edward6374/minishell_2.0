/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:51:04 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:42:15 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

static int	access_cmd(char *str, t_cmd *new, char *tmp)
{
	if (tmp)
		new->cmd = ft_strjoin(tmp, &str[1]);
	else
		new->cmd = ft_strdup(str);
	if (access(new->cmd, X_OK) == 0)
		return (0);
	else if (access(new->cmd, F_OK) == 0)
	{
		if (tmp)
		{
			free(new->cmd);
			new->cmd = ft_strdup(&str[2]);
		}
		return (CMD_FOUND_NOT_EX);
	}
	if (tmp)
	{
		free(new->cmd);
		new->cmd = ft_strdup(&str[2]);
	}
	return (CMD_NOT_FOUND);
}

void	find_command(t_min *tk, t_cmd *new, t_word *tmp_words)
{
	char	*tmp;

	if (is_builtin(tmp_words->str))
		new->cmd = ft_strdup(tmp_words->str);
	else if (tmp_words->str[0] == '/')
		new->ok = access_cmd(tmp_words->str, new, NULL);
	else if (tmp_words->str[0] == '.' && tmp_words->str[1] == '/')
	{
		tmp = getcwd(NULL, 0);
		new->ok = access_cmd(tmp_words->str, new, tmp);
		free(tmp);
	}
	else
		new->ok = get_cmd_path(tk, new, tmp_words->str);
	if (!new->cmd)
		exit_error(g_error_array[MALLOC], MALLOC);
}
