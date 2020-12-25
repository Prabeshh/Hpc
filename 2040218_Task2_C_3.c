#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>



int n_passwords = 4;

char *passwords_enc[] = {
  "$6$AS$WZOljuW2XVsnII87MbHOUk3hOcykqRFfiwbDhQJC3jsBcxjuuqKzTyUG.0TurNk35EzQxm683e.jVIFGnzDAi.",
  "$6$AS$rHxlKvijYzSHFdzLypWSpltQbvK/JXvA2BOriRuTbc/sZCfHebRnW33IoSSD05c9v4s5cswRxqSHpkFdQG4Wo/",
  "$6$AS$WkNXkgW6fmEC9/w5Xj1psRz0de1TAGW7hIt0II9G0qGUjv0WhJBdQmJPriDdLbMDxNZx.XqJTVRUmyOEISA8x0",
  "$6$AS$e4Cq3pgl0HoFFmJK7hei3AXe1bfBXhBHBBkXS.KNZSHL226widiMcSyAqE.weCYVbRJn0oAGXnlIYIrBR1s2g0"
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crackprabesh(char *salt_and_encrypted){
  int P,R,A;     
  char salt[7];    
  char plain[7];  
  char *enc; 
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(P='A';P<='Z'; P++){
    for(R='A'; R<='Z'; R++){
      for(A=0; A<=99; A++){
        sprintf(plain, "%c%c%02d", P,R,A); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main() {
int i;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  for(i=0;i<n_passwords;i<i++) {
    crackprabesh(passwords_enc[i]);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 


  return 0;
}
