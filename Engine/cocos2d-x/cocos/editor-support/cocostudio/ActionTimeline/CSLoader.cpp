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

#include "CSLoader.h"
#include "FileIO.h"

#include "base/ObjectFactory.h"
#include "base/TableFile/CTableFile.h"

#include "../../cocos/ui/CocosGUI.h"
#include "CCActionTimelineCache.h"
#include "CCActionTimeline.h"
#include "CCActionTimelineNode.h"
#include "../CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/CSParseBinary_generated.h"

#include "cocostudio/WidgetReader/NodeReaderProtocol.h"
#include "cocostudio/WidgetReader/NodeReaderDefine.h"

#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"
#include "cocostudio/WidgetReader/SingleNodeReader/SingleNodeReader.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "cocostudio/WidgetReader/ParticleReader/ParticleReader.h"
#include "cocostudio/WidgetReader/GameMapReader/GameMapReader.h"
#include "cocostudio/WidgetReader/ProjectNodeReader/ProjectNodeReader.h"
#include "cocostudio/WidgetReader/ComAudioReader/ComAudioReader.h"

#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "cocostudio/WidgetReader/CheckBoxReader/CheckBoxReader.h"
#include "cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "cocostudio/WidgetReader/TextReader/TextReader.h"
#include "cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"
#include "cocostudio/WidgetReader/TextAtlasReader/TextAtlasReader.h"
#include "cocostudio/WidgetReader/LoadingBarReader/LoadingBarReader.h"
#include "cocostudio/WidgetReader/SliderReader/SliderReader.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/WidgetReader/ScrollViewReader/ScrollViewReader.h"
#include "cocostudio/WidgetReader/PageViewReader/PageViewReader.h"
#include "cocostudio/WidgetReader/ListViewReader/ListViewReader.h"
#include "cocostudio/WidgetReader/ArmatureNodeReader/ArmatureNodeReader.h"
#include "cocostudio/WidgetReader/UserCameraReader/UserCameraReader.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/util.h"

#include "cocostudio/FlatBuffersSerialize.h"

#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "zlib.h"

#include <fstream>

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
/* peterson */
using namespace flatbuffers;
/**/

NS_CC_BEGIN

static const char* ClassName_Node     = "Node";
static const char* ClassName_SubGraph = "SubGraph";
static const char* ClassName_Sprite   = "Sprite";
static const char* ClassName_Particle = "Particle";
static const char* ClassName_TMXTiledMap = "TMXTiledMap";

static const char* ClassName_Panel      = "Panel";
static const char* ClassName_Button     = "Button";
static const char* ClassName_CheckBox   = "CheckBox";
static const char* ClassName_ImageView  = "ImageView";
static const char* ClassName_TextAtlas  = "TextAtlas";
static const char* ClassName_LabelAtlas = "LabelAtlas";
static const char* ClassName_LabelBMFont= "LabelBMFont";
static const char* ClassName_TextBMFont = "TextBMFont";
static const char* ClassName_Text       = "Text";
static const char* ClassName_LoadingBar = "LoadingBar";
static const char* ClassName_TextField  = "TextField";
static const char* ClassName_Slider     = "Slider";
static const char* ClassName_Layout     = "Layout";
static const char* ClassName_ScrollView = "ScrollView";
static const char* ClassName_ListView   = "ListView";
static const char* ClassName_PageView   = "PageView";
static const char* ClassName_Widget     = "Widget";
static const char* ClassName_Label      = "Label";

static const char* ClassName_ComAudio = "ComAudio";


static const char* NODE        = "nodeTree";
static const char* CHILDREN    = "children";
static const char* CLASSNAME   = "classname";
static const char* FILE_PATH   = "fileName";
static const char* PLIST_FILE  = "plistFile";
static const char* TMX_FILE  = "tmxFile";
static const char* TMX_STRING  = "tmxString";
static const char* RESOURCE_PATH  = "resourcePath";

static const char* COMPONENTS     = "components";
static const char* COMPONENT_TYPE     = "componentType";
static const char* COMPONENT_NAME  = "componentName";
static const char* COMPONENT_ENABLED  = "componentEnabled";
static const char* COMPONENT_AUDIO_FILE_PATH  = "comAudioFilePath";
static const char* COMPONENT_LOOP  = "comAudioloop";

static const char* TAG         = "tag";
static const char* ACTION_TAG  = "actionTag";

static const char* OPTIONS     = "options";

static const char* WIDTH            = "width";
static const char* HEIGHT           = "height";
static const char* X                = "x";
static const char* Y                = "y";
static const char* SCALE_X          = "scaleX";
static const char* SCALE_Y          = "scaleY";
static const char* SKEW_X           = "skewX";
static const char* SKEW_Y           = "skewY";
static const char* ROTATION         = "rotation";
static const char* ROTATION_SKEW_X  = "rotationSkewX";
static const char* ROTATION_SKEW_Y  = "rotationSkewY";
static const char* ANCHOR_X         = "anchorPointX";
static const char* ANCHOR_Y         = "anchorPointY";
static const char* ALPHA            = "opacity";
static const char* RED              = "colorR";
static const char* GREEN            = "colorG";
static const char* BLUE             = "colorB";
static const char* ZORDER           = "ZOrder";
static const char* PARTICLE_NUM     = "particleNum";
static const char* FLIPX            = "flipX";
static const char* FLIPY            = "flipY";
static const char* VISIBLE          = "visible";

static const char* TEXTURES     = "textures";
static const char* TEXTURES_PNG = "texturesPng";

static const char* MONO_COCOS2D_VERSION     = "cocos2dVersion";

#define SAFE_FREE( bu ) { if(bu){ free(bu);bu=0; } }
// CSLoader
static CSLoader* _sharedCSLoader = nullptr;

#define FAIL_LOAD (0xFFFFFFFF)
#define WAIT_FOR_LOAD (0xFFFFFFFE)

CSLoader* CSLoader::getInstance()
{
    if (! _sharedCSLoader)
    {
        _sharedCSLoader = new CSLoader();
        _sharedCSLoader->init();
    }
    
    return _sharedCSLoader;
}

void CSLoader::destroyInstance()
{
	CCLOG("CSLoader::destroyInstance()");


    CC_SAFE_DELETE(_sharedCSLoader);
    ActionTimelineCache::destroyInstance();
}

CSLoader::CSLoader()
: _recordJsonPath(true)
, _jsonPath("")
, _monoCocos2dxVersion("")
, _rootNode(nullptr)
, _csBuildID("2.1.0.0")
{
    CREATE_CLASS_NODE_READER_INFO(NodeReader);
    CREATE_CLASS_NODE_READER_INFO(SingleNodeReader);
    CREATE_CLASS_NODE_READER_INFO(SpriteReader);
    CREATE_CLASS_NODE_READER_INFO(ParticleReader);
    CREATE_CLASS_NODE_READER_INFO(GameMapReader);
    
    CREATE_CLASS_NODE_READER_INFO(ButtonReader);
    CREATE_CLASS_NODE_READER_INFO(CheckBoxReader);
    CREATE_CLASS_NODE_READER_INFO(ImageViewReader);
    CREATE_CLASS_NODE_READER_INFO(TextBMFontReader);
    CREATE_CLASS_NODE_READER_INFO(TextReader);
    CREATE_CLASS_NODE_READER_INFO(TextFieldReader);
    CREATE_CLASS_NODE_READER_INFO(TextAtlasReader);
    CREATE_CLASS_NODE_READER_INFO(LoadingBarReader);
    CREATE_CLASS_NODE_READER_INFO(SliderReader);
    CREATE_CLASS_NODE_READER_INFO(LayoutReader);
    CREATE_CLASS_NODE_READER_INFO(ScrollViewReader);
    CREATE_CLASS_NODE_READER_INFO(PageViewReader);
    CREATE_CLASS_NODE_READER_INFO(ListViewReader);
    
    CREATE_CLASS_NODE_READER_INFO(ArmatureNodeReader);
    CREATE_CLASS_NODE_READER_INFO(UserCameraReader);
}

void CSLoader::purge()
{
}

void CSLoader::init()
{
    using namespace std::placeholders;
    
    _funcs.insert(Pair(ClassName_Node,      std::bind(&CSLoader::loadSimpleNode, this, _1)));
    _funcs.insert(Pair(ClassName_SubGraph,  std::bind(&CSLoader::loadSubGraph,   this, _1)));
    _funcs.insert(Pair(ClassName_Sprite,    std::bind(&CSLoader::loadSprite,     this, _1)));
    _funcs.insert(Pair(ClassName_Particle,  std::bind(&CSLoader::loadParticle,   this, _1)));
    _funcs.insert(Pair(ClassName_TMXTiledMap,  std::bind(&CSLoader::loadTMXTiledMap,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelAtlas,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LabelBMFont,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Panel,     std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Button,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_CheckBox,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ImageView, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextAtlas, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextBMFont,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Text,      std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_LoadingBar,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_TextField, std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Slider,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Layout,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ScrollView,std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_ListView,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_PageView,  std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Widget,    std::bind(&CSLoader::loadWidget,   this, _1)));
    _funcs.insert(Pair(ClassName_Label,     std::bind(&CSLoader::loadWidget,   this, _1)));
    
    _componentFuncs.insert(ComponentPair(ClassName_ComAudio, std::bind(&CSLoader::loadComAudio, this, _1)));
    
}

Node* CSLoader::createNode(const std::string& filename)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    //CCLOG("suffix = %s", suffix.c_str());
    
    CSLoader* load = CSLoader::getInstance();
    
    if (suffix == "csb")
    {
        return load->createNodeWithFlatBuffersFile(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return load->createNodeFromJson(filename);
    }
    
    return nullptr;
}

Node* CSLoader::createNode(const std::string &filename, const ccNodeLoadCallback &callback)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    //CCLOG("suffix = %s", suffix.c_str());
    
    CSLoader* load = CSLoader::getInstance();
    
    if (suffix == "csb")
    {
        return load->createNodeWithFlatBuffersFile(filename, callback);
    }
    
    return nullptr;
}

