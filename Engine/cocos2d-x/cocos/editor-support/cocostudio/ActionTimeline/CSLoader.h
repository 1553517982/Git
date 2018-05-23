/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __cocos2d_libs__CSLoader__
#define __cocos2d_libs__CSLoader__

#include "cocostudio/DictionaryHelper.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocos2d.h"
#include "base/ObjectFactory.h"

#define BASE_COMPRESS_SIGN ("COMP")
#define BASE_COMPRESS_LEN (4)
typedef void(*Fun)(std::string &);

namespace flatbuffers
{
    class FlatBufferBuilder;
    
    struct NodeTree;
    
    struct WidgetOptions;
    struct SingleNodeOptions;
    struct SpriteOptions;
    struct ParticleSystemOptions;
    struct TMXTiledMapOptions;
    struct ProjectNodeOptions;
    
    struct ComponentOptions;
    struct ComAudioOptions;
}

namespace cocostudio
{
    class ComAudio;
}

namespace cocostudio
{
    namespace timeline
    {
        class ActionTimeline;
        class ActionTimelineNode;
    }
}

NS_CC_BEGIN

typedef std::function<void(Ref*)> ccNodeLoadCallback;

class CC_STUDIO_DLL CSLoader
{
public:
    static CSLoader* getInstance();
    static void destroyInstance();
    
    CSLoader();
    /** @deprecated Use method destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE void purge();    
    
    void init();
    
    static cocos2d::Node* createNode(const std::string& filename);
    static cocos2d::Node* createNode(const std::string& filename, const ccNodeLoadCallback& callback);
    static cocostudio::timeline::ActionTimeline* createTimeline(const std::string& filename);

    /*
    static cocostudio::timeline::ActionTimelineNode* createActionTimelineNode(const std::string& filename);
    static cocostudio::timeline::ActionTimelineNode* createActionTimelineNode(const std::string& filename, int startIndex, int endIndex, bool loop);
     */
    
    cocos2d::Node* createNodeFromJson(const std::string& filename);
    cocos2d::Node* loadNodeWithFile(const std::string& fileName);
    cocos2d::Node* loadNodeWithContent(const std::string& content);
    
    void setRecordJsonPath(bool record) { _recordJsonPath = record; }
    bool isRecordJsonPath() const { return _recordJsonPath; }
    
    void setJsonPath(std::string jsonPath) { _jsonPath = jsonPath; }
    std::string getJsonPath() const { return _jsonPath; }
    
    cocos2d::Node* createNodeWithFlatBuffersFile(const std::string& filename);
    cocos2d::Node* nodeWithFlatBuffersFile(const std::string& fileName);
    cocos2d::Node* nodeWithFlatBuffers(const flatbuffers::NodeTree* nodetree);
    
    bool bindCallback(const std::string& callbackName,
                      const std::string& callbackType,
                      cocos2d::ui::Widget* sender,
                      cocos2d::Node* handler);
    
    void registReaderObject(const std::string& className,
                            ObjectFactory::Instance ins);                         
    
    cocos2d::Node* createNodeWithFlatBuffersForSimulator(const std::string& filename);
    cocos2d::Node* nodeWithFlatBuffersForSimulator(const flatbuffers::NodeTree* nodetree);

protected:

    cocos2d::Node* createNodeWithFlatBuffersFile(const std::string& filename, const ccNodeLoadCallback& callback);
    cocos2d::Node* nodeWithFlatBuffersFile(const std::string& fileName, const ccNodeLoadCallback& callback);
    cocos2d::Node* nodeWithFlatBuffers(const flatbuffers::NodeTree* nodetree, const ccNodeLoadCallback& callback);
    
    cocos2d::Node* loadNode(const rapidjson::Value& json);
    
    void locateNodeWithMulresPosition(cocos2d::Node* node, const rapidjson::Value& json);
    
    void initNode(cocos2d::Node* node, const rapidjson::Value& json);
    
    // load nodes
    cocos2d::Node* loadSimpleNode(const rapidjson::Value& json);
    cocos2d::Node* loadSubGraph  (const rapidjson::Value& json);
    cocos2d::Node* loadSprite    (const rapidjson::Value& json);
    cocos2d::Node* loadParticle  (const rapidjson::Value& json);
    cocos2d::Node* loadTMXTiledMap(const rapidjson::Value& json);
    
    // load gui
    cocos2d::Node* loadWidget(const rapidjson::Value& json);
    
    // load component
    cocos2d::Component* loadComponent(const rapidjson::Value& json);
    cocos2d::Component* loadComAudio(const rapidjson::Value& json);
    
    bool isWidget(const std::string& type);
    bool isCustomWidget(const std::string& type);
    
    std::string getGUIClassName(const std::string &name);
    std::string getWidgetReaderClassName(cocos2d::ui::Widget *widget);
    
    typedef std::function<cocos2d::Node*(const rapidjson::Value& json)> NodeCreateFunc;
    typedef std::pair<std::string, NodeCreateFunc> Pair;
    
    std::unordered_map<std::string, NodeCreateFunc> _funcs;
    
    typedef std::function<cocos2d::Component*(const rapidjson::Value& json)> ComponentCreateFunc;
    typedef std::pair<std::string, ComponentCreateFunc> ComponentPair;
    
    std::unordered_map<std::string, ComponentCreateFunc> _componentFuncs;
    
    bool _recordJsonPath;
    
    std::string _jsonPath;
    
    std::string _monoCocos2dxVersion;
    
    Node* _rootNode;
    cocos2d::Vector<cocos2d::Node*> _callbackHandlers;
    
    std::string _csBuildID;
    
};

