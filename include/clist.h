/*
 * The MIT License (MIT)
 * Copyright (c) 2022 Zhengli Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 @defgroup clist
*/

/*!
 @file
 @brief Provides the function prototypes and the list structures.
 @ingroup clist
 This header provides the prototypes of the list functions for the
 source files and provides the node and the list structure.
*/

#include <stdlib.h>

#ifndef __CLIST_H
#define __CLIST_H

struct node
{
    /*!
     @struct node
     @brief A single node element for the list

     A node is a single point on a linked list. **A node shouldn't
     have to be accessed in your program by yourself since you
     should normally handle data access with the functions for the
     clist and not directly access the data on a node.** :)
     Do you like the Octocat? I like cats in general.

     @var node::prev
     A pointer pointing to a node-typed pointer (recursive typed), which
     is the previous node on the linked list.
     This is set to NULL if the list starts on this node.

     @var node::item
     A void pointer, which should point to the data the user (you :)
     provides.

     @var node::next
     A pointer pointing to a node-typed pointer (recursive type, lol),
     which is the next node on the linked list.
     This is set to NULL if the list ends on this node.
    */
    struct node *prev;
    void *item;
    struct node *next;
};

struct clist
{
    /*!
     @struct clist
     @brief A double-way linked list

     This structure is a double-way linked list. It should
     be modified and accessed with the functions written for
     this purpose, which should be found in /src.

     @var clist::begin
     A node-typed pointer that points to the node which is the beginning
     of the list.

     @var clist::current
     A node-typed pointer that points to the node which is the current
     element "focused".

     @var clist::end
     A node-typed pointer that points to the node which is the end of
     the list.

     @var clist::item_size
     A size_t variable which describes the size of data that is stored
     into a single node.

     @var clist::current_index
     An unsigned long variable that is used to note at which index clist::current is,
     on the list.

     @var clist::list_length
     A size_t variable indicating the list length/item count that is updated
     on every list operation involving removal or insertion of items.
    */
    struct node *begin;
    struct node *current;
    struct node *end;
    size_t item_size;
    unsigned long current_index;
    size_t list_length;
};

/*!
 @brief Create a clist.

 This function is used to create a clist, performing all
 necessary steps while doing this.

 @param item_size
 Specifies how big one "item" is. An item is a block of data
 that is defined by you and will be stored on the linked list.
 No explicit type for an item is required, just provide the size
 of the item.

 @return a pointer to the clist that is created, NULL if failed.
*/
struct clist *clist_init(size_t item_size);

/*!
 @brief Frees a list.

 The function frees all memory which was allocated for the list.

 @param clist
 The pointer to a clist which (including all its items) should be
 freed.

 @return The count of items in the list.
*/
size_t clist_free(struct clist *clist);

/*!
 @brief Append an item.

 Append an item at the end of the list while still staying on the
 current index. clist::list_length is updated accordingly.

 @param clist
 The list to be operated on. This has to be a pointer pointing to
 the list, since we are modifying clist::end.

 @param item
 A pointer to the item that has to to be appended.

 @return A pointer to the item on the newly appended node. If failed
 appending a node at all, returns NULL.
*/
void *clist_append(struct clist *clist, void *item);

/*!
 @brief Pops the last item from a clist.

 The last item is popped from a clist. clist::list_length is updated
 accordingly. If clist::current is the last index node, i.e. clist::current
 will be popped after this function, move one node back.

 @param clist
 The list to be operated on.

 @return The item that was popped. If no item was popped because
 the length of the list was too short, returns NULL.
*/
void *clist_pop(struct clist *clist);

/*!
 @brief Returns the length of the list.

 Returns clist::list_length.

 @param clist
 The list to be operated on.

 @return Returns clist::list_length.
*/
size_t clist_length(const struct clist *clist);

/*!
 @brief Jump to the given index.

 Jumps to the given index and returns the item on that index.

 @param clist
 The list to be operated on.

 @param index
 The index to jump to.

 @return The item on that index of the list if succeeded, NULL
 if failed (possible reasons are out-of-index access etc.).
*/
void *clist_jump(struct clist *clist, unsigned long index);

/*!
 @brief Return the item on the current index.

 Returns the item on the current index.

 @param clist
 The list to be operated on.

 @return The item on the current index of the list.
*/
void *clist_read(const struct clist *clist);

/*!
 @brief Replace the item on the current index.

 Replaces the item on the current index, with item.

 @param clist
 The list to be operated on.

 @param item
 The item that should replace the item on the current index.

 @return The item that was previously on the current index.
*/
void *clist_write(const struct clist *clist, void *item);

/*!
 @brief Insert an item.

 On the list, insert an item after the index specified by index. The current 
 index (clist::current) is preserved.

 @param clist
 The list to be operated on.

 @param item
 The item to insert.

 @param index
 The index after which to insert the item.

 @return The item if insertion was successful, otherwise NULL.
*/
void *clist_insert(struct clist *clist, void *item, unsigned long index);

/*!
 @brief Remove an item.

 Removes the item specified by index. If the current index (clist::current) 
 is to be removed, move one index back. If this is not possible, move one index
 forward. If neither of both is possible, clist::current is set to NULL.

 @param clist
 The list to be operated on.

 @param index
 The index which has to be removed.
 
 @return The removed item if succeeded, NULL if failed.
*/
void *clist_remove(struct clist *clist, unsigned long index);

#endif