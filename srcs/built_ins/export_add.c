/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:48:26 by mehernan          #+#    #+#             */
/*   Updated: 2024/07/03 17:02:11 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "libft.h"

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

static int	is_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_plus(t_export *dt)
{
	int	len;

	len = strlen(dt->name);
	if (len > 0 && dt->name[len - 1] == '+')
	{
		dt->is_plus = 1;
		dt->name[len - 1] = '\0';
	}
}

static void	export_loop(t_env *env, char **args, t_export *dt)
{
	if (!is_name(dt->name))
	{
		printf("%s export: `%s\': not valid identifier\n", TERROR, args[dt->i]);
		dt->res = 1;
		free(dt->name);
		dt->name = NULL;
	}
	if (dt->name != NULL)
	{
		if (!env_find(env, dt->name, find_env))
			env_add_back(&env, new_env(dt->name, dt->value));
		else
		{
			dt->find = env_find(env, dt->name, find_env);
			change_env_value(dt);
		}
	}
	if (dt->value && ft_strlen(dt->value) == 0)
		free(dt->value);
	free(dt->name);
}

int	export_add(t_env *env, char **args)
{
	t_export	dt;

	dt.i = 1;
	dt.res = 0;
	dt.is_plus = 0;
	dt.find = NULL;
	while (args[dt.i] != NULL)
	{
		dt.name = ft_substr(args[dt.i], 0, ft_strcspn(args[dt.i], "="));
		if (!ft_strchr(args[dt.i], '=') || (ft_strchr(args[dt.i], '=')
				&& *(ft_strchr(args[dt.i], '=') + 1) == '\0'))
			dt.value = NULL;
		else
			dt.value = ft_substr(args[dt.i], (ft_strlen(dt.name) + 1),
					0xFFFFFFF);
		remove_plus(&dt);
		export_loop(env, args, &dt);
		dt.i++;
	}
	return (dt.res);
}
