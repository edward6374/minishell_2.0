/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:28:04 by mehernan          #+#    #+#             */
/*   Updated: 2024/06/19 12:31:39 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALM_H
# define SIGNALM_H

enum
{
	NORMAL,
	INTERACT,
	HEREDOC,
};

void	set_signals(int mode);
void	ign_signal(int signal);

#endif
