//
// OpenGLScene.cpp
// MyCppGame
//
// Created by ly on 15-1-2.
//
//

#include "OpenGLScene.h"
OpenGLScene::OpenGLScene()
{
    
}

OpenGLScene::~OpenGLScene()
{
    
}

Scene* OpenGLScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OpenGLScene::create();
    scene->addChild(layer);
    return scene;
}

bool OpenGLScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initData();
    return true;
}

#pragma mark - initData
void OpenGLScene::initData()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

    // add your codes here...
    
}
void OpenGLScene::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    Layer::draw(renderer, transform, flags);
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(OpenGLScene::onDraw, this);
    renderer->addCommand(&_customCommand);
}
void OpenGLScene::onDraw(){
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins();

    auto size = Director::getInstance()->getWinSize();
//    glBindVertexArray(vao);
//    GLuint uColorLocation = glGetUniformLocation(glProgram->getProgram(), "u_color");
    
    float vertercies[] = { 0,0,   //第一个点的坐标
        size.width, 0,   //第二个点的坐标
        size.width / 2, size.height};  //第三个点的坐标
    //指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
    float color[] = { 0, 1,0, 1,    //第一个点的颜色，绿色
        1,0,0, 1,  //第二个点的颜色, 红色
        0, 0, 1, 1};  //第三个点的颜色， 蓝色
//    glUniform4fv(uColorLocation, 1, color);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    //分别给position和color指定数据源
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
//    glBindVertexArray(0);
//    
//    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
//    CHECK_GL_ERROR_DEBUG();
    
//    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    

    
}
