#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include "hnm.h"


const char *get_symbol_type_32(uint8_t info, Elf32_Sym sym, Elf32_Shdr *shdr)
{
	if (ELF32_ST_BIND(info) == STB_GNU_UNIQUE)
		return ("u");
	else if (ELF32_ST_BIND(info) == STB_WEAK && ELF32_ST_TYPE(info) == STT_OBJECT)
	{
		if (sym.st_shndx == SHN_UNDEF)
			return ("v");
		else
			return ("V");
	}
	else if (ELF32_ST_BIND(info) == STB_WEAK)
	{
		if (sym.st_shndx == SHN_UNDEF)
			return ("w");
		else
			return ("W");
	}
	else if (sym.st_shndx == SHN_UNDEF)
		return ("U");
	else if (sym.st_shndx == SHN_ABS)
		return ("A");
	else if (sym.st_shndx == SHN_COMMON)
		return ("C");
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return ("B");
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		return ("R");
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		return ("D");
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
	{
		if (ELF32_ST_BIND(info) == STB_GLOBAL)
			return ("T");
		else
			return ("t");
	}
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
	{
		return ("D");
	}
	else
	{
		return ("T");
	}
}

void process_symbols_32bit(Elf32_Ehdr *ehdr, void *map, const char *filename)
{
	int i;
	Elf32_Sym *symtab;
	char *strtab_data;
	int num_symbols;
	Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)map + ehdr->e_shoff);
	char *shstrtab = (char *)map + shdr[ehdr->e_shstrndx].sh_offset;

	/* busca seccion (SHT_SYMTAB) y la tabla de cadenas asociada (SHT_STRTAB) */
	Elf32_Shdr *symtab_section = NULL;
	Elf32_Shdr *strtab_section = NULL;

	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			symtab_section = &shdr[i];
		}
		else if (shdr[i].sh_type == SHT_STRTAB && strcmp(shstrtab + shdr[i].sh_name, ".strtab") == 0)
		{
			strtab_section = &shdr[i];
		}
	}

	if (!symtab_section || !strtab_section)
	{
		fprintf(stderr, "./hnm: %s: no symbols\n", filename);
		return;
	}

	/* Acceso tabla de símbolos y tabla de str */
	symtab = (Elf32_Sym *)((char *)map + symtab_section->sh_offset);
	strtab_data = (char *)((char *)map + strtab_section->sh_offset);

	num_symbols = symtab_section->sh_size / sizeof(Elf32_Sym);

	/* Recorre los símbolos y muestra la información */
	for (i = 0; i < num_symbols; i++)
	{
		/* if (symtab[i].st_name != 0 && (symtab[i].st_value != 0 || symtab[i].st_size != 0) && strcmp(strtab_data + symtab[i].st_name, "main.c") != 0) */
		/* if ((symtab[i].st_name != 0 || (symtab[i].st_value != 0 || symtab[i].st_size != 0)) && strcmp(strtab_data + symtab[i].st_name, "main.c") != 0) */
		if ((symtab[i].st_name != 0) && strcmp(strtab_data + symtab[i].st_name, "main.c") != 0)
		{
			char *symbol_name = strtab_data + symtab[i].st_name;
			const char *symbol_type_str = get_symbol_type_32(symtab[i].st_info, symtab[i], shdr);

			if (symbol_type_str[0] != 'U')
			{
				printf("%08x %s %s\n", symtab[i].st_value, symbol_type_str, symbol_name);
			}
			else
			{
				printf("         %s %s\n", symbol_type_str, symbol_name);
			}
		}
	}
}

const char *get_symbol_type_64(uint8_t info, Elf64_Sym sym, Elf64_Shdr *shdr)
{
	if (ELF64_ST_BIND(info) == STB_GNU_UNIQUE)
		return ("u");
	else if (ELF64_ST_BIND(info) == STB_WEAK && ELF64_ST_TYPE(info) == STT_OBJECT)
	{
		if (sym.st_shndx == SHN_UNDEF)
			return ("v");
		else
			return ("V");
	}
	else if (ELF64_ST_BIND(info) == STB_WEAK)
	{
		if (sym.st_shndx == SHN_UNDEF)
			return ("w");
		else
			return ("W");
	}
	else if (sym.st_shndx == SHN_UNDEF)
		return ("U");
	else if (sym.st_shndx == SHN_ABS)
		return ("A");
	else if (sym.st_shndx == SHN_COMMON)
		return ("C");
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
	{
		if (ELF64_ST_BIND(info) == STB_GLOBAL)
			return ("B");
		else
			return ("b");
	}
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
	{
		if (ELF64_ST_BIND(info) == STB_GLOBAL)
			return ("R");
		else
			return ("r");
	}
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
	{
		if (ELF64_ST_BIND(info) == STB_GLOBAL)
			return ("D");
		else
			return ("d");
	}
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
	{
		if (ELF64_ST_BIND(info) == STB_GLOBAL)
			return ("T");
		else
			return ("t");
	}
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
	{
		return ("d");
	}
	else
	{
		return ("t");
	}
}

