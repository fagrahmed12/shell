#include "shell.h"

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


int unset_alias(info_t *info, char *str)
{
	char *x, y;
	int ret;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*x = y;
	return (ret);
}

int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


int print_alias(list_t *node)
{
	char *x = NULL, *y = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (y = node->str; y <= x; a++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


int _myalias(info_t *info)
{
	int z = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (z = 1; info->argv[z]; i++)
	{
		p = _strchr(info->argv[z], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
