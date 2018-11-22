# RussianRoulette
 student.txt 파일을 입력받아 랜덤으로 러시안 룰렛 게임을 실행하고 생존 순서를 커맨드라인으로 출력하는 프로그램입니다.   
 circular linked list 자료구조를 사용합니다.

## 들어가기 전에
 정상적인 프로젝트 실행을 위해서는 프로젝트 파일 또는 .exe 파일과 동일한 위치에 student.txt 파일이 있어야 합니다.  
   
## main 함수
```
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
```
  head 선언 후 초기화 하는 부분이 처음 실행됩니다.  
  initializ_Roulette 함수에서 student.txt 파일을 읽어오고 circular list로 구현합니다.  
  <br />
  start_Roulette 함수에서 학생 수만큼 러시안 룰렛 게임을 실행합니다.  
  <br />
  show_me_the_score 함수에서 결과를 cmd창에 출력합니다.
  <br />
  종료 후 모든 nodes를 free합니다.
 
## initialize_Roulette 함수
```
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
```
 프로젝트 파일과 동일한 위치에 있느 student.txt 파일을 읽어옵니다.  
 student.txt 파일은 게임에 참가하는 모든 학생들의 이름이 적혀있는 텍스트 파일입니다.  
 <br />
 파일의 끝이 될 때 까지 한 줄씩 student.txt 파일의 이름을 읽어옵니다.  
 읽어온 학생의 이름을 인자로 넘기며 게이머들의 목록을 circular list 형태로 만드는 createGamers 함수를 호출합니다.  
 
## createGamers 함수
```
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
```
 Circular linked list의 헤드노드 포인터, 이름을 인자로 입력받아 게이머 목록을 생성합니다.  
 head와 rear의 사용을 위해 첫번째 노드를 생성할 때와 그 이후 새 노드를 생성할 때를 구분합니다.  
 
## start_Roulette 함수
```
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
```
 리볼버의 탄창 크기는 남은 게이머의 숫자와 동일합니다. (게이머가 6명 남았다면 탄창의 최대크기 또한 6개)  
 random seed를 통해 탄창에 랜덤으로 총알 한발을 장전합니다.  
 만약 4번째 탄창에 총알이 있다면 4번째 게이머가 사망할 것입니다.  
 <br />
 죽은 게이머는 circular list에서 제외합니다.  
 죽은 게이머의 이름과 탄창 번호(4번째 탄창에 맞았으므로, 이 경우 탄창번호는 4)를 인자로 넘겨  
 죽은 게이머의 순서를 linked list로 만드는 deadStudent 함수를 호출합니다.  
 <br />
 이 함수는 남은 게이머가 1명도 없을 때 까지 반복해서 실행합니다.  
 
## deadStudent 함수
```
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
```
 죽은 게이머의 정보를 받아와 죽은 순서대로 linked list를 구현합니다.  
 
## show_me_the_score 함수
```
void show_me_the_score(deadHEAD* deadHead, deadList* pDeadLoc){
	printf("Dead No.	Name.		bullet No.\n");
	pDeadLoc=deadHead->head;
	while(pDeadLoc!=NULL){
		printf("%d		%s		%d\n",pDeadLoc->deadNum,pDeadLoc->name,pDeadLoc->bulletNum);
		pDeadLoc=pDeadLoc->next;
	}printf("\n");

	return;
}
```
죽은 게이머들의 linked list를 첫번째 노드부터 마지막 노드까지 순차적으로 출력합니다.  


## 실행 화면
 ![roulette_results](https://user-images.githubusercontent.com/41851641/48904321-4f288100-eea1-11e8-8b33-1cbfadaeab78.PNG)
  
  이 결과 화면을 기준으로,  
  임가온  4번째 러시안룰렛 게임에서 4번째 리볼버 탄창을 맞고 사망했습니다.  
  
