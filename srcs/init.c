#include "ft_ping.h"

void set_header(t_packet *packet)
{
	packet->data[0] = 0;
	packet->data[1] = ICMP_ECHO; // type
	packet->data[2] = 0 ; // checksum
	packet->data[3] = 0; // checksum somme %256 du message
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
