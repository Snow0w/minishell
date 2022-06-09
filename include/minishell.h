/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:03:17 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:03:00 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

char	*get_variable(char *name);
void	set_variable(char *name, char *value);
void	initialize_variables(char **envp);
char	**get_envp_for_child_process(void);
int		is_var_plus_value_exist(char *name);

int		std_func_err(void);

void	destroy_vlist(void);

#endif
