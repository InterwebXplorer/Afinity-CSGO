#pragma once

namespace ESP {
    void Enemy();
    void Local();
    void Bomb();
    void PenetrationCrosshair();
    void World();
    void OOFArrows();
    void Grenades();
    void DroppedWeapons();
    void Sounds();
    void GrenadePrediction();
    void Watermark();
    void OnewayVisualization();
    void Hitmarker();
	/*--------------------Utility Functions--------------------*/
    void BoundingBox(CBaseEntity* TargetEntity, ImVec4 Color, int Mode = 0, float& LeftLeft, float& BottomBottom, float& RightRight, float& TopTop);
    void Skeleton(CBaseEntity* TargetEntity, ImVec4 Color);
    void HealthBar(CBaseEntity* TargetEntity, ImVec4 Color, float& Left, float& Bottom, float& Right, float& Top);
    void AmmoBar(CBaseEntity* TargetEntity, ImVec4 Color, float& Left, float& Bottom, float& Right, float& Top);
    const char8_t* GetWeaponIcon(short WeaponDefinitionIndex);
    void BulletTracer(CBaseEntity* TargetEntity, ImVec4 TracerColor);
    void Weapon(CBaseEntity* TargetEntity, float Left, float Bottom);
    void LineOfSight(CBaseEntity* TargetEntity, ImVec4 LOSColor);
    const char* GetWeaponName(short WeaponDefinitionIndex);
}