#include "hash_tables.h"

shash_table_t *shash_table_create(unsigned long int size);
int shash_table_set(shash_table_t *ht, const char *key, const char *value);
char *shash_table_get(const shash_table_t *ht, const char *key);
void shash_table_print(const shash_table_t *ht);
void shash_table_print_rev(const shash_table_t *ht);
void shash_table_delete(shash_table_t *ht);

/**
 * shash_table_create - develop a sorted hash_table.
 * @size: The size of develop hash_table sorted.
 *
 * Return: new sorted hash_table, else Null on error.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int j;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
		return (NULL);
	for (j = 0; j < size; j++)
		ht->array[j] = NULL;
	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - insert an element to a hash_table sorted.
 * @ht: A hash_table.
 * @key: The key to be add in the list.
 * @value: The value in link with key to hash_table.
 *
 * Return: 1 on sucessful, else 0
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new, *k;
	char *dublicate;
	unsigned long int j;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	dublicate = strdup(value);
	if (dublicate == NULL)
		return (0);

	j = key_index((const unsigned char *)key, ht->size);
	k = ht->shead;
	while (k)
	{
		if (strcmp(k->key, key) == 0)
		{
			free(k->value);
			k->value = dublicate;
			return (1);
		}
		k = k->snext;
	}

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
	{
		free(dublicate);
		return (0);
	}
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(dublicate);
		free(new);
		return (0);
	}
	new->value = dublicate;
	new->next = ht->array[j];
	ht->array[j] = new;

	if (ht->shead == NULL)
	{
		new->sprev = NULL;
		new->snext = NULL;
		ht->shead = new;
		ht->stail = new;
	}
	else if (strcmp(ht->shead->key, key) > 0)
	{
		new->sprev = NULL;
		new->snext = ht->shead;
		ht->shead->sprev = new;
		ht->shead = new;
	}
	else
	{
		k = ht->shead;
		while (k->snext != NULL && strcmp(k->snext->key, key) < 0)
			k = k->snext;
		new->sprev = k;
		new->snext = k->snext;
		if (k->snext == NULL)
			ht->stail = new;
		else
			k->snext->sprev = new;
		k->snext = new;
	}

	return (1);
}

/**
 * shash_table_get - recover the value of key in a sorted hash_table.
 * @ht: sorted hash_table.
 * @key: The key to obtained the value in hash_table.
 *
 * Return: Value on successful, else NULL.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *node;
	unsigned long int j;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	j = key_index((const unsigned char *)key, ht->size);
	if (j >= ht->size)
		return (NULL);

	node = ht->shead;
	while (node != NULL && strcmp(node->key, key) != 0)
		node = node->snext;

	return ((node == NULL) ? NULL : node->value);
}

/**
 * shash_table_print - display a sorted hash_table.
 * @ht: hash_table.
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->shead;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->snext;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - display hash_table in backward position.
 * @ht: hash_table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->stail;
	printf("{");
	while (node != NULL)
	{
		printf("'%s': '%s'", node->key, node->value);
		node = node->sprev;
		if (node != NULL)
			printf(", ");
	}
	printf("}\n");
}

/**
 * shash_table_delete - rm a sorted hash_table.
 * @ht: hash_table.
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_table_t *h = ht;
	shash_node_t *node, *k;

	if (ht == NULL)
		return;

	node = ht->shead;
	while (node)
	{
		k = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = k;
	}

	free(h->array);
	free(h);
}
