#include <stdio.h>
#include <math.h>
FILE *fileptr;
int* starting(int puzzle[]){
    fileptr = fopen("evennewpuzz.txt","r");
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
        
    }
    printf("\n Solved :)");
    return(0);

}
int solve(int puzzle[], int broken){
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
            printf("\n --------------- starting new comp in positon %d\n",i);
            int possible[9] = {1,2,3,4,5,6,7,8,9};
            row = i/9;
            column = i%9; //starting at 0->8
            // printf("\n number %d Row %d Col %d",i, row,column);
            // ----------------- box logic
            // required maybe
            for(a=0;a<3;a++) //row of box
                {
                    for(b=0;b<3;b++) //col of box
                    {
                        box = (b+(column- (column%3))+((row- (row%3)+a)*9));
                        boxcomp[(a*3)+b] = puzzle[(b+(column- column%3))+((row- row%3+a)*9)];   // might be brk
                    }
                } 
            //---------------------------
            
            for (m=0;m<9;m++) //check row for impossible options
            {
                rowvalue = puzzle[(m+(9*row))]; 
                if (rowvalue !=0)
                {
                    //printf("\n rowvalue %d detected deleting %d was compared to pos%d",rowvalue, possible[rowvalue-1], (m+(9*row)));
                    possible[rowvalue-1]=0;
                }

                columnvalue = puzzle[column+(m*9)];
                if (columnvalue != 0)
                {
                    //printf("\n col %d detected deleting %d",columnvalue, possible[columnvalue-1]);
                    possible[columnvalue-1]=0;
                    
                }
                
                if (boxcomp[m] !=0)
                {
                    // printf("\n box numbers = %d detected deleting %d",boxcomp[m], possible[boxcomp[m]-1]);
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
                // printf("\n made a change Number %d became %d",i,possible[possiblepos]);
                broken =0;

            }
        }
       
    }
    return broken;
}
void write(int done[])
{
    int printhelp = 0;
    int i;
    char writing;
    fileptr =fopen("solved.txt","w");
    for (i = 0; i < 81; i++)
    {
        writing = ("%d ", done[i]);
        fprintf(fileptr,"%d ",done[i]);
        printhelp++;
        if (printhelp == 9)
        {
            fprintf(fileptr," \n");
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
    int broken = 0;
    int new[81]= {0};
    for (i=0; i<81;i++)
    {
        new[i] = puzzle[i];
        printf("%d ",new[i]);
    }
    int cont = 1;
//---------------Main LOOP---------------
    while (cont == 1 && broken != 1)       
    {
        broken = solve(new ,1);
        cont = checkcomplete(new);
        // check and see if changes were made
        for (j=0; j<81;j++);
            if (new[j] != puzzle[j])
            {
                printf("  <- but meaningful change");
                broken = 0; // a change was made
                puzzle[j] = new[j];
            }
    }
    //----------------------------------------
    printf("\n exited while \n");
    int printhelp = 0;
    if (cont==0)
    {
        broken=0;
        printf("\n I think im done \n");
    }
    if (broken ==1){
        printf("\n Couldnt solve too stupid :( ");
    }
//    else{
    printf("\n");
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
//    }
    write(new);
    return 0;
}