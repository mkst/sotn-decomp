// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

extern s32 D_us_801D36E8[];
extern s32 D_us_801D3768[];
extern s32 D_us_801D4344;

void func_us_801C096C(void) {
    Entity* entity;
    Primitive* prim;
    s16 primIndex;
    s32 angle;
    s32 scale;
    s32 i;
    s32 colliderSize;
    s32* colliders;

    g_CurrentEntity = &DOPPLEGANGER;
    DOPPLEGANGER.animSet = ANIMSET_OVL(1);
    DOPPLEGANGER.unk5A = 8;
    g_PlayerDraw[8].enableColorBlend = 0;
    DOPPLEGANGER.zPriority = g_unkGraphicsStruct.g_zEntityCenter + 8;
    if (DOPPLEGANGER.posX.i.hi < PLAYER.posX.i.hi) {
        DOPPLEGANGER.facingLeft = false;
    } else {
        DOPPLEGANGER.facingLeft = true;
    }

    DOPPLEGANGER.palette = PAL_OVL(0x200);
    DOPPLEGANGER.scaleX = 0x100;
    DOPPLEGANGER.scaleY = 0x100;
    DOPPLEGANGER.drawMode = DRAW_DEFAULT;
    DOPPLEGANGER.flags =
        FLAG_UNK_10000000 | FLAG_POS_CAMERA_LOCKED | FLAG_UNK_400000;

    // BUG: this loop seems to be clearing parts of the floor
    //      ceiling colliders, but not all of them
    colliderSize = (sizeof(Collider) * 6) + 0x1C;
    colliders = (s32*)g_Dop.colFloor;
    for (i = 0; i < colliderSize; i++, colliders++) {
        *colliders = 0;
    }

    D_us_801D4344 = 1;
    g_Dop.vram_flag = 1;
    func_8010E570(0);
    entity = &g_Entities[E_ID_41];

    for (i = 0; i < 3; i++, entity++) {
        DestroyEntity(entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->unk5A = i + 9;
        entity->palette = PAL_OVL(0x200);
        entity->flags = FLAG_POS_CAMERA_LOCKED;
    }
    primIndex = g_api.AllocPrimitives(PRIM_TILE, 6);
    prim = &g_PrimBuf[primIndex];
    g_Entities[E_ID_41].primIndex = primIndex;
    g_Entities[E_ID_41].flags |= FLAG_HAS_PRIMS;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
    }

    for (i = 0; i < 32; i++) {
        angle = (rand() & 0x3FF) + 0x100;
        scale = (rand() & 0xFF) + 0x100;
        D_us_801D36E8[i] = ((rcos(angle) << 4) * scale) >> 8;
        D_us_801D3768[i] = -(((rsin(angle) << 4) * scale) >> 7);
    }

    g_api.TimeAttackController(
        TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, TIMEATTACK_SET_VISITED);
}

#include "../dop_check_st_collision.h"

extern s32 D_us_801805B8;
extern s16 D_us_80181274[];
extern s32 D_us_80181298[];
extern u8 D_us_80183CFC[][4];
extern AnimationFrame* D_us_80183D40[];
extern SpriteParts* D_us_801B1674[];
extern s32 D_us_801D3FEC;

