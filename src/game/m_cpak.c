#include "m_cpak.h"

#include "s_cpak.h"

mCPk_c l_paks_info;
static u8 unused[32] ATTRIBUTE_ALIGN(32); // @HACK - needed to align the TU's .bss section

mCPk_c* g_paks_info_p = { &l_paks_info };

extern int mCPk_PakOpen(mCPk_c* pak, int pak_idx) {
    return sCPk_PakOpen(&pak->save_pak);
}

extern int mCPk_InitPak(int pak_idx) {
    return 0;
}

extern int mCPk_SavePak(Private_c* private_data, Animal_c* animals, mCPk_c* cpak) {
    return 0;
}

extern mCPk_c* mCPk_get_pkinfo() {
    return g_paks_info_p;
}
