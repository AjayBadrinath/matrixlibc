
#include "matrix.h"

//#define mx(matrix) rows matrix->row
//#define  cols matrix->col

matrix * Create_Matrix(int row,int col){
if(row>0 && col>0){
//assert(row>0 && col>0);
matrix *m=(matrix*)malloc(sizeof(matrix));
m->row=row;
m->col=col;
m->data=(double *)malloc(sizeof(double)*row*col);
for (int i=0;i<row*col;i++){
	m->data[i]=0.0;
}
return m;
}
else{
	 fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	 exit(0);

}
}

void free_matrix(matrix*x){
	free(x->data);
	free(x);
}


void print_matrix( matrix *x){

double * ptr1=x->data;
/*
for (int i=1;i<=x->row;i++){
	for (int j=1;j<=x->col;j++){
		//printf("%f ",x->data[(j-1)* x->row +(i-1)]);
		printf("%f ",*(ptr1));
		(ptr1)++;
	}
	printf("\n");
}
*/
int row=x->row;
int col=x->col;
int i;
for( i=0;i<row*col;i++){
	if ((i%col)==0){
		printf("\n");
	}
	printf("%f ",*ptr1);
	ptr1++;
}
//printf("%d \n",x->row);
printf("\n");


}

void  insert_element(matrix * x,int i_row,int j_col,double val){

double *ptr1=x->data;
ptr1=(ptr1+((j_col-1)+(i_row-1)*x->col));
*ptr1=val;
//x->data[(i_row-1)*x->row+(j_col-1)]=val;
//free(ptr1);
}


void cp_matrix(matrix* src,matrix *dest){
if ((src->row!=dest->row)||(src->col!=dest->col)){
	fprintf(stderr,"For Copying a Matrix the rows and columns must be the same \n");
	exit(0);
}

dest->row=src->row;
dest->col=src->col;
double *ptr1=dest->data;
double *ptr2=src->data;
for(int i=0;i<src->row*src->col;i++){
	*ptr1=*ptr2;
	ptr1++;
	ptr2++;
}

}



matrix * create_eyematrix(int row,int col){
if (!(row>0 && col >0)){
	fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	exit(0);
}

matrix *x=Create_Matrix(row,col);
for (int i=1;i<=row;i++){
	for (int j=1;j<=col;j++){
		if (i==j){
			insert_element(x,i,j,1.0);
		}
		else{
			continue;
		}
	//insert_element(x,i,j,0.0);
		}
}
return x;
}

void check_errr(int row,int col){
	if (!(row>0 && col >0)){
	fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	exit(0);
	}

}

double  get_element(matrix* x,int row,int col){

check_errr(row,col);
double *ptr=x->data;
return *(ptr+(col-1)+(row-1)*x->col);
}


matrix *transpose(matrix* x){


matrix * tr=Create_Matrix(x->col,x->row);
double *ptr1=tr->data;
double *ptr2=x->data;
for (int row=1;row<=x->row;row++){
	for (int col=1;col<=x->col;col++){
		//if (row==col){
		//continue;
		//}
		//else{
		ptr2=ptr2+((col-1)+(row-1)*x->col);
		//ptr1=ptr1+((col-1)+(row-1)*x->row);
		//]*ptr1=*ptr2;
		insert_element(tr,col,row,get_element(x,row,col));

	//}
	}
}
return tr;

}



matrix* cofactor(matrix*x,int a ,int b ){

matrix* tmp=Create_Matrix(x->row-1,x->col-1);
int i=1,j=1;
for(int m=1;m<=x->row;m++){
	for (int o=1;o<=x->col;o++){
		if (m!=a && o!=b){
		insert_element(tmp,i,j++,get_element(x,m,o));
		//j++;
		if(j==(x->row)){
			j=1;
			i++;
			}
		}
	}
}
return tmp;
}



double determinant(matrix* x){
if (x->row==1){
	return get_element(x,1,1);
}
matrix* temp;
double d=0;
int sign=1;
for (int k=1;k<=x->row;k++){
	temp=cofactor(x,1,k);
	d+=sign*get_element(x,1,k)*determinant(temp);
	sign=-sign;
}
return d;
}


