#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//a function to turn words into all lowercase
char *turningLower(const char *givenWord)
{   //here i am allocating space from heap for the lowercase version pointer
	//if i did not do this, the return value would be unreachable since it returns a pointer
    char *lowercaseVersion = (char *)malloc(strlen(givenWord)+1);
	if(lowercaseVersion!=NULL){
    int i = 0;
        while (givenWord[i] != '\0') {
            lowercaseVersion[i] = tolower((unsigned char)givenWord[i]);
            i++;
        }
		//after while loop ends, i added the null terminating to the lowercaseversion pointer for it to be a valid string
        lowercaseVersion[i] = '\0'; 
    }
	return lowercaseVersion;

}
//counts occurences of the given words in the file "preprocessed_dataset.txt", i tried to taking file name
//as a parameter but it gave a path error 
void occurenceCounter(char *word){
	 char searchedWord[100];
 	strcpy(searchedWord,word);
 	//I did not want to modify the given word(maybe uppercase) to write unmodified word to the print message
 	strcpy(searchedWord,turningLower(searchedWord));
	 FILE *ourFile;
 	//opening the file in the read mode
 	ourFile = fopen("preprocessed_dataset.txt","r");
 	if(ourFile== NULL){
		 perror("there is an error while opening the file for Occurence Counter");
 		exit(1);
	 }
	char line[1024];
	int spamcount=0;
	int hamcount=0;
	char *eachWord= NULL;
	char lowercaseEachWrd[100];
	//I used fgets function to read the dataset line by line 
	while(fgets(line,sizeof(line),ourFile)!=NULL){
		eachWord= strtok(line," \t\n");
		while(eachWord != NULL){
			//turning each word to lower make an appropriate comparison
           		strcpy(lowercaseEachWrd,turningLower(eachWord));
	  		 if(line[0] =='s'){
	   			if(strcmp(lowercaseEachWrd,searchedWord)==0){
		  			 //spam cnt will be increased
		  			 spamcount++;
	   }
	   }
	  		 if (line[0]=='h'){
		   		if (strcmp(lowercaseEachWrd,searchedWord)==0){
                       		// ham cnt will be increased
		      		 hamcount++;
		  		 }
	   }
	  		 // changing the word to scan with another word
	  		 eachWord= strtok(NULL," \t\n");
	}

}     //if there is no matching word, it will print the following message
   if( spamcount==0 && hamcount==0){
	   printf("This word doesn't occur in the text!\n");
   }
//if there are matches, it will print how many matches there are
else{
	printf("The word %s appears %d times in ham messages and %d times in spam messages.\n", word,hamcount,spamcount);
}
fclose(ourFile);
}

