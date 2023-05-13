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
#include <vector>
#include "../global.h"
#include "../options.h"
#include "esp.h"

#pragma region EnemyESP
void ESP::Enemy() {
    if (!Options.esp_enemy_enabled)
        return;

    CBaseEntity* TargetEntity = nullptr;

    for (int i = 0; i < I::Engine->GetMaxClients(); i++) {
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
            BoundingBox(TargetEntity, Options.esp_enemy_boxcolor, 3, Left, Bottom, Right, Top);
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

    if (Options.esp_enemy_weapon)
        Weapon(TargetEntity, Left, Bottom);

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

    if (Options.esp_enemy_lineofsight)
        LineOfSight(TargetEntity, Options.esp_enemy_lineofsightcolor);

    if (Options.esp_enemy_skeleton)
        Skeleton(TargetEntity, Options.esp_enemy_skeletoncolor);

    if (Options.esp_enemy_bullettracers)
        BulletTracer(TargetEntity, Options.esp_enemy_bullettracerscolor);
}
#pragma endregion

//Team ESP

#pragma region LocalESP
void ESP::Local() {
    if (!Options.esp_local_enabled)
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (!LocalPlayer->IsAlive())
        return;

    PlayerInfo_t PlayerInfo;
    float Left, Bottom, Right, Top;

    I::Engine->GetPlayerInfo(LocalPlayer, PlayerInfo);

    if (I::Input->bCameraInThirdPerson) {
        switch (Options.esp_local_box) {
            case OFF:
                BoundingBox(LocalPlayer, nullptr, 0, Left, Bottom, Right, Top);
                break;

            case 2D:
                BoundingBox(LocalPlayer, Options.esp_local_boxcolor, 1, Left, Bottom, Right, Top);
                break;

            case CORNERED2D:
                BoundingBox(LocalPlayer, Options.esp_local_boxcolor, 2, Left, Bottom, Right, Top);
                break;

            case 3D:
                BoundingBox(LocalPlayer, Options.esp_local_boxcolor, 3, Left, Bottom, Right, Top);
                break;
        }

        if (Options.esp_local_name)
            ImDrawList::AddText(ImVec2(Left + Right / 2, Top), Options.esp_local_namecolor, PlayerInfo.szName);

        if (Options.esp_local_health)
            HealthBar(LocalPlayer, Options.esp_local_healthcolor, Left, Bottom, Right, Top);

        if (Options.esp_local_ammo)
            AmmoBar(LocalPlayer, Options.esp_local_ammocolor, Left, Bottom, Right, Top);

        if (Options.esp_local_weapon)
            Weapon(LocalPlayer, Left, Bottom);

        if (Options.esp_local_skeleton)
            Skeleton(LocalPlayer, Options.esp_local_skeletoncolor);
    }
    
    if (Options.esp_local_bullettracers)
        BulletTracer(LocalPlayer, Options.esp_local_bullettracerscolor);
}
#pragma endregion

#pragma region OtherESP
void ESP::Bomb() {
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();
    CPlantedC4* PlantedBombEntity = nullptr;
    CBaseEntity* DroppedBombEntity = nullptr;

    for (int i = 0; i < I::ClientEntityList->GetHighestEntityIndex(), i++) {
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

    float RemainingTime = PlantedBombEntity->GetBlowTime() - (LocalPlayer->GetTickBase() * I::Globals->flIntervalPerTick);
    CBaseEntity* Defuser = I::ClientEntityList->GetClientEntityFromHandle(PlantedBombEntity->GetDefuserHandle());
    float MinDefuseTime = 10.5f;

    if (Defuser->HasDefuser())
        MinDefuseTime = 5.5f;

    switch (Options.esp_other_bombtimer) {
        case RADARCURVE:
            //todo
            break;

        case BAR:
            //ImDrawList::AddRectFilled(ImVec2(0, 0), ImVec2(Global::WindowSize.x / RemainingTime, 5))
            break;
    }

    switch (Options.esp_other_bombflags) {
        case STATE:
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
            if (BombEntityIsDropped)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "0.0 SECONDS");
            else if (BombEntityIsPlanted && RemainingTime >= MinDefuseTime)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), (RemainingTime + "SECONDS").c_str());
            else if (BombEntityIsPlanted && RemainingTime < MinDefuseTime)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 0, 0, 255), (RemainingTime + "SECONDS").c_str());
            else if (BombEntityIsPlanted && PlantedBombEntity->IsDefused())
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(0, 0, 255, 255), (RemainingTime + "SECONDS").c_str());
            break;

        case LOCATION:
            if (BombEntityIsDropped)
                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), "UNKNOWN");
            else if (BombEntityIsPlanted) {
                int BombSite = PlantedBombEntity->GetBombSite();
                const char* BombSiteName = nullptr;

                if (BombSite == 0)
                    BombSiteName = "BOMBSITE A";
                else if (BombSite == 1)
                    BombSiteName = "BOMBSITE B";

                ImDrawList::AddText(ImVec2(Right, Top + Bottom / 2), ImColor(255, 255, 255, 255), BombSiteName);
            }
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

