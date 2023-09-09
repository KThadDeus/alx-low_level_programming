#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <elf.h>
#include <sys/types.h>

void print_error(const char *message) {
    dprintf(STDERR_FILENO, "%s\n", message);
    exit(98);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error("Usage: elf_header elf_filename");
    }

    const char *elf_filename = argv[1];
    int fd = open(elf_filename, O_RDONLY);
    if (fd == -1) {
        print_error("Error: Cannot open file");
    }

    // Read the ELF header.
    Elf64_Ehdr elf_header;
    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        print_error("Error: Cannot read ELF header");
    }

    // Check if it's a valid ELF file.
    if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
        print_error("Error: Not an ELF file");
    }

    // Display the ELF header information.
    printf("Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", elf_header.e_ident[i]);
    }
    printf("\nClass: %d-bit\n", elf_header.e_ident[EI_CLASS] == ELFCLASS64 ? 64 : 32);
    printf("Data: %s\n", elf_header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("Version: %d\n", elf_header.e_ident[EI_VERSION]);
    printf("OS/ABI: %d\n", elf_header.e_ident[EI_OSABI]);
    printf("ABI Version: %d\n", elf_header.e_ident[EI_ABIVERSION]);

    printf("Type: ");
    switch (elf_header.e_type) {
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("Unknown (%#x)\n", elf_header.e_type);
            break;
    }

    printf("Entry point address: %#lx\n", (unsigned long)elf_header.e_entry);

    close(fd);
    return 0;
}

