#include "../resources/imgui/imgui.h"
#include "../resources/imgui/imgui_freetype.h"
#include "../resources/imgui/imgui_internal.h"
#include "../resources/imgui/impl/imgui_impl_dx9.h"
#include "../resources/imgui/impl/imgui_impl_win32.h"
#include "../resources/sdk/datatypes/keyvalues.h"
#include "../resources/sdk/entity.h"
#include "../resources/sdk/interfaces.h"
#include "../resources/utils/filelogging.h"
#include "../resources/utils/consolelogging.h"
#include "../resources/utils/inputsystem.h"
#include "../resources/utils/math.h"
#include "../resources/utils/draw.h"
#include "../global.h"
#include "../options.h"
#include "esp.h"

#pragma region EnemyESP
void ESP::Enemy() {
    if (!Options.esp_enemy_enabled)
        return;

    CBaseEntity* TargetEntity = nullptr;

    for (int i = 0; i < I::ClientEntityList->nMaxClients(); i++) {
        CBaseEntity* Entity = I::ClientEntityList->Get<CBaseEntity>(i);

        if (!Entity->IsPlayer())
            continue;

        if (!Entity->IsEnemy())
            continue;

        if (!Entity->IsAlive())
            continue;

        if (Options.esp_enemy_dormant) {
            if (Entity->IsDormant())
                continue;
        }

        TargetEntity = Entity;
    }

    PlayerInfo_t PlayerInfo;
    float Left, Bottom, Right, Top;

    I::Engine->GetPlayerInfo(TargetEntity, PlayerInfo);

    switch (Options.esp_enemy_box) {
        case OFF:
            BoundingBox(TargetEntity, nullptr, 0, Left, Bottom, Right, Top);
            break;

        case 2D:
            BoundingBox(TargetEntity, Options.esp_enemy_boxcolor, 1, Left, Bottom, Right, Top);
            break;
        
        case CORNERED2D:
            BoundingBox(TargetEntity, Options.esp_enemy_boxcolor, 2, Left, Bottom, Right, Top);
            break;

        case 3D:
            BoundingBox(TargetEntity, Options.esp_enemy_boxcolor, 2, Left, Bottom, Right, Top);
            break;
    }

    switch (Options.esp_enemy_snaplines) {
        case OFF:
            break;

        case TOP:
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2, 0), ImVec2(Left + Right / 2, Top), Options.esp_enemy_snaplinecolor);
            break;

        case LEFT:
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x, Global::WindowSize.y / 2), ImVec2(Left, Top + Bottom / 2), Options.esp_enemy_snaplinecolor);
            break;

        case RIGHT:
            ImDrawList::AddLine(ImVec2(0, Global::WindowSize.y / 2), ImVec2(Right, Top + Bottom / 2), Options.esp_enemy_snaplinecolor);
            break;

        case BOTTOM:
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2, Global::WindowSize.y), ImVec2(Left + Right / 2, Bottom), Options.esp_enemy_snaplinecolor);
            break;

        case CENTER:
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2, Global::WindowSize.y / 2), ImVec2(Left + Right / 2, Bottom), Options.esp_enemy_snaplinecolor);
            break;
    }

    if (Options.esp_enemy_name)
        ImDrawList::AddText(ImVec2(Left + Right / 2, Top), Options.esp_enemy_namecolor, PlayerInfo.szName);

    if (Options.esp_enemy_health)
        HealthBar(TargetEntity, Options.esp_enemy_healthcolor, Left, Bottom, Right, Top);

    if (Options.esp_enemy_ammo)
        AmmoBar(TargetEntity, Options.esp_enemy_ammocolor, Left, Bottom, Right, Top);

    if (Options.esp_enemy_weapon) { //todo import font
        CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

        if (!ActiveWeapon)
            return;

        const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
        CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

        if (!ActiveWeaponData)
		    return;

        const char* WeaponIcon = reinterpret_cast<const char*>(GetWeaponIcon(WeaponDefinitionIndex));
        ImDrawList::AddText(ImVec2(Left - 1, Bottom + 7), Options.esp_enemy_weaponcolor, WeaponIcon);
    }

    switch (Options.esp_enemy_flags) {
        case TARGET:
            if (TargetEntity == Global::TargetPlayer)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 0, 0, 255), "TARGET");
            break;

        case RESOLVESTATUS:
        /*
            if (!PlayerOptions.isresolved)
                ImDrawList::AddText(ImVec2(Right, Top) ImVec4(255, 0, 0, 255), "RESOLVED");
            else
                ImDrawList::AddText(ImVec2(Right, Top) ImVec4(0, 255, 0, 255), "RESOLVED");
        */
            break;

        case MONEY:
            ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 0, 0, 255), "$" + TargetEntity->GetMoney());
            break;

        case ARMOUR:
            if (TargetEntity->HasHelmet() && TargetEntity->GetArmour() > 0)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "HK");
            else if (TargetEntity->GetArmour() > 0)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "K");
            break;

        case UTILITY:
            if (TargetEntity->HasDefuser())
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "DEFUSER");
            break;

        case SCOPE:
            if (TargetEntity->IsScoped())
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "SCOPE");
            break;

        case RELOAD:
            CAnimationLayer* AnimationLayer = TargetEntity->GetAnimationLayer(1);

            if (!AnimationLayer)
                return;
                
            if (TargetEntity->GetSequenceActivity(AnimationLayer->nSequence) == ACT_CSGO_RELOAD && AnimationLayer->flWeight != 0.0f)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 0, 0, 255), "RELOADING");
            break;

        case EXPLOITS: //todo
        /*
            bool FakeDucking = false;
            static int StoredTicks = 0;
            static int CrouchedTicks[65];
            auto DuckAmount = TargetEntity->GetAnimationState()->flDuckAmount;
            auto DuckSpeed = TargetEntity->GetAnimationState()->flDuckingSpeed;
            
            if (DuckAmount && DuckSpeed) {
                if (DuckSpeed == 8.0f && DuckAmount < 0.9f && DuckAmount > 0.5) {
                    if (StoredTicks != )
                }
            }

            if (FakeDucking)
                ImDrawList::AddText(ImVec2(Right, Top), ImColor(255, 255, 255, 255), "FAKEDUCK");
        */
            break;

        case PING:
            if (PlayerInfo.bFakePlayer)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "BOT");
            else
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), TargetEntity->GetPing() + "MS");
            break;

        case BOMB:
            if (TargetEntity->HasBomb())
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), "BOMB");
            break;

        case PRIORITY:
        /*
            if (!PlayerOptions.ispriorityplayer)
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 0, 0, 255), "PRIORITY");
            else
                ImDrawList::AddText(ImVec2(Right, Top), ImVec4(0, 255, 0, 255), "PRIORITY");
        */
            break;

        LOCATION:
            ImDrawList::AddText(ImVec2(Right, Top), ImVec4(255, 255, 255, 255), TargetEntity->GetLastPlace());
            break;
    }

    if (Options.esp_enemy_sound) {
        //Options.esp_enemy_soundcolor
    }

    if (Options.esp_enemy_lineofsight) {
        TargetEntity->GetEyeAngles();


        
        ImDrawList::AddLine(ImVec2(), ImVec2(), Options.esp_enemy_lineofsightcolor);
    }

    if (Options.esp_enemy_skeleton)
        Skeleton(TargetEntity, Options.esp_enemy_skeletoncolor);

    if (Options.esp_enemy_outline) {
        //Options.esp_enemy_outlinecolor
    }

    //Options.esp_enemy_shadeflat <- apply to all chams

    if (Options.esp_enemy_chamsbacktrack) {
        //Options.esp_enemy_chamsbacktrackcolor
    }

    if (Options.esp_enemy_chamsoccluded) {
        //Options.esp_enemy_chamsoccludedcolor
        //Options.esp_enemy_occludedchamsmaterial //MAT1 = true, MAT2 = false
    }

    if (Options.esp_enemy_chamsvisible) {
        //Options.esp_enemy_chamsvisiblecolor
        //Options.esp_enemy_visiblechamsmaterial //MAT1 = true, MAT2 = false
    }

    if (Options.esp_enemy_chamsglow) { //bloom
        //Options.esp_enemy_chamsglowcolor
    }

    if (Options.esp_enemy_bullettracers) {
        //Options.esp_enemy_bullettracerscolor
    }
}
#pragma endregion