void ESP::OOFArrows() {
    if (!Options.esp_other_oofarrows)
        return;

    //OPTION(ImVec4, Options.esp_other_oofarrowscolor, ImVec4(0, 0, 0, 0));
}

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

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    CWeaponCSBase* DroppedWeaponEntity = nullptr;
    CBaseCSGrenade* DroppedGrenadeEntity = nullptr;

    for (int i = 0; i < I::ClientEntityList->GetHighestEntityIndex(), i++) {
        CBaseEntity* Entity = I::ClientEntityList->GetClientEntity(i);

        if (!Entity)
            continue;

        if (strcmp(Entity->GetClassname(), "CWeaponCSBase"))
            DroppedWeaponEntity = static_cast<CWeaponCSBase*>(Entity);
        else if (strcmp(Entity->GetClassname(), "CBaseCSGrenade"))
            DroppedGrenadeEntity = static_cast<CBaseCSGrenade*>(Entity);
    }

    float Left, Bottom, Right, Top;

    BoundingBox(DroppedWeaponEntity, nullptr, 0, Left, Bottom, Right, Top);

    switch (Options.esp_other_droppedweaponflags) {
        case ICON:
            const char* WeaponIcon = nullptr;

            if (!DroppedWeaponEntity && DroppedGrenadeEntity)
                WeaponIcon = reinterpret_cast<const char*>(GetWeaponIcon(DroppedWeaponEntity->GetItemDefinitionIndex()));
            else if (DroppedWeaponEntity && !DroppedGrenadeEntity)
                WeaponIcon = reinterpret_cast<const char*>(GetWeaponIcon(DroppedGrenadeEntity->GetItemDefinitionIndex()));

            ImDrawList::AddText(ImVec2(Left + Right / 2, Bottom), ImColor(255, 255, 255, 255), WeaponIcon);
            break;
    
        case TEXT:
           const char* WeaponName = nullptr;

            if (!DroppedWeaponEntity && DroppedGrenadeEntity)
                WeaponIcon = reinterpret_cast<const char*>(GetWeaponName(DroppedWeaponEntity->GetItemDefinitionIndex()));
            else if (DroppedWeaponEntity && !DroppedGrenadeEntity)
                WeaponIcon = reinterpret_cast<const char*>(GetWeaponName(DroppedGrenadeEntity->GetItemDefinitionIndex()));

            ImDrawList::AddText(ImVec2(Left + Right / 2, Bottom), ImColor(255, 255, 255, 255), WeaponName);
            break;

        case DISTANCE:
            Vector LocalPlayerPosition = LocalPlayer->GetAbsOrigin();
            Vector DroppedItemPosition = nullptr;

            if (!DroppedWeaponEntity && DroppedGrenadeEntity)
                DroppedItemPosition = DroppedWeaponEntity->GetAbsOrigin();
            else if (DroppedWeaponEntity && !DroppedGrenadeEntity)
                DroppedItemPosition = DroppedGrenadeEntity->GetAbsOrigin();

            float Distance = Math::Calculate3DDistance(LocalPlayerPosition, DroppedItemPosition);

            ImDrawList::AddText(ImVec2(Right, Top), ImColor(255, 255, 255, 255), Distance.c_str())
            break;

        case AMMO:
            if (!DroppedWeaponEntity && DroppedGrenadeEntity)
                return;

            const short WeaponDefinitionIndex = DroppedWeaponEntity->GetItemDefinitionIndex();
            CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

            if (!ActiveWeaponData)
		        return;

            float Ammo = static_cast<float>(DroppedWeaponEntity->GetAmmo());
            float MaxAmmo = static_cast<float>(ActiveWeaponData->iMaxClip1);
            float CalculatedAmmo = Left - Right * (MaxAmmo / Ammo);

            ImDrawList::AddRect(ImVec2(Left - 1, Bottom + 1), ImVec2(Right + 1, Top - 1), ImVec4(0, 0, 0, 255));
            ImDrawList::AddRectFilled(ImVec2(Left, Bottom), ImVec2(Left + CalculatedAmmo, Top));
            break;
    }
}

