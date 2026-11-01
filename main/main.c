/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjuan-pa <gjuan-pa@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:02:05 by gjuan-pa          #+#    #+#             */
/*   Updated: 2026/06/13 16:34:16 by gjuan-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{

	int	fd;
	char	*linea;
	int	contador_lineas;
	char	*archivos = "archivo.txt";
	
	contador_lineas = 1;
	// 1. Abrimos el archivo en modo solo lectura (O_RDONLY)
	fd = open(archivos, O_RDONLY);
	// 2. Control de errores: si el archivo no existe o no se puede abrir
	if (fd == -1)
	{
		printf("Error: No se pudo abrir el archivo. ¡Asegúrate de que existe!\n");
		return (1);
	}
	// 3. llamamos a get_next_line en bucle para imprimir cada linea.
	// Mientras no devuelva NULL (que significa fin de archivo o error), seguimos.
	while ((linea = get_next_line(fd)) != NULL)
	{
		// Imprimimos el número de línea y el contenido
		printf("[Línea %d]: %s", contador_lineas, linea);
		//Liberamos la memori de la line impresa que nos dio GNL
		free(linea);
		contador_lineas++;
	}
	printf("\n--- FIN DEL ARCHIVO ---\n");
	// 4. Cerramos el file descriptor al terminar.
	close(fd);
	return (0);
}
