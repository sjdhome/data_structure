#include "map.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	struct array_map *m = array_map_init();
	array_map_put(m, "a", "b");
	array_map_put(m, "c", "d");
	char *str = (char *) array_map_get(m, "c");
	assert(strcmp(str, "d") == 0);
	array_map_remove(m, "a");
	assert(array_map_get(m, "a") == NULL);
	array_map_put(m, "a", "e");
	assert(strcmp(array_map_get(m, "a"), "e") == 0);
	return 0;
}

