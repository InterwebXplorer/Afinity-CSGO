#include <shlobj.h>
#include <json.hpp>

#include "config.h"
#include "../Source/Resources/Utils/logging.h"

bool C::Setup(std::string_view szDefaultFileName)
{
	//Configs and shit located %userprofile%/AppData/Roaming/afinity
	if (!std::filesystem::is_directory(fsPath))
	{
		std::filesystem::remove(fsPath);
		if (!std::filesystem::create_directories(fsPath))
			return false;
	}

	if (!Save(szDefaultFileName))
		return false;

	if (!Load(szDefaultFileName))
		return false;

	Refresh();

	return true;
}

bool C::Save(std::string_view szFileName)
{
	std::filesystem::path fsFilePath(szFileName);
	if (fsFilePath.extension() != XorStr(".afinity"))
		fsFilePath.replace_extension(XorStr(".afinity"));

	const std::string szFile = std::filesystem::path(fsPath / fsFilePath).string();
	nlohmann::json config = { };

	try
	{
		for (auto& variable : vecVariables)
		{
			nlohmann::json entry = { };

			entry[XorStr("name-id")] = variable.uNameHash;
			entry[XorStr("type-id")] = variable.uTypeHash;

			switch (variable.uTypeHash)
			{
			case FNV1A::HashConst("int"):
			{
				entry[XorStr("value")] = variable.Get<int>();
				break;
			}
			case FNV1A::HashConst("float"):
			{
				entry[XorStr("value")] = variable.Get<float>();
				break;
			}
			case FNV1A::HashConst("bool"):
			{
				entry[XorStr("value")] = variable.Get<bool>();
				break;
			}
			case FNV1A::HashConst("std::string"):
			{
				entry[XorStr("value")] = variable.Get<std::string>();
				break;
			}
			case FNV1A::HashConst("Color"):
			{
				const auto& colVariable = variable.Get<Color>();

				nlohmann::json sub = { };

				sub.push_back(colVariable.Get<COLOR_R>());
				sub.push_back(colVariable.Get<COLOR_G>());
				sub.push_back(colVariable.Get<COLOR_B>());
				sub.push_back(colVariable.Get<COLOR_A>());

				entry[XorStr("value")] = sub.dump();
				break;
			}
			case FNV1A::HashConst("std::vector<bool>"):
			{
				const auto& vecBools = variable.Get<std::vector<bool>>();

				nlohmann::json sub = { };

				for (const auto&& bValue : vecBools)
					sub.push_back(static_cast<bool>(bValue));

				entry[XorStr("value")] = sub.dump();
				break;
			}
			case FNV1A::HashConst("std::vector<int>"):
			{
				const auto& vecInts = variable.Get<std::vector<int>>();

				nlohmann::json sub = { };

				for (const auto& iValue : vecInts)
					sub.push_back(iValue);

				entry[XorStr("value")] = sub.dump();
				break;
			}
			case FNV1A::HashConst("std::vector<float>"):
			{
				const auto& vecFloats = variable.Get<std::vector<float>>();

				nlohmann::json sub = { };

				for (const auto& flValue : vecFloats)
					sub.push_back(flValue);

				entry[XorStr("value")] = sub.dump();
				break;
			}
			default:
				break;
			}

			config.push_back(entry);
		}
	}
	catch (const nlohmann::detail::exception& ex)
	{
		L::PushConsoleColor(FOREGROUND_RED);
		L::Print(fmt::format(XorStr("[error] json save failed: {}"), ex.what()));
		L::PopConsoleColor();
		return false;
	}

	std::ofstream ofsOutFile(szFile, std::ios::out | std::ios::trunc);

	if (!ofsOutFile.good())
		return false;

	try
	{
		ofsOutFile << config.dump(4);
		ofsOutFile.close();
	}
	catch (std::ofstream::failure& ex)
	{
		L::PushConsoleColor(FOREGROUND_RED);
		L::Print(fmt::format(XorStr("[error] config save failed: {}"), ex.what()));
		L::PopConsoleColor();
		return false;
	}

	L::Print(fmt::format(XorStr("saved config at: {}"), szFile));
	return true;
}

