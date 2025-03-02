#include <stdio.h>
#include <stdlib.h>
#include "../inc/map.h"

/**
 * load_map - Loads the map from a specified file.
 * @filename: The name of the file containing the map data.
 * 
 * Return: A pointer to the loaded map, or NULL on failure.
 */
char **load_map(const char *filename)
{
    FILE *file;
    char **map = NULL;
    size_t line_count = 0;
    size_t max_line_length = 0;
    char *line = NULL;
    ssize_t read;

    file = fopen(filename, "r");
    if (!file)
        return NULL;

    while ((read = getline(&line, &max_line_length, file)) != -1)
    {
        map = realloc(map, sizeof(char *) * (line_count + 1));
        map[line_count] = malloc(max_line_length);
        snprintf(map[line_count], max_line_length, "%s", line);
        line_count++;
    }

    free(line);
    fclose(file);
    return map;
}

/**
 * free_map - Frees the memory allocated for the map.
 * @map: The map to be freed.
 * @line_count: The number of lines in the map.
 */
void free_map(char **map, size_t line_count)
{
    for (size_t i = 0; i < line_count; i++)
    {
        free(map[i]);
    }
    free(map);
}

/**
 * print_map - Prints the map to the console for debugging purposes.
 * @map: The map to be printed.
 * @line_count: The number of lines in the map.
 */
void print_map(char **map, size_t line_count)
{
    for (size_t i = 0; i < line_count; i++)
    {
        printf("%s", map[i]);
    }
}