void EntityDoppleganger40(void) {
    s32 i;         // s0
    s32 status;    // s1
    s16 step;      // s2
    s16 step_s;    // s3
    s32 var_s5;    // s4
    s32 posY;      // s6
    s32 posX;      // s7
    s32 vram_flag; // s8
    Pos pos;
    Pos unused_pos;
    SpriteParts* parts;

    g_CurrentEntity = &DOPPLEGANGER;
    g_Dop.unk4C = 0;
    var_s5 = 0;
    step = 0;
    step_s = 0;
    var_s5 = 0;
    DOPPLEGANGER.drawFlags = FLAG_DRAW_DEFAULT;

    if (!(g_Dop.status & PLAYER_STATUS_DEAD)) {
        if ((DOPPLEGANGER.step != Dop_Kill) &&
            (DOPPLEGANGER.flags & FLAG_DEAD)) {
            D_us_801805B8 |= 2;
            step = DOPPLEGANGER.step;
            step_s = DOPPLEGANGER.step_s;
            pos.x.val = D_us_80181298[g_CurrentEntity->nFramesInvincibility];
            SetDopplegangerStep(Dop_Kill);
        } else {
            for (i = 0; i < LEN(g_Dop.timers); i++) {
                if (g_Dop.timers[i]) {
                    switch (i) {
                    case 0:
                    case 1:
                        break;
                    case 2:
                        DOPPLEGANGER.palette = g_Dop.unk40;
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        break;
                    case 15:
                        func_us_801C4954(0, 0);
                        break;
                    }

                    if (--g_Dop.timers[i] == 0) {
                        switch (i) {
                        case 0:
                        case 1:
                            break;
                        case 2:
                            DOPPLEGANGER.palette = PAL_OVL(0x200);
                            break;
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                        case 10:
                        case 11:
                        case 12:
                        case 13:
                        case 14:
                            break;
                        case 15:
                            func_8010E0B8();
                            break;
                        }
                    }
                }
            }

            g_Dop.padHeld = g_Dop.padPressed;
            if (g_Dop.demo_timer != 0) {
                g_Dop.demo_timer--;
                g_Dop.padPressed = g_Dop.padSim & 0xFFFF;
            } else {
                g_Dop.padPressed = g_pads[1].pressed;
            }

            g_Dop.padTapped =
                (g_Dop.padHeld ^ g_Dop.padPressed) & g_Dop.padPressed;
            if (g_Dop.status & PLAYER_STATUS_UNK8) {
                g_Dop.padTapped &= ~(PAD_SQUARE | PAD_CIRCLE);
                g_Dop.padPressed &= ~(PAD_SQUARE | PAD_CIRCLE);
            }

            if (!g_Dop.timers[14]) {
                if ((g_CurrentEntity->hitFlags > 0) &&
                    (g_CurrentEntity->hitFlags < 4)) {
                    step = DOPPLEGANGER.step;
                    step_s = DOPPLEGANGER.step_s;
                    pos.x.val =
                        D_us_80181298[g_CurrentEntity->nFramesInvincibility];

                    if ((g_Dop.unk6C - g_Dop.unk6A) >= 10) {
                        pos.y.val = 3;
                    } else {
                        pos.y.val = 2;
                    }

                    i = 3;
                    if (pos.x.val & 0x200) {
                        i = 7;
                    }

                    if (DOPPLEGANGER.step == Dop_StatusStone) {
                        i = 8;
                    }

                    switch (i) {
                    case 0:
                    case 1:
                    case 2:
                        break;
                    case 3:
                        SetDopplegangerStep(Dop_Hit);
                        break;
                    case 7:
                        SetDopplegangerStep(Dop_StatusStone);
                        break;
                    case 4:
                    case 5:
                    case 6:
                        break;
                    case 8:
                        var_s5 = 1;
                        break;
                    case 9:
                        break;
                    }
                }
            }

            if ((g_Dop.padTapped & PAD_R1) &&
                (DOPPLEGANGER.step == Dop_Stand ||
                 DOPPLEGANGER.step == Dop_Walk ||
                 DOPPLEGANGER.step == Dop_Crouch ||
                 DOPPLEGANGER.step == Dop_Fall ||
                 DOPPLEGANGER.step == Dop_Jump ||
                 DOPPLEGANGER.step == Dop_HighJump ||
                 DOPPLEGANGER.step == Dop_MorphMist)) {
                if (DOPPLEGANGER.step == Dop_Crouch) {
                    D_us_801D3FEC = 12;
                }
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
                if (DOPPLEGANGER.rotate == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotate = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(6);
                g_Dop.unk66 = 0;
            }

            if ((g_Dop.padTapped & PAD_R2) &&
                (DOPPLEGANGER.step == Dop_Stand ||
                 DOPPLEGANGER.step == Dop_Walk ||
                 DOPPLEGANGER.step == Dop_Crouch ||
                 DOPPLEGANGER.step == Dop_Fall ||
                 DOPPLEGANGER.step == Dop_Jump ||
                 DOPPLEGANGER.step == Dop_HighJump ||
                 DOPPLEGANGER.step == Dop_MorphBat)) {
                if (DOPPLEGANGER.rotate == FIX(1.0 / 32.0)) {
                    DOPPLEGANGER.rotate = 0;
                    DOPPLEGANGER.animCurFrame = 0x9D;
                    DOPPLEGANGER.facingLeft++;
                    DOPPLEGANGER.facingLeft &= 1;
                }
                SetDopplegangerStep(8);
                g_api.PlaySfx(SFX_TRANSFORM_LOW);
            }

            if ((g_Dop.padTapped & PAD_TRIANGLE) &&
                (g_Dop.padPressed & PAD_DOWN) && DOPPLEGANGER.step == 3) {
                func_us_801C504C();
            }
        }
    }
    g_Dop.prev_step = DOPPLEGANGER.step;
    g_Dop.prev_step_s = DOPPLEGANGER.step_s;

    switch (DOPPLEGANGER.step) {
    case Dop_Stand:
        DopplegangerStepStand();
        break;
    case Dop_Walk:
        DopplegangerStepWalk();
        break;
    case Dop_Crouch:
        DopplegangerStepCrouch();
        break;
    case Dop_Fall:
        DopplegangerStepFall();
        break;
    case Dop_Jump:
        DopplegangerStepJump();
        break;
    case Dop_MorphBat:
        ControlBatForm();
        break;
    case Dop_UnmorphBat:
        DopplegangerStepUnmorphBat();
        break;
    case Dop_MorphMist:
        ControlMistForm();
        break;
    case Dop_UnmorphMist:
        DopplegangerStepUnmorphMist();
        break;
    case Dop_HighJump:
        DopplegangerStepHighJump();
        break;
    case Dop_SwordWarp:
        DopplegangerStepSwordWarp();
        break;
    case Dop_Hit:
        DopplegangerHandleDamage(&pos, step, step_s);
        break;
    case Dop_Kill:
        DopplegangerStepKill(&pos, step, step_s);
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT, true);
        break;
    case Dop_StatusStone:
        DopplegangerStepStone(var_s5);
        break;
    }

    g_Dop.status &= ~PLAYER_STATUS_UNK8;
    // TODO: is unk08 previous status?
    g_Dop.unk08 = g_Dop.status;

    status = 0;

    switch (DOPPLEGANGER.step) {
    case Dop_Crouch:
        if (DOPPLEGANGER.step_s != 2) {
            status = PLAYER_STATUS_CROUCH;
        }
        // fallthrough
    case Dop_Stand:
    case Dop_Walk:
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Fall:
    case Dop_Jump:
        status = PLAYER_STATUS_UNK2000;
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_MorphBat:
        func_us_801C4954(1, 1);
        if (DOPPLEGANGER.step_s == 3) {
            func_us_801C4A30(1, 4);
        }
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_BAT_FORM;
        if (DOPPLEGANGER.step_s) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        break;
    case Dop_MorphMist:
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case Dop_UnmorphMist:
        func_us_801C4954(1, 1);
        status = PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_MIST_FORM;
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        func_us_801C4A30(1, 4);
        break;
    case Dop_UnmorphBat:
        func_us_801C4954(1, 1);
        status = PLAYER_STATUS_UNK400000 | PLAYER_STATUS_UNK100000 |
                 PLAYER_STATUS_BAT_FORM;
        if (DOPPLEGANGER.step_s == 0) {
            DOPPLEGANGER.animSet = ANIMSET_OVL(2);
        }
        func_us_801C4A30(1, 4);
        break;
    case Dop_HighJump:
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Hit:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000;
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_Kill:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_DEAD |
                 PLAYER_STATUS_UNK10000;
        if (DOPPLEGANGER.step_s == 0x80) {
            status |= PLAYER_STATUS_UNK80000;
        }
        func_us_801C4954(1, 1);
        func_us_801C4A30(1, 4);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    case Dop_SwordWarp:
        status = PLAYER_STATUS_UNK100000;
        func_us_801C4954(1, 1);
        func_us_801C4A30(4, 0x30);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        DOPPLEGANGER.palette = PAL_OVL(0x20D);
        break;
    case 12:
        status = PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK10000 |
                 PLAYER_STATUS_STONE;
        func_us_801C4954(1, 1);
        DOPPLEGANGER.animSet = ANIMSET_OVL(1);
        break;
    }

    if (g_Dop.timers[0]) {
        status |= PLAYER_STATUS_UNK100000 | PLAYER_STATUS_POISON;
        func_us_801C4954(1, 1);
    }

    g_Dop.status = status;

    if ((g_Dop.unk08 & PLAYER_STATUS_UNK10000) &&
        !(g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_UNK10000))) {
        g_Dop.timers[15] = 4;
        DOPPLEGANGER.palette = PAL_OVL(0x200);
    }
    PlayAnimation(D_us_80183CFC, D_us_80183D40);
    if (g_Dop.status & PLAYER_STATUS_DEAD) {
        if (DOPPLEGANGER.poseTimer < 0) {
            DOPPLEGANGER.animCurFrame |= 0x8000;
        }
        DOPPLEGANGER.hitboxState = 0;
    } else {
        DOPPLEGANGER.hitboxState = g_Dop.unk70;
        if (g_Dop.status & PLAYER_STATUS_STONE) {
            DOPPLEGANGER.hitboxState &= 0xFFCF;
        }
        if ((g_Dop.timers[13] | g_Dop.timers[14]) != 0) {
            DOPPLEGANGER.hitboxState = 0;
        }
    }
    func_8010D59C();
    vram_flag = g_Dop.vram_flag;
    posX = DOPPLEGANGER.posX.val;
    posY = DOPPLEGANGER.posY.val;

    if ((g_Dop.status & PLAYER_STATUS_BAT_FORM) ||
        DOPPLEGANGER.step == Dop_HighJump ||
        abs(DOPPLEGANGER.velocityX) > FIX(2)) {

        DOPPLEGANGER.velocityX >>= 2;
        DOPPLEGANGER.velocityY >>= 2;
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            if (g_Dop.status & PLAYER_STATUS_UNK400000) {
                OVL_EXPORT(CheckStageCollision)(0);
            } else {
                OVL_EXPORT(CheckStageCollision)(1);
            }
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi >= 0) {
            OVL_EXPORT(CheckStageCollision)(0);
        }
        if (DOPPLEGANGER.posY.i.hi < 0) {
            DOPPLEGANGER.posY.val = FIX(-1);
        }

        DOPPLEGANGER.velocityX *= 4;
        DOPPLEGANGER.velocityY *= 4;
    } else if (g_Dop.status & PLAYER_STATUS_UNK800000) {
        OVL_EXPORT(CheckStageCollision)(0);
    } else {
        OVL_EXPORT(CheckStageCollision)(1);
    }

    g_Dop.unk04 = vram_flag;
    func_8010D800();

    if (DOPPLEGANGER.animSet == (s16)ANIMSET_OVL(2)) {
        parts = D_us_801B1674[DOPPLEGANGER.animCurFrame & 0x7FFF];

        parts->parts[0].offsetx =
            D_us_801D3FEC + D_us_80181274[DOPPLEGANGER.animCurFrame];
    }

    FntPrint("noroi:%02x\n", g_Dop.timers[1]);
}

