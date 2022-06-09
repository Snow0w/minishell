/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:14:37 by bgohan            #+#    #+#             */
/*   Updated: 2022/05/26 14:02:47 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <libft.h>
#include <commands.h>

int	unexp_token(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	set_exit_status(258);
	return (1);
}

int	unexp_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	set_exit_status(258);
	return (1);
}

int	ambiguous_redir(const char *redir_arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir_arg, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	set_exit_status(258);
	return (1);
}
