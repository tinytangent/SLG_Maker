#ifndef PIXMAPPOOL_H
#define PIXMAPPOOL_H

#include <QMap>
#include <QPixmap>
#include <QSoundEffect>

class QString;
class QPixmap;
class QSoundEffect;
/**
 * @brief PixmapPool类提供了一个图像缓存池，可以统一地加载位图并且通过一个字符串alias进行访问。
 */
class SLGCResourceManager
{
public:
    /**
     * @brief init初始化一个PixmapPool类的实例。如果这样的实例已经存在，则返回false。
     * @return
     */
    static bool init();

    /**
     * @brief release释放一个当前已经被初始化的实例。如果这样的示例不存在，返回false
     * @return
     */
    static bool release();

    /**
     * @brief getInstance获取当前唯一的位图缓冲池的实例
     * @return 当前位图缓冲池的示例，如果该实例不存在，返回NULL
     */
	static SLGCResourceManager* getInstance();
protected:
    /**
     * @brief nullPixmap是用于getPixmap在遇到错误的时候返回的空位图。
     */
    QPixmap nullPixmap;

	/**
	 * @brief nullAudio is used to return an empty QSoundEffect when get audio encounters error.
	 */
	QSoundEffect nullAudio;

    /**
     * @brief instance是一个保护的静态成员，是PixmapPool的唯一实例。
     */
	static SLGCResourceManager* instance;

    /**
     * @brief data用于存储字符串到对应位图的指针。
     */
	QMap<QString,QPixmap*> pixmapData;

	/**
	 * @brief audioData is used to store string to pointer of an audio.
	 */
	QMap<QString,QSoundEffect*> audioData;
protected:
    /**
     * @brief PixmapPool是受到保护的构造函数，他什么都不做，被保护是为了实现单例模式。
     */
	SLGCResourceManager();

    /**
      * @brief PixmapPool类的析构函数，用于释放所有已经为Pixmap对象分配的内存。
      */
	~SLGCResourceManager();
public:
    /**
     * @brief addPixmap 向位图缓冲池中添加一个位图
     * @param alias 为该位图设定的访问用的字符串别名
     * @param fileName 该位图的文件路径
     * @return 添加成功时，返回true，如果遇到问题，图片不会被添加，返回false
     */
    bool addPixmap(const QString& alias, const QString& fileName);

    /**
     * @brief getPixmap 读取之前添加到位图缓存中的一张位图
     * @param alias 为该位图设定的字符串别名
     * @return 如果具有指定的别名的位图已被正确加载，则返回该位图，否则返回一个空的QPixmap对象（可以使用isNull判断）。
     */
    const QPixmap& getPixmap(const QString& alias) const;

	bool addAudio(const QString& alias, const QString& fileName);

	QSoundEffect& getAudio(const QString& alias);
};

#endif // PIXMAPPOOL_H