/* 
//TODO: add crates for dangerzone
void ESP::Dangerzone() {

}

//TODO: fov crap
void ESP::FOV() {

}
*/

void ESP::Sounds() {
    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    if (strstr(IGameEvent->GetName(), "player_hurt")) {
        int AttackerPlayerID = IGameEvent->GetInt("attacker");
        int AttackerPlayer = I::Engine->GetPlayerForUserID(AttackerPlayerID);

        if (AttackerPlayer == LocalPlayer) {
            switch (Options.esp_other_hitsound) {
                case OFF:
                    break;

                case AHH:

                    break;

                case ANIMEMOAN:

                    break;

                case BELL:

                    break;

                case FLICK:

                    break;

                case METALIC:

                    break;

                case MINECRAFT:

                    break;

                case ROBLOX:

                    break;
            }
        }
    }

    if (strstr(IGameEvent->GetName(), "player_death")) {
        int AttackerPlayerID = IGameEvent->GetInt("attacker");
        int AttackerPlayer = I::Engine->GetPlayerForUserID(AttackerPlayerID);

        if (AttackerPlayer == LocalPlayer) {
            switch (Options.esp_other_killsound) {
                case OFF:
                    break;

                case OVERWATCHCSGO:

                    break;

                case OVERWATCHCSS:

                    break;

                case TECHNO:

                    break;
            }
        }
    }

/* TODO
    switch (Options.esp_other_killanouncer) {
        case OFF:
            break;

        case QUAKEFEMALE:

            break;

        case QUAKESTANDARD:

            break;

        case ANIME:

            break;
    }
*/

    if (strstr(IGameEvent->GetName(), "player_death")) {
        int VictimPlayerID = IGameEvent->GetInt("userid");
        int VictimPlayer = I::Engine->GetPlayerForUserID(VictimPlayerID);

        if (VictimPlayer == LocalPlayer) {
            switch (Options.esp_other_deathsound) {
                case OFF:
                    break;

                case AHHH:

                    break;

                case MISTAKE:

                    break;

                case FAIL:

                    break;

                case WILHELM:

                    break;
            }
        }
    }
}

//MULTIOPTION(Options.esp_other_hiteffect, OFF = false, EFFECT1 = false, EFFECT2 = false); // TODO: add effects

void ESP::GrenadePrediction() {
    if (Options.esp_other_localgrenadeprediction) {
        /*
        OPTION(ImVec4, Options.esp_other_localgrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
        OPTION(ImVec4, Options.esp_other_localgrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
        */
    }

    if (Options.esp_other_enemygrenadeprediction) {
        /*
        OPTION(ImVec4, Options.esp_other_enemygrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
        OPTION(ImVec4, Options.esp_other_enemygrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
        */
    }
}

void ESP::Watermark() {
    if (!Options.esp_other_watermark)
        return;
}

void ESP::OnewayVisualization() {
    if (!Options.esp_other_visualizeoneway)
        return;
}

