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

void	take_more_exit(char **str, int i)
{
	int		j;
	char	*last;

	j = 1;
	last = ft_strdup(ft_itoa(g_exit));
	while (str[i][++j])
	{
		if (str[i][j] == '$' && str[i][j + 1] == '?' && ++j)
			last = ft_strjoin(last, ft_strdup(ft_itoa(g_exit)));
		else if (ft_strchr(str[i] + j, '$'))
		{
			last = ft_strjoin(last, ft_substr(str[i], j, ft_strchr(str[i] + j,
							'$') - &str[i][j]));
			j += ft_strchr(str[i] + j, '$') - &str[i][j] - 1;
		}
		else if (!ft_strchr(str[i] + j, '$'))
		{
			last = ft_strjoin(last, ft_substr(str[i], j, ft_strlen(str[i])
						- j));
			break ;
		}
	}
	free(str[i]);
	str[i] = ft_strdup(last);
	free(last);
}

void	end_exec(t_min *tk, pid_t *child_pid, char **env)
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
	free_double_void(env);
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

	i = 0;
	env = NULL;
	tmp = first;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	tmp = first;
	while (tmp)
	{
		if (!tmp->value)
			env[i++] = ft_strjoin(tmp->name, "");
		else
			env[i++] = ft_strjoin(tmp->name, tmp->value);
		tmp = tmp->next;
	}
	env[i] = NULL;
	tk->pt_env = env;
	return (env);
}
