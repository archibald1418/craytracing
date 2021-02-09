#include "get_next_line.h"
#include "libft.h"
#include "tests.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


void    ft_putstring(t_string *string)
{
    write(1, string->text, string->len);
}

void	ft_putnode_str(t_list *node)
{
	t_string *string = node->content;
	printf("\nNode sits at %p;\nhas values \n", node);
	ft_putstr("(\'");
	ft_putstring(string);
	printf("', len=%zu)", string->len);
	printf("\npoints to %p\n\n", node->next); 
	
}

void	ft_putlist_node(t_list *head_node, void (*putnode) (t_list *node))
{
	printf("\n>>Print linked list<<\n");
	if (head_node == NULL)
	{
		printf("\nList is NULL...\n");
		return ;
	}
	ft_delineate(".");
	while (head_node != NULL)
	{
		putnode(head_node);
		head_node = head_node->next;
		if (head_node)
			printf("-> -> ->\n");
	}
	ft_delineate(".");
	printf("\nList finished\n");
	
}



// t_list *gnl_return_list (int fd, char **line) 
// {
// 	char buf[BUFFER_SIZE]; // TODO: malloc is better (stack has limits)
// 	t_list *chunks;
// 	ssize_t bytes_read;
// 	size_t len;

// 	*line = ft_memdup("", 1); // 1 bytes allocced. 
// 	// NB: memdup shows exactly how much memory alloced!! :)
// 	len = 0;
// 	bytes_read = 0;
// 	chunks = NULL;
// 	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
// 	{
// 		len += bytes_read;
// 		ft_lstappend_back_null(&chunks, ft_lstnew_str(buf, bytes_read)); // Put buffers into list
// 	}

	
	
// 	// Malloc line and copy

// 	return (chunks);
// }

int main()
{
	char *line;

	int fd = open("test.txt", O_RDONLY);

	// gnl reads & writes to line

	t_list *chunks = NULL;
	// int stat = get_next_line (fd, &line); 

	int i = 0;
	while (i != 4)
	{
		int stat = get_next_line (fd, &line);
		printf("i = %d ; [#START]'%s'[#END]\n", i, line);
		i++;
		free(line);
	}
	
	

	// ft_putlist_node(chunks, &ft_putnode_str);

	if (fd > -1)
		close(fd);
	else
	{
		perror("ERROR: Bad file descriptor");
		return (-1);
	}

	free(line); // malloc for line in gnl
	// sleep(100);

}