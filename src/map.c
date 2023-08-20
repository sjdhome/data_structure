#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ARRAY_MAP_INITIAL_LENGTH 1

struct array_map *array_map_init(void) {
	struct array_map *m = (struct array_map *) malloc(sizeof(struct array_map));
	assert(m != NULL);
	m->len = ARRAY_MAP_INITIAL_LENGTH;
	m->values = (void **) malloc(m->len * sizeof(void *));
	assert(m->values != NULL);
	m->values[0] = NULL;
	m->keys = (char **) malloc(m->len * sizeof(char *));
	assert(m->keys != NULL);
	m->keys[0] = NULL;
	return m;
}

void array_map_free(struct array_map *m) {
	if (m == NULL) {
		return;
	}
	assert(m->keys != NULL);
	free(m->keys);
	assert(m->values != NULL);
	free(m->values);
	free(m);
}

void *array_map_get(struct array_map *m, char *key) {
	if (m == NULL || key == NULL) {
		return NULL;
	}
	assert(m->keys != NULL);
	for (int i = 0; i < m->len; i++) {
		if (m->keys[i] != NULL && strcmp(key, m->keys[i]) == 0) {
			return m->values[i];
		}
	}
	return NULL;
}

void array_map_put(struct array_map *m, char *key, void *value) {
	if (m == NULL || key == NULL) {
		return;
	}
	assert(m->keys != NULL);
	for (int i = 0; i < m->len; i++) {
		if (m->keys[i] != NULL && strcmp(key, m->keys[i]) == 0) {
			m->values[i] = value;
			return;
		}
	}
	// Not found, find free space
	again:
	for (int i = 0; i < m->len; i++) {
		if (m->keys[i] == NULL) {
			m->keys[i] = key;
			m->values[i] = value;
			return;
		}
	}
	// No free space, allocate an new array
	int old_len = m->len;
	m->len *= 2;
	void **old_values = m->values;
	m->values = (void **) malloc(m->len * sizeof(void *));
	for (int i = 0; i < m->len; i++) {
		m->values[i] = NULL;
	}
	memcpy(m->values, old_values, old_len * sizeof(void *));
	free(old_values);
	old_values = NULL;
	char **old_keys = m->keys;
	m->keys = (char **) malloc(m->len * sizeof(char *));
	for (int i = 0; i < m->len; i++) {
		m->keys[i] = NULL;
	}
	memcpy(m->keys, old_keys, old_len * sizeof(char *));
	free(old_keys);
	old_keys = NULL;

	goto again; // Try again
}

void array_map_remove(struct array_map *m, char *key) {
	if (m == NULL || key == NULL) {
		return;
	}
	assert(m->keys != NULL);
	for (int i = 0; i < m->len; i++) {
		if (m->keys[i] != NULL && strcmp(key, m->keys[i]) == 0) {
			m->keys[i] = NULL;
			m->values[i] = NULL;
			break;
		}
	}
}

