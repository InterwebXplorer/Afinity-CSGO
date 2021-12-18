#include "netvar.h"
#include "config.h"
#include "interfaces.h"

bool CNetvarManager::Setup(const std::string_view szDumpFileName)
{
	mapProps.clear();
	iStoredProps = 0;
	iStoredTables = 0;

	const std::string szTime = fmt::format(XorStr("[{:%d-%m-%Y %X}] "), fmt::localtime(std::time(nullptr)));

	#ifdef _DEBUG
	fsDumpFile.open(C::GetWorkingPath().append(szDumpFileName), std::ios::out | std::ios::trunc);

	if (fsDumpFile.good())
		fsDumpFile << szTime << XorStr("afinity | netvars dump\n\n");
	#endif

	for (auto pClass = I::Client->GetAllClasses(); pClass != nullptr; pClass = pClass->pNext)
	{
		if (pClass->pRecvTable == nullptr)
			continue;

		StoreProps(pClass->szNetworkName, pClass->pRecvTable, 0U, 0);
	}

	#ifdef _DEBUG
	fsDumpFile.close();
	#endif

	return !mapProps.empty();
}

void CNetvarManager::StoreProps(const char* szClassName, RecvTable_t* pRecvTable, const std::uintptr_t uOffset, const int iDepth)
{
	#ifdef _DEBUG
	std::string szDepth = { };

	for (int i = 0; i < iDepth; i++)
		szDepth.append("\t");

	if (fsDumpFile.good())
		fsDumpFile << fmt::format(XorStr("{0}[{1}]\n"), szDepth, pRecvTable->szNetTableName);
	#endif

	for (int i = 0; i < pRecvTable->nProps; ++i)
	{
		const auto pCurrentProp = &pRecvTable->pProps[i];

		if (pCurrentProp == nullptr || isdigit(pCurrentProp->szVarName[0]))
			continue;

		if (FNV1A::Hash(pCurrentProp->szVarName) == FNV1A::HashConst("baseclass"))
			continue;

		if (const auto pChildTable = pCurrentProp->pDataTable; pChildTable != nullptr &&
			pChildTable->nProps > 0 &&
			pChildTable->szNetTableName[0] == 'D' &&
			pCurrentProp->iRecvType == DPT_DATATABLE)
			StoreProps(szClassName, pChildTable, static_cast<std::uintptr_t>(pCurrentProp->iOffset) + uOffset, iDepth + 1);

		const FNV1A_t uHash = FNV1A::Hash(fmt::format(XorStr("{}->{}"), szClassName, pCurrentProp->szVarName).c_str());
		const std::uintptr_t uTotalOffset = static_cast<std::uintptr_t>(pCurrentProp->iOffset) + uOffset;

		if (!mapProps[uHash].uOffset)
		{
			#ifdef _DEBUG
			if (fsDumpFile.good())
				fsDumpFile << fmt::format(XorStr("{0}\t{1} {2} = 0x{3:04X};\n"), szDepth, GetPropertyType(pCurrentProp), pCurrentProp->szVarName, uTotalOffset);
			#endif

			mapProps[uHash] = { pCurrentProp, uTotalOffset };

			iStoredProps++;
		}
	}

	iStoredTables++;
}

std::string CNetvarManager::GetPropertyType(const RecvProp_t* pRecvProp) const
{
	static CStandartRecvProxies* pStandartRecvProxies = I::Client->GetStandardRecvProxies();

	if (pRecvProp == nullptr)
		return "";

	RecvVarProxyFn pProxyFn = pRecvProp->oProxyFn;

	switch (pRecvProp->iRecvType)
	{
	case DPT_INT:
		if (pProxyFn == pStandartRecvProxies->pInt32ToInt8)
			return XorStr("byte");
		else if (pProxyFn == pStandartRecvProxies->pInt32ToInt16)
			return XorStr("short");

		return XorStr("int");
	case DPT_FLOAT:
		return XorStr("float");
	case DPT_VECTOR:
		return XorStr("Vector");
	case DPT_VECTOR2D:
		return XorStr("Vector2D");
	case DPT_STRING:
		return fmt::format(XorStr("char[{}]"), pRecvProp->nStringBufferSize);
	case DPT_ARRAY:
		return fmt::format(XorStr("array[{}]"), pRecvProp->iElements);
	case DPT_DATATABLE:
		return XorStr("void*");
	case DPT_INT64:
		return XorStr("std::int64_t");
	default:
		break;
	}

	return "";
}

std::uintptr_t CNetvarManager::FindInDataMap(DataMap_t* pMap, const FNV1A_t uFieldHash)
{
	while (pMap != nullptr)
	{
		for (int i = 0; i < pMap->nDataFields; i++)
		{
			if (pMap->pDataDesc[i].szFieldName == nullptr)
				continue;

			if (FNV1A::Hash(pMap->pDataDesc[i].szFieldName) == uFieldHash)
				return pMap->pDataDesc[i].iFieldOffset[TD_OFFSET_NORMAL];

			if (pMap->pDataDesc[i].iFieldType == FIELD_EMBEDDED)
			{
				if (pMap->pDataDesc[i].pTypeDescription != nullptr)
				{
					if (const auto uOffset = FindInDataMap(pMap->pDataDesc[i].pTypeDescription, uFieldHash); uOffset != 0U)
						return uOffset;
				}
			}
		}

		pMap = pMap->pBaseMap;
	}

	return 0U;
}
