#pragma once
#include <directxmath.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../sdk/datatypes/vector.h"
#include "../sdk/datatypes/qangle.h"
#include "../sdk/datatypes/matrix.h"

#pragma region math_definitions
#define M_HPI			DirectX::XM_PIDIV2	
#define M_QPI			DirectX::XM_PIDIV4	
#define M_PI			DirectX::XM_PI		
#define M_2PI			DirectX::XM_2PI		
#define M_GPI			1.6180339887498f	
#define M_RADPI			57.295779513082f	

#define M_METRE2INCH( x )	( ( x ) / 0.0254f )
#define M_INCH2METRE( x )	( ( x ) * 0.0254f )
#define M_METRE2FOOT( x )	( ( x ) * 3.28f )
#define M_FOOT2METRE( x )	( ( x ) / 3.28f )
#define M_RAD2DEG( x )		DirectX::XMConvertToDegrees( x )
#define M_DEG2RAD( x )		DirectX::XMConvertToRadians( x )
#pragma endregion

extern "C" using RandomSeedFn = int(__cdecl*)(int iSeed);
extern "C" using RandomFloatFn = float(__cdecl*)(float flMinVal, float flMaxVal);
extern "C" using RandomFloatExpFn = float(__cdecl*)(float flMinVal, float flMaxVal, float flExponent);
extern "C" using RandomIntFn = int(__cdecl*)(int iMinVal, int iMaxVal);
extern "C" using RandomGaussianFloatFn = float(__cdecl*)(float flMean, float flStdDev);


namespace M
{
	bool	Setup();

	void	VectorAngles(const Vector& vecForward, QAngle& angView);

	void	AngleVectors(const QAngle& angView, Vector* pForward, Vector* pRight = nullptr, Vector* pUp = nullptr);

	void	AngleMatrix(const QAngle& angView, matrix3x4_t& matOutput, const Vector& vecOrigin = Vector(0.0f, 0.0f, 0.0f));

	
	Vector2D AnglePixels(const float flSensitivity, const float flPitch, const float flYaw, const QAngle& angBegin, const QAngle& angEnd);

	QAngle	PixelsAngle(const float flSensitivity, const float flPitch, const float flYaw, const Vector2D& vecPixels);

	QAngle	CalcAngle(const Vector& vecStart, const Vector& vecEnd);

	Vector	VectorTransform(const Vector& vecTransform, const matrix3x4_t& matrix);

	Vector	ExtrapolateTick(const Vector& p0, const Vector& v0);

	void	RotatePoint(const ImVec2& vecIn, const float flAngle, ImVec2* pOutPoint);

	void	RotateCenter(const ImVec2& vecCenter, const float flAngle, ImVec2* pOutPoint);

	
	inline RandomSeedFn				RandomSeed;
	inline RandomFloatFn			RandomFloat;
	inline RandomFloatExpFn			RandomFloatExp;
	inline RandomIntFn				RandomInt;
	inline RandomGaussianFloatFn	RandomGaussianFloat;

	/*--------------------Extra Math Shit--------------------*/
	
	void RandomIntSet(int number, ...);
	void RandomIntRange(int min, int max);
	void IntAddSubtractRange(int addstart, int addend, int subtractstart, int subtractend, int amount);
	void IntAddRange(int addstart, int addend, int amount);
	void IntSubtractRange(int subtractstart, int subtractend, int amount);
}
