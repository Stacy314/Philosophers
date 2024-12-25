/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/25 14:43:05 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	log_action(t_simulation *sim, int id, const char *status)
{
	pthread_mutex_lock(&sim->log_mutex);
	if (sim->simulation_running)
		printf("%ld %d %s\n", elapsed_time(sim->start_time), id, status);
	pthread_mutex_unlock(&sim->log_mutex);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}
