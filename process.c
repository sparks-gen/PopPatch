// Standard libraries
#include <stdio.h>
#include <zlib.h>
#include <errno.h>
#include <string.h>

// My libraries
#include "process.h"

// Definitions

// Global variables
int PATH_LEN = 100;
int MARGIN = 80;
int MAXCHAR = 4095;

// Functions
int stretchSeq(char const *in_fasta, char *prefix)
{

    // Open input
    gzFile in_reference = gzopen(in_fasta, "r");

    // Create output
    char outfile[PATH_LEN];
    sprintf(outfile, "%s/stretch.fa", prefix);
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        return errno;
    }

    // Loop variables
    char c;
    char description[MARGIN * 2];

    // Log variables
    char log_file[PATH_LEN];
    sprintf(log_file, "%s.log", prefix);
    FILE *log = fopen(log_file, "a");
    unsigned int fileSize = 0;
    unsigned int seqSize = 0;

    // Loop through FASTA
    while ((c = gzgetc(in_reference)) != EOF)
    {
        // If it is a new description line
        if (c == '>')
        {
            if (ftell(outptr) > 0)
            {
                fprintf(outptr, "\n");
            }
            memset(description, '\0', sizeof(description));
            gzgets(in_reference, description, MARGIN * 2);
            fprintf(outptr, ">%s", description);
            fileSize = fileSize + 1 + (int)strlen(description);
        }
        // Else, print seq
        else if (c != '\n')
        {
            fprintf(outptr, "%c", c);
            fileSize++;
            seqSize++;
        }
    }
    fprintf(outptr, "\n");
    fileSize++;

    fprintf(log, "File size: %i\nSequence length: %i\n", fileSize, seqSize);

    // Success
    fclose(outptr);
    fclose(log);
    gzclose(in_reference);
    return seqSize;
}

int stdSeq(char *out_prefix)
{
    // Open temp stretch
    char in_stretch[PATH_LEN];
    sprintf(in_stretch, "%s/stretch_out.fa", out_prefix);
    FILE *stretch = fopen(in_stretch, "r");
    if (!stretch)
    {
        return errno;
    }

    // Open output
    char out_file[PATH_LEN];
    sprintf(out_file, "%s.fa", out_prefix);
    FILE *out_ref = fopen(out_file, "w");
    if (!out_ref)
    {
        return errno;
    }

    // Loop variables
    char c;
    char description[MARGIN * 2];
    int cursor = 0;

    // Loop through stretch fasta
    while ((c = fgetc(stretch)) != EOF)
    {
        // Description line
        if (c == '>')
        {
            memset(description, '\0', sizeof(description));
            fgets(description, MARGIN * 2, stretch);
            fprintf(out_ref, ">%s", description);
            cursor = 0;
        }
        // Sequence
        else
        {
            while (c != '\n')
            {
                if (cursor < MARGIN)
                {
                    fprintf(out_ref, "%c", c);
                    cursor++;
                }
                else
                {
                    fprintf(out_ref, "\n%c", c);
                    cursor = 1;
                }
                c = fgetc(stretch);
            }
            fprintf(out_ref, "\n");
        }
    }

    // Remove old stretch fasta
    remove(in_stretch);

    // Success
    return 0;
}

