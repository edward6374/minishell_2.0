/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:10:16 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/31 18:35:35 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "execute.h"
#include "minishell.h"
#include "g_error.h"

static int	more_checks(char *str, char **last, char *tmp, int *j)
{
	char	*sub;

	if (ft_strchr(str + *j, '$'))
	{
		sub = ft_substr(str, *j, ft_strchr(str + *j, '$') - &str[*j]);
		tmp = ft_strjoin(*last, sub);
		if (!tmp)
			exit_error(g_error_array[0], MALLOC);
		free(sub);
		free(*last);
		*last = tmp;
		*j += ft_strchr(str + *j, '$') - &str[*j] - 1;
	}
	else if (!ft_strchr(str + *j, '$'))
	{
		sub = ft_substr(str, *j, ft_strlen(str) - *j);
		tmp = ft_strjoin(*last, sub);
		if (!tmp)
			exit_error(g_error_array[0], MALLOC);
		free(sub);
		free(*last);
		*last = tmp;
		return (1);
	}
	return (0);
}

void	take_more_exit(char **str, int i)
{
	int		j;
	char	*tmp;
	char	*new;
	char	*last;

	j = 1;
	last = ft_itoa(g_exit);
	while (str[i][++j])
	{
		if (str[i][j] == '$' && str[i][j + 1] == '?' && ++j)
		{
			new = ft_itoa(g_exit);
			tmp = last;
			last = ft_strjoin(last, new);
			if (!last)
				exit_error(g_error_array[0], MALLOC);
			free(new);
			free(tmp);
		}
		else if (more_checks(str[i], &last, tmp, &j))
			break ;
	}
	free(str[i]);
	str[i] = ft_strdup(last);
	free(last);
}

void	end_exec(t_min *tk, pid_t *child_pid)
{
	int		final;
	int		status;
	int		finished;
	pid_t	process;

	final = 0;
	status = 0;
	finished = 0;
	while (finished < tk->num_cmds)
	{
		process = waitpid(-1, &status, 0);
		if (process == child_pid[tk->num_cmds - 1])
			final = status;
		finished++;
	}
	if (child_pid)
		free(child_pid);
	if (WEXITSTATUS(final))
		g_exit = WEXITSTATUS(final);
}

int	run_builtin(t_min *tk, t_cmd *tmp)
{
	if (!ft_strncmp("echo", tmp->cmd, 5))
		return (ft_echo(tmp->args, 1));
	else if (!ft_strncmp("cd", tmp->cmd, 3))
		return (ft_cd(tmp->args, tk));
	else if (!ft_strncmp("pwd", tmp->cmd, 4))
		return (ft_pwd());
	else if (!ft_strncmp("export", tmp->cmd, 7))
		return (ft_export(tk, tmp));
	else if (!ft_strncmp("unset", tmp->cmd, 6))
		return (ft_unset(tk, tmp));
	else if (!ft_strncmp("env", tmp->cmd, 4))
		return (ft_env(tk));
	return (ft_exit(tmp));
}

char	**take_double(t_min *tk, t_env *first)
{
	int		i;
	t_env	*tmp;
	char	**env;

	tmp = first;
	i = count_double(first);
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		exit_error(g_error_array[0], MALLOC);
	i = 0;
	while (tmp)
	{
		if (!tmp->value)
			env[i++] = ft_strjoin(tmp->name, "");
		else
			env[i++] = ft_strjoin(tmp->name, tmp->value);
		if (!env[i - 1])
			exit_error(g_error_array[0], MALLOC);
		tmp = tmp->next;
	}
	env[i] = NULL;
	if (tk->pt_env)
		free_double_void(tk->pt_env);
	tk->pt_env = env;
	return (env);
}
