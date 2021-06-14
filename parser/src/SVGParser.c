//Sohaib Wasif
//0874921

#include "helper.h"


char* attributeToString (void* toBePrinted)
{
	return (char*) toBePrinted;
}
char* groupToString( void* data)
{
	return (char*) data;
}
char* rectangleToString(void* data)
{
	return (char*) data;
}
char* circleToString(void* data)
{
	return (char*)data;
}
char* pathToString(void* data)
{
	return (char*) data;
}
int compareAttributes(const void *first, const void *second)
{
	return(strcmp((char*) first, (char*)second));
}
int compareGroups(const void *first, const void *second)
{
	return(strcmp((char*) first, (char*)second));
}
int compareRectangles(const void *first, const void *second)
{
	return(strcmp((char*) first, (char*)second));
}
int compareCircles(const void *first, const void *second)
{
	return(strcmp((char*) first, (char*)second));
}
int comparePaths(const void *first, const void *second)
{
	return(strcmp((char*) first, (char*)second));
}
void deleteAttribute( void* data)
{
	Attribute * d = (Attribute*)data;
	free(d->name);
	free(d->value);
	free(d);
	return;
}
void deleteGroup(void* data)
{
	Group * w = (Group*) data;
	free(w);
}

void deleteRectangle(void* data)
{
	Rectangle * r = (Rectangle*) data;
	free(r);
}
void deleteCircle(void* data)
{
	Circle * s = (Circle*) data;
	free(s);	
}
void deletePath(void* data)
{
	Path * p = (Path*) data;
	free(p->data);
	free(p);
}

SVGimage* createSVGimage(char* fileName)
{
	xmlDoc * parse = NULL;
    LIBXML_TEST_VERSION
	parse = xmlReadFile(fileName, NULL, 0);
	
	if (parse == NULL) {
        return NULL;
    }
    xmlNode *root_element = NULL;
	SVGimage * img = malloc(sizeof(SVGimage));
	
    strcpy(img->namespace, "http://www.w3.org/2000/svg");
    strcpy(img->title, "");
    strcpy(img->description, "");
	img->rectangles = initializeList(rectangleToString,deleteRectangle,compareRectangles);
	img->circles = initializeList(circleToString,deleteCircle,compareCircles);
	img->paths = initializeList(pathToString,deletePath,comparePaths);
    img->groups = initializeList(groupToString,deleteGroup,compareGroups);
    img->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);

    /*Get the root element node */
    root_element = xmlDocGetRootElement(parse);
	xmlNode * cur_node = NULL;
	//xmlNode * previous = NULL;
	char * chk;
	for (cur_node = root_element; cur_node != NULL; cur_node = cur_node->next)
	{
		chk = (char*)cur_node->name;
        if (strcmp(chk, "svg") == 0) {
			xmlAttr *attr;
			for (attr = cur_node->properties; attr != NULL; attr = attr->next)
			{
                Attribute * z = malloc(sizeof(Attribute));
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
				z->name = malloc(sizeof(char)*strlen(attrName)+1);
				strcpy(z->name,attrName);
				z->value = malloc(sizeof(char)*strlen(cont)+1);
				strcpy(z->value,cont);
				insertBack(img->otherAttributes, (void*)z);
				
			}
            cur_node = cur_node->children;
        }
        else if (strcmp(chk, "title") == 0){
            chk = (char*)cur_node->name;
            chk = (char*)((cur_node)->children)->content;
            strncpy(img->title, chk, 255);
        }
        else if (strcmp(chk, "desc") == 0){
            chk = (char*)((cur_node)->children)->content;
            strncpy(img->description, chk, 255);
        }
        else if (strcmp(chk, "rect") == 0){
            Rectangle * r = malloc(sizeof(Rectangle));
            r->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            strcpy(r->units,"");
            xmlAttr *attr;
			for (attr = cur_node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                char * p = NULL;
                
                if(strcmp(attrName, "x") == 0){
                    r->x = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "y") == 0){
                    r->y = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "width") == 0){
                    r->width = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "height") == 0){
                    r->height = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(r->otherAttributes, (void*)z);
                }
				
			}
            insertBack(img->rectangles, (void*)r);
        }
        else if (strcmp(chk, "circle") == 0){
            Circle * c = malloc(sizeof(Circle));
            c->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            strcpy(c->units,"");
            xmlAttr *attr;
			for (attr = cur_node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                char * p = NULL;
                
                if(strcmp(attrName, "cx") == 0){
                    c->cx = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else if(strcmp(attrName, "cy") == 0){
                    c->cy = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else if(strcmp(attrName, "r") == 0){
                    c->r = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(c->otherAttributes, (void*)z);
                }
				
			}
            insertBack(img->circles, (void*)c);
        }
        else if (strcmp(chk, "path") == 0){
            Path * p = malloc(sizeof(Path));
            p->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            p->data = NULL;
            xmlAttr *attr;
			for (attr = cur_node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                
                if(strcmp(attrName, "d") == 0){
                    p->data = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(p->data,cont);
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(p->otherAttributes, (void*)z);
                }
				
			}
            if(p->data == NULL){
                p->data = malloc(sizeof(char)+1);
                strcpy(p->data,"");
            }
            insertBack(img->paths, (void*)p);
        }
        else if (strcmp(chk, "g") == 0){
            Group * g = createGroup(cur_node);
            insertBack(img->groups, g);
        }
        if(cur_node == NULL){
            break;
        }
    }
    /************************************************************************/
    xmlFreeDoc(parse);
	return img;
}

char* SVGimageToString(SVGimage* img)
{
	return NULL;
	
}

