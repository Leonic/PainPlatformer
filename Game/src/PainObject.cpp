#include "PainObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

CPainObject::CPainObject()
{
}

CPainObject::CPainObject(const char* name, std::string textureID, CVector2D position, CVector2D size)
{
	m_sName = name;
	m_sTextureID = textureID;
	m_vPosition = position;

	m_bShouldDraw = true;
	m_iWidth = size.GetX();
	m_iHeight = size.GetY();
}

void CPainObject::OnPlay()
{
}

void CPainObject::OnDraw()
{
	if (m_bShouldDraw)
	{
		if (m_vVelocity.GetX() > 0)
		{
			CTextureManager::Instance()->DrawFrame(m_sTextureID, (int)m_vPosition.GetX(),
				(int)m_vPosition.GetY(), m_iWidth, m_iHeight,
				m_iCurrentRow, m_iCurrentFrame, CGame::Instance()->GetRenderer(),
				SDL_FLIP_HORIZONTAL);
		}
		else
		{
			/*CTextureManager::Instance()->DrawFrame(m_sTextureID, (int)m_vPosition.GetX(),
				(int)m_vPosition.GetY(), m_iWidth, m_iHeight,
				m_iCurrentRow, m_iCurrentFrame, CGame::Instance()->GetRenderer());*/
			CTextureManager::Instance()->Draw(m_sTextureID, (int)m_vPosition.GetX(), (int)m_vPosition.GetY(),
				m_iWidth, m_iHeight, CGame::Instance()->GetRenderer());
		}
	}
}

void CPainObject::OnThink()
{
}

void CPainObject::SetPosition(CVector2D& nPos)
{
	m_vPosition = nPos;
}

void CPainObject::OnOverlapStart(IBaseObject* other)
{
	m_bIsOverlapping = true;

	std::cout << "["<< m_sName << "] Overlapping start!" << std::endl;
}

void CPainObject::OnOverlapEnd(IBaseObject* event)
{
	m_bIsOverlapping = true;

	std::cout << "[" << m_sName << "] Overlapping end!" << std::endl;
}