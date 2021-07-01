#include "UIMessage.h"

void UIMessage::displayUIMessage(float x, float y, float fx, float fy, std::string message, float ttl, CCLayer* current_layer)
{
	current_layer->removeChild(current_layer->getChildByTag(102));
	current_layer->removeChild(current_layer->getChildByTag(101));

	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //get current window size
	CCLabelTTF* messageLabel = CCLabelTTF::create(message.c_str(), "Impact", 28);
	messageLabel->setPosition(ccp(x,y));
	messageLabel->setColor(ccc3(165,42,42));

	CCSprite* message_layer_background = CCSprite::create("messagebox.png");
	//message_layer_background->setAnchorPoint(ccp(0.1,-5.9));
	message_layer_background->setPosition(ccp(x,y));
	current_layer->addChild(message_layer_background,110,102);
	current_layer->addChild(messageLabel,111,101);
}

void UIMessage::displayUIMessage(float x, float y, float fx, float fy, std::string message, float ttl, CCLayer* current_layer, int id)
{
	current_layer->removeChild(current_layer->getChildByTag(id));
	current_layer->removeChild(current_layer->getChildByTag(id+1));

	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //get current window size
	CCLabelTTF* messageLabel = CCLabelTTF::create(message.c_str(),"Impact",28);
	messageLabel->setPosition(ccp(x,y));
	messageLabel->setColor(ccc3(165,42,42));

	CCSprite* message_layer_background = CCSprite::create("messagebox.png");
	//message_layer_background->setAnchorPoint(ccp(0.1,-5.9));
	message_layer_background->setPosition(ccp(x,y));

	current_layer->addChild(message_layer_background,110,id+1);
	current_layer->addChild(messageLabel,111,id);
}

void UIMessage::removeMessageID(int id, CCLayer* current_layer)
{
	current_layer->removeChild(current_layer->getChildByTag(id));
	current_layer->removeChild(current_layer->getChildByTag(id+1));
}