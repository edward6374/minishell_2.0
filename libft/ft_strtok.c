/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:47:30 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/19 12:48:46 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	char		*token_start;
	static char	*next_token;
	char		*token_end;

	if (str != NULL)
		next_token = str;
	else if (next_token == NULL)
		return (NULL);
	token_start = next_token;
	token_end = ft_strpbrk(token_start, delim);
	if (token_end != NULL)
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
		next_token = NULL;
	return (token_start);
}