#pragma region LocalESP
void ESP::Local() {

}
#pragma endregion

#pragma region OtherESP
void ESP::Bomb(CBaseEntity* LocalPlayer) {
    CPlantedC4* PlantedBombEntity = nullptr;
    CBaseEntity* DroppedBombEntity = nullptr;

    for (int i = 0; i < I::ClientEntityList->GetHighestEntityIndex()) {
        CBaseEntity* Entity = I::ClientEntityList->GetClientEntity(i);

        if (!Entity)
            continue;

        if (Entity->GetClientClass()->nClassID == EClassIndex::CC4)
            DroppedBombEntity = Entity;
        else if (Entity->GetClientClass()->nClassID == EClassIndex::CPlantedC4)
            PlantedBombEntity = static_cast<CPlantedC4*>(Entity);
    }

    bool BombEntityIsPlanted = false;
    bool BombEntityIsDropped = false;

    if (!PlantedBombEntity == nullptr)
        BombEntityIsPlanted = true;
    else if (!DroppedBombEntity == nullptr)
        BombEntityIsDropped = true;

    float Left, Bottom, Right, Top; 

    if (BombEntityIsPlanted)
        BoundingBox(PlantedBombEntity, nullptr, 0, Left, Bottom, Right, Top);
    else if (BombEntityIsDropped)
        BoundingBox(DroppedBombEntity, nullptr, 0, Left, Bottom, Right, Top);

    if (Options.esp_other_bombtimer) { //attach to radar curve

    }

    if (Options.esp_other_bombchams) {
        //Options.esp_other_bombchamscolor
        //Options.esp_other_bombchamsmaterial //MAT1 = true, MAT2 = false
    }

    if (Options.esp_other_bombglow) {
        //Options.esp_other_bombglowcolor
    }

    switch (Options.esp_other_bombflags) {
        case STATE:
            float RemainingTime = PlantedBombEntity->GetBlowTime() - (LocalPlayer->GetTickBase() * I::Globals->flIntervalPerTick);

            if (BombEntityIsDropped)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "DROPPED");
            else if (BombEntityIsPlanted && RemainingTime > 0.0f)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "PLANTED");
            else if (BombEntityIsPlanted && PlantedBombEntity->IsDefused())
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "DEFUSED");
            else if (BombEntityIsPlanted && RemainingTime < 0.0f)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "DETONATED");
            break;

        case TIMER:
            float RemainingTime = PlantedBombEntity->GetBlowTime() - (LocalPlayer->GetTickBase() * I::Globals->flIntervalPerTick);
            float MinDefuseTime = 10.5f;

            CBaseEntity* Defuser = I::ClientEntityList->GetClientEntityFromHandle(PlantedBombEntity->GetDefuserHandle());

            if (Defuser->HasDefuser())
                MinDefuseTime = 5.5f;

            if (BombEntityIsDropped)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "0.0 SECONDS");
            else if (BombEntityIsPlanted && RemainingTime >= MinDefuseTime)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), RemainingTime << "SECONDS");
            else if (BombEntityIsPlanted && RemainingTime < MinDefuseTime)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 0, 0, 255), RemainingTime << "SECONDS");
            else if (BombEntityIsPlanted && PlantedBombEntity->IsDefused())
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(0, 0, 255, 255), RemainingTime << "SECONDS");
            break;

        case LOCATION:
            if (BombEntityIsDropped)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "UNKNOWN");
            else if (BombEntityIsPlanted)
                int BombSite = PlantedBombEntity->GetBombSite();
                const char* BombSiteName = nullptr;

                if (BombSite == 0)
                    BombSiteName = "BOMBSITE A";
                else if (BombSite == 1)
                    BombSiteName = "BOMBSITE B";

                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), BombSiteName);
            break;
    }
}

