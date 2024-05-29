#include "philo.h"

void	end_ft(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < info->total_p_num)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->writing));
	pthread_mutex_destroy(&(info->checker));
}

bool	starving(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->eating);
	if ((ft_time() - philo->finished_eating) >= info->philo_t_die)
	{
		pthread_mutex_unlock(&philo->eating);
		return (true);
	}
	pthread_mutex_unlock(&philo->eating);
	return (false);
}

void	is_dead(t_info *info)
{
	int i;

	while (1)
	{
		i = 0;
		while(i < info->total_p_num)
		{
			if ( info->eaten_all == 1)
				return;
			if (starving(info, &info->philos[i]) == true)
			{
				pthread_mutex_lock(&info->checker);
				info->is_dead = 1;
				printf("%lld %d is dead\n", (ft_time() - info->time), i + 1);
				pthread_mutex_unlock(&info->checker);
				return;
			}
			usleep(10);
			i++;
		}
	}
}
