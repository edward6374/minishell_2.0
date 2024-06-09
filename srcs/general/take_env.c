/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:02:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/31 18:35:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "g_error.h"

static t_env	*save_node(t_min *tk, t_env *new, t_env *old_tmp)
{
	t_env	*tmp;

	if (!old_tmp)
	{
		new->before = NULL;
		tk->env = new;
		tmp = tk->env;
	}
	else
	{
		old_tmp->next = new;
		old_tmp->next->before = old_tmp;
		tmp = old_tmp->next;
	}
	return (tmp);
}

// void	print_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("Name: %s\tValue: %s\n", tmp->name, tmp->value);
// 		tmp = tmp->next;
// 	}
// }

static void	check_oldpwd(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "OLDPWD", 6))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = env->next->next->next->next->next->next->next;
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			exit_error(g_error_array[0], MALLOC);
		new->name = ft_strdup("OLDPWD=");
		if (!new->name)
			exit_error(g_error_array[0], MALLOC);
		new->value = NULL;
		new->next = tmp->next;
		new->before = tmp;
		tmp->next = new;
	}
}

static void	take_value(char *env, t_env *new)
{
	if (!ft_strncmp(env, "SHLVL=", 6))
	{
		new->value = ft_itoa(ft_atoi(ft_strrchr(env, '=') + 1) + 1);
		if (!new->value)
			exit_error(g_error_array[0], MALLOC);
	}
	else if (!ft_strncmp(env, "OLDPWD", 6))
		new->value = NULL;
	else
	{
		new->value = ft_strdup(ft_strrchr(env, '=') + 1);
		if (!new->value)
			exit_error(g_error_array[0], MALLOC);
	}
}

static void	create_new_env(t_min *tk)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = -1;
	tmp = NULL;
	while (++i < 3)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			exit_error(g_error_array[0], MALLOC);
		if (i == 0)
			new->name = ft_strdup("OLDPWD=");
		else if (i == 1)
			new->name = ft_strdup("PWD=");
		else
			new->name = ft_strdup("SHLVL=");
		if (i == 1)
			new->value = getcwd(NULL, 0);
		else if (i == 2)
			new->value = ft_strdup("1");
		if (!new->name || ((i == 1 || i == 2) && !new->value))
			exit_error(g_error_array[0], MALLOC);
		tmp = save_node(tk, new, tmp);
	}
}

int	take_env(t_min *tk, char *env[])
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = -1;
	tmp = NULL;
	if (!env[0])
	{
		create_new_env(tk);
		return (0);
	}
	while (env[++i])
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			exit_error(g_error_array[0], MALLOC);
		new->name = ft_substr(env[i], 0, ft_strrchr(env[i], '=') - env[i] + 1);
		if (!new->name)
			exit_error(g_error_array[0], MALLOC);
		take_value(env[i], new);
		tmp = save_node(tk, new, tmp);
	}
	check_oldpwd(tk->env);
	return (0);
}
