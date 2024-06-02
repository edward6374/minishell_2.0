/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:46:09 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:39:50 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	change_word(t_word *tmp, int i, int len, char *value)
{
	char	*new;
	char	*temp;

	new = ft_substr(tmp->str, 0, i - 1);
	if (!new)
		exit(1);
	temp = ft_strjoin(new, value);
	if (!temp)
		exit(1);
	free(new);
	new = ft_strjoin(temp, &tmp->str[i + len]);
	if (!new)
		exit(1);
	free(temp);
	free(tmp->str);
	tmp->str = new;
	return (ft_strlen(value) - 2);
}
