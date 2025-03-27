#include "cub3d.h"

static void parse_xpm_header(char *line, t_xpm *xpm)
{
    char **parts;

    parts = ft_split(line, ' ');
    if (!parts)
        return;
    xpm->width = ft_atoi(parts[0]);
    xpm->height = ft_atoi(parts[1]);
    xpm->num_colors = ft_atoi(parts[2]);
    xpm->chars_per_pixel = ft_atoi(parts[3]);
    free(parts);
}

static void parse_xpm_colors(char **lines, t_xpm *xpm)
{
    int i;

    i = 0;
    while (i < xpm->num_colors)
    {
        xpm->color_map[i][0] = lines[i][0];
        ft_strlcpy(xpm->color_map[i] + 1, lines[i] + 3, 6);
        i++;
    }
}

static void parse_xpm_pixels(char **lines, t_xpm *xpm)
{
    int i;

    xpm->pixels = (char **)malloc(sizeof(char *) * xpm->height);
    if (!xpm->pixels)
        return;
    i = 0;
    while (i < xpm->height)
    {
        xpm->pixels[i] = ft_strdup(lines[i]);
        i++;
    }
}

void parse_xpm(char **xpm_data, t_xpm *xpm)
{
    parse_xpm_header(xpm_data[0], xpm);
    parse_xpm_colors(xpm_data + 1, xpm);
    parse_xpm_pixels(xpm_data + 1 + xpm->num_colors, xpm);
}

void free_xpm(t_xpm *xpm)
{
    int i;

    i = 0;
    while (i < xpm->height)
    {
        free(xpm->pixels[i]);
        i++;
    }
    free(xpm->pixels);
}

t_xpm *load_xpm_texture(char *texture_path)
{
    int     fd;
    char    *line;
    char    **xpm_data;
    t_xpm   *xpm;
    int     i;

    // Open the texture file
    fd = open(texture_path, O_RDONLY);
    if (fd < 0)
        error("Can't open texture file");

    // Read the texture data (you'll need to adjust the size of xpm_data)
    xpm_data = (char **)malloc(sizeof(char *) * 1024); // Arbitrary large size
    if (!xpm_data)
        error("Memory allocation failed for XPM data");

    i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		xpm_data[i++] = line;
		free(line);
		line = get_next_line(fd);
	}
    xpm_data[i] = NULL;  // Mark the end of data

    close(fd);

    // Initialize the XPM structure
    xpm = (t_xpm *)malloc(sizeof(t_xpm));
    if (!xpm)
        error("Memory allocation failed for XPM structure");

    // Parse the XPM data
    parse_xpm(xpm_data, xpm);

    // Free the raw xpm_data
    i = 0;
    while (xpm_data[i])
    {
        free(xpm_data[i]);
        i++;
    }
    free(xpm_data);

    return xpm;
}

void parse_xpm_textures(t_map *map)
{
    int i;

    i = 0;
    while (i < 4)
    {
        map->textures_xpm[i] = load_xpm_texture(map->textures[i]);
        if (!map->textures_xpm[i])
            error("Failed to parse XPM texture");
        i++;
    }
}
