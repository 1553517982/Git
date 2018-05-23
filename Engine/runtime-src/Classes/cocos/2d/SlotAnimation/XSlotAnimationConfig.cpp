#include "XSlotAnimationConfig.h"
#include "XFrameTransform.h"
#include "XFrameModifier.h"
#include "XSlotFrames.h"
#include "XCommon.h"

static XSlotAnimationConfig* g_SharedManager = NULL;

enum
{
	eFrameModifierPosX,
	eFrameModifierPosY,
	eFrameModifierZOrder,
	eFrameModifierScaleX,
	eFrameModifierScaleY,
	eFrameModifierRot,
	eFrameModifierSkewX,
	eFrameModifierSkewY,
	eFrameModifierColorRed,
	eFrameModifierColorGreen,
	eFrameModifierColorBlue,
	eFrameModifierOpacity,
	eFrameModifierMax
};

XSlotAnimationConfig::XSlotAnimationConfig()
{
	m_pkAllSlotAnimationDictionary = new tAllSlotAnimations();
}

XSlotAnimationConfig::~XSlotAnimationConfig()
{
	//m_pkEntitySlotDictionary->release();
	clear();
	delete m_pkAllSlotAnimationDictionary;
}

XSlotAnimationConfig* XSlotAnimationConfig::sharedManager()
{
	if(!g_SharedManager)
	{
		g_SharedManager = new XSlotAnimationConfig();
		//g_SharedManager->loadBodyForSlotModifier("frame_modifiers_linking.json");
	}
	return g_SharedManager;
}

void XSlotAnimationConfig :: purgeSharedManager()
{
	CC_SAFE_DELETE(g_SharedManager);
}

static void modifierReader(XFrameModifier* pkFrame, const rapidjson::Value& _frameData)
{
	XAssert(_frameData.IsObject(),"modifierReader _frameData.isObject()");
	XFrameTransform* pkHFrameTransform = new XFrameTransform();
	pkFrame->m_pkXFrameTransform = pkHFrameTransform;
	const rapidjson::Value& _frame_id = _frameData["f"];
	const rapidjson::Value& _modifiers = _frameData["m"];
	if( _frame_id.IsNumber() )
	{
		pkFrame->m_nFrameIndex = _frame_id.GetUint();
	}
	else
	{
		XLOGERROR("modifierReader m_nFrameIndex load failed");
	}
	if( _modifiers.IsArray())
	{
		//if(_frameData.size() >= eFrameModifierOpacity)
		//{
		//	pkColor = new HFrameColor();
		//	//pkHFrameTransform->m_pkColor = pkColor;
		//}

		for( unsigned int i = 0 ; i< _modifiers.Size(); i++)
		{
			const rapidjson::Value& _value = _modifiers[i];
			switch(i)
			{
			case eFrameModifierPosX:
				pkHFrameTransform->m_kPos.x = _value.GetDouble();
				break;

			case eFrameModifierPosY:
				pkHFrameTransform->m_kPos.y = _value.GetDouble();
				break;

			case eFrameModifierZOrder:
				pkHFrameTransform->m_nZOrder = _value.GetDouble();
				break;

			case eFrameModifierScaleX:
				pkHFrameTransform->m_kScale.x = _value.GetDouble();
				break;

			case eFrameModifierScaleY:
				pkHFrameTransform->m_kScale.y = _value.GetDouble();
				break;

			case eFrameModifierRot:
				pkHFrameTransform->m_fRot = _value.GetDouble();
				break;

			case eFrameModifierSkewX:
				pkHFrameTransform->m_kSkew.x = _value.GetDouble();
				break;

			case eFrameModifierSkewY:
				pkHFrameTransform->m_kSkew.y = _value.GetDouble();
				break;

			/*
			case eFrameModifierColorRed:
				if(pkColor)
					pkColor->m_kColor.r = _value.asUInt();
				break;

			case eFrameModifierColorGreen:
				if(pkColor)
					pkColor->m_kColor.g = _value.asUInt();
				break;

			case eFrameModifierColorBlue:
				if(pkColor)
					pkColor->m_kColor.b = _value.asUInt();
				break;

			case eFrameModifierOpacity:
				if(pkColor)
					pkColor->m_uOpacity = _value.asUInt();
				break;
				*/
			}
		}
	}
	else
	{
		XLOGERROR("modifierReader modifier load failed");
	}
}

static void modifierDictReader(tXFrameModifierMap* pkSlotModifierMap, const rapidjson::Value& _frameData)
{
	for (auto iter = _frameData.MemberBegin();
		iter != _frameData.MemberEnd();
		iter ++)
	{
		std::string jkey = iter->name.GetString();
		const rapidjson::Value& _slotInfo = iter->value;
		unsigned int key = atoi(jkey.c_str());
		XFrameModifier* pkFrame = XFrameModifier::create();
		modifierReader(pkFrame,_slotInfo);
		pkSlotModifierMap->insert(std::make_pair(key,pkFrame));
	}
}

tSlotFrameMap* XSlotAnimationConfig::getSlotFrames(const char* szFilename)
{
	auto iter = m_pkAllSlotAnimationDictionary->find(szFilename);
	if (iter != m_pkAllSlotAnimationDictionary->end())
		return iter->second;
	return loadSlotFrames(szFilename);
}

tSlotFrameMap* XSlotAnimationConfig::loadSlotFrames(const char* szFilename)
{
	std::string strFilename = szFilename;
	strFilename += ".json";

	FileUtils* pkFile = FileUtils::getInstance();
	std::string jsonpath = pkFile->fullPathForFilename(szFilename);
	if (jsonpath.empty())
		return NULL;

	std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);

	tSlotFrameMap* pkInfo = NULL;
	do 
	{
		rapidjson::Document doc;
		doc.Parse<0>(contentStr.c_str());
		if (doc.HasParseError())
		{
			XLOGERROR("XSlotAnimationConfig::loadSlotFrames\n%s\n[error] %s", szFilename, doc.GetParseError());
			break;
		}
		rapidjson::Value& root = doc;

		pkInfo = new tSlotFrameMap();
		//获取所有的modifier
		for( auto iter = root.MemberBegin();
			iter != root.MemberEnd();
			iter++ )
		{
			//获得slot
			std::string _slotName = iter->name.GetString();
			const rapidjson::Value& _slotInfo= iter->value;

			tXFrameModifierMap* pkFrames = new tXFrameModifierMap();
			XSlotFrames* pkAction = XSlotFrames::create(pkFrames);
			//frameReader(pkFrames,_frames);
			modifierDictReader(pkFrames,_slotInfo);
			//slotReader(pkAction,_slotInfo);
			//pkInfo->setObject(pkAction,_slotName.asCString());
			//pkInfo->insert(std::make_pair(_slotName, pkAction));
			pkInfo->insert(_slotName, pkAction);
		}
		m_pkAllSlotAnimationDictionary->insert(std::make_pair(szFilename, pkInfo));

	}while (0);

	XAssert(pkInfo,"pkInfo = NULL");
	return pkInfo;
}
void XSlotAnimationConfig::clear()
{
	for (auto it = m_pkAllSlotAnimationDictionary->begin(); it != m_pkAllSlotAnimationDictionary->end(); it++)
	{
		tSlotFrameMap* subMap = it->second;
		subMap->clear();
		delete it->second;
	}
	m_pkAllSlotAnimationDictionary->clear();
}