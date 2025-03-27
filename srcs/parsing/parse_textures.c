#include "cub3d.h"

static char **split_xpm_header(char *line) {
    char **parts = malloc(sizeof(char *) * 4);
    if (!parts) {
        return NULL;
    }

    int part_index = 0;
    int start_index = 0;
    int line_index = 0;
    int line_length = ft_strlen(line);

    while (line_index <= line_length && part_index < 4) {
        if (line[line_index] == ' ' || line[line_index] == ',' || line[line_index] == '\0') {
            int part_length = line_index - start_index;
            if (part_length > 0) {
                parts[part_index] = malloc(sizeof(char) * (part_length + 1));
                if (!parts[part_index]) {
                    //free already allocated parts.
                    for(int j = 0; j < part_index; j++){
                        free(parts[j]);
                    }
                    free(parts);
                    return NULL;
                }
                ft_strlcpy(parts[part_index], line + start_index, part_length);
                parts[part_index][part_length] = '\0';
                part_index++;
            }
            start_index = line_index + 1;
        }
        line_index++;
    }

    if (part_index != 4) {
        for (int i = 0; i < part_index; i++) {
            free(parts[i]);
        }
        free(parts);
        return NULL;
    }

    return parts;
}

static void parse_xpm_header(char *line, t_xpm *xpm) {
    char **parts;

    parts = split_xpm_header(line);
    if (!parts) {
        error("Invalid XPM header format");
        return;
    }

    xpm->width = ft_atoi(parts[0]);
    xpm->height = ft_atoi(parts[1]);
    xpm->num_colors = ft_atoi(parts[2]);
    xpm->chars_per_pixel = ft_atoi(parts[3]);

    for (int i = 0; i < 4; i++) {
        free(parts[i]);
    }
    free(parts);
}

static void parse_xpm_colors(char **lines, t_xpm *xpm) {
    int i;

    xpm->color_map = malloc(sizeof(char *) * xpm->num_colors);
    if (!xpm->color_map) {
        error("Failed to allocate memory for color map");
        return;
    }

    i = 0;
    while (i < xpm->num_colors) {
        xpm->color_map[i] = malloc(sizeof(char) * 7);
        if (!xpm->color_map[i]) {
            error("Failed to allocate memory for color");
            for(int j = 0; j<i; j++){
                free(xpm->color_map[j]);
            }
            free(xpm->color_map);
            return;
        }
        xpm->color_map[i][0] = lines[i][0];
        ft_strlcpy(xpm->color_map[i] + 1, lines[i] + 3, 6);
        i++;
    }
}

static void parse_xpm_pixels(char **lines, t_xpm *xpm) {
    int i;

    xpm->pixels = (char **)malloc(sizeof(char *) * xpm->height);
    if (!xpm->pixels) {
        error("Failed to allocate memory for pixels");
        return;
    }

    i = 0;
    while (i < xpm->height) {
        xpm->pixels[i] = ft_strdup(lines[i]);
        if (!xpm->pixels[i]) {
            error("Failed to duplicate pixel line");
            for (int j = 0; j < i; j++) {
                free(xpm->pixels[j]);
            }
            free(xpm->pixels);
            return;
        }
        i++;
    }
}

void parse_xpm(char **xpm_data, t_xpm *xpm) {
    parse_xpm_header(xpm_data[0], xpm);
    parse_xpm_colors(xpm_data + 1, xpm);
    parse_xpm_pixels(xpm_data + 1 + xpm->num_colors, xpm);
}

void free_xpm(t_xpm *xpm) {
    int i;

    if (xpm->pixels) {
        i = 0;
        while (i < xpm->height) {
            if (xpm->pixels[i]) {
                free(xpm->pixels[i]);
            }
            i++;
        }
        free(xpm->pixels);
    }
    if(xpm->color_map){
        i = 0;
        while(i < xpm->num_colors){
            if(xpm->color_map[i]){
                free(xpm->color_map[i]);
            }
            i++;
        }
        free(xpm->color_map);
    }
}

t_xpm *load_xpm_texture(char *texture_path) {
    int fd;
    char *line;
    char **xpm_data = NULL;
    t_xpm *xpm;
    int line_count = 0;
    int capacity = 10;

    fd = open(texture_path, O_RDONLY);
    if (fd < 0) {
        error("Can't open texture file");
        return NULL;
    }

    xpm_data = (char **)malloc(sizeof(char *) * capacity);
    if (!xpm_data) {
        error("Memory allocation failed for XPM data");
        close(fd);
        return NULL;
    }

    while ((line = get_next_line(fd)) != NULL) {
        if (line_count >= capacity - 1) {
            capacity *= 2;
            char **temp = (char **)realloc(xpm_data, sizeof(char *) * capacity);
            if (!temp) {
                error("Memory allocation failed during resize");
                for (int i = 0; i < line_count; i++) {
                    free(xpm_data[i]);
                }
                free(xpm_data);
                close(fd);
                return NULL;
            }
            xpm_data = temp;
        }
        xpm_data[line_count++] = line;
    }
    xpm_data[line_count] = NULL;
    close(fd);

    xpm = (t_xpm *)malloc(sizeof(t_xpm));
    if (!xpm) {
        error("Memory allocation failed for XPM structure");
        for (int i = 0; i < line_count; i++) {
            free(xpm_data[i]);
        }
        free(xpm_data);
        return NULL;
    }
    ft_memset(xpm, 0, sizeof(t_xpm));

    parse_xpm(xpm_data, xpm);

    for (int i = 0; i < line_count; i++) {
        free(xpm_data[i]);
    }
    free(xpm_data);

    return xpm;
}

void parse_xpm_textures(t_map *map) {
    int i;

    i = 0;
    while (i < 4) {
        map->textures_xpm[i] = load_xpm_texture(map->textures[i]);
        if (!map->textures_xpm[i]) {
            error("Failed to parse XPM texture");
            // Handle error, maybe free already loaded textures
            for(int j=0; j<i; j++){
                free_xpm(map->textures_xpm[j]);
                map->textures_xpm[j] = NULL;
            }
            return;
        }
        i++;
    }
}
