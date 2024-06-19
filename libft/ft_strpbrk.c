/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:47:20 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/19 12:48:44 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *str, const char *charset)
{
	const char	*char_ptr;

	while (*str != '\0')
	{
		char_ptr = charset;
		while (*char_ptr != '\0')
		{
			if (*char_ptr == *str)
				return ((char *)str);
			char_ptr++;
		}
		str++;
	}
	return (NULL);
}
