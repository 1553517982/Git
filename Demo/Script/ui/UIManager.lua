require("ui.config.UIConfig")
require ("base.baseclass")
require("base.eventsystem")
require ("base.functions")
require("gmcmd")
require("ui.base.BaseUI")

UIManager = UIManager or BaseClass()

function UIManager:__init()
	UIManager.Instance = self
end

function UIManager:init_ui(  )
    local root = scene.XLogicScene:sharedScene()
    cc.Director:getInstance():replaceScene(root)
    local showFPS = cc.UserDefault:getInstance():getBoolForKey("showFPS", true)
    cc.Director:getInstance():setDisplayStats(showFPS)
end

function UIManager:initAll()
	GlobalEventSystem = EventSystem.New()
	self:init_ui()
	self.uiList = {}
	self.uiInShow =	{}
	self.maxUILevel = 0
	self.m_pUIRootNode = scene.XLogicScene:sharedScene():getNode(2)
end

function UIManager:showUI(name,arg)
	if type(name) == "string" then
		local view = self.uiList[name]
		
		if (self.uiInShow[name]) then
			self:hideUI(name)
			self:showUI(name, arg)
			return view
		end
		
		if view == nil then
			view = self:createUI(name)
		end
		if (view == nil) then
			print("UIManager:showUI create UI"..name.." failed. return")
			return
		end
		
		local conf = UIConfig.config[name]
		self:handleShowOption(name, view)
		
		local zorder = conf.zorder or UIConfig.ZOrder.Normal
		local tag = conf.tag or 0
		
		self.m_pUIRootNode:addChild(view:getRootNode(),zorder,tag)
		
		if (view.onEnter) then
			view.onEnter(view, arg)
		end
		return view
	end
end

function UIManager:addShowingView(name, view)
	self.uiInShow[name] = view
	self.maxUILevel = self.maxUILevel + 1
end

function UIManager:handleShowOption(name, view)
	self:addShowingView(name, view)
end

function UIManager:hideUI(name)
	self:doHideUI(name)
end

function UIManager:doHideUI(name)
	if type(name) ~= "string" then
		return
	end
	
	local view = self.uiList[name]
	if view == nil then
		return
	end

	if self:isShowing(name) and view then
		view:retain()
		if (view.onExit) then
			view.onExit(view)
		end
		view:removeFromParentAndCleanup(true)
		view:release()
		self.uiInShow[name] = nil
	end
end

function UIManager:hideAllUI()
	local tmp = {}
	for k, v in pairs(self.uiInShow) do
		table.insert(tmp, k)
	end
	for kk, vv in pairs(tmp) do
		self:doHideUI(vv)
	end
end

function UIManager:clear(isClear)
	self:hideAllUI()
	if isClear then
		self.m_pUIRootNode:removeFromParentAndCleanup(true)
	end
end

function UIManager:getViewByName(name)
	return self.uiList[name]
end

function UIManager:getShowingViews()
	return self.uiInShow
end

function UIManager:isShowing(name)
	if (self.uiInShow[name]) then
		return true
	else
		return false
	end
end

function UIManager:createUI(uiKey)
	local class = _G[uiKey]
	if class then
		local view = class.New()
		self.uiList[uiKey] = view
		return view
	else
		local conf = UIConfig.config[uiKey]
		if conf ~= nil then
			require(""..conf.path)
			class = _G[uiKey]
			if class then
				local view = class.New(conf.viewType)
				self.uiList[uiKey] = view
				return view
			end
		end
		return nil
	end
end