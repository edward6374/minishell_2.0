/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:47:54 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/30 10:29:30 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	loop_arguments(t_parser **list, t_parser **next, t_cmd *new, int k)
{
	new->args[k] = ft_strdup((*list)->word);
	if (!new->args[k])
		return (free_double_int(new->args, k));
	free((*list)->word);
	free(*list);
	*list = *next;
	if (*list)
		*next = (*list)->next;
	return (0);
}

int	add_arguments(t_parser **list, t_cmd *new)
{
	int			i;
	int			k;
	t_parser	*next;

	i = 0;
	k = -1;
	next = *list;
	while (next && ft_strncmp(next->word, "|", 2) && ++i)
		next = next->next;
	new->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return (MALLOC);
	next = (*list)->next;
	while (++k < i)
	{
		if (loop_arguments(list, &next, new, k))
			return (free_commands(&new, free_parser(*list, MALLOC)));
	}
	new->args[k] = NULL;
	if (*list && !ft_strncmp((*list)->word, "|", 2))
		(*list) = (*list)->next;
	return (0);
}

int	join_paths(char **tmp, char *env)
{
	int		err;
	char	*t1;
	char	*t2;

	t1 = ft_strjoin(env, "/");
	if (!t1)
		return (MALLOC + 1);
	t2 = ft_strjoin(t1, *tmp);
	if (!t2)
		return (free_pointer(t1, MALLOC + 1));
	err = check_access(t1, t2, 1);
	if (err)
		return (free_pointer(t2, err));
	free(*tmp);
	*tmp = t2;
	return (0);
}

int	rel_path_cmd(t_min **tk, char **tmp)
{
	int		i;
	int		err;
	char	**path;

	if (((*tmp)[0] == '.' && (*tmp)[1] == '/') || (*tmp)[0] == '\0')
		return (check_access(NULL, (*tmp), 1));
	path = path_env((*tk)->env);
	if (!path)
		return (join_paths(tmp, getcwd(NULL, 0)));
	i = -1;
	while (path[++i])
	{
		err = join_paths(tmp, path[i]);
		if (!err)
			break ;
		else if (err == CMD_NOT_FOUND)
			continue ;
		else
			return (err);
	}
	if (!path[i])
		return (CMD_NOT_FOUND);
	ft_free_dptr(path);
	return (0);
}

int	add_command(t_min **tk, t_parser **list, t_cmd *new)
{
	int		err;
	char	*tmp;

	err = 0;
	tmp = ft_strdup((*list)->word);
	if (!tmp)
		return (MALLOC);
	if (!is_builtin((*list)->word))
	{
		if (tmp[0] != '/')
			err = rel_path_cmd(tk, &tmp);
		else
			err = check_access(NULL, tmp, 1);
	}
	new->cmd = tmp;
	return (err);
}
