#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * @author David Hargat
 * @email DavidHargat@yahoo.com
 * @liscence
 */

void run(char *program){
	char *p = program;

	// How many memory 'cells' are allocated
	int size = 30000; 	
	
	// Allocate
	char *m = malloc(size);
	// Initialize cells as zero.
	bzero(m,size);

	// The current instruction
	char c = *(p++);

	// Reads to end of string.	
	while( c!='\0' ){
		// Basic memory pointer instructions:
		if( c == '>' ) m++; // Forward
		if( c == '<' ) m--; // Backward
		if( c == '+' ) (*m)++; // Increment
		if( c == '-' ) (*m)--; // Decrement

		// Output char:
		if( c == '.' ) fputc((*m), stdout);
		
		// Input char:
		// Subsituted EOF for 0 since EOF isn't a valid char. 		
		if( c == ',' ){
			char t = fgetc(stdin);
			if( t!=EOF )
				(*m)=t;
			else
				(*m)=0;
		}

		// Jump Forward If Zero:
		if( c == '[' ){
			if( (*m)==0 ){
				int skip = 0;
				while( (*p)!=']' || skip>0 ){
					p++;
					if( (*p)=='[' ) skip++;
					if( (*p)==']' ){
						if(skip==0){
							p++;
							break;
						}else{
							skip--;
						}
					}
				}
			}
		}

		// Jump Back If Zero:
		if( c == ']' ){
			if( (*m) != 0 ){
				int skip = 0;
				while( (*p)!='[' || skip>0 ){
					p--;
					if( (*p)==']' ) skip++;
					if( (*p)=='[' ){
						if(skip==0){
							p++;
							break;
						}else{
							skip--;
						}
					}
				}
			}
		}

		// Move forward an instruction
		c = *(p++);
	}
}

char *readfile(char *filename){
	char * buffer = 0;
	long length;
	FILE * f = fopen (filename, "r");
	if(f==NULL) return NULL;

	int result = 0;

	if( f )
	{
		result = fseek(f, 0, SEEK_END);
		if(result==-1) return NULL;

		length = ftell(f);
		if(length==-1) return NULL;

		result = fseek(f, 0, SEEK_SET);
		if(result==-1) return NULL;
		
		buffer = malloc(length);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose (f);
	}

	if(buffer)
		return buffer;
	else
		return NULL;
}

int main(char argc, char **argv){

	char *program = readfile(argv[1]);
	if( program != NULL ){
		run(program);
	}else{
		printf("%s\n","Usage: bf <filename>");
	}

	return 0;
}
