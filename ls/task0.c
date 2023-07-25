#include "hls.h"

/**
 * main- fonction principale
 * no arguments yet
 *
 * Return: 0 if all good 1 if errors
 */


int main(int argc, char *argv[])
{
	int i;

	if (argc == 1)
	{
		openprintclosedir(".", argv[0]);
	}
	else
	{
		for(i = 1; i < argc; i++ )
		{
			openprintclosedir(argv[i], argv[0]);
		}
	}
	return (0);
}
