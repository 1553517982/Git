cc.FileUtils:getInstance():addSearchPath("../Script/")

require ("base.baseclass")
require("base.eventsystem")
require ("base.functions")
require("ui.UIManager")
require("gmcmd")

local function main()
	GlobalEventSystem = EventSystem.New()
	UIManager.New()
	UIManager.Instance:initAll()
	UIManager.Instance:showUI("LoginView")
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
