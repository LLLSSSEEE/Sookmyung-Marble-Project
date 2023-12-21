//
//  SMM_node.c
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/21 - final
//

#include "SMM_common.h"
#include "SMM_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "lecture",
       "restaurant",
       "laboratory",
       "home",
       "gotoLab",
       "foodChance",
       "festival"
};

static char smmFoodCard [14][MAX_CHARNAME] =
{
       "chicken",   
       "beer",        
       "tanghulu",   
       "ramen",       
       "gamjatang",   
       "cupbab",     
       "jajangmyeon", 
       "schoolfood",  
       "pasta",       
       "pizza",      
       "hamburger",   
       "sandwich",   
       "yogurt",     
       "bibimbap"   
};

static char smmFestival[][MAX_CHARNAME] =
{
       "Let's_sing_a song",
       "Please_say_something_about_your_goals_after_graduation",
       "What_do_you_want_to_do_when_you_get_home_today?",
       "Please_tell_us_how_you_feel_about_the_programming_class",
       "Please_introduce_a_good_restaurant_in_your_neighborhood"
};

/*char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}*/


/*typedef enum smmObjType{ //enum 정의 
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
} smmObjType_e; //.h로 옮겨야 한다.  
*/
        
/*typedef enum smmObjGrade{ //enum 정의 
        smmObjGrade_Ap = 0;
        smmObjGrade_A0,
        smmObjGrade_Am,
        smmObjGrade_Bp,
        smmObjGrade_B0,
        smmObjGrade_Bm,
        smmObjGrade_Cp,
        smmObjGrade_C0,
        smmObjGrade_Cm,
} smmObjGrade_e;        
*/
//object.h 로 이동        

/*typedef enum smmObjType {
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
        } smmObjType_e;
*/
        
/*
typedef enum smmFood {
        chicken     = 0,
        beer        = 1,
        tanghulu    = 2,
        ramen       = 3,
        gamjatang   = 4,
        cupbab      = 5,
        jajangmyeon = 6,
        schoolfood  = 7,
        pasta       = 8,
        pizza       = 9,
        hamburger   = 10, 
        sandwich    = 11,
        yogurt      = 12,
        bibimbap    = 13
        } smmFood_e; 
        
typedef enum smmObjGrade{ //enum 정의 
        smmObjGrade_Ap = 0,
        smmObjGrade_A0 = 1,
        smmObjGrade_Am = 2,
        smmObjGrade_Bp = 3,
        smmObjGrade_B0 = 4,
        smmObjGrade_Bm = 5,
        smmObjGrade_Cp = 6,
        smmObjGrade_C0 = 7,
        smmObjGrade_Cm = 8
} smmObjGrade_e;   
*/
        
//1. 구조체 형식 정의
typedef struct smmObject {
        char name[MAX_CHARNAME];
        smmObjType_e objType; //enum 새롭게. (위에서 정의해줘야 함) 
        int type;
        int credit;
        int energy;
        smmObjGrade_e grade; //성적을 가지고 있어야 하니까. 성적을 enum으로 정의. 
} smmObject_t;

      
typedef struct smmFestival {
        char fes[4][MAX_CHARNAME];
        /*char fes1[MAX_CHARNAME];
        char fes2[MAX_CHARNAME];
        char fes3[MAX_CHARNAME];
        char fes4[MAX_CHARNAME];
        char fes5[MAX_CHARNAME]; */
} smmFestival_name;

//2. 구조체 배열 변수 정의

//static smmObject_t smm_node[MAX_NODE]; //이제 배열 필요 없어짐. 
//static int smmObj_noNode = 0; 



//구조체로 선언하여 필요 없어짐. 
/*
#if 0 
static char smmObj_name[MAX_NODE][MAX_CHARNAME];
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];

#endif
static int smmObj_noNode=0;
*/  


//3. 관련 함수 변경
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade) //node->Object 로 이름 변경 
{

    smmObject_t*ptr;
    
    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
    
    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;
    
    return ptr;
    //smmObj_noNode++;    
}



//3. 관련 함수 변경 

char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}


char* smmObj_getNodeName(void* obj) //void 포인터 
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->name; 
    //return smm_node[node_nr].name;
}

//3. 관련 함수 변경 
int smmObj_getNodeType(int* type /*원래 node_nr*/)
{
     smmObject_t* ptr = (smmObject_t*)type;
     
     return ptr->objType;
     //return smm_node[node_nr].type;
}

 
int smmObj_getNodeCredit(int* credit)
{
    smmObject_t* ptr = (smmObject_t*)credit;
    
    return ptr -> credit;
    //return smm_node[node_nr].credit;
}

int smmObj_getNodeEnergy(int* energy)
{
    smmObject_t* ptr = (smmObject_t*)energy;
    
    return ptr -> energy;
    //return smm_node[node_nr].energy;
}

int smmObj_getNodeGrade(int* grade)
{
    smmObject_t* ptr = (smmObject_t*) grade;
    
    return ptr -> grade; 
}

/*
int smmObj_getFoodChance(int* energy)
{
      
    return energy;
} 
*/
