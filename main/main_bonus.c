/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjuan-pa <gjuan-pa@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:39:31 by gjuan-pa          #+#    #+#             */
/*   Updated: 2026/06/10 15:39:40 by gjuan-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *linea;
    int     contador_lineas;
	int	i;
	char *archivos[3] = {"archivo[1].txt", "archivo[2].txt", "archivo[3].txt"};
	
	i = 0;
    contador_lineas = 1;
    
    // 1. Abrimos el archivo en modo solo lectura (O_RDONLY)
    
    while (i < 3)
    {
    
    	fd = open(archivos[i], O_RDONLY);
    
    // 2. Control de errores: si el archivo no existe o no se puede abrir
    if (fd == -1)
    {
        printf("Error: No se pudo abrir el archivo.txt. ¡Asegúrate de que existe!\n");
        return (1);
    }

    printf("--- INICIO DE LA LECTURA ---\n");

    // 3. El bucle mágico: llamamos a get_next_line en bucle.
    // Mientras no devuelva NULL (que significa fin de archivo o error), seguimos.
    while ((linea = get_next_line(fd)) != NULL)
    {
        // Imprimimos el número de línea y el contenido
        printf("[Línea %d]: %s", contador_lineas, linea);
        
        // ¡MUY IMPORTANTE! Liberamos la línea que nos dio GNL para evitar leaks
        free(linea);
        
        contador_lineas++;
    }

    printf("\n--- FIN DEL ARCHIVO ---\n");

    // 4. Cerramos el file descriptor al terminar
    close(fd);
    i++;
    }
    return (0);
}
