#include "HelloWorldScene.h"


#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <spine/spine-cocos2dx.h>
#include "cocos-ext.h"
#include "extensions/cocos-ext.h"


#include "JSONParser.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace cocostudio::timeline;
using namespace rapidjson;

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "BaseObject.h"
#include "SkeletalArray.h"



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
//    Node* bg = CSLoader::createNode("Layer.csb");
//    this->addChild(bg,5);
//    bg->setPosition(300,0);
//    ActionTimeline* action = CSLoader::createTimeline("viewScene.csb");
//    bg->runAction(action);
//    action->gotoFrameAndPlay(0,true);
    
    JSONParser* test = JSONParser::create("Action.json");
    JSONObject* root =  test->getJsonRoot();
    JSONArray* array = (JSONArray*)root->seachJsonObject("bianfu");
    
    JSONObject* array1 = (JSONArray*)array->getJsonArray(1);
//    JSONObject* array1 = array->seachJsonObject("id");
//    CCLOG("%s",array1->getChar("name"));
//    CCLOG("%d",array1->getInt("startIndex"));
//    CCLOG("%d",array1->getInt("endIndex"));
//    CCLOG("%d",array->getJsonArray(0)->getInt("id"));
  

    
    SkeletalArray* dateArray = SkeletalArray::getInstence();
    dateArray->loadData(root, "bianfu");
    
    BaseObject * baseObject = new BaseObject("bianfu");
    this->addChild(baseObject);
    
    baseObject->runSkeletalAction("walk");
    baseObject->runSkeletalAction("run");
    baseObject->runSkeletalAction("walk");
    baseObject->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    JSONArray* array1= array->getJsonArray("pic");
//    if (array == NULL) {
//        CCLOG("NONE");
//    }
//    if (array1 == NULL) {
//        CCLOG("NONE 1");
//    }
//    CCLOG("length is %d",array1->getInt(0));
    
//    std::string filePath = FileUtils::getInstance()->fullPathForFilename("Action.json");
//    std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
//    
//    
//    rapidjson::Document _doc;
//    
// 
//    _doc.Parse<0>(contentStr.c_str());
//    if (_doc.HasParseError()) {
//        CCLOG("GetParseError %s\n",_doc.GetParseError());
//    }
//    rapidjson::Value & parr =_doc;
//    int i = 0;
//    rapidjson::Value & parr1 =parr["player"];
//    CCLOG("%d",parr1.Size());
//    if (parr1.Size()) {
//        CCLOG("asdf");
//    }
//    rapidjson::Document d1;
//    d1.SetObject();
//    rapidjson::Document::AllocatorType& allocator = d1.GetAllocator();
//    rapidjson::Value array(rapidjson::kArrayType);
//    rapidjson::Value object(rapidjson::kObjectType);
    
    
//    object.AddMember("id", "1", allocator);
//    object.AddMember("name", "234", allocator);
//    object.AddMember("年龄", "111", allocator);
//    array.PushBack(object, allocator);
//    d1.AddMember("propety", "PLAYER-TO", allocator);
//    d1.AddMember("player", array, allocator);
//    
//    rapidjson::StringBuffer buffer;
//    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
//    d1.Accept(write);
//    
//    StringUtils::format("%s",buffer.GetString());
//    
//    CCLOG(buffer.GetString());
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
