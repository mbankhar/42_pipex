/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:12:58 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/04 16:34:06 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/types.h>

void	get_args(int argc, char **argv)
{
	t_var	var;

	if (argc == 5)
	{
		if (argv[2] == NULL || argv[3] == NULL || argv[1] == NULL
			|| argv[4] == NULL)
			exit(EXIT_FAILURE);
		var.cmd_one = ft_split(argv[2], ' ');
		var.cmd_two = ft_split(argv[3], ' ');
		var.file_one = ft_strdup(argv[1]);
		var.file_one = ft_strdup(argv[4]);
		printf("%s\n", var.cmd_one[0]);
		printf("%s\n", var.cmd_one[1]);
		printf("%s\n", var.cmd_one[2]);
		printf("%s\n", var.cmd_two[0]);
		printf("%s\n", var.cmd_two[1]);
		printf("%s\n", var.cmd_two[2]);
		// printf("%s\n", var.file_one[0]);
		// printf("%s\n", var.file_one[1]);
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

char	*get_path(char **env, char *cmd)
{
	int		i;
	char	*path;
	char	**realpath;

	path[7] = "PATH=";
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], path, 7) != NULL)
			break ;
		else
			i++;
	}
	realpath = ft_split(env[i], ":");
	i = 0;
	while (realpath[i])
	{
		if (access(ft_strjoin(realpath[i], cmd), X_OK) == 0)
			break ;
		else
			i++;
	}
	ft_free(realpath);
	return (ft_strjoin(realpath[i], cmd));
}

void	execute(char *arg, char **env, char *cmd)
{
	char	*path_cmd;

	path_cmd = get_path(env, cmd);
	execve(path_cmd, cmd[1], env);
}

void	child(char **argv, int *pipefd, char **env)
{
	int		fd;
	t_var	var;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	execute(argv[2], env, var.cmd_one[1]);
}

void	parent(char **argv, int *pipefd, char **env)
{
	int		fd;
	t_var 	var;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit(0);
	dup2(fd, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	execute(argv[3], env, var.cmd_two[1]);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	env = NULL;
	get_args(argc, argv);
	if (pipe(pipefd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child(argv, pipefd, env);
	parent(argv, pipefd, env);
}


// < test.txt grep a1 | wc -w > test2
