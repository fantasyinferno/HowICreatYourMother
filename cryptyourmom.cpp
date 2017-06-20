#include "cryptyourmom.h"
#include "ui_cryptyourmom.h"
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSqlError>
CryptYourMom::CryptYourMom(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::CryptYourMom)
{
    ui->setupUi(this);
    myDb = database;
    ui->lineEdit->setText(myDb.databaseName());
}

CryptYourMom::~CryptYourMom()
{
    delete ui;
}

void CryptYourMom::on_pushButton_clicked()
{
    QSqlQuery query(0, myDb);
    query.prepare("SELECT password FROM account");
    if (!query.exec()) {
        qDebug() << query.lastError();
        return;
    }
    while (query.next()) {
        QString oldPassword = query.value(0).toString();
        QByteArray newPassword = QCryptographicHash::hash(oldPassword.toUtf8(), QCryptographicHash::Sha3_512);
        QSqlQuery anotherQuery(0, myDb);
        anotherQuery.prepare("UPDATE account SET password = ? WHERE password = ?");
        anotherQuery.addBindValue(newPassword);
        anotherQuery.addBindValue(oldPassword);
        if (!anotherQuery.exec()) {
            qDebug() << anotherQuery.lastError();
            return;
        }
    }
    QMessageBox::information(this, "Success (of course it must)", "You have successfully crypt'd your mother!");
}

void CryptYourMom::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Database Files (*.db)"));
    myDb.setDatabaseName(fileName);
    ui->lineEdit->setText(fileName);
    if (!myDb.open()) {
        QMessageBox::warning(this, "Unable to load mom", "Maybe that's not your mom!");
    }
}
