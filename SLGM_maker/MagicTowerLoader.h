#ifndef MAGICTOWERLOADER_H
#define MAGICTOWERLOADER_H

#include <QMap>
#include <QDebug>

class SLGMEditorScene;
class QString;

class MagicTowerLoader
{
protected:
    //与加载器关联的场景对象
    SLGMEditorScene* scene;

    //加载的对象预设表
    QMap<QString, QObject*> objectPreset;
public:
    /**
     * @brief 构造一个魔塔加载器对象，在构造时需要指定与该加载器关联的游戏场景对象。
     * @param _scene 与加载器关联的场景对象的指针
     */
    MagicTowerLoader(SLGMEditorScene* _scene);

    /**
     * @brief loadResource用于从一个文件夹加载游戏的图片资源文件，该文件夹中所有具有.png扩展名的文件都会被加载到PixmapPool之中
     * @param resourcePath存放游戏资源的图片文件夹的路径
     */
    void loadResource(const QString& resourcePath);

    /**
     * @brief loadMap加载地图已经游戏角色的初始化属性
     * @param mapPath地图文件路径
     */
    void loadMap(const QString& mapPath);

    /**
     * @brief loadGame方法加载整个游戏数据。
     * @param gamePath制定游戏的路径，该路径下的应具有res文件夹啊，作为图片资源文件夹。同时应具有startup.mtpreset.ini
     *        和startup.mtmap.ini作为预设对象定义文件和地图定义文件。
     */
    void loadGame(const QString& gamePath);

    /**
     * @brief unloadGame方法卸载当前加载的一切游戏数据。这将造成游戏地图和预设被全部清除，位图缓冲池也会被释放。
     * 在两次调用loadGame之间，必须调用unloadGame方法以避免可能造成的一切冲突。
     */
    void unloadGame();

    /**
     * @brief saveGame 保存游戏的算法
     * @param directoryName 保存游戏的路径名
     * @param saveName 保存游戏的存档名
     * @return 是否保存成功
     */
    bool saveGame(const QString &directoryName, const QString &saveName);

    /**
     * @brief loadSavedGame 加载已经存盘的游戏的算法。
     * @param directoryName 保存游戏的路径名
     * @param saveName 保存游戏的存档名
     * @return 是否保存成功
     */
    void loadSavedGame(const QString& directoryName, const QString& saveName);

    //所有addPresetXXXX方法均是根据parameters创建预设对象的算法。
    bool addPresetGeneralItemHandler(const QMap<QString,QString>& parameters);
    bool addPresetMonsterHandler(const QMap<QString,QString>& parameters);
    bool addPresetTransporterHandler(const QMap<QString,QString>& parameters);
    bool addPresetNPCHandler(const QMap<QString,QString>& parameters);
    bool addPresetPassiveObject(const QMap<QString,QString>& parameters);
    void addPresetNPCDialogData(const QMap<QString, QString>& parameters);
    void addPreset(const QString& className, const QMap<QString,QString>& parameters);
    bool addPresetCharacter(const QMap<QString, QString>& parameters);
    void loadPreset(const QString &presetFileName);
    template<class T>
    T* getPreset(const QString& presetName)
    {
        return (T*)(objectPreset[presetName]);
    }

	QMap<QString, QObject*>& allPresets();
    //析构函数，用于释放资源。
    ~MagicTowerLoader();
};

#endif // MAGICTOWERLOADER_H
