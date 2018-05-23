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

// plish、csb等文件因为文件小，所以直接使用同步加载，所以外部也用同步的函数，即syncload*** ，所以规定这些小文件必须打包并处理好
// 图片等大型文件，则采用异步加载，所以外部也是用异步的函数，即asyncload***，所以这些小文件只能单文件处理
class CPackFile;

struct SFileData
{
	CPackFile * pPackFile;
	unsigned int nDataOffiset;
	unsigned int nDataLength;
};

// VS2013的一个严重bug，我搞一个CNewLoader的文件，他居然会出现PDB无法写入的错误。。。

class CC_STUDIO_DLL CNewLoader
{
protected:
	CNewLoader();
	~CNewLoader();

public:


	// edited by aXing on 2017-9-26
	// 把读取改为分段，所以弃用这个接口，重新写一个
	void ReloadPack();

	// 清除以前读取的脚本
	void clearPack();

	typedef void(*OnFinish)(void * pContext, void * pData, int nDataLength);

	static CNewLoader & Inst();
	static void OnEnd();

	// 加载资源名字文件 -- 废弃 by aXing on 2017-3-24
	bool LoadResource(const char * pResFile);

	// 加载资源名字文件 -- 从2017-3-24启用
	bool LoadResrouceTab(const char * pResFile);

	// 加载动作类文件 -- 从2017-3-24启用
	bool LoadAnimationTab(const char * pResFile);

	// 加载边玩边下载文件 extend.m -- 从2017-5-19 启用
	bool LoadMD5Tab(const char * pResFile);

	// 加载异步资源的md5码表

	// 读取资源文件名字，即原来的depen，现在改成 名称 ： 对应资源
	std::list<std::string> * LoadResDepenence(const char * pResFile);

	// 同步加载文件包，用于res中的Config包、UI包及代码包。
	bool SyncLoadConfigPack(const char * pConfigFile);

	// 加载文件包，用于地图包，人物包及特效包
	// 由于有些情况需要知道文件大小什么的，所以只异步加载贴图
	//bool AsyncLoadConfigPack(const char * pConfigFile);

	// 加载plist、csb、tab等小型文件
	bool SyncLoadFile(const char * pConfigFile, char ** pData, unsigned int * pLength);

	// 加载图片，返回一个handle
	unsigned int AsyncLoadTex(const char * pTex, void * pContext, OnFinish fun);

	// 停止异步加载，使用返回的handle
	void StopLoad(unsigned int handle);

	void saveKey(const char * pKey, const char * pValue);

	const char * loadKey(const char * pKey);

	// 加一个接口，从http处下载到图片回调到这里
	void OnHttpLoad(std::string strFile, void * pData, int nSize);

	// 保存key文件及MD5
	void SaveKeyAndMD5();

	// 解开密码
	void Decode(unsigned char * pSrc, int nSrcSize, int nOffiset);

	// 如果加载失败则回调出去通知一下的函数
	void RegistFailLoadCallBack(Fun fun);

	// 查询是否有这个文件
	bool IsHasFile(std::string &);

	bool LoadOutSideLua(std::string & file, char ** pData, unsigned int * pLength);

private:
	// 加载资源文件名字用，即resource.tab文件
	std::map< std::string, std::list<std::string> > m_ResMap;
	// 真机中可以支持多个
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

	////保存数据用的
	std::map<std::string, std::string> m_saveKey;

	void SaveKey();
	void LoadSaveKey();

	// 线程安全
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
		unsigned int nSize;	// 如果是0xFFFFFFFF则表示挂起
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
	// 用于记录sd卡路径，只有安卓会有
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

	bool m_bNeedSaveKey; // 纯粹避免重复做

	Fun m_fun;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CSLoader__) */
