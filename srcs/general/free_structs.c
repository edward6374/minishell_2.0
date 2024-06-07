/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2024/06/02 18:29:45 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_words(t_word *words)
{
	t_word	*word_tmp;
	t_word	*word_next;

	word_tmp = words;
	word_next = word_tmp->next;
	while (word_next)
	{
		free(word_tmp->str);
		free(word_tmp);
		word_tmp = word_next;
		word_next = word_tmp->next;
	}
	free(word_tmp->str);
	free(word_tmp);
}

int	free_parser(t_pipe *pipes, int out)
{
	t_pipe	*tmp;
	t_pipe	*next;

	tmp = pipes;
	next = pipes->next;
	while (next)
	{
		free_words(tmp->words);
		free(tmp->str);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	free_words(tmp->words);
	free(tmp->str);
	free(tmp);
	return (out);
}

int	free_env(t_env *first)
{
	t_env	*next;

	if (!first)
		return (MALLOC);
	next = first->next;
	while (next)
	{
		free(first->name);
		free(first->value);
		free(first);
		first = next;
		next = first->next;
	}
	if (first->name)
		free(first->name);
	if (first->value)
		free(first->value);
	free(first);
	return (MALLOC);
}

int	free_commands(t_cmd **first, int out)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *first;
	next = (*first)->next;
	while (next)
	{
		free_one_cmd(tmp);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	free_one_cmd(tmp);
	*first = NULL;
	return (free_pointer(tmp, out));
}

int	free_all(t_min *tk, int out)
{
	if (tk->cmds)
		free_commands(&tk->cmds, 0);
	if (tk->pt_env)
		free_double_void(tk->pt_env);
	tk->pt_env = NULL;
	if (tk->env)
		free_env(tk->env);
	if (tk->home)
		free(tk->home);
	if (tk->oldpwd)
		free(tk->oldpwd);
	if (tk->pwd)
		free(tk->pwd);
	free(tk);
	return (out);
}
