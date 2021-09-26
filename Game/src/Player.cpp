#include "Player.h"
#include "EventHandler.h"

CPlayer::CPlayer(const char* name, std::string textureID, CVector2D position, CVector2D size)
{
	m_sName = name;
	m_sTextureID = textureID;
	m_vPosition = position;
	m_vAcceleration = CVector2D(0, 9.8);

	m_bShouldDraw = true;
	m_iWidth = size.GetX();
	m_iHeight = size.GetY();
}

void CPlayer::OnPlay()
{
	CEventHandler::Instance()->AddOnMouseDown(std::bind(&CPlayer::Jump, this, std::placeholders::_1));
	CEventHandler::Instance()->AddOnFingerDown(std::bind(&CPlayer::Jump, this, std::placeholders::_1));
}

void CPlayer::OnThink()
{
	m_vPosition += m_vVelocity;

	if (m_vPosition.GetY() + m_vAcceleration.GetY() + 128 > HEIGHT)
		m_vPosition.SetY(HEIGHT-128);
	else
		m_vVelocity += m_vAcceleration;
}

void CPlayer::Jump(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	case SDL_FINGERDOWN:
		m_vVelocity += CVector2D(0, 10);
		break;
	}
}
