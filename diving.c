#include <stdio.h>
#define minScore 0.0
#define maxScore 10.0
#define minDegree 1.0
#define maxDegree 5.0
#define numOfJudges 8

void judgeScore(float result[]){
	float newnum;
	int i;

	for (i=0; i<numOfJudges; ++i){
		printf("enter score from judge %d: ", i+1);
		scanf("%f",&newnum);
		if (newnum>maxScore || newnum<minScore){
			printf("Error: scores must be between %.1f and %.1f.\n", minScore, maxScore);
			result[i]=0;
		}else{
			result[i]=newnum;
		}
	}
}

float findMax1(float result[]) {
	int i;
	int max1Index=0;
	float max1=minScore-1;

	for(i=1; i<numOfJudges; i++){
		if(result[i]>=max1){
			max1Index=i;
			max1=result[i];
		}
	}
	return max1Index;
}

float findMax2(float result[], int max1) {
	int i;
	int max2Index=0;
	float max2=result[0];

	for(i=1; i<numOfJudges; i++){
		if (result[i]>=max2 && i!=max1){
			max2Index=i;
			max2=result[i];
		}
	}
	return max2Index;
}

float findMin1(float result[], int max1, int max2) {
	int i;
	int min1Index=0;
	float min1=maxScore+1;

	for(i=1; i<numOfJudges; i++) {
		if (result[i]<=min1 && i!=max1 && i!=max2){
			min1Index=i;
			min1=result[i];
		}
	}
	return min1Index;
}

float findMin2(float result[], int min1, int max1, int max2) {
	int i;
	int min2Index=0;
	float min2=result[0];

	for(i=0; i<numOfJudges; i++) {
		if(result[i]<=min2 && i!=min1 && i!=max1 && i!=max2){
			min2Index=i;
			min2=result[i];
		}
	}
	return min2Index;
}

float finalScore(float result[], float degree, int max1, int max2, int min2, int min1) {
	int i;
	float scoreFinal=0;
	float scoreBeforeMultiplication=0;

	for(i=0; i<numOfJudges; i++){
		if(i!=max1 && i!=max2 && i!=min1 && i!=min2){
			scoreBeforeMultiplication=result[i]+scoreBeforeMultiplication;
		}
	}
	scoreFinal=degree*scoreBeforeMultiplication;
	return scoreFinal;
}

int main(void) {
	float degree, score;
	float result[numOfJudges];

	printf("degree of diving difficulty: ");
	scanf("%f", &degree);

	if (degree>maxDegree || degree<minDegree){
		printf("Error: degree must be between %.1f and %.1f.\n", minDegree, maxDegree);
		degree=0;
	}
	judgeScore(result);
	int max1=findMax1(result);
	int max2=findMax2(result,max1);
	int min1=findMin1(result,max1,max2);
	int min2=findMin2(result,min1,max1,max2);
	score=finalScore(result,degree,max1,max2,min2,min1);
	printf("Score for this dive is %.2f\n", score);
}
