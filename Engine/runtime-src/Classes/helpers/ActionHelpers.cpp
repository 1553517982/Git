#include "ActionHelpers.h"
#include "XCommon.h"

ActionInterval* ActionHelpers::moveTo(float sx, float sy, float tx, float ty, float time, int tag)
{
	Vec2 from = Vec2(sx, sy);
	Vec2 to = Vec2(tx, ty);
	ActionInterval* pkAction = MoveTo::create(time, to);
	pkAction->setTag(tag);
	return pkAction;
}

FiniteTimeAction* ActionHelpers::removeWhenActionFinish(FiniteTimeAction* action, float delay, float fadeOut)
{
	if (!action)
		return NULL;

	Vector<FiniteTimeAction*> cSequenceArray;
	FiniteTimeAction* _removeSelf = RemoveSelf::create(true);
	cSequenceArray.pushBack(action);
	if (delay > 0)
	{
		cSequenceArray.pushBack(DelayTime::create(delay));
	}
	if (fadeOut > 0)
	{
		cSequenceArray.pushBack(FadeOut::create(fadeOut));
	}
	cSequenceArray.pushBack(_removeSelf);
	return Sequence::create(cSequenceArray);
}
Action* ActionHelpers::removeWhenTimelineFinish(cocostudio::timeline::ActionTimeline* action)
{
	if (action)
	{
		action->clearFrameEventCallFunc();
		action->setLastFrameCallFunc([action](void)
		{
			auto target = action->getTarget();
			FiniteTimeAction* _removeSelf = RemoveSelf::create(true);
			target->runAction(_removeSelf);
		});
	}
	return action;
}

Action* ActionHelpers::removeWhenTimelineFinish(cocostudio::timeline::ActionTimeline* action, float delay, float fadeOut)
{
	if (action)
	{
		action->clearFrameEventCallFunc();
		action->setLastFrameCallFunc([action, delay, fadeOut](void)
		{
			auto target = action->getTarget();
			FiniteTimeAction* _removeSelf = RemoveSelf::create(true);
			if (delay > 0 || fadeOut > 0)
			{
				Vector<FiniteTimeAction*> cSequenceArray;
				if (delay > 0)
				{
					cSequenceArray.pushBack(DelayTime::create(delay));
				}
				if (fadeOut > 0)
				{
					cSequenceArray.pushBack(FadeOut::create(fadeOut));
				}
				auto seq = Sequence::create(cSequenceArray);
				target->runAction(seq);
			}
			else
			{
				target->runAction(_removeSelf);
			}
		});
	}
	return action;
}

FiniteTimeAction* ActionHelpers::delayRemove(float delay)
{
	return Sequence::create(DelayTime::create(delay), RemoveSelf::create(true));
}

FiniteTimeAction* ActionHelpers::delayFadoutRemove(float delay, float fadeOut)
{
	Vector<FiniteTimeAction*> cSequenceArray;
	if (delay > 0)
	{
		cSequenceArray.pushBack(DelayTime::create(delay));
	}
	cSequenceArray.pushBack(FadeOut::create(fadeOut));
	cSequenceArray.pushBack(RemoveSelf::create(true));
	return Sequence::create(cSequenceArray);
}

FiniteTimeAction* ActionHelpers::delayEaseInFadoutRemove(float delay, float ease, float fadeOut)
{
	Vector<FiniteTimeAction*> cSequenceArray;
	if (delay > 0)
	{
		cSequenceArray.pushBack(DelayTime::create(delay));
	}
	cSequenceArray.pushBack(EaseIn::create(FadeOut::create(fadeOut), ease));
	cSequenceArray.pushBack(RemoveSelf::create(true));
	return Sequence::create(cSequenceArray);
}

FiniteTimeAction* ActionHelpers::delayEaseOutFadoutRemove(float delay, float ease, float fadeOut)
{
	Vector<FiniteTimeAction*> cSequenceArray;
	if (delay > 0)
	{
		cSequenceArray.pushBack(DelayTime::create(delay));
	}
	cSequenceArray.pushBack(EaseOut::create(FadeOut::create(fadeOut), ease));
	cSequenceArray.pushBack(RemoveSelf::create(true));
	return Sequence::create(cSequenceArray);
}



FiniteTimeAction* ActionHelpers::delayFadeIn(float delay, float fadeIn)
{
	if (delay > 0)
	{
		return Sequence::create(DelayTime::create(delay), FadeIn::create(fadeIn));
	}
	else
	{
		return FadeIn::create(fadeIn);
	}
}

FiniteTimeAction* ActionHelpers::delayEaseInFadeIn(float delay, float ease, float fadeIn)
{
	auto _fadeIn = EaseIn::create(FadeIn::create(fadeIn), ease);
	if (delay > 0)
		return Sequence::create(DelayTime::create(delay), _fadeIn);
	else
		return _fadeIn;
}

FiniteTimeAction* ActionHelpers::delayEaseOutFadeIn(float delay, float ease, float fadeIn)
{
	auto _fadeIn = EaseOut::create(FadeIn::create(fadeIn), ease);
	if (delay > 0)
		return Sequence::create(DelayTime::create(delay), _fadeIn);
	else
		return _fadeIn;
}

FiniteTimeAction* ActionHelpers::easeElasticInScale(float sx, float sy, float time, float ease)
{
	return EaseElasticIn::create(ScaleTo::create(time, sx, sy));
}

FiniteTimeAction* ActionHelpers::easeElasticOutScale(float sx, float sy, float time, float ease)
{
	return EaseElasticOut::create(ScaleTo::create(time, sx, sy));
}