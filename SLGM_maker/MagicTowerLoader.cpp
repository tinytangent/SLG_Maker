#include <QFileInfo>
#include <QFileInfoList>
#include <QFile>
#include <QDir>
#include <QString>
#include <QMessageBox>
#include "MagicTowerLoader.h"
#include "SLGCResourceManager.h"
#include "script.h"

MagicTowerLoader::MagicTowerLoader(SLGMEditorScene *_scene)
{
    this->scene = _scene;
}

MagicTowerLoader::~MagicTowerLoader()
{
}

void MagicTowerLoader::loadResource(const QString& resourcePath)
{
    QDir resourceDir(resourcePath);
    QFileInfoList resourceList = resourceDir.entryInfoList();
    for(int i=0;i<resourceList.size();i++)
    {
        if(resourceList[i].isFile() && resourceList[i].suffix()=="png")
        {
			if(!SLGCResourceManager::getInstance()->addPixmap(resourceList[i].baseName(),resourceList[i].filePath()))
            {
                QMessageBox::critical(NULL,QString("警告"),
                                         QString("警告：存在未加载的资源文件。\n"
                                                 "试图加载%1时失败。\n"
                                                 "应用程序将继续，但如果这些资源在稍后被引用，可能造成其它错误信息。").arg(resourceList[i].filePath()));
            }
        }
		else if(resourceList[i].isFile() && resourceList[i].suffix()=="wav")
		{
			if(!SLGCResourceManager::getInstance()->addAudio(resourceList[i].baseName(),resourceList[i].filePath()))
			{
				QMessageBox::critical(NULL,QString("警告"),
										 QString("Audio Load Fail %1").arg(resourceList[i].filePath()));
			}
		}
    }
}

void MagicTowerLoader::loadPreset(const QString& presetFileName)
{
    QFile presetFile(presetFileName);
    presetFile.open(QFile::ReadOnly);
    QTextStream presetFileStream(&presetFile);
    QString className;
    QMap<QString, QString> parameters;
    for(;;)
    {
        QString str = presetFileStream.readLine();
        str = str.trimmed();
        if(str.startsWith("#")) continue;
        if(presetFileStream.atEnd() || (str.startsWith("[")&&str.endsWith("]")))
        {
            if(className.size()>0)
            {
                if(className == "GeneralItemHandler")
                {
                    addPresetGeneralItemHandler(parameters);
                }
                else if(className == "MagicTowerPassiveObject")
                {
                    addPresetPassiveObject(parameters);
                }
                else if(className == "NPCDialogData")
                {
                    addPresetNPCDialogData(parameters);
                }
                else if(className == "MonsterHandler")
                {
                    addPresetMonsterHandler(parameters);
                }
                else if(className == "NPCHandler")
                {
                    addPresetNPCHandler(parameters);
                }
                else if(className == "TransportHandler")
                {
                    addPresetTransporterHandler(parameters);
                }
                else if(className == "MagicTowerCharacter")
                {
                    addPresetCharacter(parameters);
                }
                parameters.clear();
            }
            str[0] = QChar(' ');
            str[str.size()-1] = QChar(' ');
            str = str.trimmed();
            className = str;
        }
        else if(str.size()>0&&(!str.startsWith("#")))
        {
            QStringList lineParts = str.split("=");
            if(lineParts.size()==2)
            {
                parameters[lineParts[0].trimmed()] = lineParts[1].trimmed();
            }
        }
        if(presetFileStream.atEnd()) break;

    }
    presetFile.close();
}

