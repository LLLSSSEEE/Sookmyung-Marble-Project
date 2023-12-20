//
//  main.c
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/20.
//



#include <time.h>
#include <string.h>
#include "SMM_object.h"
#include "SMM_database.h"
#include "SMM_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"

#define MAX_NODE    100



//------------------------------------------------------------------------------
//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;



typedef struct player {
        int energy;
        int position;
        char name[MAX_CHARNAME];
        int accumCredit;
        int flag_graduate;
} player_t;

static player_t *cur_player; //포인터로 선언 
//static player_t cur_player[MAX_PLAYER];


#if 0
static int player_energy[MAX_PLAYER]; //일단 100개짜리로 잡기. 
static int player_position[MAX_PLAYER];
static int player_name[MAX_PLAYER][MAX_CHARNAMES];
#endif


//------------------------------------------------------------------------------
//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player
//void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif


//------------------------------------------------------------------------------
//
void printGrades(int player)
{
     int i;
     void *gradePtr;
     for (i=0; i<smmdb_len(LISTNO_OFFSET_GRADE + player); i++)
     {
         gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
         printf("%s : %i\n", smmObj_getNodeName(gradePtr), smmObj_getNodeGrade(gradePtr));
     }
}    


//------------------------------------------------------------------------------
//
void printPlayerStatus(void)
{
     int i;
     
     for (i=0; i<player_nr; i++)
     {
         printf("%s : credit %i, energy %i, position %i\n",
                      cur_player[i].name,
                      cur_player[i].accumCredit,
                      cur_player[i].energy,
                      cur_player[i].position);
     }
}

//------------------------------------------------------------------------------
//
void generatePlayers(int n, int initEnergy) //generate a new player
{
     int i;
     //n time loop
     
     //printf("cur_player : "); //뭐지############# 교수님 1.12 수업하다가 놓침. 
     
     for (i=0;i<n;i++)
     {
         //input name
         printf("Input player %i's name:", i); //¾E³≫ ¹®±¸ 
         scanf("%s", cur_player[i].name);
         fflush(stdin);
         
         //printf("input done\n : "): //12.12 #######
         
         //set position
         //player_position[i] = 0;
         cur_player[i].energy = 0;
         
         //set energy
         //player_energy[i] = initEnergy;
         cur_player[i].energy = initEnergy;
         cur_player[i].accumCredit = 0;
         cur_player[i].flag_graduate = 0;
         
         prinf("player input done\n"); //12.12#######
     }
}


//------------------------------------------------------------------------------
//
int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    

#if 0
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}


//action code when a player stays at a node
void actionNode(int player)
{
    void *boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position );
    //int type = smmObj_getNodeType(cur_player[player].position); //잠깐 주석 처리 
    int type = smmObj_getNodeType(boardPtr); 
    char *name = smmObj_getNodeName(boardPtr);
    void *gradePtr;
     
    switch(type)
    {
        //case lecture:
        case SMMNODE_TYPE_LECTURE:  
             if
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr); //cur_player[player].position
             cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr); //cur_player[player].position
             
             //garde generation 
             gradePtr = smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr), 0, rand()%9);//#######
             smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
             
             break;
             
        default:
            break;
    }
}

void goForward(int player, int step)
{
     void *boardPtr;
     cur_player[player].position += step;
     
     boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
     
     printf("%s go to node %i (name : %s)\n",
             cur_player[player].name, cur_player[player].position,
             smmObj_getNodeName(boardPtr)); //cur_player[player].position
}


//#endif


//------------------------------------------------------------------------------
//
int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy; 
    int turn = 0;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy)==4 ) //read a node parameter set
    {
        //store the parameter set
        //(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
        void *boardObj = smmObj_genObject(name, smmObjType_board, type, credit, energy, 0); //genNode->genObject //void로 저장. 
        smmdb_addTail(LISTNO_NODE, boardObj); //(list_nr, void* obj)
        
        if(type == SMMNODE_TYPE_HOME)
           initEnergy = energy;
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    
    for (i = 0; i<board_nr; i++)
    {
        void *boardObj = smmdb_getData(LISTNO_NODE, i);
        printf("node %i : %s, %i(%s), credit %i, energy %i\n", 
            i, smmObj_getNodeName(boardObj), 
            smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)), 
            smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    }
    //printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));    
    
    #if 0
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while () //read a food parameter set
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while () //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    #endif
    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf("input player no. :");
        scanf("%d", &player_nr);
        fflush(stdin); 
    }
    while (player_nr < 0 || player_nr > MAX_PLAYER);
    
    //do while 전에는 메모리 할당이 안되니까 여기서 malloc 하면 됨.
    
    cur_player = (player_t*)malloc(player_nr*sizeof(player_t));
    //cur_player = actionNode(player_t*)malloc(player_nr*sizeof(player_nr)); 
    generatePlayers(player_nr, initEnergy);
    
    //#if 0
    
    
    
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated? .1넣으면 무한 반복 
    {
        int die_result;
        
        
        //4-1. initial printing
        printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        die_result = rolldie(turn);
        
        
        //4-3. go forward
        goForward(turn, die_result);

		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        //4-5. next turn
        turn = (turn +1)%player_nr; //교수님꺼 뒷부분 없던데 뭐지. 
    }
    //#endif
  
  free(cur_player);
  system("PAUSE");	
  return 0;
}
