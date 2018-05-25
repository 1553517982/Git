cc.FileUtils:getInstance():addSearchPath("../Script/")
--cc.FileUtils:getInstance():addSearchPath("../res/") 加载资源路径
local netMgr = require "component.net.NetMgr"
local myutils = require("common.utils")
local protoutils = require("component.proto.protoutils")

function gm(command)
	local commands = myutils.split(command," ")
	--myutils.print(commands)
	if commands[1] == "login" then
		local users = {
			[1] = "111",
			[2] = "123",
			[3] = "1234",
			[4] = "12345",
		}
		local name = users[tonumber(commands[2])]
		local msg = protoutils.packmsg("login",{id = name , password = name },2)
		netMgr.send(msg)
	elseif commands[1] == "ready" then
		local msg = protoutils.packmsg("ready",nil,2)
		netMgr.send(msg)
	elseif commands[1] == "quickstart" then
		local msg = protoutils.packmsg("quickstart",nil,2)
		netMgr.send(msg)
	end
end

local function main()
	netMgr.connect("123.207.19.86", 8888)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
