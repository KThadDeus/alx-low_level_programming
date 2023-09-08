#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

ssize_t read_textfile(const char *filename, size_t letters) {
    if (filename == NULL) {
        return 0; // If filename is NULL, return 0 as specified.
    }

    int file_descriptor = open(filename, O_RDONLY); // Open the file for reading.

    if (file_descriptor == -1) {
        return 0; // If the file can't be opened, return 0.
    }

    char *buffer = malloc(letters); // Allocate memory for the buffer.

    if (buffer == NULL) {
        close(file_descriptor);
        return 0; // If memory allocation fails, return 0.
    }

    ssize_t bytes_read = read(file_descriptor, buffer, letters); // Read from the file.

    if (bytes_read == -1) {
        free(buffer);
        close(file_descriptor);
        return 0; // If reading from the file fails, return 0.
    }

    ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read); // Write to standard output.

    if (bytes_written == -1 || bytes_written != bytes_read) {
        free(buffer);
        close(file_descriptor);
        return 0; // If writing fails or doesn't write expected bytes, return 0.
    }

    free(buffer);
    close(file_descriptor);

    return bytes_read; // Return the actual number of letters read and printed.
}
