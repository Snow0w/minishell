/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:55 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <builtin.h>
#include <errno.h>
#include <string.h>
#include <commands.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>

int	prev_dup(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	if (fd[0] == -1)
		return (std_func_err());
	fd[1] = dup(STDOUT_FILENO);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (std_func_err());
	}
	return (0);
}

int	err_open_ret(char *spl)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(spl, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	put_fd_back(int *fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("Fatal STDIN_FILENO dup2 error");
		return (1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("Fatal STDOUT_FILENO dup2 error");
		return (1);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	simple_redir_builtin(t_redir **redirs, int *fd)
{
	int	flag;

	if (prev_dup(fd))
		return (1);
	flag = main_redir(redirs, fd);
	if (flag)
	{
		put_fd_back(fd);
		return (1);
	}
	return (0);
}

int	main_redir(t_redir **redirs, int *fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (redirs[i] && !flag)
	{
		if ((redirs[i])->type == INPUT)
			flag = simple_input_redir((redirs[i])->arg);
		if ((redirs[i])->type == OUTPUT)
			flag = simple_output_redir((redirs[i])->arg);
		if ((redirs[i])->type == HERE_DOC)
			flag = simple_here_doc_redir((redirs[i])->arg, fd);
		if ((redirs[i])->type == APPEND)
			flag = simple_append_redir((redirs[i])->arg);
		i++;
	}
	if (flag)
		return (1);
	return (0);
}