void deleteSVGimage(SVGimage* img)
{
    if(img == NULL){return;}
    
    List * r = img->rectangles;
    for(Node * n = r->head; n != NULL; n = n->next){
        Rectangle * rec = (Rectangle*) n->data;
        freeList(rec->otherAttributes);
    }
    freeList(r);
    
    List * c = img->circles;
    for(Node * n = c->head; n != NULL; n = n->next){
        Circle * cir = (Circle*) n->data;
        freeList(cir->otherAttributes);
    }
    freeList(c);
    
    List * p = img->paths;
    for(Node * n = p->head; n != NULL; n = n->next){
        Path * pat = (Path*) n->data;
        freeList(pat->otherAttributes);
    }
    freeList(p);
    
    deleteGroups(img->groups);
    
    freeList(img->otherAttributes);
    
    free(img);
    
    /*******************************************************/

	return;
	
}

int numRectsWithArea(SVGimage* img, float area)
{
	if(img == NULL){return 0;}
    
    List * rect  = getRects(img);
    int c = 0;
    
    for(Node * n = rect->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        float a = ceilf(r->width * r->height);
        if(ceilf(area) == a){
            c++;
        }
    }
	free(rect);
	return c;
	
}

int numCirclesWithArea(SVGimage* img, float area)
{
	if(img == NULL){return 0;}
    
    List * cir  = getCircles(img);
    int c = 0;
    
    for(Node * n = cir->head; n != NULL; n = n->next){
        Circle * ci = (Circle*) n->data;
        float x = ceilf(PI * ci->r * ci->r);
        if(ceilf(area) == x){
            c++;
        }
    }
	free(cir);
	return c;
}

int numPathsWithdata(SVGimage* img, char* data)
{
	if(img == NULL){return 0;}
	
    List * pat  = getPaths(img);
    int c = 0;
    
    for(Node * n = pat->head; n != NULL; n = n->next){
        Path * p = (Path*) n->data;
        char * chk = (char*) p->data;
        if(strcmp(data,chk) == 0){
            c++;
        }
    }
	free(pat);
	return c;
	
}

int numGroupsWithLen(SVGimage* img, int len)
{
	if(img == NULL || (img->groups)->length == 0){return 0;}
	
    int c = 0;
    
    for(Node * n = (img->groups)->head; n != NULL; n = n->next){
        int x = 0;
        
        Group * g = (Group*) n->data;
        x += (g->rectangles)->length;
        x += (g->circles)->length;
        x += (g->paths)->length;
        x += (g->groups)->length;
        
        if(x == len){
            c++;
        }
    }
	return c;
}

//Total number of attributes in the image
int numAttr(SVGimage* img)
{
	if(img == NULL){return 0;}
    int c = 0;
    
    List * x = img->rectangles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        c+= (r->otherAttributes)->length;
    }
    
    x = img->circles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Circle * cr = (Circle*) n->data;
        c+= (cr->otherAttributes)->length;
    }
    
    x = img->paths;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Path * pat = (Path*) n->data;
        c+= (pat->otherAttributes)->length;
    }
    
    c += getGAttNum(img->groups);
    
    c+= (img->otherAttributes)->length;
	
	return c;	
}

// Function that returns a list of all rectangles in the image.  
List* getRects(SVGimage* img)
{
    if(img == NULL){return NULL;}
    List * a = getGRects(img->groups);
    if(a == NULL){
        a = initializeList(rectangleToString,deleteRectangle,compareRectangles);
        a = img->rectangles;
        return a;
    }
    for(Node * n = (img->rectangles)->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        insertBack(a, (void*)r);
    }
    
    return a;
}
// Function that returns a list of all circles in the image.  
List* getCircles(SVGimage* img)
{
    if(img == NULL){return NULL;}
    List * a = getGCircles(img->groups);
    if(a == NULL){
        a = initializeList(circleToString,deleteCircle,compareCircles);
        a = img->circles;
        return a;
    }
    for(Node * n = (img->circles)->head; n != NULL; n = n->next){
        Circle * c = (Circle*) n->data;
        insertBack(a, (void*)c);
    }
    
    return a;
}
// Function that returns a list of all groups in the image.  
List* getGroups(SVGimage* img)
{
    if(img == NULL){return NULL;}
    List * a = getGGroups(img->groups);
    if(a == NULL){
        a = initializeList(groupToString,deleteGroup,compareGroups);
        //a = img->groups;
        return a;
    }
    /*for(Node * n = (img->groups)->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        insertBack(a, (void*)g);
    }*/
    
    return a;
}
// Function that returns a list of all paths in the image.  
List* getPaths(SVGimage* img)
{
    if(img == NULL){return NULL;}
    List * a = getGPaths(img->groups);
    if(a == NULL){
        a = initializeList(pathToString,deletePath,comparePaths);
        a = img->paths;
        return a;
    }
    for(Node * n = (img->paths)->head; n != NULL; n = n->next){
        Path * pat = (Path*) n->data;
        insertBack(a, (void*)pat);
    }
    return a;
}

//**********My Own Functions*************

