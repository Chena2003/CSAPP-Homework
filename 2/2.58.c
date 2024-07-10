#include <stdio.h>
#include <stdbool.h>

// bool is_little_endian() {
//      int x = 0x12345678;

//      if(x & 0xff == 0x12)
//           return 0;
//      else 
//           return 1;
// }

bool is_little_endian() {
     int x = 0xFF;

     char *p = (char *)&x;

     return p[0] == 0xFF; 
}

int main() {
     if(is_little_endian())
          printf("little endian\n");
     else 
          printf("big endian\n");

     return 0;
}