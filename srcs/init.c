#include "ft_ping.h"

void set_header(t_packet *packet)
{
	packet->header = 0;
	print_bin(packet->header);
	packet->header |= ICMP_ECHO << 24; // type
	print_bin(packet->header);
	packet->header |= 0 << 16; // code
	print_bin(packet->header);
	packet->header |= 0; // somme %256 du message
	print_bin(packet->header);
	packet->header |= 0;
	print_bin(packet->header);
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
