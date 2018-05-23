/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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
#include "2d/CCCamera.h"
#include "base/CCDirector.h"
#include "platform/CCGLView.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

Camera* Camera::_visitingCamera = nullptr;


Camera* Camera::getDefaultCamera()
{
    auto scene = Director::getInstance()->getRunningScene();
    if(scene)
    {
        return scene->getDefaultCamera();
    }

    return nullptr;
}

    Camera* Camera::create()
{
    Camera* camera = new (std::nothrow) Camera();
    camera->initDefault();
    camera->autorelease();
    camera->setDepth(0.f);
    
    return camera;
}

Camera* Camera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    auto ret = new (std::nothrow) Camera();
    if (ret)
    {
        ret->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Camera* Camera::createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    auto ret = new (std::nothrow) Camera();
    if (ret)
    {
        ret->initOrthographic(zoomX, zoomY, nearPlane, farPlane);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

Camera::Camera()
: _scene(nullptr)
, _viewProjectionDirty(true)
, _cameraFlag(1)
, _frustumDirty(true)
, _depth(-1)
{
}

Camera::~Camera()
{
    
}
bool Camera::initDefault()
{
    auto size = Director::getInstance()->getWinSize();
    //create default camera
    auto projection = Director::getInstance()->getProjection();
    switch (projection)
    {
        case Director::Projection::_2D:
        {
            initOrthographic(size.width, size.height, -1024, 1024);
            setPosition3D(Vec3(0.0f, 0.0f, 0.0f));
            setRotation3D(Vec3(0.f, 0.f, 0.f));
            break;
        }
        default:
            CCLOG("unrecognized projection");
            break;
    }
    return true;
}

bool Camera::initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    _fieldOfView = fieldOfView;
    _aspectRatio = aspectRatio;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    Mat4::createPerspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, &_projection);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
    //if needed, we need to add a rotation for Landscape orientations on Windows Phone 8 since it is always in Portrait Mode
    GLView* view = Director::getInstance()->getOpenGLView();
    if(view != nullptr)
    {
        setAdditionalProjection(view->getOrientationMatrix());
    }
#endif
    _viewProjectionDirty = true;
    _frustumDirty = true;
    
    return true;
}

bool Camera::initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    _zoom[0] = zoomX;
    _zoom[1] = zoomY;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    Mat4::createOrthographicOffCenter(0, _zoom[0], 0, _zoom[1], _nearPlane, _farPlane, &_projection);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
    //if needed, we need to add a rotation for Landscape orientations on Windows Phone 8 since it is always in Portrait Mode
    GLView* view = Director::getInstance()->getOpenGLView();
    if(view != nullptr)
    {
        setAdditionalProjection(view->getOrientationMatrix());
    }
#endif
    _viewProjectionDirty = true;
    _frustumDirty = true;
    
    return true;
}

void Camera::setDepth(int depth)
{
    if (_depth != depth)
    {
        _depth = depth;
        if (_scene)
        {
            //notify scene that the camera order is dirty
            _scene->setCameraOrderDirty();
        }
    }
}

void Camera::onEnter()
{
    if (_scene == nullptr)
    {
        auto scene = getScene();
        if (scene)
        {
            setScene(scene);
        }
    }
    Node::onEnter();
}

void Camera::onExit()
{
    // remove this camera from scene
    setScene(nullptr);
    Node::onExit();
}

void Camera::setScene(Scene* scene)
{
    if (_scene != scene)
    {
        //remove old scene
        if (_scene)
        {
            auto& cameras = _scene->_cameras;
            auto it = std::find(cameras.begin(), cameras.end(), this);
            if (it != cameras.end())
                cameras.erase(it);
            _scene = nullptr;
        }
        //set new scene
        if (scene)
        {
            _scene = scene;
            auto& cameras = _scene->_cameras;
            auto it = std::find(cameras.begin(), cameras.end(), this);
            if (it == cameras.end())
            {
                _scene->_cameras.push_back(this);
                //notify scene that the camera order is dirty
                _scene->setCameraOrderDirty();
            }
        }
    }
}

NS_CC_END
