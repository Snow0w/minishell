/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:09 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:48:29 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

int	minishell_pwd(char **cmd)
{
	char	*str;

	(void) cmd;
	str = getcwd(NULL, 1);
	if (!str)
	{
		perror("minishell: pwd:");
		return (1);
	}
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	free(str);
	return (0);
}
