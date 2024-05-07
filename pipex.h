/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:06 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/06 18:39:07 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_var
{
	int		i;
	char	*file_one;
	char	*file_two;
	char	**cmd_one;
	char	**cmd_two;
}			t_var;

void		get_args(int argc, char **argv, t_var *var);
void		ft_free(char **array);
void		execute(char **env, char *cmd, t_var var);
void		executepar(char **env, char *cmd, t_var var);
char		*get_path(char **env, char *cmd);
#endif