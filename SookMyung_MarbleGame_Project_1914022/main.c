//
//  main.c
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/21 - final
//



#include <time.h>
#include <string.h>
#include "SMM_object.h"
#include "SMM_database.h"
#include "SMM_common.h"

#define BOARDFILEPATH "C:/Users/dltld/OneDrive/2023전프기/Sookmyung-Marble-Project/SookMyung_MarbleGame_Project_1914022/marbleBoardConfig.txt"
#define FOODFILEPATH "C:/Users/dltld/OneDrive/2023전프기/Sookmyung-Marble-Project/SookMyung_MarbleGame_Project_1914022/marbleFoodConfig.txt"
#define FESTFILEPATH "C:/Users/dltld/OneDrive/2023전프기/Sookmyung-Marble-Project/SookMyung_MarbleGame_Project_1914022/marbleFestivalConfig.txt"

#define MAX_NODE    100



//------------------------------------------------------------------------------
//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;
static int player_nr;


//------------------------------------------------------------------------------
//구조체 선언 
typedef struct player 
{
        int energy;
        int position;
        int exe_lab; 
        char name[MAX_CHARNAME];
        int accumCredit;
        int flag_graduate;
} player_t;

static player_t *cur_player; //포인터로 선언 


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
//학생 평균 성적 계산
float calcAverageGrade(int player)
{
      float Average;
      
      return Average; 
}


//------------------------------------------------------------------------------
//졸업한 사람
int isGraduated(void)
{
    int i=0;
    if(cur_player[player_nr].accumCredit >= GRADUATE_CREDIT)
        i=1;
    
    return i;
}
    
 
//------------------------------------------------------------------------------
//학생당 학점 출력 함수 
void printGrades(int player)
{
     int i;
     void *gradePtr;
     
     for (i=0; i<smmdb_len(LISTNO_OFFSET_GRADE + player); i++)
     {
         gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
         printf("Your grade of %s : %i\n\n", smmObj_getNodeName(gradePtr), smmObj_getNodeGrade(gradePtr));
     }
}    


//------------------------------------------------------------------------------
// 플레이어 상태 출력 함수 
void printPlayerStatus(void)
{
     int i;
     
     for (i=0; i<player_nr; i++)
     {
         printf("\n%s : credit %i,  energy %i,  experiment %i,  position %i\n",
                      cur_player[i].name,
                      cur_player[i].accumCredit,
                      cur_player[i].energy,
                      cur_player[i].exe_lab,
                      cur_player[i].position);
     }
}

//------------------------------------------------------------------------------
// 플레이어 생성 함수 
void generatePlayers(int n, int initEnergy) //generate a new player
{
     int i;
     
     //n time loop 
     for (i=0; i<n; i++)
     {
         //input name
         printf("Input player %i's name:", i); //¾E³≫ ¹®±¸ 
         scanf("%s", cur_player[i].name);
         fflush(stdin);
         
         //set position
         cur_player[i].position = 0;
         //cur_player[i].energy = 0;
         
         //set energy
         //player_energy[i] = initEnergy;
         cur_player[i].energy = initEnergy;
         cur_player[i].accumCredit = 0;
         cur_player[i].flag_graduate = 0;
         cur_player[i].exe_lab = 0;
         
         printf("player input done\n"); //12.12#######
     }
}


