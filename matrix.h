
#ifndef __matrix__
#define __matrix__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

typedef struct mat{
int row;
int col;
double *data;

}matrix;

matrix* Create_Matrix(int ,int );

void free_matrix( matrix*);

void print_matrix( matrix*);

void insert_element( matrix*,int, int ,double );

void cp_matrix( matrix*, matrix*);

matrix * create_eyematrix(int ,int );

void check_errr(int ,int );

double  get_element( matrix* ,int ,int );


matrix *transpose( matrix*);

matrix* cofactor( matrix*,int  ,int  );

double determinant( matrix* );

void insert_multival( matrix* ,double *);

matrix* matrix_sum( matrix *, matrix *);

int * matrix_size( matrix* );

double trace( matrix * );

matrix* scalar_product(double , matrix* );

matrix* adjoint( matrix *);

matrix* random_matrix(int ,int ,int ,char );

matrix* inverse( matrix* );

matrix* multiply_matrix( matrix*, matrix*);

matrix* matrix_extendright( matrix* , matrix *);

void dump_matrix( matrix*,char *,char*  );


#endif