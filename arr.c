#include <stdlib.h>
#include "cub3d.h"

static int	arr_grow(t_arr *arr)
{
	char **new;

	arr->max_size *= 2;
	new = malloc(arr->max_size * sizeof(char *));
	if (new == NULL)
		return (1);
	ft_memcpy(new, arr->data, arr->size * sizeof(char *));
	free(arr->data);
	arr->data = new;
	return (0);
}

int arr_create(t_arr *arr) 
{
	arr->size = 0;
	arr->max_size = 1;
	arr->data = malloc(sizeof(char *));
	return (arr->data == NULL);
}

int arr_add(t_arr *arr, char *str)
{
	if (arr->size == arr->max_size && arr_grow(arr)) 
		return (1);
	arr->data[arr->size] = str;
	arr->size++;
	return (0);
}

char *arr_get(t_arr *arr, unsigned long index)
{
	return (arr->data[index]);
}

void arr_free(t_arr *arr)
{
	unsigned long	i;

	i = 0;
	while (i < arr->size)
		free(arr->data[i++]); 
	free(arr->data);
}
