#include "main.h"

/**
 * binary_to_uint - this is a function that converts
 * a binary number to an unsigned int.
 * @b: this is a pointer to a string containing a binary number
 *
 * Return: an unsigned int with decimal value of a binary number, or 0 if error
 */
unsigned int binary_to_uint(const char *b)
{
	int a;
	unsigned int num;

	num = 0;
	if (!b)
		return (0);
	for (a = 0; b[a] != '\0'; a++)
	{
		if (b[a] != '0' && b[a] != '1')
			return (0);
	}
	for (a = 0; b[a] != '\0'; a++)
	{
		num <<= 1;
		if (b[a] == '1')
			num += 1;
	}
	return (num);
}

