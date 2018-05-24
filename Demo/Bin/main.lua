cc.FileUtils:getInstance():addSearchPath("../Script/")

local proto = require "proto"
local sproto = require "sproto.sproto"

local host = sproto.new(proto.s2c):host "package"
local request = host:attach(sproto.new(proto.c2s))
local string = require("string") 


local socketevent = require("socketevent")

sock = socketevent.tcp()

local function send_package(pack)
	local buffer = string.pack(">s2", pack)
	sock:send(buffer)
end

local function unpack_package(text)
	local size = #text
	if size < 2 then
		return nil, text
	end
	local s = text:byte(1) * 256 + text:byte(2)
	if size < s+2 then
		return nil, text
	end

	return text:sub(3,2+s), text:sub(3+s)
end

local session = 0

function send_request(name, args)
	session = session + 1
	local str = request(name, args, session)
	send_package(str)
	print("Request:", session)
end

sock:on("connect", function(event)
	print("connect")
	send_request("handshake")
	send_request("get",{what = "hello"})
end)

sock:on("data", function(event)
	if event.data ~= "" then
		print("data: ",host:dispatch(unpack_package(event.data)))
	end
end)

sock:on("close", function(event)
	print("close!")
end)

sock:on("error", function(event)
	print("error: " .. event.error .. ", " .. event.message)
end)

local function main()
	sock:connect("123.207.19.86", 8888)
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