bool C::Load(std::string_view szFileName)
{
	const std::string szFile = std::filesystem::path(fsPath / szFileName).string();
	nlohmann::json config = { };

	std::ifstream ifsInputFile(szFile, std::ios::in);

	if (!ifsInputFile.good())
		return false;

	try
	{
		config = nlohmann::json::parse(ifsInputFile, nullptr, false);

		if (config.is_discarded())
			return false;

		ifsInputFile.close();
	}
	catch (std::ifstream::failure& ex)
	{
		L::PushConsoleColor(FOREGROUND_RED);
		L::Print(fmt::format(XorStr("[error] failed to load config: {}"), ex.what()));
		L::PopConsoleColor();
		return false;
	}

	try
	{
		for (const auto& variable : config)
		{
			const std::size_t nIndex = GetVariableIndex(variable[XorStr("name-id")].get<FNV1A_t>());

			if (nIndex == C_INVALID_VARIABLE)
				continue;

			auto& entry = vecVariables.at(nIndex);

			switch (variable[XorStr("type-id")].get<FNV1A_t>())
			{
			case FNV1A::HashConst("bool"):
			{
				entry.Set<bool>(variable[XorStr("value")].get<bool>());
				break;
			}
			case FNV1A::HashConst("float"):
			{
				entry.Set<float>(variable[XorStr("value")].get<float>());
				break;
			}
			case FNV1A::HashConst("int"):
			{
				entry.Set<int>(variable[XorStr("value")].get<int>());
				break;
			}
			case FNV1A::HashConst("std::string"):
			{
				entry.Set<std::string>(variable[XorStr("value")].get<std::string>());
				break;
			}
			case FNV1A::HashConst("Color"):
			{
				const nlohmann::json vector = nlohmann::json::parse(variable[XorStr("value")].get<std::string>());

				entry.Set<Color>(Color(
					vector.at(0).get<std::uint8_t>(),
					vector.at(1).get<std::uint8_t>(),
					vector.at(2).get<std::uint8_t>(),
					vector.at(3).get<std::uint8_t>()
				));

				break;
			}
			case FNV1A::HashConst("std::vector<bool>"):
			{
				const nlohmann::json vector = nlohmann::json::parse(variable[XorStr("value")].get<std::string>());
				auto& vecBools = entry.Get<std::vector<bool>>();

				for (std::size_t i = 0U; i < vector.size(); i++)
				{
					if (i < vecBools.size())
						vecBools.at(i) = vector.at(i).get<bool>();
				}

				break;
			}
			case FNV1A::HashConst("std::vector<int>"):
			{
				const nlohmann::json vector = nlohmann::json::parse(variable[XorStr("value")].get<std::string>());
				auto& vecInts = entry.Get<std::vector<int>>();

				for (std::size_t i = 0U; i < vector.size(); i++)
				{
					if (i < vecInts.size())
						vecInts.at(i) = vector.at(i).get<int>();
				}

				break;
			}
			case FNV1A::HashConst("std::vector<float>"):
			{
				const nlohmann::json vector = nlohmann::json::parse(variable[XorStr("value")].get<std::string>());
				auto& vecFloats = entry.Get<std::vector<float>>();

				for (std::size_t i = 0U; i < vector.size(); i++)
				{
					if (i < vecFloats.size())
						vecFloats.at(i) = vector.at(i).get<float>();
				}

				break;
			}
			default:
				break;
			}
		}
	}
	catch (const nlohmann::detail::exception& ex)
	{
		L::PushConsoleColor(FOREGROUND_RED);
		L::Print(fmt::format(XorStr("[error] json load failed: {}"), ex.what()));
		L::PopConsoleColor();
		return false;
	}

	L::Print(fmt::format(XorStr("loaded config at: {}"), szFile));
	return true;
}

void C::Remove(const std::size_t nIndex)
{
	const std::string& szFileName = vecFileNames.at(nIndex);

	if (szFileName.compare(XorStr("default.afinity")) == 0)
		return;

	const std::string szFile = std::filesystem::path(fsPath / szFileName).string();

	if (std::filesystem::remove(szFile))
	{
		vecFileNames.erase(vecFileNames.cbegin() + nIndex);
		L::Print(fmt::format(XorStr("Config Removed: {}"), szFile));
	}
}

void C::Refresh()
{
	vecFileNames.clear();

	for (const auto& it : std::filesystem::directory_iterator(fsPath))
	{
		if (it.path().filename().extension() == XorStr(".afinity"))
		{
			L::Print(fmt::format(XorStr("Config file located: {}"), it.path().filename().string()));
			vecFileNames.push_back(it.path().filename().string());
		}
	}
}

std::size_t C::GetVariableIndex(const FNV1A_t uNameHash)
{
	for (std::size_t i = 0U; i < vecVariables.size(); i++)
	{
		if (vecVariables.at(i).uNameHash == uNameHash)
			return i;
	}

	return C_INVALID_VARIABLE;
}

std::filesystem::path C::GetWorkingPath()
{
	std::filesystem::path fsWorkingPath;

	if (PWSTR pszPathToAppData; SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0UL, nullptr, &pszPathToAppData)))
	{
		fsWorkingPath.assign(pszPathToAppData);
		fsWorkingPath.append(XorStr(".afinity"));
		CoTaskMemFree(pszPathToAppData);
	}

	return fsWorkingPath;
}
