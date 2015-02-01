//
//  MyPhysics.cpp
//  MyCppGame
//
//  Created by ly on 14-12-23.
//
//

#include "MyPhysics.h"
#include "SkeletalArray.h"
#include "BaseObject.h"


bool MyPhysics::init(){
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MyPhysics::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto edgeSp = Sprite::create();
//    auto body = PhysicsBody::createEdgeBox(visibleSize,3); //此句仅3.0 alpha0 有效
    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    edgeSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    edgeSp->setPhysicsBody(body);this->addChild(edgeSp);edgeSp->setTag(0);
    
    JSONParser* test = JSONParser::create("Action.json");
    JSONObject* root =  test->getJsonRoot();
    JSONArray* array = (JSONArray*)root->seachJsonObject("bianfu");
    
    JSONObject* array1 = (JSONArray*)array->getJsonArray(1);
    
    SkeletalArray* dateArray = SkeletalArray::getInstence();
    dateArray->loadData(root, "bianfu");
    
    
    
    this->setTouchEnabled(true);
    
    return true;
}

void MyPhysics::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
    for(auto touch:touches)
    {
        auto location = touch->getLocation();
        addNewSpriteAtPosition(location);
    }
}
void MyPhysics::addNewSpriteAtPosition(Point p)
{
    
    BaseObject * sp = new BaseObject("bianfu");
    auto node = sp->getChildByName("bianfu");
    auto node1 = node->getChildByName("Layer2");
//
//    PhysicsBody* pbody = PhysicsBody::create();
//    PhysicsShape* shape;

    Sprite* node2 = ( Sprite*)node1->getChildByName("bianfu/b1");
//    for (int i = 0; i < node->getChildrenCount(); i++) {
//        if (node->getChildrenCount() > 0) {
//            Vector<Node*>Vec = node->getChildren();
//            
//            for (int j = 0 ; j < Vec.size(); j++) {
//                Sprite* spj = (Sprite*)Vec.at(j);
//                if (spj->getTextureRect().size.width!=0 &&spj->getTextureRect().size.height !=0) {
                    auto body = PhysicsBody::createBox(Size(node2->getTextureRect().size.width, node2->getTextureRect().size.height));
//                    body->setGravityEnable(false);
//                    shape = body->getShape(0);
//                    pbody->addShape(shape);
//                }
//            }
//        }
//        
//    }
    Vec2 vec = node->getPosition();
    vec += node1->getPosition();
    vec += node2->getPosition()+Vec2(node2->getTextureRect().size.width / 2,node2->getTextureRect().size.height / 2);
    
    body->setPositionOffset(vec);
    sp->setTag(1);
    
    sp->setPhysicsBody(body);

    sp->setPosition(p);
    this->addChild(sp);
}

void MyPhysics::menuCloseCallback(Ref* pSender)
{
    if(m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
    {
        m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    }
    else
    {
        m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    }
    
}
void MyPhysics::onEnter(){
    Layer::onEnter();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
	//创建一个物理世界, 大小和屏幕的尺寸相同, 使用默认材质, debug框的宽度为3个像素
	auto body = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
	//创建一个碰撞图形
	auto edgeShape = Node::create();
    
	//将图形和刚刚创建的世界绑定
	edgeShape->setPhysicsBody( body);
    
	//设置图形的位置在屏幕正中间
	edgeShape->setPosition( visibleSize.width / 2, visibleSize.height / 2);
    
	//添加进图层
	addChild( edgeShape);
}
Scene* MyPhysics::createScene(){
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(true);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
    auto layer = MyPhysics::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}