#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *readSection(FILE *in);
double letterGradeToDoubleValue(char grade[3]);

typedef struct course
{
	char name[2048];
	int credits;
	char letterGrade[2048];
	char term[2048];
} course;

char currentChar;

char *currentTerm, currentWord[2048];

int numClasses = 0, classCounter = 0, numTerms = 0, currentWordLength = 0, numABC = 0;

double sumCredits = 0, sumGrades = 0, sum = 0;

course courseArray[50];

int main(void)
{
	printf("Made by Noah Lang :)\n\n");

	// 1 pass through the file to determine the amount of classes there are
	FILE *first = fopen("classes.txt", "r");
	while ((currentChar = fgetc(first)) != EOF)
	{
		if (currentChar == ';')
			numClasses++;
	}
	fclose(first);

	FILE *in = fopen("classes.txt", "r");

	while (1 == 1)
	{
		if (fscanf(in, "%c", &currentChar) == EOF)
			break;

		while (currentChar != ',')
		{
			char charToString[2] = {currentChar, '\0'};
			strcat(currentWord, charToString);
			currentWordLength++;
			fscanf(in, "%c", &currentChar);
		}
		strcpy(courseArray[classCounter].name, currentWord);
		//printf("Added \"%s\"\n", currentWord);
		//break;
		//fscanf(in, " %c", &currentChar); // gets rid of the comma
		fscanf(in, " %d", &courseArray[classCounter].credits);
		//break;
		fscanf(in, " %c", &currentChar); // gets rid of the comma
		fscanf(in, " %c", &currentChar); // gets rid of the comma

		strcpy(currentWord, "");
		while (currentChar != ';')
		{
			char charToString[2] = {currentChar, '\0'};
			strcat(currentWord, charToString);
			currentWordLength++;
			fscanf(in, " %c", &currentChar);
		}
		strcpy(courseArray[classCounter].letterGrade, currentWord);
		strcpy(currentWord, "");
		
		printf("%s | %1d | %-2s |", courseArray[classCounter].name, courseArray[classCounter].credits, courseArray[classCounter].letterGrade);

		classCounter++;
	}
	printf("\n");

	for (int i = 0; i < numClasses; i++)
	{
		if (strcmp(courseArray[i].letterGrade, "S") == 0 || strcmp(courseArray[i].letterGrade, "U") == 0 )
			continue;
		/*sumCredits += courseArray[i].credits;
		sumGrades += letterGradeToDoubleValue(courseArray[i].letterGrade);*/

		sum += letterGradeToDoubleValue(courseArray[i].letterGrade) * courseArray[i].credits;
		sumCredits += courseArray[i].credits;
		numABC++;
	}

	printf("\n");
	printf("Total classes taken: %d\n", numClasses);
	printf("Total classes using letter grading: %d (S/U classes are not used for GPA calculation)\n", numABC);
	printf("Total credits attempted: %f\n", sumCredits);
	printf("Total credits earned: %f\n", sum);
	printf("You have a %f%% \"grade\" overall, which is a GPA of ", (sum/sumCredits)*100);

	printf("%f\n", (4 * sum)/sumCredits);
	printf("\n");
	printf("Press enter to exit...");

	char *pressKeyToExit;
	scanf("%c", pressKeyToExit);
}

double letterGradeToDoubleValue(char grade[3])
{
	if (strcmp(grade, "A") == 0)
		return 1.0;
	if (strcmp(grade, "A-") == 0)
		return 0.9375;
	if (strcmp(grade, "B+") == 0)
		return 0.8125;
	if (strcmp(grade, "B") == 0)
		return 0.75;
	if (strcmp(grade, "B-") == 0)
		return 0.6875;
	if (strcmp(grade, "C+") == 0)
		return 0.5625;
	if (strcmp(grade, "C") == 0)
		return 0.5;
	if (strcmp(grade, "C-") == 0)
		return 0.4375;
	if (strcmp(grade, "D+") == 0)
		return 0.3125;
	if (strcmp(grade, "D") == 0)
		return 0.25;
	if (strcmp(grade, "D-") == 0)
		return 0.1875;
	if (strcmp(grade, "F") == 0)
		return 0.0;


}