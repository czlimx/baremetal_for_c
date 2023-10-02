#ifndef LIBC_LIST_H_
#define LIBC_LIST_H_

#include "arch_compiler.h"

struct libc_list_type
{
    struct libc_list_type* prev;
    struct libc_list_type* next;
};

/**
 * @brief Initialize a list_head structure
 * @list: list_head structure to be initialized.
 *
 * Initializes the list_head to point to itself.  If it is a list header,
 * the result is an empty list.
 */
void libc_list_init(struct libc_list_type *entry);

/**
 * @brief list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void libc_list_add(struct libc_list_type *news, struct libc_list_type *head);

/**
 * @brief list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
void libc_list_add_tail(struct libc_list_type *news, struct libc_list_type *head);

/**
 * @brief list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
void libc_list_del(struct libc_list_type *entry);

/**
 * @brief list_replace - replace old entry by new one
 * @old:  the element to be replaced
 * @new:  the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
void libc_list_replace(struct libc_list_type *old, struct libc_list_type *news);

/**
 * @brief list_swap - replace entry1 with entry2 and re-add entry1 at entry2's position
 * @entry1: the location to place entry2
 * @entry2: the location to place entry1
 */
void libc_list_swap(struct libc_list_type *entry1, struct libc_list_type *entry2);

/**
 * @brief list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
void libc_list_move(struct libc_list_type *entry, struct libc_list_type *head);

/**
 * @brief list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
void libc_list_move_tail(struct libc_list_type *entry, struct libc_list_type *head);

/**
 * @brief list_is_first -- tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
bool libc_list_is_first(struct libc_list_type *entry, struct libc_list_type *head);

/**
 * @brief list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
bool libc_list_is_last(struct libc_list_type *entry, struct libc_list_type *head);

/**
 * @brief list_is_head - tests whether @list is the list @head
 * @list: the entry to test
 * @head: the head of the list
 */
bool libc_list_is_head(struct libc_list_type *entry, struct libc_list_type *head);
/**
 * @brief list_empty - tests whether a list is empty
 * @head: the list to test.
 */
bool libc_list_is_empty(struct libc_list_type *head);

/*
 * offsetof - offsetof
 */
#define offsetof(TYPE, MEMBER)	((unsigned long int)&((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define libc_list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#endif /* LIBC_LIST_H_ */
