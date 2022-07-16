#pragma once
#include <vector>
#include "../sdk/interfaces/icliententitylist.h"

class CEntityListener : public IClientEntityListener
{
public:
	struct EntityObject_t
	{
		EntityObject_t(CBaseEntity *pEntity, int nIndex) : pEntity(pEntity), nIndex(nIndex) {}

		CBaseEntity *pEntity = nullptr;
		int nIndex = 0;
	};

	void Setup();
	void Destroy();

	virtual void OnEntityCreated(CBaseEntity *pEntity) override;
	virtual void OnEntityDeleted(CBaseEntity *pEntity) override;

	std::vector<EntityObject_t> vecEntities;
};
