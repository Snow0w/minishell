/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:42:58 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:43:03 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <signals.h>
#include <stdio.h>
#include <readline/readline.h>
#include <commands.h>
#include <unistd.h>
#include <stdlib.h>

void	sig_int_handler(int signum)
{
	(void) signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_redir_handler(int signum)
{
	(void) signum;
	write(2, "\n", 1);
	exit(1);
}

void	sig_dfl_int_handler(int signum)
{
	(void) signum;
	write(2, "\n", 1);
}

void	sig_dfl_quit_handler(int signum)
{
	(void) signum;
	write(2, "Quit: 3\n", 8);
}
