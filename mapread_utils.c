#include "so_long.h"
#include <stdio.h>

t_map *mallocmap (t_map *tmpmap)
{
    t_map *map;
    map = malloc(sizeof(t_map));
    map->height = 0;
    map->width = 0;
    map->map = (char **)ft_calloc(1, 1);
    map->c = 0;
    map->e = 0;
    map->p = 0;
    tmpmap = map;
    return(tmpmap);
}

void writetomap (t_map *map, char *tmp_map)
{
    int line;
    int word;

    line = 0;
    if (!map)
        exitor();
    map->map = (char **)malloc((map->height + 1) * sizeof(char *));
    while (*tmp_map)
    {
        word = 0;
        map->map[line] = (char *)malloc((map->width + 1) * sizeof(char));
        while (*tmp_map && *tmp_map != '\n')
        {
            map->map[line][word] = *tmp_map;
            tmp_map++;
            word++;
        }
        map->map[line][word] = '\0'; 
        line++;
        tmp_map++;
    }
    isallone(map->map[line - 1]);
    exitcharacter(' ', 1, map, NULL);
    map->map[line] = 0;
}

void isallone(char *mapline)
{
    while (*mapline)
    {
        if (*mapline != '1' && *mapline != '\n')
            exitor();
        mapline++;
    }  
}

void exitcharacter(char a, int isended, t_map *map, t_game *game)
{
    if (!map)
    {
        printf("no map");
        exitor();
    }
    if (a == 'P')
    {
        map->p += 1;
        game->player->player_height = map->height;
    }
    if (a == 'E')
        map->e += 1;
    if (a == 'C')
        map->c += 1;
    if (map->p > 1 || map->e > 1 )
        exitor();
    if (isended)
    {
        if (map->p < 1 || map->e < 1 || map->c < 1)
            exitor();
    }
}