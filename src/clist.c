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
 @file
 @brief Function definitions for clist.h

 This file provides function definitions for clist.h.
*/

#include "../include/clist.h"
#include <stdlib.h>

struct clist *clist_init(size_t item_size)
{
    // I am lazy.
    struct clist *clist = (struct clist *)malloc(sizeof(struct clist));
    clist->begin = NULL;
    clist->current = NULL;
    clist->end = NULL;
    clist->current_index = 0;
    clist->item_size = item_size;
    clist->list_length = 0;
    return clist;
}

size_t clist_free(struct clist *clist)
{
    struct node *temp_node;
    for (temp_node = clist->begin; temp_node != NULL; temp_node = temp_node->next)
    {
        if (clist->current->item)
        {
            free(clist->current->item);
        }
        if (clist->current)
        {
            free(clist->current);
        }
    }
    free(clist);
}