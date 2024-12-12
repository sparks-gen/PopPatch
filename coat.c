// Standard libraries
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

// My libraries
#include "process.h"
#include "coat.h"

// Definitions

// Variables

// Functions
int coat(char const *sam_name, char *prefix)
{
    // Open strected fasta
    char stretch_file[PATH_LEN];
    sprintf(stretch_file, "%s/stretch.fa", prefix);
    FILE *stretch = fopen(stretch_file, "r");
    if (!stretch)
    {
        return errno;
    }

    // Create stretch output
    char out_file[PATH_LEN];
    sprintf(out_file, "%s/stretch_out.fa", prefix);
    FILE *out_ref = fopen(out_file, "w");
    if (!out_ref)
    {
        return errno;
    }

    // Open SAM
    FILE *in_sam = fopen(sam_name, "r");

    // Log variables
    char log_file[PATH_LEN];
    sprintf(log_file, "%s.log", prefix);
    FILE *log = fopen(log_file, "a");
    int overlaps = 0;

    // Loop variables
    char temp[MAXCHAR];
    char c;
    int offset;

    // Skip SAM header
    while ((fgetc(in_sam)) == '@')
    {
        fgets(temp, MAXCHAR, in_sam);
    }
    // Move back a char to let go of first letter of qname_1
    fseek(in_sam, -1, SEEK_CUR);

    // SAM variables
    char qname_1[MARGIN], rname_3[MARGIN], cigar_6[MAXCHAR];
    int pos_4, cigar_len;
    char cigar_op;

    // FASTA variables
    char description[MARGIN * 2], id[MARGIN];
    int scaf_pointer = 0;
    fgets(description, MARGIN * 2, stretch);
    memset(id, '\0', sizeof(id));
    for (size_t i = 1; isspace(description[i]) == 0; i++)
    {
        id[i - 1] = description[i];
    }
    fprintf(out_ref, "%s", description);

    // Loop through SAM
    while ((c = fgetc(in_sam)) != EOF)
    {
        memset(qname_1, '\0', sizeof(qname_1)); // Get qname_1
        qname_1[0] = c;
        for (size_t i = 1; isspace(c = fgetc(in_sam)) == 0; i++)
        {
            qname_1[i] = c;
        }
        // Copilot help:
        // while (isspace(fgetc(in_sam)) == 0)
        // {
        //     // Do nothing
        // }
        for (size_t i = 1; isspace(fgetc(in_sam)) == 0; i++)
        {
            ;
        }                                       // Skip flag_2
        memset(rname_3, '\0', sizeof(rname_3)); // Get rname_3
        for (size_t i = 0; isspace(c = fgetc(in_sam)) == 0; i++)
        {
            rname_3[i] = c;
        }
        memset(temp, '\0', sizeof(temp)); // Get pos_4
        for (size_t i = 0; isspace(c = fgetc(in_sam)) == 0; i++)
        {
            temp[i] = c;
        }
        pos_4 = atoi(temp);
        for (size_t i = 1; isspace(fgetc(in_sam)) == 0; i++)
        {
            ;
        }                                       // Skip mapq_5
        memset(cigar_6, '\0', sizeof(cigar_6)); // Get cigar_6
        for (size_t i = 0; isspace(c = fgetc(in_sam)) == 0; i++)
        {
            cigar_6[i] = c;
        }
        for (size_t i = 1; isspace(fgetc(in_sam)) == 0; i++)
        {
            ;
        } // Skip rnext_7
        for (size_t i = 1; isspace(fgetc(in_sam)) == 0; i++)
        {
            ;
        } // Skip pnext_8
        for (size_t i = 1; isspace(fgetc(in_sam)) == 0; i++)
        {
            ;
        } // Skip tlen_9
        // fprintf(stdout, "%s\t%s\t%i\t%s\n", qname_1, rname_3, pos_4, cigar_6);

        // Only continue if query was aligned
        if (cigar_6[0] != '*')
        {
            // Get description line until it matches
            while (strcmp(id, rname_3) != 0)
            {
                // Go through input until new description is found
                while ((c = fgetc(stretch)) != '>')
                {
                    fprintf(out_ref, "%c", c);
                }

                // Get description
                memset(description, '\0', sizeof(description));
                fgets(description, MARGIN * 2, stretch);

                // Isolate id
                memset(id, '\0', sizeof(id));
                for (size_t i = 0; isspace(description[i]) == 0; i++)
                {
                    id[i] = description[i];
                }
                fprintf(out_ref, ">%s", description);

                // New scaffold starts at 0
                scaf_pointer = 0;
            }

            // Get offset
            offset = pos_4 - 1 - scaf_pointer;

            // Only move forward
            if (offset > 0)
            {
                // Get to pos_4
                for (int i = 0; i < offset; i++)
                {
                    fprintf(out_ref, "%c", fgetc(stretch));
                }
                scaf_pointer = pos_4 - 1;
                offset = 0;
            }
            else
            {
                overlaps++;
            }

            // Read cigar_6
            for (size_t i = 0; i < strlen(cigar_6); i++)
            {
                // Get first operator and length
                memset(temp, '\0', sizeof(temp));
                for (size_t j = 0; cigar_6[i] <= '9'; j++)
                {
                    temp[j] = cigar_6[i];
                    i++;
                }
                cigar_len = atoi(temp);
                cigar_op = cigar_6[i];
                if (cigar_op == 'M')
                {
                    // If entire match is to be ignored
                    if ((offset + cigar_len) < 0)
                    {
                        // Skip seq_10 and adjust offset
                        fseek(in_sam, cigar_len, SEEK_CUR);
                        offset += cigar_len;
                    }
                    else
                    {
                        // There is still some offset
                        if (offset < 0)
                        {
                            fseek(in_sam, -1 * offset, SEEK_CUR);
                            cigar_len += offset;
                            offset = 0;
                        }
                        fseek(stretch, cigar_len, SEEK_CUR);
                        for (int j = 0; j < cigar_len; j++)
                        {
                            fprintf(out_ref, "%c", fgetc(in_sam));
                        }
                        scaf_pointer += cigar_len;
                    }
                }
                else if (cigar_op == 'D')
                {
                    // If entire deletion is to be ignored
                    if ((offset + cigar_len) < 0)
                    {
                        // Nothing to skip over, but adjust offset
                        offset += cigar_len;
                    }
                    else
                    {
                        // If there is still some offset
                        if (offset < 0)
                        {
                            cigar_len += offset;
                            offset = 0;
                        }
                        fseek(stretch, cigar_len, SEEK_CUR);
                        for (int j = 0; j < cigar_len; j++)
                        {
                            fprintf(out_ref, "N");
                            // fprintf(out_ref, "%c", fgetc(stretch));
                        }
                        scaf_pointer += cigar_len;
                    }
                }
                else if (cigar_op == 'I')
                {
                    // Inserts have no effect on the offset
                    fseek(in_sam, cigar_len, SEEK_CUR);
                }
                else if (cigar_op == 'S')
                {
                    fseek(in_sam, cigar_len, SEEK_CUR);
                }
                else if (cigar_op != 'H')
                {
                    fprintf(log, "Unknown cigar operator, %c", cigar_op);
                }
            }
        }
        // Query seq was unaligned
        else
        {
            // Unaligned sequences are to be dealt with here
            fprintf(log, "%s was unaligned", qname_1);
        }

        // Skip rest of SAM
        for (size_t i = 0; fgetc(in_sam) != '\n'; i++)
        {
            ;
        }
    }

    // Finish FASTA
    fseek(stretch, -1, SEEK_CUR); // I don't know why
    while ((c = fgetc(stretch)) != EOF)
    {
        while ((c = fgetc(stretch)) != '\n')
        {
            fprintf(out_ref, "%c", c);
        }
        fprintf(out_ref, "\n");
        if (c == '>')
        {
            memset(description, '\0', sizeof(description));
            fgets(description, MARGIN * 2, stretch);
            fprintf(out_ref, "%s", description);
            while ((c = fgetc(stretch)) != '\n')
            {
                fprintf(out_ref, "%c", c);
            }
            fprintf(out_ref, "\n");
        }
    }

    // Write log
    fprintf(log, "Number of backtracks: %i\n", overlaps);

    // Close all files
    fclose(stretch);
    fclose(in_sam);
    fclose(out_ref);
    fclose(log);

    // Remove old stretch
    remove(stretch_file);

    // Success
    return 0;
}
