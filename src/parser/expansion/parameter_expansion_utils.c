/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 07:58:34 by bgohan            #+#    #+#             */
/*   Updated: 2022/05/26 14:29:18 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

size_t	param_len(const t_word *word, size_t i)
{
	size_t	ans;

	ans = 0;
	if (!word->s[i])
		return (0);
	if (word->q[i] == 1)
		return (0);
	if (word->s[i + ans++] != '$')
		return (0);
	if (word->s[i + ans] == '?')
		return (2);
	if (!ft_isalpha(word->s[i + ans]) && word->s[i + ans] != '_')
		return (0);
	++ans;
	while (ft_isalnum(word->s[i + ans]) || word->s[i + ans] == '_')
		++ans;
	return (ans);
}

size_t	calc_len_until_param(const t_word *word, size_t i)
{
	size_t	ans;

	ans = 0;
	while (word->s[i + ans] && param_len(word, i + ans) == 0)
		++ans;
	return (ans);
}