//------------------------------------------------------------------------------
//주사위 굴리기 
int rolldie(int player)
{
    char c;
    printf("\nPress any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    

#if 1
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
    int success=0;
    char *name = smmObj_getNodeName(boardPtr);
    void *gradePtr;
     
    switch(type)
    {
        //case lecture:
        case SMMNODE_TYPE_LECTURE:  //수업 - 에너지  소모 + 성적 
             printf("\nIt's time to STUDY (%i)\n", smmObj_getNodeEnergy(boardPtr));
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr); //cur_player[player].position
             cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr); //cur_player[player].position
             
             //garde generation 
             gradePtr = smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr), 0, rand()%9);
             smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
     
             break;
        
        
        //case restaurant:
        case SMMNODE_TYPE_RESTAURANT: //레스토랑 - 에너지 보충 
             printf("\nYou are at the restaurant now! You can get energy %i\n", smmObj_getNodeEnergy(boardPtr));
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
             cur_player[player].energy += smmObj_getNodeEnergy(boardPtr);
             smmdb_addTail(LISTNO_NODE + player, boardPtr);
             
             break;
        
             
        //case laboratory:
        case SMMNODE_TYPE_LABORATORY: //실험실 -  
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
             if(cur_player[player].exe_lab == 1)
             {
                  int roll;
                  roll = rolldie(player);
                  if(roll >= success)
                  {
                          cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr);
                          printf("\nSuccess!\n");
                          cur_player[player].exe_lab = 0;
                  }
                  else
                  {
                      printf("\nFail!\n");
                  }
             }
             smmdb_addTail(LISTNO_NODE + player, boardPtr);
            
             break;
       
                  
        //case home:     
        case SMMNODE_TYPE_HOME: //집 - 지나칠 때 에너지 보충 
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
             cur_player[player].energy += smmObj_getNodeEnergy(boardPtr);
             smmdb_addTail(LISTNO_NODE + player, boardPtr);
             
             break;
             
        
        //case gotolab:     
        case SMMNODE_TYPE_GOTOLAB: //실험실로이동 
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
             cur_player[player].position = 8;
             cur_player[player].exe_lab = 1;
             success = rand()%MAX_DIE + 1;
             
             smmdb_addTail(LISTNO_NODE + player, boardPtr);    
             
             break;
         
         
         //case foodchance: 
         case SMMNODE_TYPE_FOODCHANCE:
              printf("\nThis is Food Chance Time! Press any key~!\n"); 
              char c = getchar();
              fflush(stdin);
              cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
              cur_player[player].energy += smmObj_getNodeEnergy(smmdb_getData(LISTNO_FOODCARD, rand()%food_nr));
              smmdb_addTail(LISTNO_NODE + player, boardPtr);
              
              break; 
        
             
        // case festival:     
        case SMMNODE_TYPE_FESTIVAL:
             cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
             rolldie(player);
             printf("%s\n\n", smmObj_getNodeName(smmdb_getData(LISTNO_FESTCARD, rand()%MAX_DIE)));
             smmdb_addTail(LISTNO_FESTCARD + player, boardPtr);
             
             break;
            
             
                  
        default:
            break;
    }
}

void goForward(int player, int step)
{
     void *boardPtr;
     cur_player[player].position += step;
     if(cur_player[player].position > 15)
         cur_player[player].position = cur_player[player].position%16;

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
    int initEnergy = 0;
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
    
    //게임시작 
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //read a node parameter set
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
    printf("\n<<<<< Total number of board nodes : %i >>>>>\n", board_nr);
    
    
    for (i = 0; i<board_nr; i++)
    {
        void *boardObj = smmdb_getData(LISTNO_NODE, i);
        printf("node %i : %s, %i(%s), credit %i, energy %i\n", 
            i, smmObj_getNodeName(boardObj), 
            smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)), 
            smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    }
    //printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));    
    
    
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");

    while (fscanf(fp, "%s %i", &name, &energy ) == 2 ) //read a food parameter set
    {
        //store the parameter set
        void *boardObj = smmObj_genObject(name, smmObjType_card, type, credit, energy, 0);
        //genObject(name, smmObjType_board, type, credit, energy+food_nr, 0);
        smmdb_addTail(LISTNO_FOODCARD, boardObj);
        food_nr++;
        
        //if(type == SMMNODE_TYPE_HOME)
            //initEnergy = energy;
        
                
    }
    fclose(fp);
    printf("<<<<< Total number of food cards : %i >>>>>\n", food_nr);
    
    for(i=0; i<food_nr; i++)
    {
        void *boardObj = smmdb_getData(LISTNO_FOODCARD, i);
        printf("%s : %i\n", smmObj_getNodeName(boardObj), smmObj_getNodeEnergy(boardObj));
    }
    
    
    /*3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s",name)==1) //read a festival card string
    {
          void *boardObj = smmObj_genObject(name, smmObjType_card, type, credit, energy, 0);
          smmdb_addTail(LISTNO_FESTCARD, boardObj);
          festival_nr ++;
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    
    for(i=0; i<festival_nr; i++)
    {
        void *boardObj = smmdb_getData(LISTNO_FESTCARD, i);
        printf("%s\n", smmObj_getNodeName(boardObj));
    }
    */
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf(" Input player number :");
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
  
  return 0;
}
