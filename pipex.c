/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:35 by saazcon-          #+#    #+#             */
/*   Updated: 2023/05/23 18:29:35 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(char *argc, int flags)
{
	int fd;

	fd = open(argc, flags, 0644);
	if(fd < 0)
	{
		perror(argc);
		exit(1);
		//close(fd[0]); Cierra todo.
	}
	return (fd);
}

void	ft_pipex(int *fd, char **argv, char **envp)
{
	int		pipex[2];
	pid_t	ps1_id;
	pid_t	ps2_id;

	if (pipe(pipex) == -1)
		exit(1);
	ps1_id = fork();
	if (ps1_id == -1)
		exit(1);
	else if (ps1_id == 0)
	{
		close(pipex[0]);
		dup2(fd[1], STDIN_FILENO);
		dup2(pipex[1], STDOUT_FILENO);
		close(pipex[1]);
		//exec(argv[2], envp);
	}
	else
	{
		ps2_id = fork();
		if (ps2_id == -1)
			exit(1);
		else if (ps2_id == 0)
		{
			close(pipex[1]);
			dup2(pipex[0], STDIN_FILENO);
			dup2(fd[0], STDOUT_FILENO);
			close(pipex[0]);
			//exec(argv[3], envp);
		}
		else
		{
			close_fds(pipex);
			waitpid(ps1_id, NULL, 0);
			waitpid(ps2_id, NULL, 0);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc == 5)
		return (0);
	fd[0] = ft_open_file(argv[1], O_RDONLY);
	fd[1] = ft_open_file(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC);
	ft_pipex(fd, argv, envp);
	//system("leaks pipex");
	return (0);
}

/*
* Preguntas:
	- Que es 'env' en los args? Se debe a que en este punetero
	doble guarda todo el comando env completo 
	- Cada fork se debe porque al usar el comando exeve
	se cierra el programa y no deseamos cerra el programa principal.
	- Devo saber como enfocar el dup2.
* Controles de errorers:
	- Los argumentos que nos pasan.
	- Los archivos abiertos.
	- Los procesos en ejecucion.
	- Diferentes tipos de errores: 128, perror, stdio...
* Comandos nuevos:
	Control de errores sobre los permisos del archivo con access();
	Ejecutar el comando con: execve();
		char *args[3];

		args[0] = "ls";
		args[1] = "-l";
		args[2] = NULL;
		execve("/bin/ls", args, NULL);
		printf("This line will not be executed.\n");
	wait - espera a que termine un proceso hijo
	sleep - mata los precosos.
	Eliminar archivos temporales:  unlink();
*/