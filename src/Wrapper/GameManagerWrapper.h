#ifndef GAMEMANAGERWRAPPER_H
#define GAMEMANAGERWRAPPER_H

#include <QObject>
#include "GameManager.h"

class GameManagerWrapper : public QObject
{
    Q_OBJECT
public:
    explicit GameManagerWrapper(GameManager* gm = nullptr, QObject *parent = nullptr);

signals:

private:
    GameManager* m_gm = nullptr;
};

#endif // GAMEMANAGERWRAPPER_H
