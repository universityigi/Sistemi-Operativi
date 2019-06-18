#pragma once

#define MESSAGE_QUEUE_ID 40
#define MAX_MSG_SIZE 4096
#define SHARED_MEMORY_SIZE 4096

typedef struct MessageHeader{
  int type; // 1
  int seq;
} MessageHeader;

typedef struct MessageOne{
  MessageHeader header;
  int values[2];
} MessageOne;

typedef struct MessageTwo{
  MessageHeader header;
  float values[3];
} MessageTwo;