void insert_multival(matrix* x,double *arr){
int i,j;
for ( i=1;i<=x->row;i++){
	for ( j=1;j<=x->col;j++){
		insert_element(x,i,j,*arr);
		//k++;
		arr++;
	}
}


}



matrix* matrix_sum(matrix *x,matrix *y){

matrix* tmp=Create_Matrix(x->row,x->col);
int m=1,n=1;
for (int i=1;i<=x->row;i++){
	for (int j=1;j<=x->row;j++){
		insert_element(tmp,m,n++,get_element(x,i,j)+get_element(y,i,j));
		if (n==x->row+1){
			n=1;
			m++;
		}
	}
}

return tmp;
}



int * matrix_size(matrix* x){

int arr[]={x->row,x->col};
int *ptr =arr;
return ptr;
}



double trace(matrix * x){

if (!(x->row==x->col)){
	fprintf(stderr,"Trace is defined only for square matrix");
	exit(0);
}
double sum=0.0;
double* ptr=x->data;
for (int i=1;i<=x->row;i++){
	for(int j=1;j<=x->row;j++){
		if (i==j){
			sum+=get_element(x,i,j);
		}

	}	
}
return sum;
}


matrix* scalar_product(double scalar,matrix* x){
	double temp=0;
	for(int i=1;i<=x->row;i++){
		for(int j=1;j<=x->col;j++){
			temp=get_element(x,i,j);
			insert_element(x,i,j,scalar*temp);

		}

	}
	return x;

}


matrix* adjoint(matrix *x){

matrix*  adjoint_t=Create_Matrix(x->row,x->col);
int k=0;
int sign=1;
for(int row=1;row<=x->row;row++){
	for(int col=1;col<=x->col;col++){
		insert_element(adjoint_t,row,col,sign*determinant(cofactor(x,row,col)));
	sign=-sign;
	}

}
return transpose(adjoint_t);
}

matrix* inverse(matrix* x){
	if((x->row!=x->col)){
		fprintf(stderr,"Inverse is defined only for square matrix\n");
		exit(0);
	}
	return scalar_product((1/determinant(x)),adjoint(x));

}

matrix* random_matrix(int row,int col,int maxval,char *a){
	time_t t;

	matrix*x =Create_Matrix(row,col);

	srand(time(&t));
	if (a=="float"){
	for(int i=1;i<=row;i++){
		for (int j=1;j<=col;j++){
			insert_element(x,i,j,(double)(rand())/(double)(RAND_MAX/maxval));
		}
	}
}
	else{
		for(int i=1;i<=row;i++){
			for (int j=1;j<=col;j++){
				insert_element(x,i,j,(double)(rand()%maxval));
		}
	}
}
	return x;


}


void dump_matrix(matrix*x,char * filename,char* mode ){

	FILE *fptr;
	fptr=fopen(filename,mode);
	fprintf(fptr,"%s","\n");
	if (fptr!=NULL){
		for(int i=1;i<=x->row;i++){
			for (int j=1;j<=x->col;j++){
				fprintf(fptr,"% 10.7f ",get_element(x,i,j));
			}
			fprintf(fptr,"\n");
		}
		fclose(fptr);

	}
	else{
		fprintf(stderr,"Error Creating File");
	}


}


matrix* multiply_matrix(matrix*x,matrix*y){
	double val=0;
	matrix* prod=Create_Matrix(x->row,y->col);
	for (int i=1;i<=x->row;i++){

		for (int j=1;j<=y->col;j++){
			val=0;
			for (int k=1;k<=y->row;k++){
				insert_element(prod,i,j,val+=(get_element(x,i,k)*get_element(y,k,j)));
				
			}
			
			//printf("%f ",get_element(prod,i,j));
		}
		//printf("\n");
		
	}


return prod;
}

matrix* matrix_extendright(matrix* x, matrix *y){
 matrix * t=Create_Matrix(x->row,x->col+y->col);
 int k=x->col+1;
 t=matrix_sum(t,x);
 for(int i=1;i<=x->row;i++){
 	for(int j=x->col;j<=y->col+x->col;j++){
 		insert_element(t,i,j,get_element(y,i,(k-x->col)));
 		k=j;
 	}
 }

return t;
}

