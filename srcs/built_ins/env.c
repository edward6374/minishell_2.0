/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/17 17:40:00 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	change_env_value(t_export *dt)
{
	char	*tmp;

	if (dt->is_plus)
	{
		if (dt->find->value == NULL)
			dt->find->value = ft_strdup("");
		tmp = ft_strjoin(dt->find->value, dt->value);
		free(dt->find->value);
		free(dt->value);
		dt->find->value = tmp;
	}
	else
	{
		free(dt->find->value);
		dt->find->value = dt->value;
	}
}

int	find_env(char *s1, char *s2, int mode)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			if (!mode && !ft_isalnum(s2[i]))
				break ;
			else
				return (1);
		}
	}
	if (s1[i] == '=')
		return (0);
	return (1);
}

t_env	*env_find(t_env *env, void *data_ref, int (*cmp)(char *, char *, int))
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if ((*cmp)(curr->name, data_ref, 1) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_env(t_min *tk)
{
	t_env	*env;

	env = tk->env;
	while (env != NULL)
	{
		if (env->value)
			printf("%s%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
