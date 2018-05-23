#include "cocos2d.h"
//导出期__EXPORT_QWidget_H__应未定义
#ifndef __EXPORT_QWidget_H__
#define __EXPORT_QWidget_H__
class QWidget
{
public:
	bool isEnabled() const;
	void setEnabled(bool);
	void setDisabled(bool);
};

class QComboBox : public QWidget
{
public:
	void setCurrentIndex(int index);
	int  currentIndex() const;
};

class MapEditor
{
public:
	static MapEditor* shareMapEditor();
	QWidget* getWidget(const std::string& name);
};
#else
//运行期__EXPORT_QWidget_H__应在MapEditor定义
#include "QWidget"
#include "QComboBox"
#include "mapeditor.h"
#endif