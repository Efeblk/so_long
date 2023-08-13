#include "so_long.h"
#include <stdio.h>

static int charvalid(char c, t_map *map)
{
    char *valid;
    
    valid = "01CEP\n";
    while (*valid)
    {      
        if (*valid == c)
        { 
            exitcharacter(c, 0, map);
            return (1);
        }
        valid++;
    }
    exitor();
    return(0);
}

static void checkline(char *line, t_map *map)
{
    int last;

    last = ft_strlen1(line) - 1;
    if (line[0] != '1' || line[last] != '1')
        exitor();
    while (*line && charvalid(*line, map))
        line++;
}

static int firstlinecheck(int mapwidth, char *mapline, int firstlinebool)
{
    int tmpwidth;

    if (firstlinebool)
    {
        mapwidth = ft_strlen1(mapline);
        isallone(mapline);
    }
    tmpwidth = ft_strlen1(mapline);
    if (mapwidth != tmpwidth)
        exitor();
    return(mapwidth);
}

char *checkmap(t_map *map, char *tmp_map, int fdmap)
{
    int firstlinebool;
    char *mapline;

    mapline = "tmp";
    firstlinebool = 1;
    while (mapline != NULL)
    {
        mapline = get_next_line(fdmap);
        if (mapline == NULL)
            break;
        map->width = firstlinecheck(map->width, mapline, firstlinebool);
        firstlinebool = 0;
        checkline(mapline, map);
        tmp_map = ft_strjoin(tmp_map, mapline);
        map->height += 1;
    }
    return(tmp_map);
}

void readmap(char *mapname, int doreach, t_map *map)
{
    int fdmap;
    char *tmp_map;
    
    if(!doreach)
        mapfree(map);
    fdmap = open(mapname, O_RDONLY);
    tmp_map = ft_calloc(1, 1);
    mallocmap(map);
    tmp_map = checkmap(map, tmp_map, fdmap);
    writetomap(map, tmp_map);
    close(fdmap);
    if (doreach)
        is_reachable(map);
    printf("%s\n", map->map[0]);
    printf("%s\n", map->map[1]);
    printf("%s\n", map->map[2]);
    printf("%s\n", map->map[3]);
}
