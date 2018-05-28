UIConfig = {}

UIConfig.ZOrder = {
	Normal = 99,
}

UIConfig.viewType = {
	FullScreen = 1,
}

UIConfig.config = {
    ["UpdateView"] = {path = "ui.update.UpdateView",viewType = UIConfig.viewType.FullScreen},--热更新界面
    ["LoginView"] = {path = "ui.login.LoginView", viewType = UIConfig.viewType.FullScreen}--登录界面
}