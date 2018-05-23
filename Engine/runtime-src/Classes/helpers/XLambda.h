#ifndef __ScriptLambdaWrapper_H__
#define __ScriptLambdaWrapper_H__

#include "CCLuaValue.h"
#include "cocos2d.h"

USING_NS_CC;

class XLambda : public Ref
 {
protected:
	XLambda();
public:
	virtual ~XLambda()	override;

	virtual void begin() = 0;
	virtual void pushInt(int val) = 0;
	virtual void pushFloat(float val) = 0;
	virtual void pushString(const char* ch) = 0;
	virtual void pushObject(Ref* objectValue, const char* typeName) = 0;
	virtual void pushValueMap(const ValueMap* dict) = 0;
	virtual void cleanup() = 0;
	virtual int  invoke() = 0;

	static unsigned int s_lambda_count;
};

class XLambdaHolder
{
protected:
	XLambdaHolder()	{};
	XLambdaHolder(XLambda* lambda);
public:
	~XLambdaHolder();
	static std::shared_ptr<XLambdaHolder> create(XLambda* lambda);
	XLambda* getLambda(void)	{ return m_lambda; }
protected:
	XLambda*	m_lambda;
};

class XLambdaLua : public XLambda
{
protected:
	XLambdaLua();
public:
	virtual ~XLambdaLua() override;
	
	static XLambdaLua* create(LUA_FUNCTION handle);

	virtual void begin() override;
	virtual void pushInt(int val) override;
	virtual void pushFloat(float val) override;
	virtual void pushString(const char* ch) override;
	virtual void pushObject(Ref* objectValue, const char* typeName) override;
	virtual void pushValueMap(const ValueMap* dict) override;
	virtual void cleanup() override;
	virtual int invoke() override;

	static void init();
	static void fini();
private:
	void setLambda(LUA_FUNCTION handle);
	LUA_FUNCTION		m_handle;
	unsigned int		m_argCount;
	bool				m_bBegined;
};

typedef std::shared_ptr<XLambdaHolder> XLambdaHolderPtr;

#endif