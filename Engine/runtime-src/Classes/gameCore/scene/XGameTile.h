#ifndef __ZX_GAME_TILE_H_
#define __ZX_GAME_TILE_H_

#include "cocos2d.h"
#include "supports/XResource/XAsyncLoaderCallbacks.h"

USING_NS_CC;

struct SVec2
{
	unsigned short x, y;
};

class XGameTile : public Sprite
{
	// cocos不允许我用
	XGameTile();
public:
	~XGameTile();

	static XGameTile* create();

	// 异步加载后的回调函数
	void		onTextureAsyncLoad(const XAsyncLoaderRet* ret);

	void		loadAsync(const std::string&filename);

	virtual void cleanup() override;

	void		resetTile();

	void		setXQuad(const V3F_C4B_T2F_Quad& quad)
	{
		_quad = quad;
	}

protected:
	static void OnFinish(void * pContext, void * pData, int nDataLength);
	void _OnFinish(void * pData, int nDataLength);

	bool OnCreate();
	bool					m_bCreated;
	Texture2D				m_tex;		// 贴图
	std::string				m_strTextureName;
	SVec2					m_position;
	unsigned short			m_nId;

	friend class XSceneTileLayer;

	CC_DISALLOW_COPY_AND_ASSIGN(XGameTile);

	unsigned int			m_nLoadHandle;

	XAsyncLoaderCallback*	m_pkLoadCallback;
};



#endif