/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/04 19:48:45 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	minus;

	nbr = 0;
	minus = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		nptr++;
	}
	return (nbr * minus);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	length;

	if (nmemb && size > SIZE_MAX / nmemb)
		return (NULL);
	length = size * nmemb;
	ptr = malloc(length);
	if (!ptr)
		return (NULL);
	while (length--)
		ptr[length] = 0;
	return (ptr);
}

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_action(int id, const char *action)
{
	printf("%d %s\n", id, action);
}
