#include "ft_ping.h"

void	ft_checksum(t_packet *packet)
{
	unsigned short *data;
	unsigned int sum;
	size_t i;

	packet->data[2] = 0;
	packet->data[3] = 0;

	data = (unsigned short *)packet->data;
	sum = 0;
	i = packet->size;

	while (i > 1)
	{
		sum += *data++;
		i -= 2;
	}
	if (i == 1)
		sum += *(unsigned char *)data;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	packet->data[2] = ~sum & 0xFFFF;
	packet->data[3] = (~sum >> 8) & 0xFFFF;
}