Group * createGroup(xmlNode * head)
{
    xmlNode * node = NULL;
    Group * g = malloc(sizeof(Group));
    
    g->rectangles = initializeList(rectangleToString,deleteRectangle,compareRectangles);
	g->circles = initializeList(circleToString,deleteCircle,compareCircles);
	g->paths = initializeList(pathToString,deletePath,comparePaths);
    g->groups = initializeList(groupToString,deleteGroup,compareGroups);
    g->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    
    for(node = head; node != NULL; node = node->next){
        char * chk = (char*)node->name;
        
        if (strcmp(chk, "g") == 0){
            xmlAttr *attr;
			for (attr = node->properties; attr != NULL; attr = attr->next)
			{
                Attribute * z = malloc(sizeof(Attribute));
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
				z->name = malloc(sizeof(char)*strlen(attrName)+1);
				strcpy(z->name,attrName);
				z->value = malloc(sizeof(char)*strlen(cont)+1);
				strcpy(z->value,cont);
				insertBack(g->otherAttributes, (void*)z);
				
			}
            node = node->children;
        }
        
        else if (strcmp(chk, "rect") == 0){
            Rectangle * r = malloc(sizeof(Rectangle));
            r->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            strcpy(r->units,"");
            xmlAttr *attr;
			for (attr = node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                char * p = NULL;
                
                if(strcmp(attrName, "x") == 0){
                    r->x = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "y") == 0){
                    r->y = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "width") == 0){
                    r->width = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else if(strcmp(attrName, "height") == 0){
                    r->height = strtof(cont, &p);
                    if(p != NULL){strcpy(r->units,p);}
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(r->otherAttributes, (void*)z);
                }
				
			}
            insertBack(g->rectangles, (void*)r);
        }
        else if (strcmp(chk, "circle") == 0){
            Circle * c = malloc(sizeof(Circle));
            c->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            strcpy(c->units,"");
            xmlAttr *attr;
			for (attr = node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                char * p = NULL;
                
                if(strcmp(attrName, "cx") == 0){
                    c->cx = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else if(strcmp(attrName, "cy") == 0){
                    c->cy = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else if(strcmp(attrName, "r") == 0){
                    c->r = strtof(cont, &p);
                    if(p != NULL && strcmp(p,"") != 0){strcpy(c->units,p);}
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(c->otherAttributes, (void*)z);
                }
				
			}
            insertBack(g->circles, (void*)c);
        }
        else if (strcmp(chk, "path") == 0){
            Path * p = malloc(sizeof(Path));
            p->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
            p->data = NULL;
            xmlAttr *attr;
			for (attr = node->properties; attr != NULL; attr = attr->next)
			{
				xmlNode *value = attr->children;
				char *attrName = (char *)attr->name;
				char *cont = (char *)(value->content);
                
                if(strcmp(attrName, "d") == 0){
                    p->data = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(p->data,cont);
                }
                else{
                    Attribute * z = malloc(sizeof(Attribute));
                    z->name = malloc(sizeof(char)*strlen(attrName)+1);
				    strcpy(z->name,attrName);
				    z->value = malloc(sizeof(char)*strlen(cont)+1);
				    strcpy(z->value,cont);
				    insertBack(p->otherAttributes, (void*)z);
                }
				
			}
            if(p->data == NULL){
                p->data = malloc(sizeof(char)+1);
                strcpy(p->data,"");
            }
            insertBack(g->paths, (void*)p);
        }
        else if (strcmp(chk, "g") == 0){
            Group * gr = createGroup(node);
            insertBack(g->groups, gr);
        }
    }
    return g;
}

void deleteGroups(List * groups)
{
    if(groups->length == 0){return;}
    for(Node * node = groups->head; node != NULL; node = node->next){
        Group * gr = (Group*) node->data;
        
        List * r = gr->rectangles;
        for(Node * n = r->head; n != NULL; n = n->next){
            Rectangle * rec = (Rectangle*) n->data;
            freeList(rec->otherAttributes);
        }
        freeList(r);

        List * c = gr->circles;
        for(Node * n = c->head; n != NULL; n = n->next){
            Circle * cir = (Circle*) n->data;
            freeList(cir->otherAttributes);
        }
        freeList(c);

        List * p = gr->paths;
        for(Node * n = p->head; n != NULL; n = n->next){
            Path * pat = (Path*) n->data;
            freeList(pat->otherAttributes);
        }
        freeList(p);

        deleteGroups(gr->groups);
        freeList(gr->groups);

        freeList(gr->otherAttributes);
        //free(gr);
    }
    freeList(groups);
    return;
}

List* getGRects(List * groups)
{
    if(groups->length == 0){return NULL;}
    List * rects = initializeList(rectangleToString,deleteRectangle,compareRectangles);
    for(Node * n = groups->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        for(Node * n2 = (g->rectangles)->head; n2 != NULL; n2 = n2->next){
            Rectangle * r = (Rectangle*) n2->data;
            insertBack(rects, (void*)r);
        }
        List * x = getGRects(g->groups);
        if(x != NULL){
            for(Node * n3 = x->head; n3 != NULL; n3 = n3->next){
                Rectangle * r2 = (Rectangle*) n3->data;
                insertBack(rects, (void*)r2);
            }
        }
    }
    return rects;
}

List* getGCircles(List * groups)
{
    if(groups->length == 0){return NULL;}
    List * circles = initializeList(circleToString,deleteCircle,compareCircles);
    for(Node * n = groups->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        for(Node * n2 = (g->circles)->head; n2 != NULL; n2 = n2->next){
            Circle * c = (Circle*) n2->data;
            insertBack(circles, (void*)c);
        }
        List * x = getGCircles(g->groups);
        if(x != NULL){
            for(Node * n3 = x->head; n3 != NULL; n3 = n3->next){
                Circle * c2 = (Circle*) n3->data;
                insertBack(circles, (void*)c2);
            }
        }
    }
    return circles;
}

List* getGPaths(List * groups)
{
    if(groups->length == 0){return NULL;}
    List * paths = initializeList(pathToString,deletePath,comparePaths);
    for(Node * n = groups->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        for(Node * n2 = (g->paths)->head; n2 != NULL; n2 = n2->next){
            Path * p = (Path*) n2->data;
            insertBack(paths, (void*)p);
        }
        List * x = getGPaths(g->groups);
        if(x != NULL){
            for(Node * n3 = x->head; n3 != NULL; n3 = n3->next){
                Path * p2 = (Path*) n3->data;
                insertBack(paths, (void*)p2);
            }
        }
    }
    return paths;
}

List* getGGroups(List * groups)
{
    if(groups->length == 0){return NULL;}
    List * grps = initializeList(groupToString,deleteGroup,compareGroups);
    for(Node * n = groups->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        List * x = getGGroups(g->groups);
        if(x != NULL){
            for(Node * n3 = x->head; n3 != NULL; n3 = n3->next){
                Group * g2 = (Group*) n3->data;
                insertBack(grps, (void*)g2);
            }
        }
        insertBack(grps, (void*)g);
    }
    
    return grps;
}

int getGAttNum(List * gr)
{
    if(gr->length == 0){return 0;}
    
    int x = 0;
    
    for(Node * n = gr->head; n != NULL; n = n->next){
        Group * g = (Group*) n->data;
        int y = getGAttNum(g->groups);
        x += (g->otherAttributes)->length + y;
        for(Node * n2 = (g->rectangles)->head; n2 != NULL && (g->rectangles)->length > 0 ; n2 = n2->next){
            Rectangle * r = (Rectangle*) n2->data;
            x += (r->otherAttributes)->length;
        }
        for(Node * n2 = (g->circles)->head; n2 != NULL && (g->circles)->length > 0; n2 = n2->next){
            Circle * c = (Circle*) n2->data;
            x += (c->otherAttributes)->length;
        }
        for(Node * n2 = (g->paths)->head; n2 != NULL && (g->paths)->length > 0; n2 = n2->next){
            Path * p = (Path*) n2->data;
            x += (p->otherAttributes)->length;
        }

    }
    return x;
}

/************************A2***********************/

bool validateSVGimage(SVGimage* image, char* schemaFile)
{
    if(image == NULL || schemaFile == NULL || validateImage(image) == false)
	{
		return (false);
	}
    
    xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewParserCtxt(schemaFile);
	xmlSchemaPtr schema = xmlSchemaParse(ctxt);
	xmlSchemaFreeParserCtxt(ctxt);
	xmlSchemaValidCtxtPtr ctxtv;
	ctxtv = xmlSchemaNewValidCtxt(schema);
    
    xmlDocPtr tree = createXmlDoc(image);
    
    if(xmlSchemaValidateDoc(ctxtv, tree) != 0){
		if(schema != NULL){xmlSchemaFree(schema);}
		xmlSchemaFreeValidCtxt(ctxtv);
		xmlSchemaCleanupTypes();
		xmlFreeDoc(tree);
		xmlCleanupParser();
		return (false);
	}
    if(schema != NULL){xmlSchemaFree(schema);}
	xmlSchemaFreeValidCtxt(ctxtv);
	xmlSchemaCleanupTypes();
	xmlFreeDoc(tree);
	xmlCleanupParser();
    
	return true;
}

bool validateImage(SVGimage * img)
{
    if(strcmp(img->namespace, "") == 0){
        return (false);
    }
    
    if(img->rectangles == NULL || img->circles == NULL || img->paths == NULL || img->groups == NULL || img->otherAttributes == NULL){
        return (false);
    }
    
    if(validateRects(img->rectangles) == false){
        return (false);
    }
    
    if(validateCircles(img->circles) == false){
        return (false);
    }
    
    if(validatePaths(img->paths) == false){
        return (false);
    }
    
    if(validateAtts(img->otherAttributes) == false){
        return (false);
    }
    
    if(validateGroups(img->groups) == false){
        return (false);
    }
    
    return (true);
}

bool validateRects(List * rects)
{
    for(Node * n = rects->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle *) n->data;
        if(r->width < 0 || r->height < 0 || r->otherAttributes == NULL){
            return (false);
        }
        if(validateAtts(r->otherAttributes) == false){
            return (false);
        }
    }
    return (true);
}

