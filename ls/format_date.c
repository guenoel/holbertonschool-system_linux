#include "hls.h"

/**
 *  formate_date - format date and remove the four first characters
 *  @st_mtime: non formated date and time
 *
 *  return: formated date and time string
 */

char *format_date(char *datetime)
{
	int p = 4;
	int i;

	char *formatted_date = (char *)malloc(13 * sizeof(char));
	if (formatted_date == NULL) {
		perror("Memory allocation error");
		exit(1);
	}
	for (i = 0; i < 12; i++)
	{
		formatted_date[i] = datetime[p++];
	}
	formatted_date[12] = '\0';

	return formatted_date;
}
