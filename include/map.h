struct array_map {
	void **values;
	char **keys;
	int len;
};

struct array_map *array_map_init(void);
void array_map_free(struct array_map *);
void *array_map_get(struct array_map *, char *);
void array_map_put(struct array_map *, char *, void *);
void array_map_remove(struct array_map *, char *);
