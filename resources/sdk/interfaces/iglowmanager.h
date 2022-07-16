#pragma once
#include "../datatypes/color.h"

#define END_OF_FREE_LIST -1
#define ENTRY_IN_USE -2

enum EGlowRenderStyle : int
{
	GLOWRENDERSTYLE_DEFAULT = 0,
	GLOWRENDERSTYLE_RIMGLOW3D,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
	GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
	GLOWRENDERSTYLE_COUNT
};

class IGlowObjectManager
{
public:
	struct GlowObject_t
	{
		void Set(const Color &colGlow, const int nRenderStyle = GLOWRENDERSTYLE_DEFAULT)
		{
			this->arrColor = colGlow.BaseAlpha();
			this->flBloomAmount = 1.0f;
			this->bRenderWhenOccluded = true;
			this->bRenderWhenUnoccluded = false;
			this->nRenderStyle = nRenderStyle;
		}

		inline bool IsEmpty() const
		{
			return nNextFreeSlot != ENTRY_IN_USE;
		}

		int nNextFreeSlot;
		CBaseEntity *pEntity;
		std::array<float, 4U> arrColor;
		bool bAlphaCappedByRenderAlpha;
		std::byte pad0[0x3];
		float flAlphaFunctionOfMaxVelocity;
		float flBloomAmount;
		float flPulseOverdrive;
		bool bRenderWhenOccluded;
		bool bRenderWhenUnoccluded;
		bool bFullBloomRender;
		std::byte pad1[0x1];
		int iFullBloomStencilTestValue;
		int nRenderStyle;
		int nSplitScreenSlot;
	};

	struct GlowBoxObject_t
	{
		Vector vecPosition;
		QAngle angOrientation;
		Vector vecMins;
		Vector vecMaxs;
		float flBirthTimeIndex;
		float flTerminationTimeIndex;
		Color colColor;
	};

	CUtlVector<GlowObject_t> vecGlowObjectDefinitions;
	int nFirstFreeSlot;
	CUtlVector<GlowBoxObject_t> vecGlowBoxDefinitions;
};
