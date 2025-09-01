#include "GameManagerWrapper.h"

GameManagerWrapper::GameManagerWrapper(GameManager* gm, QObject *parent)
    : QObject{parent}, m_gm(gm)
{}
