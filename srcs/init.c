#include "ft_ping.h"

void set_header(t_packet *packet)
{
	packet->header.type = ICMP_ECHO;
	packet->header.code = 0;
	packet->header.un.echo.id = getpid();
	packet->header.un.echo.sequence = packet->seq;
	packet->header.checksum = 0;
	packet->header.checksum = htons(0);
}

t_ping *init_ping(int argc, char **argv)
{
	t_ping *ping;

	if (!(ping = (t_ping *)malloc(sizeof(t_ping))))
		return (NULL);
	ping->argc = argc;
	ping->argv = argv;
	ping->host = NULL;
	ping->socket_fd = -1;
	ping->packet_received = 0;
	ping->packet_transmitted = 0;
	ping->packet_loss = 0;
	ping->addr = (struct sockaddr_in){0};
	ping->arg = 0;
	return (ping);
}

t_packet *init_packet(void)
{
	t_packet *packet;

	if (!(packet = (t_packet *)malloc(sizeof(t_packet))))
		return (NULL);
	ft_bzero(packet, sizeof(t_packet));
	packet->seq = 1;
	set_header(packet);
	return (packet);
}
