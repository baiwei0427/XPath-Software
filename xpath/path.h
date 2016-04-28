#ifndef __PATH_H__
#define __PATH_H__

#include <linux/types.h>
#include <linux/list.h>

/* Hash range for XPath path table */
#define XPATH_PATH_HASH_RANGE 256

struct xpath_path_entry
{
    struct hlist_node hlist;
    unsigned int daddr; //destination IP address
    unsigned int num_paths;
    unsigned int *paths;    //available paths to 'daddr'
    atomic_t *congestions;    //congestion degree for different paths
};

struct xpath_path_table
{
    struct hlist_head *lists;   //linked list
};

/* Initialize XPath path table */
bool xpath_init_path_table(struct xpath_path_table *pt);

/* Search available paths to 'daddr' */
struct xpath_path_entry *xpath_search_path_table(struct xpath_path_table *pt, unsigned int daddr);

/* Insert a new path entry (daadr, num_paths, paths) to XPath path table */
bool xpath_insert_path_table(struct xpath_path_table *pt, unsigned int daddr, unsigned int num_paths, unsigned int *paths);

/* Clear all path entries in XPath path table */
bool xpath_clear_path_table(struct xpath_path_table *pt);

/* Exit XPath path table. Release all resrouces. */
bool xpath_exit_path_table(struct xpath_path_table *pt);

#endif