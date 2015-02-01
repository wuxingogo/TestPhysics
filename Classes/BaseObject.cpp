//
//  BaseObject.cpp
//  MyCppGame
//
//  Created by ly on 14-12-20.
//
//

#include "BaseObject.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

BaseObject::BaseObject(const char * filename){
    printf("nane is %s\n",filename);
    
    this->filename = new char[20];
    sprintf(this->filename,filename);
    getData();
    strcat(this->filename,".csb");
    printf("nane is %s\n",this->filename);
    _node = CSLoader::createNode(this->filename);
    this->addChild(_node,5);
   
    _action = CSLoader::createTimeline(this->filename);
    _node->runAction(_action);
    _action->gotoFrameAndPlay(1,true);
    _action->setTimeSpeed(0.6);
    
}

void BaseObject::getData(){
    SkeletalArray* skeletal = SkeletalArray::getInstence();
    actionSeq = skeletal->getData(this->filename);
}
void BaseObject::runSkeletalAction(const char * act){
 
    int * i = actionSeq.at(act);
    _action->gotoFrameAndPlay(i[0],i[1], true);
    _node->stopAction(_action);
    _node->runAction(_action);

}
