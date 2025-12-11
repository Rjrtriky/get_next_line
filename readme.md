# 📜 get_next_line

## 📖 Descripción

El proyecto get_next_line consiste en implementar una función en C que permite leer un archivo descriptor línea por línea.Su objetivo es profundizar en el manejo de memoria dinámica, punteros y lectura de archivos mediante la función read().

### Prototipo:
char *get_next_line(int fd);

Cada llamada devuelve la siguiente línea del archivo, incluyendo el carácter \n si existe.Cuando se alcanza el final del archivo, devuelve la última línea (aunque no termine en \n).Si ocurre un error o no hay nada más que leer, devuelve NULL.

### Parametros:
En C, a los ficheros se les identifica con un numero. No obstante, se reservan algunos para los ficheros estándar cuyos numeros por defecto son:

    -Entrada estándar:   STDIN_FILENO  0
    -Salida estándar:    STDOUT_FILENO 1
	-Error estándar:     STDERR_FILENO 2

### Retorno:
    -Correcto:    Puntero a la cadena con la linea leida del fichero. 
    -Incorrecto:  NULL.

## ⚙️ Instrucciones

COMPILACION

El proyecto debe compilarse con las banderas estándar de 42:

gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42 -o gnl

EJECUCION

Ejemplo de uso:

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}

## 📚 Recursos

Referencias clásicas:

-Documentación de read() en Linux con man

Tutoriales sobre manejo de memoria dinámica en C.

Ejemplos de proyectos previos de 42 relacionados con get_next_line.

Uso de IA

En este proyecto se ha utilizado IA para:

Depuración de código: análisis de errores de referencia y seguridad en punteros.

Visualización: creación de diagramas de flujo y pseudocódigo para entender el algoritmo.


## 🔄 Diagrama de flujo del algoritmo

```plaintext
┌─────────────────────────────┐
│     get_next_line(fd)       │
└────────────┬────────────────┘
             │
             ▼
┌──────────────────────────────┐
│ ¿fd válido y BUFFER_SIZE > 0?│
└───────┬───────────────┬──────┘
        │Sí             │No
        ▼               ▼
┌─────────────┐     ┌─────────────┐
│ Inicializar │     │   return    │
│   buffer    │     │    NULL     │
└────┬────────┘     └─────────────┘
     │
     ▼
┌──────────────────────────────┐
│ ¿Hay '\\n' en el buffer?     │
└────┬───────────────┬─────────┘
     │Sí             │No
     ▼               ▼
┌─────────────┐   ┌──────────────────────────────┐
│ Extraer     │   │ ¿Bytes leídos == 0?          │
│ línea hasta │   └────┬───────────────┬─────────┘
│ '\\n'       │        │Sí             │No
└────┬────────┘        ▼               ▼
     │           ┌─────────────┐   ┌────────────────────┐
     │           │ Devolver    │   │ Concatenar buffer  │
     │           │ resto final │   └────────────┬───────┘
     │           └────┬────────┘                │
     ▼                ▼                         ▼
┌──────────────────────────────────────────────────┐
│                 return línea                     │
└──────────────────────────────────────────────────┘
