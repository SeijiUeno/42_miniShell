/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:19:15 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/07 16:28:09 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../shell.h"

/* Function prototypes */
int 	control_status(int status);
int	    filter_status(int status);
void	handle_signal_exec(int signum);
void	handle_signal(int signum);
void	prepare_signals(void);

#endif /* SIGNAL_H */
