#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TITLE "DECIMAL TO RADIX-i converter"
#define AUTHOR "TANAKA"
#define YEAR 2022
int main()
{
    int radix,j,i,qoutient,reminder;
    int dec = 1;
    for (j = 1;j<30;j++)
    {
        printf("*");     //displays a line of starts
    }
    printf("\n");

//to display the program name,
//programmer and date created

    printf("%s \n",TITLE);
    printf("Written by:%s\n",AUTHOR);
    printf("Date: %d \n", YEAR);

    for (j = 1;j<30;j++)
    {
        printf("*");
    }
    printf("\n");

//loop to continuously run the program,
//until a value of less than one is entered
//terminates the program and display EXIT

    while(dec > 0){
         printf("Enter a decimal number: ");
         scanf("%d",&dec);
         if (dec< 0){
            printf("EXIT");
            break;}

         else {
            printf("The number you have entered is %d \n",dec);
            printf("Enter a radix for the converter between 2 and 16: ");
            scanf("%d",&radix);
            printf("The radix you have entered is %d \n",radix);
         }

         double dec_double = dec,log_result;
         log_result = log2(dec_double);
         printf("The log2 of the number is %.2f \n",log_result);

         qoutient = dec/radix;
         printf("The integer result of the number divided by %d is %d \n",radix,qoutient);

         reminder = dec % radix;
         printf("The remainder is %d \n",reminder);

//calls function that displays
// the radix equavalent to decimal
         Dec2RadixI(dec,radix);


    }

    return 0;
}
void Dec2RadixI(int decValue, int radValue ){

//calculate the size of an array
//to store the radix equalavent

     double dec_double = decValue, rad_double = radValue,log_res;
     log_res = ((log10(dec_double))/(log10(rad_double)));
     int size = (log_res +1) ;

//form array to store the result

     char str[size];
     int temp,result[size];

//continuous division of the decimal by radix
//storing the reminder in array to form result

     for(int i=0;decValue>0;i++){
            result[i]=decValue%radValue;
            decValue = decValue/radValue;
     }
//store the reminders from bottom up,
//reverse the result array
     for(int k = 0;k< (size/2) ; k++){
        temp = result[k];
        result[k] = result[size-k-1];
        result[size-k-1] = temp;
     }
//change integer values after nine
//to equavalent characters,eg
//10 = 'A' , 11 = 'B' , etc

     for (int i = 0; i < size; i++)
    {
	if (result[i]>= 0 && result[i] <= 9)
		str[i] = (result[i]+48);
	else
		str[i] = (result[i] + 55);
    }

//print the final result as a string in correct format
    printf("The radix-%d value is ",radValue);
    for(int h = 0;h <size; h++){
        printf("%c", str[h]);
    }
    printf("\n");
}