ActionTimeline* CSLoader::createTimeline(const std::string &filename)
{
    std::string path = filename;
    size_t pos = path.find_last_of('.');
    std::string suffix = path.substr(pos + 1, path.length());
    //CCLOG("suffix = %s", suffix.c_str());
    
    ActionTimelineCache* cache = ActionTimelineCache::getInstance();
    
    if (suffix == "csb")
    {
        return cache->createActionWithFlatBuffersFile(filename);
    }
    else if (suffix == "json" || suffix == "ExportJson")
    {
        return cache->createActionFromJson(filename);
    }
    
    return nullptr;
}

/*
ActionTimelineNode* CSLoader::createActionTimelineNode(const std::string& filename)
{
    Node* root = createNode(filename);
    ActionTimeline* action = createTimeline(filename);
    
    if(root && action)
    {
        root->runAction(action);
        action->gotoFrameAndPlay(0);
    }
    
    ActionTimelineNode* node = ActionTimelineNode::create(root, action);
    return node;
}
ActionTimelineNode* CSLoader::createActionTimelineNode(const std::string& filename, int startIndex, int endIndex, bool loop)
{
    ActionTimelineNode* node = createActionTimelineNode(filename);
    ActionTimeline* action = node->getActionTimeline();
    if(action)
        action->gotoFrameAndPlay(startIndex, endIndex, loop);
    
    return node;
}
 */



Node* CSLoader::createNodeFromJson(const std::string& filename)
{
    if (_recordJsonPath)
    {
        std::string jsonPath = filename.substr(0, filename.find_last_of('/') + 1);
        GUIReader::getInstance()->setFilePath(jsonPath);
        
        _jsonPath = jsonPath;
    }
    else
    {
        GUIReader::getInstance()->setFilePath("");
        _jsonPath = "";
    }
    
    Node* node = loadNodeWithFile(filename);
    
    return node;
}

Node* CSLoader::loadNodeWithFile(const std::string& fileName)
{
    // Read content from file
    std::string contentStr = FileUtils::getInstance()->getStringFromFile(fileName);
    
    Node* node = loadNodeWithContent(contentStr);
    
    // Load animation data from file
    ActionTimelineCache::getInstance()->loadAnimationActionWithContent(fileName, contentStr);
    
    return node;
}

Node* CSLoader::loadNodeWithContent(const std::string& content)
{
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError())
    {
        CCLOG("GetParseError %s\n", doc.GetParseError());
    }
    
    // cocos2dx version mono editor is based on
    _monoCocos2dxVersion = DICTOOL->getStringValue_json(doc, MONO_COCOS2D_VERSION, "");
    
    // decode plist
    int length = DICTOOL->getArrayCount_json(doc, TEXTURES);
    
    for(int i=0; i<length; i++)
    {
        std::string plist = DICTOOL->getStringValueFromArray_json(doc, TEXTURES, i);
        std::string png   = DICTOOL->getStringValueFromArray_json(doc, TEXTURES_PNG, i);
        plist = _jsonPath + plist;
        png   = _jsonPath + png;
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, png);
    }
    
    // decode node tree
    const rapidjson::Value& subJson = DICTOOL->getSubDictionary_json(doc, NODE);
    Node* root = loadNode(subJson);
    root->release();
    
    return root;
}

Node* CSLoader::loadNode(const rapidjson::Value& json)
{
    Node* node = nullptr;
    std::string nodeType = DICTOOL->getStringValue_json(json, CLASSNAME);
    
    NodeCreateFunc func = _funcs[nodeType];
    if (func != nullptr)
    {
        const rapidjson::Value& options = DICTOOL->getSubDictionary_json(json, OPTIONS);
        node = func(options);
        
        // component
        if (node)
        {
            const rapidjson::Value& components = DICTOOL->getSubDictionary_json(options, COMPONENTS);
            int componentSize = DICTOOL->getArrayCount_json(options, COMPONENTS, 0);
            for (int i = 0; i < componentSize; ++i)
            {
                const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(components, COMPONENTS, i);
                Component* component = loadComponent(dic);
                if (component)
                {
                    node->addComponent(component);
                }
            }
        }
    }
    
    if(node)
    {
        int length = DICTOOL->getArrayCount_json(json, CHILDREN, 0);
        for (int i = 0; i<length; i++)
        {
            const rapidjson::Value &dic = DICTOOL->getSubDictionary_json(json, CHILDREN, i);
            Node* child = loadNode(dic);
            if (child)
            {
                PageView* pageView = dynamic_cast<PageView*>(node);
                ListView* listView = dynamic_cast<ListView*>(node);
                if (pageView)
                {
                    Layout* layout = dynamic_cast<Layout*>(child);
                    if (layout)
                    {
                        pageView->addPage(layout);
                    }
                }
                else if (listView)
                {
                    Widget* widget = dynamic_cast<Widget*>(child);
                    if (widget)
                    {
                        listView->pushBackCustomItem(widget);
                    }
                }
                else
                {
                    if (_monoCocos2dxVersion != "3.x")
                    {
                        Widget* widget = dynamic_cast<Widget*>(child);
                        Widget* parent = dynamic_cast<Widget*>(node);
                        if (widget
                            && parent
                            && !dynamic_cast<Layout*>(parent))
                        {
                            if (widget->getPositionType() == ui::Widget::PositionType::PERCENT)
                            {
                                widget->setPositionPercent(Vec2(widget->getPositionPercent().x + parent->getAnchorPoint().x, widget->getPositionPercent().y + parent->getAnchorPoint().y));
                                widget->setPosition(Vec2(widget->getPositionX() + parent->getAnchorPointInPoints().x, widget->getPositionY() + parent->getAnchorPointInPoints().y));
                            }
                            else
                            {
                                Size parentSize = parent->getContentSize();
                                widget->setPosition(Vec2(widget->getPositionX() + parentSize.width * parent->getAnchorPoint().x,
                                                         widget->getPositionY() + parentSize.height * parent->getAnchorPoint().y));
                            }
                        }
                    }
                    
                    node->addChild(child);
                }
                child->release();
            }
        }
    }
    else
    {
        CCLOG("Not supported NodeType: %s", nodeType.c_str());
    }
    
    return node;
}

void CSLoader::initNode(Node* node, const rapidjson::Value& json)
{
    float width         = DICTOOL->getFloatValue_json(json, WIDTH);
    float height        = DICTOOL->getFloatValue_json(json, HEIGHT);
    float x             = DICTOOL->getFloatValue_json(json, X);
    float y             = DICTOOL->getFloatValue_json(json, Y);
    float scalex        = DICTOOL->getFloatValue_json(json, SCALE_X, 1);
    float scaley        = DICTOOL->getFloatValue_json(json, SCALE_Y, 1);
    float rotation      = DICTOOL->getFloatValue_json(json, ROTATION);
    float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
    float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_Y);
    float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
    float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
    float anchorx       = DICTOOL->getFloatValue_json(json, ANCHOR_X, 0.5f);
    float anchory       = DICTOOL->getFloatValue_json(json, ANCHOR_Y, 0.5f);
    GLubyte alpha       = (GLubyte)DICTOOL->getIntValue_json(json, ALPHA, 255);
    GLubyte red         = (GLubyte)DICTOOL->getIntValue_json(json, RED, 255);
    GLubyte green       = (GLubyte)DICTOOL->getIntValue_json(json, GREEN, 255);
    GLubyte blue        = (GLubyte)DICTOOL->getIntValue_json(json, BLUE, 255);
    int zorder		    = DICTOOL->getIntValue_json(json, ZORDER);
    int tag             = DICTOOL->getIntValue_json(json, TAG);
    int actionTag       = DICTOOL->getIntValue_json(json, ACTION_TAG);
    bool visible        = DICTOOL->getBooleanValue_json(json, VISIBLE);
    
    if(x != 0 || y != 0)
        node->setPosition(Point(x, y));
    if(scalex != 1)
        node->setScaleX(scalex);
    if(scaley != 1)
        node->setScaleY(scaley);
    if (rotation != 0)
        node->setRotation(rotation);
    if(rotationSkewX != 0)
        node->setRotationSkewX(rotationSkewX);
    if(rotationSkewY != 0)
        node->setRotationSkewY(rotationSkewY);
    if(skewx != 0)
        node->setSkewX(skewx);
    if(skewy != 0)
        node->setSkewY(skewy);
    if(anchorx != 0.5f || anchory != 0.5f)
        node->setAnchorPoint(Point(anchorx, anchory));
    if(width != 0 || height != 0)
        node->setContentSize(Size(width, height));
    if(zorder != 0)
        node->setLocalZOrder(zorder);
    if(visible != true)
        node->setVisible(visible);
    
    if(alpha != 255)
    {
        node->setOpacity(alpha);
    }
    if(red != 255 || green != 255 || blue != 255)
    {
        node->setColor(Color3B(red, green, blue));
    }
    
    
    node->setTag(tag);
    node->setUserObject(ActionTimelineData::create(actionTag));
}

