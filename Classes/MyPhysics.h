//
//  MyPhysics.h
//  MyCppGame
//
//  Created by ly on 14-12-23.
//
//

#ifndef __MyCppGame__MyPhysics__
#define __MyCppGame__MyPhysics__

#include "cocos2d.h"
USING_NS_CC;

class MyPhysics : public Layer {
public:
    
    bool init();
    static Scene* createScene();
    void onEnter();
    CREATE_FUNC(MyPhysics);
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    PhysicsWorld* m_world;
    void menuCloseCallback(Ref* pSender);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    void addNewSpriteAtPosition(Point p);
};

#endif /* defined(__MyCppGame__MyPhysics__) */
