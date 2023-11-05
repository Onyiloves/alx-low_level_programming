#include "hash_tables.h"

/**
 * hash_table_get - recover the value in a hash_table.
 * @ht: A hash_table.
 * @key: The key to obtained the value in hash_table.
 *
 * Return: the value on success, else Null if key unavaliable
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	hash_node_t *node;
	unsigned long int j;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	j = key_index((const unsigned char *)key, ht->size);
	if (j >= ht->size)
		return (NULL);

	node = ht->array[j];
	while (node && strcmp(node->key, key) != 0)
		node = node->next;

	return ((node == NULL) ? NULL : node->value);
}
