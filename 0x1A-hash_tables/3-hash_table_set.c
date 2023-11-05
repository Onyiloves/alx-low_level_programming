#include "hash_tables.h"

/**
 * hash_table_set - insert an element in a hash_table.
 * @ht: A hash_table.
 * @key: The key to be added in the list
 * @value: The value of the element to add in the list
 *
 * Return: 1 on successful, else 0
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *new;
	char *dublicate;
	unsigned long int index, j;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	dublicate = strdup(value);
	if (dublicate == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	for (j = index; ht->array[j]; j++)
	{
		if (strcmp(ht->array[j]->key, key) == 0)
		{
			free(ht->array[j]->value);
			ht->array[j]->value = dublicate;
			return (1);
		}
	}

	new = malloc(sizeof(hash_node_t));
	if (new == NULL)
	{
		free(dublicate);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (0);
	}
	new->value = dublicate;
	new->next = ht->array[index];
	ht->array[index] = new;

	return (1);
}
