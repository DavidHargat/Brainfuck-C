#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

// How many memory 'cells' are allocated
#define MEMORY_SIZE (30000)

char *find_matching_open(char *p) {
	int skip = 0;

	while (*(--p)) {
		if (*p == ']') {
			skip++;
		} else if (*p == '[') {
			if (skip == 0) {
				return p;
			} else {
				skip--;
			}
		}
	}

	return NULL; /* matching bracket not found */
}

char *find_matching_close(char *p) {
	int skip = 0;

	while (*(++p)) {
		if (*p == '[') {
			skip++;
		} else if (*p == ']') {
			if (skip == 0) {
				return p;
			} else {
				skip--;
			}
		}
	}

	return NULL; /* matching bracket not found */
}

int run(char *program) {
	char *p;
	char mem[MEMORY_SIZE];
	char *m;
	char c;

	// set cells to zero
	bzero(mem, sizeof(mem));

	// instruction pointer
	p = program;

	// memory pointer
	m = mem;

	// current instruction
	c = *p;

	// Reads to end of string.	
	while (c != '\0') {
		switch (c) {
		case '>':
			m++;
			break;

		case '<':
			m--;
			break;

		case '+':
			(*m)++;
			break;

		case '-':
			(*m)--;
			break;

		case '.':
			fputc(*m, stdout);
			break;

		case ',':
			(*m) = getc(stdin);
			break;

		case '[':
			if (*m == 0) {
				p = find_matching_close(p);
				if (p == NULL) {
					printf("unbalanced brackets\n");
					return 1;
				}
			}
			break;

		case ']':
			if (*m) {
				p = find_matching_open(p);
				if (p == NULL) {
					printf("unbalanced brackets\n");
					return 1;
				}
			}
			break;

		default:
			break;
		}

		// move instruction pointer forward
		c = *(++p);
	}

	return 0;
}

char *alloc_file(char *filename) {
	int fd;
	struct stat info;
	char *buf;
	ssize_t size;

	if (stat(filename, &info) == -1)
		{ perror("stat"); return NULL; }

	if ((fd = open(filename, O_RDONLY)) == -1)
		{ perror("open"); return NULL; }

	if ((buf = (char *)malloc(info.st_size + 2)) == NULL)
		{ perror("malloc"); close(fd); return NULL; }
	
	if ((size = read(fd, buf + 1, info.st_size)) == -1)
		{ perror("read"); close(fd); return NULL; }

	if (size != info.st_size)
		{ printf("unexpected read (%ld != %lld)\n", size, info.st_size); close(fd); return NULL; }

	/* We pad the beginning and end with nul bytes, so the interpreter knows where to halt.
	 */
	buf[0] = buf[size] = '\0';

	close(fd);
	return buf + 1;
}

int main(int argc, char **argv) {
	char *program;

	if ((argc == 2)
			&& (program = alloc_file(argv[1]))
			&& program) {
		return run(program);
	}

	printf("Usage: %s <filename>\n", argv[0]);
	return 1;
}