void ESP::PenetrationCrosshair() {

    //LOGIC

    Switch (Options.esp_other_penetrationcrosshair) {
        case OFF:
            break;

        case DEFAULT:

            break;

        case CIRCLE:

            break;

        case SQUARE:

            break;
    }
}

void ESP::World() {
    /*
    OPTION(bool, Options.esp_other_fullbright, false);
    OPTION(bool, Options.esp_other_worldcolor, false);
    OPTION(ImVec4, Options.esp_other_worldcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_propcolor, false);
    OPTION(ImVec4, Options.esp_other_propcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_skycolor, false);
    OPTION(ImVec4, Options.esp_other_skycolorcolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_skybox, SKYBOX1 = false, SKYBOX2 = false);
    OPTION(std::string, Options.esp_other_customskybox, nullptr);
    */
}

void ESP::Removals(CBaseEntity* LocalPlayer) {
    switch(Options.esp_other_removals) {
        case SCOPEOVERLAY:
            CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon;

            if (!ActiveWeapon)
                return;
        
	        const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
	        const CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

            if (!ActiveWeaponData)
                return;

            if (!ActiveWeaponData->nWeaponType == WEAPONTYPE_SNIPER)
                return;

            if (LocalPlayer->IsScoped()) {
                I::ConVar->FindVar("cl_drawhud")->SetValue(0);
                ImDrawList::AddLine(ImVec2(0, Global::WindowSize.y / 2), ImVec2(Global::WindowSize.x, Global::WindowSize.y / 2), ImVec4(0, 0, 0, 255))
                ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2, 0), ImVec2(Global::WindowSize.x / 2, Global::WindowSize.y), ImVec4(0, 0, 0, 255))
            }
            else
                I::ConVar->FindVar("cl_drawhud")->SetValue(1);
            break;

        case SCOPEZOOM:

            break;

        case VIEWPUNCH:

            break;

        case AIMPUNCH:

            break;

        case SMOKEEFFECTS:

            break;

        case FLASHEFFECTS:
            LocalPlayer->GetFlashAlpha() = 0.0f;
            break;

        case FOG:

            break;

        case POSTPROCESSING:

            break;

        case ARMS:

            break;

        case WEAPON:

            break;
    }
}

