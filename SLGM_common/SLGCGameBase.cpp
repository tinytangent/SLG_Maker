#include <QString>

#include "SLGCGameBase.h"


SLGCGameBase::SLGCGameBase()
{

}

SLGCGameBase::~SLGCGameBase()
{

}

bool SLGCGameBase::addGameProperty(const QString& name, const QString& value)
{
	if(name.isEmpty()) return false;
	return AddProperty(name.toStdString(), value.toStdString()) == 0;
}

bool SLGCGameBase::addGameProperty(const QString& name, const int value)
{
	if(name.isEmpty()) return false;
	return AddProperty(name.toStdString(), value)==0;
}

bool SLGCGameBase::deleteGameProperty(const QString& name)
{
	if(name.isEmpty()) return false;
	return DeleteProperty(name.toStdString()) == 0;
}

bool SLGCGameBase::setGameProperty(const QString& name, const QString& value)
{
	if(name.isEmpty()) return false;
	return ChangeProperty(name.toStdString(), value.toStdString());
}

bool SLGCGameBase::getGameProperty(const QString& name, QString& value)
{
	std::string temp;
	if(name.isEmpty()) return false;
	int ret = QueryProperty(name.toStdString(), &temp);
	if(ret!=0)
	{
		return false;
	}
	else
	{
		value = QString::fromStdString(temp);
		return true;
	}
}

QMap<QString, QString> SLGCGameBase::getAllStringGameProperties()
{
	QMap<QString, QString> ret;
	for(std::map<string,string>::iterator i = sProperty.begin();i!=sProperty.end();i++)
	{
		ret.insert(QString::fromStdString(i->first),QString::fromStdString(i->second));
	}
	return ret;
}

QMap<QString, int> SLGCGameBase::getAllIntGameProperties()
{
	QMap<QString, int> ret;
	for(std::map<string,int>::iterator i = nProperty.begin();i!=nProperty.end();i++)
	{
		ret.insert(QString::fromStdString(i->first),i->second);
	}
	return ret;
}

bool SLGCGameBase::setGameProperty(const QString &name, const int value)
{
	if(name.isEmpty()) return false;
	if(nProperty.find(name.toStdString())!=nProperty.end())
		return ChangeProperty(name.toStdString(), value) == 0;
	else
		return AddProperty(name.toStdString(), value) == 0;
}

bool SLGCGameBase::getGameProperty(const QString& name, int& value)
{
	return QueryProperty(name.toStdString(), &value) == 0;
}

int SLGCGameBase::getIntGameProperty(const QString& name)
{
	int ret = 0;
	getGameProperty(name, ret);
	return ret;
}

QString SLGCGameBase::getStringGameProperty(const QString& name)
{
	QString ret;
	getGameProperty(name, ret);
	return ret;
}