void MagicTowerLoader::loadMap(const QString &mapPath)
{
    QFile mapFile(mapPath);
    mapFile.open(QFile::ReadOnly);
    QTextStream mapFileStream(&mapFile);
    QString sectionName;
    QMap<QString, QString> parameters;
    for(;;)
    {
        QString str = mapFileStream.readLine();
        str = str.trimmed();
        if(str.startsWith("[")&&str.endsWith("]"))
        {
            str[0] = QChar(' ');
            str[str.size()-1] = QChar(' ');
            str = str.trimmed();
        }
        QStringList mapParts = str.split("/");
        if(mapParts.size()<=1) continue;
        QString mapName = mapParts[1];
		//scene->game->addMap(mapName,13,13);

		//TODO : This is a temporary hack! will not use
		SLGCGameMap* map = scene->game->getMap(mapName);
        map->addLayer("character",200);
		//map->addLayer("main",100);
        map->addLayer("ground",0);

		QString musicLine = mapFileStream.readLine();
		map->backgroundMusic = musicLine.trimmed();
        for(int i=0;i<13;i++)
        {
            if(i==0||i==12)
            {
                for(int j=0;j<13;j++)
                {
                    SLGCGameUnit* obj = new SLGCGameUnit();
                    obj->setPixmap("ground");
					scene->setObjectAt(mapName,"ground",j,i,obj);

                    obj = new MagicTowerPassiveObject();
                    obj->setPixmap("wall_brown");
					scene->setObjectAt(mapName,"main",j,i,obj);
                }
                continue;
            }
            qDebug()<<i;
            QString mapLine = mapFileStream.readLine();
            QStringList mapLineParts = mapLine.split("|");
            for(int j=0;j<13;j++)
            {
                SLGCGameUnit* obj = new SLGCGameUnit();
                obj->setPixmap("ground");
				scene->setObjectAt(mapName,"ground",j,i,obj);
                if(j==0||j==12)
                {
                    MagicTowerPassiveObject* obj = new MagicTowerPassiveObject();
                    obj->setPixmap("wall_brown");
					scene->setObjectAt(mapName,"main",j,i,obj);
                }
                else
                {
                    MagicTowerPassiveObject* obj = NULL;
                    if(mapLineParts[j-1] != "" && mapLineParts[j-1]!="null" && mapLineParts[j-1]!="void")
                    {
                        if(getPreset<MagicTowerPassiveObject>(mapLineParts[j-1])!=NULL)
                        {
                            obj = (MagicTowerPassiveObject*)getPreset<MagicTowerPassiveObject>(mapLineParts[j-1])->clone();
                        }
                        else
                        {
                            QMessageBox::critical(NULL,QString("警告"),
                                                     QString("警告：游戏地图中指定了无效对象预设%1。\n"
                                                             "应用程序将继续，但这些对象的丢失可能影响游戏体验。")
                                                  .arg(mapLineParts[j-1]));
                        }
                    }
					scene->setObjectAt(mapName,"main",j,i,obj);
                }
            }
        }
        if(mapFileStream.atEnd()) break;
    }
    mapFile.close();
}

bool MagicTowerLoader::addPresetPassiveObject(const QMap<QString,QString>& parameters)
{
    QString presetName = parameters["name"];
    MagicTowerPassiveObject* object = new MagicTowerPassiveObject();
    if(parameters.find("pixmap")!=parameters.end())
    {
		if(SLGCResourceManager::getInstance()->getPixmap(parameters["pixmap"]).isNull())
        {
            QMessageBox::critical(NULL,QString("警告"),
                                     QString("警告：预设%1试图引用未加载的资源文件。\n"
                                             "引用的位图资源%2不存在。\n"
                                             "应用程序将继续，但该预设不会被存储，这在之后可能造成其它错误信息。")
                                  .arg(presetName)
                                  .arg(parameters["pixmap"]));
            delete object;
            return false;
        }
        object->setPixmap(parameters["pixmap"]);
    }
    if(parameters.find("pixmapAnimation")!=parameters.end())
    {
        object->setTwoFrameAnimation(parameters["pixmapAnimation"]);
    }
    if(parameters.find("handler")!=parameters.end())
    {
        object->handler = this->getPreset<MTPOEHandler>(parameters["handler"]);
    }
    //TODO: more properties should be regarded as extra game property.
    qDebug() << "Property PIXMAP" << presetName;
    QMap<QString, QString>::const_iterator i = parameters.begin();
    while (i != parameters.end())
    {
        //if(i.key()!="name"&&i.key()!="handler"&&i.key()!="pixmap"&&i.key()!="pixmapAnimation")
            object->setGameProperty(i.key(),i.value().toInt());
        i++;
    }
    object->setPresetName(presetName);
    objectPreset[presetName] = object;
    return true;
}

bool MagicTowerLoader::addPresetGeneralItemHandler(const QMap<QString,QString>& parameters)
{
    QString presetName = parameters["name"];
    QString targetProperty = parameters["targetProperty"];
    int targetDeltaValue = parameters["targetDeltaValue"].toInt();
    objectPreset[presetName] = new GeneralItemHandler(targetProperty, targetDeltaValue);
    return true;
}