void ESP::ThirdPerson(CBaseEntity* LocalPlayer) { //TODO
    if (Options.esp_other_thirdperson)
        return;

    bool ThirdPerson = true;

    if (Options.esp_other_thirdpersonondeath) {
        if (!LocalPlayer->IsAlive())
            return;
    }

    if (Options.esp_other_thirdpersondisablenade) {
        CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

        if (!ActiveWeapon)
            return;

        const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
        CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

        if (!ActiveWeaponData)
		    return;

        if (ActiveWeaponData->nWeaponType == WEAPONTYPE_GRENADE)
            ThirdPerson = false;
    }

//
    bool InTransition = false;
    float ModelOpacity = 1.0f - (/*current dist*/ / Options.esp_other_thirdpersondistance)


    I::RenderView->SetBlend() = ;
    I::RenderView->GetBlend();


    I::Input->bCameraInThirdPerson;

}

/*
OPTION(bool, Options.esp_other_radarhack, false);
OPTION(bool, Options.esp_other_streamproof, false);
OPTION(bool, Options.esp_other_oofarrows, false);
OPTION(ImVec4, Options.esp_other_oofarrowscolor, ImVec4(0, 0, 0, 0));
*/

void ESP::Grenades() {
    if (Options.esp_other_incendiarytracer) {
        //Options.esp_other_incendiarytracercolor
    }

    if (Options.esp_other_smoketracer) {
        //Options.esp_other_smoketracercolor
    }

    if (Options.esp_other_hetracer) {
        //Options.esp_other_hetracercolor
    }

    if (Options.esp_other_flashbangtracer) {
        //Options.esp_other_flashbangtracercolor
    }

    if (Options.esp_other_decoytracer) {
        //Options.esp_other_decoytracercolor
    }

    if (Options.esp_other_incendiaryspread) {
        //Options.esp_other_incendiaryspreadcolor
    }

    if (Options.esp_other_smokespread) {
        //Options.esp_other_smokespreadcolor
    }
}

void ESP::DroppedWeapons() {
    if (Options.esp_other_droppedweapons)
        return;

    switch (Options.esp_other_droppedweaponflags) {
    case ICON:

        break;
    
    case TEXT:

        break;

    case DISTANCE:

        break;

    case AMMO:

        break;
    }

    if (Options.esp_other_droppedweaponchams) {
        //Options.esp_other_droppedweaponchamscolor
    
        switch (Options.esp_other_droppedweaponchamsmateria) {
            case MAT1:

                break;

            case MAT2:

                break;
        }
    }

    if (Options.esp_other_droppedweaponglow) {
        //Options.esp_other_droppedweaponglowcolor
    }
}

/*

----------------/////------------------
// TODO: add crates for dangerzone
// TODO: fov crap
----------------/////------------------

MULTIOPTION(Options.esp_other_hitsound, OFF = false, AHHH = false, ANIMEMOAN = false, BELL = false, FLICK = false, METALIC = false, MINECRAFT = false, ROBLOX = false);
MULTIOPTION(Options.esp_other_hiteffect, OFF = false, EFFECT1 = false, EFFECT2 = false); // TODO: add effects
MULTIOPTION(Options.esp_other_killsound, OFF = false, OVERWATCHCSGO = false, OVERWATCHCSS = false, TECHNO = false);
MULTIOPTION(Options.esp_other_killanouncer, OFF = false, QUAKEFEMALE = false, QUAKESTANDARD = false, VALORANT = false, ANIME = false);
MULTIOPTION(Options.esp_other_deathsound, OFF = false, AHHH = false, ERROR = false, FAIL = false, WILHELM = false);

OPTION(bool, Options.esp_other_localgrenadeprediction, false);
OPTION(ImVec4, Options.esp_other_localgrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
OPTION(ImVec4, Options.esp_other_localgrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
OPTION(bool, Options.esp_other_enemygrenadeprediction, false);
OPTION(ImVec4, Options.esp_other_enemygrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
OPTION(ImVec4, Options.esp_other_enemygrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));

OPTION(bool, Options.esp_other_watermark, false);

OPTION(bool, Options.esp_other_visualiseoneway, false);
OPTION(char, Options.esp_other_visualiseonewaykey, NULL);
MULTIOPTION(Options.esp_other_visualiseonewaykeymode, ALWAYS = false, TOGGLE = false, ONHOLD = false, OFFHOLD = false);

OPTION(bool, Options.esp_other_hitmarker, false);
*/
#pragma endregion

