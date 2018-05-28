cc.FileUtils:getInstance():addSearchPath("Script/")

require "base.baseclass"
require "base.functions"
require("ui.UIManager")
local myutils = require("common.utils")

function gm(command)
	local debugger = require("debug")
	myutils.print(debugger)
	debugger.gmcmd(command)
end

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
