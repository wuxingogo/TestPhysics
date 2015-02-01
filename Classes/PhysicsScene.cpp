//
//  PhysicsScene.cpp
//  MyCppGame
//
//  Created by ly on 14-12-21.
//
//

#include "PhysicsScene.h"
#include <Box2D/Box2D.h>



bool PhysicsScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    world = new b2World(b2Vec2(0,-5.0f));
    
    ground = Sprite::create("HelloWorld.png");
    ground->setPosition(300,500);
    
//    ground->setAnchorPoint(Vec2::ZERO);
    this->addChild(ground);
    createTiled(ground);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    createGround(0, 0, winSize.width, 10,NULL);
    createGround(0, winSize.height-10, winSize.width, 10,NULL);
    createGround(0, winSize.height-10, 10, winSize.height,NULL);
    createGround(winSize.width-10, winSize.height-10, 10, winSize.height,NULL);
    
//    Sprite* sp1 =
    
    this->scheduleUpdate();
    
    
    
    mB2DebugDraw = new GLESDebugDraw(worldScale);
    world->SetDebugDraw(mB2DebugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
//    flags += b2Draw::e_pairBit;
//    flags += b2Draw::e_centerOfMassBit;
    
    mB2DebugDraw->SetFlags(flags);
    
    
    
    this->setTouchEnabled(true);
    
    return true;
    
}

void PhysicsScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    for(auto touch:touches)
    {
        auto location = touch->getLocation();
        addNewSpriteAtPosition(location);
    }
}
void PhysicsScene::addNewSpriteAtPosition(Point p)
{
    CCLOG("add");
    
    auto sprite = Sprite::create("CloseNormal.png");
    sprite->setPosition(p);
    createTiled(sprite);
    this->addChild(sprite);
//    b2RevoluteJointDef jointDef;
//    
//    jointDef.bodyA = myBody;
//    jointDef.localAnchorA =  myBody->GetPosition();
//    b2RevoluteJoint * joint = world->CreateJoint(&jointDef);
    
}


void PhysicsScene::createGround(int x,int y,int width,int height,Sprite* sp){
    b2BodyDef b2def;
    b2def.position.Set(x/worldScale, y/worldScale);
    b2def.type = b2BodyType::b2_staticBody;
    b2def.userData = sp;
    b2PolygonShape b2shape;
    b2shape.SetAsBox(width/worldScale, height/worldScale);
    b2FixtureDef b2fix;
    b2fix.shape = &b2shape;
    b2fix.density = 10.0f;
    b2fix.friction =1.0f; // We don't want the ball to have friction!
    b2fix.restitution = 0;
    
    b2Body *body = world->CreateBody(&b2def);
    body->CreateFixture(&b2fix);
    
}

void PhysicsScene::createTiled(Sprite* sp){
    b2BodyDef b2def;
    b2def.position.Set(sp->getPosition().x/worldScale, sp->getPosition().y/worldScale);
    b2def.type = b2BodyType::b2_dynamicBody;
    b2def.userData = sp;
    b2PolygonShape b2shape;
    b2shape.SetAsBox(sp->getContentSize().width/2/worldScale, sp->getContentSize().height/2/worldScale);
    b2FixtureDef b2fix;
    b2fix.shape = &b2shape;
    b2fix.density = 1.0f;
	b2fix.friction = 0.0f;
	b2fix.restitution = 0.0f;
    
    myBody = world->CreateBody(&b2def);
    myBody->CreateFixture(&b2fix);
}
void PhysicsScene::update(float dt){
    world->Step(dt, 10, 10);
    world->ClearForces();
    
    for (b2Body* i = world->GetBodyList(); i; i=i->GetNext()) {
        if (i->GetUserData() != NULL) {
            Sprite* sp = (Sprite*)i->GetUserData();
            sp->setPosition(i->GetPosition().x*worldScale,i->GetPosition().y*worldScale );
            sp->setRotation(-1 * CC_RADIANS_TO_DEGREES(i->GetAngle()) );
//            CCLOG("%f,%f",i->GetPosition().x, i->GetPosition().y);
        }

    }
    
    
}

void PhysicsScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION );
    
    kmGLPushMatrix();
    
    world->DrawDebugData();
    
    kmGLPopMatrix();
    Layer::draw(renderer, transform, flags);
    
}

void PhysicsScene::onDraw(){
    CCLOG("ONDRAW");
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Mat4 oldMV;
    oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
    world->DrawDebugData();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}
Scene* PhysicsScene::createScene(){
    auto scene = Scene::create();
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    PhysicsScene* layer = PhysicsScene::create();
    
    scene->addChild(layer);
    return scene;
}

