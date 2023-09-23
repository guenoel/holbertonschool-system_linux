#include <elf.h>
#include "hreadelf.h"
#include <endian.h>

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
