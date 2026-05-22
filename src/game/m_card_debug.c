#include "m_card.h"
#include "libultra/libultra.h"

static int l_mcd_err_debug[mCD_ERROR_NUM] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
static s32 l_mcd_err_result = CARD_RESULT_READY;

extern void mCD_ClearErrInfo(void) {
    bzero(l_mcd_err_debug, sizeof(l_mcd_err_debug));
    l_mcd_err_result = 0;
}

extern void mCD_OnErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = TRUE;
    }
}

extern void mCD_OffErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = FALSE;
    }
}

extern void mCD_SetErrResult(s32 result) {
    l_mcd_err_result = result;
}

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 250, 100, 250, 255);
    gfxprint_locate8x8(gfxprint, 22, 3);

    if (l_mcd_err_debug[mCD_ERROR_NOT_ENABLED]) {
        gfxprint_printf(gfxprint, "N");
    }

    if (l_mcd_err_debug[mCD_ERROR_AREA]) {
        gfxprint_printf(gfxprint, "A");
    }

    if (l_mcd_err_debug[mCD_ERROR_WRITE]) {
        gfxprint_printf(gfxprint, "W");
    }

    if (l_mcd_err_debug[mCD_ERROR_READ]) {
        gfxprint_printf(gfxprint, "R");
    }

    if (l_mcd_err_debug[mCD_ERROR_CHECKSUM]) {
        gfxprint_printf(gfxprint, "C");
    }

    if (l_mcd_err_debug[mCD_ERROR_OUTDATED]) {
        gfxprint_printf(gfxprint, "O");
    }

    if (l_mcd_err_debug[mCD_ERROR_CREATE]) {
        gfxprint_printf(gfxprint, "c");
    }

    if (l_mcd_err_result != CARD_RESULT_READY) {
        gfxprint_printf(gfxprint, "%d", l_mcd_err_result);
    }
}
