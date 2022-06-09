/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_brige.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:40:39 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <builtin.h>
#include <commands.h>
#include <libft.h>

int	check_builtin(t_cmd *cmd)
{
	char	*name;

	name = (cmd->argv)[0];
	if (ft_streq(name, "echo"))
		return (1);
	if (ft_streq(name, "exit"))
		return (2);
	if (ft_streq(name, "cd"))
		return (3);
	if (ft_streq(name, "env"))
		return (4);
	if (ft_streq(name, "export"))
		return (5);
	if (ft_streq(name, "unset"))
		return (6);
	if (ft_streq(name, "pwd"))
		return (7);
	return (0);
}

int	builtin_work_without_redir(t_cmd *cmd, int status)
{
	if (status == 1)
		return (minishell_echo(cmd->argv));
	if (status == 2)
		return (minishell_exit(cmd->argv));
	if (status == 3)
		return (minishell_cd(cmd->argv));
	if (status == 4)
		return (minishell_env(cmd->argv));
	if (status == 5)
		return (minishell_export(cmd->argv));
	if (status == 6)
		return (minishell_unset(cmd->argv));
	if (status == 7)
		return (minishell_pwd(cmd->argv));
	return (0);
}

int	simple_builtin_work(t_cmd **cmd, int status)
{
	int	fd[2];

	if (simple_redir_builtin((*cmd)->redirs, fd))
		return (set_exit_status(1));
	set_exit_status(builtin_work_without_redir(*cmd, status));
	if (put_fd_back(fd))
		return (set_exit_status(1));
	return (*get_exit_status());
}
