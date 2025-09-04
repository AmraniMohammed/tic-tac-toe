#ifndef GAMETYPESWRAPPER_H
#define GAMETYPESWRAPPER_H

#include <QObject>
#include "GameTypes.h"

class GameTypesWrapper : public QObject
{
    Q_OBJECT
public:
    Q_ENUM(Player)

    Q_ENUM(Winner)

    Q_ENUM(GameState)

    Q_ENUM(GameMode)

    Q_ENUM(BoardValue)
};

#endif // GAMETYPESWRAPPER_H
