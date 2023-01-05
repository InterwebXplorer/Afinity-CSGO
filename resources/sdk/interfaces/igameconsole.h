#pragma once

class IGameConsole {
public:
	virtual ~IGameConsole() {}
	virtual void Activate() = 0;
	virtual void Initialize() = 0;
	virtual void Hide() = 0;
	virtual void Clear() = 0;
	virtual bool IsConsoleVisible() = 0;
	virtual void SetParent(int parent) = 0;
};
