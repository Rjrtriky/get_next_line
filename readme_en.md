*This project was created as part of the curriculum for 42 by rjuarez-*
# 📚 get_next_line

## 📖 Description

The get_next_line project involves implementing a function in C that allows reading a file descriptor line by line. Its goal is to deepen understanding of dynamic memory management, pointers, and file reading using the read() function.

DEFINITION:

Each call returns the next line from the file, including the `\n` character if it exists. When the end of the file is reached, it returns the last line (even if it doesn’t end with `\n`). If an error occurs or there is nothing left to read, it returns NULL.

PROTOTYPE:

    char *get_next_line(int fd);

PARAMETERS:

In C, files are identified by a number. However, some are reserved for standard files whose default numbers are:

    - Standard input:   STDIN_FILENO  0
    - Standard output:  STDOUT_FILENO 1
    - Standard error:   STDERR_FILENO 2

RETURN:

    - Success:   Pointer to the string with the line read from the file.
    - Failure:   NULL.

## ⚙️ Instructions

COMPILATION

The project must be compiled with the standard 42 flags:

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42 -o gnl

EXECUTION

Example usage:

    #include "get_nex_line.h"
    int main(void)
    {
        int fd = open("file.txt", O_RDONLY);
        char *line;
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("%s", line);
            free(line);
        }
        close(fd);
        return 0;
    }

## 📚 Resources

CLASSIC REFERENCES:

    - Linux read() documentation via man or at https://man7.org/linux/man-pages/man2/read.2.html
    - Tutorials on dynamic memory management in C.
    - Examples of previous 42 projects related to get_next_line.

AI USAGE:

    - Pointer safety.
    - Creating flowcharts after coding.


## 📊 Algorithm Flowchart

```plaintext
┌─────────────────────────────┐
│     get_next_line(fd)       │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│ Is fd valid and BUFFER_SIZE │
│          > 0?               │
└──────────────┬──────────────┘
        │Yes           │No
        ▼              ▼
┌─────────────┐  ┌─────────────┐
│ Initialize  │  │   return    │
│   buffer    │  │    NULL     │
└─────────────┘  └─────────────┘
        │
        ▼
┌─────────────────────────────┐
│ Is there a '\\n' in the     │
│        buffer?              │
└─────────────┬───────────────┘
        │Yes           │No
        ▼              ▼
┌─────────────┐  ┌─────────────────────────────┐
│ Extract     │  │ Bytes read == 0?            │
│ line up to  │  └─────────────┬───────────────┘
│ '\\n'       │         │Yes           │No
└─────────────┘         ▼              ▼
        │       ┌─────────────┐  ┌─────────────┐
        │       │ Return      │  │ Concatenate │
        │       │ final rest  │  │ buffer      │
        ▼       └─────────────┘  └─────────────┘
┌─────────────────────────────────────────────────────┐
│                return line                          │
└─────────────────────────────────────────────────────┘
