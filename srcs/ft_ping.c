#include "ft_ping.h"
#include <math.h>

void	time_min_max(t_ping *ping)
{
	t_list *tmp;
	long double *time;
	long double min;
	long double max;
	long double sum;
	long double mdev;
	int i;

	i = 0;
	sum = 0;
	min = 0;
	max = 0;
	mdev = 0;
	tmp = ping->time_list;
	while (tmp)
	{
		time = (long double *)tmp->content;
		if (i == 0)
		{
			min = *time;
			max = *time;
		}
		if (*time < min)
			min = *time;
		if (*time > max)
			max = *time;
		sum += *time;
		tmp = tmp->next;
		i++;
	}
	tmp = ping->time_list;
	while (tmp)
	{
		time = (long double *)tmp->content;
		mdev += pow(*time - sum / i, 2);
		tmp = tmp->next;
	}
	mdev = sqrt(mdev / i);
	printf("rtt min/avg/max/mdev = %.3Lf/%.3Lf/%.3Lf/%.3Lf ms\n", min, sum / i, max, mdev);
}

void	ft_ping(t_ping *ping, t_packet *packet)
{
	int ret;
	struct msghdr msg;
	struct timeval tv = {1, 0};
	long double *time;
	t_list *tmp;
	
	ret = 0;
	ft_bzero(&msg, sizeof(msg));

	if (inet_pton(AF_INET, ping->host, &ping->addr.sin_addr) <= 0)
		ft_exit(INVALID_HOST, ping, packet);

	printf("PING %s (%s) 56(84) bytes of data.\n", ping->host, ping->host);
	gettimeofday(&ping->start, NULL);
	
	while (1)
	{
		ft_checksum(packet);
		if (sendto(ping->socket_fd, packet->data, ICMP_HEADER_SIZE + 1, 0,
			(struct sockaddr *)&ping->addr, sizeof(ping->addr)) != ICMP_HEADER_SIZE + 1)
				ft_exit(UNKNOWN_ERROR, ping, packet);
		gettimeofday(&packet->start, NULL);

		ping->packet_transmitted++;

		setsockopt(ping->socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

		ret = recvmsg(ping->socket_fd, &msg, 0);
		if (ret >= 0)
		{
			gettimeofday(&packet->end, NULL);
			ping->packet_received++;
			packet->time = get_time(packet->start, packet->end);
			printf("64 bytes from %s: icmp_seq=%d ttl=64 time=%.3Lf ms\n", ping->host, packet->seq, packet->time);

			time = (long double *)malloc(sizeof(long double));
			if (!time)
				ft_exit(MALLOC_ERROR, ping, packet);
			*time = packet->time;
			tmp = ft_lstnew(time);
			if (!tmp)
				ft_exit(MALLOC_ERROR, ping, packet);
			ft_lstadd_back(&ping->time_list, tmp);
		}
		else
		{
			ping->packet_loss++;
			printf("From %s icmp_seq=%d Destination Host Unreachable\n", ping->host, packet->seq);
		}
		usleep(1000000);

		packet->seq++;
		packet->data[6] = packet->seq >> 8;
		packet->data[7] = packet->seq & 0xFF;
	}
}
