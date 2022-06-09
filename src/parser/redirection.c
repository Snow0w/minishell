/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:31:08 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:54:37 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>

static t_redir	*create_redir(const char *type, const char *arg)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	if (!redir)
		return (perror_and_null());
	if (ft_streq(type, "<"))
		redir->type = INPUT;
	else if (ft_streq(type, ">"))
		redir->type = OUTPUT;
	else if (ft_streq(type, "<<"))
		redir->type = HERE_DOC;
	else
		redir->type = APPEND;
	redir->arg = ft_strdup(arg);
	if (!redir->arg)
		return (free_redir(redir));
	return (redir);
}

static size_t	count_redirs(char **splitted)
{
	size_t	ans;
	size_t	i;

	ans = 0;
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
		if (is_redir_operator(splitted[i++]))
			++ans;
	return (ans);
}

t_redir	**parse_redirs(char **splitted, size_t *len)
{
	t_redir	**redirs;
	size_t	i;

	redirs = malloc(sizeof(*redirs) * (count_redirs(splitted) + 1));
	if (!redirs)
		return (perror_and_null());
	i = 0;
	while (splitted[i] && !is_control_operator(splitted[i]))
	{
		redirs[i / 2] = create_redir(splitted[i], splitted[i + 1]);
		if (!redirs[i / 2])
			return (free_redirs(redirs));
		i += 2;
	}
	redirs[(i + 1) / 2] = 0;
	if (len)
		*len = i;
	return (redirs);
}
