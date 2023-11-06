#include "hnm.h"


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
