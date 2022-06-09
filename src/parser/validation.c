/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:41:47 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:46:46 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>
#include <stdlib.h>

/*
	Returns
	1 if error occured
	0 otherwise
*/
static int	validate_first_token(char *token)
{
	if (is_logical_operator(token) || ft_streq(token, "|"))
		return (1);
	return (0);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
static int	validate_token(char *token, char *next, int *group_ended)
{
	if (is_logical_operator(token) && \
		!(is_redir_operator(next) || ft_streq(next, "(") || !is_operator(next)))
		return (1);
	if (ft_streq(token, "(") && \
		!(is_redir_operator(next) || ft_streq(next, "(") || !is_operator(next)))
		return (1);
	if (ft_streq(token, ")") && \
		!(is_redir_operator(next) || ft_streq(next, ")")))
		return (1);
	if (ft_streq(token, "|") && \
		!(is_redir_operator(next) || !is_operator(next)))
		return (1);
	if (is_redir_operator(token) && is_operator(next))
		return (1);
	if (ft_streq(token, ")"))
		*group_ended = 1;
	if (is_logical_operator(token))
		*group_ended = 0;
	if (*group_ended && !is_operator(next) && !is_redir_operator(token))
		return (1);
	return (0);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
static int	validate_last_token(char *token)
{
	if (ft_streq(token, ")"))
		return (0);
	if (is_operator(token))
		return (1);
	return (0);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
int	validate_quotes(char *token)
{
	int	*q;
	int	ret;

	if (ft_strlen(token) == 0)
		return (0);
	q = get_quoting(token);
	if (!q)
		return (1);
	ret = 0;
	if (q[ft_strlen(token) - 1] != 0)
		ret = 1;
	free(q);
	return (ret);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
int	validate(char **splitted)
{
	size_t	i;
	int		bal;
	int		group_ended;

	bal = 0;
	i = 0;
	if (validate_first_token(splitted[0]) == 1)
		return (unexp_token(splitted[0]));
	group_ended = 0;
	while (splitted[i] && splitted[i + 1])
	{
		bal = bal + ft_streq(splitted[i], "(") - ft_streq(splitted[i], ")");
		if (bal < 0)
			return (unexp_token(splitted[i]));
		if (validate_token(splitted[i], splitted[i + 1], &group_ended) == 1)
			return (unexp_token(splitted[i + 1]));
		++i;
	}
	bal = bal + ft_streq(splitted[i], "(") - ft_streq(splitted[i], ")");
	if (bal > 0 || validate_last_token(splitted[i]) == 1 || \
												validate_quotes(splitted[i]))
		return (unexp_eof());
	return (0);
}
