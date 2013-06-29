//
//  Config.cpp
//  SuperSector
//
//  Created by ZhouRui on 13-6-24.
//
//

#include "Config.h"
#include "CCFileUtils.h"
#include <string>
#include <libxml/parser.h>
#include <libxml/xpath.h>

using namespace cocos2d;



void toBarrierParamList(xmlNodePtr node,BarrierParamList& list)
{
    xmlNodePtr curChild;
    xmlAttrPtr attr;
    attr = node->properties;
    if(attr != NULL)
        sscanf((const char*)xmlNodeGetContent((xmlNodePtr)attr),"%f",&list.movedLength);
    else
        list.movedLength = 0.6;
    for(curChild=node->children;curChild != NULL; curChild = curChild->next)
    {
        BarrierParam param;
        attr = curChild->properties;
        //for( attr = curChild->properties; attr != NULL; attr = attr->next)
        sscanf((const char*)xmlNodeGetContent((xmlNodePtr)attr),"%f",&param.innerR);
        attr = attr->next;
        sscanf((const char*)xmlNodeGetContent((xmlNodePtr)attr),"%f",&param.outerR);
        attr = attr->next;
        sscanf((const char*)xmlNodeGetContent((xmlNodePtr)attr),"%d",&param.start);
        attr = attr->next;
        sscanf((const char*)xmlNodeGetContent((xmlNodePtr)attr),"%d",&param.end);
        list.push_back(param);
    }
}

void toLevelData(xmlNodePtr node,LevelData& data)
{
    xmlAttrPtr curAttr = node->properties;
    sscanf((const char*)xmlNodeGetContent((xmlNodePtr)curAttr),"%d",&data.level);
    curAttr = curAttr->next;
    sscanf((const char*)xmlNodeGetContent((xmlNodePtr)curAttr),"%f",&data.maxRotateSpeed);
    
    for(xmlNodePtr curChild = node->children->children; curChild != NULL; curChild = curChild->next)
    {
        BarrierParamList list;
        toBarrierParamList(curChild, list);
        data.barrierParamLists.push_back(list);
    }
}

static ConfigAndData* s_configAndData = NULL;
ConfigAndData* ConfigAndData::sharedInstance()
{
    if(s_configAndData == NULL)
    {
        xmlDocPtr doc;
        xmlNodePtr root;
        xmlXPathContextPtr xpathCtx;
        xmlXPathObjectPtr xpathObj;
        s_configAndData = new ConfigAndData;
        doc = xmlReadFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("ConfigAndData.xml").c_str(), NULL, (XML_PARSE_NOCDATA | XML_PARSE_NOBLANKS));
        CCAssert(doc != NULL, "Error: unable to load ConfigAndData.xml");
        xpathCtx = xmlXPathNewContext(doc);
        root = xmlDocGetRootElement(doc);
        
        xpathObj = xmlXPathEval((const xmlChar*)"//LevelData", xpathCtx);
        if(xpathObj)
        {
            xmlNodeSetPtr nodeSet = xpathObj->nodesetval;
            if (nodeSet) {
                for (int index = 0; index < nodeSet->nodeNr; index++) {
                    LevelData levelData;
                    toLevelData(nodeSet->nodeTab[index], levelData);
                    s_configAndData->levelDatas.push_back(levelData);
                }
            }
            xmlXPathFreeObject(xpathObj);
        }    
        xmlFreeDoc(doc);
    }
    return s_configAndData;
}