Node* CSLoader::loadSimpleNode(const rapidjson::Value& json)
{
    Node* node = Node::create();
    // fix memory leak for v3.3
    //node->retain();
    initNode(node, json);
    
    return node;
}

Node* CSLoader::loadSubGraph(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);
    
    Node* node = nullptr;
    if (filePath && strcmp("", filePath) != 0)
    {
        node = createNode(filePath);
    }
    else
    {
        node = Node::create();
    }
    // fix memory leak for v3.3
    //node->retain();
    
    initNode(node, json);
    
    return node;
}

Node* CSLoader::loadSprite(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, FILE_PATH);
    Sprite *sprite = nullptr;
    
    if(filePath != nullptr)
    {
        std::string path = filePath;
        
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
        if(!spriteFrame)
        {
            path = _jsonPath + path;
            sprite = Sprite::create(path);
        }
        else
        {
            sprite = Sprite::createWithSpriteFrame(spriteFrame);
        }
        
        if(!sprite)
        {
            sprite = CCSprite::create();
            CCLOG("filePath is empty. Create a sprite with no texture");
        }
    }
    else
    {
        sprite = Sprite::create();
    }
    
    // fix memory leak for v3.3
    //sprite->retain();
    
    initNode(sprite, json);
    
    bool flipX          = DICTOOL->getBooleanValue_json(json, FLIPX);
    bool flipY          = DICTOOL->getBooleanValue_json(json, FLIPY);
    
    if(flipX != false)
        sprite->setFlippedX(flipX);
    if(flipY != false)
        sprite->setFlippedY(flipY);
    
    return sprite;
}

Node* CSLoader::loadParticle(const rapidjson::Value& json)
{
    const char* filePath = DICTOOL->getStringValue_json(json, PLIST_FILE);
    int num = DICTOOL->getIntValue_json(json, PARTICLE_NUM);
    
    ParticleSystemQuad* particle = ParticleSystemQuad::create(filePath);
    particle->setTotalParticles(num);
    // fix memory leak for v3.3
    //particle->retain();
    
    initNode(particle, json);
    
    return particle;
}

Node* CSLoader::loadTMXTiledMap(const rapidjson::Value &json)
{
    const char* tmxFile = DICTOOL->getStringValue_json(json, TMX_FILE);
    const char* tmxString = DICTOOL->getStringValue_json(json, TMX_STRING);
    const char* resourcePath = DICTOOL->getStringValue_json(json, RESOURCE_PATH);
    
    TMXTiledMap* tmx = nullptr;
    
    if (tmxFile && strcmp("", tmxFile) != 0)
    {
        tmx = TMXTiledMap::create(tmxFile);
    }
    else if ((tmxString && strcmp("", tmxString) != 0)
             && (resourcePath && strcmp("", resourcePath) != 0))
    {
        tmx = TMXTiledMap::createWithXML(tmxString, resourcePath);
    }
    
    return tmx;
    
}

Node* CSLoader::loadWidget(const rapidjson::Value& json)
{
    const char* str = DICTOOL->getStringValue_json(json, CLASSNAME);
    if(str == nullptr)
        return nullptr;
    
    std::string classname = str;
    
    
    
    WidgetPropertiesReader0300* widgetPropertiesReader = new WidgetPropertiesReader0300();
    Widget* widget = nullptr;
    
    if (isWidget(classname))
    {
        std::string readerName = getGUIClassName(classname);
        readerName.append("Reader");
        
        std::string guiClassName = getGUIClassName(classname);
        widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(guiClassName));
        // fix memory leak for v3.3
        //widget->retain();
        
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        
        if (reader && widget)
        {
            widgetPropertiesReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
        }
    }
    else if (isCustomWidget(classname))
    {
        widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(classname));
        
        //fix memory leak for v3.3
        //widget->retain();
        
        //
        // 1st., custom widget parse properties of parent widget with parent widget reader
        std::string readerName = getWidgetReaderClassName(widget);
        WidgetReaderProtocol* reader = dynamic_cast<WidgetReaderProtocol*>(ObjectFactory::getInstance()->createObject(readerName));
        if (reader && widget)
        {
            widgetPropertiesReader->setPropsForAllWidgetFromJsonDictionary(reader, widget, json);
            
            // 2nd., custom widget parse with custom reader
            const char* customProperty = DICTOOL->getStringValue_json(json, "customProperty");
            rapidjson::Document customJsonDict;
            customJsonDict.Parse<0>(customProperty);
            if (customJsonDict.HasParseError())
            {
                CCLOG("GetParseError %s\n", customJsonDict.GetParseError());
            }
            
            widgetPropertiesReader->setPropsForAllCustomWidgetFromJsonDictionary(classname, widget, customJsonDict);
        }
        else
        {
            CCLOG("Widget or WidgetReader doesn't exists!!!  Please check your protocol buffers file.");
        }
    }
    CC_SAFE_DELETE(widgetPropertiesReader);
    
    if (widget)
    {
        float rotationSkewX = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_X);
        float rotationSkewY = DICTOOL->getFloatValue_json(json, ROTATION_SKEW_Y);
        float skewx         = DICTOOL->getFloatValue_json(json, SKEW_X);
        float skewy         = DICTOOL->getFloatValue_json(json, SKEW_Y);
        if(rotationSkewX != 0)
            widget->setRotationSkewX(rotationSkewX);
        if(rotationSkewY != 0)
            widget->setRotationSkewY(rotationSkewY);
        if(skewx != 0)
            widget->setSkewX(skewx);
        if(skewy != 0)
            widget->setSkewY(skewy);
        
        int actionTag = DICTOOL->getIntValue_json(json, ACTION_TAG);
        widget->setUserObject(ActionTimelineData::create(actionTag));
    }
    
    return widget;
}

Component* CSLoader::loadComponent(const rapidjson::Value &json)
{
    Component* component = nullptr;
    
    std::string componentType = DICTOOL->getStringValue_json(json, COMPONENT_TYPE);
    
    ComponentCreateFunc func = _componentFuncs[componentType];
    
    if (func != nullptr)
    {
        component = func(json);
    }
    
    return component;
}

Component* CSLoader::loadComAudio(const rapidjson::Value &json)
{
    ComAudio* audio = ComAudio::create();
    
    const char* name = DICTOOL->getStringValue_json(json, COMPONENT_NAME);
    bool enabled = DICTOOL->getBooleanValue_json(json, COMPONENT_ENABLED);
    
    audio->setName(name);
    audio->setEnabled(enabled);
    
    const char* filePath = DICTOOL->getStringValue_json(json, COMPONENT_AUDIO_FILE_PATH);
    bool loop = DICTOOL->getBooleanValue_json(json, COMPONENT_LOOP);
    
    audio->setFile(filePath);
    audio->setLoop(loop);
    
    
    return audio;
}

Node* CSLoader::createNodeWithFlatBuffersFile(const std::string &filename)
{
    return createNodeWithFlatBuffersFile(filename, nullptr);
}

Node* CSLoader::createNodeWithFlatBuffersFile(const std::string &filename, const ccNodeLoadCallback &callback)
{
    Node* node = nodeWithFlatBuffersFile(filename, callback);
    
    /* To reconstruct nest node as WidgetCallBackHandlerProtocol. */
    auto callbackHandler = dynamic_cast<WidgetCallBackHandlerProtocol *>(node);
    if (callbackHandler)
    {
        _callbackHandlers.popBack();
        if (_callbackHandlers.empty())
        {
            _rootNode = nullptr;
            CCLOG("Call back handler container has been clear.");
        }
        else
        {
            _rootNode = _callbackHandlers.back();
            CCLOG("after pop back _rootNode name = %s", _rootNode->getName().c_str());
        }
    }
    /**/
    
    return node;
}

Node* CSLoader::nodeWithFlatBuffersFile(const std::string &fileName)
{
    return nodeWithFlatBuffersFile(fileName, nullptr);
}

Node* CSLoader::nodeWithFlatBuffersFile(const std::string &fileName, const ccNodeLoadCallback &callback)
{
	char * pData = 0;
	unsigned int nLength = 0;
	if (!CNewLoader::Inst().SyncLoadFile(fileName.c_str(), &pData, &nLength))
	{
		CCLOGERROR("Load %s failed", fileName.c_str());
		return nullptr;
	}		

	auto csparsebinary = GetCSParseBinary(pData);
    
    auto csBuildId = csparsebinary->version();
    if (csBuildId)
    {
		//

        CCASSERT(strcmp(_csBuildID.c_str(), csBuildId->c_str()) == 0,
                 String::createWithFormat("%s%s%s%s%s%s%s%s%s%s",
                                          "The reader build id of your Cocos exported file(",
                                          csBuildId->c_str(),
                                          ") and the reader build id in your Cocos2d-x(",
                                          _csBuildID.c_str(),
                                          ") are not match.\n",
                                          "Please get the correct reader(build id ",
                                          csBuildId->c_str(),
                                          ")from ",
                                          "http://www.cocos2d-x.org/filedown/cocos-reader",
                                          " and replace it in your Cocos2d-x")->getCString());
    }
	//

    // decode plist
    auto textures = csparsebinary->textures();
	int textureSize = textures ? textures->size() : 0;
	//

    //CCLOG("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());
    }
	//

    Node* node = nodeWithFlatBuffers(csparsebinary->nodeTree(), callback);
	

    return node;
}

