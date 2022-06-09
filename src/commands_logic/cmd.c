/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:22 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>
#include <commands.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int	build_path(char **spl_path, char *cmd)
{
	int		len_path;
	int		i;
	char	*var;

	i = 0;
	while (spl_path[i])
	{
		len_path = ft_strlen(spl_path[i]);
		var = malloc(sizeof(char) * (2 + len_path + ft_strlen(cmd)));
		if (!var)
			return (1);
		ft_strlcpy(var, spl_path[i], len_path + 1);
		ft_strlcat(var, "/", len_path + 2);
		ft_strlcat(var, cmd, len_path + ft_strlen(cmd) + 2);
		free(spl_path[i]);
		spl_path[i] = var;
		i++;
	}
	return (0);
}

char	**get_path(char **envp, char *cmd)
{
	int		i;
	char	**spl_path;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5))
		i++;
	spl_path = ft_split(envp[i] + 5, ':');
	if (!spl_path)
		return (NULL);
	if (build_path(spl_path, cmd))
		return (str_split_free(spl_path));
	return (spl_path);
}

int	full_path_work(char **spl_cmd, char **envp)
{
	int	access_value;

	access_value = check_cmd_access(spl_cmd[0]);
	if (access_value)
		exit(err_access_one(access_value, spl_cmd[0], envp));
	if (execve(spl_cmd[0], spl_cmd, envp) == -1)
		exit(err_execve_one(spl_cmd[0], envp));
	return (0);
}

int	full_check_access(char **spl_path, int *flag)
{
	struct stat	statbuf;
	int			i;
	int			mark;

	i = 0;
	mark = -1;
	while (spl_path[i])
	{
		if (!access(spl_path[i], F_OK))
		{
			mark = i;
			stat(spl_path[i], &statbuf);
			if (!(S_ISDIR(statbuf.st_mode)))
				if (!access(spl_path[i], X_OK))
					return (i);
		}
		i++;
	}
	if (mark == -1)
		return (-1);
	*flag = 1;
	return (mark);
}

int	call_cmd(char **spl_cmd)
{
	char	**spl_path;
	char	**envp;
	int		flag;
	int		pos;

	envp = get_envp_for_child_process();
	if (ft_streq(spl_cmd[0], ".") || ft_streq(spl_cmd[0], ".."))
		return (err_cmd_not_found_ret(spl_cmd[0]));
	if (ft_strchr(spl_cmd[0], 47) || is_var_plus_value_exist("PATH"))
		return (full_path_work(spl_cmd, envp));
	spl_path = get_path(envp, spl_cmd[0]);
	if (!spl_path)
		exit(err_malloc_env_free(envp));
	flag = 0;
	pos = full_check_access(spl_path, &flag);
	if (pos == -1)
		exit(err_cmd_not_found(envp, spl_path, spl_cmd[0]));
	if (flag)
		exit(wrong_name_in_path(envp, spl_path, pos));
	if (execve(spl_path[pos], spl_cmd, envp) == -1)
	{
		str_split_free(spl_path);
		exit(err_execve_one(spl_cmd[0], envp));
	}
	return (0);
}