void MagicTowerLoader::addPresetNPCDialogData(const QMap<QString, QString>& parameters)
{
    NPCDialogData* object = new NPCDialogData();
    QString presetName = parameters["name"];
    for(int i=1;;i++)
    {
        QString pattern = QString("page%1_").arg(i);
        if(parameters.find(pattern+"title")==parameters.end()) break;
        QString title = parameters[pattern+"title"];
        QString titlePixmap = parameters[pattern+"titlePixmap"];
        QString content = parameters[pattern+"content"];
        if(parameters.find(pattern+"options")==parameters.end())
        {
            object->addPage(titlePixmap,title,content);
            continue;
        }
        QStringList listOption = parameters[pattern+"options"].trimmed().split("|");
        QStringList listProp = parameters[pattern+"purchasedProperties"].trimmed().split("|");
        QString costProperty = parameters[pattern+"costProperty"];
        int costValues = parameters[pattern+"costValues"].toInt();
        int costIncreaseMode = parameters[pattern+"costIncreaseMode"].toInt();
        int costIncreaseRate = parameters[pattern+"costIncreaseRate"].toInt();
        QStringList listValueString = parameters[pattern+"purchasedValues"].trimmed().split("|");
        QList<int> listValue;
        for(int i=0;i<listValueString.size();i++)
        {
            listValue << listValueString[i].toInt();
        }
        object->addPage(titlePixmap,title,content,costProperty,costValues,costIncreaseMode,costIncreaseRate,listOption,listProp,listValue);
    }
    objectPreset[presetName] = object;
}

bool MagicTowerLoader::addPresetMonsterHandler(const QMap<QString,QString>& parameters)
{
    QString presetName = parameters["name"];
    objectPreset[presetName] = new MonsterHandler();
    return false;
}

bool MagicTowerLoader::addPresetTransporterHandler(const QMap<QString,QString>& parameters)
{
    QString presetName = parameters["name"];
    QString targetMap = parameters["targetMap"];
    QString targetLayer = parameters["targetLayer"];
    int targetX = parameters["targetX"].toInt();
    int targetY = parameters["targetY"].toInt();
    objectPreset[presetName] = new TransporterHandler(targetMap,targetLayer,targetX,targetY);
    return false;
}

bool MagicTowerLoader::addPresetNPCHandler(const QMap<QString,QString>& parameters)
{
    QString presetName = parameters["name"];
    QString dialogPages = parameters["dialogPages"];
    objectPreset[presetName] = new NPCHandler(*getPreset<NPCDialogData>(dialogPages));
    return true;
}

bool MagicTowerLoader::addPresetCharacter(const QMap<QString, QString> &parameters)
{
    QString presetName = parameters["name"];
    MagicTowerCharacter* object = new MagicTowerCharacter();
    if(parameters.find("characterAnimation")==parameters.end())
    {
        QMessageBox::critical(NULL,QString("警告"),
                                 QString("警告：角色预设%1没有指定有效的角色动画表。\n"
                                         "应用程序将继续，但该预设不会被存储，这在之后可能造成其它错误信息。")
                              .arg(presetName));
        delete object;
        return false;
    }
	if(SLGCResourceManager::getInstance()->getPixmap(parameters["characterAnimation"]).isNull())
    {
        QMessageBox::critical(NULL,QString("警告"),
                                 QString("警告：预设%1试图引用未加载的资源文件。\n"
                                         "引用的位图资源%2不存在。\n"
                                         "应用程序将继续，但该预设不会被存储，这在之后可能造成其它错误信息。")
                              .arg(presetName)
                              .arg(parameters["characterAnimation"]));
        delete object;
        return false;
    }
    object->setCharacterAnimation(parameters["characterAnimation"]);

    QMap<QString, QString>::const_iterator i = parameters.begin();
    while (i != parameters.end())
    {
        if(i.key()=="name"||i.key()=="characterAnimation")
        {
            i++;
            continue;
        }
        object->setGameProperty(i.key(),i.value().toInt());
        i++;
    }
    object->setPresetName(presetName);
    objectPreset[presetName] = object;
    return true;
}

void MagicTowerLoader::loadGame(const QString& gamePath)
{
	SLGCResourceManager::init();
    loadResource(gamePath+"/res");
    loadPreset(gamePath + "/startup.mtpreset.ini");
	scene->game->loadMap(gamePath + "/map.xml");
}

