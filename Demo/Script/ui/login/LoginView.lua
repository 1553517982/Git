LoginView = LoginView or BaseClass(BaseUI)

function LoginView:__init()
	self.viewName = "LoginView"
	local layer = cc.LayerColor:create({r=100,g=0,b=0,a=255},300,300)
	layer:setPosition(0,0)
	self:addChild(layer)
end

function LoginView:onEnter()
    
end

function LoginView:onExit()
    
end