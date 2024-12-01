/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/29 18:55:54 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

static int	count(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static void	fill(int i, int n, char *str)
{
	while (n != 0)
	{
		i--;
		str[i] = (char)(((n % 10) * (2 * (n > 0) - 1)) + '0');
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		num;
	int		i;
	char	*str;

	num = n;
	i = count(n);
	if (n < 0)
		i++;
	str = (char *) ft_calloc(sizeof(char) * (i + 1), 1);
	if (!str)
		return (0);
	str[i] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	fill(i, n, str);
	if (num < 0)
		str[0] = '-';
	return (str);
}
