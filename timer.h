#ifndef TIMER_H
#define TIMER_H
#include <QObject>
#include<QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer();
    Q_INVOKABLE void setTime(int time);
    Q_INVOKABLE void Start();

private:
    QTimer *timer;
signals:
    void timesUp();

};

#endif // TIMER_H
