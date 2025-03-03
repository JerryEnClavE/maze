#include "../inc/utils.h"
#include <stdlib.h>

/**
 * allocate_memory - Allocates memory of a given size.
 * @size: The size of memory to allocate.
 *
 * Return: Pointer to the allocated memory, or NULL if allocation fails.
 */
void *allocate_memory(size_t size, size_t element_size);
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/**
 * free_memory - Frees allocated memory.
 * @ptr: Pointer to the memory to free.
 */
void free_memory(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
    }
}

/**
 * clamp - Clamps a value between a minimum and maximum range.
 * @value: The value to clamp.
 * @min: The minimum value.
 * @max: The maximum value.
 *
 * Return: The clamped value.
 */
float clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}

/**
 * degrees_to_radians - Converts degrees to radians.
 * @degrees: The angle in degrees.
 *
 * Return: The angle in radians.
 */
float degrees_to_radians(float degrees)
{
    return degrees * (3.14159265358979323846 / 180.0);
}

/**
 * radians_to_degrees - Converts radians to degrees.
 * @radians: The angle in radians.
 *
 * Return: The angle in degrees.
 */
float radians_to_degrees(float radians)
{
    return radians * (180.0 / 3.14159265358979323846);
}