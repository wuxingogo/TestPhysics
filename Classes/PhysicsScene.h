//
//  PhysicsScene.h
//  MyCppGame
//
//  Created by ly on 14-12-21.
//
//

#ifndef __MyCppGame__PhysicsScene__
#define __MyCppGame__PhysicsScene__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "GLES-Render.h"
USING_NS_CC;

class PhysicsScene : public Layer {
    
public:
    bool init();
    
    static Scene* createScene();
    
    void createGround(int x,int y,int width,int height,Sprite* sp);
    void createTiled(Sprite* sp);
    void update(float dt);
    b2World* world;
    b2Body * myBody;
    Sprite* ground;
    GLESDebugDraw* mB2DebugDraw;
    
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    
    const int worldScale = 32;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
    void addNewSpriteAtPosition(Point p);
    
    
    
    CREATE_FUNC(PhysicsScene);
private:
    Mat4 _modelViewMV;
    void onDraw();
    CustomCommand _customCommand;
};

#endif /* defined(__MyCppGame__PhysicsScene__) */
