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
	pDeadLoc=deadHead->head;	// head ����� �ʱ�ȭ

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
			// ��带 ó�� �����ϴ� ���
			gameHEAD->head = newGamer;
			gameHEAD->rear = newGamer;
			newGamer->right= newGamer;
			gameHEAD->count++;
		} else { 
			//��尡 �̹� �ϳ��̻� �����Ǿ� �ִ� ���
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
	int deadNum=1;		// ���° ���ӿ��� �׾��°�?
	int randomNum;		// �������� ����, �� ���° �Ѿ˿��� �׾��°�?
	int i;				// �ݺ��� ����
	int leftGamers;		// ���� �л� ��
	char name[10];
	leftGamers=gameHEAD->count;
	(*ppLoc)=gameHEAD->head;

	while(leftGamers>0){

		srand(time(NULL));
		randomNum=rand()%leftGamers+1;	// ���� �Ѿ� ���� (1~n)
		for(i=1;i!=randomNum;i++){
			(*ppPre)=(*ppLoc);
			(*ppLoc)=(*ppLoc)->right;
		} // ppLoc �� �ִ� ����� ���
		strcpy(name,(*ppLoc)->name);	// ���ڿ��� �ݵ�� strcpy ���

		(*ppPre)->right=(*ppLoc)->right;
		if((*ppLoc)==gameHEAD->head){		// ���� �Ǿ��� free �ϸ�
			gameHEAD->head=gameHEAD->head->right;
			free((*ppLoc));
		} else free((*ppLoc));				// free ���ش�, student ���
		(*ppLoc)=(*ppPre)->right;	
		gameHEAD->count--;
		leftGamers--;
		
		deadStudent(deadHead, deadNum,randomNum, name);	// linked list ����
		
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