#include "pch.h"
#include "CRigidBody.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{


	m_vForce = Vec2(0.f, 0.f);
}


