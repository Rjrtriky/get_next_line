*This project was created as part of the curriculum for 42 by rjuarez-*
# 📚 get_next_line

## 📖 Description

The get_next_line project consists of implementing a function in C that allows reading multiple file descriptors line by line. Its goal is to deepen the understanding of dynamic memory management, pointers, and file reading through the read() function.

DEFINITION:

Each call on a specific file descriptor returns the next line of the file, including the \n character if it exists. When the end of the file is reached, it returns the last line (even if it does not end with \n). If an error occurs or there is nothing else to read, it returns NULL.

DEFINITION:

Each call on a specific file descriptor returns the next line of the file, including the \n character if it exists. When the end of the file is reached, it returns the last line (even if it does not end with \n). If an error occurs or there is nothing else to read, it returns NULL.

PROTOTYPE:
┌─────────────────────────────┐
│     get_next_line(fd)       │
└────────────┬────────────────┘
             │
             ▼
┌───────────────────────────────┐
│ Is fd valid and BUFFER_SIZE >=0? │
└───────┬───────────────┬───────┘
        │Yes            │No
        ▼               ▼
┌─────────────┐     ┌─────────────┐
│ Initialize  │     │   return    │
│   rest[fd]  │     │    NULL     │
└────┬────────┘     └─────────────┘
     │
     ▼
┌──────────────────────────────┐
│  Is there '\n' in rest[fd]?  │
└────┬───────────────┬─────────┘
     │Yes            │No
     ▼               ▼
┌─────────────┐   ┌──────────────────────────────┐
│ Extract     │   │ Are bytes read == 0?         │
│ line until  │   └────┬───────────────┬─────────┘
│ '\n'        │        │Yes            │No
└────┬────────┘        ▼               ▼
     │           ┌─────────────┐   ┌────────────────────┐
     │           │ Return      │   │ Concatenate buffer │
     │           │ final rest  │   └────────────┬───────┘
     │           └────┬────────┘                │
     ▼                ▼                         ▼
┌──────────────────────────────────────────────────┐
│                 return line                      │
└──────────────────────────────────────────────────┘
