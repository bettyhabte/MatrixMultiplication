#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
/*
 prints out the parenthesized expression of the matrices for multiplying A1 through An
 checks if it is a single matrix
 if not, based of the split point that is store in kvalues, it will keep splitting it at kvalues[i][j]-1 and prints out in a proper multiplication order
 */
void parenthesizedMatrixExpression(int** kvalues, int i,  int j){
    if(i==j){
        cout << "A" << i+1 ;
    }
    else{
    
        cout << "(";
        parenthesizedMatrixExpression(kvalues, i, kvalues[i][j]-1);//the left of the split point
        parenthesizedMatrixExpression(kvalues, kvalues[i][j], j);//the right of the split point
        cout << ")";

    }
}

int main(){
    int n;
    //the number of matrices will be entered
    cout << "please enter the number of matrices less than or equal to 10:  ";
    cin >> n;
    while(n > 10){
        cerr << "Invalid input! " << endl;
        cout << "please enter the number of matrices less than or equal to 10:  ";
        cin >> n;
        
    }

    int matrix[n+1];
    /*
     the dimentions are m0, m1, m2 ... mn
     A1 m0Xm1
     A2 m1Xm2
     A3 m2Xm3 ... the user will be able to enter the dimentions and
     dimentions are set in the array matrix
     */
    for(int i=0; i<=n; i++){
        int dimention;
        cout << "please enter the  dimentions of the matix m" <<i<< " : ";
        cin >> dimention;
        matrix[i]= dimention;
    }
    
    /*
     prints the matrices with their dimentions
     */
    cout << endl;
    cout <<"the " << n<< " matrices  are : " <<endl;
    for(int i = 0; i<n; i++){
        cout << "A" << i+1 <<": "<< matrix[i]<< "x" <<matrix[i+1]<< endl;;
    }
    
    
    int temp, j;
    int M[n][n];
    int** kvalues = new int*[n];
    
    /*
     the kvalues[][] are set to zero initially
     */
    for (int i = 0; i < n; i++)
    {
        kvalues[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            kvalues[i][j] = 0;
        }
    }
    /*
     M[][] is set to -1 initially
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M[i][j] = -1;
        }
    }
    /*
     the number of multiplications are zero when the is only one matrix, zero work
     */
    for(int i=0;i<n; i++){
        M[i][i] = 0;
    }
    
    
    /*
     this part of the code finds the values of each diagonals  M[i][j]
      which represents the number of multiplication occur to multiply Ai..Aj,
     there are k possibilities to multiply, i<=k<j
     */
    for(int diagonal = 1; diagonal < n ; diagonal ++){
        for( int i = 0; i < n-diagonal ; i++){// number of rows
            j = i + diagonal;                 // sets the index of the column
            M[i][j]= INT_MAX;                 //maximum value is assigned
            for(int k = i; k <j; k++){ //
                temp =(M[i][k] + M[k+1][j] + (matrix[i] * matrix[k+1] * matrix[j+1]));
                if(temp < M[i][j]){//checks if the number of multiplications that just computed is less
                    M[i][j] = temp;//if it is less, then update with the minimum value
                    kvalues[i][j] = k+1; // kvalues records k+1 value, top-level split point, where the split occur
                }
            }
        }
    }
   

    /*
        prints out the number of multiplication values for multiplying Ai through Aj
     */
   
    cout << endl << "Multiplication Values" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] == -1){
                cout << "X" << '\t';
            } else {
                cout << M[i][j] << '\t';
            }
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "the minimum cost value is :  " << M[0][n-1] << endl;//minimum cost value is the value that is stored at m[0][n-1]
    
    /*
        prints out the top-level split point  for multiplying Ai through Aj
         for A1.A2.A3, Kvalues[1][3] holds the value where to split A1 through A3, 1<=k<3
    */
    cout << endl << "K Values" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << kvalues[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "the parenthesized expression is :   ";
    parenthesizedMatrixExpression(kvalues, 0, n-1);
    cout << endl;

}
 
