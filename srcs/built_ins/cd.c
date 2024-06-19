/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:27:06 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/19 12:53:02 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "g_error.h"
#include "built_ins.h"
#include "struct.h"

static int	change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("cd");
		g_exit = 1;
		return (1);
	}
}

static void	upgrade(t_min *tk, char *str, t_env *find)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	find = env_find(tk->env, str, find_env);
	if (find)
	{
		free(find->value);
		find->value = pwd;
	}
	if (!ft_strncmp("PWD", str, 4))
	{
		if (tk->pwd != NULL)
			free(tk->pwd);
		tk->pwd = ft_strdup(pwd);
		if (!tk->pwd)
			exit_error(g_error_array[MALLOC], MALLOC);
	}
	else
	{
		if (tk->oldpwd != NULL)
			free(tk->oldpwd);
		tk->oldpwd = ft_strdup(pwd);
		if (!tk->oldpwd)
			exit_error(g_error_array[MALLOC], MALLOC);
	}
}

static int	return_value(t_min *tk, char *path)
{
	int		res;
	t_env	*find;

	res = 0;
	find = NULL;
	upgrade(tk, "OLDPWD", find);
	if (!path)
		res = change_directory(tk->home);
	else
		res = change_directory(path);
	upgrade(tk, "PWD", find);
	return (res);
}

int	ft_cd(char **args, t_min *tk)
{
	char	*path;

	if (args[1] != NULL)
	{
		if (!ft_strncmp("~", args[1], 1))
			path = tk->home;
		else if (!ft_strncmp("-", args[1], 2))
		{
			if (!tk->oldpwd)
			{
				printf("%s cd: OLDPWD not set\n", TERROR);
				return (0);
			}
			path = tk->oldpwd;
		}
		else
			path = args[1];
		return (return_value(tk, path));
	}
	return (return_value(tk, NULL));
}