Node* CSLoader::nodeWithFlatBuffers(const flatbuffers::NodeTree *nodetree)
{
    return nodeWithFlatBuffers(nodetree, nullptr);
}

Node* CSLoader::nodeWithFlatBuffers(const flatbuffers::NodeTree *nodetree, const ccNodeLoadCallback &callback)
{
    {
        Node* node = nullptr;
        
        std::string classname = nodetree->classname()->c_str();
        //CCLOG("classname = %s", classname.c_str());
        
        auto options = nodetree->options();
        
        if (classname == "ProjectNode")
        {
            auto reader = ProjectNodeReader::getInstance();
            auto projectNodeOptions = (ProjectNodeOptions*)options->data();
            std::string filePath = projectNodeOptions->fileName()->c_str();
            //CCLOG("filePath = %s", filePath.c_str());
            
            cocostudio::timeline::ActionTimeline* action = nullptr;
            if (filePath != "" && FileUtils::getInstance()->isFileExist(filePath))
            {
                node = createNodeWithFlatBuffersFile(filePath, callback);
                action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersFile(filePath);
            }
            else
            {
                node = Node::create();
            }
            reader->setPropsWithFlatBuffers(node, options->data());
            if (action)
            {
                action->setTimeSpeed(projectNodeOptions->innerActionSpeed());
                node->runAction(action);
                action->gotoFrameAndPause(0);
            }
        }
        else if (classname == "SimpleAudio")
        {
            node = Node::create();
            auto reader = ComAudioReader::getInstance();
            Component* component = reader->createComAudioWithFlatBuffers(options->data());
            if (component)
            {
                node->addComponent(component);
                reader->setPropsWithFlatBuffers(node, options->data());
            }
        }
        else
        {
            std::string customClassName = nodetree->customClassName()->c_str();
            if (customClassName != "")
            {
                classname = customClassName;
            }
            std::string readername = getGUIClassName(classname);
            readername.append("Reader");
            
            NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
            if (reader)
            {
                node = reader->createNodeWithFlatBuffers(options->data());
            }
            
            Widget* widget = dynamic_cast<Widget*>(node);
            if (widget)
            {
                std::string callbackName = widget->getCallbackName();
                std::string callbackType = widget->getCallbackType();
                
                bindCallback(callbackName, callbackType, widget, _rootNode);
            }
            
            /* To reconstruct nest node as WidgetCallBackHandlerProtocol. */
            auto callbackHandler = dynamic_cast<WidgetCallBackHandlerProtocol *>(node);
            if (callbackHandler)
            {
                _callbackHandlers.pushBack(node);
                _rootNode = _callbackHandlers.back();
                CCLOG("after push back _rootNode name = %s", _rootNode->getName().c_str());
            }
            /**/
            //        _loadingNodeParentHierarchy.push_back(node);
        }
        
        // If node is invalid, there is no necessity to process children of node.
        if (!node)
        {
            return nullptr;
        }
        
		auto children = nodetree->children();
		int size = children ? children->size() : 0;
        //CCLOG("size = %d", size);
        for (int i = 0; i < size; ++i)
        {
            auto subNodeTree = children->Get(i);
            Node* child = nodeWithFlatBuffers(subNodeTree, callback);
            //CCLOG("child = %p", child);
            if (child)
            {
                PageView* pageView = dynamic_cast<PageView*>(node);
                ListView* listView = dynamic_cast<ListView*>(node);
                if (pageView)
                {
                    Layout* layout = dynamic_cast<Layout*>(child);
                    if (layout)
                    {
                        pageView->addPage(layout);
                    }
                }
                else if (listView)
                {
                    Widget* widget = dynamic_cast<Widget*>(child);
                    if (widget)
                    {
                        listView->pushBackCustomItem(widget);
                    }
                }
                else
                {
                    node->addChild(child);
                }
                
                if (callback)
                {
                    callback(child);
                }
            }
        }
        
        //    _loadingNodeParentHierarchy.pop_back();
        
        return node;
    }
}

bool CSLoader::bindCallback(const std::string &callbackName,
                            const std::string &callbackType,
                            cocos2d::ui::Widget *sender,
                            cocos2d::Node *handler)
{
    auto callbackHandler = dynamic_cast<WidgetCallBackHandlerProtocol *>(handler);
    if (callbackHandler) //The handler can handle callback
    {
        if (callbackType == "Click")
        {
            Widget::ccWidgetClickCallback callbackFunc = callbackHandler->onLocateClickCallback(callbackName);
            if (callbackFunc)
            {
                sender->addClickEventListener(callbackFunc);
                return true;
            }
        }
        else if (callbackType == "Touch")
        {
            Widget::ccWidgetTouchCallback callbackFunc = callbackHandler->onLocateTouchCallback(callbackName);
            if (callbackFunc)
            {
                sender->addTouchEventListener(callbackFunc);
                return true;
            }
        }
        else if (callbackType == "Event")
        {
            Widget::ccWidgetEventCallback callbackFunc = callbackHandler->onLocateEventCallback(callbackName);
            if (callbackFunc)
            {
                sender->addCCSEventListener(callbackFunc);
                return true;
            }
        }
    }
    
	if (callbackName.length())
		CCLOG("callBackName %s cannot be found", callbackName.c_str());
    
    return false;
    
}

bool CSLoader::isWidget(const std::string &type)
{
    return (type == ClassName_Panel
            || type == ClassName_Button
            || type == ClassName_CheckBox
            || type == ClassName_ImageView
            || type == ClassName_TextAtlas
            || type == ClassName_LabelAtlas
            || type == ClassName_LabelBMFont
            || type == ClassName_TextBMFont
            || type == ClassName_Text
            || type == ClassName_LoadingBar
            || type == ClassName_TextField
            || type == ClassName_Slider
            || type == ClassName_Layout
            || type == ClassName_ScrollView
            || type == ClassName_ListView
            || type == ClassName_PageView
            || type == ClassName_Widget
            || type == ClassName_Label);
    
}

bool CSLoader::isCustomWidget(const std::string &type)
{
    Widget* widget = dynamic_cast<Widget*>(ObjectFactory::getInstance()->createObject(type));
    if (widget)
    {
        CC_SAFE_DELETE(widget);
        return true;
    }
    
    return false;
}

std::string CSLoader::getGUIClassName(const std::string &name)
{
    std::string convertedClassName = name;
    if (name == "Panel")
    {
        convertedClassName = "Layout";
    }
    else if (name == "TextArea")
    {
        convertedClassName = "Text";
    }
    else if (name == "TextButton")
    {
        convertedClassName = "Button";
    }
    else if (name == "Label")
    {
        convertedClassName = "Text";
    }
    else if (name == "LabelAtlas")
    {
        convertedClassName = "TextAtlas";
    }
    else if (name == "LabelBMFont")
    {
        convertedClassName = "TextBMFont";
    }
    
    
    return convertedClassName;
}

std::string CSLoader::getWidgetReaderClassName(Widget* widget)
{
    std::string readerName;
    
    // 1st., custom widget parse properties of parent widget with parent widget reader
    if (dynamic_cast<Button*>(widget))
    {
        readerName = "ButtonReader";
    }
    else if (dynamic_cast<CheckBox*>(widget))
    {
        readerName = "CheckBoxReader";
    }
    else if (dynamic_cast<ImageView*>(widget))
    {
        readerName = "ImageViewReader";
    }
    else if (dynamic_cast<TextAtlas*>(widget))
    {
        readerName = "TextAtlasReader";
    }
    else if (dynamic_cast<TextBMFont*>(widget))
    {
        readerName = "TextBMFontReader";
    }
    else if (dynamic_cast<Text*>(widget))
    {
        readerName = "TextReader";
    }
    else if (dynamic_cast<LoadingBar*>(widget))
    {
        readerName = "LoadingBarReader";
    }
    else if (dynamic_cast<Slider*>(widget))
    {
        readerName = "SliderReader";
    }
    else if (dynamic_cast<TextField*>(widget))
    {
        readerName = "TextFieldReader";
    }
    else if (dynamic_cast<ListView*>(widget))
    {
        readerName = "ListViewReader";
    }
    else if (dynamic_cast<PageView*>(widget))
    {
        readerName = "PageViewReader";
    }
    else if (dynamic_cast<ScrollView*>(widget))
    {
        readerName = "ScrollViewReader";
    }
    
    else if (dynamic_cast<Layout*>(widget))
    {
        readerName = "LayoutReader";
    }
    else if (dynamic_cast<Widget*>(widget))
    {
        readerName = "WidgetReader";
    }
    
    return readerName;
}

void CSLoader::registReaderObject(const std::string &className,
                                  ObjectFactory::Instance ins)
{
    ObjectFactory::TInfo t;
    t._class = className;
    t._fun = ins;
    
    ObjectFactory::getInstance()->registerType(t);
}

Node* CSLoader::createNodeWithFlatBuffersForSimulator(const std::string& filename)
{
    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
    fbs->_isSimulator = true;
    FlatBufferBuilder* builder = fbs->createFlatBuffersWithXMLFileForSimulator(filename);
    
    auto csparsebinary = GetCSParseBinary(builder->GetBufferPointer());
    
    // decode plist
    auto textures = csparsebinary->textures();
    int textureSize = csparsebinary->textures()->size();
    //    CCLOG("textureSize = %d", textureSize);
    for (int i = 0; i < textureSize; ++i)
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(textures->Get(i)->c_str());
    }
    
    auto nodeTree = csparsebinary->nodeTree();

    Node* node = nodeWithFlatBuffersForSimulator(nodeTree);
    
    _rootNode = nullptr;
    
    fbs->deleteFlatBufferBuilder();
    
    return node;
}

