
#ifndef __XResourceDataBase__
#define __XResourceDataBase__
#include "cocos2d.h"
#include <vector.h>
#include "XResource/XAsyncLoaderCallbacks.h"

enum XResouceDataTypes
{
	eResTypeFile,
	eResTypeImage,
	eResTypePlist,
	eResTypeFrame,
	eResTypeZip
};

typedef std::list<std::string>				tNameList;
typedef std::map<std::string, tNameList*>	tDependMap;


class XResouceData
{
public:
	XResouceData()	{};
	~XResouceData() {};
	std::string		m_strFilename;
	int				m_nType;
};
typedef std::vector<XResouceData*>					tResourceDataVector;
typedef std::map<std::string, tResourceDataVector*>	tResourceDataVectorMap;


class XResouceGroup
{
public:
	XResouceGroup();

	~XResouceGroup();

	tResourceDataVector* getResource();

private:
	tResourceDataVector m_resources;
};

typedef std::map<std::string, XResouceGroup*>	tDependGroupMap;

class XResourceDataBase
{
public:
	XResourceDataBase();
	~XResourceDataBase();
	bool loadDependency(const std::string& filename);
	bool loadConfig(const std::string& filename);

	//tNameList*	   getDependency(const std::string& filename);
	XResouceGroup* getResourceGroup(const std::string& filename);
	void setResourceGroup(const std::string& filename, XResouceGroup* group);
protected:
	//tDependMap		m_dependencyMap;
	tDependGroupMap	m_dependencyGroups;

};
#endif