#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make bracket jumps constant time

// How many memory 'cells' are allocated
#define MEMORY_SIZE (30000)

struct bf_state {
	char memory[MEMORY_SIZE];
	char *m;
	char *p;
	char  c;
};

typedef struct bf_state bf_state;

char *find_matching_bracket(char *p, char bracket) {
	int skip;
	char c;
	char matching;
	skip = 0;
	matching = (bracket == '[') ? ']' : '[';
	while(1) {
		if( bracket == '[' )
		{
			c = *(++p);
		}
		else
		{
			c = *(--p);
		}
		if( c == bracket )
		{
			skip++;
		}
		else if( c == matching )
		{
			if( skip == 0 ){
				return p;
			}else{
				skip--;
			}
		}
	}
}

void run(char *program) {
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
	while( c != '\0' ) {
		switch(c) {
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
			if( (*m) == 0 ) {
				p = find_matching_bracket(p, '[');
			}
			break;

		case ']':
			if( (*m) != 0 ) {
				p = find_matching_bracket(p, ']');
			}
			break;

		default:
			break;
		}

		// move instruction pointer forward
		c = *(++p);
	}
}

char *readfile(char *filename) {
	char *buffer;
	long length;
	FILE *f;
	int result;

	if( ( f = fopen(filename, "r") ) == NULL ) {
		return NULL;
	}

	if( fseek(f, 0, SEEK_END) == -1 ) {
		fclose(f);
		return NULL;
	}

	if( ( length = ftell(f) ) == -1 ) { 
		fclose(f);
		return NULL;
	}

	if( ( result = fseek(f, 0, SEEK_SET) ) == -1 ) {
		fclose(f);
		return NULL;
	}

	if( ( buffer = malloc(length+1) ) == NULL ) {
		fclose(f);
		return NULL;
	}

	fread(buffer, 1, length, f);

	fclose(f);

	buffer[length] = '\0'; // NULL terminator.

	return buffer;
}

int main(char argc, char **argv) {

	char *program = readfile(argv[1]);
	if( program != NULL ) {
		run(program);
	}else{
		printf("Usage: bf <filename>\n");
		perror("ERROR");
	}

	return 0;
}