Node* CSLoader::nodeWithFlatBuffersForSimulator(const flatbuffers::NodeTree *nodetree)
{
    Node* node = nullptr;
    
    std::string classname = nodetree->classname()->c_str();
    //CCLOG("classname = %s", classname.c_str());
    
    auto options = nodetree->options();
    
    if (classname == "ProjectNode")
    {
        auto reader = ProjectNodeReader::getInstance();
        auto projectNodeOptions = (ProjectNodeOptions*)options->data();
        std::string filePath = projectNodeOptions->fileName()->c_str();
        //CCLOG("filePath = %s", filePath.c_str());
        
        cocostudio::timeline::ActionTimeline* action = nullptr;
        if (filePath != "" && FileUtils::getInstance()->isFileExist(filePath))
        {
            node = createNodeWithFlatBuffersForSimulator(filePath);
            action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator(filePath);
        }
        else
        {
            node = Node::create();
        }
        reader->setPropsWithFlatBuffers(node, options->data());
        if (action)
        {
            action->setTimeSpeed(projectNodeOptions->innerActionSpeed());
            node->runAction(action);
            action->gotoFrameAndPause(0);
        }
    }
    else if (classname == "SimpleAudio")
    {
        node = Node::create();
        auto reader = ComAudioReader::getInstance();
        Component* component = reader->createComAudioWithFlatBuffers(options->data());
        if (component)
        {
            node->addComponent(component);
            reader->setPropsWithFlatBuffers(node, options->data());
        }
    }
    else
    {
        std::string readername = getGUIClassName(classname);
        readername.append("Reader");
        
        NodeReaderProtocol* reader = dynamic_cast<NodeReaderProtocol*>(ObjectFactory::getInstance()->createObject(readername));
        if (reader)
        {
            node = reader->createNodeWithFlatBuffers(options->data());
        }
        
        Widget* widget = dynamic_cast<Widget*>(node);
        if (widget)
        {
            std::string callbackName = widget->getCallbackName();
            std::string callbackType = widget->getCallbackType();
            
            bindCallback(callbackName, callbackType, widget, _rootNode);
        }
        
        if (_rootNode == nullptr)
        {
            _rootNode = node;
        }
//        _loadingNodeParentHierarchy.push_back(node);
    }
    
    // If node is invalid, there is no necessity to process children of node.
    if (!node)
    {
        return nullptr;
    }
    
    auto children = nodetree->children();
    int size = children->size();
    //CCLOG("size = %d", size);
    for (int i = 0; i < size; ++i)
    {
        auto subNodeTree = children->Get(i);
        Node* child = nodeWithFlatBuffersForSimulator(subNodeTree);
        //CCLOG("child = %p", child);
        if (child)
        {
            PageView* pageView = dynamic_cast<PageView*>(node);
            ListView* listView = dynamic_cast<ListView*>(node);
            if (pageView)
            {
                Layout* layout = dynamic_cast<Layout*>(child);
                if (layout)
                {
                    pageView->addPage(layout);
                }
            }
            else if (listView)
            {
                Widget* widget = dynamic_cast<Widget*>(child);
                if (widget)
                {
                    listView->pushBackCustomItem(widget);
                }
            }
            else
            {
                node->addChild(child);
            }
        }
    }
    
//    _loadingNodeParentHierarchy.pop_back();
    
    return node;
}


#include "base/CCDirector.h"

class CPackFile
{
public:
	CPackFile()
		:m_pBuff(0)
	{
	}

	// LoadFile跟LoadPackFile只能调用其中一个，否则。。。
	// throw ? 飞
	void LoadFile(const char * pFilePack, CNewLoader::FileMap & fileMap)
	{
#ifdef RAYMOND_PACK_DEBUG
		ssize_t chunkSize = 0;
		char * pBuff = 0;
		FileUtils* utils = FileUtils::getInstance();
		//一进来就直接throw
		pBuff = (char*)utils->getFileData(pFilePack, "rb", &chunkSize);

		if (!pBuff)
			throw;

		SFileData & data = fileMap[pFilePack];
		m_fileMap[pFilePack] = &data;
		data.pPackFile = this;
		data.nDataOffiset = 0;
		data.nDataLength = chunkSize;
		m_pBuff = pBuff;
#endif
	}

	void LoadPackFile(const char * pFilePack, CNewLoader::FileMap & fileMap)
	{
#ifdef RAYMOND_PACK_DEBUG
		// 打开lua包
		FileUtils* utils = FileUtils::getInstance();
		ssize_t chunkSize = 0;
		unsigned char * pBuff = 0;
		FileIO io;
		//到底应该是绝对还是相对??
		if (io.FileOpen((utils->getWritablePath() + pFilePack).c_str(), false, false))
		{
			chunkSize = io.GetFileSize();
			pBuff = (unsigned char *)malloc(chunkSize);
			io.ReadFile(pBuff, 0, chunkSize);
			io.FileClose();
		}
		else
		{
			pBuff = utils->getFileData(pFilePack, "rb", &chunkSize);
		}

		if (!pBuff || !chunkSize)
			return;

		bool useKey = false;
		char key[8] = {};

		int nHead = 0;
		memcpy(&nHead, pBuff, 4);
		if (nHead == *(int*)BASE_COMPRESS_SIGN)
		{
			// 首先解压缩
			uLongf nOriginalSize = *(unsigned int *)(pBuff + 4);
			if (0 == nOriginalSize)
			{
				// why
				SAFE_FREE(pBuff);
				return;
			}

			unsigned char * pOriginalBuff = (unsigned char * )malloc(nOriginalSize);	// 因为下面用的是free
			int nRet = uncompress(pOriginalBuff, &nOriginalSize, pBuff + 4 + sizeof(unsigned int), chunkSize - (4 + sizeof(unsigned int) ));
			SAFE_FREE(pBuff);
			if (nRet)
			{
				SAFE_FREE(pOriginalBuff);
				// why
				return;
			}
			pBuff = pOriginalBuff;
			chunkSize = nOriginalSize;
		}
		else if (nHead == *(int*)"ENCO")
		{
			// 读加密key
			useKey = true;
			memcpy(key, pBuff + 4, 8);

			// 首先解压缩
			uLongf nOriginalSize = *(unsigned int *)(pBuff + 12);
			if (0 == nOriginalSize)
			{
				// why
				SAFE_FREE(pBuff);
				return;
			}

			unsigned char * pOriginalBuff = (unsigned char *)malloc(nOriginalSize);	// 因为下面用的是free
			int nRet = uncompress(pOriginalBuff, &nOriginalSize, pBuff + 12 + sizeof(unsigned int), chunkSize - (12 + sizeof(unsigned int)));
			SAFE_FREE(pBuff);
			if (nRet)
			{
				SAFE_FREE(pOriginalBuff);
				// why
				return;
			}
			pBuff = pOriginalBuff;
			chunkSize = nOriginalSize;
		}

		if (pBuff)
		{
			// 读
			unsigned short nNameLength = 0;
			unsigned int nFileSize = 0;
			unsigned int nCurOffiset = 0;
			do
			{
				nNameLength = *(unsigned short *)(pBuff + nCurOffiset);
				nCurOffiset += sizeof(unsigned short);
				nFileSize = *(unsigned int *)(pBuff + nCurOffiset);
				nCurOffiset += sizeof(unsigned int);

				std::string strFileName = std::string((char *)(pBuff + nCurOffiset), nNameLength);
				SFileData & data = fileMap[strFileName];

				m_fileMap[strFileName] = &data;

				nCurOffiset += nNameLength;
				data.pPackFile = this;
				data.nDataOffiset = nCurOffiset;
				data.nDataLength = nFileSize;

				// 加密和解密都是依次按位异或key中的字符
				if (useKey)
				{
					for (int i = 0; i < nFileSize; i++)
					{
						int idx = i % 8;
						// char oldChar = *(char *)(pBuff + nCurOffiset + i);
						// char newChar = oldChar ^ key[idx];
						*(char *)(pBuff + nCurOffiset + i) ^= key[idx];
					}
				}

				nCurOffiset += data.nDataLength;

			} while (nCurOffiset < chunkSize);

			m_pBuff = (char*)pBuff;
		}
#endif
	}


	~CPackFile()
	{
		SAFE_FREE(m_pBuff);

	}
	// 获取文件
	bool LoadFile(std::string strName, SFileData * pFileData, char ** pData, unsigned int * pLength)
	{
#if defined RAYMOND_PACK_DEBUG
		// 本来应该判断一下 if this == data.pPackFile 然而似乎没这个必要阿
		//CCLOG("LoadFile ~~~~~~ [%s][%u] ???[%u] offset[%u]", strName.c_str(), *pLength, pFileData->nDataLength, pFileData->nDataOffiset);
		*pLength = pFileData->nDataLength;
		*pData = &m_pBuff[pFileData->nDataOffiset];
#else
		// pc 里面，先读包外的，因为没办法保证包内文件是最新的
		std::map<std::string, SBuff>::iterator it = m_SBuffMap.find(strName);
		if (it == m_SBuffMap.end())
		{ 
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename(strName);

			if (fullPath.length() <= 0)
				fullPath = FileUtils::getInstance()->fullPathForFilename( "ui/" + strName );

			if (fullPath.length() <= 0)
				return false;

			SBuff & buf = m_SBuffMap[strName];

			ssize_t chunkSize = 0;

			unsigned char * pBuff = FileUtils::getInstance()->getFileData(fullPath.c_str(), "rb", &chunkSize);
			buf.m_pBuff = new char[chunkSize];
			buf.nLength = chunkSize;
			memcpy(buf.m_pBuff, pBuff, chunkSize);
			*pData = buf.m_pBuff;
			*pLength = buf.nLength;
			SAFE_FREE(pBuff);
		}
		else
		{
			*pData = it->second.m_pBuff;
			*pLength = it->second.nLength;
		}
#endif
		return true;
	}

#ifndef RAYMOND_PACK_DEBUG
	struct SBuff
	{
		char * m_pBuff;
		unsigned int nLength;
		SBuff()
			:m_pBuff(0)
		{

		}

