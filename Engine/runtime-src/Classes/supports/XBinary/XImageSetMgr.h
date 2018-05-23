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
		 *  @brief ��ȡ����������
		 *  @return XImageSetMgr*
		*/
		//static XImageSetMgr*	sharedManager();

		/** 
		 *  
		 *  @brief ����ͼԪ������
		 *  @return void
		*/
		//static void purgeManager();

		/** 
		 *  
		 *  @brief Ԥ����ͼԪ
		 *  @param const char * filename
		 *  @return bool
		*/
		bool loadImageSet(const char* filename);

		/** 
		 *  
		 *  @brief Ԥ����֡ͼԪ����������һ���ģ�ֻ���������֡Ŀ¼�ϲ����б�������ն��
		 *  @param const char * filename
		 *  @return bool
		*/
		bool loadFrameSet(const char* filename);

		//���Ҿ�֡
		/** 
		 *  
		 *  @brief ����֡
		 *  @param const char * szName
		 *  @param bool bCreateWhenNotFound Ĭ�϶���true����˼���Ҳ����ͳ��Դ�ɢͼ�����ң�������ʧ�ܣ���Ϊ������һ������������
		 *  @return XImageUnit*
		*/
		XImageUnit* findImageUnit(const char* szName, bool bCreateWhenNotFound = true);


		/** 
		 *  
		 *  @brief ��ȡ����֡�б�
		 *  @param const char * animationName
		 *  @return XFrameList*
		*/
		XFrameList*	getFrameList(const char *animationName);


		/** 
		 *  
		 *  @brief ��ݷ�������new CCSprite
		 *  @param const char * szName
		 *  @return CCSprite*
		*/
		Sprite* Sprite_createWithImagetUnit(const char* szName);

		/** 
		 *  
		 *  @brief ��ݷ�������new CCSpriteFrame����ʵ���岻��
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

		//���һ��CCSpriteFrame��shared
		/**
		*
		*  @brief ��ȡһ��CCSpriteFrame�������þ���ȣ�ͬgetCCSpriteFrame
		*  @param const char * szName
		*  @param bool bCreateWhenNotFound
		*  @return CCSpriteFrame*
		*/
		SpriteFrame* getSpriteFrame(const char* szName, bool bCreateWhenNotFound = true);
	
	private:
		/** 
		 *  
		 *  @brief ���
		 *  @return void
		*/
		void  clear();
		//��̬ͼƬ
		XImageSetMap						m_kImageSetMap;				// ԭʼ������Դ
		XImageUnitMap						m_kImagetUnitMap;			// ָ��ԭʼ��Դ�Ŀ��ټ���
		

		XImageUnitMap						m_kTextureMap;				// ȫ����

		XFrameListMap						m_kFrameListMap;			// ���ݶ����ļ�����Ҫ���ټ��������б�
};

NS_CC_END;
#endif