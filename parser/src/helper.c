#include "helper.h"

int isValid(char file[256])
{
    //printf("%s\n", file);
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    if(img == NULL){
        return 0;
    }
    deleteSVGimage(img);
    return 1;
}

int getNumRects(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    List * a = getRects(img);
    int x = a->length;
    deleteSVGimage(img);
    //free(a);
    return x;
}

int getNumCircs(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    List * a = getCircles(img);
    int x = a->length;
    deleteSVGimage(img);
    //free(a);
    return x;
}

int getNumPaths(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    List * a = getPaths(img);
    int x = a->length;
    deleteSVGimage(img);
    //free(a);
    return x;
}

int getNumGroups(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    List * a = getGroups(img);
    int x = a->length;
    deleteSVGimage(img);
    //free(a);
    return x;
}

char * getTitle(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char buff[256];
    buff[255] = '\0';
    strcpy(buff, img->title);
    deleteSVGimage(img);
    if(strcmp(buff, "") == 0){
        strcpy(buff, "NA");
    }
    char * ret = malloc(sizeof(char)*strlen(buff)+1);
    strcpy(ret, buff);
    return ret;
}

char * getDesc(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char buff[256];
    buff[255] = '\0';
    strcpy(buff, img->description);
    deleteSVGimage(img);
    if(strcmp(buff, "") == 0){
        strcpy(buff, "NA");
    }
    char * ret = malloc(sizeof(char)*strlen(buff)+1);
    strcpy(ret, buff);
    return ret;
}

char * getAllRects(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * ret = rectListToJSON(img->rectangles);
    deleteSVGimage(img);
    return ret;
}

char * getAllCircs(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * ret = circListToJSON(img->circles);
    deleteSVGimage(img);
    return ret;
}

char * getAllPaths(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * ret = pathListToJSON(img->paths);
    deleteSVGimage(img);
    return ret;
}

char * getAllGroups(char file[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * ret = groupListToJSON(img->groups);
    deleteSVGimage(img);
    return ret;
}

char * getAllAtts(char file[256], char val[32])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    
    char * c = malloc(sizeof(char)*2+1);
    strncpy(c, val, 2);
    int id = (int)(c[0]) - 48;
    int ind = (int)(c[1]) - 48;
    //printf("chk = %d, %d", id, ind);
    int cnt = 0;
    char * ret = NULL;
    List * a = NULL;
    if(id == 1){
        a = img->circles;
    }
    else if(id == 2){
        a = img->rectangles;
    }
    else if(id == 3){
        a = img->paths;
    }
    else{
        a = img->groups;
    }
    for(Node * n = a->head; n != NULL; n = n->next){
        if(cnt == ind){
            if(id == 1){
                Circle * c = (Circle*) n->data;
                ret = attrListToJSON(c->otherAttributes);
            }
            else if(id == 2){
                Rectangle * r = (Rectangle*) n->data;
                ret = attrListToJSON(r->otherAttributes);
            }
            else if(id == 3){
                Path * p = (Path*) n->data;
                ret = attrListToJSON(p->otherAttributes);
            }
            else if(id == 4){
                Group * g = (Group*) n->data;
                ret = attrListToJSON(g->otherAttributes);
            }
            break;
        }
        cnt++;
    }
    free(c);
    deleteSVGimage(img);
    if(ret == NULL){
        return "[]";
    }
    return ret;
}

int editAtts(char file[256], char val[32], char nameA[1048], char valA [1048])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * c = malloc(sizeof(char)*2+1);
    strncpy(c, val, 2);
    int id = (int)(c[0]) - 48;
    int ind = (int)(c[1]) - 48;
    Attribute * a = malloc(sizeof(Attribute));
    a->name = malloc(sizeof(char)*strlen(nameA)+1);
    strcpy(a->name, nameA);
    a->value = malloc(sizeof(char)*strlen(valA)+1);
    strcpy(a->value, valA);
    //printf("chk = %s, %s\n", a-)
    setAttribute(img, id, ind, a);
    
    bool ret = validateSVGimage(img, "parser/bin/svg.xsd");
    if(ret == true){
        ret = writeSVGimage(img, file);
    }
    if (ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int editTitle(char file[256], char val[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    img->title[255] = '\0';
    strncpy(img->title, val, 255);
    bool ret = writeSVGimage(img, file);
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int editDesc(char file[256], char val[256])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    img->description[255] = '\0';
    strncpy(img->description, val, 255);
    bool ret = writeSVGimage(img, file);
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int addRect(char file[256], char val[1024])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * json = malloc(sizeof(char)*strlen(val)+1);
    strcpy(json, val);
    //printf("chk = %s\n", json);
    Rectangle * r = JSONtoRect(json);
    //printf("chk = %f, %f, %f, %f, %s\n", r->x, r->y, r->width, r->height, r->units);
    addComponent(img, 2, (void*)r);
    bool ret = validateSVGimage(img, "parser/bin/svg.xsd");
    if(ret == true){
        ret = writeSVGimage(img, file);
    }
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int addCirc(char file[256], char val[1024])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char * json = malloc(sizeof(char)*strlen(val)+1);
    strcpy(json, val);
    //printf("chk = %s\n", json);
    Circle * c = JSONtoCircle(json);
    //printf("chk = %f, %f, %f, %f, %s\n", r->x, r->y, r->width, r->height, r->units);
    addComponent(img, 1, (void*)c);
    bool ret = validateSVGimage(img, "parser/bin/svg.xsd");
    if(ret == true){
        ret = writeSVGimage(img, file);
    }
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int addPath(char file[256], char val[1024])
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    char json [65];
    json [64] = '\0';
    strncpy(json, val, 64);
    //printf("chk = %s\n", json);
    Path * p = malloc(sizeof(Path));
    p->data = malloc(sizeof(char)*strlen(json)+1);
    strcpy(p->data, json);
    p->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    //printf("chk = %f, %f, %f, %f, %s\n", r->x, r->y, r->width, r->height, r->units);
    addComponent(img, 3, (void*)p);
    bool ret = validateSVGimage(img, "parser/bin/svg.xsd");
    if(ret == true){
        ret = writeSVGimage(img, file);
    }
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int scaleRect(char file[256], float ratio)
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    
    for(Node * n = (img->rectangles)->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        r->width *= ratio;
        r->height *= ratio;
    }
    bool ret = writeSVGimage(img, file);
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int scaleCirc(char file[256], float ratio)
{
    SVGimage * img = createValidSVGimage(file, "parser/bin/svg.xsd");
    
    for(Node * n = (img->circles)->head; n != NULL; n = n->next){
        Circle * c = (Circle*) n->data;
        c->r *= ratio;
    }
    bool ret = writeSVGimage(img, file);
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}

int createSvg(char file[256])
{
    int i = strlen(file);
    if(file[i-1] != 'g' && file[i-2] != 'v' && file[i-3] != 's' && file[i-4] != '.'){
        return 0;
    }
    SVGimage * img = malloc(sizeof(SVGimage));
	
    strcpy(img->namespace, "http://www.w3.org/2000/svg");
    strcpy(img->title, "");
    strcpy(img->description, "");
	img->rectangles = initializeList(rectangleToString,deleteRectangle,compareRectangles);
	img->circles = initializeList(circleToString,deleteCircle,compareCircles);
	img->paths = initializeList(pathToString,deletePath,comparePaths);
    img->groups = initializeList(groupToString,deleteGroup,compareGroups);
    img->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    bool ret = writeSVGimage(img, file);
    if(ret == true){
        deleteSVGimage(img);
        return 1;
    }
    deleteSVGimage(img);
    return 0;
}






























