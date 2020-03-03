#ifndef CLOCK_H
#define CLOCK_H

#include <systemc.h>
#include <QObject>
#include <QTimer>

class Clock:public QObject, public sc_module
{
    Q_OBJECT
public:
    SC_CTOR(Clock)


    {
        SC_METHOD(op){}
        connect(this->timer, SIGNAL(timeout()),this,SLOT(next()));
    }

public slots:
    Q_INVOKABLE void next()
    {
        emit this->newCycle();
        clk.write(true);
        sc_start(10, SC_NS);
        clk.write(false);
        sc_start(10, SC_NS);
    }

    Q_INVOKABLE void start(int ms)
    {
        sc_start(0, SC_NS);
        timer->setInterval(ms);
        timer->setSingleShot(false);
        timer->start();
    }

    Q_INVOKABLE void stop()
    {
        timer->stop();
        sc_stop();
    }

    Q_INVOKABLE void pause()
    {
        timer->stop();
    }

signals:
    void newCycle();


public:
    sc_out<bool> clk;
private:
    void op(){}
    QTimer *timer = new QTimer(this);
};

#endif // CLOCK_H
