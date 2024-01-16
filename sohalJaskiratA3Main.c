/************************sohalJaskiratA3Main.c************** 
Student Name: Jaskirat Singh Sohal Email Id: jsohal03@uoguelph.ca
Due Date: November 25 Course Name: CIS 1300 
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


int main(int argc, char * argv[]) {

    //Variables Declaration
    int country[COUNTRIES][MEDALCAT];
    char countryNames[COUNTRIES][MAX_LENGTH_CNAME];
    int totalAllCountries[COUNTRIES];
    int totalAllMedals[MEDALCAT];
    int * whichMedal= &totalAllMedals[MEDALCAT];
    int indexOfCountries [COUNTRIES];
    int choice;
    int sum;
    int medalNum;
    int count;
    int num;
    int maxIndex ,minIndex;
    char name[COUNTRIES];
  

    readFromFile(argv[1], country, countryNames);// calling the required function
 

    do {
        printf("\nHere is the menu \n\n");
        printf("1.Display all country names read from file and the total number of medals won by each\n");
        printf("2.Function 2 - Find total number of medals won by each country\n");
        printf("3.Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
        printf("4.Function 4 - Display horizontal histogram\n");
        printf("5.Function 5 - Search for a country and return the total number of medals won by it\n");
        printf("6.Function 6 - Rank and display top three countries in order of total medals won\n");
        printf("7.Function 7 - Rank and display top three countries in order of total gold medals won\n");
        printf("8.Function 8 - Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
        printf("9.Function 9 - Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
        printf("10.Function 10 - Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", & choice);

        switch (choice) {
            case 1:
                readFromFile(argv[1], country, countryNames);
                break;
            case 2:
                findTotalPerCountry(country,totalAllCountries);
                for(int i=0;i<COUNTRIES;i++){
                    printf("Country %s = %d\n",countryNames[i],totalAllCountries[i]);
                }
                break;
            case 3:
                findTotalPerMedal (country,totalAllMedals,whichMedal);
                printf("In findTotalPerMedal\n");
                printf("Medal = Gold, Total = %d\n", totalAllMedals[0]);
                printf("Medal = Silver, Total = %d\n", totalAllMedals[1]);
                printf("Medal = Bronze, Total = %d\n", totalAllMedals[2]);
                break;
            case 4:
                hHistogram (countryNames, totalAllCountries);
                break;
            case 5:
                
                printf("Searching for which country ?");
                scanf("%s", name);
                sum = searchCountry(name,countryNames,totalAllCountries);
                printf("In searchCountry\n");
                if(sum==-1){
                    printf("Country name not found in database\n");
                }
                else{
                    printf("Found it - %s has a total of %d medals", name,sum);
                }
                break;
            case 6:
                rankTopThreeByTotal (totalAllCountries, countryNames);
                break;
            case 7:
                rankTopThreeByMedal (country , countryNames);
                break;
            case 8:

                printf("Which medal do you want to look for - Type 0 for Gold, 1 for Silver, 2 for Bronze? ");
                scanf("%d",&medalNum);
                count = findAllWithNoXMedals (country,medalNum, indexOfCountries);
                if(medalNum==0){
                    printf("Number of countries with no Gold medals = %d", count);
                }
                else if(medalNum==1){
                    printf("Number of countries with no Silver medals = %d", count);
                }
                else if(medalNum==2){
                    printf("Number of countries with no Bronze medals = %d",count);
                }
                
                break;
            case 9:
                printf("Which medal do you want to look for - Type 0 for Gold, 1 for Silver, 2 for Bronze? ");
                scanf("%d",&medalNum);
                count = findAllWithOnlyXMedals (country,medalNum, indexOfCountries);
                if(medalNum==0){
                    printf("Number of countries with only Gold medals = %d", count);
                }
                else if(medalNum==1){
                    printf("Number of countries with only Silver medals = %d", count);
                }
                else if(medalNum==2){
                    printf("Number of countries with only Bronze medals = %d",count);
                }
                
                break;
            case 10:
                printf("Do you want min(Enter 1) or max(Enter 2): ");
                scanf("%d",&num);
                if(num==1){
                    minIndex = findCountryIndexWithMinOrMaxLength(num, countryNames);
                    printf("Country name with minimum length = %s", countryNames[minIndex]);

                }
                else if(num==2){
                    maxIndex = findCountryIndexWithMinOrMaxLength(num, countryNames);
                    printf("Country name with maximum length = %s", countryNames[maxIndex]);

                }
                break;

            default:
                printf("That is an invalid choice\n");

        }

  } while (choice != 11);

    return 0;

}