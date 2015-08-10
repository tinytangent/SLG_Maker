#ifndef SLGCGAMELOADER_H
#define SLGCGAMELOADER_H

class SLGCGame;
class SLGCGameBase;
class QString;
class QXmlStreamReader;

/**
 * @brief The SLGCGameLoader class is a helper class used to load a SLGMaker game project.
 * An object of the SLGCGameLoader class is always associated with an object of SLGCCGame.
 */
class SLGCGameLoader
{
protected:
	SLGCGame* game;
	bool parseMapFile(QXmlStreamReader* reader);
	bool parseMap(QXmlStreamReader* reader);
	bool parseLayer(QXmlStreamReader* reader, const QString& mapName);
	bool parseProperty(QXmlStreamReader* reader, SLGCGameBase* obj);
public:
	SLGCGameLoader(SLGCGame* _game);
	bool loadMap(const QString& fileName);
signals:

};

#endif // SLGCGAMELOADER_H
