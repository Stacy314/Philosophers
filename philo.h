/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/04 19:46:05 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	struct s_simulation	*sim;
	t_fork				*left_fork;
	t_fork				*right_fork;
}	t_philosopher;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	t_philosopher	*philosophers;
	t_fork			*forks;
	int				simulation_running;
}	t_simulation;

int		initialize_simulation(t_simulation *sim, int argc, char **argv);
void	start_simulation(t_simulation *sim);
void	*philosopher_lifecycle(void *arg);
void	cleanup_simulation(t_simulation *sim);
long	current_time(void);
void	log_action(int id, const char *action);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif