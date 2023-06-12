/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:41:37 by saazcon-          #+#    #+#             */
/*   Updated: 2023/06/12 19:09:12 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(struct s_var *v, char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		ft_error(v, file, 1);
	return (fd);
}

char	*ft_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	}
	return (NULL);
}

void	ft_free(char	**paco)
{
	int	i;

	i = -1;
	while (paco[++i])
		free(paco[i]);
	free(paco);
}

void	ft_free_all(struct s_var *v)
{
	close(v->fd[0]);
	close(v->fd[1]);
	if (v->path)
		ft_free(v->path);
	if (v->exec)
		ft_free(v->exec);
	if (v->bin)
		free(v->bin);
	free(v);
}

void	ft_error(struct s_var *v, char *error, int num)
{
	perror(error);
	if (!v)
		ft_free_all(v);
	exit(num);
}