#pragma region UtilityFunctions
void ESP::BoundingBox(CBaseEntity* TargetEntity, ImVec4 Color, int Mode = 0, float& LeftLeft, float& BottomBottom, float& RightRight, float& TopTop) {
    if (!TargetEntity)
        return;

    const matrix3x4_t& CoordinateFrameMatrix = TargetEntity->GetCoordinateFrame();
    ICollideable* Collision = (ICollideable*)TargetEntity->GetCollideable();

    if (!Collision)
        return;

    Vector CollisionMin = Collision->OBBMins();
    Vector CollisionMax = Collision->OBBMaxs();

    vec3_t Points[] = {
        {CollisionMin.x, CollisionMin.y, CollisionMin.z},
		{CollisionMin.x, CollisionMax.y, CollisionMin.z},
		{CollisionMax.x, CollisionMax.y, CollisionMin.z},
		{CollisionMax.x, CollisionMin.y, CollisionMin.z},
		{CollisionMax.x, CollisionMax.y, CollisionMax.z},
		{CollisionMin.x, CollisionMax.y, CollisionMax.z},
		{CollisionMin.x, CollisionMin.y, CollisionMax.z},
		{CollisionMax.x, CollisionMin.y, CollisionMax.z}
    };

    for (int i = 0; i < 8; i++) {
        vec3_t WorldCoordinates;
        vec3_t ScreenCoordinates;
        Math::VectorTransform(Points[i], CoordinateFrameMatrix, WorldCoordinates);

        if (!Draw::WorldToScreen(WorldCoordinates, ScreenCoordinates))
            return;
    
        Points[i] = ScreenCoordinates;
    } 

    if (Mode == 0) {
        float Left = Points[0].x;
        float Bottom = Points[0].y;
        float Right = Points[0].x;
        float Top = Points[0].y;

        for (int i = 0; i < 8; i++) {
            if (Left > Points[i].x) 
                Left = Points[i].x;

            if (Bottom < Points[i].y) 
                Bottom = Points[i].y;

            if (Right < Points[i].x) 
                Right = Points[i].x;
        
            if (Top > Points[i].y) 
                Top = Points[i].y;
        }

        LeftLeft = Left;
        BottomBottom = Bottom;
        RightRight = Right;
        TopTop = Top;
    }

    if (Mode == 1) {
        float Left = Points[0].x;
        float Bottom = Points[0].y;
        float Right = Points[0].x;
        float Top = Points[0].y;

        for (int i = 0; i < 8; i++) {
            if (Left > Points[i].x) 
                Left = Points[i].x;

            if (Bottom < Points[i].y) 
                Bottom = Points[i].y;

            if (Right < Points[i].x) 
                Right = Points[i].x;
        
            if (Top > Points[i].y) 
                Top = Points[i].y;
        }

        ImDrawList::AddLine(ImVec2(Left, Bottom), ImVec2(Left, Top), Color);
        ImDrawList::AddLine(ImVec2(Left, Top), ImVec2(Right, Top), Color);
        ImDrawList::AddLine(ImVec2(Right, Top), ImVec2(Right, Bottom), Color);
        ImDrawList::AddLine(ImVec2(Right, Bottom), ImVec2(Left, Bottom), Color);

        LeftLeft = Left;
        BottomBottom = Bottom;
        RightRight = Right;
        TopTop = Top;
    }
    
    if (Mode == 2) {
        float Left = Points[0].x;
        float Bottom = Points[0].y;
        float Right = Points[0].x;
        float Top = Points[0].y;

        for (int i = 0; i < 8; i++) {
            if (Left > Points[i].x) 
                Left = Points[i].x;

            if (Bottom < Points[i].y) 
                Bottom = Points[i].y;

            if (Right < Points[i].x) 
                Right = Points[i].x;
        
            if (Top > Points[i].y) 
                Top = Points[i].y;
        }

        ImDrawList::AddLine(ImVec2(Left, Bottom), ImVec2(Left, Bottom - 15), Color);
        ImDrawList::AddLine(ImVec2(Left, Bottom), ImVec2(Left + 15, Bottom), Color);
        ImDrawList::AddLine(ImVec2(Left, Top), ImVec2(Left, Top + 15), Color);
        ImDrawList::AddLine(ImVec2(Left, Top), ImVec2(Left + 15, Top), Color);
        ImDrawList::AddLine(ImVec2(Right, Top), ImVec2(Right, Top + 15), Color);
        ImDrawList::AddLine(ImVec2(Right, Top), ImVec2(Right - 15, Top), Color);
        ImDrawList::AddLine(ImVec2(Right, Bottom), ImVec2(Right, Bottom - 15), Color);
        ImDrawList::AddLine(ImVec2(Right, Bottom), ImVec2(Right - 15, Bottom), Color);

        LeftLeft = Left;
        BottomBottom = Bottom;
        RightRight = Right;
        TopTop = Top;
    }
    
    if (Mode == 3) {
        float FrontLeft = Points[0].x;
        float FrontBottom = Points[0].y;
        float FrontRight = Points[0].x;
        float FrontTop = Points[0].y;
        float BackLeft = Points[0].x;
        float BackBottom = Points[0].y;
        float BackRight = Points[0].x;
        float BackTop = Points[0].y;

        for (int i = 0; i < 8; i++) {
            if (FrontLeft > Points[i].x) 
                FrontLeft = Points[i].x;

            if (FrontBottom < Points[i].y) 
                FrontBottom = Points[i].y;

            if (FrontRight < Points[i].x) 
                FrontRight = Points[i].x;
        
            if (FrontTop > Points[i].y) 
                FrontTop = Points[i].y;

            if (BackLeft > Points[i].x) 
                BackLeft = Points[i].x;

            if (BackBottom < Points[i].y) 
                BackBottom = Points[i].y;

            if (BackRight < Points[i].x) 
                BackRight = Points[i].x;
        
            if (BackTop > Points[i].y) 
                BackTop = Points[i].y;
        }

        ImDrawList::AddLine(ImVec2(FrontLeft, FrontBottom), ImVec2(FrontLeft, FrontTop), Color);
        ImDrawList::AddLine(ImVec2(FrontLeft, FrontTop), ImVec2(FrontRight, FrontTop), Color);
        ImDrawList::AddLine(ImVec2(FrontRight, FrontTop), ImVec2(FrontRight, FrontBottom), Color);
        ImDrawList::AddLine(ImVec2(FrontRight, FrontBottom), ImVec2(FrontLeft, FrontBottom), Color);
        ImDrawList::AddLine(ImVec2(BackLeft, BackBottom), ImVec2(BackLeft, BackTop), Color);
        ImDrawList::AddLine(ImVec2(BackLeft, BackTop), ImVec2(BackRight, BackTop), Color);
        ImDrawList::AddLine(ImVec2(BackRight, BackTop), ImVec2(BackRight, BackBottom), Color);
        ImDrawList::AddLine(ImVec2(BackRight, BackBottom), ImVec2(BackLeft, BackBottom), Color);
        ImDrawList::AddLine(ImVec2(FrontLeft, FrontBottom), ImVec2(BackLeft, BackBottom), Color);
        ImDrawList::AddLine(ImVec2(FrontLeft, FrontTop), ImVec2(BackLeft, BackTop), Color);
        ImDrawList::AddLine(ImVec2(FrontRight, FrontTop), ImVec2(BackRight, BackTop), Color);
        ImDrawList::AddLine(ImVec2(FrontRight, FrontBottom), ImVec2(BackRight, BackBottom), Color);

        LeftLeft = FrontLeft;
        BottomBottom = FrontBottom;
        RightRight = FrontRight;
        TopTop = FrontTop;
    }
}

