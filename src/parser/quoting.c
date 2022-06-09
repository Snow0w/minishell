/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:22:19 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:58:01 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

int	*get_quoting(const char *s)
{
	int		*quotes;
	int		quote;
	size_t	i;

	quotes = malloc(sizeof(*quotes) * ft_strlen(s));
	if (!quotes)
		return (perror_and_null());
	quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			if (quote != 2)
				quote = 1 - quote;
		if (s[i] == '"')
			if (quote != 1)
				quote = 2 - quote;
		quotes[i] = quote;
		++i;
	}
	return (quotes);
}

/*
	Returns
	1 if error occured
	0 otherwise
*/
int	check_quotes_match(const int *quotes, size_t n)
{
	if (n == 0)
		return (0);
	if (quotes[n - 1] == 1)
	{
		ft_putstr_fd(\
		"minishell: unexpected EOF while looking for matching `''\n", 2);
		return (1);
	}
	if (quotes[n - 1] == 2)
	{
		ft_putstr_fd(\
		"minishell: unexpected EOF while looking for matching `\'\n", 2);
		return (1);
	}
	return (0);
}
