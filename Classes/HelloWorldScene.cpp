#pragma execution_character_set("utf-8")
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
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
    
    visibleSize = Director::getInstance()->getVisibleSize();

	hasStart = false;

	preloadMusic(); // Ԥ������Ч

	addListener();  // ��Ӽ�����
	addBall();    // ���С��

	obstacle = new Obstacle();
	this->addChild(obstacle, 2);

	// update 
	scheduleUpdate();

    return true;
}

void HelloWorld::preloadMusic()
{
}

void HelloWorld::update(float time) {
	static int count = 0;
	obstacle->update();
	count++;
	if (count == 100) {
		obstacle->deleteOne();
		count = 0;
	}
	velocity -= GRAVITY;
	ball->setPositionY(ball->getPositionY() + velocity);
}

void HelloWorld::addListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	log("test");
	static int offsetY = 100;
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) {
		// add an obstacle and a prop
		obstacle->addOne(offsetY);
		addProp(offsetY - 150);
		offsetY += 300;
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		velocity = 5;
	}
}
//������ɫ���Ƿ��Ǻ��ϰ���ײ
bool HelloWorld::onConcactBegin(bool isObstacle, std::string color)
{
	return false;
}

bool HelloWorld::addBall()
{
	ball = Sprite::create("Ball/Ball3.png");
	ball->setScale(0.5f);
	ball->setPosition(Vec2(visibleSize.width / 2, 200));
	ball->setTag(TAG_BALL);
	addChild(ball, 1);
	return true;
}

void HelloWorld::addProp(int offsetY)
{
	auto prop = Sprite::create(IMG_PROP);
	prop->setScale(0.1);
	prop->setPosition(Vec2(visibleSize.width / 2, offsetY));
	prop->setTag(TAG_PROP);
	addChild(prop, 1);
}
