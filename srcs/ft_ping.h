#ifndef FT_PING_H
# define FT_PING_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>

#define PACKET_SIZE     64
#define IP_HEADER_SIZE  20
#define ICMP_HEADER_SIZE 8

enum e_error_code
{
	NO_ERROR = 0,
	TOO_MANY_ARGS,
	TOO_FEW_ARGS,
	INVALID_OPTION,
	INVALID_HOST,
	UNKNOWN_ERROR,
	MALLOC_ERROR,
	HELP_ERROR,
	SOCKET_ERROR,
};

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_ping
{
	int				argc;
	char			**argv;
	char			*host;
	char			arg;

	int				socket_fd;

	int				packet_received;
	int				packet_transmitted;
	int				packet_loss;

	int				identifier;

	struct sockaddr_in	addr;

	struct timeval	start;
	struct timeval	end;
	long double		time;

	t_list			*time_list;
}				t_ping;

typedef struct	s_packet
{
	int				seq;

	unsigned char	data[9];
	size_t			size;

	struct timeval	start;
	struct timeval	end;
	long double		time;
}				t_packet;

int			ft_strcmp(const char *s1, const char *s2);
void		ft_bzero(void *str, size_t n);
size_t		ft_strlen(const char *str);

long double get_time(struct timeval start, struct timeval end);

void		option_parser(t_ping *ping);

t_packet	*init_packet(t_ping *ping);
t_ping		*init_ping(int argc, char **argv);
void		ft_checksum(t_packet *packet);
void		set_header(t_packet *packet, t_ping *ping);

void		sig_handler(int code);
void		ft_exit(int code, t_ping *ping, t_packet *packet);

void		ft_ping(t_ping *ping, t_packet *packet);
void		time_min_max(t_ping *ping);

void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

#endif