extern s32 D_us_801D32F4;
extern s32 D_us_801D32F8;

void func_us_801C1DB0(s32 arg0) {
    D_us_801D32F4 = arg0;
    D_us_801D32F8 = 0;
}

INCLUDE_ASM("boss/rbo5/nonmatchings/doppleganger", func_us_801C1DC8);

extern EInit D_us_80180424;

void func_us_801C2D90(Entity* self) {
    Entity* entity;
    s32 i;

    g_Dop.unk6A = DOPPLEGANGER.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180424);
        if (PLAYER.posX.i.hi > 0x80) {
            DOPPLEGANGER.posX.i.hi = 0x10;
        } else {
            DOPPLEGANGER.posX.i.hi = 0xF0;
        }
        func_us_801C096C();
        entity = &g_Entities[68];
        for (i = 68; i < 144; i++, entity++) {
            DestroyEntity(entity);
        }
        g_Dop.unk6C = DOPPLEGANGER.hitPoints;
        g_Dop.unk6A = DOPPLEGANGER.hitPoints;
        g_Dop.unk6E = DOPPLEGANGER.hitPoints;
        g_Dop.unk70 = DOPPLEGANGER.hitboxState;
        if (PLAYER.posX.i.hi > 0x80) {
            func_us_801C1DB0(0x12);
        } else {
            func_us_801C1DB0(0x14);
        }
        func_us_801C4954(1, 0x30);
    } else {
        func_us_801C1DC8();
        EntityDoppleganger40();
        func_us_801C9624();
    }
    g_Dop.unk6C = g_Dop.unk6A;
}

#include "../dop_collision.h"