		~SBuff()
		{
			if ( m_pBuff )
				delete[] m_pBuff;
		}
	};

	std::map<std::string, SBuff> m_SBuffMap;
#else

	std::map< std::string, SFileData * > & GetPackFileMap()
	{
		return m_fileMap;
	}

	std::map< std::string, SFileData * > m_fileMap;
#endif
	char * m_pBuff;
};

CNewLoader * CNewLoader::s_loader = 0;

CNewLoader & CNewLoader::Inst()
{
	if (!s_loader)
		s_loader = new CNewLoader;
	return *s_loader;
}

void CNewLoader::OnEnd()
{
	if (s_loader)
	{
		delete s_loader;
		s_loader = 0;
	}	
}

#include "base/CCUserDefault.h"

const char * g_pKeyFile = "key.tab";
const char * g_pMD5File = "check.m";

CNewLoader::CNewLoader()
	:m_bIsThreadOpen( false )
	, m_bIsOpenSche( false )
	, m_fun( 0 )
	, m_bNeedSaveKey( false )
{
#ifndef RAYMOND_PACK_DEBUG
	m_pPackFile = new CPackFile;
#else
	//SyncLoadConfigPackForFile("ui/loading.csb");
	//SyncLoadConfigPackForFile("ui/Plist.pl");
	//SyncLoadConfigPackForFile("ui/Plist.png");
	//SyncLoadConfigPackForFile("ui/Plist1.pl");
	//SyncLoadConfigPackForFile("ui/Plist1.png");
	//SyncLoadConfigPackForFile("ui/shan.csb");

	// 因为热更的时候需要实时更新
	//SyncLoadConfigPack("PackUI.pak");

#endif

#if ( defined (ANDROID) && defined (COCOS2D_DEBUG) )
	m_strSDCardPath = cocos2d::UserDefault::getInstance()->getStringForKey("EXTERNAL_DIR", "/sdcard/");
#endif


	LoadSaveKey();

	FileUtils* utils = FileUtils::getInstance();
	m_strWriteAblePath = utils->getWritablePath();
}


CNewLoader::~CNewLoader()
{
	SaveKeyAndMD5();
#ifndef RAYMOND_PACK_DEBUG
	delete m_pPackFile;
#else
	for (int i = 0; i < m_PackFileVec.size(); i++)
		delete m_PackFileVec[i];

	m_FileMap.clear();
#endif
}

void CNewLoader::ReloadPack()
{
#ifdef RAYMOND_PACK_DEBUG
	for (int i = 0; i < m_PackFileVec.size(); i++)
		delete m_PackFileVec[i];

	m_PackFileVec.clear();
	m_FileMap.clear();
	
#endif

	/// 更改此处，需要更改GetUIFileData接口
//	SyncLoadConfigPack("PackUI.pak");
	SyncLoadConfigPack("PackSrc.pak");
	SyncLoadConfigPack("PackConfig.pak");

#ifdef RAYMOND_PACK_DEBUG
	CCLOG("m_PackFileVec size = %d", m_PackFileVec.size());
#endif
}

void CNewLoader::clearPack()
{
#ifdef RAYMOND_PACK_DEBUG
	for (int i = 0; i < m_PackFileVec.size(); i++)
		delete m_PackFileVec[i];

	m_PackFileVec.clear();
	m_FileMap.clear();
#endif
}

void CNewLoader::SaveKeyAndMD5()
{
	SaveKey();
	//SaveMD5();	// md5不在c++里面做了，所以此处屏蔽
}

void CNewLoader::SaveKey()
{
	if (!m_bNeedSaveKey)
		return;

	// 写入一个key文件
	FileUtils* utils = FileUtils::getInstance();
	CCLOG("write for SaveKey %s", utils->getWritablePath().c_str());
	std::string wFile = utils->getWritablePath() + g_pKeyFile;
	
	FileIO::RemoveFile(wFile.c_str());
	FileIO io;
	
	if (m_saveKey.size() && io.FileOpen(wFile.c_str(), true, true))
	{
		char * pbuff = new char[1024 * 1024];
		int nCurIndex = 0;
		// 先写头部
		memcpy(&pbuff[nCurIndex], "key", 3);
		nCurIndex += 3;
		pbuff[nCurIndex++] = '\t';
		memcpy(&pbuff[nCurIndex], "value", 5);
		nCurIndex += 5;
		pbuff[nCurIndex++] = '\n';

		for (std::map<std::string, std::string>::iterator it = m_saveKey.begin(); it != m_saveKey.end(); it++)
		{
			memcpy(&pbuff[nCurIndex], it->first.c_str(), it->first.length());
			nCurIndex += it->first.length();
			pbuff[nCurIndex++] = '\t';
			memcpy(&pbuff[nCurIndex], it->second.c_str(), it->second.length());
			nCurIndex += it->second.length();
			pbuff[nCurIndex++] = '\n';
		}
		io.WriteFile(pbuff, nCurIndex);
		io.FileClose();
		delete[] pbuff;
	}
	m_bNeedSaveKey = false;
}

unsigned char g_code[] = "diao ni ma hai po jie wo mi ma,bu guo wo gao su ni wo men de tie tu ji ben kao kou";
int g_nColdSize = strlen(( char * )&(g_code[0]));
void CNewLoader::Decode(unsigned char * pSrc, int nSrcSize, int nOffiset)
{
	if (!pSrc)
		return;
	
	for (unsigned int i = 0; i + nOffiset < nSrcSize && i < g_nColdSize; i++)
		// edited by aXing on 2017-4-11
		// 加解密算法改为异或
		pSrc[i + nOffiset] -= g_code[i];
//		pSrc[i + nOffiset] ^= g_code[i];
}

void CNewLoader::RegistFailLoadCallBack(Fun fun)
{
	this->m_fun = fun;
}

bool CNewLoader::IsHasFile(std::string & f)
{
	FileMap::iterator it = m_FileMap.find(f);
	if (it == m_FileMap.end())
		it = m_FileMap.find("ui/" + f);
	return it != m_FileMap.end();
}


bool CNewLoader::LoadResource(const char * pResFile)
{
	FileUtils* utils = FileUtils::getInstance();
	char * pBuff = 0;
	unsigned int chunkSize = 0;
	//CCLOG("load file %s", chunkSize);
	//pBuff = (char*)utils->getFileData(pResFile, "rb", &chunkSize);
	SyncLoadFile(pResFile, &pBuff, &chunkSize);

	do
	{
		if (!pBuff)
			break;

		CTableFile tfile;
		if (!tfile.LoadTableBuff(pBuff, chunkSize))
		{
			SAFE_FREE(pBuff);
			break;
		}

		unsigned int height = tfile.GetHeight();
		unsigned int width = tfile.GetWidth();

//		static const int nSourceName = 0;

		for (unsigned int j = 0; j < height; j++)
		{
//			std::string strName = tfile.GetString(j, nSourceName);
			// edited by aXing on 2017-3-23
			// 这里不用 m_ResMap保存了，改为直接去SpriteFrameCache保存数据结构
//			std::list<std::string> & sourceList = m_ResMap[strName];
//			for (int i = 1; i < width; i++)
//			{
//				string str = tfile.GetString(j, i);
//				if (0 == str.length())
//					break;
//				sourceList.push_back(str);
//			}
			string absoluteFile	= tfile.GetString(j, 0);		// 原贴图的绝对路径
			string textureFile	= tfile.GetString(j, 1);		// 整图的绝对路径

			int frameA1			= tfile.GetInteger(j, 2);		// 切图位置a
			int frameA2			= tfile.GetInteger(j, 3);		// 切图位置a
			int frameB1			= tfile.GetInteger(j, 4);		// 切图位置b
			int frameB2			= tfile.GetInteger(j, 5);		// 切图位置b

			int offsetX			= tfile.GetInteger(j, 6);		// 偏移量x
			int offsetY			= tfile.GetInteger(j, 7);		// 偏移量y

			int sourceSizeWidth	= tfile.GetInteger(j, 8);		// 原大小
			int sourceSizeHeight= tfile.GetInteger(j, 9);		// 原大小

			int sourceColorRectA1 = tfile.GetInteger(j, 10);	// 颜色矩阵
			int sourceColorRectA2 = tfile.GetInteger(j, 11);	// 颜色矩阵
			int sourceColorRectB1 = tfile.GetInteger(j, 12);	// 颜色矩阵
			int sourceColorRectB2 = tfile.GetInteger(j, 13);	// 颜色矩阵

			string r = tfile.GetString(j, 14);
			bool rotated		= r == "true";					// 是否反转

			// 开始创建一个spriteFrame放入内存
			SpriteFrame * spriteFrame = SpriteFrame::create(
				textureFile,
				Rect(frameA1, frameA2, frameB1, frameB2),
				rotated,
				Vec2(offsetX, offsetY),
				Size(sourceSizeWidth, sourceSizeHeight));

			SpriteFrameCache* mgr = SpriteFrameCache::getInstance();
			mgr->addSpriteFrame(spriteFrame, absoluteFile);
		}

		return true;
	} while (0);
	return false; 
}

