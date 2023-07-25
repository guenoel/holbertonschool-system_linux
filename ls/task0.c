#include "hls.h"

/**
 * main- fonction principale
 * no arguments yet
 *
 * Return: 0 if all good 1 if errors
 */


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		openprintclosedir(".", argv[0]);
	}
	else
	{
		for(int i = 1; i < argc; i++ )
		{
			openprintclosedir(argv[i], argv[0]);
		}
	}
	return (0);
}
