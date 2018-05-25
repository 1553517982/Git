local socketevent = require("socketevent")
local myutils = require("common.utils")
local protoutils = require("component.proto.protoutils")

--是否已连接
local isconnect = false
--全局tcp socket实例
local sock = socketevent.tcp()

local NetMgr = {}

NetMgr.getInstance = function()
	return sock
end

NetMgr.connect = function(ip ,port)
	sock:connect(ip, port)
end

NetMgr.send = function(msg)
	if isconnect then
		sock:send(msg)
	end
end

NetMgr.onReceiveMsg = function(msg)
	local type , session ,result = protoutils.unpackmsg(msg)
	print("type: ",type)
	print("session: ",session)
	print("result:" , myutils.print(result))
end


NetMgr.onConnected = function()
	isconnect = true
end

NetMgr.onDisConnect = function()
	isconnect = false
	
end

sock:on("connect", function(event)
	NetMgr.onConnected()
end)

sock:on("data", function(event)
	if event.data ~= "" then
		NetMgr.onReceiveMsg(event.data)
	end
end)

sock:on("close", function(event)
	NetMgr.onDisConnect() 
	print("close!")
end)

sock:on("error", function(event)
	NetMgr.onDisConnect()
	print("error: " .. event.error .. ", " .. event.message)
end)

return NetMgr