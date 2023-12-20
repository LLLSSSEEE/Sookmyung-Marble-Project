//
//  SMM_node.c
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/20.
//

#include "SMM_common.h"
#include "SMM_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "����",
       "�Ĵ�",
       "�����",
       "��",
       "����Ƿ��̵�",
       "��������",
       "�����ð�"
};


/*char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}*/


/*typedef enum smmObjType{ //enum ���� 
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
} smmObjType_e; //.h�� �Űܾ� �Ѵ�.  
*/
        
/*typedef enum smmObjGrade{ //enum ���� 
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
//object.h �� �̵�        
        
//1. ����ü ���� ����
typedef struct smmObject {
        char name[MAX_CHARNAME];
        smmObjType_e objType; //enum ���Ӱ�. (������ ��������� ��) 
        int type;
        int credit;
        int energy;
        smmObjGrade_e grade; //������ ������ �־�� �ϴϱ�. ������ enum���� ����. 
} smmObject_t;



//2. ����ü �迭 ���� ����

//static smmObject_t smm_node[MAX_NODE]; //���� �迭 �ʿ� ������. 
//static int smmObj_noNode = 0; 



//����ü�� �����Ͽ� �ʿ� ������. 
/*
#if 0 
static char smmObj_name[MAX_NODE][MAX_CHARNAME];
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];

#endif
static int smmObj_noNode=0;
*/  


//3. ���� �Լ� ����
//object generation
void smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade) //node->Object �� �̸� ���� 
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



//3. ���� �Լ� ���� 

char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}


char* smmObj_getNodeName(void* obj) //void ������ 
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->name; 
    //return smm_node[node_nr].name;
}

//3. ���� �Լ� ���� 
int smmObj_getNodeType(int* type /*���� node_nr*/)
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

int smmObj_getNodeEnergy(int energy)
{
    smmObject_t* ptr = (smmObject_t*)energy;
    
    return ptr -> energy;
    //return smm_node[node_nr].energy;
}

int smmObj_getNodeGrade(int grade)
{
    smmObject_t* ptr = (smmObject_t*) grade;
    
    return ptr -> grade; 
}

