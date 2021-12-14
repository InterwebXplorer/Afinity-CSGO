#pragma once
#include <any>
#include <filesystem>
#include <deque>
#include <vector>

#include "Resources/common.h"
#include "../Source/Resources/SDK/datatypes/color.h"
#include "../Source/Resources/SDK/hash/fnv1a.h"

#pragma region config_definitions
#define C_ADD_VARIABLE( Type, szName, pDefault ) const std::uint32_t szName = C::AddVariable<Type>(FNV1A::HashConst(#szName), FNV1A::HashConst(#Type), pDefault);
#define C_ADD_VARIABLE_VECTOR( Type, uSize, szName, pDefault ) const std::uint32_t szName = C::AddVariable<std::vector<Type>>(FNV1A::HashConst(#szName), FNV1A::HashConst("std::vector<" #Type ">"), MEM::GetFilledVector<Type, uSize>(pDefault));
#define C_INVALID_VARIABLE (std::size_t)(-1)
#pragma endregion

struct VariableObject_t
{
	VariableObject_t(const FNV1A_t uNameHash, const FNV1A_t uTypeHash, std::any&& pDefault)
		: uNameHash(uNameHash), uTypeHash(uTypeHash), pValue(std::move(pDefault)) { }

	~VariableObject_t() = default;

	template<typename T>
	T& Get()
	{
		return *static_cast<T*>(std::any_cast<T>(&pValue));
	}

	template<typename T>
	void Set(T value)
	{
		pValue.emplace<T>(value);
	}

	FNV1A_t uNameHash = 0x0;
	FNV1A_t uTypeHash = 0x0;
	std::any pValue = { };
};

namespace C
{
	bool Setup(std::string_view szDefaultFileName);
	bool Save(std::string_view szFileName);
	bool Load(std::string_view szFileName);
	void Remove(const std::size_t nIndex);
	void Refresh();

	std::size_t GetVariableIndex(const FNV1A_t uNameHash);
	std::filesystem::path GetWorkingPath();

	const std::filesystem::path fsPath = GetWorkingPath() / XorStr("settings");
	inline std::deque<std::string> vecFileNames = { };
	inline std::vector<VariableObject_t> vecVariables = { };

	template <typename T>
	T& Get(const std::uint32_t nIndex)
	{
		return vecVariables.at(nIndex).Get<T>();
	}

	template <typename T>
	std::uint32_t AddVariable(const FNV1A_t uNameHash, const FNV1A_t uTypeHash, const T pDefault)
	{
		vecVariables.emplace_back(uNameHash, uTypeHash, std::make_any<T>(pDefault));
		return vecVariables.size() - 1U;
	}
}
