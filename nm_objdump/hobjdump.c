#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include "hobjdump.h"


/**
 * my_be16toh - convert 16 bits value big endian
 * @value: hex value
 *
 * Return: value in little edian
 */
uint16_t my_be16toh(uint16_t value)
{
	return (((value >> 8) & 0xFF) | ((value & 0xFF) << 8));
}

/**
 * my_be32toh - convert 32 bits value big endian
 * @value: hex value
 *
 * Return: value in little edian
 */
uint32_t my_be32toh(uint32_t value)
{
	return (((value >> 24) & 0xFF) |
		((value >>  8) & 0xFF00) |
		((value & 0xFF00) <<  8) |
		((value & 0xFF) << 24));
}

/**
 * read_elf32_be_section - Convert a 32-bit ELF section header from big-endian
 * to host byte order.
 * This function takes a pointer to a 32-bit ELF section header in big-endian
 * byte order
 * and converts various section header fields to the host byte order.It is used
 * to ensure
 * correct interpretation of the section header on the host system.
 *
 * @section_header32: pointer to a 32-bit ELF section header in big-endian
 * byte order.
 */
void read_elf32_be_section(Elf32_Shdr *section_header32)
{
	section_header32->sh_name = my_be32toh(section_header32->sh_name);
	section_header32->sh_type = my_be32toh(section_header32->sh_type);
	section_header32->sh_addr = my_be32toh(section_header32->sh_addr);
	section_header32->sh_offset = my_be32toh(section_header32->sh_offset);
	section_header32->sh_size = my_be32toh(section_header32->sh_size);
	section_header32->sh_entsize = my_be32toh(section_header32->sh_entsize);
	section_header32->sh_flags = my_be32toh(section_header32->sh_flags);
	section_header32->sh_link = my_be32toh(section_header32->sh_link);
	section_header32->sh_info = my_be32toh(section_header32->sh_info);
	section_header32->sh_addralign = my_be32toh(section_header32->sh_addralign);
}

