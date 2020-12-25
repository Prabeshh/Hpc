#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAT_SIZE 1024
int MAX_THREADS;


int N,M,P;         //Parameters For Rows And Columns
int matrix1[MAT_SIZE][MAT_SIZE]; //First Matrix
int matrix2[MAT_SIZE][MAT_SIZE]; //Second Matrix
int result [MAT_SIZE][MAT_SIZE]; //Multiplied Matrix
int i = 0;

void* mult(void* arg){


    int core = i++;
    //Calculating Each Element in Result Matrix Using Passed Arguments
    for (int i = core * MAT_SIZE / MAX_THREADS; i < (core + 1) * MAT_SIZE / MAX_THREADS; i++)
        for (int k = 0; k< MAT_SIZE; k++)
            for (int j = 0; j< MAT_SIZE; j++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    pthread_exit(0);
}


int main(){

    // Getting Row And Column(Same As Row In Matrix2) Number For Matrix1
    printf(" --- Defining Matrix 1 ---\n\n");
    printf("Enter number of rows for matrix 1: ");
    scanf("%d",&N);
    printf("Enter number of columns for matrix 1: ");
    scanf("%d",&M);
    printf("\n --- Defining Matrix 2 ---\n\n");
    printf("Number of rows for matrix 2 : %d\n",M);
    printf("Enter number of columns for matrix 2: ");
    scanf("%d",&P);
    printf("Enter the number for threads \n");
    scanf("%d",&MAX_THREADS);


    for(int x=0;x<N;x++){
        for(int y=0;y<M;y++){
            matrix1[x][y]=rand()%50;
        }
    }

    for(int x=0;x<M;x++){
        for(int y=0;y<P;y++){
            matrix2[x][y]=rand()%50;
        }
    }

    pthread_t *t = malloc(sizeof(pthread_t) * MAX_THREADS);

    //Defining Threads
    pthread_t thread[MAX_THREADS];

    //Counter For Thread Index
    int thread_number = 0;

    //Start Timer
    time_t start = time(NULL);


    for (int x = 0; x < MAX_THREADS; x++)
    {
        int *p;
            //Status For Checking Errors
            int status;

            //Create Specific Thread For Each Element In Result Matrix
            status = pthread_create(&thread[thread_number], NULL, mult, (void *) &p[thread_number]);

            //Check For Error
            if(status!=0){
                printf("Error In Threads");
                exit(0);
            }

            thread_number++;
        }





    //Wait For All Threads Done - - - - - - - - - - - - - - - - - - - - - - //

   for (int z = 0; z < MAX_THREADS; z++)
        pthread_join(thread[z], NULL);


    //Print Multiplied Matrix (Result) - - - - - - - - - - - - - - - - - - -//

    printf(" --- Multiplied Matrix ---\n\n");
    for(int x=0;x<N;x++){
        for(int y=0;y<P;y++){
            printf("%5d",result[x][y]);
        }
        printf("\n\n");
    }


    //Calculate Total Time Including 3 Soconds Sleep In Each Thread - - - -//

    printf(" ---> Time Elapsed : %.2f Sec\n\n", (double)(time(NULL) - start));


    //Total Threads Used In Process - - - - - - - - - - - - - - - - - - - -//

    printf(" ---> Used Threads : %d \n\n",thread_number);
    for(int z=0;z<thread_number;z++)
        printf(" - Thread %d ID : %d\n",z+1,(int)thread[z]);
    free(t);
    return 0;
}
