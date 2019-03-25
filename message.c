#include <stdlib.h>
#include <string.h>


#define TIME_REQUEST_CODE "0002"
#define TIME_RESPONSE_CODE "1002"
#define DATA_MAX_SIZE 128

typedef unsigned char byte;

typedef struct message{
    byte message_code[4 * sizeof(char)];
    byte rq_id[sizeof(int)];
    byte data[DATA_MAX_SIZE];
}message;


void write_message_code(message * self, char * code){
    memcpy(self->message_code, code, 4 * sizeof(char));
}


void write_rq_id(message * self, int rq_id){
    rq_id = htonl(rq_id);
    memcpy(self->rq_id, &rq_id, sizeof(int));
}


void write_time(message * self, char * time, int length){
    byte * time_wsk = self->data + sizeof(int);
    memcpy(time_wsk, time, length);
}

void write_length(message * self, int length){
    length = htonl(length);
    memcpy(self->data, &length, sizeof(int));
}

char * get_message_code(message * self){
    char * code = malloc(sizeof(self->message_code) + 1);
    memcpy(code, self->message_code, sizeof(self->message_code));
    code[4] = '\0';
    return code;
}

int get_rq_id(message * self){
    int rq_id = -1;
    memcpy(&rq_id, self->rq_id, sizeof(int));
    rq_id = ntohl(rq_id);
    return rq_id;
}

int get_length(message * self){
    int length = -1;
    memcpy(&length, self->data, sizeof(int));
    length = ntohl(length);
    return length;
}

char * get_time(message * self, int length){
    char * time_message = malloc(sizeof(char) * length) ;
    byte * time_wsk = self->data + sizeof(int);
    memcpy(time_message, time_wsk, length);
    return time_message;
}
