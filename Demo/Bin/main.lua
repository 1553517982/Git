cc.FileUtils:getInstance():addSearchPath("../Script/")
--cc.FileUtils:getInstance():addSearchPath("../res/") ������Դ·��
local netMgr = require "component.net.NetMgr"

local function main()
	netMgr.connect("123.207.19.86", 8888)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
