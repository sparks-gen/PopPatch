# Using PopPatch safely (interim — before the bug fixes / Rust rewrite)

PopPatch's core function works: it correctly patches a reference genome with a
population's aligned sequence. But the current build has three bugs that **crash on
the commands shown in its own README**, one bug that **silently corrupts output**, and
several undocumented input requirements. Until these are fixed, follow the rules below.
Every rule here was confirmed by running the compiled binary.

---

## The command to use

Run it **from inside the cloned PopPatch directory** (it reads `DOCS/` by relative path):

```sh
# from within the PopPatch/ repo directory, after `make`
./poppatch -f coat -m sorted.sam -r reference.fna -pOUTPREFIX
```

Then **always** validate and repair the output (see the validator at the bottom):

```sh
python3 validate_poppatch.py --reference reference.fna --output OUTPREFIX.fa --fixed OUTPREFIX.fixed.fa
```

Use `OUTPREFIX.fixed.fa` as your reference genome, not the raw `OUTPREFIX.fa`.

---

## Rules (all verified by execution)

1. **Run from the repo directory.** The binary opens `DOCS/version` and `DOCS/usage`
   with unchecked relative paths; from any other directory it segfaults.
2. **Attach the prefix with no space: `-pNAME`, never `-p NAME`.** The space form
   segfaults. (The README example `-p newReference` is the crashing form — don't copy it.)
3. **Keep all paths short — well under ~90 characters.** Paths are copied into fixed
   100-byte buffers with no bounds check; long paths corrupt the stack. Work from a
   directory close to the data and use short names, not long absolute paths.
4. **Do not use `-v`.** It is mis-declared and errors out. Use `-h` for help.
5. **Input SAM must be coordinate-sorted**, and reference scaffolds must appear in the
   same order the SAM first references them. The internal cursor is forward-only; wrong
   order silently produces a wrong genome. Sort first:
   `samtools sort -O sam -o sorted.sam aln.sam`
6. **SAM only, not BAM.** Convert first: `samtools view -h aln.bam > aln.sam`.
7. **Validate + repair every output** (rule below explains why).

---

## The silent-corruption bug (why validation is mandatory)

**What happens:** Scaffolds located *after the last scaffold that receives an alignment*
are corrupted in the output — the tool drops the `>` on each such scaffold's header
(fusing it onto the previous sequence) and truncates its final base. Scaffolds that
receive at least one alignment, and everything up to the last aligned scaffold, are fine.

**Why it bites real data:** The vulnerable scaffolds are the *untouched trailing* ones —
in a real reference these are the unplaced contigs / decoy sequences at the end of the
FASTA, which often get few or no alignments. So the corruption tends to hit exactly the
tail of a real genome, quietly.

**Why it's cheap to repair:** The corrupted scaffolds are *unchanged* ones (no alignment
means their correct content is identical to the input reference). So the fix is to detect
them and copy them verbatim from the original reference. The validator does this.

**What to check:** output scaffold count == input; every scaffold present with its `>`
header intact; each untouched scaffold's length == input length.

---

## Semantic behavior to be aware of (not bugs — design choices)

- **Deletions become `N`.** Where the assembly is missing bases present in the reference
  (CIGAR `D`), the output gets a run of `N`, not the original reference base.
- **Insertions are dropped.** Bases the assembly has but the reference doesn't (CIGAR `I`)
  are discarded, to keep reference coordinates.
- **Overlaps: first alignment wins.** Where two alignments overlap, the first is kept and
  the overlapping part of the second is discarded (counted as a "backtrack" in the `.log`).
- **Unaligned records are skipped** and noted in the `.log`.

Read the `OUTPREFIX.log` file after each run — it reports the backtrack count and any
unaligned or unknown-CIGAR records.

---

## Not available yet

- `-f pan` (pan-genome) is advertised in the help text but is an empty stub — it does nothing.
- BAM input, progress display, and input-format sanity checks are not implemented.
