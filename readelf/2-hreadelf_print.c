#include "hreadelf.h"


/**
* print_header - Print information about ELF section headers.
*
* Prints information about the section headers of an ELF (Executable
* and Linkable Format) file. It provides details such as the number of section
* headers, their names, types, addresses, offsets, sizes, and other attributes
*
* @is_32bits: Indicates whether the ELF file is 32-bit (true) or 64-bit (false)
* @file: A pointer to the open ELF file.
* @elf_header32: The 32-bit ELF header (if applicable).
* @elf_header64: The 64-bit ELF header (if applicable).
* @sect_table_offset: offset of the section header table within the file.
*/
void print_header2(int is_32bits, FILE *file, Elf_Ehdr elf_header)
{
	printf("Elf file type is %s\n", get_osabi_type(is_32bits ? elf_header.elf_header32.e_type : elf_header.elf_header64.e_type));
	if (is_32bits)
		printf("Entry point 0x%x\n", elf_header.elf_header32.e_entry);
	else
		printf("Entry point 0x%lx\n", elf_header.elf_header64.e_entry);
	/* Imprimir la información sobre la tabla de secciones y encabezado */
	printf("There are %u program headers, starting at offset %ld:\n\n",
		is_32bits ? elf_header.elf_header32.e_phnum : elf_header.elf_header64.e_phnum,
		is_32bits ? (long)elf_header.elf_header32.e_phoff : (long)elf_header.elf_header64.e_phoff);
	if (is_32bits)
	{
		fseek(file, elf_header.elf_header32.e_shoff, SEEK_SET);
		printf("Program Headers:\n");
		printf("  Type           Offset   VirtAddr   PhysAddr");
		printf("   FileSiz MemSiz  Flg Align\n");
	}
	else
	{
		fseek(file, elf_header.elf_header64.e_shoff, SEEK_SET);
		printf("Program Headers:\n");
		printf("  Type           Offset   VirtAddr           PhysAddr");
		printf("           FileSiz  MemSiz   Flg Align\n");
	}
}

/**
* print_Section_Info_32bits - Print information about an ELF32 section.
* This function prints detailed information about a specific ELF32 section,
* including its index,
* name, type, address, offset, size, entry size, flags, link, info, and
* address alignment.
* @index: The index of the section.
* @section_header: The ELF32 section header structure.
* @name:The name of the section.
*/
void print_Section_Info_32bits(int index, char *name,
								Elf32_Shdr section_header)
{
	const char *flags = getSectionFlags(section_header.sh_flags);

	printf("  [%2d] %-17s %-15s %08x %06x %06x %02x %s %2d %3d %2d\n",
		index, name, getSectionTypeName(section_header.sh_type),
		section_header.sh_addr, section_header.sh_offset,
		section_header.sh_size, section_header.sh_entsize, flags,
		section_header.sh_link, section_header.sh_info,
		section_header.sh_addralign);
}

/**
* print_Section_Info_64bits - Print information about an ELF64 section.
* This function prints detailed information about a specific ELF64 section,
* including its index,
* name, type, address, offset, size, entry size, flags, link, info, and
* address alignment.
* @index: The index of the section.
* @section_header: The ELF64 section header structure.
* @name:The name of the section.
*/
void print_Section_Info_64bits(int index, char *name,
								Elf64_Shdr section_header)
{
	const char *flags = getSectionFlags(section_header.sh_flags);

	printf("  [%2d] %-17s %-15s %016lx %06lx %06lx %02lx %s %2d %3d %2ld\n",
		index, name, getSectionTypeName(section_header.sh_type),
		section_header.sh_addr, section_header.sh_offset,
		section_header.sh_size, section_header.sh_entsize, flags,
		section_header.sh_link, section_header.sh_info,
		section_header.sh_addralign);
}

/**
* printKeyToFlags_32bits - Print a key to ELF32 flags.
* Prints a key that describes the meaning of individual flags in ELF32 header
* structures.
* It helps interpret flags such as write (W), allocate (A), execute (X),
* merge (M), strings (S), and others.
* Additionally, it provides information about flags related to OS processing
* and processor-specific flags.
*/
void printKeyToFlags_32bits(void)
{
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude),");
	printf(" x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific),");
	printf(" p (processor specific)\n");
}

/**
* printKeyToFlags_64bits - Print a key to ELF64 flags.
* This function prints a key that describes the meaning of individual flags
* in ELF64 header structures.
* It helps interpret flags such as write (W), allocate (A), execute (X),
* merge (M), strings (S), and others.
* Additionally, it provides information about flags related to OS processing,
* processor-specific flags,
* and flags specific to 64-bit ELF files.
*/
void printKeyToFlags_64bits(void)
{
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings),");
	printf(" l (large)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude),");
	printf(" x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific),");
	printf(" p (processor specific)\n");
}

/**
* print_Section_Info_32bits - Print information about an ELF32 section.
* This function prints detailed information about a specific ELF32 section,
* including its index,
* name, type, address, offset, size, entry size, flags, link, info, and
* address alignment.
* @index: The index of the section.
* @section_header: The ELF32 section header structure.
* @name:The name of the section.
*/
void print_Program_Info_32bits(Elf32_Phdr prog_header)
{
	printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %c%c%c 0x%01x\n",
		getProgramTypeName(prog_header.p_type),
		prog_header.p_offset,
		prog_header.p_vaddr, 
		prog_header.p_paddr,
		prog_header.p_filesz,
		prog_header.p_memsz,
		(prog_header.p_flags & PF_R) ? 'R' : ' ',
		(prog_header.p_flags & PF_W) ? 'W' : ' ',
		(prog_header.p_flags & PF_X) ? 'E' : ' ',
		prog_header.p_align);
}

/**
* print_Section_Info_64bits - Print information about an ELF64 section.
* This function prints detailed information about a specific ELF64 section,
* including its index,
* name, type, address, offset, size, entry size, flags, link, info, and
* address alignment.
* @index: The index of the section.
* @section_header: The ELF64 section header structure.
* @name:The name of the section.
*/
void print_Program_Info_64bits(Elf64_Phdr prog_header)
{
	printf("  %-14s 0x%06lx 0x%016lx 0x%016lx 0x%06lx 0x%06lx %c%c%c 0x%01lx\n",
		getProgramTypeName(prog_header.p_type),
		(unsigned long)prog_header.p_offset,
		(unsigned long)prog_header.p_vaddr, 
		(unsigned long)prog_header.p_paddr,
		(unsigned long)prog_header.p_filesz,
		(unsigned long)prog_header.p_memsz,
		(prog_header.p_flags & PF_R) ? 'R' : ' ',
		(prog_header.p_flags & PF_W) ? 'W' : ' ',
		(prog_header.p_flags & PF_X) ? 'E' : ' ',
		(unsigned long)prog_header.p_align);
}
