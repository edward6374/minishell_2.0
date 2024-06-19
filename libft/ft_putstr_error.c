/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:33:17 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/19 12:33:19 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_error(const char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	else
	{
		write (2, s, ft_strlen(s));
		exit (EXIT_FAILURE);
	}
}
