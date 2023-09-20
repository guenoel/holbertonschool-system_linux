#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include "hreadelf.h"

/**
 * main - entry point of make 0
 * @argc: count of arguments
 * @argv: array of arguments
 * Return: 0 success, 1 otherwise
 */
int main(int argc, char *argv[])
{
	FILE *file = NULL;
	Elf_Ehdr elf_header;

	int is_32bits = 0; /* Flag 1 -> 32 bits 0 -> 64 bits */

	if (argc != 2)
		return (EXIT_SUCCESS);
	file = fopen(argv[1], "rb");
	if (file == NULL)
	{
		perror("Can't open file");
		return (1);
	}
	/* Read ELF header to check if class 32 or 64 */
	fread(&elf_header, sizeof(Elf_Ehdr), 1, file);

	/* Check if 32 bits */
	if (elf_header.elf_header32.e_ident[EI_CLASS] == ELFCLASS32)
	{
		/* Store in struct from start of file to end of ELF header */
		is_32bits = 1;
		/* Check if Big Endian (not Little Endian) */
		if (elf_header.elf_header32.e_ident[EI_DATA] == ELFDATA2MSB)
			read_elf32_be_header(&elf_header.elf_header32);
	}
	print_header2(is_32bits, file, elf_header);
	fseek(file, (is_32bits ? elf_header.elf_header32.e_phoff : elf_header.elf_header64.e_phoff), SEEK_SET);
	loop_print2(is_32bits, file, elf_header);

	printf("\n");
	printf(" Section to Segment mapping:\n");
	printf("  Segment Sections...\n");

	fclose(file);
	return (0);
}

/**
 * read_elf32_be_header - Convert a 32-bit ELF header from big-endian to host
 * byte order.
 * This function takes a pointer to a 32-bit ELF header big-endian byte order
 * and converts various header fields to the host byte order. It is used to
 * ensure
 * correct interpretation of the header on the host system.
 *
 * @ehdr: A pointer to a 32-bit ELF header in big-endian byte order.
 */
