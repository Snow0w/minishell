/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:08 by kirill            #+#    #+#             */
/*   Updated: 2022/05/26 13:51:35 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>

static int	check_n_flag(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	if (*cmd != '-')
		return (0);
	i = 1;
	while (cmd[i] == 'n')
		i++;
	if (cmd[i] != '\0')
		return (0);
	return (1);
}

int	minishell_echo(char	**cmd)
{
	int	i;
	int	mode;

	i = 1;
	mode = 0;
	if (check_n_flag(cmd[1]))
	{
		mode = 1;
		i = 2;
	}
	while (check_n_flag(cmd[i]))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!mode)
		ft_putstr_fd("\n", 1);
	return (0);
}