void process_symbols_64bit(Elf64_Ehdr *ehdr, void *map, const char *filename)
{
	int i;
	Elf64_Sym *symtab;
	char *strtab_data;
	int num_symbols;
	Elf64_Shdr *shdr = (Elf64_Shdr *)((char *)map + ehdr->e_shoff);

	/* busca seccion (SHT_SYMTAB) y la tabla de cadenas asociada (SHT_STRTAB) */
	Elf64_Shdr *symtab_section = NULL;
	Elf64_Shdr *strtab_section = NULL;

	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
			symtab_section = &shdr[i];
		else if (shdr[i].sh_type == SHT_STRTAB)
			strtab_section = &shdr[i];
	}

	if (!symtab_section || !strtab_section)
	{
		fprintf(stderr, "./hnm: %s: no symbols\n", filename);
		return;
	}

	/* Acceso tabla de símbolos y tabla de str */
	symtab = (Elf64_Sym *)((char *)map + symtab_section->sh_offset);
	strtab_data = (char *)((char *)map + strtab_section->sh_offset);

	num_symbols = symtab_section->sh_size / sizeof(Elf64_Sym);

	/* Recorre los símbolos y muestra la información */
	for (i = 0; i < num_symbols; i++)
	{
		/* Verifica si el nombre del símbolo contiene la extensión ".c" y omite la impresión */
		char *symbol_name = strtab_data + symtab[i].st_name;
		if (strstr(symbol_name, ".c") != NULL)
			continue;

		if (symtab[i].st_name)
		{
			const char *symbol_type_str = get_symbol_type_64(symtab[i].st_info, symtab[i], shdr);

			if (symbol_type_str[0] != 'U' && symbol_type_str[0] != 'w')
				printf("%16.16lx %s %s\n", symtab[i].st_value, symbol_type_str, symbol_name);
			else
				printf("                 %s %s\n", symbol_type_str, symbol_name);
		}
	}
}

uint32_t byteswap32(uint32_t value)
{
	return (((value & 0x000000FF) << 24) |
		((value & 0x0000FF00) << 8) |
		((value & 0x00FF0000) >> 8) |
		((value & 0xFF000000) >> 24));
}

uint16_t byteswap16(uint16_t value)
{
	return (((value & 0x00FF) << 8) |
		((value & 0xFF00) >> 8));
}

void process_symbols_32bit_big_endian(Elf32_Ehdr *ehdr, void *map, const char *filename)
{
	int i;
	Elf32_Sym *symtab;
	char *strtab_data;
	int num_symbols;
	Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)map + byteswap32(ehdr->e_shoff));

	/* Busca la sección (SHT_SYMTAB) y la tabla de cadenas asociada (SHT_STRTAB). */
	Elf32_Shdr *symtab_section = NULL;
	Elf32_Shdr *strtab_section = NULL;

	for (i = 0; i < byteswap16(ehdr->e_shnum); i++)
	{
		if (byteswap32(shdr[i].sh_type) == SHT_SYMTAB)
		{
			symtab_section = &shdr[i];
		}
		else if (byteswap32(shdr[i].sh_type) == SHT_STRTAB)
		{
			strtab_section = &shdr[i];
		}
	}

	if (!symtab_section || !strtab_section)
	{
		fprintf(stderr, "./hnm: %s: no symbols\n", filename);
		return;
	}
	/* Acceso a la tabla de símbolos y tabla de cadenas. */
	symtab = (Elf32_Sym *)((char *)map + byteswap32(symtab_section->sh_offset));
	strtab_data = (char *)((char *)map + byteswap32(strtab_section->sh_offset));
	num_symbols = byteswap32(symtab_section->sh_size) / sizeof(Elf32_Sym);

	/* Recorre los símbolos y muestra la información. */

	for (i = 0; i < num_symbols; i++)
	{
		if (byteswap32(symtab[i].st_name) != 0)
		{
			char *symbol_name = strtab_data + byteswap32(symtab[i].st_name);
			const char *symbol_type_str = get_symbol_type_32(symtab[i].st_info, symtab[i], shdr);

			if (symbol_type_str[0] != 'U')
			{
				printf("%08x %s %s\n", byteswap32(symtab[i].st_value), symbol_type_str, symbol_name);
			}
			else
			{
				printf("         %s %s\n", symbol_type_str, symbol_name);
			}
		}
	}
}

int analyze_32bit_elf(Elf32_Ehdr *ehdr, void *map, const char *filename)
{

	/* printf("32 bits, "); */
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
	{
		/* printf("little-endian.\n"); */
		process_symbols_32bit(ehdr, map, filename);
	}
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		process_symbols_32bit_big_endian(ehdr, map, filename);
	}
	else
	{
		printf("endianness unknown.\n");
	}

	return (0);
}

int analyze_64bit_elf(Elf64_Ehdr *ehdr, void *map, const char *filename)
{

	/* printf("64 bits, "); */
	if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB)
	{
		/* printf("little-endian.\n"); */
		process_symbols_64bit(ehdr, map, filename);

	}
	else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		printf("big-endian.\n");
	}
	else
	{
		printf("endianness unknown.\n");
	}
	/* llamar funcion se ocupara procesar sinbolos y salida */

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
	ehdr32 = (Elf32_Ehdr *)map;
	ehdr64 = (Elf64_Ehdr *)map;
	if (ehdr32->e_ident[EI_CLASS] == ELFCLASS32)
		return (analyze_32bit_elf(ehdr32, map, filename));
	else if (ehdr64->e_ident[EI_CLASS] == ELFCLASS64)
		return (analyze_64bit_elf(ehdr64, map, filename));
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
		fprintf(stderr, "hnm: %s [objfile...]\n", argv[0]);
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
