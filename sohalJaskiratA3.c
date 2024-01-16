/************************sohalJaskiratA3.c************** 
Student Name: Jaskirat Singh Sohal Email Id: jsohal03@uoguelph.ca
Due Date: November 30 Course Name: CIS 1300 
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that: 
1) I have read and understood the University policy on academic integrity. 
2) I have completed the Computing with Integrity Tutorial on Moodle; and 
3) I have achieved at least 80% in the Computing with Integrity Self Test. 

I assert that this work is my own. I have appropriately acknowledged any and 
all material that I have used, whether directly quoted or paraphrased. 
Furthermore, I certify that this assignment was prepared by me specifically for 
this course. 
********************************************************/

/*********************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall 
compiling:

gcc -std=c99 -Wall sohalJaskiratA3Main.c sohalJaskiratA3.c
Running the Program: ./a.out commonWealth.txt
*********************************************************/

#include "givenA3.h"

#include "stdio.h"

#include"math.h"

/*
This function takes 3 parameters as shown. The 1st parameter called fileWithMedals is a string that
stores the filename of a sequential data file. The 2nd and 3rd parameters are populated using data file
that stores the country names and medals won by each country.
*/
void readFromFile(char fileWithMedals[30], int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
 
    FILE * fPtr;

    fPtr = fopen(fileWithMedals, "r");//Opened the file in read mode.
    int i=0;
    int j=0; 
    if(fPtr==NULL){//If file is empty.
        printf("Cannot open the file.\n");
    }
    else{
        while(!feof(fPtr)){//File will be read and data will be stored in array until it is the end of it.
            fscanf(fPtr,"%s %d %d %d",countryNames[i],&country[i][j],&country[i][j+1],&country[i][j+2]);
            i++;
        }
        fclose(fPtr);
    }
    
    printf("Countries\tTotal Medals\n");
    for (int i = 0; i < COUNTRIES; i++) {

        printf("%s\t%d\n", countryNames[i], (country[i][0] + country[i][1] + country[i][2])); 

    }


}

//This function finds total medals for each country and stores it in array totalAllCountries.
void findTotalPerCountry(int country[COUNTRIES][MEDALCAT], int totalAllCountries[COUNTRIES]) {
    int i;
    int totalMedals;
    for (i = 0; i < COUNTRIES; i++) {

        totalMedals=(country[i][0] + country[i][1] + country[i][2]);//sum of medals.
        totalAllCountries[i]=totalMedals;
    }
}

/*
This function finds total number of medals in each category (Gold/Silver/Bronze) and stores them in array totalAllMedals.
It Returns the maximum value in totalAllMedals.
Outputs (through call-by-reference parameter) the index of the category with maximum medals –
category given in parameter whichMeda
*/
int findTotalPerMedal (int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal){

    int i;
    int maxNum;
    totalAllMedals[0]=0;//Stores total Gold Medals
    totalAllMedals[1]=0;//Stores total Silver Medals
    totalAllMedals[2]=0;//Stores total Bronse Medals
    for (i = 0; i < COUNTRIES; i++) {
        totalAllMedals[0]=totalAllMedals[0]+country[i][0];
        totalAllMedals[1]=totalAllMedals[1]+country[i][1];
        totalAllMedals[2]=totalAllMedals[2]+country[i][2];
    }
    maxNum=totalAllMedals[0];
    for(i=0;i<3;i++){

        if(maxNum<totalAllMedals[i]){
            maxNum=totalAllMedals[i];
            whichMedal=&i;
        }
    }
    return maxNum;

}

/* 
This function Displays a horizontal histogram of stars, where each star represents 2 medals (any remaining medal
will also count as 1 star).   
*/
void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES]){
    int i,j;
    int count;
    for(i=0;i<COUNTRIES;i++){
        printf("%s : ",countryNames[i]);
        count =(totalMedals[i]/2)+(totalMedals[i]%2);

        for(j=0;j<count;j++){
            printf("*");

        }
        printf(" (%d)\n",totalMedals[i]);
    }
}
 
