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
	int realargc = 0;

	char *options = getoptions(argc, argv);

	for(i = 1; i < argc; i++)
	{
		if(argv[i][0] != '-')
		{
			realargc++;
		}
	}

	if (realargc == 0)
	{
		openprintclosedir(".", argv[0], realargc, options);
	}
	else
	{
		for(i = 1; i < argc; i++ )
		{
			openprintclosedir(argv[i], argv[0], realargc, options);
		}
	}
	
	free(options);
	return (0);
}
