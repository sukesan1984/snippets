#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_node t_node;
struct s_node
{
	char	c;
	t_node	*lhs;
	t_node	*rhs;
};


t_node	*new_node(char c, t_node *lhs, t_node *rhs)
{
	t_node *n;

	n = calloc(1, sizeof(t_node));
	n->c = c;
	n->lhs = lhs;
	n->rhs = rhs;
	return (n);
}

void show_node(t_node *node, char *prefix, char *children_prefix)
{
	char *str1;
	char *str2;

	if (!node)
		return;
	printf("%s", prefix);
	printf("%c\n", node->c);
	if (node->rhs)
	{
		if (node->lhs)
		{
			asprintf(&str1, "%s├── ", children_prefix);
			asprintf(&str2, "%s│   ", children_prefix);
		}
		else
		{
			asprintf(&str1, "%s└── ", children_prefix);
			asprintf(&str2, "%s    ", children_prefix);
		}
		show_node(node->rhs, str1, str2);
		free(str1);
		free(str2);
	}
	if (node->lhs)
	{
		asprintf(&str1, "%s└── ", children_prefix);
		asprintf(&str2, "%s    ", children_prefix);
		show_node(node->lhs, str1, str2);
		free(str1);
		free(str2);
	}
}

// A : A k | l

// A: l A'
// A': k A' | e

t_node	*adash(char *input)
{
	t_node	*lhs = NULL;
	t_node	*rhs = NULL;

	if (*input == 'k')
	{
		lhs = new_node('k', NULL, NULL);
		input++;
		rhs = (adash(input));
		return (new_node('.', lhs, rhs));
	}
	return NULL;
}

t_node	*a(char *input)
{
	t_node	*lhs = NULL;
	t_node	*rhs = NULL;

	if (*input == 'l')
	{
		lhs = new_node('l', NULL, NULL);
		input++;
	}
	else
	{
		printf("should start with l\n");
		exit(1);
	}
	rhs = adash(input);
	return new_node('.', lhs, rhs);
}

int main()
{
	FILE *file;
	char buf[4096];
	char *input;
	t_node *node;

	file = fdopen(0, "r");
	input = fgets(buf, 4096, file);
	if (!input)
	{
		perror("failed to read");
		exit(1);
	}
	node = a(input);
	show_node(node, "", "");
	free(node);
	return (0);
}
