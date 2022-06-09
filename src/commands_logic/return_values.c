/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:55 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int	err_execve_ret(char *spl)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(spl, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (127);
}

int	std_func_err(void)
{
	perror("minishell: ");
	return (1);
}

int	check_cmd_access(char *cmd)
{
	struct stat	statbuf;

	if (access(cmd, F_OK))
		return (2);
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		return (3);
	if (access(cmd, X_OK))
		return (4);
	return (0);
}

int	access_value_ret(int access_value, char *spl)
{
	if (access_value == 1)
		return (1);
	if (access_value == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(spl, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (access_value == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(spl, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (126);
	}
	if (access_value == 4)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(spl, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

int	err_cmd_not_found_ret(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	return (127);
}
