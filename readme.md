📜 get_next_line

📖 Descripción

El proyecto get_next_line consiste en implementar una función en C que permite leer un archivo descriptor línea por línea.Su objetivo es profundizar en el manejo de memoria dinámica, punteros y lectura de archivos mediante la función read().

La función principal es:

char *get_next_line(int fd);

Cada llamada devuelve la siguiente línea del archivo, incluyendo el carácter \n si existe.Cuando se alcanza el final del archivo, devuelve la última línea (aunque no termine en \n).Si ocurre un error o no hay nada más que leer, devuelve NULL.

⚙️ Instrucciones

Compilación

El proyecto debe compilarse con las banderas estándar de 42:

gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42 -o gnl

Ejecución

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

📚 Recursos

Referencias clásicas

Documentación de read() en Linux

ISO C Standard Library

Tutoriales sobre manejo de memoria dinámica en C.

Ejemplos de proyectos previos de 42 relacionados con get_next_line.

Uso de IA

En este proyecto se ha utilizado IA para:

Depuración de código: análisis de errores de referencia y seguridad en punteros.

Visualización: creación de diagramas de flujo y pseudocódigo para entender el algoritmo.

Documentación: generación de este README.md siguiendo las especificaciones del currículo.

🧮 Algoritmo seleccionado y justificación

El algoritmo implementado se basa en un buffer estático que conserva el estado entre llamadas sucesivas a get_next_line.

Flujo del algoritmo

Lectura con read(): se leen bloques de tamaño BUFFER_SIZE desde el descriptor.

Concatenación: el contenido leído se añade a un buffer dinámico (rest).

Búsqueda de salto de línea: se localiza el primer \n en el buffer.

Extracción de línea: se copia la parte hasta \n en una nueva cadena y se ajusta el buffer restante.

Retorno final: si no hay \n, se devuelve lo que queda en el buffer como última línea.

Justificación

Eficiencia: el uso de BUFFER_SIZE permite controlar el rendimiento y adaptarse a distintos tamaños de lectura.

Seguridad: se emplean funciones auxiliares (ft_calloc, ft_recalloc) para gestionar memoria evitando fugas.

Flexibilidad: el algoritmo funciona tanto con archivos como con stdin.

Claridad: separar en funciones auxiliares (ft_get_line, ft_read_concat, ft_return_last) mejora la legibilidad y facilita la depuración.

✨ Características adicionales

Compatible con múltiples descriptores de archivo.

Manejo seguro de memoria dinámica.

Devuelve líneas completas, incluyendo \n.

Correcto comportamiento al final de archivo.

## 🔄 Diagrama de flujo del algoritmo

```plaintext
┌──────────────────────────────┐
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
│ ¿Hay '\\n' en el buffer?      │
└────┬───────────────┬─────────┘
     │Sí             │No
     ▼               ▼
┌─────────────┐   ┌──────────────────────────────┐
│ Extraer     │   │ ¿Bytes leídos == 0?          │
│ línea hasta │   └────┬───────────────┬─────────┘
│ '\\n'        │        │Sí             │No
└────┬────────┘        ▼               ▼
     │           ┌─────────────┐   ┌────────────────────┐
     │           │ Devolver    │   │ Concatenar buffer  │
     │           │ resto final │   └────────────┬───────┘
     │           └────┬────────┘                │
     ▼                ▼                        ▼
┌──────────────────────────────────────────────┐
│               return línea                   │
└──────────────────────────────────────────────┘
