#include "dolphin/BASE/ppcarch.h"

union FpscrUnion {
    f64 f;
    struct {
        u32 fpscr_pad;
        u32 fpscr;
    } u;
};

asm u32 PPCMfmsr(void){
    nofralloc
    mfmsr r3
    blr
}

asm void PPCMtmsr(register u32 value){
    nofralloc
    mtmsr value
    blr
}

asm u32 PPCMfhid0(void){
    nofralloc
    mfspr r3, 0x3f0
    blr
}

asm void PPCMthid0(register u32 value) {
    nofralloc
    mtspr 0x3f0, value
    blr
} 

asm u32 PPCMfl2cr(void) {
    nofralloc
    mfspr r3, 0x3f9
    blr
}

asm void PPCMtl2cr(register u32 value) {
    nofralloc
    mtspr 0x3f9, value
    blr
}
asm void PPCMtdec(register u32 value) {
    nofralloc
    mtspr 0x16, value
    blr
}

asm void PPCSync(void){
    nofralloc
    sc
    blr
}

asm void PPCHalt(void){
    nofralloc 
    sync

loop:
    nop
    li r3, 0
    nop
    b loop
}

asm void PPCMtmmcr0(register u32 newMmcr0){
    nofralloc
    mtspr 952, newMmcr0
    blr
}

asm void PPCMtmmcr1(register u32 newMmcr1){
    nofralloc
    mtspr 956, newMmcr1
    blr
}

asm void PPCMtpmc1(register u32 newPmc1){
    nofralloc
    mtspr 953, newPmc1
    blr
}

asm void PPCMtpmc2(register u32 newPmc2){
    nofralloc
    mtspr 954, newPmc2
    blr
}

asm void PPCMtpmc3(register u32 newPmc3){
    nofralloc
    mtspr 957, newPmc3
    blr
}

asm void PPCMtpmc4(register u32 newPmc4){
    nofralloc
    mtspr 958, newPmc4
    blr
}

u32 PPCMffpscr(void){
    union FpscrUnion m;

    asm {
        mffs fp31
        stfd fp31, m.f;
    }

    return m.u.fpscr;
}

void PPCMtfpscr(register u32 newFPSCR){
    union FpscrUnion m;

    asm {
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xff, fp31
    }
}
asm u32 PPCMfhid2(void){
    nofralloc
    mfspr r3, 0x398
    blr
}

asm void PPCMthid2(u32 register value){
    nofralloc
    mtspr 0x398, value
    blr
}
asm u32 PPCMfwpar(void){
    nofralloc
    sync
    mfspr r3, 0x399
    blr
}

asm void PPCMtwpar(u32 register value){
    nofralloc
    mtspr 0x399, value
    blr
}

void PPCDisableSpeculation(void) { 
    PPCMthid0(PPCMfhid0() | (1 << (31 - 22))); 
}

asm void PPCSetFpNonIEEEMode(void){
    nofralloc
    mtfsb1 0x1D
    blr
}
 