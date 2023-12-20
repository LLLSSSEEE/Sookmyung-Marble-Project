//
//  SMM_object.h
//  SookMyung_MarbleGame
//
//  Created by Sieun Lee on 2023/12/20-(4)
//

#ifndef SMM_object_h
#define SMM_object_h

#define SMMNODE_TYPE_LECTURE            0
#define SMMNODE_TYPE_RESTAURANT         1
#define SMMNODE_TYPE_LABORATORY         2
#define SMMNODE_TYPE_HOME               3
#define SMMNODE_TYPE_GOTOLAB            4
#define SMMNODE_TYPE_FOODCHANCE         5
#define SMMNODE_TYPE_FESTIVAL           6

#define SMMNODE_TYPE_MAX                7


typedef enum smmObjType {
        smmObjType_board = 0,
        smmObjType_card,
        smmObjType_grade
        } smmObjType_e;

typedef enum smmObjGrade{ //enum ���� 
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

/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/



//object generation
//void smmObj_genNode(char* name, int type, int credit, int energy);
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade);

//member retrieving
char* smmObj_getNodeName(void* obj);
int smmObj_getNodeType(int* type);
int smmObj_getNodeCredit(int* credit);
int smmObj_getNodeEnergy(int* energy);
int smmObj_getNodeGrade(int* grade);

//element to string
char* smmObj_getTypeName(int type);


#endif /* SMM_object_h */