void MagicTowerLoader::unloadGame()
{
    QMapIterator<QString, QObject*> i(objectPreset);
    while (i.hasNext())
    {
        i.next();
        delete i.value();
    }
    objectPreset.clear();
    scene->reset();
	SLGCResourceManager::release();
}

bool MagicTowerLoader::saveGame(const QString& directoryName, const QString& saveName)
{
    QFile mapFile(directoryName + "/" + saveName + ".mtsavedmap.ini");
    QFile extraFile(directoryName + "/" + saveName + ".mtsavedextra.ini");
    if(!mapFile.open(QIODevice::WriteOnly))
    {
        return false;
    }
    if(!extraFile.open(QIODevice::WriteOnly))
    {
        mapFile.close();
        return false;
    }
    QTextStream mapOutputStream(&mapFile);
    QTextStream extraOutputStream(&extraFile);
	QStringList maps = scene->game->allMaps();
	for(int i=0;i<maps.size();i++)
    {
        QString title = QString("[map/")+maps[i]+"]";
        mapOutputStream << title << "\r\n";
        for(int j=1;j<12;j++)
        {
            QString line;
            for(int k=1;k<12;k++)
            {
				if(scene->game->getObjectAt(maps[i],"main",k,j)!=NULL)
					line.append(scene->game->getObjectAt(maps[i],"main",k,j)->presetName);
                else
                    line.append("null");
                if(k!=12)
                {
                    line.append("|");
                }
				MagicTowerCharacter* character = dynamic_cast<MagicTowerCharacter*>(scene->game->getObjectAt(maps[i],"character",k,j));
                if(character!=NULL)
                {
                    extraOutputStream << "[Character]" << "\r\n";
                    extraOutputStream << "map = " << maps[i] << "\r\n";
                    extraOutputStream << "x = " << k << "\r\n";
                    extraOutputStream << "y = " << j << "\r\n";
					const QMap<QString,int>& properties = character->getAllIntGameProperties();
                    QMap<QString, int>::const_iterator i = properties.begin();
                    while(i != properties.end())
                    {
                        extraOutputStream << i.key() << " = " << i.value() << "\r\n";
                        i++;
                    }
                }
            }
            mapOutputStream << line << "\r\n";
        }
    }
    mapFile.close();
    extraOutputStream << "\r\n";
    extraFile.close();
}

void MagicTowerLoader::loadSavedGame(const QString& directoryName, const QString& saveName)
{
    scene->reset();
    loadMap(directoryName + "/" + saveName + ".mtsavedmap.ini");
    QFile extraFile(directoryName + "/" + saveName + ".mtsavedextra.ini");
    extraFile.open(QFile::ReadOnly);
    QTextStream extraFileStream(&extraFile);
    QString className;
    QMap<QString, QString> parameters;
    for(;;)
    {
        QString str = extraFileStream.readLine();
        str = str.trimmed();
        if(extraFileStream.atEnd() || (str.startsWith("[")&&str.endsWith("]")))
        {
            if(className.size()>0)
            {
                if(className == "Character")
                {
                    QString map = parameters["map"];
                    int x = parameters["x"].toInt();
                    int y = parameters["y"].toInt();
                    scene->setObjectAt(map,"character",x,y,getPreset<MagicTowerCharacter>("warrior")->clone());
                    MagicTowerCharacter* character = dynamic_cast<MagicTowerCharacter*>(
								scene->game->getObjectAt(map,"character",x,y));
                    if(character!=NULL)
                    {
                        QMap<QString, QString>::const_iterator i = parameters.begin();
                        while (i != parameters.end())
                        {
                            if(i.key()=="x"||i.key()=="y"||i.key()=="map")
                            {
                                i++;
                                continue;
                            }
                            character->setGameProperty(i.key(),i.value().toInt());
                            i++;
                        }
                        scene->setActiveCharacter(character);
                    }
                }
                parameters.clear();
            }
            str[0] = QChar(' ');
            str[str.size()-1] = QChar(' ');
            str = str.trimmed();
            className = str;
        }
        else if(str.size()>0)
        {
            QStringList lineParts = str.split("=");
            if(lineParts.size()==2)
            {
                parameters[lineParts[0].trimmed()] = lineParts[1].trimmed();
            }
        }
        if(extraFileStream.atEnd()) break;
    }
    extraFile.close();
}

QMap<QString, QObject*>& MagicTowerLoader::allPresets()
{
	return objectPreset;
}
