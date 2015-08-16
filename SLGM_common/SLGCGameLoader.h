#ifndef SLGCGAMELOADER_H
#define SLGCGAMELOADER_H

#include <QObject>

class SLGCGame;
class SLGCGameBase;
class QString;
class QXmlStreamReader;
class QXmlStreamWriter;

/**
 * @brief The SLGCGameLoader class is a helper class used to load a SLGMaker game project.
 * An object of the SLGCGameLoader class is always associated with an object of SLGCCGame.
 */
class SLGCGameLoader : public QObject
{
	Q_OBJECT
protected:
	SLGCGame* game;
	bool parseMapFile(QXmlStreamReader* reader);
	bool parseMap(QXmlStreamReader* reader);
	bool parseLayer(QXmlStreamReader* reader, const QString& mapName);
	bool parseProperty(QXmlStreamReader* reader, SLGCGameBase* obj);
	bool writeMapFile(QXmlStreamWriter* writer);
	bool writeMap(QXmlStreamWriter* writer, const QString& mapName);
	bool writeLayer(QXmlStreamWriter* writer);
	bool writeProperties(QXmlStreamWriter* writer, SLGCGameBase* obj);
public:
	SLGCGameLoader(SLGCGame* _game);
	bool loadMapFile(const QString& fileName);
	bool saveMapFile(const QString& fileName);
signals:
	void mapChanged(QString mapName, QString layerName, const int x, const int y, QString presetName);
};

#endif // SLGCGAMELOADER_H
