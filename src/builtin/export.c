/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:08 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:48:12 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <commands.h>
#include <variables.h>
#include <libft.h>
#include <builtin.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	export_without_param(void)
{
	t_vlist	*env;
	char	*str;

	env = *get_vlist();
	while (env)
	{
		str = get_variable(env->name);
		if (!str)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("\n", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\"\n", 1);
			free(str);
		}
		env = env->next;
	}
	return (0);
}

static int	export_without_string(char *word)
{
	char	*name;

	name = ft_strdup(word);
	if (!name)
		return (1);
	set_variable(name, NULL);
	return (0);
}

static int	export_with_string(char *word, size_t eq)
{
	char	*name;
	char	*value;

	name = malloc(sizeof(char) * (eq + 1));
	if (!name)
		return (1);
	ft_strlcpy(name, word, eq + 1);
	value = ft_strdup(word + eq + 1);
	if (!value)
	{
		free(name);
		return (1);
	}
	set_variable(name, value);
	return (0);
}

static int	add_to_vlist(char *word, int *exit_status)
{
	size_t	i;
	int		flag;
	int		iter_exit_status;

	i = 0;
	flag = 0;
	iter_exit_status = 0;
	while (word[i] && word[i] != '=')
		i++;
	if (!(word[i]))
		flag = 1;
	if (flag)
		check_spelling(word, ft_strlen(word), &iter_exit_status, 1);
	else
		check_spelling(word, i, &iter_exit_status, 1);
	if (iter_exit_status)
		*exit_status = 1;
	if (iter_exit_status)
		return (0);
	if (flag)
		return (export_without_string(word));
	return (export_with_string(word, i));
}

int	minishell_export(char **cmd)
{
	int		exit_status;
	size_t	i;
	int		flag;

	if (!cmd[1])
		return (export_without_param());
	exit_status = 0;
	i = 1;
	flag = 0;
	while (cmd[i] && !flag)
	{
		flag = add_to_vlist(cmd[i], &exit_status);
		i++;
	}
	if (flag)
		return (std_func_err());
	return (exit_status);
}