// a struct to keep the word and its occurence in one object
struct wordandcount
{
	char word[50];
	int count;
};
// this function returns a pointer to a struct array, i will use the return value later
struct wordandcount *commonWords(){
 	int lenghtofWord, i,j, numWordsProcessed, isWordUnique;
	//I assumed, a lines max lenght is 1024 chars
	char line[1024];
	//here is an array of structs
	// i checked the numwordsprocessed variable after writing my code and changed the size of the struct array accordingly
	struct wordandcount arrayofWordCtStc[2126];
	FILE *filePointer;
	filePointer = fopen("preprocessed_dataset.txt","r");
	if(filePointer== NULL){
		perror("there is an error while opening the file for common words");
 		exit(1);
}
	numWordsProcessed =0;
	char lowercaseEachWrd[50];
	while(fgets(line,sizeof(line),filePointer)!=NULL){
		if(line[0]!='s'){
			//here it will not check for the distinct words in ham messages
			continue;
		}
		char *eachWord= strtok(line," \t\n");
		

		while(eachWord != NULL){
        	strcpy(lowercaseEachWrd,turningLower(eachWord));
			//here i will not count the word "spam" bc is appears at all spam messages
				//If i count it, it will be the most occuring word
			if(strcmp(lowercaseEachWrd,"spam")!=0){
				isWordUnique =1;
				for (i=0;i<numWordsProcessed;i++){
					//printf("inside of first for, num words processed: %d \n",numWordsProcessed);
					if(strcmp(arrayofWordCtStc[i].word,lowercaseEachWrd)==0){
						//a matching word found, the count will be increased.
						arrayofWordCtStc[i].count++;
						isWordUnique =0;
						break;		
				}
				}
				if(isWordUnique){
					strcpy(arrayofWordCtStc[numWordsProcessed].word,lowercaseEachWrd);
					//if word is not found in already existing structs, we will add the word to struct array with occurence 1
					arrayofWordCtStc[numWordsProcessed].count=1;
					numWordsProcessed++;
				}
			}
			// changing the word to scan with another word
	  		 eachWord= strtok(NULL," \t\n");
	}
	}
	fclose(filePointer);
	// to sort the words according to their occurences, i will use a descending bubble sort algorithm.
	//MY SORT ALGORITHM
	for(i=0;i<numWordsProcessed;i++){
		for(j=i+1; j<numWordsProcessed;j++){
			if(arrayofWordCtStc[i].count<arrayofWordCtStc[j].count){
				struct wordandcount tempWordCount = arrayofWordCtStc[i];
				arrayofWordCtStc[i]= arrayofWordCtStc[j];
				arrayofWordCtStc[j]= tempWordCount;

			}
		}
	}
	//here i have to return top 10 used words to use it in the 3rd function and main function
	// to print the words and occurences, i will return a struct array
	// allocating memory for a struct array with 10 elements
	struct wordandcount *returnValue= (struct wordandcount*)malloc(sizeof(struct wordandcount)*10);
	if(returnValue){
		for(i=0;i<10;i++){
			returnValue[i]= arrayofWordCtStc[i];
		}
	}
	return returnValue;
} 
/*void freeWordsArray(struct wordandcount *words){
	int i;
	for(i=0;i<10;i++){
		free(words[i]);
	}
	free(words);
}*/
// here is a function to check if a single message is spam or not
int isLineSpam(char *line){
	char *eachWord;
	char lowercaseEachWrd[100];
	int distinctSpamCount=0;
	int i;
	struct wordandcount *toptenWordsstc= commonWords();
	eachWord = strtok(line," \t\n");
	// here is an integer array to keep track of if that spam word occured more than once
	//since we are asked to count only distinct spam words
	int didItseenBefore[10];
	for(i=0;i<10;i++){
		didItseenBefore[i]=0;
	}
	while(eachWord!=NULL){
		strcpy(lowercaseEachWrd,turningLower(eachWord));
		for(i=0;i<10;i++){
			if(didItseenBefore[i]==0 && strcmp(lowercaseEachWrd,toptenWordsstc[i].word)==0){
				didItseenBefore[i]=1;
				distinctSpamCount++;
			}
			
		}
		eachWord=strtok(NULL," \t\n");
	}
	if(distinctSpamCount>=3){
		return 1;//means the line is labeled as spam
	}
	else{
		return 0;
	}
}
void spamDetector(){
	int spamBeingSpam = 0;//true detection
	int spamBeingHam = 0;//false detection
	int hamBeingSpam=0;//false detection
	int hamBeingHam=0;//true detection
	int i;
	FILE *filePointer;
 	//opening the file in the read mode
 	filePointer = fopen("testData.txt","r");
 	if(filePointer== NULL){
		 perror("there is an error while opening the file for spam detector");
 		exit(1);
	 }
	 char line[1000];
	 char *eachWord= NULL;
	 char lowercaseEachWrd[100];
	 while(fgets(line,sizeof(line),filePointer)!=NULL){
		int tempDistinctSpm=0;	
		int spamStatus= isLineSpam(line);
		// two if statements to keep track of the spam and ham word counts
	  	if(line[0] =='s'){
			if(spamStatus){
					spamBeingSpam++;// true detection
				}
				else{spamBeingHam++;}// false detection
			
	   }
		if (line[0]=='h'){
				if(spamStatus){
					hamBeingSpam++;//false detection
				}
				else{hamBeingHam++;}// true detection
	   }
	  		 
			
	   }
	   // here i am not sure of the accuracy of the ham predictions so i made my program write explicitly the values
	   // since it labels ham messages as spam, this have to decrease the accuracy rate of the ham messages 
	double accuracySpam = 100.0*(spamBeingSpam/(double)(spamBeingSpam+spamBeingHam));
	double accuracyHam =100.0*( hamBeingHam/(double)(hamBeingHam+spamBeingHam));
	int totalHam= hamBeingSpam+hamBeingHam;
	int totalSpam = spamBeingSpam+spamBeingHam;
	//printf("total correct spam detection: %d\n",spamBeingSpam);
	printf("spam labeled as spam: %d\n",spamBeingSpam);
	printf("spam labeled as ham:(wrong detection) %d\n",spamBeingHam);
	printf("ham labeled as spam: (wrong detection) %d\n",hamBeingSpam);
	printf("ham labeled as ham: %d \n",hamBeingHam);
	printf("Accuracy of spam predictions: %f %% \n",accuracySpam);
	printf("Accuracy of ham predictions: %f %%\n",accuracyHam);
	printf("Total spam messages: %d (actual spam count)\n",totalSpam);
	printf("Total ham messages: %d (actual ham count)\n",totalHam);
	   }


int main(){
	char searchedWord[100];
	int i;
	printf("Please enter a word to search for: ");
	scanf("%s", searchedWord);
	occurenceCounter(searchedWord);
	struct wordandcount *topTenSpam =commonWords();
	printf("Top 10 occurring words in spam messages: \n");
	for(i=0; i<10; i++){
		// getting top 10 word and count struct from the return value of commonwords function to print output
		printf("%s:  %d times \n",topTenSpam[i].word,topTenSpam[i].count);
	}
	spamDetector();
	free(topTenSpam);

return 0;
}
/* Task 4 Question: Did the spam detector perform as well as you expected? If not, what could be the reason for this behavior?
What would you change to improve the detector?
TASK 4 ANSWER: My expectations about accuracy rate was higher but still i was not expecting it to be %100 true.
I think the reason for this error is that we are only checking top 10 words, in the preprocessed dataset, especially in spam messages there
are 2024 different words but we are just taking top ten for spam check.
I think we could take top 200 words from this list,accuracy rate would be higher. But my algorithm is already not so efficient right now
so, if we were to make this changes i have to change the implementation of spamdetector function.
(I checked other functions and spamdetector function is the most time consuming function above all)

*/
