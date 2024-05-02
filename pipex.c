/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbankhar <mbankhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:12:58 by mbankhar          #+#    #+#             */
/*   Updated: 2024/05/02 18:52:16 by mbankhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}
int	main(int argc, char **argv)
{
	get_args(argc, argv);
}

// < test.txt grep a1 | wc -w > test2