/* 
This function returns the total number of medals won by a country, given its name (countryName). If countryName
does not exist in the given list of 10 countries, it returns -1.
*/
int searchCountry(char countryName[MAX_LENGTH_CNAME], char countryNames[COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries[COUNTRIES]) {
    int i;
    int medalSum=-1;
    for (i = 0; i < COUNTRIES; i++) {
        if (strcmp(countryName,countryNames[i]) == 0) {//Compares both arrays if same then return total.
            medalSum = totalAllCountries[i];
            break;
        }
    }
    return medalSum;

}
 
//This function displays the top three country names and the total medals won by each of them.
void rankTopThreeByTotal(int totalMedals[COUNTRIES], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]) {
    int first = 0;
    int second = 0;
    int third = 0;
    char topFirst[50];
    char topSecond[50];
    char topThird[50];
    for (int i = 0; i < COUNTRIES; i++) {

        if (first < totalMedals[i]) {//If first is less than some value it has to be either second or third.
            third = second;
            second = first;
            first = totalMedals[i];//Greater value gets stored in first
            strcpy(topFirst, countryNames[i]);
        } 
        else if (second < totalMedals[i] && first != totalMedals[i]) {
            third = second;
            second = totalMedals[i];
            strcpy(topSecond, countryNames[i]);
        } 
        else if (third < totalMedals[i] && second != totalMedals[i]) {
            third = second;
            third = totalMedals[i];
            strcpy(topThird, countryNames[i]);
        }
    }
    printf("%s (%d)\n", topFirst, first);
    printf("%s (%d)\n", topSecond, second);
    printf("%s (%d)\n", topThird, third);
}

//Displays the top three country names and the total gold medals won by each of them.
void rankTopThreeByMedal (int country [COUNTRIES] [MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    int first = 0;
    int second = 0;
    int third = 0;
    char topFirst[50];
    char topSecond[50];
    char topThird[50];
    for (int i = 0; i < COUNTRIES; i++) {

        if (first < country[i][0]) {//Similar to the logic used in function 6.
            third = second;
            second = first;
            first = country[i][0];
            strcpy(topFirst, countryNames[i]);
        } 
        else if (second < country[i][0] && first != country[i][0]) {
            third = second;
            second = country[i][0];
            strcpy(topSecond, countryNames[i]);
        } 
        else if (third < country[i][0] && second != country[i][0]) {
            third = second;
            third = country[i][0];
            strcpy(topThird, countryNames[i]);
        }
    }
    printf("%s (%d)\n", topFirst, first);
    printf("%s (%d)\n", topSecond, second);
    printf("%s (%d)\n", topThird, third);

}

/*
Returns the total number of countries with no medal of a specific category, where category = indexMedal (0 for Gold, 1 for Silver, 2 for Bronze).
*/
int findAllWithNoXMedals (int country [COUNTRIES] [MEDALCAT],int indexMedal, int indexOfCountries [COUNTRIES]){
    int i;
    int medalCount=0; 
    for(i=0;i< COUNTRIES;i++){
        if(country[i][indexMedal]==0){
            medalCount++;
            indexOfCountries [i]=i;//Stored the index of country in a array.

        }
    }
    return medalCount;
 }

 /* 
 This function returns the total number of countries that have ONLY won medals of a specific category, where 
 category = indexMedal (0 for Gold, 1 for Silver, 2 for Bronze)
 */
int findAllWithOnlyXMedals (int country [COUNTRIES][MEDALCAT],int indexMedal, int indexOfCountries [COUNTRIES]){
    int i;
    int medalCount=0;
    for(i=0;i<COUNTRIES;i++){
        if(indexMedal==1){
            if(country[i][0]>0 && country[i][1]==0  && country[i][2]==0 ){
                medalCount++;
                indexOfCountries [i]=i;
            }
        }
        else if(indexMedal==2){
            if(country[i][1]>0 && country[i][0]==0  && country[i][2]==0 ){
                medalCount++;
                indexOfCountries [i]=i;
            }
        }
        else if(indexMedal==3){
            if(country[i][2]>0 && country[i][1]==0  && country[i][0]==0 ){
                medalCount++;
                indexOfCountries [i]=i;
            }
        }
    }
    return medalCount;
}

 /*
Returns the index of the countryName that has min or max length - use 1 for min and 2 for max. You
must return only one index, even if there are more than 1 countryNames with a max or min length.
*/
int findCountryIndexWithMinOrMaxLength (int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){
    int index = 0;
    int minLen , maxLen;
    int len, i;
    if(minOrMax==1){
        minLen=strlen(countryNames[0]);
        for(i=0;i<COUNTRIES;i++){
            len=strlen(countryNames[i]);
            if(minLen>len){
                minLen=len;
                index=i;
            }
        }
    }
    else if(minOrMax==2){
        maxLen=strlen(countryNames[0]);
        for(i=0;i<COUNTRIES;i++){
            len=strlen(countryNames[i]);
            if(maxLen<len){
                maxLen=len;
                index=i;
            }
        }
    }
    return index;
 }
 
