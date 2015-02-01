//
//  BaseObject.h
//  MyCppGame
//
//  Created by ly on 14-12-20.
//
//

#ifndef __MyCppGame__BaseObject__
#define __MyCppGame__BaseObject__

#include "cocos2d.h"
#include "JSONParser.h"
#include "cocostudio/CocoStudio.h"
#include "SkeletalArray.h"
USING_NS_CC;
using namespace cocostudio::timeline;



struct actSeq{
    int _startIndex;
    int _endIndex;
    const char * _name;
};

class BaseObject : public Node{
public:
    BaseObject(const char * filename);
    Node *_node;
    char * filename;

    void getData();
    void runSkeletalAction(const char * act);
    ActionTimeline* _action;
    
    map<std::string,int *> actionSeq;
};



#endif /* defined(__MyCppGame__BaseObject__) */
