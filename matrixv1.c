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
    INT =0,
    FLOAT=1,
    RATIONAL=2
    
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

//typedef void* (*getter)(datatype*);
typedef void(*setter)(datatype*,void*,int);
typedef void*(*createType)(int);
void setInt (datatype*dt,void* val,int idx){
    mpz_set(*(dt->mpz_type.i),*(mpz_t*)val);

}
void setFloat (datatype*dt,void* val,int idx){
 printf("FLTSET");
 mpf_set(*(dt->mpz_type.f),*(mpf_t*)val);
 
    
}
void setRational (datatype*dt,void* val,int idx){
    printf("rat creat");
    mpq_set(*(dt->mpz_type.r),*(mpq_t*)val);
    
}

void* CreateInt(int size){
    printf("int CREATEfn");
    mpz_t* a=(mpz_t*)malloc(sizeof(mpz_t)*size);
    for (int i=0;i<size;i++){
                
        mpz_init(*(a+i));
        mpz_set_ui(*(a+i),0);
    }
    return a;

}
void* CreateFloat(int size){
    printf("FLOAT CREATEfn");
    mpf_t* a=(mpf_t*)malloc(sizeof(mpf_t)*size);
    for (int i=0;i<size;i++){
                
        mpf_init(*(a+i));
        mpf_set_ui(*(a+i),0);
    }
    return a;
}
void* CreateRational(int size){
    printf("rational CREATEfn");
    mpq_t* a=(mpq_t*)malloc(sizeof(mpq_t)*size);
    for (int i=0;i<size;i++){
        mpq_init(*(a+i));
        mpq_set_ui(*(a+i),0,1);
    }
    return a;
}
setter set[]={setInt,setFloat,setRational};
createType creator[]={CreateInt,CreateFloat,CreateRational};
//getter get[]={getInt,getFloat,getRational};

matrix*Create_Matrix(int row,int col, datatype* dt){
    if(row>0&&col>0){
        matrix*m=(matrix*)malloc(sizeof(matrix));
        m->row=row;
        m->col=col;
        m->data=(datatype*)malloc(sizeof(datatype));
        m->data->mpz_types=dt->mpz_types;
        //void* z=getType(m->data->mpz_type,dt->mpz_types)

        
        switch (dt->mpz_types){

            case INT:
                printf("INT CREATE");
                m->data->mpz_type.i=creator[INT](row*col);
                break;
            case RATIONAL:
                printf("RATIONAL CREATE");
                m->data->mpz_type.r=creator[RATIONAL](row*col);
                break;

            case FLOAT:
                printf("FLOAT CREATE");
                m->data->mpz_type.f=creator[FLOAT](row*col);
                break;
            
            
        }
        
        return m;

    
    }else{
        fprintf(stderr,"Matrix rows and colums are indexed form [1....n]\n");
	    exit(0);
    }
    return NULL;
}
void setVal(matrix*dt,void*val,int idx){
    set[dt->data->mpz_types](dt->data,val,idx);
}
void* getVal(datatype*dt,int idx){

    //assert(dt->mpz_types==type);
    //dt->mpz_types=type;
    switch(dt->mpz_types){
        case INT:
            printf("INT CREATE");
            return dt->mpz_type.i[idx];
            break;
        case FLOAT:
            printf("float CREATE");
            return dt->mpz_type.f[idx];
        case RATIONAL:
            printf("rational CREATE");
            return dt->mpz_type.r[idx];

    }
    return NULL;

    
}


void insert_element(matrix*mat,int i_row,int j_col,void *val){
    //mpz_t* m=mat->data;
    //set[mat->data->mpz_types]
    printf("gyug CREATE");
    setVal(mat,val,((j_col)+(i_row)*(mat->col)));
    //setType(getType(mat->data->mpz_types),mat->data->mpz_types,val,((j_col)+(i_row)*(mat->col)));
}
int get_element(matrix*mat,int row,int col){
    mpz_t* m=mat->data;
	return mpz_get_ui(*(m+((col)+(row)*(mat->col))));
}
void print_matrix(matrix*mat){
    printf("HELOOL\n%d",mat->data->mpz_types);
    switch(mat->data->mpz_types){
        

        case FLOAT:
            printf("\n");
            printf("FLOAT PRINT\n");
            mpf_t * p_f=mat->data->mpz_type.f;
            for(int i=0;i<mat->row*mat->col;i++){
                if((i%mat->col)==0)printf("\n");
                printf("%f\t",mpf_get_d(*(p_f++)));
            }
            printf("\n");
            break;

        case INT:
            printf("\n");
            printf("INT PRINT\n");
            mpz_t * p=mat->data->mpz_type.i;
            for(int i=0;i<mat->row*mat->col;i++){
                if((i%mat->col)==0)printf("\n");
                printf("%ld\t",mpz_get_ui(*(p++)));
            }
            printf("\n");
            break;
        case RATIONAL:
            printf("\n");
            printf("RATIONAL PRINT\n");
            mpq_t * p_r=mat->data->mpz_type.r;
            for(int i=0;i<mat->row*mat->col;i++){
                if((i%mat->col)==0)printf("\n");
                printf("%lf\t",mpq_get_d(*(p_r++)));
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
    return NULL;
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
    datatype * t= malloc(sizeof(datatype));
    t->mpz_types=RATIONAL;
    //(t->mpz_type.r)=(mpq_t*)malloc(sizeof(mpq_t));
    //mpq_set_d(*t->mpz_type.r,12.35);
    //mpz_t* i;
    //mpz_set(*i,1);
    //printf(";lllool;;%f",mpq_get_d(getType(t)));
    double *x =malloc(sizeof(double));
    *x=2.45;
    matrix* k=Create_Matrix(3,5,t);
    //mpq_t* j=*(mpq_t*)x;
    mpq_t j;
    mpq_init(j);
    mpq_set_d(j, *x);
    insert_element(k,1,1,j);

    //printf(";lllool;;%f",mpq_get_d(getType(k->data,1)));
    //printf("%ld",mpz_get_ui(k->data->mpz_type.i[0]));
    //mpq_t* l=k->data->mpz_type.r;
    //printf("%f",mpf_get_d(k->data->mpz_type.f[1]));
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
