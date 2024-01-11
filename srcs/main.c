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
				g_ping->packet_transmitted, g_ping->packet_received,
				(g_ping->packet_transmitted / g_ping->packet_loss * 100),
				(long int)get_time(g_ping->start, g_ping->end));
		if (g_ping->packet_received > 0)
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

	g_ping->socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	perror("THERE:");
	printf("[%d]\n", g_ping->socket_fd);
	if (g_ping->socket_fd < 0)
		ft_exit(SOCKET_ERROR, g_ping, g_packet);

	struct timeval tv = {1, 0};
	
	if (setsockopt(g_ping->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) == -1)
		ft_exit(SOCKET_ERROR, g_ping, g_packet);

	g_ping->addr.sin_family = AF_INET;
	ft_ping(g_ping, g_packet);
	ft_exit(NO_ERROR, g_ping, g_packet);
	return (0);
}
