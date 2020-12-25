#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


int n_passwords = 4;

char *passwords_enc[] = {
  "$6$KB$fyo99S0gm72R/M2MTWbQnTj.Vyw0ewZaAy55Pu8EOiEoX0GC4AUTuMfvuamABMtr37/oIcXza1XOguA/vLAmG.",
  "$6$KB$H8RIsbCyr2r7L1lklCPKY0tLK9k5WudNWpxkNbx2bCBRHCsI3qyVRY.0nrovdkDLDJRsogQE9mA3OqcIafVsV0",
  "$6$KB$fpZDw2bDkmDJqQTwQLByx39LhurTAIQmFCNYU1t8EGX4gw9qwDQrkRMvNq1yf/lFPjAckzqc5K12bMGhybRBB.",
  "$6$KB$OpOIZac00sMBfYemANRTO3lKNZCFLegKAMakI3i2fk78/vZgo01X5mdG/1R1K0Ohs0V1AuxfOK7KY.th3dInb0"
};

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void pnthread(){
int i;
pthread_t SS1, SS2;

void *kernel_function_1();
void *kernel_function_2();
for(i=0; i<n_passwords;i<i++){

pthread_create(&SS1, NULL,kernel_function_1,passwords_enc[i] );
pthread_create(&SS2, NULL,kernel_function_2,passwords_enc[i] );

pthread_join(SS1, NULL);
pthread_join(SS2,NULL);
}
}
void *kernel_function_1(char *salt_and_encrypted){
  int P,R,A;  
  char salt[7];   
  char plain[7]; 
  char *enc;   
  int count = 0; 
  substr(salt, salt_and_encrypted, 0, 6);

  for(P='A';P<='M'; P++){
    for(R='A'; R<='Z'; R++){
      for(A=0; A<=99; A++){
        sprintf(plain, "%c%c%02d", P,R,A); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
	else {
	printf("%-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(char *salt_and_encrypted){
  int N,I,R;     
  char salt[7];    
  char plain[7]; 
  char *enc;  
  int count = 0;

  substr(salt, salt_and_encrypted, 0, 6);

  for(N='N';N<='Z'; N++){
    for(I='I'; I<='Z'; I++){
      for(R=0; R<=99; R++){
        sprintf(plain, "%c%c%02d", N,I,R); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
        else{
        printf("%-8d%s %s\n", count, plain, enc);
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
 
 
    pnthread();
  

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 


  return 0;
}
