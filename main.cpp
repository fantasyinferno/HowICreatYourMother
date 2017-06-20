#include "cryptyourmom.h"
#include <QApplication>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("F:/SoftwareDevelopment/Qt/libpro/libpro.db");
    if (!db.open()) {
        return -1;
    }
    CryptYourMom w(0, db);
    w.show();

    return a.exec();
}
