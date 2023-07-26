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
	char options[1024] = "";
	int realargc = 0;

	for(i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			char *opt = argv[i] + 1;
			char *opts = options;
			strcat(opts, opt);
		} else {
			realargc++;
		}
	}

	if (realargc == 1)
	{
		openprintclosedir(".", argv[0], realargc);
	}
	else
	{
		for(i = 1; i < argc; i++ )
		{
			openprintclosedir(argv[i], argv[0], realargc);
		}
	}
	
	return (0);
}
