# RussianRoulette  
 student.txt 파일을 입력받아 랜덤으로 러시안 룰렛 게임을 실행하고  
 생존 순서를 cmd로 출력하는 프로그램입니다.  
 <br />
 circular linked list 자료구조를 사용합니다.

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
 
 ## 
