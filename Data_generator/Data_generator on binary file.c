#define _CRT_SECURE_NO_WARNINGS    // SDL 경고를 발생하지 않도록 설정
#include <stdio.h>
#include <time.h>     
#include <stdlib.h>
#include <string.h>


#define ROW 5
#define COL 5

int main() {

   srand((unsigned int)time(NULL));
   int value;
   char* ary[] = { "emergency-state", "warning-state", "nomarl-state" };
   int ch;

   FILE* fp = fopen("data_bin.bin", "wb");


   for (int i = 0; i < ROW; i++) {
      value = rand() % 101;
      printf("%d", value);
      fwrite(&value, sizeof(int), 1, fp);
      for (int j = 0; j < COL -2; j++) {
         value = rand() % 101; //0~100 Random Number
         printf(", %d", value);
         fwrite(&value, sizeof(int), 1, fp);
      }
      ch = rand() % 3;
      printf(", %s\n", ary[ch]);

      //the string length + 1 for the null
      unsigned short size_of_string = strlen(ary[ch]) + 1;
      fwrite(&size_of_string, sizeof(unsigned short), 1, fp);

      //write the string
      fwrite(ary[ch], sizeof(char), size_of_string, fp);

   }

   fclose(fp);

   printf("\n===Reading Binary file===\n");


   fp = fopen("data_bin.bin", "rb");


   int num;
   int count;
   unsigned short string_length = 0;



   for (int i = 0; i < ROW; i++) {
      fread(&num, sizeof(num), 1, fp);
      printf("%d", num);
      for (int j = 0; j < COL - 2; j++) {
         fread(&num, sizeof(num), 1, fp);
         printf(", %d", num);
      }

      fread(&string_length, sizeof(unsigned short), 1, fp);
      char* read_ary = malloc(sizeof(char) * string_length);
      count = fread(read_ary, sizeof(char), string_length, fp);
      //printf("count : %d ", count);
      printf(", %s\n", read_ary);
   }
      

   fclose(fp);

}