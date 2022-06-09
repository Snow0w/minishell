/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:34 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <commands.h>

int	err_access_one(int access_value, char *cmd, char **envp)
{
	str_split_free(envp);
	return (access_value_ret(access_value, cmd));
}

int	err_execve_one(char *cmd, char **envp)
{
	str_split_free(envp);
	return (err_execve_ret(cmd));
}

int	err_malloc_env_free(char **envp)
{
	str_split_free(envp);
	return (std_func_err());
}

int	err_cmd_not_found(char **envp, char **spl, char *cmd)
{
	str_split_free(envp);
	str_split_free(spl);
	return (err_cmd_not_found_ret(cmd));
}

int	wrong_name_in_path(char **envp, char **spl, int pos)
{
	int	ret;

	str_split_free(envp);
	ret = access_value_ret(check_cmd_access(spl[pos]), spl[pos]);
	str_split_free(spl);
	return (ret);
}
