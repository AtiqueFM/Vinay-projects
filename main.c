/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define DIFF    150.0f

int raw_data[250000];
float low_range_array[100000];
float high_range_array[100000];
//unsigned int index_ = 0;
unsigned int len_of_array = 0;
float den = 1;
float average_ = 0;
unsigned int averaged_index_low = 0;
unsigned int averaged_index_high = 0;
float data = 0;
float temp_sum = 0;

void reading_file(void)
{
    //read input file into int memory[]
    FILE *ifp;
    ifp = fopen("data", "r"); //input file TODO: change to "../instr/proj1a.dat" before submitting
    
       
   char str[18] = {0};//current line from file 
   int i = 0; //index of memory
    while(fgets(str, sizeof(str), ifp) != NULL){
        raw_data[i] = (short)(strtol(str, NULL, 10));
        //printf("%d\n", raw_data[i]);//DEBUG
        i++;
    }
    len_of_array = i;
    printf("length of data: %d\n",len_of_array);
}
int main()
{
    printf("Reading data from file...\n");
    reading_file();
    printf("Starting!!!!!\n");
    
    for(int index_ = 0;index_ < len_of_array;index_++)
    {
        //printf("index : %d\n",index_
        data = raw_data[index_];
        float temp = abs(raw_data[index_] - raw_data[index_ + 1]);
        
        //printf("sub : %f\n",temp);
        if( temp < DIFF)
        {
            temp_sum += data;
            average_ = temp_sum/den;
            //printf("Average: %f\n",average_);
            den += 1;
        }else if(average_ == 0)
        {
            den = 1;
            temp_sum = 0;
            average_ = 0;
        }else if(average_ > 0)
        {
            if(average_ < 11000)
            {
                low_range_array[averaged_index_low++] = average_;
            }else
            {
                high_range_array[averaged_index_high++] = average_;
            }
            
            average_ = 0;
            temp_sum = 0;
            
            den = 1;
            //index_ += 1;
        }
    }
    
    printf("Averaged index low :%d\n",averaged_index_low);
    printf("Averaged index high :%d\n",averaged_index_high);
    #if defined(SHOW_DATA)
    printf("Low range values are\n");
    for(int i = 0;i<averaged_index_low;i++)
    {
        printf("%f\n",low_range_array[i]);
    }
    
    printf("High range values are\n");
    for(int i = 0;i<averaged_index_high;i++)
    {
        printf("%f\n",high_range_array[i]);
    }
    #endif
    return 0;
}