bool validateCircles(List * circles)
{
    for(Node * n = circles->head; n != NULL; n = n->next){
        Circle * c = (Circle *) n->data;
        if(c->r < 0 || c->otherAttributes == NULL){
            return (false);
        }
        if(validateAtts(c->otherAttributes) == false){
            return (false);
        }
    }
    return (true);
}

bool validatePaths(List * paths)
{
    for(Node * n = paths->head; n != NULL; n = n->next){
        Path * p = (Path *) n->data;
        if(p->data == NULL || p->otherAttributes == NULL){
            return (false);
        }
        if(validateAtts(p->otherAttributes) == false){
            return (false);
        }
    }
    return (true);
}

bool validateGroups(List * groups)
{
    for(Node * n = groups->head; n != NULL; n = n->next){
        Group * g = (Group *) n->data;
        if(g->rectangles == NULL || g->circles == NULL || g->paths == NULL || g->groups == NULL || g->otherAttributes == NULL){
            return (false);
        }

        if(validateRects(g->rectangles) == false){
            return (false);
        }

        if(validateCircles(g->circles) == false){
            return (false);
        }

        if(validatePaths(g->paths) == false){
            return (false);
        }

        if(validateAtts(g->otherAttributes) == false){
            return (false);
        }
        
        if((g->groups)->length > 0){
            if(validateGroups(g->groups) == false){
                return (false);
            }
        }
    }
    return (true);
}

bool validateAtts(List * atts)
{
    for(Node * n2 = atts->head; n2 != NULL; n2 = n2->next){
        Attribute * a = (Attribute *) n2->data;
        if(a->name == NULL || a->value == NULL){
            return (false);
        }
    }
    return (true);
}

SVGimage* createValidSVGimage(char* fileName, char* schemaFile)
{
    if(fileName == NULL || schemaFile == NULL){
        return NULL;
    }
    xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewParserCtxt(schemaFile);
	xmlSchemaPtr schema = xmlSchemaParse(ctxt);
	xmlSchemaFreeParserCtxt(ctxt);
	xmlSchemaValidCtxtPtr ctxtv;
	ctxtv = xmlSchemaNewValidCtxt(schema);
	xmlDoc * parse = NULL;

    parse = xmlReadFile(fileName, NULL, 0);
	
	if (parse == NULL) {
        printf("error: could not parse file %s\n", fileName);
		return NULL;
    }
	if(xmlSchemaValidateDoc(ctxtv, parse) != 0){
		printf("Invalid SVG File\n");
		if(schema != NULL){xmlSchemaFree(schema);}
		xmlSchemaFreeValidCtxt(ctxtv);
		xmlSchemaCleanupTypes();
		return NULL;
	}	
	if(schema != NULL){xmlSchemaFree(schema);}
	xmlSchemaFreeValidCtxt(ctxtv);
	xmlSchemaCleanupTypes();
        
    return createSVGimage(fileName);

}

