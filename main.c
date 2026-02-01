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
    fclose(fileptr);
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
int* solve(int puzzle[]){
    int i;
    int m;
    int a;
    int b;
    int row; // top to bottom
    int rowvalue;
    int column; // left to right
    int columnvalue;
    int box; // 1 top left 2 middle top
    int boxcomp[9] = {0};
//SOLVE LOGIC-------------------------------------
    for(i=0; i<81; i++) // for each number
    {
        if (puzzle[i]==0) //if unsolved
        {
            int possible[9] = {1,2,3,4,5,6,7,8,9};
            row = floor(i/9);
            column = i%9; //starting at 0->8
            // ----------------- box logic
            for(a=0;a<3;a++) //row of box
                {
                    for(b=0;b<3;b++) //col of box
                    {
                        box = (b+(column- (column%3))+((row- (row%3)+a)*9));
                        boxcomp[a*3+b] = puzzle[(b+(column- column%3)+((row- row%3+a)*9))];   
                    }
                    
                } 
            //---------------------------
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
                if (boxcomp[m] !=0)
                {
                    possible[boxcomp[m]-1]=0;
                }
            }

            // insert logic to sub in the numbers to puzzle if theres only one possible
            int possibleoptions =0;
            int possiblepos;
            for(m=0;m<9;m++)
            {
                if (possible[m]!=0)
                {
                    possibleoptions++;
                    possiblepos=m;
                }
            }
            if (possibleoptions==1) // if there is only one possible option
            {
                puzzle[i] = possible[possiblepos];
                // printf("\n made a change");

            }
        }
       
    }
    return puzzle;
}
int *write(int done[])
{
    int printhelp;
    int i;
    char writing;
    fileptr =fopen("solved.txt","w");
    for (i = 0; i < 81; i++)
    {
        writing = ("%d ", done[i]);
        fprintf(fileptr,"%d ",done[i]);
        printhelp++;
        if (printhelp ==9)
        {
            fprintf(fileptr,"\n");
            printhelp =0;
        }
    }
    fclose(fileptr);
}


int main(void){
//---------------- INITALISATIONS--------------
    int puzzle[81] = {0};
    starting(puzzle);
    int i;
    int j;
    int new[81]= {0};
    for (i=0; i<81;i++)
    {
        new[i] = puzzle[i];
    }
    int cont = 1;
    int broken =0;
//---------------Main LOOP---------------
    while (cont == 1 && broken != 1)       
    {
        cont = checkcomplete(new);
        broken = 1;
        solve(new);
        // check and see if changes were made
        for (j=0; j<81;j++);
            if (new[i] != puzzle[i])
            {
                printf("this happened");
                broken = 0; // a change was made
                puzzle[i] = new[i];
            }
    }
    //----------------------------------------
    printf("\n exited while \n");
    int printhelp = 0;
    if (cont==0)
    {
        broken=0;
    }
    if (broken ==1){
        printf("\n Couldnt solve too stupid :( ");
    }
    else{
        for (i = 0; i < 81; i++)
        {
            printf("%d ", new[i]);
            printhelp++;
            if (printhelp ==9)
            {
                printf("\n");
                printhelp =0;
            }
        }
    }
    write(new);
    return 0;
}