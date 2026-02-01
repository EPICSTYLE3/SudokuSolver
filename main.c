#include <stdio.h>
#include <math.h>
FILE *fileptr;
int* starting(int puzzle[]){
    fileptr = fopen("puzzle.txt","r");
    int i;
    for (i = 0; i < 81; i++)
    {
        fscanf(fileptr, "%d", &puzzle[i]);
    }
    int b = puzzle[6]+puzzle[7];

    //for (i = 0; i < 81; i++)
    //{
    //    printf("Number is: %d\n\n", puzzle[i]);
    //}
    return puzzle;
}
int checkcomplete(int puzzle[]){
    int i;
    for (i=0; i<81;i++)
    {
        if (puzzle[i]==0){
            printf("\n Not done lol");
            return(1);
        }
        return(0);
    }

}
int solve(int puzzle[]){
    int i;
    int m;
    int row; // top to bottom
    int rowvalue;
    int column; // left to right
    int columnvalue;
    int box; // 1 top left 2 middle top
    int new[81]= {0};
    for (i=0; i<81;i++);
        new[i] = puzzle[i];
//SOLVE LOGIC-------------------------------------
    for(i=0; i<81; i++) // for each number
    {
        if (puzzle[i]==0) //if unsolved
        {
            int possible[9] = {1,2,3,4,5,6,7,8,9};
            row = floor(i/9);
            column = i%9; //starting at 0->8
            for (m=0;m<9;m++) //check row for impossible options
            {
                rowvalue = puzzle[(m+9*row)]; 
                if (rowvalue !=0)
                {
                    possible[rowvalue-1]=0;
                }
                columnvalue = puzzle[column+m*9];
                if (columnvalue!=0);
                {
                    possible[columnvalue-1]=0;
                }
                // insert box removal logic here 
            }
            // insert logic to sub in the numbers to puzzle if theres only one possible

            for (m=0;m<9;m++){printf("\n here is the value remaining %d",possible[m]);}

        }
       
    }


// ---------------------------------------------
// check to see if we did anything if not break
    for (i=0; i<81;i++);
        if (new[i] != puzzle[i])
        {
            //return(0);
        }
    return (1);
}

int main(void){
//---------------- INITALISATIONS--------------
    int puzzle[81] = {0};
    starting(puzzle);
    int i;
    //for (i=0;i<81; i++)
    //    printf("Number is: %d\n\n", puzzle[i]);
    int cont = 1;
    int broken =0;
// ---------------Main LOOP---------------
    while (cont == 1 && broken != 1){
        broken = solve(puzzle);
        cont = checkcomplete(puzzle);
    }
    if (broken ==1){
        printf("\n Couldnt solve too stupid :( ");
    }
    else{
        for (i = 0; i < 81; i++)
        {
            printf("Number is: %d\n\n", puzzle[i]);
        }
    }
    return 0;
}
