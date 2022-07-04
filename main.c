#include <stdio.h>
#include<sys/time.h>
#include <time.h>
#include "matrix.h"

int main(){
struct timeval start,end;
gettimeofday(&start,NULL);
/*
double x[3][3];
for (int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		x[i][j]=0.0;

	}

}
for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		printf("%f ",x[i][j]);
	}
	printf("\n");
}
*/

/*
matrix *ptr=Create_Matrix(3,3);
matrix *ptr2=create_eyematrix(3,3);
print_matrix(ptr);
printf("\n");
insert_element(ptr,2,2,5);
print_matrix(ptr);
cp_matrix(ptr,ptr2);
printf("\n");
print_matrix(ptr2);
printf("\n");
matrix *ptr3=create_eyematrix(2,3);
print_matrix(ptr3);
*/
matrix *ptr=Create_Matrix(3,4);
//matrix *ptr1=Create_Matrix(3,2);
//print_matrix(Create_Matrix(3,3));
double arr[]={1,1,1,1,2,2,2,2,3,3,3,3,4,4,5};
//double arr[]={1,1,1,1,2,2,2,2,3,3,3,3};
//double *p=arr;
insert_multival(ptr,arr);
//print_matrix(ptr);
double arr1[]={1,1,2,2,3,3};
//double *p1=arr1;
//insert_multival(ptr1,arr1);
print_matrix(ptr);

//print_matrix(ptr1);
//print_matrix(matrix_extendright(ptr,ptr1));
//insert_element(ptr,1,4,5.0);
//insert_element(ptr,1,1,5.0);
//insert_element(ptr,1,3,5.0);
//insert_element(ptr,1,2,5.0);
//print_matrix(random_matrix(4,3,100,"int"));
//print_matrix(ptr);

//print_matrix(multiply_matrix(random_matrix(10,9,100,"float"),random_matrix(9,10,100,"float")));
//int k=0;
//for(int i=1;i<=4;i++){
//for(int j=1;j<=4;j++){
//insert_element(ptr,i,j,++k);
//}
//}
//*(ptr++->data)={1,2,1,2,5,3,3,7,5};
//matrix* ptr=random_matrix(5,7,100,"int");
//dump_matrix(random_matrix(1,1,100,"float"),"abx.txt","w");
matrix *tr=transpose(ptr);
print_matrix(tr);
matrix* new=Create_Matrix(ptr->row,ptr->col);
cp_matrix(ptr,new);

print_matrix(new);

matrix* I=create_eyematrix(4,4);

print_matrix(I);



free_matrix(ptr);
//matrix * t=cofactor(ptr,1,1);
//print_matrix(t);
//double x=get_element(ptr,1,2);
//printf("\n%f\n ",trace(ptr));
//print_matrix(matrix_sum(ptr,tr));
//print_matrix(adjoint(ptr));
//print_matrix(inverse(ptr));
//print_matrix(scalar_product(2,ptr));
//double elapsed=(double)(clock()-start)/CLOCKS_PER_SEC;
gettimeofday(&end,NULL);
long sec=(end.tv_sec-start.tv_sec);
long us=(((sec*1000000)+end.tv_usec)-(start.tv_usec));
printf("\nExecutionTime: %lf ms\n",(double)us/1000);
return 0;
}
