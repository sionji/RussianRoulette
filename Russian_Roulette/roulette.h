typedef struct tmemberNODE{
	char name[10];
	struct tmemberNODE *right;
} memberNODE;

typedef struct {
	int count;
	memberNODE *head;
	memberNODE *rear;
} List;

typedef struct tdead{
	int deadNum;
	int bulletNum;
	char name[10];
	struct tdead *next;
} deadList;

typedef struct {
	deadList *head;
	deadList *rear;		// 편의를 위해 rear를 선언
} deadHEAD;

void createGamers(List*, char*);
void initialize_Roulette(List*);
void deadStudent(deadHEAD*, int , int , char* );
void start_Roulette(List*, deadHEAD*, memberNODE**, memberNODE**);
void show_me_the_score(deadHEAD* , deadList* );
void free_all(deadHEAD* , deadList*);