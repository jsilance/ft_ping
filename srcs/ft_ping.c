#include "ft_ping.h"

void ft_ping(t_ping *ping, t_packet *packet)
{
	int ret;
	struct msghdr msg;
	struct iovec iov;

	ret = 0;
	iov.iov_base = packet->header;
	iov.iov_len = sizeof(packet->header);

	ft_bzero(&msg, sizeof(msg));
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;

	if (inet_pton(AF_INET, ping->host, &ping->addr.sin_addr) <= 0)
		ft_exit(INVALID_HOST, ping, packet);

	printf("PING %s (%s) 56(84) bytes of data.\n", ping->host, ping->host);
	gettimeofday(&ping->start, NULL);
	
	while (1)
	{
		if (sendto(ping->socket_fd, packet->header, ICMP_HEADER_SIZE + PACKET_SIZE,
			0, (struct sockaddr *)&ping->addr, sizeof(ping->addr)) != ICMP_HEADER_SIZE + PACKET_SIZE)
				ft_exit(UNKNOWN_ERROR, ping, packet);
		gettimeofday(&packet->start, NULL);
		ping->packet_transmitted++;
		ret = recvmsg(ping->socket_fd, &msg, 0);
		if (ret == ICMP_HEADER_SIZE + PACKET_SIZE)
		{
			gettimeofday(&packet->end, NULL);
			ping->packet_received++;
			packet->time = get_time(packet->start, packet->end);
			printf("64 bytes from %s: icmp_seq=%d ttl=64 time=%.3Lf ms\n", ping->host, packet->seq, packet->time);
		}
		else
		{
			ping->packet_loss++;
			printf("From %s icmp_seq=%d Destination Host Unreachable\n", ping->host, packet->seq);
		}
		usleep(1000000);

		packet->seq++;
	}
}