bool writeSVGimage(SVGimage* image, char* fileName)
{
    if(image == NULL || fileName == NULL)
	{
		return (false);
	}
	xmlDocPtr tree = createXmlDoc(image);
	
	xmlSaveFormatFileEnc(fileName, tree, "UTF-8", 1);
	xmlFreeDoc(tree);
	xmlCleanupParser();
	return (true);
}

xmlDocPtr createXmlDoc(SVGimage* img)
{
	xmlDocPtr tree = NULL;       /* xml document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
    char buff[5000];
    char buff2[5000];

	List * x = img->otherAttributes;

    LIBXML_TEST_VERSION;

	tree = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "svg");
    xmlNewProp(root_node, BAD_CAST "xmlns", BAD_CAST img->namespace);

    for(Node * n = x->head; n != NULL; n = n->next){
        Attribute * a = (Attribute*) n->data;
        strcpy(buff, a->name);
        strcpy(buff2, a->value);
        xmlNewProp(root_node, BAD_CAST buff, BAD_CAST buff2);
    }
	
    xmlDocSetRootElement(tree, root_node);
	xmlCreateIntSubset(tree, BAD_CAST "svg", NULL, BAD_CAST "svg.dtd");
    
    if(strcmp(img->title, "") != 0){
        node = xmlNewNode(NULL, BAD_CAST "title");
        node1 = xmlNewText(BAD_CAST img->title);
        xmlAddChild(node, node1);
        xmlAddChild(root_node, node);
    }
    if(strcmp(img->description, "") != 0){
        node = xmlNewNode(NULL, BAD_CAST "desc");
        node1 = xmlNewText(BAD_CAST img->description);
        xmlAddChild(node, node1);
        xmlAddChild(root_node, node);
    }

    x = img->rectangles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "rect");
        sprintf(buff, "%0.1f%s", r->x, r->units);
        xmlNewProp(node, BAD_CAST "x", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->y, r->units);
        xmlNewProp(node, BAD_CAST "y", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->width, r->units);
        xmlNewProp(node, BAD_CAST "width", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->height, r->units);
        xmlNewProp(node, BAD_CAST "height", BAD_CAST buff);
        List * la = r->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(root_node, node);
    }
    
    x = img->circles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Circle * c = (Circle*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "circle");
        sprintf(buff, "%0.1f%s", c->cx, c->units);
        xmlNewProp(node, BAD_CAST "cx", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", c->cy, c->units);
        xmlNewProp(node, BAD_CAST "cy", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", c->r, c->units);
        xmlNewProp(node, BAD_CAST "r", BAD_CAST buff);
        List * la = c->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(root_node, node);
    }
    
    x = img->paths;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Path * p = (Path*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "path");
        strcpy(buff, p->data);
        xmlNewProp(node, BAD_CAST "d", BAD_CAST buff);
        List * la = p->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(root_node, node);
    }
	
    x = img->groups;
    for(Node * n = x->head; n != NULL && x->length != 0; n = n->next){
        Group * g = (Group*) n->data;
        xmlNodePtr gnode = gNode(g);
        xmlAddChild(root_node, gnode);
    }
    
	xmlSaveFormatFileEnc("swasif.svg", tree, "UTF-8", 1);
	//free(tree);
	//tree = 
	xmlFreeDoc(tree);
	//xmlCleanupParser();
	//xmlMemoryDump();
	
    return(xmlReadFile("swasif.svg", NULL, 0));
	
}

xmlNodePtr gNode(Group * g)
{
    xmlNodePtr node2 = xmlNewNode(NULL, BAD_CAST "g"), node = NULL;
    List * x = NULL;
    char buff[5000];
    char buff2[5000];
    
    x = g->rectangles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Rectangle * r = (Rectangle*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "rect");
        sprintf(buff, "%0.1f%s", r->x, r->units);
        xmlNewProp(node, BAD_CAST "x", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->y, r->units);
        xmlNewProp(node, BAD_CAST "y", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->width, r->units);
        xmlNewProp(node, BAD_CAST "width", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", r->height, r->units);
        xmlNewProp(node, BAD_CAST "height", BAD_CAST buff);
        List * la = r->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(node2, node);
    }
    
    x = g->circles;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Circle * c = (Circle*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "circle");
        sprintf(buff, "%0.1f%s", c->cx, c->units);
        xmlNewProp(node, BAD_CAST "cx", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", c->cy, c->units);
        xmlNewProp(node, BAD_CAST "cy", BAD_CAST buff);
        sprintf(buff, "%0.1f%s", c->r, c->units);
        xmlNewProp(node, BAD_CAST "r", BAD_CAST buff);
        List * la = c->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(node2, node);
    }
    
    x = g->paths;
    
    for(Node * n = x->head; n != NULL; n = n->next){
        Path * p = (Path*) n->data;
        node = xmlNewNode(NULL, BAD_CAST "path");
        strcpy(buff, p->data);
        xmlNewProp(node, BAD_CAST "d", BAD_CAST buff);
        List * la = p->otherAttributes;
        for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
            Attribute * a = (Attribute*) n2->data;
            strcpy(buff, a->name);
            strcpy(buff2, a->value);
            xmlNewProp(node, BAD_CAST buff, BAD_CAST buff2);
        }
        xmlAddChild(node2, node);
    }
	
    x = g->groups;
    for(Node * n = x->head; n != NULL && x->length != 0; n = n->next){
        Group * g = (Group*) n->data;
        xmlNodePtr gnode = gNode(g);
        xmlAddChild(node2, gnode);
    }
    
    List * la = g->otherAttributes;
    for(Node * n2 = la->head; n2 != NULL; n2 = n2->next){
        Attribute * a = (Attribute*) n2->data;
        strcpy(buff, a->name);
        strcpy(buff2, a->value);
        xmlNewProp(node2, BAD_CAST buff, BAD_CAST buff2);
    }
    
    return node2;
}

void setAttribute(SVGimage* image, elementType elemType, int elemIndex, Attribute* newAttribute)
{
    if(image == NULL || elemType < 0 || elemType > 4 || newAttribute == NULL){
        
        if(newAttribute != NULL){
            deleteAttribute((void*)newAttribute);
        }
        return;
    }
    if(elemIndex < 0 && elemType != 0){
        return;
    }
    int i = 0;
    List * x = NULL;
    if(elemType == 0){
        x = image->otherAttributes;
        char * chk = NULL;
        chk = newAttribute->name;
        if(strcmp(chk,"title") == 0 || strcmp(chk,"desc") == 0){
            if(strcmp(chk,"title") == 0 && newAttribute->value != NULL){
                strcpy(image->title, newAttribute->value);
                deleteAttribute((void*)newAttribute);
                return;
            }
            if(strcmp(chk,"desc") == 0 && newAttribute->value != NULL){
                strcpy(image->description, newAttribute->value);
                deleteAttribute((void*)newAttribute);
                return;
            }
        }
        else{
            for(Node * n2 = x->head; n2 != NULL; n2 = n2->next){
                Attribute * a = (Attribute*) n2->data;
                if(chk != NULL && strcmp(a->name, chk) == 0 && newAttribute->value != NULL){
                    a->value = realloc(a->value, sizeof(char)*strlen(newAttribute->value)+1);
                    strcpy(a->value, newAttribute->value);
                    deleteAttribute((void*)newAttribute);
                    return;
                }
            }
            insertBack(image->otherAttributes, (void*)newAttribute);
            return;
        }
    }
    
    if(elemType == 2){
        x = image->rectangles;
        char * chk = NULL;
        //strcpy(chk, newAttribute->name);
        chk = newAttribute->name;
        for(Node * n = x->head; n != NULL; n = n->next){
            if(i == elemIndex){
                Rectangle * r = (Rectangle*) n->data;
                if(strcmp(chk,"x") == 0 || strcmp(chk,"y") == 0 || strcmp(chk,"width") == 0 || strcmp(chk,"height") == 0){
                    char * p;
                    if(strcmp(chk,"x") == 0 && newAttribute->value != NULL){
                        r->x = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                    if(strcmp(chk,"y") == 0 && newAttribute->value != NULL){
                        r->y = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                    if(strcmp(chk,"width") == 0 && newAttribute->value != NULL){
                        r->width = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                    if(strcmp(chk,"height") == 0 && newAttribute->value != NULL){
                        r->height = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                }
                else{
                    List * y = r->otherAttributes;
                    for(Node * n2 = y->head; n2 != NULL; n2 = n2->next){
                        Attribute * a = (Attribute*) n2->data;
                        if(strcmp(a->name, chk) == 0 && newAttribute->value != NULL){
                            a->value = realloc(a->value, sizeof(char)*strlen(newAttribute->value)+1);
                            strcpy(a->value, newAttribute->value);
                            deleteAttribute((void*)newAttribute);
                            return;
                        }
                    }
                    insertBack(r->otherAttributes, (void*)newAttribute);
                    return;
                }
            }
            i++;
        }
        
        deleteAttribute((void*)newAttribute);
        return;
    }
    
    if(elemType == 1){
        x = image->circles;
        char * chk = NULL;
        //strcpy(chk, newAttribute->name);
        chk = newAttribute->name;
        for(Node * n = x->head; n != NULL; n = n->next){
            if(i == elemIndex){
                Circle * c = (Circle*) n->data;
                if(strcmp(chk,"cx") == 0 || strcmp(chk,"cy") == 0 || strcmp(chk,"r") == 0){
                    char * p;
                    if(strcmp(chk,"cx") == 0 && newAttribute->value != NULL){
                        c->cx = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                    if(strcmp(chk,"cy") == 0 && newAttribute->value != NULL){
                        c->cy = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                    if(strcmp(chk,"r") == 0 && newAttribute->value != NULL){
                        c->r = strtof(newAttribute->value, &p);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                }
                else{
                    List * y = c->otherAttributes;
                    for(Node * n2 = y->head; n2 != NULL; n2 = n2->next){
                        Attribute * a = (Attribute*) n2->data;
                        if(strcmp(a->name, chk) == 0 && newAttribute->value != NULL){
                            a->value = realloc(a->value, sizeof(char)*strlen(newAttribute->value)+1);
                            strcpy(a->value, newAttribute->value);
                            deleteAttribute((void*)newAttribute);
                            return;
                        }
                    }
                    insertBack(c->otherAttributes, (void*)newAttribute);
                    return;
                }
            }
            i++;
        }
        
        deleteAttribute((void*)newAttribute);
        return;
    }
    
    if(elemType == 3){
        x = image->paths;
        char * chk = NULL;
        //strcpy(chk, newAttribute->name);
        chk = newAttribute->name;
        for(Node * n = x->head; n != NULL; n = n->next){
            if(i == elemIndex){
                Path * p = (Path*) n->data;
                if(strcmp(chk,"d") == 0 && newAttribute->value != NULL){
                    //strcpy(p->data,"");
                    p->data = realloc(p->data, sizeof(char)*strlen(newAttribute->value)+1);
                    strcpy(p->data, newAttribute->value);
                    deleteAttribute((void*)newAttribute);
                    return;
                }
                else{
                    List * y = p->otherAttributes;
                    for(Node * n2 = y->head; n2 != NULL; n2 = n2->next){
                        Attribute * a = (Attribute*) n2->data;
                        if(strcmp(a->name, chk) == 0 && newAttribute->value != NULL){
                            a->value = realloc(a->value, sizeof(char)*strlen(newAttribute->value)+1);
                            strcpy(a->value, newAttribute->value);
                            deleteAttribute((void*)newAttribute);
                            return;
                        }
                    }
                    insertBack(p->otherAttributes, (void*)newAttribute);
                    return;
                }
            }
            i++;
        }
        deleteAttribute((void*)newAttribute);
        return;
    }
    
    if(elemType == 4){
        x = image->groups;
        char * chk = NULL;
        //strcpy(chk, newAttribute->name);
        chk = newAttribute->name;
        for(Node * n = x->head; n != NULL && i <= elemIndex; n = n->next){
            if(i == elemIndex){
                Group * g = (Group*) n->data;
                List * y = g->otherAttributes;
                for(Node * n2 = y->head; n2 != NULL; n2 = n2->next){
                    Attribute * a = (Attribute*) n2->data;
                    if(strcmp(a->name, chk) == 0 && newAttribute->value != NULL){
                        a->value = realloc(a->value, sizeof(char)*strlen(newAttribute->value)+1);
                        strcpy(a->value, newAttribute->value);
                        deleteAttribute((void*)newAttribute);
                        return;
                    }
                }
                insertBack(g->otherAttributes, (void*)newAttribute);
                return;
            }
            i++;
        }
        deleteAttribute((void*)newAttribute);
        return;
    }
    deleteAttribute((void*)newAttribute);
    return;
}

void addComponent(SVGimage* img, elementType type, void* newElement)
{
    if(img == NULL || type < 1 || type > 3 || newElement == NULL){
        return;
    }
    if(type == 1){
        insertBack(img->circles, newElement);
        return;
    }
    if(type == 2){
        insertBack(img->rectangles, newElement);
        return;
    }
    if(type == 3){
        insertBack(img->paths, newElement);
        return;
    }
}

char* attrToJSON(const Attribute *a)
{
    if(a == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    
    char buff[512];
    sprintf(buff, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name, a->value);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    return x;
}

char* circleToJSON(const Circle *c)
{
    if(c == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    
    char buff[512];
    sprintf(buff, "{\"cx\":%0.2f,\"cy\":%0.2f,\"r\":%0.2f,\"numAttr\":%d,\"units\":\"%s\"}", c->cx, c->cy, c->r, (c->otherAttributes)->length, c->units);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    return x;
}

char* rectToJSON(const Rectangle *r)
{
    if(r == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    
    char buff[512];
    sprintf(buff, "{\"x\":%0.2f,\"y\":%0.2f,\"w\":%0.2f,\"h\":%0.2f,\"numAttr\":%d,\"units\":\"%s\"}", r->x, r->y, r->width, r->height, (r->otherAttributes)->length, r->units);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    return x;
}

char* pathToJSON(const Path *p)
{
    if(p == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    
    char buff[512];
    char turn[65];
    turn[64] = '\0';
    strncpy(turn, p->data, 64);
    sprintf(buff, "{\"d\":\"%s\",\"numAttr\":%d}", turn, (p->otherAttributes)->length);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    return x;
}

char* groupToJSON(const Group *g)
{
    if(g == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    int y = (g->rectangles)->length + (g->circles)->length + (g->paths)->length + (g->groups)->length;
    char buff[512];
    sprintf(buff, "{\"children\":%d,\"numAttr\":%d}", y, (g->otherAttributes)->length);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    return x;
}

char* attrListToJSON(const List *list)
{
    if(list == NULL || list->length == 0){
        char * x = malloc(sizeof(char)*2+1);
        strcpy(x, "[]");
        return x;
	}
    
	char buff[512];
	char * read;
	char * x;
	
	sprintf(buff,"[");
	x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
	
    for(Node * n = list->head; n != NULL; n = n->next){
        if(n->next == NULL){
            read = attrToJSON((Attribute*)n->data);
            sprintf(buff,"%s]", read);
            int len = strlen(x) + strlen(buff);
            x = realloc(x, sizeof(char)*len+1);
            strncat(x, buff, strlen(buff));
            free(read);
            return x;
        }
        read = attrToJSON((Attribute*)n->data);
        sprintf(buff,"%s,", read);
        int len = strlen(x) + strlen(buff);
        x = realloc(x, sizeof(char)*len+1);
		strncat(x, buff, strlen(buff));
		free(read);
    }
    free(x);
    char * y = malloc(sizeof(char)*2+1);
    strcpy(y, "[]");
    return y; 
}

char* circListToJSON(const List *list)
{
    if(list == NULL || list->length == 0){
        char * x = malloc(sizeof(char)*2+1);
        strcpy(x, "[]");
        return x;
	}
    
	char buff[512];
	char * read;
	char * x;
	
	sprintf(buff,"[");
	x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
	
    for(Node * n = list->head; n != NULL; n = n->next){
        if(n->next == NULL){
            read = circleToJSON((Circle*)n->data);
            sprintf(buff,"%s]", read);
            int len = strlen(x) + strlen(buff);
            x = realloc(x, sizeof(char)*len+1);
            strncat(x, buff, strlen(buff));
            free(read);
            return x;
        }
        read = circleToJSON((Circle*)n->data);
        sprintf(buff,"%s,", read);
        int len = strlen(x) + strlen(buff);
        x = realloc(x, sizeof(char)*len+1);
		strncat(x, buff, strlen(buff));
		free(read);
    }
    free(x);
    char * y = malloc(sizeof(char)*2+1);
    strcpy(y, "[]");
    return y; 
}

char* rectListToJSON(const List *list)
{
    if(list == NULL || list->length == 0){
        char * x = malloc(sizeof(char)*2+1);
        strcpy(x, "[]");
        return x;
	}
    
	char buff[512];
	char * read;
	char * x;
	
	sprintf(buff,"[");
	x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
	
    for(Node * n = list->head; n != NULL; n = n->next){
        if(n->next == NULL){
            read = rectToJSON((Rectangle*)n->data);
            sprintf(buff,"%s]", read);
            int len = strlen(x) + strlen(buff);
            x = realloc(x, sizeof(char)*len+1);
            strncat(x, buff, strlen(buff));
            free(read);
            return x;
        }
        read = rectToJSON((Rectangle*)n->data);
        sprintf(buff,"%s,", read);
        int len = strlen(x) + strlen(buff);
        x = realloc(x, sizeof(char)*len+1);
		strncat(x, buff, strlen(buff));
		free(read);
    }
    free(x);
    char * y = malloc(sizeof(char)*2+1);
    strcpy(y, "[]");
    return y; 
}

char* pathListToJSON(const List *list)
{
    if(list == NULL || list->length == 0){
        char * x = malloc(sizeof(char)*2+1);
        strcpy(x, "[]");
        return x;
	}
    
	char buff[512];
	char * read;
	char * x;
	
	sprintf(buff,"[");
	x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
	
    for(Node * n = list->head; n != NULL; n = n->next){
        if(n->next == NULL){
            read = pathToJSON((Path*)n->data);
            sprintf(buff,"%s]", read);
            int len = strlen(x) + strlen(buff);
            x = realloc(x, sizeof(char)*len+1);
            strncat(x, buff, strlen(buff));
            free(read);
            return x;
        }
        read = pathToJSON((Path*)n->data);
        sprintf(buff,"%s,", read);
        int len = strlen(x) + strlen(buff);
        x = realloc(x, sizeof(char)*len+1);
		strncat(x, buff, strlen(buff));
		free(read);
    }
    free(x);
    char * y = malloc(sizeof(char)*2+1);
    strcpy(y, "[]");
    return y;
}

char* groupListToJSON(const List *list)
{
    if(list == NULL || list->length == 0){
        char * x = malloc(sizeof(char)*2+1);
        strcpy(x, "[]");
        return x;
	}
    
	char buff[512];
	char * read;
	char * x;
	
	sprintf(buff,"[");
	x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
	
    for(Node * n = list->head; n != NULL; n = n->next){
        if(n->next == NULL){
            read = groupToJSON((Group*)n->data);
            sprintf(buff,"%s]", read);
            int len = strlen(x) + strlen(buff);
            x = realloc(x, sizeof(char)*len+1);
            strncat(x, buff, strlen(buff));
            free(read);
            return x;
        }
        read = groupToJSON((Group*)n->data);
        sprintf(buff,"%s,", read);
        int len = strlen(x) + strlen(buff);
        x = realloc(x, sizeof(char)*len+1);
		strncat(x, buff, strlen(buff));
		free(read);
    }
    free(x);
    char * y = malloc(sizeof(char)*2+1);
    strcpy(y, "[]");
    return y;
}

char* SVGtoJSON(const SVGimage* image)
{
    if(image == NULL){
        char * x = malloc(sizeof(char)*2+1);
		strcpy(x, "{}");
		return x;
    }
    List * a = getRects((SVGimage*)image);
    List * b = getCircles((SVGimage*)image);
    List * c = getPaths((SVGimage*)image);
    List * d = getGroups((SVGimage*)image);
    char buff[512];
    sprintf(buff, "{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}", a->length, b->length, c->length, d->length);
    char * x = malloc(sizeof(char)*strlen(buff)+1);
	strcpy(x, buff);
    
    freeList(a);
    freeList(b);
    freeList(c);
    freeList(d);
    
    return x;
}

/**************BONUS A2***************************/

SVGimage* JSONtoSVG(const char* svgString)
{
    if(svgString == NULL){
        return NULL;
    }
    SVGimage * img = malloc(sizeof(SVGimage));
	
    strcpy(img->namespace, "http://www.w3.org/2000/svg");
	img->rectangles = initializeList(rectangleToString,deleteRectangle,compareRectangles);
	img->circles = initializeList(circleToString,deleteCircle,compareCircles);
	img->paths = initializeList(pathToString,deletePath,comparePaths);
    img->groups = initializeList(groupToString,deleteGroup,compareGroups);
    img->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    
    char buff[512];
	char b [256];
	char x [256];
	strcpy(buff, svgString);
	sscanf(buff, "{\"title\":\"%[^\t\n\"]\",\"descr\":\"%[^\t\n\"]\"}", x, b);
    strcpy(img->title, x);
    strcpy(img->description, b);
    
    return img;
}

Rectangle* JSONtoRect(const char* svgString)
{
    if(svgString == NULL){
        return NULL;
    }
    Rectangle * r = malloc(sizeof(Rectangle));
    
    r->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    
    char buff[512];
    strcpy(buff, svgString);
    float x, y, w, h;
    char u[50];
    u[49] = '\0';
    sscanf(buff, "{\"x\":%f,\"y\":%f,\"w\":%f,\"h\":%f,\"units\":\"%[^\t\n\"]\"}", &x, &y, &w, &h, u);
    
    r->x = x;
    r->y = y;
    r->width = w;
    r->height = h;
    strcpy(r->units, u);
    
    return r;
}

Circle* JSONtoCircle(const char* svgString)
{
    if(svgString == NULL){
        return NULL;
    }
    Circle * c = malloc(sizeof(Circle));
    
    c->otherAttributes = initializeList(attributeToString,deleteAttribute,compareAttributes);
    
    char buff[512];
    strcpy(buff, svgString);
    float x, y, r;
    char u[50];
    sscanf(buff, "{\"cx\":%f,\"cy\":%f,\"r\":%f,\"units\":\"%[^\t\n\"]\"}", &x, &y, &r, u);
    
    c->cx = x;
    c->cy = y;
    c->r = r;
    strcpy(c->units, u);
    
    return c;
}