void ESP::Skeleton(CBaseEntity* TargetEntity, ImVec4 Color) {
    if (!TargetEntity)
        return;

    studiohdr_t* StudioHDR = I::ModelInfo->GetStudioModel(TargetEntity->GetModel());

    if (!StudioHDR)
        return;

    Vector BreastBone = TargetEntity->GetBonePosition(BONE_SPINE_3) + TargetEntity->GetBonePosition(BONE_SPINE_3 + 1) - TargetEntity->GetBonePosition(BONE_SPINE_3) / 2;

    for (int i = 0; i < StudioHDR->nBones; i++) {
        mstudiobone_t* Bone = StudioHDR->GetBone(i);

        if (!Bone)
            continue;

        if (Bone->iParent == BONE_INVALID)
            continue;

        if (!Bone->iFlags & BONE_USED_BY_HITBOX)
            continue;

        std::optional<Vector> Child = TargetEntity->GetBonePosition(i);
        std::optional<Vector> Parent = TargetEntity->GetBonePosition(Bone->iParent);
        Vector DeltaChild = Child - BreastBone;
        Vector DeltaParent = Parent - BreastBone;

        if (DeltaParent.size() < 9 && DeltaChild.size() < 9)
            Parent = BreastBone;

        if (i == BONE_SPINE_2)
            Child = BreastBone;

        if (abs(DeltaChild.z) < 5 && (DeltaParent.size() < 5 && DeltaChild.size() < 5) || i == BONE_SPINE_3)
            continue;

        ImVec2 ScreenChild;
        ImVec2 ScreenParent;

        Draw::WorldToScreen(Child, ScreenChild);
        Draw::WorldToScreen(Parent, ScreenParent);

        ImDrawList::AddLine(ImVec2(ScreenParent.x, ScreenParent.y), ImVec2(ScreenChild.x, ScreenChild.y), Color);
    }
}

