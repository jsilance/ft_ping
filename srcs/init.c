#include "ft_ping.h"

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
	return (packet);
}
