local proto = require ("proto")
local sproto = require ("component.proto.sproto")

local host = sproto.new(proto.s2c):host "package"
local request = host:attach(sproto.new(proto.c2s))
local string = require("string") 


local function send_package(pack)
	local buffer = string.pack(">s2", pack)
	return buffer
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

local function packmsg(name, args, session)
	local str = request(name, args, session)
	local buffer = string.pack(">s2", str)
	return buffer
end

local function unpackmsg(receivedata)
	return host:dispatch(unpack_package(receivedata))
end


local protoutils = {}
protoutils.packmsg = packmsg
protoutils.unpackmsg = unpackmsg

return protoutils