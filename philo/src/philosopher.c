/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/05 17:13:02 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	print_action(philo->sim, philo->id, "has taken a fork");
	usleep(philo->sim->time_to_die * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}

void	*philosopher_lifecycle(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
		return (one_philosopher(philo), NULL);
	while (1)
	{
		if (!check_simulation_running(philo->sim))
			break ;
		take_forks(philo);
		if (!check_simulation_running(philo->sim))
		{
			release_forks(philo);
			break ;
		}
		eat(philo);
		release_forks(philo);
		if (!check_simulation_running(philo->sim))
			break ;
		sleep_and_log(philo);
		if (!check_simulation_running(philo->sim))
			break ;
		think(philo);
	}
	return (NULL);
}

