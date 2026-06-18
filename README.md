*Este proyecto ha sido creado como parte del currículo de 42 por <gjuan-pa>.*

# Get Next Line

## Descripción
El objetivo de este proyecto es programar una función que devuelva una línea leída desde un descriptor de archivo (file descriptor). Cada llamada sucesiva a la función `get_next_line` permite leer el contenido de un archivo de texto línea por línea hasta el final, gestionando eficientemente la memoria y sin perder el hilo de la lectura entre llamadas. Este proyecto introduce el concepto de variables estáticas en C y es fundamental para entender la gestión de buffers y la lectura de archivos de (Entrada/Salida).

### Soporte Multi-Archivo (Parte Bonus)
El objetivo del **Bonus** es permitir que la función lea de **múltiples archivos a la vez de forma intercalada**, sin perder el hilo de ninguna lectura y sin mezclar los textos.

### ¿Cómo funciona?
*   **Intercalado**: Puedes leer una línea del *Archivo A*, luego una línea del *Archivo B*, y al volver al *Archivo A* continuarás exactamente donde lo dejaste.
*   **Independencia**: Cada archivo mantiene su propio progreso de lectura sin interferir en los demás.

### Implementación Técnica
*   **Estructura**: Se sustituye la variable estática simple por un **array estático** (`static char *buffer_line[1024]`).
*   **Identificación**: Se utiliza el número identificador del archivo (*File Descriptor*) como índice directo del array.
*   **Aislamiento**: Si lees el archivo número `3`, su contenido sobrante se guarda exclusivamente en la posición `buffer_line[3]`, quedando totalmente aislado del resto.


## Estructura del Proyecto

### Archivo de Cabecera (`get_next_line.h`)
El archivo de configuración de este proyecto define las librerías del sistema necesarias, el tamaño de buffer por defecto y los prototipos de todas las funciones utilizadas:

*   **Librerías del Sistema:**
    *   `<stdlib.h>`: Para la gestión de memoria dinámica mediante `malloc` y `free`.
    *   `<unistd.h>`: Para realizar operaciones de lectura mediante la función del sistema `read`.
    *   `<fcntl.h>`: Necesario para usar la función `open` en los archivos de prueba (`main.c`).
*   **Macro `BUFFER_SIZE`:** Se establece un valor predeterminado de `42` mediante directivas de control (`#ifndef`), permitiendo que este valor sea sobrescrito en tiempo de compilación.

### Funciones Principales
*   `get_next_line`: Función principal que coordina la lectura, el corte de la línea y el almacenamiento del excedente.
*   `read_file`: Lee el descriptor de archivo y acumula el contenido en el buffer acumulador hasta encontrar un salto de línea (`\n`) o llegar al final del archivo (`EOF`).
*   `cut_line`: Extrae la línea actual completa (hasta el salto de línea incluido) del buffer acumulador para ser devuelta.
*   `saved_content`: Limpia el buffer acumulador, eliminando la línea ya devuelta y conservando únicamente los caracteres sobrantes para la siguiente llamada.

### Funciones Auxiliares (Libft)
*   `ft_strlen`: Saca la longitud exacta de una cadena de caracteres.
*   `ft_strchr`: Busca la primera aparición de un carácter específico (en este caso, `\n`) dentro de una cadena.
*   `ft_strjoin`: Concatena dos cadenas de caracteres reservando la memoria necesaria.

## Instrucciones

### Codigo Prueba (main.c)
```
#include "get_next_line.h"

int    main(void)
	{

    	int    fd;
    	char    *linea;
    	int    contador_lineas;
    	char    *archivos = "archivo.txt";
    
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
```
### Requisitos previos
Es necesario disponer de un compilador de C como `gcc` o `cc` y las herramientas estándar de desarrollo en entornos Unix/Linux.

### Compilación
Para compilar el proyecto junto con tu propio archivo principal (`main.c`), ejecuta el siguiente comando en la terminal. Puedes modificar el valor de `BUFFER_SIZE` según tus necesidades de prueba, pero si no pones nada coje por defeccto el que hay en la libreria del sistema y tiene de sacar la flag de -D el compilar:

##Compilacion sin bonus:
```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

##Compilacion bonus:
```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl
```

### Ejecución
Una vez compilado, puedes ejecutar el programa pasando un archivo de texto como entrada (si tu `main.c` está preparado para abrir un archivo) o leer directamente de la entrada estándar:

```bash
./gnl archivo.txt
```

## Algoritmo y Decisiones Técnicas
El algoritmo seleccionado combina la persistencia de una **variable estática** con la flexibilidad de la **gestión de memoria dinámica**. La variable estática `static char *buffer_line` funciona conservando su valor entre diferentes llamadas a la misma función, lo que permite recordar los caracteres leídos que pertenecen a la siguiente línea. Sin embargo, no almacena un tamaño fijo, sino que se redimensiona dinámicamente en cada ciclo de lectura mediante `ft_strjoin` y se libera/recorta mediante `saved_content`.

### Justificación del Algoritmo
1.  **Lectura Acumulativa (`read_file`):** Se lee el archivo en bloques de tamaño `BUFFER_SIZE`. Cada bloque se une al contenido anterior usando `ft_strjoin`. Este bucle termina cuando `ft_strchr` detecta un salto de línea `\n` en el acumulador o cuando `read` devuelve `0` (final del archivo).
2.  **Extracción Dinámica (`cut_line`):** Una vez que sabemos que tenemos una línea completa en `buffer_line`, localizamos la posición del `\n`. Se reserva la memoria exacta para esa línea, se copia y se prepara para su devolución.
3.  **Gestión de Residuos (`saved_content`):** El texto que quedó después del `\n` no se puede perder. Esta función reubica ese "residuo" al principio de la variable estática `buffer_line` y libera la memoria de la línea vieja. Esto optimiza el uso de la memoria RAM y evita fugas (leaks).

### Otros algoritmos y Alternativas
1.  **Frente a Listas Enlazadas:** Las listas enlazadas ahorran tiempo de copia en cada lectura (evitan el `strjoin`), pero fragmentan más la memoria y complican la función de extracción (`cut_line`), la cual tendría que recorrer múltiples nodos para reconstruir una sola línea.
2.  **Frente a Arrays Estáticos Fijos:** Un array estático puro (`static char buf[BUFFER_SIZE]`) evita el uso de `malloc` para el residuo, pero se vuelve ineficiente y limitado cuando el tamaño de la línea excede por mucho al `BUFFER_SIZE`, obligando de todos modos a implementar lógica dinámica externa.

## Recursos

### Referencias Clásicas
*   [Documentación de GNU sobre File Descriptors](https://gnu.org)
*   [Man de las funciones `read`, `malloc` y `free`](https://man7.org)
*   Tutoriales de la comunidad de 42 sobre variables estáticas y gestión de buffers.

### Uso de Inteligencia Artificial
En este proyecto se ha utilizado IA de la siguiente manera:
*   **Tareas:** Estructuración de la documentación del archivo README y revisión de la coherencia lógica de las explicaciones técnicas.
*   **Partes del proyecto:** Exclusivamente en la fase de documentación y redacción de este archivo explicativo, sin intervenir en la arquitectura ni en la escritura del código fuente en C.
