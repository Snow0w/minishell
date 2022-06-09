/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_commands_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:55 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <commands.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int	waiter(pid_t final_pid, int num)
{
	int		status;
	int		final_status;
	pid_t	ret;
	int		i;

	i = 0;
	final_status = 0;
	while (i < num)
	{
		ret = wait(&status);
		if (ret == -1)
			std_func_err();
		if (ret == final_pid)
			final_status = status;
		i++;
	}
	if (WIFSIGNALED(final_status))
		return (128 + WTERMSIG(final_status));
	return (WEXITSTATUS(final_status));
}

int	open_pipes_sev_com(int pipes[2][2], size_t i, size_t num)
{
	if (i % 2 && (i + 1 != num))
		if (pipe(pipes[1]) == -1)
			return (1);
	if (!(i % 2) && (i + 1 != num))
		if (pipe(pipes[0]) == -1)
			return (1);
	return (0);
}
