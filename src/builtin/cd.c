/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:01 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:48:57 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*cd_to_home(void)
{
	char	*home_path;

	home_path = get_variable("HOME");
	if (!home_path)
		write(2, "minishell: cd: HOME not set\n", 28);
	return (home_path);
}

int	err_get_cwd(char *str)
{
	perror("minishell: cd:");
	free(str);
	return (1);
}

int	err_ch_dir(char *str, char *buf)
{
	perror("minishell: cd:");
	free(str);
	free(buf);
	return (1);
}

static int	set_cwd_var(char *old_pwd, char *new_pwd)
{
	set_variable("OLD_PWD", old_pwd);
	set_variable("PWD", new_pwd);
	return (0);
}

int	minishell_cd(char **cmd)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*str;

	if (cmd[1])
		str = ft_strndup(cmd[1], ft_strlen(cmd[1]) + 1);
	if (!cmd[1])
		str = cd_to_home();
	if (!str)
		return (1);
	else if (!(*str))
	{
		free(str);
		return (0);
	}
	old_pwd = getcwd(NULL, 1);
	if (!old_pwd)
		return (err_get_cwd(str));
	if (chdir(str) == -1)
		return (err_ch_dir(str, old_pwd));
	free(str);
	new_pwd = getcwd(NULL, 1);
	if (!new_pwd)
		return (err_get_cwd(old_pwd));
	return (set_cwd_var(old_pwd, new_pwd));
}
