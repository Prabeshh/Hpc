#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>


int n_passwords = 4;

char *passwords_enc[] = {
  "$6$AS$e4Cq3pgl0HoFFmJK7hei3AXe1bfBXhBHBBkXS.KNZSHL226widiMcSyAqE.weCYVbRJn0oAGXnlIYIrBR1s2g0",
  "$6$AS$eWw.SMCo11FCcaesAj/wPSTdia8Nl0jW26RKKyfluuMaPIysCByena.0JCrX9j.HE4he87P5PurG0tL6WIoE7/",
  "$6$AS$XhySLCOLZcDLpPtPvPSxvVtvnT6yJlsqZo/cBsMElNQRj0hfVW4FArBDlC/PslJ2wNsUcAi62HT41UYHd8NwV.",
  "$6$AS$cHiRhMetc.PKoSxp8lvNE2ya.O0McKDMK42ABGQTjpkNIZPQA2cKM95RgJwgrMIsxLZZE6sIj2rEtBPHTHFh7/"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crackshree(char *salt_and_encrypted){
  int P,R,A,B;     
  char salt[7];   
  char plain[7];   
  char *enc;      
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(P='A';P<='Z'; P++){
    for(R='A'; R<='Z'; R++){
      for(A='A'; A<='Z'; A++){
      for(B=0; B<=99; B++){
        sprintf(plain, "%c%c%c%02d", P,R,A,B); 
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
    crackshree(passwords_enc[i]);
  }

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 


  return 0;
}
