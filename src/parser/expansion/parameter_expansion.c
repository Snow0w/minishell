/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 08:52:17 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:58:55 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <commands.h>
#include <libft.h>

static t_word	*process_text(const t_word *word, t_word *new, size_t *i)
{
	size_t	len;
	char	*s;

	len = calc_len_until_param(word, *i);
	s = ft_strndup(&word->s[*i], len + 1);
	if (!s)
		return (free_word(new));
	new = append_str(new, s, &word->q[*i]);
	free(s);
	*i += len;
	return (new);
}

static char	*get_param_value(const t_word *word, size_t i)
{
	size_t	len;
	char	*name;
	char	*ans;

	len = param_len(word, i);
	name = ft_strndup(&word->s[i + 1], len);
	if (!name)
		return (NULL);
	if (ft_streq(name, "?"))
		ans = ft_itoa(*get_exit_status());
	else
		ans = get_variable(name);
	free(name);
	return (ans);
}

static t_word	*process_param(const t_word *word, t_word *new, size_t *i)
{
	size_t	len;
	char	*var;
	int		*q;
	size_t	j;

	var = get_param_value(word, *i);
	if (!var)
		return (NULL);
	len = ft_strlen(var);
	q = malloc(sizeof(*q) * len);
	if (!q)
		return (perror_and_null());
	j = 0;
	while (j < len)
		q[j++] = word->q[*i];
	new = append_str(new, var, q);
	free(q);
	*i += param_len(word, *i);
	free(var);
	return (new);
}

/*
	Returns
	-1 if error occured
	0 if expansion did not occured
	1 if expansion occured
*/
int	param_exp(t_word **word)
{
	t_word	*new;
	int		ret;
	size_t	i;

	new = create_word(NULL);
	i = 0;
	ret = 0;
	while ((*word)->s[i])
	{
		if (param_len(*word, i) == 0)
			new = process_text(*word, new, &i);
		else
		{
			ret = 1;
			new = process_param(*word, new, &i);
		}
		if (!new)
		{
			ret = -1;
			break ;
		}
	}
	free_word(*word);
	*word = new;
	return (ret);
}
