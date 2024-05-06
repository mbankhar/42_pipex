/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:13:37 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/06 16:17:20 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_args(int argc, char **argv, t_var *var)
{
	if (argc == 5)
	{
		if (argv[2] == NULL || argv[3] == NULL || argv[1] == NULL
			|| argv[4] == NULL)
			exit(EXIT_FAILURE);
		if (ft_strchrmodif(argv[2]) != -1)
			var->cmd_one = ft_splitmodif(argv[2], ' ');
		else
			var->cmd_one = ft_split(argv[2], ' ');
		if (ft_strchrmodif(argv[3]) != -1)
			var->cmd_two = ft_splitmodif(argv[3], ' ');
		else
			var->cmd_two = ft_split(argv[3], ' ');
		// int	i = -1;
		// while (var->cmd_two[++i])
		// {
		// 	printf("%s\n", var->cmd_two[i]);
		// }
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	execute(char **env, char *cmd, char **argv, t_var var)
{
	char	*path_cmd;

	path_cmd = get_path(env, cmd, var);
	if (execve(path_cmd, var.cmd_one, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(var.cmd_one[0], 2);
		ft_free(var.cmd_one);
		exit(0);
	}
}

void	executepar(char **env, char *cmd, char **argv, t_var var)
{
	char	*path_cmd;

	path_cmd = get_path(env, cmd, var);
	if (execve(path_cmd, var.cmd_two, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(var.cmd_two[0], 2);
		ft_free(var.cmd_two);
		exit(0);
	}
}
