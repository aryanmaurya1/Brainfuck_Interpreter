/*
Author : Aryan Maurya
Date : 13 August 2020
Mail : aryanmaurya1@outlook.com

This is source code of interpreter of an programming language "Brainfuck". 
Brainfuck is an esoteric programming language created in 1993 by Urban Müller.
It is a turing complete programming language, having only 8 programming
constructs. 
You can read more about it on wikipedia. https://en.wikipedia.org/wiki/Brainfuck
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 30000

const int DEBUG = 0;

int run(char inst[], char data[]){
	char* data_ptr = data;
	char* inst_ptr = inst;

	while((*inst_ptr) != '\0'){
		switch(*inst_ptr){
			case '>':
			 	if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);				 
				}
				data_ptr++;
				inst_ptr++;
				break;
			case '<':
				if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);				 
				 }
				data_ptr--;
				inst_ptr++;
				break;
			case '+':
				if(DEBUG){
					 printf("%c |", *inst_ptr);
					 printf("%c -> %d \n", *data_ptr, *data_ptr);
				 }
				(*data_ptr)++;
				inst_ptr++;
				break;
			case '-':
				if(DEBUG){
					 printf("%c |", *inst_ptr);
					 printf("%c -> %d \n", *data_ptr, *data_ptr);
				}				
				(*data_ptr)--;
				inst_ptr++;
				break;
			case '.':
				if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);				 
				}
				printf("%c",*data_ptr);
				inst_ptr++;
				break;
			case ',':
				if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);
				}
				scanf("%c", data_ptr);
				inst_ptr++;
				break;
			case '[':
				if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);
				}
				if((*data_ptr) == 0){
					int count = 1;
					inst_ptr++;
					while(count != 0){
						if((*inst_ptr) == ']'){
							count--;
						}else if ((*inst_ptr) == '['){
							count++;
						}
						inst_ptr++;
					}
				}
				break;
			case ']':
				if(DEBUG){
					printf("%c |", *inst_ptr);
					printf("%c -> %d \n", *data_ptr, *data_ptr);
				}
				if((*data_ptr) != 0){
					int count = -1;
					inst_ptr--;
					while(count != 0){
						if((*inst_ptr) == ']'){
							count--;
						}else if((*inst_ptr) == '['){
							count++;
						}
						if(count != 0){
							inst_ptr--;
						}
					}
					inst_ptr++;
				}
				break;
			default:
				printf("%c |", *inst_ptr);
				printf("%c -> %d \n", *data_ptr, *data_ptr);
				inst_ptr++;
		}
	}
	return 0;
}

int main(int argc, char** argv){

	char* filename = *(argv+1);

	char data[MAX] = {0};
	char inst[MAX] = {0};

	int fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("Error");
	}

	ssize_t read_amt =  read(fd,(void*)inst, (size_t)MAX);
	if(read_amt == -1) {
		perror("Error");
	}
	inst[read_amt] = '\0';
	int status = run(inst, data);
	if(status == 0){
		printf("\nProgram Executed sucessfully. \n");
	}
	return 0;
}
