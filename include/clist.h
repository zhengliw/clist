/*!
 @brief Provides the function definitions and the list structures.

 This header provides the definitions of the list functions for the
 source files and provides the node and the list structure.
*/

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

#include <stdlib.h>

#ifndef __CLIST_H
#define __CLIST_H

struct node {
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
    struct node * prev;
    void * item;
    struct node * next;
};

struct clist {
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
     A long variable that is used to note at which index clist::current is,
     on the list.
    */
    struct node * begin;
    struct node * current;
    struct node * end;
    size_t item_size;
    long current_index;
};

/*!
 @brief Create a clist.
 
 This function is used to create a clist, performing all
 necessary steps while doing this.

 @param item_size
 Specifies how big one "item" is. An item is a block of data
 that is defined by you and will be stored on the linked list.
 No explicit type for an item is required, Just provide the size
 of the item.

 @return a pointer to the clist that is created, NULL if failed.
*/
struct clist * clist_init(size_t item_size);

#endif