#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "roulette.h"

int main(void){
	List *gameHEAD = (List*)malloc(sizeof(List));
	deadHEAD *deadHead = (deadHEAD*)malloc(sizeof(deadHEAD));
	memberNODE *pPre;	// pPre
	memberNODE *pLoc;	// pLoc
	deadList *pDeadLoc;
	gameHEAD->head = NULL;
	gameHEAD->rear = NULL;
	gameHEAD->count= 0;		
	deadHead->head = NULL;
	deadHead->rear = NULL;
	pLoc=gameHEAD->head;
	pDeadLoc=deadHead->head;	// head 선언과 초기화

	initialize_Roulette(gameHEAD);
	
	start_Roulette(gameHEAD,deadHead,&pLoc,&pPre);
	
	show_me_the_score(deadHead, pDeadLoc);
	
	free_all(deadHead, pDeadLoc);
	free(gameHEAD);
	free(deadHead);				// free all nodes
	
	system("pause");
	return 0;
}

void createGamers(List* gameHEAD, char* inputName){
	memberNODE *newGamer= (memberNODE*)malloc(sizeof(memberNODE));
	strcpy(newGamer->name, inputName);
		if((gameHEAD)->head==NULL && (gameHEAD)->rear==NULL) {
			// 노드를 처음 생성하는 경우
			gameHEAD->head = newGamer;
			gameHEAD->rear = newGamer;
			newGamer->right= newGamer;
			gameHEAD->count++;
		} else { 
			//노드가 이미 하나이상 생성되어 있는 경우
			gameHEAD->rear->right=newGamer;
			newGamer->right=gameHEAD->head;
			gameHEAD->rear=newGamer;
			gameHEAD->count++;
		}
	return;
}

void initialize_Roulette(List* gameHEAD){
	char inputName[10];
	FILE *fstudent;
	fstudent = fopen("student.txt","r");

	while(!feof(fstudent)){
		fscanf_s(fstudent, "%s", inputName,sizeof(inputName));
		createGamers(gameHEAD, inputName);
	}
	fclose(fstudent);
	return;
}

void deadStudent(deadHEAD* deadHead, int deadNum, int randomNum, char* name){
	deadList *deadStudent = (deadList*)malloc(sizeof(deadList));
	deadList *pLoc;
	if((deadHead)->head==NULL) {
		(deadHead)->head=deadStudent;
		(deadHead)->rear=deadStudent;
	}
	deadStudent->bulletNum = randomNum;
	deadStudent->deadNum = deadNum;
	strcpy(deadStudent->name,name);
	deadStudent->next=NULL;

	pLoc=deadHead->rear;
	pLoc->next=deadStudent;
	deadHead->rear=deadStudent;

	return;
}

void start_Roulette(List* gameHEAD, deadHEAD* deadHead, memberNODE** ppLoc, memberNODE** ppPre){
	int deadNum=1;		// 몇번째 게임에서 죽었는가?
	int randomNum;		// 난수생성 변수, 즉 몇번째 총알에서 죽었는가?
	int i;				// 반복문 변수
	int leftGamers;		// 남은 학생 수
	char name[10];
	leftGamers=gameHEAD->count;
	(*ppLoc)=gameHEAD->head;

	while(leftGamers>0){

		srand(time(NULL));
		randomNum=rand()%leftGamers+1;	// 랜덤 총알 장전 (1~n)
		for(i=1;i!=randomNum;i++){
			(*ppPre)=(*ppLoc);
			(*ppLoc)=(*ppLoc)->right;
		} // ppLoc 에 있는 사람이 사망
		strcpy(name,(*ppLoc)->name);	// 문자열은 반드시 strcpy 사용

		(*ppPre)->right=(*ppLoc)->right;
		if((*ppLoc)==gameHEAD->head){		// 만약 맨앞을 free 하면
			gameHEAD->head=gameHEAD->head->right;
			free((*ppLoc));
		} else free((*ppLoc));				// free 해준다, student 사망
		(*ppLoc)=(*ppPre)->right;	
		gameHEAD->count--;
		leftGamers--;
		
		deadStudent(deadHead, deadNum,randomNum, name);	// linked list 생성
		
		deadNum++;
		
	}

	return;

}

void show_me_the_score(deadHEAD* deadHead, deadList* pDeadLoc){
	printf("Dead No.	Name.		bullet No.\n");
	pDeadLoc=deadHead->head;
	while(pDeadLoc!=NULL){
		printf("%d		%s		%d\n",pDeadLoc->deadNum,pDeadLoc->name,pDeadLoc->bulletNum);
		pDeadLoc=pDeadLoc->next;
	}printf("\n");

	return;
}

void free_all(deadHEAD* deadHead,deadList* pDeadLoc){
	pDeadLoc=deadHead->head;
	while(pDeadLoc!=NULL){
		deadList *ptr = pDeadLoc->next;
		free(pDeadLoc);
		pDeadLoc = ptr;
	}
	
	return;
}