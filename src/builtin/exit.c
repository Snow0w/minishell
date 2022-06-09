/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:35:53 by omanie            #+#    #+#             */
/*   Updated: 2022/06/02 12:38:41 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <parser.h>
#include <libft.h>
#include <builtin.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	many_arg_exit(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

static int	wrong_exit(char *str)
{
	ft_putstr_fd("exit\n", 1);
	destroy_vlist();
	rl_clear_history();
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_tree(*tree_to_exit_delete());
	return (255);
}

int	minishell_exit(char **cmd)
{
	long	status;
	int		flag;

	if (!(cmd[1]))
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	flag = 0;
	status = calc_status_minishell_exit(cmd[1], &flag);
	if (flag)
		exit(wrong_exit(cmd[1]));
	if (cmd[1])
		if (cmd[2])
			return (many_arg_exit());
	ft_putstr_fd("exit\n", 1);
	destroy_vlist();
	rl_clear_history();
	free_tree(*tree_to_exit_delete());
	exit(status);
}
