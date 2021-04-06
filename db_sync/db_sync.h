#ifndef DB_SYNC_H
#define DB_SYNC_H

#include <QObject>
#include <QMutex>
#include <QDebug>
#include <QPixmap>
#include <QFileDialog>
#include <QDir>

class db_sync : public QObject
{
    Q_OBJECT
public:
    explicit db_sync(QObject *parent = 0);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWorkSyTh();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abortSyTh();

    QPixmap pic_s;
    QString name_s, gender;
    int index_s;
    double confidence_s;


    QString encodeString(QString);
    void writeIntoJSONFile(QString);

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;
    int count =0, counter = 0;

signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void workRequestedSyTh();
    /**
     * @brief This signal is emitted when counted value is changed (every sec)
     */
    void finishedSyTh();
    void insertToDb(int Id, QPixmap pic, QString str, int indx, double confidence,
                    QString date_time, int sync_states, QString date, QString image_path, QString image_name, int, QString);

public slots:
    void doWarkSync(int Id, QPixmap, QString, int, double, QString);
};

#endif // DB_SYNC_H
