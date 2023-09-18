#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

/* Task 0-hreadelf.c */
typedef struct
{
	Elf32_Ehdr ehdr;
} Elf32_Header;

typedef struct
{
	Elf64_Ehdr ehdr;
} Elf64_Header;

/* Functions 0-hreadelf_tools.c */
const char *get_osabi_name(uint8_t osabi);
const char *get_osabi_version(uint8_t version);
const char *get_osabi_type(uint16_t type);
const char *get_osabi_machine(uint16_t machine);
const char *get_osabi_data(uint8_t data);

/* Functions 0-hreadelf_convert.c */
uint16_t my_be16toh(uint16_t value);
uint32_t my_be32toh(uint32_t value);

/* Task 1-hreadelf.c */
typedef struct
{
	Elf32_Word sh_name;		 /* Section name, index in string tbl */
	Elf32_Word sh_type;		 /* Type of section */
	Elf32_Word sh_flags;	 /* Miscellaneous section attributes */
	Elf32_Addr sh_addr;		 /* Section virtual addr at execution */
	Elf32_Off sh_offset;	 /* Section file offset */
	Elf32_Word sh_size;		 /* Size of section in bytes */
	Elf32_Word sh_link;		 /* Index of another section */
	Elf32_Word sh_info;		 /* Additional section information */
	Elf32_Word sh_addralign; /* Section alignment */
	Elf32_Word sh_entsize;	 /* Entry size if section holds table */
} MyElf32_Shdr;

typedef struct
{
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
} MyElf64_Shdr;

const char *getSectionTypeName(unsigned int sh_type);
const char *getSectionFlags(unsigned int sh_flags);
void print_Section_Info_32bits(int index,
							   Elf32_Shdr section_header, char *name);
void print_Section_Info_64bits(int index,
							   Elf64_Shdr section_header, char *name);
void printKeyToFlags_32bits(void);
void printKeyToFlags_64bits(void);
char *get_section_name32(Elf32_Shdr section_header, FILE *file);
char *get_section_name64(Elf64_Shdr section_header, FILE *file);

void read_elf32_be_section(Elf32_Shdr *section_header32);
void read_elf32_be_header(Elf32_Ehdr *ehdr);
uint16_t my_be16toh(uint16_t value);
uint32_t my_be32toh(uint32_t value);
char *get_section_name32_big(Elf32_Shdr section_header, FILE *file);
void loop_print(int is_32bit, FILE *file, Elf32_Ehdr elf_header32,
				Elf64_Ehdr elf_header64, char *section_names);
void print_header(int is_32bit, FILE *file, Elf32_Ehdr elf_header32,
				  Elf64_Ehdr elf_header64, off_t section_table_offset);
char *set_section_names(int is_32bit, FILE *file, Elf32_Ehdr elf_header32,
						Elf64_Ehdr elf_header64);

#endif /* HELF_H */
