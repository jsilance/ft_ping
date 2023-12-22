#include "ft_ping.h"

void	option_parser(t_ping *ping)
{
	if (ping->argc < 2)
		ft_exit(TOO_FEW_ARGS, ping, NULL);
	if (ping->argc > 3)
		ft_exit(TOO_MANY_ARGS, ping, NULL);

	if (ping->argc == 2)
	{
		if (!ft_strcmp(ping->argv[1], "-h"))
			ft_exit(HELP_ERROR, ping, NULL);
		else if (ping->argv[1][0] == '-')
			ft_exit(TOO_FEW_ARGS, ping, NULL);
		else
			ping->host = ping->argv[1];
	}
	else if (!ft_strcmp(ping->argv[1], "-v") && ping->argc == 3)
	{
		ping->arg = 'v';
		ping->host = ping->argv[2];
	}
	else
		ft_exit(INVALID_OPTION, ping, NULL);
}
