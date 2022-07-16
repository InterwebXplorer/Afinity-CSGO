#pragma once
#include <fstream>
#include <unordered_map>
#include <Windows.h>
#include "../sdk/hash/fnv1a.h"
#include "../sdk/datatypes/datatable.h"
#include "../sdk/datatypes/datamap.h"

#pragma region netvar_definitions

#define N_ADD_VARIABLE_OFFSET(Type, szFunctionName, szNetVar, uAdditional)                                  \
	[[nodiscard]] std::add_lvalue_reference_t<Type> szFunctionName()                                        \
	{                                                                                                       \
		static constexpr FNV1A_t uHash = FNV1A::HashConst(szNetVar);                                        \
		static std::uintptr_t uOffset = CNetvarManager::Get().mapProps[uHash].uOffset;                      \
		return *(std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset + uAdditional); \
	}

#define N_ADD_VARIABLE(Type, szFunctionName, szNetVar) N_ADD_VARIABLE_OFFSET(Type, szFunctionName, szNetVar, 0U)

#define N_ADD_PVARIABLE_OFFSET(Type, szFunctionName, szNetVar, uAdditional)                                \
	[[nodiscard]] std::add_pointer_t<Type> szFunctionName()                                                \
	{                                                                                                      \
		static constexpr FNV1A_t uHash = FNV1A::HashConst(szNetVar);                                       \
		static std::uintptr_t uOffset = CNetvarManager::Get().mapProps[uHash].uOffset;                     \
		return (std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset + uAdditional); \
	}

#define N_ADD_PVARIABLE(Type, szFunctionName, szNetVar) N_ADD_PVARIABLE_OFFSET(Type, szFunctionName, szNetVar, 0U)

#define N_ADD_RESOURCE_VARIABLE(Type, szFunctionName, szNetVar)                                                       \
	[[nodiscard]] std::add_lvalue_reference_t<Type> szFunctionName(int nIndex)                                        \
	{                                                                                                                 \
		static constexpr FNV1A_t uHash = FNV1A::HashConst(szNetVar);                                                  \
		static std::uintptr_t uOffset = CNetvarManager::Get().mapProps[uHash].uOffset;                                \
		return *(std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset + nIndex * sizeof(Type)); \
	}

#define N_ADD_DATAFIELD(Type, szFunctionName, pMap, szDataField)                              \
	[[nodiscard]] std::add_lvalue_reference_t<Type> szFunctionName()                          \
	{                                                                                         \
		static constexpr FNV1A_t uHash = FNV1A::HashConst(szDataField);                       \
		static std::uintptr_t uOffset = CNetvarManager::Get().FindInDataMap(pMap, uHash);     \
		return *(std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset); \
	}

#define N_ADD_PDATAFIELD(Type, szFunctionName, pMap, szDataField)                            \
	[[nodiscard]] std::add_pointer_t<Type> szFunctionName()                                  \
	{                                                                                        \
		static constexpr FNV1A_t uHash = FNV1A::HashConst(szDataField);                      \
		static std::uintptr_t uOffset = CNetvarManager::Get().FindInDataMap(pMap, uHash);    \
		return (std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset); \
	}

#define N_ADD_OFFSET(Type, szFunctionName, uOffset)                                           \
	[[nodiscard]] std::add_lvalue_reference_t<Type> szFunctionName()                          \
	{                                                                                         \
		return *(std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset); \
	}

#define N_ADD_POFFSET(Type, szFunctionName, uOffset)                                         \
	[[nodiscard]] std::add_pointer_t<Type> szFunctionName()                                  \
	{                                                                                        \
		return (std::add_pointer_t<Type>)(reinterpret_cast<std::uintptr_t>(this) + uOffset); \
	}
#pragma endregion

class CRecvPropHook
{
public:
	CRecvPropHook(RecvProp_t *pRecvProp, const RecvVarProxyFn pNewProxyFn) : pRecvProp(pRecvProp), pOriginalFn(pRecvProp->oProxyFn)
	{
		SetProxy(pNewProxyFn);
	}

	void Replace(RecvProp_t *pRecvProp)
	{
		this->pRecvProp = pRecvProp;
		this->pOriginalFn = pRecvProp->oProxyFn;
	}

	void Restore() const
	{
		if (this->pOriginalFn != nullptr)
			this->pRecvProp->oProxyFn = this->pOriginalFn;
	}

	void SetProxy(const RecvVarProxyFn pNewProxyFn) const
	{
		this->pRecvProp->oProxyFn = pNewProxyFn;
	}

	RecvVarProxyFn GetOriginal() const
	{
		return this->pOriginalFn;
	}

private:
	RecvProp_t *pRecvProp = nullptr;

	RecvVarProxyFn pOriginalFn = nullptr;
};

class CNetvarManager : public CSingleton<CNetvarManager>
{
public:
	struct NetvarObject_t
	{
		RecvProp_t *pRecvProp = nullptr;
		std::uintptr_t uOffset = 0U;
	};

	bool Setup(const std::string_view szDumpFileName);

	std::uintptr_t FindInDataMap(DataMap_t *pMap, const FNV1A_t uFieldHash);

	int iStoredProps = 0;
	int iStoredTables = 0;

	std::unordered_map<FNV1A_t, NetvarObject_t> mapProps = {};

private:
	void StoreProps(const char *szClassName, RecvTable_t *pRecvTable, const std::uintptr_t uOffset, const int iDepth);

	std::string GetPropertyType(const RecvProp_t *pRecvProp) const;

	std::ofstream fsDumpFile = {};
};
