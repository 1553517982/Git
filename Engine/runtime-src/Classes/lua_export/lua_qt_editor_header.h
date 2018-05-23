#include "cocos2d.h"
//������__EXPORT_QWidget_H__Ӧδ����
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
//������__EXPORT_QWidget_H__Ӧ��MapEditor����
#include "QWidget"
#include "QComboBox"
#include "mapeditor.h"
#endif