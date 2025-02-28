#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/**
 * struct Vector2D - A structure to represent a 2D vector.
 * @x: The x-coordinate of the vector.
 * @y: The y-coordinate of the vector.
 */
typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

/**
 * Allocates memory for an array of elements.
 * @size: The number of elements to allocate.
 * @element_size: The size of each element.
 * 
 * Return: A pointer to the allocated memory, or NULL on failure.
 */
void *allocate_memory(size_t size, size_t element_size);

/**
 * Frees the allocated memory.
 * @ptr: Pointer to the memory to be freed.
 */
void free_memory(void *ptr);

/**
 * Calculates the distance between two points.
 * @a: The first point.
 * @b: The second point.
 * 
 * Return: The distance between the two points.
 */
float calculate_distance(Vector2D a, Vector2D b);

/**
 * Normalizes a vector to have a length of 1.
 * @vector: The vector to normalize.
 * 
 * Return: A normalized vector.
 */
Vector2D normalize_vector(Vector2D vector);

#endif /* UTILS_H */