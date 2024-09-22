/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:31:49 by amanjon           #+#    #+#             */
/*   Updated: 2024/09/22 13:38:15 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void ft_exec(char **argv, int i, char **env)
{
	int pipes, pid, fd[2], status;

	pipes = argv[i] && strcmp(argv[i], "|");

	if (pipes && pipe(fd) == -1)
		ft_print("error: fatal\n"), exit(1);
	if (!pipes && !strcmp(*argv, "cd"))
		return (ft_cd(argv, i));
	if ((pid = fork()) == -1)
		ft_print("error: fatal\n"), exit(1);
	if (!pid)
	{
		argv[i] = 0;
		set_pipe(pipes, fd, 1);
		if (!strcmp(*argv, "cd"))
			exit(ft_cd(argv, i));
		execve(*argv, argv, env);
		ft_print("error: cannot execute "), ft_print(*argv), ft_print("\n"), exit(0);
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));	
}

int main(int argc, char **argv, char **env)
{
	int i;
	int status;
	
	i = 0;
	status = 0;
	while (argv[i])
	{
		argv += i + 1;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i)
			status = ft_exec(argv, i, env);
	}
	return (status);
}