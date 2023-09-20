#include "hreadelf.h"

/**
* get_section_name32 - Retrieve the name of an ELF32 section big endian.
* This function reads and returns the name of an ELF32 section based on the
* provided section headerand file pointer.
* @section_header: The ELF32 section header structure.
* @file: A pointer to the ELF file.
* @elf_header32: The 32-bit ELF header (if applicable).
* @is_big_endian: flag for big endian detection
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_section_name2(Elf_Shdr section_header, FILE *file,
						Elf_Ehdr elf_header, int is_32bits, int is_big_endian)
{
	char *section_names = NULL;

	if (is_32bits)
	{
	/* Start of section header + section index * size of a section */
	fseek(file, elf_header.elf_header32.e_shoff + elf_header.elf_header32.e_shstrndx *
			elf_header.elf_header32.e_shentsize, SEEK_SET);
	/* Store section header in struct */
	fread(&section_header, 1, sizeof(section_header), file);
	/* Big endian conversion */
	if (is_big_endian)
		read_elf32_be_section(&section_header.sect_header32);
	/* Allocate space for the string */
	section_names = (char *)malloc(section_header.sect_header32.sh_size);
	fseek(file, section_header.sect_header32.sh_offset, SEEK_SET);
	fread(section_names, 1, section_header.sect_header32.sh_size, file);
	
	} else {
	/* Start of section header + section index * size of a section */
	fseek(file, elf_header.elf_header64.e_shoff + elf_header.elf_header64.e_shstrndx *
			elf_header.elf_header64.e_shentsize, SEEK_SET);
	/* Store section header */
	fread(&section_header, 1, sizeof(section_header), file);
	/* Allocate space for the string */
	section_names = (char *)malloc(section_header.sect_header64.sh_size);
	/* Move pointer to the start of the section */
	fseek(file, section_header.sect_header64.sh_offset, SEEK_SET);
	/* Store all section names in a string with multiple NULL terminating char */
	/* TODO: or store all section header ? */
	fread(section_names, 1, section_header.sect_header64.sh_size, file);
	}
	return (section_names);
}

/**
* get_section_name32 - Retrieve the name of an ELF32 section big endian.
* This function reads and returns the name of an ELF32 section based on the
* provided section headerand file pointer.
* @section_header: The ELF32 section header structure.
* @file: A pointer to the ELF file.
* @elf_header32: The 32-bit ELF header (if applicable).
* @is_big_endian: flag for big endian detection
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_program_name(Elf_Phdr prog_header, FILE *file,
						Elf_Ehdr elf_header, int is_32bits, int is_big_endian)
{
	char *section_names = NULL;

	if (is_32bits)
	{
	/* Start of section header + section index * size of a section */
	fseek(file, elf_header.elf_header32.e_shoff + elf_header.elf_header32.e_shstrndx *
			elf_header.elf_header32.e_shentsize, SEEK_SET);
	/* Store section header in struct */
	fread(&prog_header.prog_header32, 1, sizeof(prog_header.prog_header32), file);
	/* Big endian conversion */
	if (is_big_endian)
		read_elf32_be_prog(&prog_header.prog_header32);
	/* Allocate space for the string */
	section_names = (char *)malloc(prog_header.prog_header32.p_memsz);
	fseek(file, prog_header.prog_header32.p_offset, SEEK_SET);
	fread(section_names, 1, prog_header.prog_header32.p_memsz, file);
	
	} else {
	/* Start of section header + section index * size of a section */
	fseek(file, elf_header.elf_header64.e_shoff + elf_header.elf_header64.e_shstrndx *
			elf_header.elf_header64.e_shentsize, SEEK_SET);
	/* Store section header */
	fread(&prog_header.prog_header64, 1, sizeof(prog_header.prog_header64), file);
	/* Allocate space for the string */
	section_names = (char *)malloc(prog_header.prog_header64.p_memsz);
	/* Move pointer to the start of the section */
	fseek(file, prog_header.prog_header64.p_offset, SEEK_SET);
	/* Store all section names in a string with multiple NULL terminating char */
	/* TODO: or store all section header ? */
	fread(section_names, 1, prog_header.prog_header64.p_memsz, file);
	}
	return (section_names);
}

