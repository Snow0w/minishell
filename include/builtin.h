/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:50:19 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:50:35 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <parser.h>

void		check_spelling(char *word, size_t len, int *exit_status, int mode);
long		calc_status_minishell_exit(char *str, int *flag);

int			minishell_pwd(char **cmd);
int			minishell_cd(char **cmd);
int			minishell_echo(char	**cmd);
int			minishell_env(char **cmd);
int			minishell_export(char **cmd);
int			minishell_unset(char **cmd);
int			minishell_exit(char **cmd);

t_cmdtree	**tree_to_exit_delete(void);
#endif
