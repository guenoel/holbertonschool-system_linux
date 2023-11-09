#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include "hobjdump.h"


int analyze_file(const char *filename)
{
	int fd;
	void *map;
	size_t file_size;
	Elf32_Ehdr *ehdr32;
	Elf64_Ehdr *ehdr64;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	map = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
	{
		perror("mmap");
		return (1);
	}
	ehdr32 = (Elf32_Ehdr *)map;
	ehdr64 = (Elf64_Ehdr *)map;

	if (ehdr32->e_ident[EI_CLASS] == ELFCLASS32)
	{
		analyze_32bit_elf(ehdr32, filename, map);
	}
	else if (ehdr64->e_ident[EI_CLASS] == ELFCLASS64)
		analyze_64bit_elf(ehdr64, filename, map);
	else
	{
		fprintf(stderr, "No es un archivo ELF válido.\n");
		return (1);
	}

	close(fd);
	munmap(map, file_size);
	return (0);
}

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2)
	{
		fprintf(stderr, "hobjdump: %s [objfile...]\n", argv[0]);
		return (1);
	}

	for (i = 1; i < argc; i++)
	{

		if (analyze_file(argv[i]) != 0)
		{
			return (1);
		}
	}

	return (0);
}
