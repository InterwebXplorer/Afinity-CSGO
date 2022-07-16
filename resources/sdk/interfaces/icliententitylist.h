#pragma once
using CBaseHandle = std::uintptr_t;
#include "../datatypes/utlvector.h"
#include "../entity.h"

class IClientEntityListener
{
public:
	virtual void OnEntityCreated(CBaseEntity *pEntity) {}
	virtual void OnEntityDeleted(CBaseEntity *pEntity) {}
};

class IClientNetworkable;
class IClientUnknown;
class IClientEntity;

class IClientEntityList
{
public:
	virtual IClientNetworkable *GetClientNetworkable(int nIndex) = 0;
	virtual IClientNetworkable *GetClientNetworkableFromHandle(CBaseHandle hNetworkable) = 0;
	virtual IClientUnknown *GetClientUnknownFromHandle(CBaseHandle hUnknown) = 0;
	virtual IClientEntity *GetClientEntity(int nIndex) = 0;
	virtual IClientEntity *GetClientEntityFromHandle(CBaseHandle hEntity) = 0;
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int GetHighestEntityIndex() = 0;
	virtual void SetMaxEntities(int iMax) = 0;
	virtual int GetMaxEntities() = 0;

	template <class T = IClientEntity>
	inline T *Get(const int nIndex)
	{
		return static_cast<T *>(GetClientEntity(nIndex));
	}

	template <class T = IClientEntity>
	inline T *Get(const CBaseHandle hEntity)
	{
		return static_cast<T *>(GetClientEntityFromHandle(hEntity));
	}

	void AddListenerEntity(IClientEntityListener *pListener)
	{
		vecEntityListeners.AddToTail(pListener);
	}

	void RemoveListenerEntity(IClientEntityListener *pListener)
	{
		vecEntityListeners.FindAndRemove(pListener);
	}

private:
	CUtlVector<IClientEntityListener *> vecEntityListeners;
};
