#include "hls.h"

/**
 * _count - concatener un string a la suite d un string
 * @str: un string
 *
 * Return: le string concaténé
 */

int _count(char *str)
{
	int c;

	for (c = 0; str[c] != '\0'; c++)
		;
	return (c);
}

/**
 * _strcat - concatener un string a la suite d un string
 * @dest: string destination
 * @src: string source
 *
 * Return: le string concaténé
 */

char *_strcat(char *dest, char *src)
{
	int a, b, i, j;

	a = _count(src);
	b = _count(dest);
	for (i = b, j = 0; src[j] != '\0'; i++, j++)
	{
		dest[i] = src[j];
	}
	dest[a + b + 1] = '\0';
	return (dest);
}
