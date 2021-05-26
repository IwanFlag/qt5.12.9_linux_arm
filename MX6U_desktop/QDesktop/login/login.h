#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QDebug>


class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = 0);

signals:
    void sig_disp();

public slots:
    void login_verift_slot(int val);
};
#endif // LOGIN_H
