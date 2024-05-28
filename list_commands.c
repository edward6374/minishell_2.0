/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:25:39 by mehernan          #+#    #+#             */
/*   Updated: 2024/05/28 18:59:34 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "parser.h"
#include "struct.h"

int	get_cmd_path(t_min *tk, t_cmd *new, char *word)
{
	int		i;
	int		out;
	char	**split;
	t_env	*tmp;

	if (take_path_env(&tmp, tk, new, word))
		return (CMD_NOT_FOUND);
	split = ft_split(tmp->value, ':');
	if (!split)
		exit(MALLOC);
	i = 0;
	while (split[i])
	{
		out = check_path(split, word, new, i);
		if (out == CMD_FOUND_NOT_EX)
			return (out);
		else if (!out)
			return (0);
		i++;
	}
	ft_free_dptr(split);
	new->cmd = ft_strdup(word);
	return (CMD_NOT_FOUND);
}

static void	put_args(t_cmd *new, t_test *node)
{
	int		n;
	t_word	*tmp_words;

	n = 0;
	tmp_words = node->words;
	while (tmp_words)
	{
		if (tmp_words->str[0] != '<' && tmp_words->str[0] != '>')
			n++;
		else
			tmp_words = tmp_words->next;
		tmp_words = tmp_words->next;
	}
	new->args = ft_calloc(n + 1, sizeof(char *));
	if (!new->args)
		exit(MALLOC);
	tmp_words = node->words;
	take_args(tmp_words, new);
}

static void	command_inside(t_min *tk, t_cmd *new, t_test *node)
{
	t_word	*tmp_words;

	tmp_words = node->words;
	while (tmp_words)
	{
		if ((tmp_words->prev == NULL && tmp_words->str[0] != '<'
				&& tmp_words->str[0] != '>')
			|| (tmp_words->prev && tmp_words->prev->str[0] != '<'
				&& tmp_words->prev->str[0] != '>'))
		{
			new->ok = get_cmd_path(tk, new, tmp_words->str);
			break ;
		}
		tmp_words = tmp_words->next;
	}
	if (!new->ok)
		put_args(new, node);
}

static void	put_command_list(t_min *tk, t_cmd **list_cmd, t_test *node)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		exit(MALLOC);
	new->out_fd = 1;
	new->hdoc = ft_calloc(1, sizeof(t_here_doc));
	if (!new->hdoc)
		exit(MALLOC);
	do_open(node, new);
	if (new->ok == 0)
		command_inside(tk, new, node);
	if (!(*list_cmd))
		*list_cmd = new;
	else
	{
		tmp = *list_cmd;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->before = tmp;
		new->n = new->before->n + 1;
	}
}

t_cmd	*get_command_list(t_min *tk, t_test *list)
{
	t_test	*tmp;
	t_cmd	*list_cmd;

	list_cmd = NULL;
	tmp = list;
	while (tmp != NULL)
	{
		put_command_list(tk, &list_cmd, tmp);
		tmp = tmp->next;
	}
	return (list_cmd);
}
