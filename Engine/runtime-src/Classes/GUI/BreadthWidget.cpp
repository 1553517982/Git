#include <queue>
#include "base/CCDirector.h"
#include "BreadthWidget.h"

USING_NS_CC;

BreadthWidget::BreadthWidget(void)
{

}

BreadthWidget::~BreadthWidget(void)
{

}

BreadthWidget* BreadthWidget::create()
{
	BreadthWidget* widget = new (std::nothrow) BreadthWidget();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

void BreadthWidget::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// quick return if not visible. children won't be drawn.
	if (!_visible || !isVisitableByVisitingCamera())
	{
		return;
	}

	uint32_t flags = processParentFlags(parentTransform, parentFlags);

	// IMPORTANT:
	// To ease the migration to v3.0, we still support the Mat4 stack,
	// but it is deprecated and your code should not rely on it
	//Director* director = Director::getInstance();
	//CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	//director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	//director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

	// 先儿子按深度排序,因为广度遍历也是需要儿子排序好了，才开始做的
//	sortAllChildren();
//	sortAllProtectedChildren();

	// 然后从这里开始儿子广度遍历
	std::queue<Node*> nodeQueue;
	nodeQueue.push(this);
	
	while (!nodeQueue.empty())
	{
		auto node = nodeQueue.front();
		nodeQueue.pop();
		
		//
		// draw self
		//
		if (node->isVisible())
		{
//			node->adaptRenderers();

//			uint32_t flags = processParentFlags(parentTransform, parentFlags);
			cocos2d::Mat4 transform = node->getNodeToParentTransform() * parentTransform;

			// IMPORTANT:
			// To ease the migration to v3.0, we still support the Mat4 stack,
			// but it is deprecated and your code should not rely on it
			Director* director = Director::getInstance();
			CCASSERT(nullptr != director, "Director is null when seting matrix stack");
			director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
			director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

			// 先儿子按深度排序,因为广度遍历也是需要儿子排序好了，才开始做的
			sortAllChildren();
			sortAllProtectedChildren();
			node->draw(renderer, transform, parentFlags);

			director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
		}
			
		
		auto children = node->getChildren();
		for (auto it = children.cbegin(); it != children.cend(); ++it)
			//(*it)->visit(renderer, transform, flags);
			nodeQueue.push((*it));

	}
}