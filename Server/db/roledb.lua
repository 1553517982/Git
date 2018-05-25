local skynet = require("skynet")
require "skynet.manager"

local CMD = {}
local login = {}
local roledb = {
	["111"] = "111",
	["222"] = "222",
	["333"] = "333",
	["123"] = "123",
	["1234"] = "1234",
	["12345"] = "12345",
}

function CMD.checkRole(id, password)
	if login[id] then 
		return 10
	end
	local psd = roledb[id]
	if not psd then 
		return 1 -- 无角色
	elseif psd ~= password then 
		return 2 -- 密码错误
	end
	login[id] = true
	print("+++++++++++登录成功：", id)
	return 0
end

-- 下线
function CMD.unLine(id)
	if login[id] then 
		print("+++++++++++下线：", id)
		login[id] = nil
	end
end

skynet.start(function()
	skynet.dispatch("lua", function(_, _, cmd, ...)
		local f = CMD[cmd]
		if f then
			skynet.ret(skynet.pack(f(...)))
		else
			error(string.format("Unknown CMD %s", tostring(cmd)))
		end
	end)

	-- skynet.register "ROLEDB"
end)