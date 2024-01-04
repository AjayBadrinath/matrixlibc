#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>

typedef union  type{
    mpf_t* f;
    mpq_t* r;
    mpz_t* i;

}u_T;
typedef enum {
    INT ,
    RATIONAL,
    FLOAT
} e_T;

typedef struct DataType{
    u_T mpz_type;
    e_T mpz_types;
}datatype;

typedef struct mat{
int row;
int col;
 datatype  *data;
}matrix;

matrix*Create_Matrix(int row,int col, datatype* dt){
    if(row>0&&col>0){
        matrix*m=(matrix*)malloc(sizeof(matrix));
        m->row=row;
        m->col=col;
        m->data=(datatype*)malloc(sizeof(datatype));
        switch (dt->mpz_types){
            case INT:
            printf("%d",18);
                mpz_t* a=(mpz_t*)malloc(sizeof(mpz_t)*row*col);
                m->data->mpz_type.i=a;
                for (int i=0;i<row*col;i++){
                    mpz_init(m->data->mpz_type.i[i]);
                    mpz_set_ui(m->data->mpz_type.i[i],0);
                }
                break;
            case RATIONAL:
                m->data->mpz_type.r=(mpq_t*)malloc(sizeof(mpq_t)*row*col);
                for (int i=0;i<row*col;i++){
                    mpq_init(m->data->mpz_type.r[i]);
                    mpq_set_ui(m->data->mpz_type.r[i],0,0);
                }
                break;

            case FLOAT:
                m->data->mpz_type.f=(mpf_t*)malloc(sizeof(mpf_t)*row*col);
                for (int i=0;i<row*col;i++){
                    mpf_init(m->data->mpz_type.f[i]);
                    mpf_set_ui(m->data->mpz_type.f[i],0);
                }
                break;
            
        }
        return m;

    
    }else{
        fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	    exit(0);
    }
    return NULL;
}
void setType(datatype*dt,e_T type,void*val){
    dt->mpz_types=type;
    switch(type){
        case INT:
            mpz_set(*(dt->mpz_type.i),*(mpz_t*)val);
    }
    
}
void getType(datatype*dt,e_T type){
    assert(dt->mpz_types==type);
    dt->mpz_types=type;
    switch(type){
        case INT:
            return dt->mpz_type.i;
            break;
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
    switch(mat->data->mpz_types){
        case INT:
            printf("\n");
            mpz_t * p=mat->data->mpz_type.i;
            for(int i=0;i<mat->row*mat->col;i++){
                if((i%mat->col)==0)printf("\n");
                printf("%ld\t",mpz_get_ui(*(p++)));
            }
            printf("\n");
            break;
        case FLOAT:
            printf("\n");
            mpf_t * p_f=mat->data->mpz_type.f;
            for(int i=0;i<mat->row*mat->col;i++){
                if((i%mat->col)==0)printf("\n");
                printf("%ld\t",mpf_get_ui(*(p_f++)));
            }
            printf("\n");
            break;


    }
}

matrix* transpose(matrix*mat,datatype *dt){
    matrix*T=Create_Matrix(mat->col,mat->row,dt);
    for(int row=0;row<mat->row;row++){
        for(int col=0;col<mat->col;col++){
            insert_element(T,col,row,get_element(mat,row,col));
        }
    }
    return T;
}
matrix* Create_Eye_Matrix(int row,datatype *dt){
    matrix* x=Create_Matrix(row,row,dt);
    for(int i=0;i<=row;i++){
        for(int j=0;j<row;j++){
            //if(i==j)insert_element(x,i,j,1);
            
        }
    }
}
matrix* cofactor(matrix*x,int a,int b,datatype *dt){
    matrix* tmp=Create_Matrix(x->row-1,x->col-1,dt);
    int i=1,j=1;
    for(int m=1;m<x->row;m++){
        for(int o=1;o<x->col;o++){
            if(m!=a && o!=b){
                //insert_element(tmp,i,j++,get_element(x,m,o));
                if(j==(x->row)){
                    j=1;
                    i++;
                }
            }
        }
    }
    //return tmp;
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
    datatype * t= malloc(sizeof(datatype));
    t->mpz_types=FLOAT;
    
    matrix* k=Create_Matrix(3,5,t);
    print_matrix(k);
    /*
    int arr1[]={
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
    };
    insert_multival(k,arr1);
 

    k=transpose(k);


    int arr[]={1,2,3,4,5,6,7,8,9};
    matrix*m=Create_Matrix(3,3,"int");
    insert_multival(m,arr);
    matrix*cf=cofactor(m,0,1);
    print_matrix(cf);
*/
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
