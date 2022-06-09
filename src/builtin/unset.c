/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:09 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:48:12 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <builtin.h>
#include <libft.h>

static void	delete_from_list(char *word, int *exit_status)
{
	int	iter_exit_status;

	iter_exit_status = 0;
	check_spelling(word, ft_strlen(word), &iter_exit_status, 0);
	if (iter_exit_status)
	{
		*exit_status = 1;
		return ;
	}
	delete_vlist(get_vlist(), word);
}

int	minishell_unset(char **cmd)
{
	int		exit_status;
	size_t	i;

	if (!(cmd[1]))
		return (0);
	exit_status = 0;
	i = 1;
	while (cmd[i])
	{
		delete_from_list(cmd[i], &exit_status);
		i++;
	}
	return (exit_status);
}
