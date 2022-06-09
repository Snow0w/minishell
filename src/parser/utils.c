/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:01:08 by bgohan            #+#    #+#             */
/*   Updated: 2022/04/27 20:23:51 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

int	is_logical_operator(const char *token)
{
	return (ft_streq(token, "||") || ft_streq(token, "&&"));
}

int	is_redir_operator(const char *token)
{
	return (ft_streq(token, ">>") || ft_streq(token, "<<") || \
			ft_streq(token, "<") || ft_streq(token, ">"));
}

int	is_control_operator(const char *token)
{
	return (ft_streq(token, "||") || ft_streq(token, "&&") || \
			ft_streq(token, "(") || ft_streq(token, ")") || \
			ft_streq(token, "|"));
}

int	is_operator(const char *token)
{
	return (is_control_operator(token) || is_redir_operator(token));
}
