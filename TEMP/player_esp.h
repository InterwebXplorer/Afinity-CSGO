#pragma once

#include <vector>
#include "..\..\includes.hpp"
#include "..\..\sdk\structs.hpp"

struct Box;

class playeresp : public singleton <playeresp>
{
public:
	int type = ENEMY;
	float esp_alpha_fade[65];
	int health[65];
	HPInfo hp_info[65];

	void paint_traverse();
	void draw_box(player_t* m_entity, const Box& box);
	void draw_skeleton(player_t* e, Color color, matrix3x4_t matrix[MAXSTUDIOBONES]);
	bool draw_ammobar(player_t* m_entity, const Box& box);
	void draw_name(player_t* m_entity, const Box& box);
	void draw_flags(player_t* e, const Box& box);
	void draw_lines(player_t* e);
	void draw_multi_points(player_t* e);

	void dlight();


};

class CEsp : public playeresp
{
public:

	void CustomVisuals(ImVec2 Start, int player);
	void VisualPreview();
	void InitVisuals();

	enum Sides
	{
		LEFT_S,
		RIGHT_S,
		TOP_S,
		DOWN_S,
		LEFT_TOP_S,
		RIGHT_TOP_S,
		LEFT_DOWN_S,
		RIGHT_DOWN_S,
		DOWN_LEFT_DOWN_S,
		DOWN_RIGHT_DOWN_S,
		CENTER_LEFT_S,
		CENTER_RIGHT_S,
	};

	struct MoveStruct
	{
		ImVec2 ZonePos;

		ImVec2 StartPos;
		ImVec2 Position;
		ImVec2 Offset;
		ImVec2 Correct;
		ImVec2 Size;
		ImVec2 SizeV;
		ImVec2 SizeH;
		ImVec2 Center;
		ImVec2 CorrectPadding;

		std::string Name;

		Color Color1;
		Color Color2;
		Color Color3;


		int NumParam1 = 4;
		int NumParam2 = 5;

		int TextSize = 17;

		bool boolParam1 = true;
		bool boolParam2 = true;
		bool boolParam3 = false;

		bool IsHover = false;
		bool Set = false;
		bool IsText = false;
		bool IsEnabled = false;

		int Id = -2;

		Vector CorrectOfst;

		Sides Side = LEFT_S;

		static int ActiveIdx;
		static int LastActive;
		static bool InitMItems;
	};

	enum MITypes : int
	{
		MI_HEALTH_BAR = 0,
		MI_ARMOR_BAR = 1,
		MI_NAME_TEXT = 2,
		MI_WEAPON_TEXT = 3,
		MI_AMMO_TEXT = 4,
		MI_DISTANCE_TEXT = 5,
		MI_MONEY_TEXT = 6,
		MI_SCOPE_TEXT = 7,
		MI_FLASHED_TEXT = 8,
		MI_DEFUSING_TEXT = 9,
		MI_HEALTH_TEXT = 10,
		MI_ARMOR_TEXT = 11,
		MI_MAX
	};

	std::vector<MoveStruct> MVItemList;
	void Move(MoveStruct& Cont, bool IsPressed, ImVec2 MouseP, ImVec2 StartP, ImVec2 CLines, bool IsText = false);
	enum Orent
	{
		HORIZONTAL,
		VERTICAL
	};
};


