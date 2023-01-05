#pragma once
#include "../../utils/memory.h"

struct Texture_t {
	std::byte pad0[0xC];
	IDirect3DTexture9 *lpRawTexture;
};

class ITexture {
private:
	std::byte pad0[0x50];

public:
	Texture_t **pTextureHandles;

	int GetActualWidth() {
		return MEM::CallVFunc<int>(this, 3);
	}

	int GetActualHeight() {
		return MEM::CallVFunc<int>(this, 4);
	}

	void IncrementReferenceCount() {
		MEM::CallVFunc<void>(this, 10);
	}

	void DecrementReferenceCount() {
		MEM::CallVFunc<void>(this, 11);
	}
};
