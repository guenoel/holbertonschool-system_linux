/**
 * _strcmp - compare a string a to an other string
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: vrai ou faux ?
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && (s1[i] - s2[i]) == 0; i++)
		;
return (s1[i] - s2[i]);
}
