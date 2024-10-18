# Program design

## Minimal viable product

These are all the items needed to have a working product.
- [x] Sanity checks
    - [x] Correct number of arguments
    - [x] First argument opens
    - [x] Second argument opens
    - [x] Establish output prefix
    - [x] Can output be opened?
    - [x] errno
- [x] Remove `\n`s from FASTA 
- [x] Write coat function
    - [x] Loop through SAM
    - [x] fix end of fasta
    - [x] Get to correct position
    - [x] Do cigar operation
        - [x] interpret cigar correctly
        - [x] (mis)matches
            - [x] Write reference as is
            - [x] Change to sam:seq_10
        - [x] deletions
        - [x] insertions
        - [x] clipping
- [x] Convert stretch back to fasta
- [x] Quit if function unsuccessful
- [x] Process SAM to remove overlaps
    - [x] Take only first map
        - [x] Skip over beginning of subsequent maps
- [x] Make temp dir name same as prefix
- [ ] Makefile

```bash
# Example commands
./poppatch.out ~/Documents/Data/True/SArsHG38p13Sorted.sam \
~/Documents/Data/True/GRCh38p13.fna \
~/Documents/Data/poppatch

# Small set
./poppatch.out ~/Documents/Data/Mock/small.sam \
~/Documents/Data/Mock/converted.fa

# Overlaps included
./poppatch.out ~/Documents/Data/Mock/overlaps.sam \
~/Documents/Data/Mock/converted.fa
```

## Nice to haves

These are all the features that will improve on the usability.
- [ ] Read BAM
- [x] give arguments in any order using flags
- [ ] Check that file types are correct
    - [ ] SAM starts with a '@'
    - [ ] FASTA starts with a '>'
- [ ] Do something with the unaligned sequences
- [ ] Check storage space before starting
- [ ] Show progress somehow (ftell(reference) / sizeof(reference))
- [x] Log file
- [ ] Process SAM to remove overlaps
    - [ ] Take a SAM and write a SAM
    - [ ] Consense overlaps?
        - [ ] Each coordinate is an array
            - [ ] Per scaffold to minimise memory

## Things to fix
- [ ] Prefix is not being picked up

# Progress

## 12 December 2023

I had to remake my reference. Luckily, I already had my align files, so I just to re-run PopPatch on it. 

I had some unexpected behaviour. The command was:

```bash
./poppatch.out -m Data/SArsHG38p13Sorted.sam -r Data/GRCh38p13.fna -f coat -p SApop2023
```

Output:

```bash
PopPatch 1.0a
Map: Data/SArsHG38p13Sorted.sam
Reference: Data/GRCh38p13.fna
Function: coat
Prefix: (null)
Options checked
Stretching reference (removing new lines)...
Done.
Coating old reference...
Done.
Restructuring scaffolds (80 bases per line)...
Done.
```

There is something wrong with the `-p` (prefix) tag. Added it to [Things to fix](#things-to-fix). Another issue is that the file "[usage](../DOCS/usage)" prints more like a help doc and there is no `--usage` option.