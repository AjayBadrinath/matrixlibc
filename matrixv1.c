#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
typedef struct mat{
int row;
int col;
 mpz_t  *data;
}matrix;
matrix*Create_Matrix(int row,int col,char* type){
    if(row>0&&col>0){
        matrix*m=(matrix*)malloc(sizeof(matrix));
        m->row=row;
        m->col=col;

        if(type=="int"){
        
            m->data=(mpz_t*)malloc(sizeof(mpz_t)*row*col);
        //printf("%d",m->row);
            for (int i=0;i<row*col;i++){
                mpz_init(m->data[i]);
                mpz_set_ui(m->data[i],0);
            }  
            return m;
        }/*
        else if(type=="rational"){
            m->data=(mpq_t*)malloc(sizeof(mpq_t)*row*col);
        //printf("%d",m->row);
            for (int i=0;i<row*col;i++){
                mpq_init(m->data[i]);
                mpq_set_ui(m->data[i],0,0);
            }  
            return m;
        }
        */
        else{
            fprintf(stderr,"Unsupported Type\n");
            return NULL;
        }
    }else{
        fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	    exit(0);
    }
    return NULL;
}
void insert_element(matrix*mat,int i_row,int j_col,int val){
    mpz_t* m=mat->data;
    mpz_set_ui(*(m+((j_col)+(i_row)*(mat->col))),val);
}
int get_element(matrix*mat,int row,int col){
    mpz_t* m=mat->data;
	    return mpz_get_ui(*(m+((col)+(row)*(mat->col))));
}
void print_matrix(matrix*mat){
    mpz_t * p=mat->data;
    for(int i=0;i<mat->row*mat->col;i++){
        if((i%mat->col)==0)printf("\n");
        printf("%ld\t",mpz_get_ui(*(p++)));
    }
   printf("\n");
}

matrix* transpose(matrix*mat){
    matrix*T=Create_Matrix(mat->col,mat->row,"int");
    for(int row=0;row<mat->row;row++){
        for(int col=0;col<mat->col;col++){
            insert_element(T,col,row,get_element(mat,row,col));
        }
    }
    return T;
}
matrix* Create_Eye_Matrix(int row){
    matrix* x=Create_Matrix(row,row,"int");
    for(int i=0;i<=row;i++){
        for(int j=0;j<row;j++){
            if(i==j)insert_element(x,i,j,1);
            
        }
    }
}
matrix* cofactor(matrix*x,int a,int b){
    matrix* tmp=Create_Matrix(x->row-1,x->col-1,"int");
    int i=1,j=1;
    for(int m=1;m<x->row;m++){
        for(int o=1;o<x->col;o++){
            if(m!=a && o!=b){
                insert_element(tmp,i,j++,get_element(x,m,o));
                if(j==(x->row)){
                    j=1;
                    i++;
                }
            }
        }
    }
    return tmp;
}

void insert_multival(matrix* x, int *arr){
    int i,j;
    for(int i=0;i<x->row;i++){
        for(int j=0;j<x->col;j++){
            insert_element(x,i,j,*(arr++));
        }
    }
}
void main(){
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
    matrix* k=Create_Matrix(3,5,"int");
    int arr1[]={
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
    };
    insert_multival(k,arr1);
  //  print_matrix(k);

    k=transpose(k);

   // print_matrix(k);
    int arr[]={1,2,3,4,5,6,7,8,9};
    matrix*m=Create_Matrix(3,3,"int");
    insert_multival(m,arr);
    matrix*cf=cofactor(m,0,1);
    print_matrix(cf);
    /*
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            insert_element(k,i,j,-i+1*-j+1);
        }
    }
    //print_matrix(transpose(k));
    */
gettimeofday(&end,NULL);
long sec=(end.tv_sec-start.tv_sec);
long us=(((sec*1000000)+end.tv_usec)-(start.tv_usec));
printf("\nExecutionTime: %lf ms\n",(double)us/1000);
}
