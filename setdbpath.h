#ifndef SETDBPATH_H
#define SETDBPATH_H

#include <QDialog>

namespace Ui {
class SetDbPath;
}

class SetDbPath : public QDialog
{
    Q_OBJECT

public:
    explicit SetDbPath(QWidget *parent = nullptr);
    ~SetDbPath();

private slots:
    void on_exitDbApp_clicked();

    void on_saveDbPathBtn_clicked();

signals:
    void sendDbPath(const QString &newValue);
private:
    Ui::SetDbPath *ui;
};

#endif // SETDBPATH_H
