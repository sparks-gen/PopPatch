// Std libraries
#include <stdio.h>
#include <zlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <getopt.h>

// My libraries
#include "process.h"
#include "coat.h"

// Variables
char *PREFIX = "poppatch";

// Prototypes
struct option longopts[] = {
    {"function", required_argument, 0, 'f'},
    {"help", no_argument, 0, 'h'},
    {"usage", no_argument, 0, 'u'},
    {"map", required_argument, 0, 'm'},
    {"prefix", optional_argument, 0, 'p'},
    {"reference", required_argument, 0, 'r'},
    {"version", no_argument, 0, 'v'}
  };

// Main
int main(int argc, char *argv[])
{
    // Print name and version
    fprintf(stdout, "PopPatch ");
    FILE *version = fopen("DOCS/version", "r");
    char c;
    while (isspace(c = fgetc(version)) == 0)
    {
        fprintf(stdout, "%c", c);
    }
    fprintf(stdout, "\n\n");
    fclose(version);

    // Open usage info
    FILE *usage = fopen("DOCS/usage", "r");
    char basic[80];
    fgets(basic, 80, usage);

    // Correct number of arguments
    if (argc == 1)
    {
        fprintf(stderr, "Incorrect usage.\n\n");
        fprintf(stdout, "%s\n", basic);
        fclose(usage);
        return 1;
    }

    int indexptr = 0;
    char opt;
    char function;
    char map[PATH_LEN];
    char prefix[PATH_LEN];
    memset(prefix, '\0', PATH_LEN);
    char reference[PATH_LEN];
    while ((opt = getopt_long(argc, argv, "f:hum:p::r:v:", longopts, &indexptr)) != -1)
    {
        switch (opt)
        {
        case 'f':
            if (strcmp(optarg, "coat") == 0)
            {
                function = 'c';
            }
            else if (strcmp(optarg, "pan") == 0)
            {
                function = 'p';
            }
            else
            {
                fprintf(stderr, "Unknown function: %s\n", optarg);
                fprintf(stdout, "\n%s\n", basic);
                return 1;
            }
            fprintf(stdout, "Function: %s\n", optarg);
            break;
        case 'h':
            fseek(usage, 0, SEEK_SET);
            while((c = fgetc(usage)) != EOF)
            {
                fprintf(stdout, "%c", c);
            }
            fclose(usage);
            return 0;
        case 'u':
            fseek(usage, 0, SEEK_SET);
            while((c = fgetc(usage)) != EOF)
            {
                fprintf(stdout, "%c", c);
            }
            return 0;
        case 'm':
            sprintf(map, "%s", optarg);
            fprintf(stdout, "Map: %s\n", map);
            break;
        case 'p':
            sprintf(prefix, "%s", optarg);
            fprintf(stdout, "Prefix: %s\n", prefix);
            break;
        case 'r':
            sprintf(reference, "%s", optarg);
            fprintf(stdout, "Reference: %s\n", reference);
            break;
        case 'v':
            version = fopen("DOCS/version", "r");
            while ((c = fgetc(version)) != '\n')
            {
                fprintf(stdout, "%c", c);
            }
            fprintf(stdout, "\n%s\n", basic);
            return 0;
        // case '?':
        //     fprintf(stdout, "\n%s\n", basic);
        //     break; this causes default not to work
        default:
            fprintf(stdout, "\n%s\n", basic);
            return 1;
        }
    }

    fprintf(stdout, "Options checked\n");

    // Sam file opens
    FILE *insam = fopen(map, "r");
    if (!insam)
    {
        fprintf(stderr, "Cannot open %s\n\n", map);
        fprintf(stdout, "%s\n", basic);
        fclose(usage);
        return errno;
    }
    fclose(insam);

    // Reference file opens
    gzFile infa = gzopen(reference, "r");
    if (!infa)
    {
        fprintf(stderr, "Cannot open %s\n\n", reference);
        fprintf(stdout, "%s\n", basic);
        fclose(usage);
        return errno;
    }
    gzclose(infa);

    // Establish output prefix
    if (prefix[0] == '\0')
    {
        strcpy(prefix, PREFIX);
    }
    char output[PATH_LEN];
    sprintf(output, "%s.fa", prefix);

    // Open output
    FILE *outfa = fopen(output, "w");
    if (!outfa)
    {
        fprintf(stderr, "Cannot open %s\n\n", output);
        fprintf(stdout, "%s\n", basic);
        fclose(usage);
        return errno;
    }
    fclose(outfa);

    // Check log file
    char log_file[PATH_LEN];
    sprintf(log_file, "%s.log", prefix);
    FILE *log = fopen(log_file, "w");
    if (!log)
    {
        fprintf(stderr, "Could not create %s", log_file);
        fprintf(stdout, "%s\n", basic);
        fclose(usage);
        return errno;
    }
    fclose(log);

    // Make temporary directory
    char tempDir[PATH_LEN];
    sprintf(tempDir, "%s", prefix);
    mkdir(tempDir, 0755);

    // Usage no longer needed
    fclose(usage);
    
    // Remove \n from fasta
    fprintf(stdout, "Stretching reference (removing new lines)...\n");
    stretchSeq(reference, prefix);
    fprintf(stdout, "Done.\n");

    // Do the thing
    if (function == 'c')
    {
        // Coat genome
        fprintf(stdout, "Coating old reference...\n");
        int patch = coat(map, prefix);
        if (patch != 0)
        {
            fprintf(stderr, "Error coating genome.\n\n");
            rmdir(tempDir);
            return patch;
        }
        fprintf(stdout, "Done.\n");
    }
    else if (function == 'p')
    {
        // Create pan genome
    }
    

    // Restructure fasta
    fprintf(stdout, "Restructuring scaffolds (80 bases per line)...\n");
    if (stdSeq(prefix) != 0)
    {
        fprintf(stderr, "Could not finish new reference");
        return errno;
    }
    fprintf(stdout, "Done.\n");

    // Success
    rmdir(tempDir);
    return 0;
}
