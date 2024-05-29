#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] == '0')
		i++;
	i = j;
	while (str[j])
		j++;
	return (i);
}

long	ft_atoi(char *str)
{
	long	atoi;
	long	signe;

	signe = 1;
	atoi = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = signe * -1;
		str++;
		if (*str == '-' || *str == '+')
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		atoi = (atoi * 10 + (*str - '0'));
		str++;
	}
	return (atoi * signe);
}

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void my_printf(t_info *info, int i, char *str)
{
    pthread_mutex_lock(&info->print);
    if (info->is_dead == 1 || info->eaten_all == 1)
    {
        pthread_mutex_unlock(&info->print);
        return;
    }
    pthread_mutex_unlock(&info->print);
    pthread_mutex_lock(&(info->writing));
    printf("%lld %i %s\n", (ft_time() - info->time), (i + 1), str);
    pthread_mutex_unlock(&(info->writing));
}