#include "header.h"
#include "libft.h"
#include "tests.h"

typedef struct	s_string
{
	char	*text;
	size_t	len;
}				t_string;

void	*ft_memdup(const void *s, size_t size)
{
	void *out = malloc(size);
	if (out != NULL)
		ft_memmove(out, s, size);
	return (out);
}

t_list	*ft_lstnew_str(void *content, size_t len) 
{
	t_list *new;
	t_string *string;

	new = (t_list *)malloc(sizeof(t_list));
	if (new != NULL)
	{
		string = (t_string *)malloc(sizeof(t_string));
		string->text = ft_memdup(content, len); 
		string->len = len;
		new->content = string;
		new->next = NULL;
	}
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list *node;

	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

void	ft_lstappend_back_null(t_list **phead, t_list *node) 
{
	static t_last last;
	
	if (*phead == NULL)
	{
		*phead = node;
		return ;
	}

	if ((*phead) != last.host)
	{
		last.host = *phead;
		last.last = ft_lstlast(*phead);
	}
	last.last->next = node;
	
	// ft_lstadd_back:
	node->next = NULL; // (*node).next
	last.last = node;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *current;
	t_list *next;

	current = *lst;
	while (current)
	{
		next = current->next;
		// ft_lstdelone:
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}



void	ft_fill_list_back_null(t_list **phead, size_t len, char **contents)
{
	size_t i = 0;
	t_list *node;
	while (i < len)
	{
		node = ft_lstnew_str(contents[i], ft_strsize(contents[i]));
		ft_lstappend_back(phead, node);
		i++;
	}
}

int main()
{	
	
	char *lines = 	"You know James Joyce, I like your voice\n\
					You know Baudelaire, I like your hair\n\
					You know Churchill, I know Kill Bill\n\
					You know Tolstoy, I know Playboy";

	
	char **arr = ft_split(lines, '\n');

	// t_list **phead; // 

	t_list *head = NULL;

	ft_fill_list_back_null(&head, 3, arr);

	ft_putlist(head);

}