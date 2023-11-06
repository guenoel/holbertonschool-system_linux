#include "hreadelf.h"

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
void print_Section_Info_32bits(int index, Elf32_Shdr section_header,
								char *name)
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
void print_Section_Info_64bits(int index, Elf64_Shdr section_header,
								char *name)
{
	const char *flags = getSectionFlags(section_header.sh_flags);

	printf("  [%2d] %-17s %-15s %016lx %06lx %06lx %02lx %s %2d %3d %2ld\n",
		index, name, getSectionTypeName(section_header.sh_type),
		section_header.sh_addr, section_header.sh_offset,
		section_header.sh_size, section_header.sh_entsize, flags,
		section_header.sh_link, section_header.sh_info,
		section_header.sh_addralign);
}

