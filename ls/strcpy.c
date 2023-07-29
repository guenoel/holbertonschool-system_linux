#include "hls.h"

/**
 * _strcpy - print
 * @dest: array
 * @src: element strings from elements
 *
 * Return: la meme chose
 */

char *_strcpy(char *dest, char *src)
{
	int c, i;

	c = 0;
	while (src[c] != '\0')
	{
		c++;
	}
	i = 0;
	while (i <= c)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