void ESP::HealthBar(CBaseEntity* TargetEntity, ImVec4 Color, float& Left, float& Bottom, float& Right, float& Top) {
    if (!TargetEntity)
        return;

    float Health = static_cast<float>TargetEntity->GetHealth();
    float MaxHealth = static_cast<float>TargetEntity->GetMaxHealth();
    float CalculatedHealth = Bottom - Top * (MaxHealth / Health);

    ImDrawList::AddRect(ImVec2(Left - 6, Top - 1), ImVec2(Left - 2, Bottom + 1), ImVec4(0, 0, 0, 255));
    ImDrawList::AddRectFilled(ImVec2(Left - 5, Top + CalculatedHealth), ImVec2(Left - 1, Bottom), Color);
}

void ESP::AmmoBar(CBaseEntity* TargetEntity, ImVec4 Color, float& Left, float& Bottom, float& Right, float& Top) {
    if (!TargetEntity)
        return;

    CBaseCombatWeapon* ActiveWeapon = LocalPlayer->GetWeapon();

    if (!ActiveWeapon)
        return;

    const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return;

    if (!ActiveWeaponData->IsGun())
        return;

    float Ammo = static_cast<float>ActiveWeapon->GetAmmo();
    float MaxAmmo = static_cast<float>ActiveWeaponData->iMaxClip1;
    float CalculatedAmmo = Left - Right * (MaxAmmo / Ammo);

    CAnimationLayer* AnimationLayer = TargetEntity->GetAnimationLayer(1);

    if (!AnimationLayer)
        return;
                
    if (TargetEntity->GetSequenceActivity(AnimationLayer->nSequence) == ACT_CSGO_RELOAD && AnimationLayer->flWeight != 0.0f)
        CalculatedAmmo = Left - Right * AnimationLayer->flCycle;

    ImDrawList::AddRect(ImVec2(Left - 1, Bottom + 2), ImVec2(Right + 1, Bottom + 6), ImVec4(0, 0, 0, 255));
    ImDrawList::AddRectFilled(ImVec2(Left, Bottom + 1), ImVec2(Left + CalculatedAmmo, Bottom + 5), Color);
};

