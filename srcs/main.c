#include <stdio.h>
#include "ft_ping.h"

int main(int argc, char **argv)
{
	(void) argv;
	if (argc < 2 || argc > 3)
	{
		printf("Usage: ./ft_ping <option> host\n");
		return (1);
	}
	if (!ft_strcmp(argv[1], "-h"))
	{
		printf("Usage: ./ft_ping <option> host\n");
		return (0);
	}
	if (!ft_strcmp(argv[1], "-v"))
	{
		// some code;
	}
	// start here
	return (0);
}