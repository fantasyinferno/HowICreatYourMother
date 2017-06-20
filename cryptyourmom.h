#ifndef CRYPTYOURMOM_H
#define CRYPTYOURMOM_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class CryptYourMom;
}

class CryptYourMom : public QMainWindow
{
    Q_OBJECT

public:
    explicit CryptYourMom(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CryptYourMom();

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::CryptYourMom *ui;
    QSqlDatabase myDb;
};

#endif // CRYPTYOURMOM_H