void ESP::Hitmarker() {
    if (!Options.esp_other_hitmarker)
        return;

    if (!I::Engine->IsInGame())
        return;

    CBaseEntity* LocalPlayer = I::Engine->GetLocalPlayer();

    if (!LocalPlayer)
        return;

    ImVec4 HitmarkerColor = ImVec4(255, 255, 255, 255);

    if (strstr(IGameEvent->GetName(), "player_hurt")) {
        int AttackerPlayerID = IGameEvent->GetInt("attacker");
        int AttackerPlayer = I::Engine->GetPlayerForUserID(AttackerPlayerID);

        if (AttackerPlayer == LocalPlayer) {
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 - 5, Global::WindowSize.y / 2 - 5), ImVec2(Global::WindowSize.x / 2 - 10, Global::WindowSize.y / 2 - 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 - 5, Global::WindowSize.y / 2 + 5), ImVec2(Global::WindowSize.x / 2 - 10, Global::WindowSize.y / 2 + 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 + 5, Global::WindowSize.y / 2 - 5), ImVec2(Global::WindowSize.x / 2 + 10, Global::WindowSize.y / 2 - 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 + 5, Global::WindowSize.y / 2 + 5), ImVec2(Global::WindowSize.x / 2 + 10, Global::WindowSize.y / 2 + 10), HitmarkerColor);
        }
    }
    else if (strstr(IGameEvent->GetName(), "player_death")) {
        int AttackerPlayerID = IGameEvent->GetInt("attacker");
        int AttackerPlayer = I::Engine->GetPlayerForUserID(AttackerPlayerID);

        if (AttackerPlayer == LocalPlayer) {
            HitmarkerColor = ImVec4(255, 0, 0, 255);

            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 - 5, Global::WindowSize.y / 2 - 5), ImVec2(Global::WindowSize.x / 2 - 10, Global::WindowSize.y / 2 - 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 - 5, Global::WindowSize.y / 2 + 5), ImVec2(Global::WindowSize.x / 2 - 10, Global::WindowSize.y / 2 + 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 + 5, Global::WindowSize.y / 2 - 5), ImVec2(Global::WindowSize.x / 2 + 10, Global::WindowSize.y / 2 - 10), HitmarkerColor);
            ImDrawList::AddLine(ImVec2(Global::WindowSize.x / 2 + 5, Global::WindowSize.y / 2 + 5), ImVec2(Global::WindowSize.x / 2 + 10, Global::WindowSize.y / 2 + 10), HitmarkerColor);
        }
    }
}
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

    float Health = static_cast<float>(TargetEntity->GetHealth());
    float MaxHealth = static_cast<float>(TargetEntity->GetMaxHealth());
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

    float Ammo = static_cast<float>(ActiveWeapon->GetAmmo());
    float MaxAmmo = static_cast<float>(ActiveWeaponData->iMaxClip1);
    float CalculatedAmmo = Left - Right * (MaxAmmo / Ammo);

    CAnimationLayer* AnimationLayer = TargetEntity->GetAnimationLayer(1);

    if (!AnimationLayer)
        return;
                
    if (TargetEntity->GetSequenceActivity(AnimationLayer->nSequence) == ACT_CSGO_RELOAD && AnimationLayer->flWeight != 0.0f)
        CalculatedAmmo = Left - Right * AnimationLayer->flCycle;

    ImDrawList::AddRect(ImVec2(Left - 1, Bottom + 2), ImVec2(Right + 1, Bottom + 6), ImVec4(0, 0, 0, 255));
    ImDrawList::AddRectFilled(ImVec2(Left, Bottom + 1), ImVec2(Left + CalculatedAmmo, Bottom + 5), Color);
}

const char8_t* ESP::GetWeaponIcon(short WeaponDefinitionIndex) {
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
}

void ESP::BulletTracer(CBaseEntity* TargetEntity, ImVec4 TracerColor) {
    if (!TargetEntity)
        return;

    if (strstr(IGameEvent->GetName(), "bullet_impact")) {
        int AttackerPlayerID = IGameEvent->GetInt("userid");
        int AttackerPlayer = I::Engine->GetPlayerForUserID(AttackerPlayerID);

        if (!AttackerPlayerID || !AttackerPlayer)
            return;

        if (!AttackerPlayer == TargetEntity)
            return;

        Vector ImpactPosition = Vector(IGameEvent->GetFloat("x"), IGameEvent->GetFloat("y"), IGameEvent->GetFloat("z"));
        Vector EyePosition = TargetEntity->GetEyePosition();

        ImVec2 ScreenStartPosition;
        ImVec2 ScreenEndPosition;

        if (!Draw::WorldToScreen(EyePosition, ScreenStartPosition) && Draw::WorldToScreen(ImpactPosition, ScreenEndPosition))
            return;

        std::vector<Vector> BulletImpacts;
        BulletImpacts.push_back(ScreenEndPosition);

        auto StartTime = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < BulletImpacts.size(); i++) {
            auto CurrentTime = std::chrono::high_resolution_clock::now();
            auto ElapsledTime = CurrentTime - StartTime;

            ImDrawList::AddLine(ScreenStartPosition, ScreenEndPosition, TracerColor);

            if (ElapsledTime.count() > 5.0)
                BulletImpacts.erase(BulletImpacts.begin() + i);
        }
    }
}

