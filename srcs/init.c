#include "ft_ping.h"

void set_header(t_packet *packet)
{
	// type 8
	packet->header[0] = 8;
	// code 16
	packet->header[1] = 8;
	// checksum 32
	packet->header[2] = 0;
	packet->header[3] = 0;
	// id 48
	packet->header[4] = 0;
	packet->header[5] = 0;
	// seq 64
	packet->header[6] = packet->seq / 256;
	packet->header[7] = packet->seq % 256;

	update_checksum(packet);
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

void update_checksum(t_packet *packet)
{
	unsigned short *ptr;
	unsigned int sum;
	int i;

	ptr = (unsigned short *)packet->header;
	sum = 0;
	i = 0;
	while (i < 8)
	{
		sum += *ptr++;
		i++;
	}
	sum = (sum >> 16) + (sum & 65535);
	sum += (sum >> 16);
	sum = ~sum;
	packet->header[2] = sum >> 8;
	packet->header[3] = sum & 255;
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
