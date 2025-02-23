// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

AnimationFrame g_DefaultBatAnimationFrame[] = {
    /* 801704A8 */ {4, 0x0415},
    /* 801704AC */ {1, 0x0416},
    /* 801704B0 */ {1, 0x0417},
    /* 801704B4 */ {1, 0x041E},
    /* 801704B8 */ {1, 0x0418},
    /* 801704BC */ {1, 0x0419},
    /* 801704C0 */ {4, 0x041A},
    /* 801704C4 */ {2, 0x041B},
    /* 801704C8 */ {2, 0x041C},
    /* 801704CC */ {2, 0x041D},
    /* 801704D0 */ {1, 0x041E},
    /* 801704D4 */ {2, 0x0417},
    /* 801704D8 */ {2, 0x0416},
    /* 801704DC */ {0, 0x0000},
};

AnimationFrame D_801704E0[] = {
    /* 801704E0 */ {5, 0x041F},
    /* 801704E4 */ {5, 0x0420},
    /* 801704E8 */ {5, 0x041F},
    /* 801704EC */ {5, 0x0420},
    /* 801704F0 */ {5, 0x041F},
    /* 801704F4 */ {5, 0x0420},
    /* 801704F8 */ {4, 0x041F},
    /* 801704FC */ {4, 0x0420},
    /* 80170500 */ {3, 0x041F},
    /* 80170504 */ {3, 0x0420},
    /* 80170508 */ {2, 0x041F},
    /* 8017050C */ {16, 0x0420},
    /* 80170510 */ {0, 0x0000},
};

AnimationFrame g_BatFarFromTargetAnimationFrame[] = {
    /* 80170514 */ {1, 0x0415},
    /* 80170518 */ {1, 0x0416},
    /* 8017051C */ {1, 0x0417},
    /* 80170520 */ {1, 0x041E},
    /* 80170524 */ {1, 0x0418},
    /* 80170528 */ {1, 0x0419},
    /* 8017052C */ {1, 0x041A},
    /* 80170530 */ {1, 0x041B},
    /* 80170534 */ {1, 0x041C},
    /* 80170538 */ {1, 0x041D},
    /* 8017053C */ {1, 0x041E},
    /* 80170540 */ {1, 0x0417},
    /* 80170544 */ {1, 0x0416},
    /* 80170548 */ {0, 0x0000},
};

AnimationFrame g_BatCloseToTargetAnimationFrame[] = {
    /* 8017054C */ {1, 0x0415},
    /* 80170550 */ {1, 0x0416},
    /* 80170554 */ {1, 0x0417},
    /* 80170558 */ {1, 0x041E},
    /* 8017055C */ {1, 0x0418},
    /* 80170560 */ {1, 0x0419},
    /* 80170564 */ {1, 0x041A},
    /* 80170568 */ {1, 0x041B},
    /* 8017056C */ {1, 0x041C},
    /* 80170570 */ {1, 0x041D},
    /* 80170574 */ {1, 0x041E},
    /* 80170578 */ {1, 0x0417},
    /* 8017057C */ {1, 0x0416},
    /* 80170580 */ {1, 0x0415},
    /* 80170584 */ {1, 0x0416},
    /* 80170588 */ {1, 0x0417},
    /* 8017058C */ {1, 0x041E},
    /* 80170590 */ {1, 0x0418},
    /* 80170594 */ {1, 0x0419},
    /* 80170598 */ {2, 0x041A},
    /* 8017059C */ {2, 0x041B},
    /* 801705A0 */ {2, 0x041C},
    /* 801705A4 */ {2, 0x041D},
    /* 801705A8 */ {2, 0x041E},
    /* 801705AC */ {2, 0x0417},
    /* 801705B0 */ {2, 0x0416},
    /* 801705B4 */ {2, 0x0415},
    /* 801705B8 */ {2, 0x0416},
    /* 801705BC */ {2, 0x0417},
    /* 801705C0 */ {2, 0x041E},
    /* 801705C4 */ {2, 0x0418},
    /* 801705C8 */ {2, 0x0419},
    /* 801705CC */ {3, 0x041A},
    /* 801705D0 */ {3, 0x041B},
    /* 801705D4 */ {3, 0x041C},
    /* 801705D8 */ {3, 0x041D},
    /* 801705DC */ {3, 0x041E},
    /* 801705E0 */ {3, 0x0417},
    /* 801705E4 */ {3, 0x0416},
    /* 801705E8 */ {-2, 0x0000},
};

AnimationFrame g_BatHighVelocityAnimationFrame[] = {
    /* 801705EC */ {1, 0x0415},
    /* 801705F0 */ {-1, 0x0000},
};

AnimationFrame* g_BatAnimationFrames[] = {
    /* 801705F4 */ g_DefaultBatAnimationFrame,
    /* 801705F8 */ D_801704E0,
    /* 801705FC */ g_BatFarFromTargetAnimationFrame,
    /* 80170600 */ g_BatCloseToTargetAnimationFrame,
    /* 80170604 */ g_BatHighVelocityAnimationFrame,
};