void ESP::Weapon(CBaseEntity* TargetEntity, float Left, float Bottom) { //todo import weapon icon font
    CBaseCombatWeapon* ActiveWeapon = TargetEntity->GetWeapon();

    if (!ActiveWeapon)
        return;

    const short WeaponDefinitionIndex = ActiveWeapon->GetItemDefinitionIndex();
    CCSWeaponData* ActiveWeaponData = I::WeaponSystem->GetWeaponData(WeaponDefinitionIndex);

    if (!ActiveWeaponData)
		return;

    const char* WeaponIcon = reinterpret_cast<const char*>(GetWeaponIcon(WeaponDefinitionIndex));
    ImDrawList::AddText(ImVec2(Left - 1, Bottom + 7), Options.esp_local_weaponcolor, WeaponIcon);
}

void ESP::LineOfSight(CBaseEntity* TargetEntity, ImVec4 LOSColor) {
    Vector StartPosition = TargetEntity->GetEyePosition();
    Vector EyeAngles = TargetEntity->GetEyeAngles();
    Vector Forward = Math::AngleVectors(EyeAngles);
    Vector EndPosition = StartPosition + (Forward * 3000.0f);
        
    Trace_t Trace;
    Ray_t Ray;
    CTraceFilter* Filter;

    I::EngineTrace->TraceRay(Ray, MASK_SOLID, &Filter, &Trace);

    ImVec2 ScreenStartPostion;
    ImVec2 ScreenEndPostion;

    if (!Draw::WorldToScreen(StartPosition, ScreenStartPostion) && Draw::WorldToScreen(Trace.vecEnd, ScreenEndPostion))
        return;

    ImDrawList::AddLine(ScreenStartPostion, ScreenEndPostion, LOSColor);
}

