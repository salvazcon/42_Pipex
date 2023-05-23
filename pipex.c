/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:44:32 by marvin            #+#    #+#             */
/*   Updated: 2023/05/23 00:44:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
    int		fd[2];
    
    if (argc == 5)
        return();
    fd[0] = open(argv[1], O_RDONLY);
    if (infule < 0)
        return();
    fd[1] = open(argv[argc - 1], );
    if (outfile < 0)
        return();
    /*Preguntas:
        - Que es env
        - por que divides, imagino por que son 2 procesos = 2 hijos
        - por que tanto access
        - me explicas los permisos de open , porfis
    //Control de errores de los argumentos que nos pasan
    //redirir la salida de la informacion con dup2();
    //control de errores sobre los permisos del archivo con access();
    // Ejecutar los comandos que nos pasen como argumentos: execve();
        /* char *args[3];
    
            args[0] = "ls";
            args[1] = "-l";
            args[2] = NULL;
            execve("/bin/ls", args, NULL);
            printf("This line will not be executed.\n"); */
    /*no se que uso le podenmos dar a los procesos hijos y padres,imagino que mas adelante.
    Por lo que voy viendo el comando pipe y el fork deben ir de la mano por el tema de dividr
    pocesos y unir archivos */
    /*Procesos secunduarios:
        wait - espera a que termine un proceso hijo
        sleep
    */
    //Ejecutar programas
    //Liberar memoria
    //Eliminar archivos temporales unlink();
    return (0);
}