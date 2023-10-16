# Matrix Library for C [Under Development Currently - New Version   Ported to gmp ]

Fast matrix library for C 

This library was designed for performing basic matrix operations .Haskell/python like functions [more like python   ] implemented for simple matrix operations   
All of the given functions in the header take and throwout <b>ONLY POINTERS TO MATRIX . NOT THE MATRIX ITSELF</b>.
Plus the values output /built in for the matrix structure IS ONLY DOUBLE .

# Usage :

Matrix Creation  :

Create matrix using :
        
       
      matrix* <matrix alias>=CreateMatrix(int row,int col);
      
      
The function CreateMatrix Creates the required matrix and return pointer to the defined struct in matrix.h

Free Matrix:

Once the work with the matrix is done it is always a good practice to free the pointers to the matrix to avoid any future memory leaks .
But be sure before freeing as calling any future functions on the pointer that is free will obviosly result in SegFault !
      
      
              free_matrix(matrix*);
Printing Matrix:

Fast printing matrix without the user running 2 for loops to print contents,
        
              print_matrix(matrix*);


Insertion Of Matrix Elements:

The elements in the matrix start from row=[1...n]/col=[1...n]

Insertion can be done by calling the below function 
            
              insert_element(matrix*<alias>,int row,int col,double <value> );
    
Copying matrix 
  To call this function there must be a matrix of same dimension already existing or created by user[or overwrite matrix] as the given void function  returns nothing 
              
               matrix * a=Create_Matrix(3,4);
               cp_matrix(matrix*<src> ,a<dest>);

Create EYE matrix:
  Creates a square matrix of only 1 in leading diagonal
  
              matrix*<alias>=create_eyematrix(int row,int col)

Retrieve Elements from the matrix :
  The user can call the get_element() function to retrieve the elements or if the user wishes can also use pointers to poke around with the data
  usage with function:
              
              <double> a=get_element(matrix*<alias>,int row,int col);
  Usage with Pointers:
              
              matrix* m=Create_Matrix(12,14);
              <double> a=m->data[nth data ];
  
Write the given matrix to a file :
Incase you wish to write the matrix to a file 
              
                
               dump_matrix(matrix*<alias>,char*<filename.txt>,char* mode);
               


Generate Random Matrix:

Incase you want to generate matrix that has random float values 

                
               matrix* x=random_matrix(int rows,int cols,int maxval,char * "float") ;
               
               
Create Matrix with predefined vals:


  The user can use array like contiguous syntax to denote elements of matrix 
  example
   to create 5x3 matrix there needs to be 15 entries 
              
              matrix* a;
              double arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
              insert_multival(a,arr);
              

Other Functions included in the library:




           Transpose    
           Cofactor
           Adjoint 
           Determinant
           Sum 
           Scalar Product
           Dot Product
           Trace 
           Inverse
   
 
 
References:

      http://theory.stanford.edu/~arbrad/pfe/html
