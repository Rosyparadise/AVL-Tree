#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctype.h>
#include <time.h>
#include "AVLT.h"



#define N 1000000//Number Of Random Words
#define C 1//if C==1, the output file will contain all words with their respective counters (takes longer)

//saving the words from the text file in the data array
void Data_creation (char **&data,unsigned int &cw)
{
    //opening the file
    ifstream readtext("insert_name_here.txt");
    string word;
    unsigned int j, i=0;
    //allocating dynamic memory for the data array
    data= (char**)malloc(sizeof(char*));

    if(readtext.is_open())//if the text file is open without a problem
    {
        while (readtext >> word)//and while there are words to read from it
        {
            //edit each word --removing the punctuation and turning it to lower case-- and save the word in the data array
            i=0;//counter to know which letter of the word is being edited
            data[cw] = (char*)malloc(sizeof(char));

            for(j=0;j<word.length();j++)
            {
                word[j] = tolower(word[j]); //conversion to lowercase

                if(!(ispunct(word[j])&& word[j]!='\n'))//if the word[j] character is not punctuation or '\n', it is added to data
                {
                    data[cw][i] = word[j];
                    i++;//next letter
                    data[cw] = (char*)realloc(data[cw], sizeof(char)*(i+1));//adding dynamic memory for each letter
                }
            }
            //once the word editing is done, at the end of the word we add '\0' to symbolize the end of it
            data[cw][i]='\0';

            cw++;//word counter

            if (!((cw+99999)%100000))
            {
                data = (char**)realloc(data, sizeof(char*)*(cw+100000));//adding extra dynamic memory, new row
            }
        }
    }
    readtext.close();
    data = (char**)realloc(data, sizeof(char*)*(cw));//removing the extra allocated memory
}

//creation of array Q, which contains random words from the array Data
void Q_creation (char**&Q,char** data,unsigned int cw)
{
    int i, j,ranum;

    Q = (char**)malloc(sizeof(char*)*N);//allocating dynamic memory
    for(i=0; i<N;i++)
    {
        Q[i] = (char*)malloc(sizeof(char));
    }

    for(i=0;i<N;i++)
    {
        ranum = rand()%cw;//generating a random number within the data array limits - - this number corresponds to the array cell the random word will be saved in
        for(j=0;data[ranum][j]!='\0';j++)
        {
            Q[i][j] = data[ranum][j];//copying the word letter by letter from the data array to Q
            Q[i] = (char*)realloc(Q[i], sizeof(char)*(j+2));//allocating memory for the next letter
        }
        Q[i][j] = '\0';
    }//repeating as many times as the random words we need
}

//counts time taken for each data structure to search for every word in Q
void Get_time(AVLT b,char** Q)
{
    ofstream output("output.txt");//the output file, the results will be shown in this file

    int i=0;

    clock_t tStart0 = clock();
    for (i=0;i<N;i++)
    {
       b.GetSer(Q[i]);//searching each word in the AVLT class
    }
   output<<"Time taken for the creation of AVLT: "<<(double)(clock() - tStart0)/CLOCKS_PER_SEC<<endl;


    if (C==1)
    {
        for (i=0;i<N;i++)
        {
            b.printsearch(Q[i], output);
        }
    }
    output.close();
}



int main()
{
    unsigned int i, cw=0;//cw is the word counter
    char **Q,**data ; //data is a dynamic array that contains every word in the given text, Q is a dynamic array that contains random words of data
    cout<<"Processing"<<endl<<endl;
    Data_creation(data,cw);
    Q_creation(Q,data,cw);

    AVLT b;//creating AVLT object

    for (i=0;i<cw;i++)
    {
        //inserting words in each class
        b.GetIns(data[i]);
    }

    Get_time(b,Q);

    cout<<"Please check output.txt"<<endl;//for the time and counter results please check the output text file!
    return 0;
}
