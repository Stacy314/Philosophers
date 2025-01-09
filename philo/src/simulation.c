/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:51:12 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	log_action(philo->sim, philo->id, "has taken a fork");
	usleep(philo->sim->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}

//void	*philosopher_lifecycle(void *arg)
//{
//	t_philosopher	*philo;

//	philo = (t_philosopher *)arg;
//	if (philo->sim->num_philosophers == 1)
//		return (one_philosopher(philo), NULL);
//	while (1)
//	{
//		if (!check_simulation_running(philo->sim))
//			break ;
//		take_forks(philo);
//		if (!check_simulation_running(philo->sim))
//		{
//			release_forks(philo);
//			break ;
//		}
//		eat(philo);
//		release_forks(philo);
//		if (!check_simulation_running(philo->sim))
//			break ;
//		sleep_and_log(philo);
//		if (!check_simulation_running(philo->sim))
//			break ;
//		think(philo);
//	}
//	return (NULL);
//}
void	*philosopher_lifecycle(void *arg)
{
	t_philosopher	*philo;
	int				num;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
		return (one_philosopher(philo), NULL);
	if (philo->sim->num_philosophers % 2 == 0)
		num = 2;
	else
		num = 1;
	while (1)
	{
		if (!check_simulation_running(philo->sim))
			break ;
		if (num == 2)
			take_forks(philo);
		else if (num == 1)
			for_odd(philo);
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

static void	join_threads(t_simulation *sim)
{
	int	i;
	int	thread;

	i = 0;
	while (i < sim->num_philosophers)
	{
		thread = pthread_join(sim->philosophers[i].thread, NULL);
		if (thread != 0)
		{
			ft_putendl_fd("Error: pthread_join failed ", 2);
		}
		i++;
	}
	thread = pthread_join(sim->monitor_thread, NULL);
	if (thread != 0)
	{
		ft_putendl_fd("Error: pthread_join failed ", 2);
	}
}

static void	stop_simulation(t_simulation *sim, int i)
{
	int	j;
	int	thread;

	pthread_mutex_lock(&sim->log_mutex);
	sim->simulation_running = STOPPED;
	pthread_mutex_unlock(&sim->log_mutex);
	ft_putendl_fd("Error: pthread_create failed", 2);
	j = 0;
	while (j < i)
	{
		thread = pthread_join(sim->philosophers[j].thread, NULL);
		j++;
	}
}

int	start_simulation(t_simulation *sim)
{
	int			i;
	int			thread;

	pthread_mutex_lock(&sim->log_mutex);
	sim->simulation_running = RUNNING;
	pthread_mutex_unlock(&sim->log_mutex);
	sim->start_time = current_time();
	i = 0;
	while (i < sim->num_philosophers)
	{
		thread = pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_lifecycle, &sim->philosophers[i]);
		if (thread != 0)
			return (stop_simulation(sim, i + 1), 0);
		i++;
	}
	thread = pthread_create(&sim->monitor_thread, NULL, death_monitor, sim);
	if (thread != 0)
	{
		stop_simulation(sim, sim->num_philosophers);
		return (0);
	}
	join_threads(sim);
	return (1);
}