/**
* get_section_name64 - Retrieve the name of an ELF64 section little endian.
* This function reads and returns the name of an ELF64 section based on the
* provided section headerand file pointer.
* @section_header: The ELF64 section header structure.
* @file: A pointer to the ELF file.
* @elf_header64: The 64-bit ELF header (if applicable).
* Return: A dynamically allocated string containing the section name.
* The caller is responsible for freeing the allocated memory.
*/
char *get_section_name64(Elf64_Shdr section_header, FILE *file,
						Elf64_Ehdr elf_header64)
{
	char *section_names = NULL;

	/* Start of section header + section index * size of a section */
	fseek(file, elf_header64.e_shoff + elf_header64.e_shstrndx *
			elf_header64.e_shentsize, SEEK_SET);
	/* Store section header */
	fread(&section_header, 1, sizeof(section_header), file);
	/* Allocate space for the string */
	section_names = (char *)malloc(section_header.sh_size);
	/* Move pointer to the start of the section */
	fseek(file, section_header.sh_offset, SEEK_SET);
	/* Store all section names in a string with multiple NULL terminating char */
	/* TODO: or store all section header ? */
	fread(section_names, 1, section_header.sh_size, file);
	return (section_names);
}

/**
* getSectionFlags - Convert ELF section flags to a string representation.
* This function converts the ELF section flags into a string representation.
* Each flag character represents a specific attribute, such as Write (W),
* Alloc (A),
* Execute (X), Merge (M), Strings (S), Info Link (I), and Exclude (E).
* Flags not present are represented by spaces.
* @sh_flags: The ELF section flags to be converted.
* Return: A string representation of the section flags.
*/
const char *getSectionFlags(unsigned int sh_flags)
{
	int i;
	static char flags[4];
	/* initalisation */
	for (i = 0; i < 3; i++)
		flags[i] = ' ';
	/* fill each character from the end with conditions */
	flags[3] = '\0';
	i = 2;

	if (sh_flags & SHF_STRINGS)
		flags[i--] = 'S';

	if (sh_flags & SHF_INFO_LINK)
		flags[i--] = 'I';

	if (sh_flags & SHF_MERGE)
		flags[i--] = 'M';

	if (sh_flags & SHF_EXECINSTR)
		flags[i--] = 'X';

	if (sh_flags & SHF_ALLOC)
		flags[i--] = 'A';

	if (sh_flags & SHF_WRITE)
		flags[i--] = 'W';

	if (sh_flags & SHF_EXCLUDE)
		flags[i--] = 'E';

	return (flags);
}

/**
* getSectionTypeName - Convert an ELF section type to a string representation.
* This function converts the ELF section type into a string representation.
* It returns human-readable names for known section types such as PROGBITS,
* RELA,NOTE, HASH, DYNSYM, STRTAB, and others. For unknown types, it returns
* "UNKNOWN".
* @sh_type: The ELF section type to be converted.
* Return: A string representation of the section type.
*/
const char *getSectionTypeName(unsigned int sh_type)
{
	switch (sh_type)
	{
	case SHT_NULL:         return "NULL";
	case SHT_PROGBITS:     return "PROGBITS";
	case SHT_RELA:         return "RELA";
	case SHT_NOTE:         return "NOTE";
	case SHT_HASH:         return "HASH";
	case SHT_DYNSYM:       return "DYNSYM";
	case SHT_STRTAB:       return "STRTAB";
	case SHT_REL:          return "REL";
	case SHT_NOBITS:       return "NOBITS";
	case SHT_SYMTAB:       return "SYMTAB";
	case SHT_INIT_ARRAY:   return "INIT_ARRAY";
	case SHT_FINI_ARRAY:   return "FINI_ARRAY";
	case DT_VERSYM:        return "VERSYM";
	case SHT_GNU_versym:   return "VERSYM";
	case DT_VERNEED:       return "VERNEED";
	case SHT_DYNAMIC:      return "DYNAMIC";
	case SHT_GNU_HASH:     return "GNU_HASH";
	case DT_VERDEF:        return "VERDEF";
	case SHT_LOOS + 0xffffff3: return "LOOS+ffffff3";
	case SHT_LOOS + 0xffffff1: return "LOOS+ffffff1";
	default:               return "UNKNOWN";
	}
}

/**
* getSectionTypeName - Convert an ELF section type to a string representation.
* This function converts the ELF section type into a string representation.
* It returns human-readable names for known section types such as PROGBITS,
* RELA,NOTE, HASH, DYNSYM, STRTAB, and others. For unknown types, it returns
* "UNKNOWN".
* @sh_type: The ELF section type to be converted.
* Return: A string representation of the section type.
*/
const char *getProgramTypeName(unsigned int p_type)
{
	switch (p_type)
	{
		case PT_NULL: return "NULL";
		case PT_LOAD: return "LOAD";
		case PT_DYNAMIC: return "DYNAMIC";
		case PT_INTERP: return "INTERP";
		case PT_NOTE: return "NOTE";
		case PT_SHLIB: return "SHLIB";
		case PT_PHDR: return "PHDR";
		case PT_TLS: return "TLS";
		case PT_GNU_EH_FRAME: return "GNU_EH_FRAME";
		case PT_GNU_STACK: return "GNU_STACK";
		case PT_GNU_RELRO: return "GNU_RELRO";
		default: return "UNKNOWN";
	}
}