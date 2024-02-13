#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include<ctype.h>

#include "utils.h"
BUFFER file_Buffer;
BUFFER info_buffer;

int read_to_buffer(FILE *fp, BUFFER *buffer) {

    // Seek to the end to get file size
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // Go back to the beginning

    // Allocate memory and check for success
    char *buffer1 = malloc(size); // Plus 1 for null terminator
    buffer->buffer_start = buffer1;
    if (buffer1 == NULL) {
        perror("malloc");
        fclose(fp);
        return NULL;
    }

    // Read the entire file into the buffer
    size_t bytes_read = fread(buffer1, 1, size, fp);
    if (bytes_read != size) {
        perror("fread");
        free(buffer1);
        fclose(fp);
        return NULL;
    }
    buffer->buffer_size = bytes_read;
    buffer->buffer_position = (buffer->buffer_start + bytes_read);

    // Close the file and return the buffer
    fclose(fp);
    return EXIT_SUCCESS;
}
char** capitalToSmall(BUFFER *buffer){
    char ch;
    char str[255];
    int word_count = 0;
    char *buffer_start = buffer->buffer_start;
    char *buffer_end = buffer->buffer_position;
    int count = 0;
    printf("start: %d,stop: %d\n",buffer->buffer_start, buffer->buffer_position);
    printf("word_no1 %d\n",buffer->words_no);
    printf("test 02\n");
    char strings_arr[buffer->words_no][maximum_length];
    for(buffer_start; buffer_start != buffer_end; buffer_start++){
        ch = *buffer_start;
        if(ch == '\n'){
            str[count] = '\0';
            strcpy(strings_arr[word_count],str);
            word_count++;
            count = 0;
        }else{
            str[count] = ch;
            count++;
        }        
    }
    if(word_count == buffer->words_no)printf("perfectoo!!!\n");
    //printf("world no: %d",buffer->words_no);
    // for(int count = 0; count <= word_count; count++){
    //     printf("%s\n", strings_arr[count]);
    // }
return strings_arr;
}

 int printcmd(FILE* file){
    char ch = 65;
    printf("test 2");
    //ch = fgetc(file);
    rewind(file);
    while(ch != EOF){
        ch = fgetc(file);
        if(ch == EOF)break;
        if(ch != 32){
            //delay(1);
            printf("%c",ch);
        }else printf("%c",ch);
    }
return EXIT_SUCCESS;
 };

int print_buffer(BUFFER *buffer){
    char ch;
    int count = 0;
    char *buffer_start = buffer->buffer_start;
    char *buffer_end = buffer->buffer_position;
    printf("test 01\n");
    FILE *temp = tmpfile();

    if (temp == NULL) {
        perror("tmpfile() failed");
        return 1;
    }
    while(buffer_start != buffer_end){
        ch = *buffer_start;
        if(isalpha(ch)){
            fputc(tolower(ch),temp);
            count = 0;
        }else if(isspace(ch) && count == 0){
            fputc('\n',temp);
            count++;
            buffer->words_no++;
        }
    buffer_start++;
    }
//printcmd(temp);
read_to_buffer(temp, buffer);
return 0;
}
int count_words(BUFFER *buffer){
    char *buffer_start = buffer->buffer_start;
    char *buffer_end = buffer->buffer_position;
    buffer->words_no = 0;
    while(buffer_start != buffer_end){
        char ch = *buffer_start;
        if(ch == '\n')buffer->words_no++;
        buffer_start++;
    }
return 0;
}
int main(int argc,char** argv){
    int count = 0;
    char ch;
    BUFFER *buffer = &file_Buffer;
    BUFFER *buffer2 = &info_buffer;
    FILE *fp = fopen(argv[1], "rb"); // Open in binary mode
    if (fp == NULL) {
        perror("fopen");
        return NULL;
    }
    FILE *fptr = fopen("/usr/share/dict/american-english", "rb");
    if (fptr == NULL){
        perror("fopen");
        return NULL;
    }
    read_to_buffer(fptr,buffer2);
    count_words(buffer2);
    printf("dic count: %d\n", buffer2->words_no);
    HashTable *dictionary = ht_create(buffer2->words_no);
    char str1[maximum_length];
    char *buffer_st = buffer2->buffer_start;
    char *buffer_pos = buffer2->buffer_position;
    while(buffer_st != buffer_pos){
        ch = *buffer_st;
        if(ch == '\n'){
            str1[count] = '\0';
            //char *key;
            //strcpy(key, str1);
            //printf("%s",str1);
            insert(dictionary, str1);
            count = 0;
        }else{
            str1[count] = ch;
            count++;
        } 
        buffer_st++;
    }
    read_to_buffer(fp, buffer);
    printf("start: %d,stop: %d\n",buffer->buffer_start, buffer->buffer_position);
    print_buffer(buffer);
    char str[255];
    int word_count = 0;
    char *buffer_start = buffer->buffer_start;
    char *buffer_end = buffer->buffer_position;
    count = 0;
    char strings_arr[(buffer->words_no)][(maximum_length)];
    for(buffer_start; buffer_start != buffer_end; buffer_start++){
        ch = *buffer_start;
        if(ch == '\n'){
            str[count] = '\0';
            strcpy(strings_arr[word_count],str);
            word_count++;
            count = 0;
        }else{
            str[count] = ch;
            count++;
        }        
    }

    for(int count = 0; count <= buffer->words_no; count++){
        if((search(dictionary, strings_arr[count])) == true){
            //printf("%s - found\n",strings_arr[count]);
        }else{
            printf("%s\n",strings_arr[count]);
        }

    }

    return 0;
}
