#include <stdio.h>
#include <stdlib.h>
int main()
{
	int row_first_matrix;
	int column_first_matrix;
	int row_second_matrix;
	int column_second_matrix;
	
	printf("Enter the Row of First matrix\n");
	scanf("%d",&row_first_matrix);
	
	printf("Enter the column of First matrix\n");
	scanf("%d",&column_first_matrix);
	
	
	printf("Enter the Row of Second matrix\n");
	scanf("%d",&row_second_matrix);
	
	printf("Enter the column of Second matrix\n");
	scanf("%d",&column_second_matrix);
	
	if(column_first_matrix==row_second_matrix){
		int a[row_first_matrix][column_first_matrix], b[row_second_matrix][column_second_matrix], c[row_first_matrix][column_second_matrix];
		int i, j, k;
		printf("\nFirt Matrix:\n");
		for(i=0; i<row_first_matrix; i++) {
			for(j=0; j<column_first_matrix; j++) {
				a[i][j]=rand()%50;
				printf("%d  ", a[i][j]);
				
			}
			printf("\n");
		}
		printf("\nSecond Matrix;\n");
		for(i=0; i<row_second_matrix; i++) {
			for(j=0; j<column_second_matrix; j++) {
				b[i][j]=rand()%50;
				printf("%d  ", a[i][j]);
			}
			printf("\n");
		}
		for(i=0; i<row_first_matrix; i++) {
			for(j=0; j<column_second_matrix; j++) {
				c[i][j]=0;
				for(k=0; k<column_first_matrix; k++) {

					c[i][j]=c[i][j] + a[i][k] * b[k][j];

				}
			}
		}
		printf("\nThe results is...\n");
		for(i=0; i<row_first_matrix; i++) {
			for(j=0; j<column_second_matrix; j++) {
				printf("%d  ", c[i][j]);
			}
			printf("\n");
		}
		return 0;
	
	}
	else{
	
	printf("\nThe number of column of first matrix should be equal to row of second matrix!\n");
	
	
	}
	
	

}
