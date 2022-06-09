/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_work_utils.c                              :+:      :+:    :+:   */
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
#include <unistd.h>

size_t	get_cmd_number(t_cmd **cmd)
{
	size_t	num;

	if (*((*cmd)->argv) == NULL)
		return (0);
	num = 0;
	while (cmd[num])
	{
		num++;
	}
	return (num);
}

int	close_unused_pipes(int pipes[2][2], size_t i)
{
	if (i == 0)
		return (0);
	close(pipes[(i + 1) % 2][0]);
	close(pipes[(i + 1) % 2][1]);
	return (0);
}

int	err_pipe_open(int pipes[2][2], size_t i)
{
	std_func_err();
	if (i == 0)
		return (1);
	close(pipes[(i + 1) % 2][0]);
	close(pipes[(i + 1) % 2][1]);
	return (1);
}

int	err_fork_create(int pipes[2][2], size_t i)
{
	std_func_err();
	if (i == 0)
	{
		close(pipes[0][0]);
		close(pipes[0][1]);
		return (1);
	}
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	return (1);
}