void read_elf32_be_header(Elf32_Ehdr *ehdr)
{
	ehdr->e_type = my_be16toh(ehdr->e_type);
	ehdr->e_machine = my_be16toh(ehdr->e_machine);
	ehdr->e_version = my_be32toh(ehdr->e_version);
	ehdr->e_entry = my_be32toh(ehdr->e_entry);
	ehdr->e_phoff = my_be32toh(ehdr->e_phoff);
	ehdr->e_shoff = my_be32toh(ehdr->e_shoff);
	ehdr->e_flags = my_be32toh(ehdr->e_flags);
	ehdr->e_ehsize = my_be16toh(ehdr->e_ehsize);
	ehdr->e_phentsize = my_be16toh(ehdr->e_phentsize);
	ehdr->e_phnum = my_be16toh(ehdr->e_phnum);
	ehdr->e_shentsize = my_be16toh(ehdr->e_shentsize);
	ehdr->e_shnum = my_be16toh(ehdr->e_shnum);
	ehdr->e_shstrndx = my_be16toh(ehdr->e_shstrndx);
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
 * read_elf32_be_prog - Convert a 32-bit ELF header from big-endian to host
 * byte order.
 * This function takes a pointer to a 32-bit ELF header big-endian byte order
 * and converts various header fields to the host byte order. It is used to
 * ensure
 * correct interpretation of the header on the host system.
 *
 * @phdr: A pointer to a 32-bit program header in big-endian byte order.
 */
void read_elf32_be_prog(Elf32_Phdr *phdr)
{
	phdr->p_type = my_be32toh(phdr->p_type);
	phdr->p_offset = my_be32toh(phdr->p_offset);
	phdr->p_vaddr = my_be32toh(phdr->p_vaddr);
	phdr->p_paddr = my_be32toh(phdr->p_paddr);
	phdr->p_filesz = my_be32toh(phdr->p_filesz);
	phdr->p_memsz = my_be32toh(phdr->p_memsz);
	phdr->p_flags = my_be32toh(phdr->p_flags);
	phdr->p_align = my_be32toh(phdr->p_align);
}

/**
* set_prog_names - Retrieve the section names string table from an ELF file
*
* This function seeks the section names string table in ELF file and returns
* a pointer to it.It can handle both 32-bit and 64-bit ELF files, adjusting its
* behavior based on the provided parameters.
*
* @is_32bits: Indicates whether the ELF file is 32-bit (true) or 64-bit (false)
* @file: A pointer to the open ELF file.
* @elf_header32: The 32-bit ELF header (if applicable).
* @elf_header64: The 64-bit ELF header (if applicable).
*
* Return: A pointer to the section names string table.
*/
char *set_prog_names(int is_32bits, FILE *file, Elf_Ehdr elf_header)
{
	Elf_Phdr prog_header;
	char *program_names = NULL;

	if (is_32bits)
	{
		/* 32 bits Small Endian */
		if (elf_header.elf_header32.e_ident[EI_DATA] == ELFDATA2LSB)
		{
			/* Store sections names  */
			program_names = get_program_name(prog_header, file, elf_header, 1, 0);
		}
		/* 32 bits Big Endian */
		if (elf_header.elf_header32.e_ident[EI_DATA] == ELFDATA2MSB)
		{
			/* read with conversion for big endian */
			read_elf32_be_prog(&prog_header.prog_header32);
			program_names = get_program_name(prog_header, file, elf_header, 1, 1);
		}
	}
	else /* 64 bits */
		program_names = get_program_name(prog_header, file, elf_header, 0, 0);
	return (program_names);
}

/**
 * loop_print - Iterate through and print information about ELF section headers
 *
 * This function iterates through the section headers of an ELF (Executable and
 * Linkable Format) file, reading and printing details such as section names,
 * types,
 * addresses, offsets, sizes, and other attributes. It can handle both 32-bit
 * and 64-bit ELF files.
 *
 * @is_32bits: Indicates whether the ELF file is 32-bit (true) or 64-bit (false)
 * @file: A pointer to the open ELF file.
 * @elf_header32: The 32-bit ELF header (if applicable).
 * @elf_header64: The 64-bit ELF header (if applicable).
 * @section_names: A pointer to the section names string table.
 */
void loop_print2(int is_32bits, FILE *file, Elf_Ehdr elf_header)
{
	int index = 0;

	if (is_32bits)
	{
		for (index = 0; index < elf_header.elf_header32.e_phnum; index++)
		{
			Elf32_Phdr prog_header32;
			/* Store program header */
			fread(&prog_header32, sizeof(Elf32_Phdr), 1, file);

			/* convert program header for big endian */
			if (elf_header.elf_header32.e_ident[EI_DATA] == ELFDATA2MSB)
				read_elf32_be_prog(&prog_header32);

			print_Program_Info_32bits(prog_header32);
			print_interp32(prog_header32, file);
		}
	}
	else
	{
		Elf64_Phdr prog_header64;

		for (index = 0; index < elf_header.elf_header64.e_phnum; index++)
		{
			fread(&prog_header64, sizeof(Elf64_Phdr), 1, file);

			print_Program_Info_64bits(prog_header64);
			print_interp64(prog_header64, file);
		}
	}
}

int print_interp32(Elf32_Phdr prog_header32, FILE *file)
{
	char interp[MAX_INTERP_SIZE];
	if (prog_header32.p_type == PT_INTERP)
	{
		if (prog_header32.p_filesz <= MAX_INTERP_SIZE)
		{
			/* Guardo la posicion actual */
			long current_pos = ftell(file);

			/* Mover el puntero posicio del programa intérprete */
			fseek(file, prog_header32.p_offset, SEEK_SET);

			/* Leer el programa intérprete en la matriz interp */
			fread(interp, prog_header32.p_filesz, 1, file);
			interp[prog_header32.p_filesz] = '\0';

			printf("      [Requesting program interpreter: %s]\n", interp);

			/* Recupero la posicion guardada */
			fseek(file, current_pos, SEEK_SET);
		}
		else
		{
			fprintf(stderr, "MAX_INTERP_SIZE.\n");
			fclose(file);
			return 1;
		}
	}
	return (0);
}

int print_interp64(Elf64_Phdr prog_header64, FILE *file)
{
	char interp[MAX_INTERP_SIZE];

	if (prog_header64.p_type == PT_INTERP)
	{
		if (prog_header64.p_filesz <= MAX_INTERP_SIZE)
		{
			/* Guardo la posicion actual */
			long current_pos = ftell(file);

			/* Mover el puntero posicio del programa intérprete */
			fseek(file, prog_header64.p_offset, SEEK_SET);

			/* Leer el programa intérprete en la matriz interp */
			fread(interp, prog_header64.p_filesz, 1, file);
			interp[prog_header64.p_filesz] = '\0';

			printf("      [Requesting program interpreter: %s]\n", interp);

			/* Recupero la posicion guardada */
			fseek(file, current_pos, SEEK_SET);
		}
		else
		{
			fprintf(stderr, "MAX_INTERP_SIZE.\n");
			fclose(file);
			return 1;
		}
	}
	return (0);
}