std::string ESP::GetWeaponIcon(short WeaponDefinitionIndex) {
    switch (WeaponDefinitionIndex) {
	    case WEAPON_DEAGLE:
		    return u8"\uE001";
	    case WEAPON_ELITE:
		    return u8"\uE002";
        case WEAPON_FIVESEVEN:
		    return u8"\uE003";
	    case WEAPON_GLOCK:
		    return u8"\uE004";
	    case WEAPON_AK47:
		    return u8"\uE007";
	    case WEAPON_AUG:
		    return u8"\uE008";
	    case WEAPON_AWP:
		    return u8"\uE009";
	    case WEAPON_FAMAS:
		    return u8"\uE00A";
	    case WEAPON_G3SG1:
		    return u8"\uE00B";
    	case WEAPON_GALILAR:
	    	return u8"\uE00D";
    	case WEAPON_M249:
	    	return u8"\uE00E";
	    case WEAPON_M4A1:
		    return u8"\uE010";
	    case WEAPON_MAC10:
		    return u8"\uE011";
	    case WEAPON_P90:
		    return u8"\uE013";
	    case WEAPON_MP5SD:
		    return u8"\uE017";
	    case WEAPON_UMP45:
		    return u8"\uE018";
	    case WEAPON_XM1014:
		    return u8"\uE019";
	    case WEAPON_BIZON:
		    return u8"\uE01A";
	    case WEAPON_MAG7:
	    	return u8"\uE01B";
	    case WEAPON_NEGEV:
		    return u8"\uE01C";
	    case WEAPON_SAWEDOFF:
	    	return u8"\uE01D";
	    case WEAPON_TEC9:
	    	return u8"\uE01E";
	    case WEAPON_TASER:
		    return u8"\uE01F";
	    case WEAPON_HKP2000:
		    return u8"\uE020";
	    case WEAPON_MP7:
		    return u8"\uE021";
	    case WEAPON_MP9:
		    return u8"\uE022";
	    case WEAPON_NOVA:
		    return u8"\uE023";
	    case WEAPON_P250:
		    return u8"\uE024";
        case WEAPON_SHIELD:
            return "RIOT SHIELD";
	    case WEAPON_SCAR20:
		    return u8"\uE026";
	    case WEAPON_SG556:
	    	return u8"\uE027";
	    case WEAPON_SSG08:
	    	return u8"\uE028";
	    case WEAPON_KNIFE:
	    	return u8"\uE02A";
	    case WEAPON_FLASHBANG:
	    	return u8"\uE02B";
	    case WEAPON_HEGRENADE:
	    	return u8"\uE02C";
	    case WEAPON_SMOKEGRENADE:
	    	return u8"\uE02D";
	    case WEAPON_MOLOTOV:
	    	[[fallthrough]];
	    case WEAPON_FIREBOMB:
	    	return u8"\uE02E";
	    case WEAPON_DECOY:
	    	[[fallthrough]];
	    case WEAPON_DIVERSION:
	    	return u8"\uE02F";
	    case WEAPON_INCGRENADE:
	    	return u8"\uE030";
	    case WEAPON_C4:
	    	return u8"\uE031";
	    case WEAPON_HEALTHSHOT:
	    	return u8"\uE039";
        case WEAPON_BUMPMINE:
            return "BUMP MINE";
	    case WEAPON_KNIFE_GG:
	    	[[fallthrough]];
	    case WEAPON_KNIFE_T:
	    	return u8"\uE03B";
	    case WEAPON_M4A1_SILENCER:
	    	return u8"\uE03C";
	    case WEAPON_USP_SILENCER:
	    	return u8"\uE03D";
	    case WEAPON_CZ75A:
	    	return u8"\uE03F";
	    case WEAPON_REVOLVER:
	    	return u8"\uE040";
	    case WEAPON_TAGRENADE:
	    	return u8"\uE044";
	    case WEAPON_FISTS:
	    	return u8"\uE045";
        case WEAPON_BREACHCHARGE:
            return "BREACH CHARGE";
	    case WEAPON_TABLET:
	    	return u8"\uE048";
	    case WEAPON_MELEE:
	    	return u8"\uE04A"; 
	    case WEAPON_AXE:
	    	return u8"\uE04B";
	    case WEAPON_HAMMER:
	    	return u8"\uE04C";
	    case WEAPON_SPANNER:
	    	return u8"\uE04E";
	    case WEAPON_KNIFE_BAYONET:
	    	return u8"\uE1F4";
	    case WEAPON_KNIFE_CSS:
	    	return u8"\uE1F7";
	    case WEAPON_KNIFE_FLIP:
	    	return u8"\uE1F9";
	    case WEAPON_KNIFE_GUT:
	    	return u8"\uE1FA";
	    case WEAPON_KNIFE_KARAMBIT:
	    	return u8"\uE1FB";
	    case WEAPON_KNIFE_M9_BAYONET:
	    	return u8"\uE1FC";
	    case WEAPON_KNIFE_TACTICAL:
	    	return u8"\uE1FD";
	    case WEAPON_KNIFE_FALCHION:
	    	return u8"\uE200";
	    case WEAPON_KNIFE_SURVIVAL_BOWIE:
	    	return u8"\uE202";
	    case WEAPON_KNIFE_BUTTERFLY:
	    	return u8"\uE203";
	    case WEAPON_KNIFE_PUSH:
	    	return u8"\uE204";
	    case WEAPON_KNIFE_CORD:
	    	return u8"\uE205";
	    case WEAPON_KNIFE_CANIS:
	    	return u8"\uE206";
	    case WEAPON_KNIFE_URSUS:
	    	return u8"\uE207";
	    case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	    	return u8"\uE208";
	    case WEAPON_KNIFE_OUTDOOR:
	    	return u8"\uE209";
	    case WEAPON_KNIFE_STILETTO:
	    	return u8"\uE20A";
	    case WEAPON_KNIFE_WIDOWMAKER:
	    	return u8"\uE20B";
	    case WEAPON_KNIFE_SKELETON:
	    	return u8"\uE20D";
	    default:
		    return u8"\u003F";
	}

void ESP::Chams(CBaseEntity* TargetEntity, ImVec4 Color) {
    if (!TargetEntity)
        return;

    
}
}
#pragma endregion