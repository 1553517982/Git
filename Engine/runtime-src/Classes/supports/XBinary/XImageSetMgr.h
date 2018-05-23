#ifndef _X_IMAGESET_MANAGER_H_
#define _X_IMAGESET_MANAGER_H_

#include "cocos2d.h"
#include "XBinary/XImageSet.h"
#include "XBinary/XFrameSet.h"
#include "supports/XResource/XResourceDataBase.h"
NS_CC_BEGIN

class SpriteFrameData : public SpriteFrame
{
public:
	SpriteFrameData();
	~SpriteFrameData();

	bool initWithTexture(Texture2D* pobTexture, const Rect& rect, bool rotated, const Point& offset, const Size& originalSize);
	void clearTexture();
};

class XImageSetMgr
{
	public:
		XImageSetMgr();
		~XImageSetMgr();

		/** 
		 *  
		 *  @brief 获取管理器单例
		 *  @return XImageSetMgr*
		*/
		//static XImageSetMgr*	sharedManager();

		/** 
		 *  
		 *  @brief 销毁图元管理器
		 *  @return void
		*/
		//static void purgeManager();

		/** 
		 *  
		 *  @brief 预加载图元
		 *  @param const char * filename
		 *  @return bool
		*/
		bool loadImageSet(const char* filename);

		/** 
		 *  
		 *  @brief 预加载帧图元，本质上是一样的，只不过会根据帧目录合并成列表，沿用自斩仙
		 *  @param const char * filename
		 *  @return bool
		*/
		bool loadFrameSet(const char* filename);

		//查找静帧
		/** 
		 *  
		 *  @brief 查找帧
		 *  @param const char * szName
		 *  @param bool bCreateWhenNotFound 默认都是true，意思是找不到就尝试从散图里面找，不可能失败，因为我们有一个纹理代表错误
		 *  @return XImageUnit*
		*/
		XImageUnit* findImageUnit(const char* szName, bool bCreateWhenNotFound = true);


		/** 
		 *  
		 *  @brief 获取动画帧列表
		 *  @param const char * animationName
		 *  @return XFrameList*
		*/
		XFrameList*	getFrameList(const char *animationName);


		/** 
		 *  
		 *  @brief 便捷方法用来new CCSprite
		 *  @param const char * szName
		 *  @return CCSprite*
		*/
		Sprite* Sprite_createWithImagetUnit(const char* szName);

		/** 
		 *  
		 *  @brief 便捷方法用来new CCSpriteFrame，其实意义不大
		 *  @param const char * szName
		 *  @return CCSpriteFrame*
		*/
		SpriteFrame* SpriteFrame_createWithImagetUnit(const char* szName);

		//************************************
		// Method:    setCCSpriteTexture
		// FullName:  XImageSetMgr::setCCSpriteTexture
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: CCSprite * pkSprite
		// Parameter: const char * szName
		//************************************
		void setSprite_withFrameName(Sprite* pkSprite, const char* szName );

		//获得一个CCSpriteFrame的shared
		/**
		*
		*  @brief 获取一个CCSpriteFrame用来设置精灵等，同getCCSpriteFrame
		*  @param const char * szName
		*  @param bool bCreateWhenNotFound
		*  @return CCSpriteFrame*
		*/
		SpriteFrame* getSpriteFrame(const char* szName, bool bCreateWhenNotFound = true);
	
	private:
		/** 
		 *  
		 *  @brief 清除
		 *  @return void
		*/
		void  clear();
		//静态图片
		XImageSetMap						m_kImageSetMap;				// 原始数据资源
		XImageUnitMap						m_kImagetUnitMap;			// 指向原始资源的快速检索
		

		XImageUnitMap						m_kTextureMap;				// 全纹理

		XFrameListMap						m_kFrameListMap;			// 根据动画文件夹需要快速检索动画列表
};

NS_CC_END;
#endif