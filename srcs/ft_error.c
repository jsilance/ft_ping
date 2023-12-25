#include "ft_ping.h"

static void print_help(void)
{
	printf("Usage: ./ft_ping <option> <host>\n");
	printf("Options:\n");
	printf("  <host>:\n");
	printf("  -h: print help\n");
	printf("  -v: verbose output\n");
}

void ft_exit(int code, t_ping *ping, t_packet *packet)
{
	switch (code)
	{
		case NO_ERROR:
			break;
		case TOO_MANY_ARGS:
			printf("Too many arguments.\n");
			break;
		case TOO_FEW_ARGS:
			printf("Too few arguments.\n");
			break;
		case INVALID_OPTION:
			printf("Invalid option.\n");
			break;
		case INVALID_HOST:
			printf("Invalid host.\n");
			break;
		case UNKNOWN_ERROR:
			printf("Unknown error.\n");
			break;
		case MALLOC_ERROR:
			printf("Malloc error.\n");
			break;
		case HELP_ERROR:
			print_help();
			break;
		case SOCKET_ERROR:
			printf("Socket error.\n");
			break;
		default:
			printf("Usage: ./ft_ping <option> <host>\n");
			break;
	}
	if (code != NO_ERROR && code != HELP_ERROR)
		printf("\033[0;31mUsage: ./ft_ping <option> <host>\033[0m\n");
	if (ping)
	{
		close(ping->socket_fd);
		ft_bzero(ping, sizeof(t_ping));
		free(ping);
	}
	if (packet)
	{
		ft_bzero(packet, sizeof(t_packet));
		free(packet);
	}
	exit((code > 0));
}