bool cocos2d::CNewLoader::LoadResrouceTab(const char * pResFile)
{
//	CCLOG("CNewLoader::LoadResrouceTab .................... :: %s", pResFile);
	FileUtils* utils = FileUtils::getInstance();
	char * pBuff = 0;
	unsigned int chunkSize = 0;
	SyncLoadFile(pResFile, &pBuff, &chunkSize);

	do
	{
		if (!pBuff)
			break;

		CTableFile tfile;
		if (!tfile.LoadTableBuff(pBuff, chunkSize))
		{
			SAFE_FREE(pBuff);
			break;
		}
//		CCLOG("CTableFile size.................... :: %u", chunkSize);
		unsigned int height = tfile.GetHeight();
		unsigned int width = tfile.GetWidth();

		for (unsigned int j = 0; j < height; j++)
		{
			string absoluteFile = tfile.GetString(j, 0);		// 原贴图的绝对路径
			string textureFile = tfile.GetString(j, 1);		// 整图的绝对路径

//			CCLOG("Path =============== [%s]  [%s]", absoluteFile.c_str(), textureFile.c_str());

			int frameA1 = tfile.GetInteger(j, 2);		// 切图位置a
			int frameA2 = tfile.GetInteger(j, 3);		// 切图位置a
			int frameB1 = tfile.GetInteger(j, 4);		// 切图位置b
			int frameB2 = tfile.GetInteger(j, 5);		// 切图位置b

			int offsetX = tfile.GetInteger(j, 6);		// 偏移量x
			int offsetY = tfile.GetInteger(j, 7);		// 偏移量y

			int sourceSizeWidth = tfile.GetInteger(j, 8);		// 原大小
			int sourceSizeHeight = tfile.GetInteger(j, 9);		// 原大小

			int sourceColorRectA1 = tfile.GetInteger(j, 10);	// 颜色矩阵
			int sourceColorRectA2 = tfile.GetInteger(j, 11);	// 颜色矩阵
			int sourceColorRectB1 = tfile.GetInteger(j, 12);	// 颜色矩阵
			int sourceColorRectB2 = tfile.GetInteger(j, 13);	// 颜色矩阵

			string r = tfile.GetString(j, 14);
			bool rotated = r == "true";					// 是否反转

			// 开始创建一个spriteFrame放入内存
			SpriteFrame * spriteFrame = SpriteFrame::create(
				textureFile,
				Rect(frameA1, frameA2, frameB1, frameB2),
				rotated,
				Vec2(offsetX, offsetY),
				Size(sourceSizeWidth, sourceSizeHeight));

			SpriteFrameCache* mgr = SpriteFrameCache::getInstance();
			mgr->addSpriteFrame(spriteFrame, absoluteFile);
		}

		return true;
	} while (0);
	return false;
}

bool cocos2d::CNewLoader::LoadAnimationTab(const char * pResFile)
{
	FileUtils* utils = FileUtils::getInstance();
	char * pBuff = 0;
	unsigned int chunkSize = 0;
	SyncLoadFile(pResFile, &pBuff, &chunkSize);

	do
	{
		if (!pBuff)
			break;

		CTableFile tfile;
		if (!tfile.LoadTableBuff(pBuff, chunkSize))
		{
			SAFE_FREE(pBuff);
			break;
		}

		unsigned int height = tfile.GetHeight();
		unsigned int width = tfile.GetWidth();

		for (unsigned int j = 0; j < height; j++)
		{
			string absolutePath = tfile.GetString(j, 0);		// 原贴图的绝对路径
			
			std::list<std::string> & sourceList = m_ResMap[absolutePath];	// 动画依赖贴图表
			for (int i = 1; i < width; i++)
			{
				string str = tfile.GetString(j, i);
				if (0 == str.length())
					break;
				SpriteFrameCache* mgr = SpriteFrameCache::getInstance();
				const string fileName = absolutePath + "/" + str;
				mgr->addSpriteFramesWithFile(fileName);
				
				string temp = fileName;
				int index = temp.find(".plist");
				const string textureName = temp.replace(index, 6, ".png");
				sourceList.push_back(textureName);
			}
		}

		return true;
	} while (0);
	return false;
}

bool cocos2d::CNewLoader::LoadMD5Tab(const char * pResFile)
{
	FileUtils* utils = FileUtils::getInstance();
	unsigned char * pBuff = 0;
	unsigned int chunkSize = 0;
	//SyncLoadFile(pResFile, &pBuff, &chunkSize);
	// 这里还不是用启亮小包读取，md5表在包外
	pBuff = utils->getFileData(pResFile, "r", (ssize_t*)&chunkSize);

	do
	{
		if (!pBuff)
		{
			CCLog(":CNewLoader::LoadMD5Tab %s is null!!", pResFile);
			break;
		}
		CCLog(":CNewLoader::LoadMD5Tab %s succeed!!", pResFile);
		CTableFile tfile;
		if (!tfile.LoadTableBuff((char*)pBuff, chunkSize))
		{
			SAFE_FREE(pBuff);
			break;
		}
		
		unsigned int height = tfile.GetHeight();
		unsigned int width = tfile.GetWidth();

		for (unsigned int j = 0; j < height; j++)
		{
			string path = tfile.GetString(j, 0);		// 原贴图的绝对路径
			string md5	= tfile.GetString(j, 1);		// md5
			int size	= tfile.GetInteger(j, 2);		// 图片大小
			string ver	= tfile.GetString(j, 3);		// 版本号

			Director::getInstance()->getTextureCache()->setFileVersion(path, ver);
		}
		return true;
	} while (0);
	return false;
}

void cocos2d::CNewLoader::LoadSaveKey()
{
	FileUtils* utils = FileUtils::getInstance();
	char * pBuff;
	ssize_t chunkSize = 0;
	FileIO io;
	if (!io.FileOpen((utils->getWritablePath() + g_pKeyFile).c_str(), false, false))
		return;

	chunkSize = io.GetFileSize();
	if (!chunkSize)
		return;
	pBuff = (char *)malloc(chunkSize);
	io.ReadFile(pBuff, 0, chunkSize);

	do
	{
		if (!pBuff)
			break;

		CTableFile tfile;
		if (!tfile.LoadTableBuff(pBuff, chunkSize))
		{
			SAFE_FREE(pBuff);
			break;
		}

		unsigned int height = tfile.GetHeight();
		unsigned int width = tfile.GetWidth();
		if (width < 2)
		{
			SAFE_FREE(pBuff);
			break;
		}

		for (unsigned int i = 1; i < height; i++)
			m_saveKey[tfile.GetString(i, 0)] = tfile.GetString(i, 1);

	} while (0);
}

std::list<std::string> * CNewLoader::LoadResDepenence(const char * pResFile)
{
	std::map< std::string, std::list<std::string> >::iterator it = m_ResMap.find(pResFile);
	if (it == m_ResMap.end())
		return 0;
	else
		return &(it->second);
}

bool CNewLoader::SyncLoadConfigPack(const char * pConfigFile)
{
#ifdef RAYMOND_PACK_DEBUG
	int nSize = m_PackFileVec.size();
	m_PackFileVec.resize(nSize + 1);
	m_PackFileVec[nSize] = new CPackFile;
	// 读取文件
	m_PackFileVec[nSize]->LoadPackFile(pConfigFile, m_FileMap);
	return true;
#endif
	return false;
}

#ifdef RAYMOND_PACK_DEBUG
std::map< std::string, SFileData * > & CNewLoader::GetUIFileData()
{
	return m_PackFileVec[6]->GetPackFileMap();
}

void CNewLoader::GetDataByFData(SFileData * pFileData, char ** pData, unsigned int * pLength)
{
	pFileData->pPackFile->LoadFile("", pFileData, pData, pLength);
}

#endif

//bool CNewLoader::AsyncLoadConfigPack(const char * pConfigFile)
//{
//	return false;
//}

bool CNewLoader::SyncLoadFile(const char * pConfigFile, char ** pData, unsigned int * pLength)
{
	if (!pConfigFile)
		return false;
		
	std::string fileName = pConfigFile;
#ifdef RAYMOND_PACK_DEBUG
	// 如果需要进来这里，应该只需要找lua， pl， tab，脚本和配置文件，贴图一定不在包里
	FileMap::iterator it = m_FileMap.find(fileName);
	if (it == m_FileMap.end())
		it = m_FileMap.find("ui/" + fileName);			// 居然还有 ui/xxx.plist 文件，佩服
	//if (it == m_FileMap.end())
	//	it = m_FileMap.find("loadui/" + fileName);
	if (it == m_FileMap.end())
		return false;
	
	return it->second.pPackFile->LoadFile(fileName, &(it->second), pData, pLength);
#else
	m_ioMutex.lock();

	// 模拟真机的加载效果，只读取 ui/ icon/下面的png文件
	//int nPngPos = fileName.find(".png");
	bool bRes = false;
	// removed by aXing on 2017-3-24
	// 这里不明白为什么要这样写，先试试屏蔽，到时候打真机出来看出了什么问题
	//if (fileName.length() - 4 == nPngPos)
	//{
	//	if (0 == fileName.find("ui/") || 0 == fileName.find("icon/") || 0 == fileName.find("zitiku/"))
	//		bRes = m_pPackFile->LoadFile(fileName, 0, pData, pLength);
	//}
	//else
	//	bRes = m_pPackFile->LoadFile(fileName, 0, pData, pLength);
	bRes = m_pPackFile->LoadFile(fileName, 0, pData, pLength);

	m_ioMutex.unlock();
	return bRes;
#endif

}

