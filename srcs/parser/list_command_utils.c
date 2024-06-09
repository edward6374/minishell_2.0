/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:44:25 by vduchi            #+#    #+#             */
/*   Updated: 2024/05/28 18:58:54 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "g_error.h"

void	take_args(t_word *tmp_words, t_cmd *new)
{
	int	n;

	n = 0;
	while (tmp_words)
	{
		if (tmp_words->str[0] == '<' || tmp_words->str[0] == '>')
			tmp_words = tmp_words->next;
		else
		{
			new->args[n] = ft_strdup(tmp_words->str);
			if (!new->args)
				exit_error(g_error_array[0], MALLOC);
			n++;
		}
		tmp_words = tmp_words->next;
	}
}

static t_env	*find_path_var(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH=", 6) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	take_path_env(t_env **tmp, t_min *tk, t_cmd *new, char *word)
{
	*tmp = find_path_var(tk->env);
	if (!(*tmp))
	{
		new->cmd = ft_strdup(word);
		return (CMD_NOT_FOUND);
	}
	return (0);
}

static char	*take_full_path(char *pwd, char *str)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(pwd, "/");
	if (!tmp)
		exit_error(g_error_array[0], MALLOC);
	new = ft_strjoin(tmp, str);
	if (!new)
		exit_error(g_error_array[0], MALLOC);
	free(tmp);
	return (new);
}

int	check_path(char **split, char *word, t_cmd *new, int i)
{
	char	*path;

	path = take_full_path(split[i], word);
	if (access(path, X_OK) == 0)
	{
		ft_free_dptr(split);
		new->cmd = path;
		return (0);
	}
	else if (access(path, F_OK) == 0)
	{
		ft_free_dptr(split);
		free(path);
		new->cmd = ft_strdup(word);
		return (CMD_FOUND_NOT_EX);
	}
	free(path);
	return (1);
}
