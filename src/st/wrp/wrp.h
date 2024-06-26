#include "stage.h"

#define CASTLE_FLAG_BANK 0x00

// WRP Sound IDs
#define SE_WARP_ENTER 0x636
#define SE_WARP_DEBRIS 0x644

typedef enum {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_SAVE_GAME_POPUP,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_UNK_14,
    E_ID_15,
    E_WARP,
    E_SMALL_ROCKS,
} EntityIDs;

typedef struct {
    s16 x, y;
} WarpCoord;

extern u8 D_8003BEBC[];
extern s32 D_8003C8B8;

extern u16 g_InitializeData0[];
extern u16 D_80180458[];
extern u16 g_EInitGeneric[];
extern u16 D_801804C4[];
extern u32 D_80180608[];
extern u32 D_80180648;
extern WarpCoord D_8018065C[];
extern u16 D_80180FE8[];
extern u32 D_80181044[];
extern u16 D_801810A0[]; // sestren: soul steal random angle offsets?
extern u16 D_801810B0[]; // sestren: soul steal animation frame properties?
extern u32 D_80181110[];

extern s32 D_80193AA0; // rename into move_room?
extern s32 D_80193AA4;
extern s32 D_80193AA8;
extern s32 D_80193AAC;

void func_8018F838(Entity*);
void EntityUnkId15(Entity* entity);
