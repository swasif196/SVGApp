//Sohaib Wasif
//0874921

#ifndef HELPER_H
#define HELPER_H

#include "SVGParser.h"
#include <math.h>

Group* createGroup(xmlNode * node);
void deleteGroups(List * groups);
List* getGRects(List * groups);
List* getGCircles(List * groups);
List* getGPaths(List * groups);
List* getGGroups(List * groups);
int getGAttNum(List * gr);
xmlDocPtr createXmlDoc(SVGimage* img);
xmlNodePtr gNode(Group * g);
bool validateImage(SVGimage * img);
bool validateRects(List * rects);
bool validateCircles(List * circles);
bool validatePaths(List * paths);
bool validateGroups(List * groups);
bool validateAtts(List * atts);
int isValid(char file[256]);
int getNumRects(char file[256]);
int getNumCircs(char file[256]);
int getNumPaths(char file[256]);
int getNumGroups(char file[256]);
char * getTitle(char file[256]);
char * getDesc(char file[256]);
char * getAllRects(char file[256]);
char * getAllCircs(char file[256]);
char * getAllPaths(char file[256]);
char * getAllGroups(char file[256]);
char * getAllAtts(char file[256], char val[32]);
int editAtts(char file[256], char val[32], char nameA[1048], char valA [1048]);
int editTitle(char file[256], char val[256]);
int editDesc(char file[256], char val[256]);
int addRect(char file[256], char val[1024]);
int addCirc(char file[256], char val[1024]);
int addPath(char file[256], char val[1024]);
int createSvg(char file[256]);
int scaleRect(char file[256], float ratio);
int scaleCirc(char file[256], float ratio);

#define PI 3.141592653

#endif