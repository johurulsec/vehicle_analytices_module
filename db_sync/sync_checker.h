#ifndef SYNC_CHECKER_H
#define SYNC_CHECKER_H

#include <QObject>
#include <QMutex>
#include <QDebug>
#include <QPixmap>
#include "QFile"

class sync_checker : public QObject
{
    Q_OBJECT
public:
    explicit sync_checker(QObject *parent = nullptr);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWorkSyChT();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abortSyChT();
    void writeIntoJSONFile(QString json);

    QString person, face; int id, source, status; QString date_time, mask_st;

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    std::string serverUrl;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;
signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void workRequestedChT();
    /**
     * @brief This signal is emitted when counted value is changed (every sec)
     */
    void finishedSyChT();
    void updateDb(int);
public slots:
    void doWarkSyncChe(int, QString, QString, QString, double, int, int, int);
    void doWarkSyncChe(int, QString, QString, QString, int, QString, int);
};

#endif // SYNC_CHECKER_H
