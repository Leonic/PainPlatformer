#pragma once
#ifndef __PAINOBJ_H__
#define __PAINOBJ_H__

#include <string>
#include "BaseObject.h"

class CPainObject : public IBaseObject
{
public:
	CPainObject();
	CPainObject(const char* name, std::string textureID, CVector2D position, CVector2D size);

	virtual void OnPlay() override;
	virtual void OnDraw() override;
	virtual void OnThink() override;

	virtual CVector2D GetPosition() override { return m_vPosition; }
	virtual void SetPosition(CVector2D& nPos) override;

	virtual const char* GetName() override { return m_sName; }

	virtual void OnOverlapStart(IBaseObject* other) override;
	virtual void OnOverlapEnd(IBaseObject* event) override;

protected:
	const char* m_sName = "";
	std::string m_sTextureID = "";

	CVector2D m_vPosition = CVector2D(0, 0);
	CVector2D m_vVelocity = CVector2D(0, 0);
	CVector2D m_vAcceleration = CVector2D(0, 0);

	bool m_bShouldDraw = false;
	bool m_bIsOverlapping = false;

	int m_iWidth = 0;
	int m_iHeight = 0;

	int m_iCurrentFrame = 0;
	int m_iCurrentRow = 0;
};

#endif