#include "ft_ping.h"

void ft_ping(t_ping *ping, t_packet *packet)
{
	printf("PING %s (%s) 56(84) bytes of data.\n", ping->host, ping->host);
	gettimeofday(&ping->start, NULL);
	while (1)
	{
		gettimeofday(&packet->start, NULL);
		usleep(100);
		gettimeofday(&packet->end, NULL);
		packet->time = get_time(packet->start, packet->end);

		printf("64 bytes from %s: icmp_seq=%d ttl=64 time=%.3Lf ms\n", ping->host, packet->seq, packet->time);
		usleep(1000000);

		packet->seq++;
	}
}
