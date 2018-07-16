

#ifndef QUEUE_BYTE_H
#define QUEUE_BYTE_H

/****************** ????? *****************************/
#define NUM_MES_DATA 64
typedef struct QUEUE_byte 
{
  unsigned char date[NUM_MES_DATA];  //??????
  unsigned char Front;     //??????
  unsigned char Rear;     //??????
  unsigned char FullFlag;
}QUEUE_byte;



void Queue_byteInit(QUEUE_byte * This);
unsigned char GetByteFromQueue(QUEUE_byte *This);
void PutByteInQueue(QUEUE_byte *This,unsigned char PutData);
unsigned char Queue_byteCount(QUEUE_byte * This);

#endif
