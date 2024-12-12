release:
	gcc  -std=c99 poppatch.c coat.c process.c -lz -o poppatch -O3
debug:
	gcc  -std=c99 -Wall -Wextra poppatch.c coat.c process.c -lz -o poppatch