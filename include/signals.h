/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:50:59 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:51:00 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

int		signals_default(void);
int		signals_init(void);
int		signals_ignore(void);
int		signals_redir(void);

void	sig_int_handler(int signum);
void	sig_redir_handler(int signum);
void	sig_dfl_int_handler(int signum);
void	sig_dfl_quit_handler(int signum);
#endif
