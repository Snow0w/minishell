/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
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
#include <stdlib.h>
#include <signals.h>
#include <sys/wait.h>

int	group_start(t_cmdtree *tree)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	int		flag;

	pid = fork();
	if (pid == -1)
		return (std_func_err());
	if (pid == 0)
	{
		flag = 0;
		if (prev_dup(fd))
			exit(1);
		if (expand_redirs(tree->arg2))
			exit(1);
		flag = main_redir(tree->arg2, fd);
		if (flag)
			exit(1);
		exit(start(tree->arg1));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (std_func_err());
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	start(t_cmdtree *tree)
{
	if (tree->type == PIPELINE)
		return (pipeline_work(tree));
	if (tree->type == OR)
		start(tree->arg1);
	if (tree->type == OR && *get_exit_status())
		start(tree->arg2);
	if (tree->type == AND)
		start(tree->arg1);
	if (tree->type == AND && !*get_exit_status())
		start(tree->arg2);
	if (tree->type == GROUP)
	{
		signals_ignore();
		set_exit_status(group_start(tree));
	}
	return (0);
}
