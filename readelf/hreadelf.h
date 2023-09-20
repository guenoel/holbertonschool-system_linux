#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

/* ------------------- Task 0-hreadelf.c ----------------------------------*/
/**
* struct header32 - Represents a 32-bit ELF header.
* Structure represents a 32-bit ELF (Executable and Linkable Format) header.
* It includes a member named 'ehdr' of type 'Elf32_Ehdr', which holds the main
* ELF header information.
* ELF header provides essential information about the ELF file format, such
* as its class (32-bit), data encoding, file type, machine architecture, entry
* point, program header and section header information, and more.
* @ehdr: structure is typically used for parsing and working with 32-bit ELF
*/
typedef struct header32
{
	Elf32_Ehdr ehdr;
} Elf32_Header;

/**
* struct header64 - Represents a 64-bit ELF header.
* Structure represents a 64-bit ELF (Executable and Linkable Format) header.
* It includes a member named 'ehdr' of type 'Elf64_Ehdr', which holds the main
* ELF header information.
* ELF header provides essential information about the ELF file format, such
* as its class (64-bit), data encoding, file type, machine architecture, entry
* point, program header and section header information, and more.
* @ehdr: structure is typically used for parsing and working with 64-bit ELF
*/
typedef struct header64
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

/* Functions 0-hreadelf.c */
void print_elf32_header(Elf32_Header *elf32);
void print_elf64_header(Elf64_Header *elf64);
void read_elf32_be_header0(Elf32_Header *elf32, FILE *file);
int main(int argc, char *argv[]);

/* ------------------- Task 1-hreadelf.c ----------------------------------*/

/**
* struct Shdr32 - Represents a 32-bit ELF section header entry.
* This structure represents a section header entry in a 32-bit ELF (Executable
* and Linkable Format) file. It stores information about a specific section in
* the ELF file, including its name, type, flags, memory address, file offset,
* size, linkage, additional information, alignment, and entry size.
*
* The section header is a crucial part of the ELF file format, as it defines
* the layout and properties of various sections within the file, such as code,
* data, and symbol tables.
* Structure is typically used for parsing and working with 32-bit ELF
*
* @sh_name: Section name, index in string tbl
* @sh_type: Type of section
* @sh_flags: Miscellaneous section attributes
* @sh_addr: Section virtual addr at execution
* @sh_offset: Section file offset
* @sh_size: Size of section in bytes
* @sh_link: Index of another section
* @sh_info: Additional section information
* @sh_addralign:Section alignment
* @sh_entsize: Entry size if section holds table
*/
typedef struct Shdr32
{
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
} MyElf32_Shdr;

/**
* struct Shdr64 - Represents a 64-bit ELF section header entry.
* This structure represents a section header entry in a 32-bit ELF (Executable
* and Linkable Format) file. It stores information about a specific section in
* the ELF file, including its name, type, flags, memory address, file offset,
* size, linkage, additional information, alignment, and entry size.
*
* The section header is a crucial part of the ELF file format, as it defines
* the layout and properties of various sections within the file, such as code,
* data, and symbol tables.
* Structure is typically used for parsing and working with 64-bit ELF.
*
* @sh_name: Section name, index in string tbl
* @sh_type: Type of section
* @sh_flags: Miscellaneous section attributes
* @sh_addr: Section virtual addr at execution
* @sh_offset: Section file offset
* @sh_size: Size of section in bytes
* @sh_link: Index of another section
* @sh_info: Additional section information
* @sh_addralign:Section alignment
* @sh_entsize: Entry size if section holds table
*/
typedef struct Shdr64
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


typedef union _Elf_Ehdr
{
	Elf32_Ehdr elf_header32;
	Elf64_Ehdr elf_header64;
} Elf_Ehdr;

typedef union _Elf_Shdr
{
	Elf32_Shdr sect_header32;
	Elf64_Shdr sect_header64;
} Elf_Shdr;

typedef union _Elf_Phdr
{
	Elf32_Phdr prog_header32;
	Elf64_Phdr prog_header64;
} Elf_Phdr;

/* Functions 1-hreadelf.c */
void read_elf32_be_section(Elf32_Shdr *section_header32);
void read_elf32_be_header(Elf32_Ehdr *ehdr);
char *set_section_names(int is_32bits, FILE *file, Elf32_Ehdr elf_header32,
						Elf64_Ehdr elf_header64);
void loop_print(int is_32bits, FILE *file, Elf32_Ehdr elf_header32,
				Elf64_Ehdr elf_header64, char *section_names);

/* Functions 1-hreadelf_print.c*/
void printKeyToFlags_32bits(void);
void printKeyToFlags_64bits(void);
void print_Section_Info_32bits(int index, char *name,
								Elf32_Shdr section_header);
void print_Section_Info_64bits(int index, char *name,
								Elf64_Shdr section_header);
void print_header(int is_32bits, FILE *file, Elf32_Ehdr elf_header32,
					Elf64_Ehdr elf_header64, off_t sect_table_offset);
void print_header2(int is_32bits, FILE *file, Elf_Ehdr elf_header);

/* Functions 1-hreadelf_tools.c */
char *get_section_name32(Elf32_Shdr section_header, FILE *file,
						Elf32_Ehdr elf_header32, int is_big_endian);
char *get_section_name64(Elf64_Shdr section_header, FILE *file,
						Elf64_Ehdr elf_header64);
const char *getSectionTypeName(unsigned int sh_type);
const char *getSectionFlags(unsigned int sh_flags);

/* Functions 2-hreadelf */
#define MAX_INTERP_SIZE 1024

char *get_program_name(Elf_Phdr prog_header, FILE *file,
						Elf_Ehdr elf_header, int is_32bits, int is_big_endian);
char *set_prog_names(int is_32bits, FILE *file, Elf_Ehdr elf_header);
void loop_print2(int is_32bits, FILE *file, Elf_Ehdr elf_header);
char *get_section_name2(Elf_Shdr section_header, FILE *file,
						Elf_Ehdr elf_header, int is_32bits, int is_big_endian);
void read_elf32_be_prog(Elf32_Phdr *phdr);
void print_Program_Info_32bits(Elf32_Phdr prog_header);
void print_Program_Info_64bits(Elf64_Phdr prog_header);
int print_interp32(Elf32_Phdr program_header32, FILE *file);
int print_interp64(Elf64_Phdr program_header64, FILE *file);
const char *getProgramTypeName(unsigned int p_type);
#endif /* HELF_H */
