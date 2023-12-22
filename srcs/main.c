#include "ft_ping.h"

t_ping	*g_ping = NULL;
t_packet *g_packet = NULL;

void sig_handler(int code)
{
	if (code == SIGINT)
	{
		gettimeofday(&g_ping->end, NULL);
		printf("\n--- %s ping statistics ---\n", g_ping->host);
		printf("%d packets transmitted, %d received, %d%% packet loss, time %ldms\n",
				g_packet->seq, 0, 0, (long int)get_time(g_ping->start, g_ping->end));
		printf("rtt min/avg/max/mdev = %d/%d/%d/%d ms\n",
				0, 0, 0, 0);
		ft_exit(NO_ERROR, g_ping, g_packet);
	}
}

long double get_time(struct timeval start, struct timeval end)
{
	long double time;

	time = (end.tv_sec - start.tv_sec) * 1000.0;
	time += (end.tv_usec - start.tv_usec) / 1000.0;
	return (time);
}

int main(int argc, char **argv)
{
	signal(SIGINT, sig_handler);
	g_ping = init_ping(argc, argv);
	if (!g_ping)
		ft_exit(MALLOC_ERROR, NULL, NULL);
	option_parser(g_ping);
	
	g_packet = init_packet();
	if (!g_packet)
		ft_exit(MALLOC_ERROR, g_ping, NULL);

	// define fd of socket
	// define protocol and type of socket

	ft_ping(g_ping, g_packet);
	return (0);
}
