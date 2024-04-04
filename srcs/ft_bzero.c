/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:28:39 by jusilanc          #+#    #+#             */
/*   Updated: 2024/04/04 05:54:04 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = str;
	i = 0;
	while (ptr && i < n)
		ptr[i++] = 0;
}
