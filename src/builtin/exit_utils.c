/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:37:10 by omanie            #+#    #+#             */
/*   Updated: 2022/05/25 15:37:12 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <parser.h>
#include <libft.h>
#include <builtin.h>

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (c >= 9 && c <= 13);
}

static int	ft_skip(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	if (str[i] == '+')
		++i;
	else if (str[i] == '-')
	{
		*sign = -1;
		++i;
	}
	return (i);
}

static int	check_digit(char *str, int i, int *flag)
{
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			*flag = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

long	calc_status_minishell_exit(char *str, int *flag)
{
	int	ans;
	int	i;
	int	sign;

	ans = 0;
	sign = 1;
	i = ft_skip(str, &sign);
	if (check_digit(str, i, flag))
		return (1);
	ans = ft_atoi(str);
	if (ft_strncmp(str + i, "9223372036854775807", 20) > 0 && sign == 1)
		*flag = 1;
	if (ft_strncmp(str + i, "9223372036854775808", 20) > 0 && sign == -1)
		*flag = 1;
	return (ans % 256);
}
