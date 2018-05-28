cc.FileUtils:getInstance():addSearchPath("../Script/")
cc.FileUtils:getInstance():addSearchPath("../res/")

local function main()
	require("ui.UIManager")
	UIManager.New()
	UIManager.Instance:initAll()
	UIManager.Instance:showUI("LoginView")
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