/**
* get_section_name32 - Retrieve the name of an ELF32 section little endian.
* This function reads and returns the name of an ELF32 section based on the
* provided section headerand file pointer.
* @section_header: The ELF32 section header structure.
* @file: A pointer to the ELF file.
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_section_name32(Elf32_Shdr section_header, FILE *file)
{
	char *section_names = NULL;

	fread(&section_header, 1, sizeof(section_header), file);
	section_names = (char *)malloc(section_header.sh_size);
	fseek(file, section_header.sh_offset, SEEK_SET);
	fread(section_names, 1, section_header.sh_size, file);
	return (section_names);
}

/**
* get_section_name32_big - Retrieve the name of an ELF32 section big endian.
* This function reads and returns the name of an ELF32 section based on the
* provided section headerand file pointer.
* @section_header: The ELF32 section header structure.
* @file: A pointer to the ELF file.
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_section_name32_big(Elf32_Shdr section_header, FILE *file)
{
	char *section_names = NULL;

		fread(&section_header, 1, sizeof(section_header), file);
		read_elf32_be_section(&section_header);
		section_names = (char *)malloc(section_header.sh_size);
		fseek(file, section_header.sh_offset, SEEK_SET);
		fread(section_names, 1, section_header.sh_size, file);
	return (section_names);
}

/**
* get_section_name64 - Retrieve the name of an ELF64 section little endian.
* This function reads and returns the name of an ELF64 section based on the
* provided section headerand file pointer.
* @section_header: The ELF64 section header structure.
* @file: A pointer to the ELF file.
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_section_name64(Elf64_Shdr section_header, FILE *file)
{
	char *section_names = NULL;

	fread(&section_header, 1, sizeof(section_header), file);
	section_names = (char *)malloc(section_header.sh_size);
	fseek(file, section_header.sh_offset, SEEK_SET);
	fread(section_names, 1, section_header.sh_size, file);
	return (section_names);
}

int print_sections_32(Elf32_Ehdr *ehdr, const char *filename)
{
	FILE *file = NULL;
	char *section_names = NULL;
	Elf32_Shdr section_header32;
	int index = 0;

	file = fopen(filename, "rb");
	if (file == NULL)
	{
		perror("Cannot open the file");
		return (1);
	}

	fseek(file, ehdr->e_shoff + ehdr->e_shstrndx *
					ehdr->e_shentsize, SEEK_SET);
	section_names = get_section_name32(section_header32, file);

	fseek(file, 0, SEEK_SET);
	fseek(file, ehdr->e_shoff, SEEK_SET);

	for (index = 0; index < ehdr->e_shnum; index++)
	{
		char *name = "";

		fread(&section_header32, sizeof(Elf32_Shdr), 1, file);

		if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
			read_elf32_be_section(&section_header32);

		if (section_header32.sh_name)
		{
			name = section_names + section_header32.sh_name;
			printf("%s\n", name);
		}
	}
	fclose(file);
	return (0);
}

int print_sections_64(Elf64_Ehdr *ehdr, const char *filename)
{
	FILE *file = NULL;
	char *section_names = NULL;
	Elf64_Shdr section_header64;
	int index = 0;

	file = fopen(filename, "rb");
	if (file == NULL)
	{
		perror("Cannot open the file");
		return (1);
	}

	fseek(file, ehdr->e_shoff + ehdr->e_shstrndx *
					ehdr->e_shentsize, SEEK_SET);
	section_names = get_section_name64(section_header64, file);

	fseek(file, 0, SEEK_SET);
	fseek(file, ehdr->e_shoff, SEEK_SET);

	for (index = 0; index < ehdr->e_shnum; index++)
	{
		char *name = "";

		fread(&section_header64, sizeof(Elf32_Shdr), 1, file);
		if (section_header64.sh_name)
		{
			name = section_names + section_header64.sh_name;
			printf("%s\n", name);
		}
	}
	fclose(file);
	return (0);
}

void print_flag(int *flag_printed, unsigned long flags, unsigned long flag,
				const char *flag_name)
{
	if (flags & flag)
	{
		if (*flag_printed)
			printf(", ");
		printf("%s", flag_name);
		*flag_printed = 1;
	}
}

void print_elf_header_32(Elf32_Ehdr *ehdr, const char *filename)
{
	const char *formatted_filename = filename;
	int flag_printed = 0;
	unsigned long flags_interp = 0;

	if (formatted_filename[0] == '.' && formatted_filename[1] == '/')
		formatted_filename += 2;

	printf("%s:     file format elf32-i386\n", formatted_filename);
	printf("architecture: i386");

	if (ehdr->e_type == ET_EXEC)
		flags_interp |= EXEC_P;
	if (ehdr->e_type == ET_REL)
		flags_interp |= HAS_RELOC;
	if (ehdr->e_type == ET_DYN)
		flags_interp |= DYNAMIC;

	flags_interp |= (ehdr->e_shnum > 0) ? HAS_SYMS : 0;
	flags_interp |= (ehdr->e_phnum > 0) ? D_PAGED : 0;

	printf(" flags 0x%08lx:\n", flags_interp);

	print_flag(&flag_printed, flags_interp, EXEC_P, "EXEC_P");
	print_flag(&flag_printed, flags_interp, HAS_RELOC, "HAS_RELOC");
	print_flag(&flag_printed, flags_interp, HAS_SYMS, "HAS_SYMS");
	print_flag(&flag_printed, flags_interp, DYNAMIC, "DYNAMIC");
	print_flag(&flag_printed, flags_interp, D_PAGED, "D_PAGED");

	printf("\n");

	printf("start address 0x%08lx\n", (unsigned long)ehdr->e_entry);

	print_sections_32(ehdr, filename);
}


void print_elf_header_64(Elf64_Ehdr *ehdr, const char *filename)
{
	const char *formatted_filename = filename;
	int flag_printed = 0;
	unsigned long flags_interp = 0;

	if (formatted_filename[0] == '.' && formatted_filename[1] == '/')
		formatted_filename += 2;

	printf("%s:     file format elf64-x86-64\n", formatted_filename);
	printf("architecture: i386:x86-64");

	if (ehdr->e_type == ET_EXEC)
		flags_interp |= EXEC_P;
	if (ehdr->e_type == ET_REL)
		flags_interp |= HAS_RELOC;
	if (ehdr->e_type == ET_DYN)
		flags_interp |= DYNAMIC;

	flags_interp |= (ehdr->e_shnum > 0) ? HAS_SYMS : 0;
	flags_interp |= (ehdr->e_phnum > 0) ? D_PAGED : 0;

	printf(" flags 0x%08lx:\n", flags_interp);

	print_flag(&flag_printed, flags_interp, EXEC_P, "EXEC_P");
	print_flag(&flag_printed, flags_interp, HAS_RELOC, "HAS_RELOC");
	print_flag(&flag_printed, flags_interp, HAS_SYMS, "HAS_SYMS");
	print_flag(&flag_printed, flags_interp, DYNAMIC, "DYNAMIC");
	print_flag(&flag_printed, flags_interp, D_PAGED, "D_PAGED");

	printf("\n");

	printf("start address 0x%016lx\n", (unsigned long)ehdr->e_entry);

	print_sections_64(ehdr, filename);
}

int analyze_32bit_elf(Elf32_Ehdr *ehdr, const char *filename)
{
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
	{
		print_elf_header_32(ehdr, filename);
	}
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		print_elf_header_32(ehdr, filename);
	}
	else
	{
		printf("endianness unknown.\n");
	}
	return (0);
}

int analyze_64bit_elf(Elf64_Ehdr *ehdr, const char *filename)
{
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
	{
		print_elf_header_64(ehdr, filename);
	}
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		printf("big-endian64.\n");
	}
	else
	{
		printf("endianness unknown.\n");
	}

	return (0);
}

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
	close(fd);

	ehdr32 = (Elf32_Ehdr *)map;
	ehdr64 = (Elf64_Ehdr *)map;

	if (ehdr32->e_ident[EI_CLASS] == ELFCLASS32)
	{
		analyze_32bit_elf(ehdr32, filename);
	}
	else if (ehdr64->e_ident[EI_CLASS] == ELFCLASS64)

		analyze_64bit_elf(ehdr64, filename);
	else
	{
		fprintf(stderr, "No es un archivo ELF válido.\n");
		return (1);
	}

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
