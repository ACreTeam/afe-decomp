#ifndef M_EAPPLI_H
#define M_EAPPLI_H

#include "types.h"
#include "m_actor_type.h"
#include "m_eappli_h.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mEA_InitLetterCardE();
extern int mEA_CheckLetterCardE(int card_no);
extern void mEA_SetLetterCardE(int card_no);
extern int mEA_animal_carde_info_to_save_idx(u16 info);
extern int mEA_animal_carde_info_to_paper_idx(u16 info);
extern mActor_name_t mEA_animal_carde_info_to_npc_no(u16 info);
extern mActor_name_t mEA_animal_carde_info_to_present(u16 info);
extern int mEA_animal_carde_info_to_check_special_npc(u16 info);
extern int mEA_animal_carde_info_to_letter_no(u16 info);
extern void mEA_GetCardDLProgram();
extern void mEA_CleanCardDLProgram();
extern u8* mEA_dl_carde_program_p();
extern size_t mEA_dl_carde_program_size();

#ifdef __cplusplus
}
#endif

#endif
