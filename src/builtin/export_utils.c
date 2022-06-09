/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:48:08 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:48:12 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <builtin.h>
#include <libft.h>
#include <stdlib.h>

void	check_spelling(char *word, size_t len, int *exit_status, int mode)
{
	size_t	i;

	if (!(ft_isalpha(*word) || *word == '_'))
		*exit_status = 1;
	i = 1;
	while (i < len && !(*exit_status))
	{
		if (!(ft_isalnum(word[i]) || word[i] == '_'))
			*exit_status = 1;
		i++;
	}
	if (*exit_status)
	{
		if (mode)
			ft_putstr_fd("minishell: export: '", 2);
		else
			ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}
