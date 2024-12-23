#include "pch.h"
#include "Player.h"

/*
========
Player
========
*/

bool Player::Initialize(IT_EngineCore* engineCore, IT_Level* curLevel, Game* game)
{
    IT_GeometryObject* geoObj = engineCore->CreateGeometryObject(GEOMETRY_TYPE::SPHERE, true);
    geoObj->SetScale(0.5f, 0.8f, 0.5f); // 160cm °¡Á¤
    geoObj->SetPosition(Vector3(0.0f, 0.8f, 0.0f));
    m_position = Vector3(0.0f);

    m_geoObj = geoObj;

    curLevel->AddGmaeObject(m_geoObj, GAME_OBJ_TYPE::PLAYER);

    return true;
}

void Player::Tick()
{

}

void Player::CleanUp()
{
}