#include <string>
#include <list>
#include <map>

// plish��csb���ļ���Ϊ�ļ�С������ֱ��ʹ��ͬ�����أ������ⲿҲ��ͬ���ĺ�������syncload*** �����Թ涨��ЩС�ļ��������������
// ͼƬ�ȴ����ļ���������첽���أ������ⲿҲ�����첽�ĺ�������asyncload***��������ЩС�ļ�ֻ�ܵ��ļ�����
class CPackFile;

struct SFileData
{
	CPackFile * pPackFile;
	unsigned int nDataOffiset;
	unsigned int nDataLength;
};

// VS2013��һ������bug���Ҹ�һ��CNewLoader���ļ�������Ȼ�����PDB�޷�д��Ĵ��󡣡���

class CC_STUDIO_DLL CNewLoader
{
protected:
	CNewLoader();
	~CNewLoader();

public:


	// edited by aXing on 2017-9-26
	// �Ѷ�ȡ��Ϊ�ֶΣ�������������ӿڣ�����дһ��
	void ReloadPack();

	// �����ǰ��ȡ�Ľű�
	void clearPack();

	typedef void(*OnFinish)(void * pContext, void * pData, int nDataLength);

	static CNewLoader & Inst();
	static void OnEnd();

	// ������Դ�����ļ� -- ���� by aXing on 2017-3-24
	bool LoadResource(const char * pResFile);

	// ������Դ�����ļ� -- ��2017-3-24����
	bool LoadResrouceTab(const char * pResFile);

	// ���ض������ļ� -- ��2017-3-24����
	bool LoadAnimationTab(const char * pResFile);

	// ���ر���������ļ� extend.m -- ��2017-5-19 ����
	bool LoadMD5Tab(const char * pResFile);

	// �����첽��Դ��md5���

	// ��ȡ��Դ�ļ����֣���ԭ����depen�����ڸĳ� ���� �� ��Ӧ��Դ
	std::list<std::string> * LoadResDepenence(const char * pResFile);

	// ͬ�������ļ���������res�е�Config����UI�����������
	bool SyncLoadConfigPack(const char * pConfigFile);

	// �����ļ��������ڵ�ͼ�������������Ч��
	// ������Щ�����Ҫ֪���ļ���Сʲô�ģ�����ֻ�첽������ͼ
	//bool AsyncLoadConfigPack(const char * pConfigFile);

	// ����plist��csb��tab��С���ļ�
	bool SyncLoadFile(const char * pConfigFile, char ** pData, unsigned int * pLength);

	// ����ͼƬ������һ��handle
	unsigned int AsyncLoadTex(const char * pTex, void * pContext, OnFinish fun);

	// ֹͣ�첽���أ�ʹ�÷��ص�handle
	void StopLoad(unsigned int handle);

	void saveKey(const char * pKey, const char * pValue);

	const char * loadKey(const char * pKey);

	// ��һ���ӿڣ���http�����ص�ͼƬ�ص�������
	void OnHttpLoad(std::string strFile, void * pData, int nSize);

	// ����key�ļ���MD5
	void SaveKeyAndMD5();

	// �⿪����
	void Decode(unsigned char * pSrc, int nSrcSize, int nOffiset);

	// �������ʧ����ص���ȥ֪ͨһ�µĺ���
	void RegistFailLoadCallBack(Fun fun);

	// ��ѯ�Ƿ�������ļ�
	bool IsHasFile(std::string &);

	bool LoadOutSideLua(std::string & file, char ** pData, unsigned int * pLength);

private:
	// ������Դ�ļ������ã���resource.tab�ļ�
	std::map< std::string, std::list<std::string> > m_ResMap;
	// ����п���֧�ֶ��
#ifdef RAYMOND_PACK_DEBUG
	std::vector< CPackFile * > m_PackFileVec;
#else
	CPackFile * m_pPackFile;
#endif

	friend class CPackFile;
	typedef std::map< std::string, SFileData > FileMap;
	FileMap m_FileMap;
private:
	std::mutex m_ioMutex;
	void OnThreadStart();

	////���������õ�
	std::map<std::string, std::string> m_saveKey;

	void SaveKey();
	void LoadSaveKey();

	// �̰߳�ȫ
	bool m_bIsThreadOpen;
	bool m_bIsOpenSche;
	unsigned int m_nTickHandle;

	struct SLoadStruct
	{
		std::string strTex;
		std::string strFullTex;
		void * pContext;
		OnFinish fun;
		void * pLoadData;
		unsigned int nSize;	// �����0xFFFFFFFF���ʾ����
		~SLoadStruct()
		{
			if (pLoadData)
				free(pLoadData);
		}
	};

	typedef std::map< unsigned int, SLoadStruct > LoadMap;
	LoadMap m_LoadMap;

	static void OnTick(float);
	void _OnTick(float);

#if ( defined (ANDROID) && defined (COCOS2D_DEBUG) )
	// ���ڼ�¼sd��·����ֻ�а�׿����
	std::string m_strSDCardPath;
#endif

public:
	//typedef std::map< std::string, std::string > MD5Map;
	//static std::string LoadMD5ByData(unsigned char * pData, int nDataSize, MD5Map & md5m);

#ifdef RAYMOND_PACK_DEBUG
	std::map< std::string, SFileData * > & GetUIFileData();

	void GetDataByFData(SFileData *, char ** pData, unsigned int * pLength);
#endif

private:

	std::string m_strWriteAblePath;

	static CNewLoader * s_loader;

	bool m_bNeedSaveKey; // ��������ظ���

	Fun m_fun;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CSLoader__) */
