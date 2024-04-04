#include "ft_ping.h"

void	set_header(t_packet *packet, t_ping *ping)
{
	packet->data[0] = ICMP_ECHO; // type
	packet->data[1] = 0; // code

	packet->data[2] = 0 ; // checksum
	packet->data[3] = 0; // checksum

	packet->data[4] = ping->identifier >> 8; // identifier
	packet->data[5] = ping->identifier & 0xFF; // identifier

	packet->data[6] = 0; // seq
	packet->data[7] = 1; // seq

	packet->data[8] = 0x01; // data

	packet->size = ICMP_HEADER_SIZE + 1; // header size + data size
}

t_ping *init_ping(int argc, char **argv)
{
	t_ping *ping;

	srand(time(NULL));
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
	ping->identifier = rand() & 0xFFFF;
	ping->time_list = NULL;
	return (ping);
}

t_packet *init_packet(t_ping *ping)
{
	t_packet *packet;

	if (!(packet = (t_packet *)malloc(sizeof(t_packet))))
		return (NULL);
	ft_bzero(packet, sizeof(t_packet));
	packet->seq = 1;
	set_header(packet, ping);

	return (packet);
}
