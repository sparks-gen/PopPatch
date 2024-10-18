#ifndef PROCESS_H_
#define PROCESS_H_

#include <zlib.h>

// Variables
extern int PATH_LEN;
extern int MARGIN;
extern int MAXCHAR;

// Functions
int stretchSeq(char const *in_fasta, char *prefix);

int stdSeq(char *out_prefix);

#endif