unsigned int CNewLoader::AsyncLoadTex(const char * pTex, void * pContext, OnFinish fun)
{
	if (!pTex)
		return 0;

	std::string sTmp = pTex;

	// TODO:: 如果textureCache有，不就是可以直接return了吗？

#ifdef RAYMOND_PACK_DEBUG
	//int nPos = sTmp.find("/");
	//while (-1 != nPos)
	//{
	//	sTmp.replace(nPos, 1, "_");
	//	nPos = sTmp.find("/");
	//}
#endif

	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(sTmp);

	static unsigned int nHandle = 0;
	nHandle++;
	// 加载图片
	if (!m_bIsThreadOpen)
	{
		// 插入到map里面
		SLoadStruct & sLS = m_LoadMap[nHandle];
		sLS.strTex = sTmp;
		sLS.strFullTex = strFullPath;
		sLS.fun = fun; 
		sLS.pContext = pContext;
		sLS.nSize = 0;
		sLS.pLoadData = 0;

		// 开始一个定时器，处理一下加载之后的情况
		if (!m_bIsOpenSche)
		{
			std::string str("load");
			CCDirector::getInstance()->getScheduler()->schedule(CNewLoader::OnTick, this, 0.01, false, str);
			m_bIsOpenSche = true;
		}

		// 启动线程
		m_bIsThreadOpen = true;
		std::thread th(&CNewLoader::OnThreadStart, this);

		th.detach();
	}
	else
	{
		// 同步一下然后就塞进去咯
		m_ioMutex.lock();

		SLoadStruct & sLS = m_LoadMap[nHandle];
		sLS.strTex = sTmp;
		sLS.strFullTex = strFullPath;
		sLS.fun = fun;
		sLS.pContext = pContext;
		sLS.pLoadData = 0;
		sLS.nSize = 0;

		m_ioMutex.unlock();
	}


	return nHandle;
}


void cocos2d::CNewLoader::OnHttpLoad(std::string strFile, void * pData, int nSize)
{
	// 判断一下有没有需要异步回调的
	void * pContext = 0;
	OnFinish fun;

	m_ioMutex.lock();

	for (LoadMap::iterator it = m_LoadMap.begin(); it != m_LoadMap.end(); it++)
	{
		if (it->second.strTex == strFile)
		{
			fun = it->second.fun;
			pContext = it->second.pContext;

			it->second.pContext = 0;
			it->second.nSize = 0;
			
			// 然后释放
			m_LoadMap.erase(it);

			// 避免在lock里面做回调
			break;
		}
	}

	m_ioMutex.unlock();

	if ( pContext )
		fun(pContext, pData, nSize);
}

void cocos2d::CNewLoader::StopLoad(unsigned int handle)
{
	m_ioMutex.lock();
	m_LoadMap.erase(handle);
	m_ioMutex.unlock();
}

void CNewLoader::OnTick(float t)
{
	CNewLoader::Inst()._OnTick(t);
}

void CNewLoader::_OnTick(float)
{
	// 因为安全问题，每次只回调一次
	void * pContext = 0;
	OnFinish fun;
	void * pLoadData = 0;
	unsigned int nSize;
	unsigned int nKey = 0;
	std::string strTex;
	m_ioMutex.lock();

	if (0 == m_LoadMap.size())
	{
		// 停掉计时器
		std::string str("load");
		CCDirector::getInstance()->getScheduler()->unschedule(str, this);
		m_bIsOpenSche = false;
	}
	else
	{
		LoadMap::iterator it = m_LoadMap.begin();
		while (it != m_LoadMap.end())
		{
			LoadMap::iterator tmp = it;
			it++;

			SLoadStruct & sl = tmp->second;
			if (sl.pLoadData)
			{
				pContext = sl.pContext;
				pLoadData = sl.pLoadData;
				nSize = sl.nSize;
				nKey = tmp->first;	// 用于释放
				fun = sl.fun;
				
				break;
			}
			else if (sl.nSize == FAIL_LOAD && m_fun)
			{
				sl.nSize = WAIT_FOR_LOAD;
				strTex = sl.strTex;
				//m_fun(sl.strTex);
				break;
			}
		}
	}

	m_ioMutex.unlock();

	// 避免在lock里面做回调
	if (pContext)
	{
		fun(pContext, pLoadData, nSize);


		m_ioMutex.lock();
		m_LoadMap.erase(nKey);
		m_ioMutex.unlock();
	}
	else if (strTex.length() > 0)
	{
		m_fun(strTex);
	}
}

void CNewLoader::OnThreadStart()
{
	std::string strLoad;
	std::string strFull;
	unsigned int nHandle;

	m_ioMutex.lock();

	while (true)
	{
		strLoad.clear();
		nHandle = 0;


		for (LoadMap::iterator it = m_LoadMap.begin(); it != m_LoadMap.end(); it++)
		{
			if (!it->second.pLoadData && it->second.nSize != FAIL_LOAD && it->second.nSize != WAIT_FOR_LOAD )
			{
				strLoad = it->second.strTex;
				strFull = it->second.strFullTex;
				nHandle = it->first;
				break;
			}
		}
		
		

		void * pData = 0;
		unsigned int nSize = 0;

		if (strLoad.size() > 0)
		{
// 打开文件的位置不同，所以打开也不同
#ifdef RAYMOND_PACK_DEBUG
			int nPos = strLoad.find( "/" );
			while (-1 != nPos)
			{
				strLoad.replace(nPos, 1, "_");
				nPos = strLoad.find("/");
			}
			
			FileIO io;
			// 优先考虑下载后的
			if (!io.FileOpen( (m_strWriteAblePath + strLoad).c_str(), false, false))
			{
				// 没有的话，则要考虑初始包里面的
				char * pBuff;
				ssize_t chunkSize = 0;
				FileUtils* utils = FileUtils::getInstance();
				pData = (char*)utils->getFileDataThread(strFull.c_str(), "rb", (ssize_t*)&nSize);
			}
			else
			{
				nSize = io.GetFileSize();
				if (nSize > 0)
				{
					pData = malloc(nSize);
					io.ReadFile(pData, 0, nSize);
				}
			}
#else
			//m_ioMutex.lock();
			//// 开发版出现这个错误，就是因为这里用的是一个线程不是安全的迭代器，所以先保证开发版本线程安全
			//std::string strFile = FileUtils::getInstance()->fullPathForFilename(strLoad);

			//m_ioMutex.unlock();

			FileIO io;
			if (io.FileOpen(strFull.c_str(), false, false))
			{
				nSize = io.GetFileSize();
				if (nSize > 0)
				{
					pData = malloc(nSize);
					io.ReadFile(pData, 0, nSize);
				}
			}
#endif
			if (nSize == 0)
			{
				// 加载，如果没有文件，则挂起，等待文件下来，并且要直接设置nHnadle = 0
				//m_ioMutex.lock();
				
				LoadMap::iterator it = m_LoadMap.find(nHandle);
				if (it != m_LoadMap.end() && it->second.nSize == 0)
					it->second.nSize = FAIL_LOAD;

				//m_ioMutex.unlock();
				nHandle = 0;
			}
		}
		else
		{
			// 暂停加载
			break;
		}

		// 加载完成，由于有可能取消加载了，所以要重新获取一下
		if (nHandle > 0)
		{
			// m_ioMutex.lock();

			LoadMap::iterator it = m_LoadMap.find(nHandle);
			if (it != m_LoadMap.end())
			{
				// 放到里面来回收
				it->second.nSize = nSize;
				it->second.pLoadData = pData;
			}
			else
			{
				free(pData);
			}

		}
	}

	m_ioMutex.unlock();

	m_bIsThreadOpen = false;	// 线程停了
}

const char * cocos2d::CNewLoader::loadKey(const char * pKey)
{
	std::map<std::string, std::string>::iterator it = m_saveKey.find(pKey);
	if (it == m_saveKey.end())
		return "";
	else
		return it->second.c_str();
}

void cocos2d::CNewLoader::saveKey(const char * pKey, const char * pValue)
{
	if (!pKey || 0 == strlen(pKey))
		return;
	m_saveKey[pKey] = pValue;
	m_bNeedSaveKey = true;
}

bool cocos2d::CNewLoader::LoadOutSideLua(std::string & file, char ** pData, unsigned int * pLength)
{
#if ( defined (ANDROID) && defined (COCOS2D_DEBUG) )
	FileIO io;
//	CCLOG( "LoadOutSideLua %s", ( m_strSDCardPath + "/" + file ).c_str() );
	if ( io.FileOpen(  ( m_strSDCardPath + "/" + file ).c_str(), false, false ) )
	{
		*pLength = io.GetFileSize();
		char * pOutputFileBuff = (char *)malloc(*pLength);
		io.ReadFile(pOutputFileBuff, 0, *pLength);
		io.FileClose();

		// 外部只能调用lua
		*pData = pOutputFileBuff;

		return true;
	}
	else
	{
		return false;
	}
	

#endif
	return false;
}



NS_CC_END
