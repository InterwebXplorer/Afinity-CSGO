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
#include "../global.h"
#include "../options.h"
#include "esp.h"

void esp::getenemyplayerinfo(CBaseEntity* pEntity) {
    for (int i; i = I::ClientEntityList->GetMaxEntities(); i++) {
        pEntity = I::ClientEntityList->GetClientEntity(i); 

        if (!pEntity)
            return;

        if (!pEntity->IsPlayer())
            return;

        if (!pEntity->IsAlive())
            return;

        if (!pEntity->IsEnemy())
            return;        
    }

    PlayerInfo_t pEntityInfo = {};
    //get other info
    return pEntityInfo;
}

void esp::enemy(CBaseEntity* pEntity) {
    if (!Options.esp_enemy_enabled)
        return;
    
}

//team esp

void esp::local(CBaseEntity* pLocal) {
    if (!Options.esp_local_enabled)
        return;

    
}


/*
void enemyesp::boxesp(CBaseEntity* pEntity) {
    //Options.esp_enemy_boxcolor;


    
}

void enemyesp::boxesp() {
    ImVec4 BoxColor = Options.esp_enemy_boxcolor;

    CBaseEntity* pEntity = getplayerentity();

    if ()

    switch (Options.esp_enemy_box) {
        case 1: //off
            break;

        case 2: //normal
            break;

        case 3: //cornered
            break;

        case 4: ;//3d
            break;
    }
}

void enemyesp::() {
    
}

void esp::enemy() {
    for (int i; i < I::ClientEntityList->GetMaxEntities(); i++) {
        CBaseEntity* pEntity = I::ClientEntityList->Get<CBaseEntity>(i);

        if (!pEntity)
            return;

        if (!pEntity->IsPlayer())
            return;

        if (!pEntity->IsAlive())
            return;

        if (!pEntity->IsEnemy())
            return;

        PlayerInfo_t pEntityInfo = {};
        Vector pEntityPosition = pEntity->GetBonePosition(8);

        if (Options.esp_enemy_dormant) {
            pEntity->IsDormant();
            return;
        }

        if (Options.esp_enemy_shadeflat) {

        }


        ImColor BoxColor = ImColor(Options.esp_enemy_boxcolor);

        if (pEntity == Global::pTarget)
            BoxColor = ImColor(255, 0, 0, 255);
    
        switch (Options.esp_enemy_box) {
            case 1: //off
                break;

            case 2: //normal
                break;

            case 3: //cornered
                break;

            case 4: ;//3d
                break;
        }

        ImColor SnaplineColor = ImColor(Options.esp_enemy_snaplinecolor);

        if (pEntity == Global::pTarget)
            SnaplineColor = ImColor(255, 0, 0, 255);
        
        switch (Options.esp_enemy_snaplines) {
            case 1: //off
                break;

            case 2: ImDrawList::AddLine(, pEntityPosition, SnaplineColor); //top
                break;

            case 3: ImDrawList::AddLine(, pEntityPosition, SnaplineColor); //left
                break;

            case 4: ImDrawList::AddLine(, pEntityPosition, SnaplineColor); //right
                break;

            case 5: ImDrawList::AddLine(, pEntityPosition, SnaplineColor); //bottom
                break;

            case 6: ImDrawList::AddLine(, pEntityPosition, SnaplineColor); //center
                break;
        }

        if (Options.esp_enemy_name) {
            ImColor NameColor = ImColor(Options.esp_enemy_namecolor);

        }

        if (Options.esp_enemy_health) {
            ImColor HealthColor = ImColor(Options.esp_enemy_healthcolor);
        }

        if (Options.esp_enemy_ammo) {
            ImColor AmmoColor = ImColor(Options.esp_enemy_ammocolor);
        }

        if (Options.esp_enemy_weapon) {
            ImColor WeaponColor = ImColor(Options.esp_enemy_weaponcolor);
        }

        switch (Options.esp_enemy_flags) {
            case 1: //target
                break;

            case 2: //resolve status
                break;

            case 3: //money
                break;

            case 4: //armour
                break;
            
            case 5: //utility
                break;

            case 6: //scope
                break;

            case 7: //reload
                break;
            
            case 8: //exploits
                break;

            case 9: //ping
                break;

            case 10: //bomb?
                break;

            case 11: //priority?
                break;

            case 12: //location
                break;
        }

        if (Options.esp_enemy_sound) {
            ImColor SoundColor = ImColor(Options.esp_enemy_soundcolor);
        }

        if (Options.esp_enemy_lineofsight) {
            ImColor LOSColor = ImColor(Options.esp_enemy_lineofsightcolor);
        }

        if (Options.esp_enemy_skeleton) {
            ImColor SkeletonColor = ImColor(Options.esp_enemy_skeletoncolor);

            for (int i = 0; i < pStudioHdr->nBones; i++) {
                mstudiobone_t* pBone = pStudioHdr->GetBone(i);

                if (!pBone)
                    return;

                if (!pBone->iFlags & BONE_USED_BY_HITBOX)
                    return;

                pBoneChild = pBone->GetBonePosition(i);
                pBoneParent = pBone->GetBonePosition(pBone->iParent)
            
                int iChestBone = 6;
                Vector 
            }
        }

        if (Options.esp_enemy_outline) {
            ImColor OutlineColor = ImColor(Options.esp_enemy_outlinecolor);
        }

        if (Options.esp_enemy_chamsbacktrack) {
            ImColor BacktrackChamsColor = ImColor(Options.esp_enemy_chamsbacktrackcolor);
        }

        if (Options.esp_enemy_chamsoccluded) {
            ImColor OccludedChamsColor = ImColor(Options.esp_enemy_chamsoccludedcolor);
            int OccludedChamsGlow = Options.esp_enemy_chamsglow;

            switch (Options.esp_enemy_occludedchamsmaterial) {
                case 1:
                    break;

                case 2:
                    break;
            }
        }

        if (Options.esp_enemy_chamsvisible) {
            ImColor VisibleChamsColor = ImColor(Options.esp_enemy_chamsvisiblecolor);
            int VisibleChamsGlow = Options.esp_enemy_chamsglow;


            switch (Options.esp_enemy_chamsvisiblecolor) {
                case 1:
                    break;

                case 2:
                    break;
            }
        }

        if (Options.esp_enemy_bullettracers) {
            ImColor BulletTracerColor = ImColor(Options.esp_enemy_bullettracerscolor);
        }
    }
}

void esp::removals(CBaseEntity* pLocal) {
    constexpr std::array SmokeMaterials = { "particle/vistasmokev1/vistasmokev1_fire", "particle/vistasmokev1/vistasmokev1_smokegrenade", "particle/vistasmokev1/vistasmokev1_emods", "particle/vistasmokev1/vistasmokev1_emods_impactdust" };

    switch (Options.esp_other_removals) {
        case 1: //Scope overlay
            break;
        
        case 2: //Scope zoom
            break;

        case 3: //View punch
            break;
        
        case 4: //Aim punch
            break;
        
        case 5: for (const char* SmokeMaterial : SmokeMaterials) { //Smoke Effects
                    if (IMaterial* pMaterial = I::MaterialSystem->FindMaterial(SmokeMaterial, TEXTURE_GROUP_OTHER)) {
                        if (!pMaterial)
                            return;

                        if (pMaterial->IsErrorMaterial())
                            return;

                        pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
                    }     
                } //remove smoke overlay in hooks
            break;
        
        case 6: if (pLocal->GetFlashDuration() > 0.0f) //Flash Effects
                    pLocal->GetFlashDuration() = 0.0f;
            break;

        case 7: //Fog
            break;

        case 8: //Post Processing
            break;
        
        case 9: //Arms
            break;

        case 10: //Weapon
            break;
    }
}

void esp::team() {

}

void esp::local(CBaseEntity* pLocal) {

}

void esp::world() {

}

void esp::bomb() {
    if (Options.esp_other_bombtimer) { //attach to radar curve

    }

    if (Options.esp_other_bombchams) { //Options.esp_other_bombchamscolor, Options.esp_other_bombchamsmaterial

    }

    if (Options.esp_other_bombglow) {

    }

    switch (Options.esp_other_bombflags) {
        case 1: //State
            break;

        case 2: //Timer
            break;
    }
}

void esp::droppedweapons() {

}

void esp::grenades() {

}

void esp::sounds() {

    const char* hitsound = nullptr;

    switch (Options.esp_other_hitsound) {
        case 1: //off
            break;

        case 2: hitsound = "ahhh.wav"; //ahhh
            break;

        case 3: hitsound = "animemoan.wav"; //anime moan
            break;

        case 4: hitsound = "bell.wav"; //bell
            break;

        case 5: hitsound = "flick.wav"; //flick
            break;

        case 6: hitsound = "metallic.wav"; //metalic
            break;

        case 7: hitsound = "minecrafthurt.wav"; //Minecraft
            break;

        case 8: hitsound = "robloxoof.wav"; //Roblox
            break;
    }

    switch (Options.esp_other_hiteffect) {
        case 1: //off
            break;

        case 2: 
            break;
    }

    const char* killsound = nullptr;

    switch (Options.esp_other_killsound) {
        case 1: //off
            break;

        case 2: killsound = "overwatchkillsound(csgo).wav"; //overwatch(csgo)
            break;

        case 3: killsound = "overwatchkillsound(css).wav"; //overwatch(css)
            break;

        case 4: killsound = "technojingle.wav"; //techno
            break;
    }

    switch (Options.esp_other_killanouncer) {
        case 1: //off
            break;

        case 2: //quake (female)
            break;

        case 3: //quake (standard)
            break;

        case 4: //valorant
            break;

        case 5: //anime
            break;
    }

    const char* deathsound = nullptr;

    switch (Options.esp_other_deathsound) {
        case 1: //off
            break;

        case 2: deathsound = "ahhh.wav"; //ahhh
            break;

        case 3: deathsound = "error.wav"; //error
            break;
        
        case 4: deathsound = "fail.wav"; //fail
            break;

        case 5: deathsound = "wilhelmscream.wav"; //wilhelm
            break;
    }
}

void esp::misc() {

}
*/