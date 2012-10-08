// (C) Copyright 2004, David M. Blei (blei [at] cs [dot] cmu [dot] edu)

// This file is part of LDA-C.

// LDA-C is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your
// option) any later version.

// LDA-C is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA

#include "lda-data.h"

corpus* read_data(char* data_filename)
{
    FILE *fileptr;
    long length, count, word, n, nd, nw, ml;
    corpus* c;

    printf("reading data from %s\n", data_filename);
    c = malloc(sizeof(corpus));
    c->docs = 0;
    c->num_terms = 0;
    c->num_docs = 0;
    c->max_length = 0;
    fileptr = fopen(data_filename, "r");
    nd = 0; nw = 0; ml = 0;
    while ((fscanf(fileptr, "%10ld", &length) != EOF))
    {
	c->docs = (document*) realloc(c->docs, sizeof(document)*(nd+1));
	c->docs[nd].length = length;
	c->docs[nd].total = 0;
	c->docs[nd].words = malloc(sizeof(long)*length);
	c->docs[nd].counts = malloc(sizeof(long)*length);
	if (length > ml) { ml = length; }
	for (n = 0; n < length; n++)
	{
	    fscanf(fileptr, "%10ld:%10ld", &word, &count);
	    word = word - OFFSET;
	    c->docs[nd].words[n] = word;
	    c->docs[nd].counts[n] = count;
	    c->docs[nd].total += count;
	    if (word >= nw) { nw = word + 1; }
	}
	nd++;
    }
    fclose(fileptr);
    c->num_docs = nd;
    c->num_terms = nw;
    c->max_length = ml;
    printf("number of docs    : %ld\n", nd);
    printf("number of terms   : %ld\n", nw);
    return(c);
}

