#include "hash_tables.h"

/**
 * hash_table_print - display the elements in a given hash table.
 * @ht: The hash table.
 * Return: the value on success, else Null if ht didn't print
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *node;
	unsigned long int j;
	unsigned char display = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (j = 0; j < ht->size; j++)
	{
		if (ht->array[j] != NULL)
		{
			if (display == 1)
				printf(", ");

			node = ht->array[j];
			while (node != NULL)
			{
				printf("'%s': '%s'", node->key, node->value);
				node = node->next;
				if (node != NULL)
					printf(", ");
			}
			display = 1;
		}
	}
	printf("}\n");
}
