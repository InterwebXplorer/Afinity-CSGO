#pragma once

#include <string>

#define OPTION(type, name, value) type name = value
#define MULTIOPTION(name, ...) enum name { __VA_ARGS__ }

struct Options {
    /*---------------RAGEAIM-----------------*/
    /*---------------general-----------------*/
    OPTION(bool, Options.rage_enable, false);
    OPTION(bool, Options.rage_safepoint_enable, false);
    OPTION(bool, Options.rage_forcesafepoint, false);
    OPTION(char, Options.rage_forcesafepointkey, NULL);
    MULTIOPTION(Options.rage_safepointhitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_safepointdelay, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_safepointmaxdelay, 0);
    OPTION(bool, Options.rage_silentaim, false);
    OPTION(bool, Options.rage_autofire, false);
    OPTION(bool, Options.rage_autoscope, false);
    OPTION(bool, Options.rage_autostop, false);
    OPTION(bool, Options.rage_penetration, false);
    OPTION(bool, Options.rage_knifebot, false);
    OPTION(bool, Options.rage_zeusbot, false);
    OPTION(bool, Options.rage_resolver, false);
    OPTION(bool, Options.rage_resolverx, false);
    OPTION(bool, Options.rage_resolvery, false);
    OPTION(bool, Options.rage_bruteforce, false);
    OPTION(char, Options.rage_bruteforcekey, NULL);
    OPTION(bool, Options.rage_hideshots, false);
    OPTION(char, Options.rage_hideshotskey, NULL);
    OPTION(bool, Options.rage_doubletap, false);
    OPTION(char, Options.rage_doubletapkey, NULL);
    OPTION(bool, Options.rage_doubletapinstant, false);
    MULTIOPTION(Options.rage_teleportmode, NORMAL = false, EXTENDED = false, DISABLED = false);
    OPTION(bool, Options.rage_global_norecoil, false);
    OPTION(bool, Options.rage_global_nospread, false);
    OPTION(bool, Options.rage_revolverprep, false);
    OPTION(bool, Options.rage_noscope, false);
    OPTION(char, Options.rage_damageoverridekey, NULL);
    OPTION(bool, Options.rage_spasmlock, false);
    /*----------------default----------------*/
    OPTION(int, Options.rage_default_hitchance, 0);
    MULTIOPTION(Options.rage_default_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_default_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_default_mindmgocluded, 0);
    OPTION(int, Options.rage_default_mindmgvisible, 0);
    OPTION(int, Options.rage_default_backtrack, 0);
    OPTION(int, Options.rage_default_delay, 0);
    OPTION(bool, Options.rage_default_forcebody, false);
    OPTION(bool, Options.rage_default_forcehead, false);
    OPTION(bool, Options.rage_default_forceaccuracy, false);
    OPTION(bool, Options.rage_default_inair, false);
    OPTION(int, Options.rage_default_dmgoverride, 0);
    /*----------------pistol-----------------*/
    OPTION(int, Options.rage_pistol_hitchance, 0);
    MULTIOPTION(Options.rage_pistol_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_pistol_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_pistol_mindmgocluded, 0);
    OPTION(int, Options.rage_pistol_mindmgvisible, 0);
    OPTION(int, Options.rage_pistol_backtrack, 0);
    OPTION(int, Options.rage_pistol_delay, 0);
    OPTION(bool, Options.rage_pistol_forcebody);
    OPTION(bool, Options.rage_pistol_forcehead);
    OPTION(bool, Options.rage_pistol_forceaccuracy);
    OPTION(bool, Options.rage_pistol_inair);
    OPTION(int, Options.rage_pistol_dmgoverride, 0);
    /*-----------------awp-------------------*/
    OPTION(int, Options.rage_awp_hitchance, 0);
    MULTIOPTION(Options.rage_awp_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_awp_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_awp_mindmgocluded, 0);
    OPTION(int, Options.rage_awp_mindmgvisible, 0);
    OPTION(int, Options.rage_awp_backtrack, 0);
    OPTION(int, Options.rage_awp_delay, 0);
    OPTION(bool, Options.rage_awp_forcebody);
    OPTION(bool, Options.rage_awp_forcehead);
    OPTION(bool, Options.rage_awp_forceaccuracy);
    OPTION(bool, Options.rage_awp_inair);
    OPTION(int, Options.rage_awp_dmgoverride, 0);
    /*----------------scout------------------*/
    OPTION(int, Options.rage_scout_hitchance, 0);
    MULTIOPTION(Options.rage_scout_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_scout_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_scout_mindmgocluded, 0);
    OPTION(int, Options.rage_scout_mindmgvisible, 0);
    OPTION(int, Options.rage_scout_backtrack, 0);
    OPTION(int, Options.rage_scout_delay, 0);
    OPTION(bool, Options.rage_scout_forcebody, false);
    OPTION(bool, Options.rage_scout_forcehead, false);
    OPTION(bool, Options.rage_scout_forceaccuracy, false);
    OPTION(bool, Options.rage_scout_inair, false);
    OPTION(int, Options.rage_scout_dmgoverride, 0);
    /*----------------auto-------------------*/
    OPTION(int, Options.rage_auto_hitchance, 0);
    MULTIOPTION(Options.rage_auto_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_auto_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_auto_mindmgocluded, 0);
    OPTION(int, Options.rage_auto_mindmgvisible, 0);
    OPTION(int, Options.rage_auto_backtrack, 0);
    OPTION(int, Options.rage_auto_delay, 0);
    OPTION(bool, Options.rage_auto_forcebody, false);
    OPTION(bool, Options.rage_auto_forcehead, false);
    OPTION(bool, Options.rage_auto_forceaccuracy, false);
    OPTION(bool, Options.rage_auto_inair, false);
    OPTION(int, Options.rage_auto_dmgoverride, 0);
    /*-----------------ESP-------------------*/
    /*----------------enemy------------------*/
    OPTION(bool, Options.esp_enemy_enabled, false);
    OPTION(char, Options.esp_enemy_enabledkey, NULL);
    MULTIOPTION(Options.esp_enemy_box, OFF = true, 2D = false, CORNERED2D = false, 3D = false);
    OPTION(ImVec4, Options.esp_enemy_boxcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_snaplines, OFF = true, TOP = false, LEFT = false, RIGHT = false, BOTTOM = false, CENTER = false);
    OPTION(ImVec4, Options.esp_enemy_snaplinecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_name, false);
    OPTION(ImVec4, Options.esp_enemy_namecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_health, false);
    OPTION(ImVec4, Options.esp_enemy_healthcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_ammo, false);
    OPTION(ImVec4, Options.esp_enemy_ammocolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_weapon, false);
    OPTION(ImVec4, Options.esp_enemy_weaponcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_flags, TARGET = false, RESOLVESTATUS = false, MONEY = false, ARMOUR = false, UTILITY = false, SCOPE = false, RELOAD = false, EXPLOITS = false, PING = false, BOMB = false, PRIORITY = false, LOCATION = false);
    OPTION(bool, Options.esp_enemy_sound, false);
    OPTION(ImVec4, Options.esp_enemy_soundcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_lineofsight, false);
    OPTION(ImVec4, Options.esp_enemy_lineofsightcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_skeleton, false);
    OPTION(ImVec4, Options.esp_enemy_skeletoncolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_outline, false);
    OPTION(ImVec4, Options.esp_enemy_outlinecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_chamsbacktrack, false);
    OPTION(ImVec4, Options.esp_enemy_chamsbacktrackcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_chamsoccluded, false);
    OPTION(ImVec4, Options.esp_enemy_chamsoccludedcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_occludedchamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_enemy_chamsvisible, false);
    OPTION(ImVec4, Options.esp_enemy_chamsvisiblecolor);
    MULTIOPTION(Options.esp_enemy_visiblechamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_enemy_chamsglow, false);
    OPTION(ImVec4, Options.esp_enemy_chamsglowcolor);
    OPTION(bool, Options.esp_enemy_bullettracers, false);
    OPTION(ImVec4, Options.esp_enemy_bullettracerscolor);
    OPTION(bool, Options.esp_enemy_shadeflat, false);
    OPTION(bool, Options.esp_enemy_dormant, false);
    /*----------------local------------------*/
    OPTION(bool, Options.esp_local_enabled, false);
    OPTION(char, Options.esp_local_enabledkey, NULL);
    OPTION(bool, Options.esp_local_flat, false);
    MULTIOPTION(Options.esp_local_box, OFF = true, 2D = false, CORNERED2D = false, 3D = false);
    OPTION(ImVec4, Options.esp_local_boxcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_name, false);
    OPTION(bool, Options.esp_local_namecolor, false);
    OPTION(bool, Options.esp_local_health, false);
    OPTION(bool, Options.esp_local_ammo, false);
    OPTION(ImVec4, Options.esp_local_ammocolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_weapon, false);
    OPTION(ImVec4, Options.esp_local_weaponcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_glow, false);
    OPTION(ImVec4, Options.esp_local_glowcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_skeleton, false);
    OPTION(ImVec4, Options.esp_local_skeletoncolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_bullettracers, false);
    OPTION(ImVec4, Options.esp_local_bullettracerscolor, ImVec4(0, 0, 0, 0));
    OPTION(int, Options.esp_local_scopeblend, 0);
    OPTION(bool, Options.esp_local_chamsbacktrack, false);
    OPTION(ImVec4, Options.esp_local_chamsbacktrackcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_chams, false);
    OPTION(Options.esp_local_chamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_chamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_local_desyncchams, false);
    OPTION(ImVec4, Options.esp_local_desyncchamscolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_armchams, false);
    OPTION(ImVec4, Options.esp_local_armchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_armchamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool Options.esp_local_armchamsdraworiginal, false);
    OPTION(bool, Options.esp_local_weaponchams, false);
    OPTION(ImVec4, Options.esp_local_weaponchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_weaponchamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_local_weaponchamsdraworiginal, false);
    /*----------------other------------------*/
    OPTION(bool, Options.esp_other_bombtimer, false); // attach to radar curve
    OPTION(bool, Options.esp_other_bombchams, false);
    OPTION(ImVec4, Options.esp_other_bombchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_bombchamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_other_bombglow, false);
    OPTION(ImVec4, Options.esp_other_bombglowcolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_bombflags, STATE = false, TIMER = false);
    MULTIOPTION(Options.esp_other_penetrationcrosshair, OFF = false, DEFAULT = false, CIRCLE = false, SQUARE = false);
    OPTION(bool, Options.esp_other_fullbright, false);
    OPTION(bool, Options.esp_other_worldcolor, false);
    OPTION(ImVec4, Options.esp_other_worldcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_propcolor, false);
    OPTION(ImVec4, Options.esp_other_propcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_skycolor, false);
    OPTION(ImVec4, Options.esp_other_skycolorcolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_skybox, SKYBOX1 = false, SKYBOX2 = false);
    OPTION(std::string, Options.esp_other_customskybox, nullptr);
    MULTIOPTION(Options.esp_other_removals, SCOPEOVERLAY = false, SCOPEZOOM = false, VIEWPUNCH = false, AIMPUNCH = false, SMOKEEFFECTS = false, FLASHEFFECTS = false, FOG = false, POSTPROCCESING = false, ARMS = false, WEAPON = false);
    OPTION(bool, Options.esp_other_thirdperson, false);
    OPTION(char, Options.esp_other_thirdpersonkey, NULL);
    OPTION(int, Options.esp_other_thirdpersondistance, 0);
    OPTION(bool, Options.esp_other_thirdpersonondeath, false);
    OPTION(bool, Options.esp_other_thirdpersondisablenade, false);
    OPTION(bool, Options.esp_other_radarhack, false);
    OPTION(bool, Options.esp_other_streamproof, false);
    OPTION(bool, Options.esp_other_oofarrows, false);
    OPTION(ImVec4, Options.esp_other_oofarrowscolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_molotovtracer, false);
    OPTION(ImVec4, Options.esp_other_molotovtracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_smoketracer, false);
    OPTION(ImVec4, Options.esp_other_smoketracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_hetracer, false);
    OPTION(ImVec4, Options.esp_other_hetracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_flashbangtracer, false);
    OPTION(ImVec4, Options.esp_other_flashbangtracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_decoytracer, false);
    OPTION(ImVec4, Options.esp_other_decoytracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_molotovspread, false);
    OPTION(ImVec4, Options.esp_other_molotovspreadcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_smokespread, false);
    OPTION(ImVec4, Options.esp_other_smokespreadcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_droppedweapons, false);
    MULTIOPTION(Options.esp_other_droppedweaponflags, ICON = false, TEXT = false, DISTANCE = false, AMMO = false);
    OPTION(bool, Options.esp_other_droppedweaponchams, false);
    OPTION(ImVec4, Options.esp_other_droppedweaponchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_droppedweaponchamsmaterial, TEXT = false, GLOW = false, ICON = false);
    OPTION(bool, Options.esp_other_droppedweaponglow, false);
    /*----------------/////------------------*/
    // TODO: add crates for dangerzone
    // TODO: fov crap
    /*----------------/////------------------*/
    MULTIOPTION(Options.esp_other_hitsound, OFF = false, AHHH = false, ANIMEMOAN = false, BELL = false, FLICK = false, METALIC = false, MINECRAFT = false, ROBLOX = false);
    MULTIOPTION(Options.esp_other_hiteffect, OFF = false, EFFECT1 = false, EFFECT2 = false); // TODO: add effects
    MULTIOPTION(Options.esp_other_killsound, OFF = false, OVERWATCHCSGO = false, OVERWATCHCSS = false, TECHNO = false);
    MULTIOPTION(Options.esp_other_killanouncer, OFF = false, QUAKEFEMALE = false, QUAKESTANDARD = false, VALORANT = false, ANIME = false);
    MULTIOPTION(Options.esp_other_deathsound, OFF = false, AHHH = false, ERROR = false, FAIL = false, WILHELM = false);
    OPTION(bool, Options.esp_other_grenadeprediction, false);
    OPTION(ImVec4, Options.esp_other_grenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
    OPTION(ImVec4, Options.esp_other_grenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_enemygrenadeprediction, false);
    OPTION(ImVec4, Options.esp_other_enemygrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
    OPTION(ImVec4, Options.esp_other_enemygrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_watermark, false);
    OPTION(bool, Options.esp_other_visualiseoneway, false);
    OPTION(char, Options.esp_other_visualiseonewaykey, NULL);
    OPTION(bool, Options.esp_other_hitmarker, false);
    /*---------------ANTIAIM-----------------*/
    /*----------------rage-------------------*/
    OPTION(bool, Options.antiaim_rage_xenable, false);
    OPTION(int, Options.antiaim_rage_xbaseangle, 0);
    MULTIOPTION(Options.antiaim_rage_xanglemode, STATIC = false, UDZRANDOM = false, FLUCTUATE = false);
    OPTION(bool, Options.antiaim_rage_xjitterenable, false);
    OPTION(int, Options.antiaim_rage_xjitterrangemin - 15);
    OPTION(int, Options.antiaim_rage_xjitterrangemax, 15);
    MULTIOPTION(Options.antiaim_rage_xjittermode, OFFSET = false, RANDOM = false);
    OPTION(bool, Options.antiaim_rage_yenable, false);
    OPTION(int, Options.antiaim_rage_ybaseangle, -180, 180);
    MULTIOPTION(Options.antiaim_rage_yanglemode, STATIC = false, SPIN = false, WASDRANDOM = false);
    OPTION(bool, Options.antiaim_rage_yjitterenable, false);
    OPTION(int, Options.antiaim_rage_yjitterrangemin, -15);
    OPTION(int, Options.antiaim_rage_yjitterrangemax, 15);
    MULTIOPTION(Options.antiaim_rage_yjittermode, OFFSET = false, RANDOM = false);
    OPTION(bool, Options.antiaim_rage_desyncenable, false);
    MULTIOPTION(Options.antiaim_rage_desyncside, OFF = false, LEFT = false, RIGHT = false, RANDOM = false);
    OPTION(int, Options.antiaim_rage_desyncrangeleft, -15);
    OPTION(int, Options.antiaim_rage_desyncrangeright, 15);
    MULTIOPTION(Options.antiaim_rage_desyncfreestand, OFF = false, FREESTAND = false, ANTIFREESTAND = false);
    OPTION(bool, Options.antiaim_rage_desyncavoidoverlap, false);
    OPTION(bool, Options.antiaim_rage_desyncdormant, false);
    OPTION(bool, Options.antiaim_rage_fakelagenable, false);
    OPTION(int, Options.antiaim_rage_fakelagrangemin, 2);
    OPTION(int, Options.antiaim_rage_fakelagrangemax, 6);
    MULTIOPTION(Options.antiaim_rage_maxfakelagtriggers, STANDING = false, MOVING = false, INAIR = false, ONSHOT = false, ONPEEK = false, ONDAMAGE = false, ONRELOAD = false);
    OPTION(bool, Options.antiaim_rage_fakelagdormant, false);
    OPTION(bool, Options.antiaim_rage_invert, false);
    OPTION(char, Options.antiaim_rage_invertkey, NULL);
    OPTION(bool, Options.antiaim_rage_targetdetection, false);
    OPTION(bool, Options.antiaim_rage_walldetection, false);
    OPTION(bool, Options.antiaim_rage_slidewalk, false);
    OPTION(bool, Options.antiaim_rage_fakeduck, false);
    OPTION(char, Options.antiaim_rage_fakeduckkey, NULL);
    OPTION(bool, Options.antiaim_rage_teleport, false);
    OPTION(char, Options.antiaim_rage_teleportkey, NULL);
    OPTION(bool, Options.antiaim_rage_crimwalk, false);
    OPTION(char, Options.antiaim_rage_crimwalkkey, NULL);
    OPTION(bool, Options.antiaim_rage_antibackstab, false);
    /*---------------MODIFIER----------------*/
    /*-----------------MISC------------------*/
    /*---------------general-----------------*/
    OPTION(bool, Options.misc_general_autoaccept, false);
    OPTION(bool, Options.misc_general_autopisol, false);
    OPTION(int, Options.misc_general_autopistoldelay, 0);
    OPTION(bool, Options.misc_general_preservekillfeed, false);
    OPTION(bool, Options.misc_general_autodefuse, false);
    OPTION(bool, Options.misc_general_autoextinguishincendiarys, false);
    OPTION(bool, Options.misc_general_fakeping, false)
    OPTION(int, Options.misc_general_fakepingamount, 0);
    OPTION(bool, Options.misc_general_clantag, false);
    OPTION(bool, Options.misc_general_blockbot, false);
    OPTION(char, Options.misc_general_blockbotkey, NULL);
    OPTION(bool, Options.misc_general_headstandbot, false);
    OPTION(char, Options.misc_general_headstandbotkey, NULL);
    MULTIOPTION(Options.misc_general_forceregion, OFF = false, AUSTRALIA = false, AUSTRIA = false, BRAZIL = false, CHILE = false, DUBAI = false, FRANCE = false, GERMANY = false, HONGKONG = false, INDIACHENNAI = false, INDIAMUMBAI = false, JAPAN = false, LUXEMBOURG = false, THENETHER = false, PERU = false, PHILLIPINES = false, POLAND = false, SINGAPORE = false, NOWATER = false, SPAIN = false, SWEDEN = false, UNITEDKINGDOM = false, USAATLANTA = false, USACHICAGO = false, USALOSANGELES = false, USAMOSESLAKE = false, USASEATTLE = false, USAOKLAHOMA = false, USAWASHINGTONDC = false);
    OPTION(bool, Options.misc_general_revealoverwatch, false);
    OPTION(bool, Options.misc_general_revealranks, false);
    OPTION(bool, Options.misc_general_slowwalk, false);
    OPTION(int, Options.misc_general_slowwalkspeed, 100);
    OPTION(bool, Options.misc_general_antiuntrusted, false);
    OPTION(bool, Options.misc_general_bypasssvpure, false);
    OPTION(bool, Options.misc_general_infiniteduck, false);
    OPTION(bool, Options.misc_general_quickstop, false);
    OPTION(bool, Options.misc_general_unlockinventory, false);
    MULTIOPTION(Options.misc_general_namechanger, OFF = false, TEAMONLY = false, ENEMYONLY = false, EVERYONE = false, CORRUPT = false);
    OPTION(std::string, Options.misc_general_commandspammer, nullptr);
    MULTIOPTION(Options.misc_general_informationspammer, NAME = false, RANK = false, WEAPON = false, LOCATION = false, HEALTH = false);
    OPTION(bool, Options.misc_general_grenadehelper, false);
    OPTION(char, Options.misc_general_grenadehelpervisiblekey, NULL);
    OPTION(char, Options.misc_general_grenadehelperexecutekey, NULL);
    OPTION(bool, Options.misc_general_grenadehelpervwge, false);
    OPTION(bool, Options.misc_general_bhop, false);
    OPTION(int, Options.misc_general_bhophitchance, 100);
    OPTION(bool, Options.misc_general_bhophitchancerandom, false);
    OPTION(bool, Options.misc_general_autostrafe, false);
    OPTION(bool, Options.misc_general_aircrouch, false);
    OPTION(bool, Options.misc_general_peekassist, false);
    OPTION(char, Options.misc_general_peekassistkey, NULL);
    OPTION(bool, Options.misc_buybot_enable, false);
    MULTIOPTION(Options.misc_buybot_primary, OFF = false, AUTO = false, SCOUT = false, AWP = false, AKM4 = false);
    MULTIOPTION(Options.misc_buybot_secondary, OFF = false, DUALBERETTAS = false, P250 = false, FIVE7TEC9 = false, DEAGLER8 = false);
    MULTIOPTION(Options.misc_buybot_nades, SMOKE = false, FLASH = false, MOLOTOV = false, DECOY = false, HEGRENADE = false);
    MULTIOPTION(Options.misc_buybot_other, KEVLAR = false, HELMET = false, DEFUSER = false, TASER = false, RIOTSHEILD = false);
    OPTION(bool, Options.misc_general_triggerban, false);
    OPTION(bool, Options.misc_general_unlockachievements, false);
    OPTION(bool, Options.misc_general_unload, false);
    // for loop here? for config list
    OPTION(std::String, Options.config_name, nullptr);
    OPTION(bool, Options.config_create, false);
    OPTION(bool, Options.config_save, false);
    OPTION(bool, Options.config_load, false);
    OPTION(bool, Options.config_delete, false);
    OPTION(bool, Options.config_reset, false);
    OPTIONS(bool, Options.config_refresh, false);
    /*-------------playerlist----------------*/
    OPTION(bool, Options.misc_player_enable, false);
    // for loop here? for player list
    OPTION(bool, Options.misc_player_stealname, false);
    OPTION(bool, Options.misc_player_copyclantag, false);
    OPTION(bool, Options.misc_player_priority, false);
    OPTION(bool, Options.misc_player_whitelist, false);
    OPTION(bool, Options.misc_player_set_rage, false);
    OPTION(bool, Options.misc_player_set_legit, false);
    OPTION(bool, Options.misc_player_follow, false);
    MULTIOPTION(Options.misc_player_forcehitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(bool, Options.misc_player_forcehead, false);
    OPTION(bool, Options.misc_player_forcebody, false);
    OPTION(bool, Options.misc_player_dontresolve, false);
};

//todo: create some default settings
struct DefaultOptions {
    /*---------------RAGEAIM-----------------*/
    /*---------------general-----------------*/
    OPTION(bool, Options.rage_enable, false);
    OPTION(bool, Options.rage_safepoint_enable, false);
    OPTION(bool, Options.rage_forcesafepoint, false);
    OPTION(char, Options.rage_forcesafepointkey, NULL);
    MULTIOPTION(Options.rage_safepointhitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_safepointdelay, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_safepointmaxdelay, 0);
    OPTION(bool, Options.rage_silentaim, false);
    OPTION(bool, Options.rage_autofire, false);
    OPTION(bool, Options.rage_autoscope, false);
    OPTION(bool, Options.rage_autostop, false);
    OPTION(bool, Options.rage_penetration, false);
    OPTION(bool, Options.rage_knifebot, false);
    OPTION(bool, Options.rage_zeusbot, false);
    OPTION(bool, Options.rage_resolver, false);
    OPTION(bool, Options.rage_resolverx, false);
    OPTION(bool, Options.rage_resolvery, false);
    OPTION(bool, Options.rage_bruteforce, false);
    OPTION(char, Options.rage_bruteforcekey, NULL);
    OPTION(bool, Options.rage_hideshots, false);
    OPTION(char, Options.rage_hideshotskey, NULL);
    OPTION(bool, Options.rage_doubletap, false);
    OPTION(char, Options.rage_doubletapkey, NULL);
    OPTION(bool, Options.rage_doubletapinstant, false);
    MULTIOPTION(Options.rage_teleportmode, NORMAL = false, EXTENDED = false, DISABLED = false);
    OPTION(bool, Options.rage_global_norecoil, false);
    OPTION(bool, Options.rage_global_nospread, false);
    OPTION(bool, Options.rage_revolverprep, false);
    OPTION(bool, Options.rage_noscope, false);
    OPTION(char, Options.rage_damageoverridekey, NULL);
    OPTION(bool, Options.rage_spasmlock, false);
    /*----------------default----------------*/
    OPTION(int, Options.rage_default_hitchance, 0);
    MULTIOPTION(Options.rage_default_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_default_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_default_mindmgocluded, 0);
    OPTION(int, Options.rage_default_mindmgvisible, 0);
    OPTION(int, Options.rage_default_backtrack, 0);
    OPTION(int, Options.rage_default_delay, 0);
    OPTION(bool, Options.rage_default_forcebody, false);
    OPTION(bool, Options.rage_default_forcehead, false);
    OPTION(bool, Options.rage_default_forceaccuracy, false);
    OPTION(bool, Options.rage_default_inair, false);
    OPTION(int, Options.rage_default_dmgoverride, 0);
    /*----------------pistol-----------------*/
    OPTION(int, Options.rage_pistol_hitchance, 0);
    MULTIOPTION(Options.rage_pistol_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_pistol_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_pistol_mindmgocluded, 0);
    OPTION(int, Options.rage_pistol_mindmgvisible, 0);
    OPTION(int, Options.rage_pistol_backtrack, 0);
    OPTION(int, Options.rage_pistol_delay, 0);
    OPTION(bool, Options.rage_pistol_forcebody);
    OPTION(bool, Options.rage_pistol_forcehead);
    OPTION(bool, Options.rage_pistol_forceaccuracy);
    OPTION(bool, Options.rage_pistol_inair);
    OPTION(int, Options.rage_pistol_dmgoverride, 0);
    /*-----------------awp-------------------*/
    OPTION(int, Options.rage_awp_hitchance, 0);
    MULTIOPTION(Options.rage_awp_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_awp_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_awp_mindmgocluded, 0);
    OPTION(int, Options.rage_awp_mindmgvisible, 0);
    OPTION(int, Options.rage_awp_backtrack, 0);
    OPTION(int, Options.rage_awp_delay, 0);
    OPTION(bool, Options.rage_awp_forcebody);
    OPTION(bool, Options.rage_awp_forcehead);
    OPTION(bool, Options.rage_awp_forceaccuracy);
    OPTION(bool, Options.rage_awp_inair);
    OPTION(int, Options.rage_awp_dmgoverride, 0);
    /*----------------scout------------------*/
    OPTION(int, Options.rage_scout_hitchance, 0);
    MULTIOPTION(Options.rage_scout_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_scout_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_scout_mindmgocluded, 0);
    OPTION(int, Options.rage_scout_mindmgvisible, 0);
    OPTION(int, Options.rage_scout_backtrack, 0);
    OPTION(int, Options.rage_scout_delay, 0);
    OPTION(bool, Options.rage_scout_forcebody, false);
    OPTION(bool, Options.rage_scout_forcehead, false);
    OPTION(bool, Options.rage_scout_forceaccuracy, false);
    OPTION(bool, Options.rage_scout_inair, false);
    OPTION(int, Options.rage_scout_dmgoverride, 0);
    /*----------------auto-------------------*/
    OPTION(int, Options.rage_auto_hitchance, 0);
    MULTIOPTION(Options.rage_auto_hitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    MULTIOPTION(Options.rage_auto_multipoint, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(int, Options.rage_auto_mindmgocluded, 0);
    OPTION(int, Options.rage_auto_mindmgvisible, 0);
    OPTION(int, Options.rage_auto_backtrack, 0);
    OPTION(int, Options.rage_auto_delay, 0);
    OPTION(bool, Options.rage_auto_forcebody, false);
    OPTION(bool, Options.rage_auto_forcehead, false);
    OPTION(bool, Options.rage_auto_forceaccuracy, false);
    OPTION(bool, Options.rage_auto_inair, false);
    OPTION(int, Options.rage_auto_dmgoverride, 0);
    /*-----------------ESP-------------------*/
    /*----------------enemy------------------*/
    OPTION(bool, Options.esp_enemy_enabled, false);
    OPTION(char, Options.esp_enemy_enabledkey, NULL);
    MULTIOPTION(Options.esp_enemy_box, OFF = true, 2D = false, CORNERED2D = false, 3D = false);
    OPTION(ImVec4, Options.esp_enemy_boxcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_snaplines, OFF = true, TOP = false, LEFT = false, RIGHT = false, BOTTOM = false, CENTER = false);
    OPTION(ImVec4, Options.esp_enemy_snaplinecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_name, false);
    OPTION(ImVec4, Options.esp_enemy_namecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_health, false);
    OPTION(ImVec4, Options.esp_enemy_healthcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_ammo, false);
    OPTION(ImVec4, Options.esp_enemy_ammocolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_weapon, false);
    OPTION(ImVec4, Options.esp_enemy_weaponcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_flags, TARGET = false, RESOLVESTATUS = false, MONEY = false, ARMOUR = false, UTILITY = false, SCOPE = false, RELOAD = false, EXPLOITS = false, PING = false, BOMB = false, PRIORITY = false, LOCATION = false);
    OPTION(bool, Options.esp_enemy_sound, false);
    OPTION(ImVec4, Options.esp_enemy_soundcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_lineofsight, false);
    OPTION(ImVec4, Options.esp_enemy_lineofsightcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_skeleton, false);
    OPTION(ImVec4, Options.esp_enemy_skeletoncolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_outline, false);
    OPTION(ImVec4, Options.esp_enemy_outlinecolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_chamsbacktrack, false);
    OPTION(ImVec4, Options.esp_enemy_chamsbacktrackcolor, ImVec4(0, 0, 0, 0, ));
    OPTION(bool, Options.esp_enemy_chamsoccluded, false);
    OPTION(ImVec4, Options.esp_enemy_chamsoccludedcolor, ImVec4(0, 0, 0, 0, ));
    MULTIOPTION(Options.esp_enemy_occludedchamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_enemy_chamsvisible, false);
    OPTION(ImVec4, Options.esp_enemy_chamsvisiblecolor);
    MULTIOPTION(Options.esp_enemy_visiblechamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_enemy_chamsglow, false);
    OPTION(ImVec4, Options.esp_enemy_chamsglowcolor);
    OPTION(bool, Options.esp_enemy_bullettracers, false);
    OPTION(ImVec4, Options.esp_enemy_bullettracerscolor);
    OPTION(bool, Options.esp_enemy_shadeflat, false);
    OPTION(bool, Options.esp_enemy_dormant, false);
    /*----------------local------------------*/
    OPTION(bool, Options.esp_local_enabled, false);
    OPTION(char, Options.esp_local_enabledkey, NULL);
    OPTION(bool, Options.esp_local_flat, false);
    MULTIOPTION(Options.esp_local_box, OFF = true, 2D = false, CORNERED2D = false, 3D = false);
    OPTION(ImVec4, Options.esp_local_boxcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_name, false);
    OPTION(bool, Options.esp_local_namecolor, false);
    OPTION(bool, Options.esp_local_health, false);
    OPTION(bool, Options.esp_local_ammo, false);
    OPTION(ImVec4, Options.esp_local_ammocolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_weapon, false);
    OPTION(ImVec4, Options.esp_local_weaponcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_glow, false);
    OPTION(ImVec4, Options.esp_local_glowcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_skeleton, false);
    OPTION(ImVec4, Options.esp_local_skeletoncolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_bullettracers, false);
    OPTION(ImVec4, Options.esp_local_bullettracerscolor, ImVec4(0, 0, 0, 0));
    OPTION(int, Options.esp_local_scopeblend, 0);
    OPTION(bool, Options.esp_local_chamsbacktrack, false);
    OPTION(ImVec4, Options.esp_local_chamsbacktrackcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_chams, false);
    OPTION(Options.esp_local_chamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_chamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_local_desyncchams, false);
    OPTION(ImVec4, Options.esp_local_desyncchamscolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_local_armchams, false);
    OPTION(ImVec4, Options.esp_local_armchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_armchamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool Options.esp_local_armchamsdraworiginal, false);
    OPTION(bool, Options.esp_local_weaponchams, false);
    OPTION(ImVec4, Options.esp_local_weaponchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_enemy_weaponchamsmaterial MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_local_weaponchamsdraworiginal, false);
    /*----------------other------------------*/
    OPTION(bool, Options.esp_other_bombtimer, false); // attach to radar curve
    OPTION(bool, Options.esp_other_bombchams, false);
    OPTION(ImVec4, Options.esp_other_bombchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_bombchamsmaterial, MAT1 = true, MAT2 = false); // TODO: add materials
    OPTION(bool, Options.esp_other_bombglow, false);
    OPTION(ImVec4, Options.esp_other_bombglowcolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_bombflags, STATE = false, TIMER = false);
    MULTIOPTION(Options.esp_other_penetrationcrosshair, OFF = false, DEFAULT = false, CIRCLE = false, SQUARE = false);
    OPTION(bool, Options.esp_other_fullbright, false);
    OPTION(bool, Options.esp_other_worldcolor, false);
    OPTION(ImVec4, Options.esp_other_worldcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_propcolor, false);
    OPTION(ImVec4, Options.esp_other_propcolorcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_skycolor, false);
    OPTION(ImVec4, Options.esp_other_skycolorcolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_skybox, SKYBOX1 = false, SKYBOX2 = false);
    OPTION(std::string, Options.esp_other_customskybox, nullptr);
    MULTIOPTION(Options.esp_other_removals, SCOPEOVERLAY = false, SCOPEZOOM = false, VIEWPUNCH = false, AIMPUNCH = false, SMOKEEFFECTS = false, FLASHEFFECTS = false, FOG = false, POSTPROCCESING = false, ARMS = false, WEAPON = false);
    OPTION(bool, Options.esp_other_thirdperson, false);
    OPTION(char, Options.esp_other_thirdpersonkey, NULL);
    OPTION(int, Options.esp_other_thirdpersondistance, 0);
    OPTION(bool, Options.esp_other_thirdpersonondeath, false);
    OPTION(bool, Options.esp_other_thirdpersondisablenade, false);
    OPTION(bool, Options.esp_other_radarhack, false);
    OPTION(bool, Options.esp_other_streamproof, false);
    OPTION(bool, Options.esp_other_oofarrows, false);
    OPTION(ImVec4, Options.esp_other_oofarrowscolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_molotovtracer, false);
    OPTION(ImVec4, Options.esp_other_molotovtracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_smoketracer, false);
    OPTION(ImVec4, Options.esp_other_smoketracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_hetracer, false);
    OPTION(ImVec4, Options.esp_other_hetracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_flashbangtracer, false);
    OPTION(ImVec4, Options.esp_other_flashbangtracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_decoytracer, false);
    OPTION(ImVec4, Options.esp_other_decoytracercolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_molotovspread, false);
    OPTION(ImVec4, Options.esp_other_molotovspreadcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_smokespread, false);
    OPTION(ImVec4, Options.esp_other_smokespreadcolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_droppedweapons, false);
    MULTIOPTION(Options.esp_other_droppedweaponflags, ICON = false, TEXT = false, DISTANCE = false, AMMO = false);
    OPTION(bool, Options.esp_other_droppedweaponchams, false);
    OPTION(ImVec4, Options.esp_other_droppedweaponchamscolor, ImVec4(0, 0, 0, 0));
    MULTIOPTION(Options.esp_other_droppedweaponchamsmaterial, TEXT = false, GLOW = false, ICON = false);
    OPTION(bool, Options.esp_other_droppedweaponglow, false);
    /*----------------/////------------------*/
    // TODO: add crates for dangerzone
    // TODO: fov crap
    /*----------------/////------------------*/
    MULTIOPTION(Options.esp_other_hitsound, OFF = false, AHHH = false, ANIMEMOAN = false, BELL = false, FLICK = false, METALIC = false, MINECRAFT = false, ROBLOX = false);
    MULTIOPTION(Options.esp_other_hiteffect, OFF = false, EFFECT1 = false, EFFECT2 = false); // TODO: add effects
    MULTIOPTION(Options.esp_other_killsound, OFF = false, OVERWATCHCSGO = false, OVERWATCHCSS = false, TECHNO = false);
    MULTIOPTION(Options.esp_other_killanouncer, OFF = false, QUAKEFEMALE = false, QUAKESTANDARD = false, VALORANT = false, ANIME = false);
    MULTIOPTION(Options.esp_other_deathsound, OFF = false, AHHH = false, ERROR = false, FAIL = false, WILHELM = false);
    OPTION(bool, Options.esp_other_grenadeprediction, false);
    OPTION(ImVec4, Options.esp_other_grenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
    OPTION(ImVec4, Options.esp_other_grenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_enemygrenadeprediction, false);
    OPTION(ImVec4, Options.esp_other_enemygrenadepredictiontrailcolor, ImVec4(0, 0, 0, 0));
    OPTION(ImVec4, Options.esp_other_enemygrenadepredictionbouncecolor, ImVec4(0, 0, 0, 0));
    OPTION(bool, Options.esp_other_watermark, false);
    OPTION(bool, Options.esp_other_visualiseoneway, false);
    OPTION(char, Options.esp_other_visualiseonewaykey, NULL);
    OPTION(bool, Options.esp_other_hitmarker, false);
    /*---------------ANTIAIM-----------------*/
    /*----------------rage-------------------*/
    OPTION(bool, Options.antiaim_rage_xenable, false);
    OPTION(int, Options.antiaim_rage_xbaseangle, 0);
    MULTIOPTION(Options.antiaim_rage_xanglemode, STATIC = false, UDZRANDOM = false, FLUCTUATE = false);
    OPTION(bool, Options.antiaim_rage_xjitterenable, false);
    OPTION(int, Options.antiaim_rage_xjitterrangemin - 15);
    OPTION(int, Options.antiaim_rage_xjitterrangemax, 15);
    MULTIOPTION(Options.antiaim_rage_xjittermode, OFFSET = false, RANDOM = false);
    OPTION(bool, Options.antiaim_rage_yenable, false);
    OPTION(int, Options.antiaim_rage_ybaseangle, -180, 180);
    MULTIOPTION(Options.antiaim_rage_yanglemode, STATIC = false, SPIN = false, WASDRANDOM = false);
    OPTION(bool, Options.antiaim_rage_yjitterenable, false);
    OPTION(int, Options.antiaim_rage_yjitterrangemin, -15);
    OPTION(int, Options.antiaim_rage_yjitterrangemax, 15);
    MULTIOPTION(Options.antiaim_rage_yjittermode, OFFSET = false, RANDOM = false);
    OPTION(bool, Options.antiaim_rage_desyncenable, false);
    MULTIOPTION(Options.antiaim_rage_desyncside, OFF = false, LEFT = false, RIGHT = false, RANDOM = false);
    OPTION(int, Options.antiaim_rage_desyncrangeleft, -15);
    OPTION(int, Options.antiaim_rage_desyncrangeright, 15);
    MULTIOPTION(Options.antiaim_rage_desyncfreestand, OFF = false, FREESTAND = false, ANTIFREESTAND = false);
    OPTION(bool, Options.antiaim_rage_desyncavoidoverlap, false);
    OPTION(bool, Options.antiaim_rage_desyncdormant, false);
    OPTION(bool, Options.antiaim_rage_fakelagenable, false);
    OPTION(int, Options.antiaim_rage_fakelagrangemin, 2);
    OPTION(int, Options.antiaim_rage_fakelagrangemax, 6);
    MULTIOPTION(Options.antiaim_rage_maxfakelagtriggers, STANDING = false, MOVING = false, INAIR = false, ONSHOT = false, ONPEEK = false, ONDAMAGE = false, ONRELOAD = false);
    OPTION(bool, Options.antiaim_rage_fakelagdormant, false);
    OPTION(bool, Options.antiaim_rage_invert, false);
    OPTION(char, Options.antiaim_rage_invertkey, NULL);
    OPTION(bool, Options.antiaim_rage_targetdetection, false);
    OPTION(bool, Options.antiaim_rage_walldetection, false);
    OPTION(bool, Options.antiaim_rage_slidewalk, false);
    OPTION(bool, Options.antiaim_rage_fakeduck, false);
    OPTION(char, Options.antiaim_rage_fakeduckkey, NULL);
    OPTION(bool, Options.antiaim_rage_teleport, false);
    OPTION(char, Options.antiaim_rage_teleportkey, NULL);
    OPTION(bool, Options.antiaim_rage_crimwalk, false);
    OPTION(char, Options.antiaim_rage_crimwalkkey, NULL);
    OPTION(bool, Options.antiaim_rage_antibackstab, false);
    /*---------------MODIFIER----------------*/
    /*-----------------MISC------------------*/
    /*---------------general-----------------*/
    OPTION(bool, Options.misc_general_autoaccept, false);
    OPTION(bool, Options.misc_general_autopisol, false);
    OPTION(int, Options.misc_general_autopistoldelay, 0);
    OPTION(bool, Options.misc_general_preservekillfeed, false);
    OPTION(bool, Options.misc_general_autodefuse, false);
    OPTION(bool, Options.misc_general_autoextinguishincendiarys, false);
    OPTION(bool, Options.misc_general_fakeping, false)
    OPTION(int, Options.misc_general_fakepingamount, 0);
    OPTION(bool, Options.misc_general_clantag, false);
    OPTION(bool, Options.misc_general_blockbot, false);
    OPTION(char, Options.misc_general_blockbotkey, NULL);
    OPTION(bool, Options.misc_general_headstandbot, false);
    OPTION(char, Options.misc_general_headstandbotkey, NULL);
    MULTIOPTION(Options.misc_general_forceregion, OFF = false, AUSTRALIA = false, AUSTRIA = false, BRAZIL = false, CHILE = false, DUBAI = false, FRANCE = false, GERMANY = false, HONGKONG = false, INDIACHENNAI = false, INDIAMUMBAI = false, JAPAN = false, LUXEMBOURG = false, THENETHER = false, PERU = false, PHILLIPINES = false, POLAND = false, SINGAPORE = false, NOWATER = false, SPAIN = false, SWEDEN = false, UNITEDKINGDOM = false, USAATLANTA = false, USACHICAGO = false, USALOSANGELES = false, USAMOSESLAKE = false, USASEATTLE = false, USAOKLAHOMA = false, USAWASHINGTONDC = false);
    OPTION(bool, Options.misc_general_revealoverwatch, false);
    OPTION(bool, Options.misc_general_revealranks, false);
    OPTION(bool, Options.misc_general_slowwalk, false);
    OPTION(int, Options.misc_general_slowwalkspeed, 100);
    OPTION(bool, Options.misc_general_antiuntrusted, false);
    OPTION(bool, Options.misc_general_bypasssvpure, false);
    OPTION(bool, Options.misc_general_infiniteduck, false);
    OPTION(bool, Options.misc_general_quickstop, false);
    OPTION(bool, Options.misc_general_unlockinventory, false);
    MULTIOPTION(Options.misc_general_namechanger, OFF = false, TEAMONLY = false, ENEMYONLY = false, EVERYONE = false, CORRUPT = false);
    OPTION(std::string, Options.misc_general_commandspammer, nullptr);
    MULTIOPTION(Options.misc_general_informationspammer, NAME = false, RANK = false, WEAPON = false, LOCATION = false, HEALTH = false);
    OPTION(bool, Options.misc_general_grenadehelper, false);
    OPTION(char, Options.misc_general_grenadehelpervisiblekey, NULL);
    OPTION(char, Options.misc_general_grenadehelperexecutekey, NULL);
    OPTION(bool, Options.misc_general_grenadehelpervwge, false);
    OPTION(bool, Options.misc_general_bhop, false);
    OPTION(int, Options.misc_general_bhophitchance, 100);
    OPTION(bool, Options.misc_general_bhophitchancerandom, false);
    OPTION(bool, Options.misc_general_autostrafe, false);
    OPTION(bool, Options.misc_general_aircrouch, false);
    OPTION(bool, Options.misc_general_peekassist, false);
    OPTION(char, Options.misc_general_peekassistkey, NULL);
    OPTION(bool, Options.misc_buybot_enable, false);
    MULTIOPTION(Options.misc_buybot_primary, OFF = false, AUTO = false, SCOUT = false, AWP = false, AKM4 = false);
    MULTIOPTION(Options.misc_buybot_secondary, OFF = false, DUALBERETTAS = false, P250 = false, FIVE7TEC9 = false, DEAGLER8 = false);
    MULTIOPTION(Options.misc_buybot_nades, SMOKE = false, FLASH = false, MOLOTOV = false, DECOY = false, HEGRENADE = false);
    MULTIOPTION(Options.misc_buybot_other, KEVLAR = false, HELMET = false, DEFUSER = false, TASER = false, RIOTSHEILD = false);
    OPTION(bool, Options.misc_general_triggerban, false);
    OPTION(bool, Options.misc_general_unlockachievements, false);
    OPTION(bool, Options.misc_general_unload, false);
    // for loop here? for config list
    OPTION(std::String, Options.config_name, nullptr);
    OPTION(bool, Options.config_create, false);
    OPTION(bool, Options.config_save, false);
    OPTION(bool, Options.config_load, false);
    OPTION(bool, Options.config_delete, false);
    OPTION(bool, Options.config_reset, false);
    OPTIONS(bool, Options.config_refresh, false);
    /*-------------playerlist----------------*/
    OPTION(bool, Options.misc_player_enable, false);
    // for loop here? for player list
    OPTION(bool, Options.misc_player_stealname, false);
    OPTION(bool, Options.misc_player_copyclantag, false);
    OPTION(bool, Options.misc_player_priority, false);
    OPTION(bool, Options.misc_player_whitelist, false);
    OPTION(bool, Options.misc_player_set_rage, false);
    OPTION(bool, Options.misc_player_set_legit, false);
    OPTION(bool, Options.misc_player_follow, false);
    MULTIOPTION(Options.misc_player_forcehitboxes, HEAD = false, CHEST = false, BODY = false, ARMS = false, LEGS = false);
    OPTION(bool, Options.misc_player_forcehead, false);
    OPTION(bool, Options.misc_player_forcebody, false);
    OPTION(bool, Options.misc_player_dontresolve, false);
};