const char* ESP::GetWeaponName(short WeaponDefinitionIndex) {
    switch (WeaponDefinitionIndex) {
	    case WEAPON_DEAGLE:
		    return "DESERT EAGLE";
	    case WEAPON_ELITE:
		    return "DUEL BERETTAS";
        case WEAPON_FIVESEVEN:
		    return "FIVE SEVEN";
	    case WEAPON_GLOCK:
		    return "GLOCK";
	    case WEAPON_AK47:
		    return "AK47";
	    case WEAPON_AUG:
		    return "AUG";
	    case WEAPON_AWP:
		    return "AWP";
	    case WEAPON_FAMAS:
		    return "FAMAS";
	    case WEAPON_G3SG1:
		    return "G3SG1";
    	case WEAPON_GALILAR:
	    	return "GALIL AR";
    	case WEAPON_M249:
	    	return "M249";
	    case WEAPON_M4A1:
		    return "M4A1";
	    case WEAPON_MAC10:
		    return "MAC10";
	    case WEAPON_P90:
		    return "P90";
	    case WEAPON_MP5SD:
		    return "MP5SD";
	    case WEAPON_UMP45:
		    return "UMP45";
	    case WEAPON_XM1014:
		    return "XM1014";
	    case WEAPON_BIZON:
		    return "PP BIZON";
	    case WEAPON_MAG7:
	    	return "MAG7";
	    case WEAPON_NEGEV:
		    return "NEGEV";
	    case WEAPON_SAWEDOFF:
	    	return "SAWED OFF";
	    case WEAPON_TEC9:
	    	return "TEC9";
	    case WEAPON_TASER:
		    return "TASER";
	    case WEAPON_HKP2000:
		    return "P2000";
	    case WEAPON_MP7:
		    return "MP7";
	    case WEAPON_MP9:
		    return "MP9";
	    case WEAPON_NOVA:
		    return "NOVA";
	    case WEAPON_P250:
		    return "P250";
        case WEAPON_SHIELD:
            return "RIOT SHIELD";
	    case WEAPON_SCAR20:
		    return "SCAR20";
	    case WEAPON_SG556:
	    	return "SG556";
	    case WEAPON_SSG08:
	    	return "SSG08";
	    case WEAPON_KNIFE:
	    	return "KNIFE";
	    case WEAPON_FLASHBANG:
	    	return "FLASHBANG";
	    case WEAPON_HEGRENADE:
	    	return "HE GRENADE";
	    case WEAPON_SMOKEGRENADE:
	    	return "SMOKE";
	    case WEAPON_MOLOTOV:
	    	[[fallthrough]];
	    case WEAPON_FIREBOMB:
	    	return "MOLOTOV";
	    case WEAPON_DECOY:
	    	[[fallthrough]];
	    case WEAPON_DIVERSION:
	    	return "DECOY";
	    case WEAPON_INCGRENADE:
	    	return "INCENDIARY";
	    case WEAPON_C4:
	    	return "BOMB";
	    case WEAPON_HEALTHSHOT:
	    	return "HEALTHSHOT";
        case WEAPON_BUMPMINE:
            return "BUMP MINE";
	    case WEAPON_KNIFE_GG:
	    	[[fallthrough]];
	    case WEAPON_KNIFE_T:
	    	return "KNIFE";
	    case WEAPON_M4A1_SILENCER:
	    	return "M4A1-S";
	    case WEAPON_USP_SILENCER:
	    	return "USP-S";
	    case WEAPON_CZ75A:
	    	return "CZ75A";
	    case WEAPON_REVOLVER:
	    	return "REVOLVER";
	    case WEAPON_TAGRENADE:
	    	return "UNKNOWN";
	    case WEAPON_FISTS:
	    	return "FISTS";
        case WEAPON_BREACHCHARGE:
            return "BREACH CHARGE";
	    case WEAPON_TABLET:
	    	return "TABLET";
	    case WEAPON_MELEE:
	    	return "UNKNOWN"; 
	    case WEAPON_AXE:
	    	return "AXE";
	    case WEAPON_HAMMER:
	    	return "HAMMER";
	    case WEAPON_SPANNER:
	    	return "SPANNER";
	    case WEAPON_KNIFE_BAYONET:
	    	return "KNIFE";
	    case WEAPON_KNIFE_CSS:
	    	return "KNIFE";
	    case WEAPON_KNIFE_FLIP:
	    	return "KNIFE";
	    case WEAPON_KNIFE_GUT:
	    	return "KNIFE";
	    case WEAPON_KNIFE_KARAMBIT:
	    	return "KNIFE";
	    case WEAPON_KNIFE_M9_BAYONET:
	    	return "KNIFE";
	    case WEAPON_KNIFE_TACTICAL:
	    	return "KNIFE";
	    case WEAPON_KNIFE_FALCHION:
	    	return "KNIFE";
	    case WEAPON_KNIFE_SURVIVAL_BOWIE:
	    	return "KNIFE";
	    case WEAPON_KNIFE_BUTTERFLY:
	    	return "KNIFE";
	    case WEAPON_KNIFE_PUSH:
	    	return "KNIFE";
	    case WEAPON_KNIFE_CORD:
	    	return "KNIFE";
	    case WEAPON_KNIFE_CANIS:
	    	return "KNIFE";
	    case WEAPON_KNIFE_URSUS:
	    	return "KNIFE";
	    case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	    	return "KNIFE";
	    case WEAPON_KNIFE_OUTDOOR:
	    	return "KNIFE";
	    case WEAPON_KNIFE_STILETTO:
	    	return "KNIFE";
	    case WEAPON_KNIFE_WIDOWMAKER:
	    	return "KNIFE";
	    case WEAPON_KNIFE_SKELETON:
	    	return "KNIFE";
	    default:
		    return "DEFAULT";
	}
}
#pragma endregion