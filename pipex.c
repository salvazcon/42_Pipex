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

void	ft_cmd(struct s_var *v, char *cmd, char **envp)
{
	int		i;

	v->path = ft_split(ft_path(envp), ':');
	if (!v->path)
		ft_error(v, "Error: Path not found:", 1);
	v->exec = ft_split(cmd, ' ');
	i = -1;
	while (v->path[++i])
	{
		v->bin = ft_strjoin(v->path[i], "/");
		v->bin = ft_strjoin(v->bin, v->exec[0]);
		if (access(v->bin, F_OK) == 0)
			break ;
		v->bin = NULL;
	}
	if (!v->bin)
		ft_error(v, "Error: Command not found:", 127);
	if (execve(v->bin, v->exec, envp) == -1)
		ft_error(v, v->bin, 1);
}

void	ft_first_son(struct s_var *v, char *cmd, char **envp)
{
	close(v->pipex[0]);
	dup2(v->fd[0], STDIN_FILENO);
	dup2(v->pipex[1], STDOUT_FILENO);
	close(v->pipex[1]);
	ft_cmd(v, cmd, envp);
}

void	ft_last_son(struct s_var *v, char *cmd, char **envp)
{
	close(v->pipex[1]);
	dup2(v->pipex[0], STDIN_FILENO);
	dup2(v->fd[1], STDOUT_FILENO);
	close(v->pipex[0]);
	ft_cmd(v, cmd, envp);
}

void	ft_pipex(struct s_var *v, char **cmd, char **envp)
{
	if (pipe(v->pipex) == -1)
		ft_error(v, "Error: Pipe Error:", 1);
	v->ps1_id = fork();
	if (v->ps1_id == -1)
		ft_error(v, "Error: Fork Error:", 1);
	else if (v->ps1_id == 0)
		ft_first_son(v, cmd[2], envp);
	v->ps2_id = fork();
	if (v->ps2_id == -1)
		ft_error(v, "Error: Fork Error:", 1);
	else if (v->ps2_id == 0)
		ft_last_son(v, cmd[3], envp);
	close(v->pipex[0]);
	close(v->pipex[1]);
	waitpid(v->ps1_id, NULL, 0);
	waitpid(v->ps2_id, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	struct s_var	*v;

	v = ft_calloc(sizeof(struct s_var), 1);
	if (!v)
		return (0);
	if (argc == 5)
		ft_error(v, "Error: Invalid arguments.", 1);
	v->fd[0] = ft_open_file(v, argv[1], O_RDONLY);
	v->fd[1] = ft_open_file(v, argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC);
	ft_pipex(v, argv, envp);
	ft_free_all(v);
	return (0);
}

/*
//ft_putstr_fd("Error: Invalid arguments.\n", 2);
- El organizar el tema de la memroia en el ft_cmd
- Aclarar el tema de Exec del ft_cmd
- Optimizar las funciones dedicadas a iniciar porcesos...
- La mayoria de problemas son unicamente de este archivo.
*/