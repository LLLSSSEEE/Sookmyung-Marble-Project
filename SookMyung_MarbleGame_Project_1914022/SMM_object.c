//
//  SMM_node.c
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/07.
//

#include "SMM_common.h"
#include "SMM_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "강의",
       "식당",
       "실험실",
       "집",
       "실험실로이동",
       "음식찬스",
       "축제시간"
};

char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}

typedef enum smmObjType{ //enum 정의 
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
} smmObjType_e; //.h로 옮겨야 한다.  
        
typedef enum smmObjGrade{ //enum 정의 
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
        
        
//1. 구조체 형식 정의
typedef struct smmObject {
        char name[MAX_CHARNAME];
        smmObjType_e objType; //enum 새롭게. (위에서 정의해줘야 함) 
        int type;
        int credit;
        int energy;
        smmObjGrade_e grade; //성적을 가지고 있어야 하니까. 성적을 enum으로 정의. 
} smmObject_t;



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
void smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade) //node->Object 로 이름 변경 
{

    smmObject_t*ptr;
    
    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
    
    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;
    
    smmObj_noNode++;    
}



//3. 관련 함수 변경 
char* smmObj_getNodeName(void* obj) //void 포인터 
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->name; 
    //return smm_node[node_nr].name;
}

//3. 관련 함수 변경 
int smmObj_getNodeType(int node_nr)
{
     return smm_node[node_nr].type;
}

int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit;
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}


