/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:34:34 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	current_time(void) // check
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putendl_fd("Error: gettimeofday", 2), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	elapsed_time(long start_time)
{
	return (current_time() - start_time);
}
