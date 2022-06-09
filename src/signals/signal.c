/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:42:41 by kirill            #+#    #+#             */
/*   Updated: 2022/06/01 19:18:43 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <signals.h>

int	signals_init(void)
{
	struct sigaction	sig_quit_act;
	struct sigaction	sig_int_act;

	sig_quit_act.sa_handler = SIG_IGN;
	sig_int_act.sa_handler = sig_int_handler;
	sig_quit_act.sa_flags = SA_RESTART;
	sig_int_act.sa_flags = SA_RESTART;
	sig_quit_act.sa_mask = 0;
	sig_int_act.sa_mask = 0;
	sigaction(SIGQUIT, &sig_quit_act, NULL);
	sigaction(SIGINT, &sig_int_act, NULL);
	return (0);
}

int	signals_default(void)
{
	struct sigaction	sig_quit_act;
	struct sigaction	sig_int_act;

	sig_quit_act.sa_handler = sig_dfl_quit_handler;
	sig_int_act.sa_handler = sig_dfl_int_handler;
	sig_quit_act.sa_flags = SA_RESTART;
	sig_int_act.sa_flags = SA_RESTART;
	sig_quit_act.sa_mask = 0;
	sig_int_act.sa_mask = 0;
	sigaction(SIGQUIT, &sig_quit_act, NULL);
	sigaction(SIGINT, &sig_int_act, NULL);
	return (0);
}

int	signals_ignore(void)
{
	struct sigaction	sig_quit_act;
	struct sigaction	sig_int_act;

	sig_quit_act.sa_handler = SIG_IGN;
	sig_int_act.sa_handler = SIG_IGN;
	sig_quit_act.sa_flags = SA_RESTART;
	sig_int_act.sa_flags = SA_RESTART;
	sig_quit_act.sa_mask = 0;
	sig_int_act.sa_mask = 0;
	sigaction(SIGQUIT, &sig_quit_act, NULL);
	sigaction(SIGINT, &sig_int_act, NULL);
	return (0);
}

int	signals_redir(void)
{
	struct sigaction	sig_int_act;
	struct sigaction	sig_quit_act;

	sig_int_act.sa_handler = sig_redir_handler;
	sig_quit_act.sa_handler = SIG_IGN;
	sig_quit_act.sa_flags = SA_RESTART;
	sig_int_act.sa_flags = SA_RESTART;
	sig_quit_act.sa_mask = 0;
	sig_int_act.sa_mask = 0;
	sigaction(SIGQUIT, &sig_quit_act, NULL);
	sigaction(SIGINT, &sig_int_act, NULL);
	return (0);
}
