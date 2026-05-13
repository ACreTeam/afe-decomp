MEMORY
{
    text : origin = $ORIGIN
}

SECTIONS
{
    GROUP:
    {
        .init ALIGN(0x20): {}
        extab ALIGN(0x20): {}
        extabindex ALIGN(0x20): {}
        .text ALIGN(0x20): {}
        .ctors ALIGN(0x20): {}
        .dtors ALIGN(0x20): {}
        .rodata ALIGN(0x20): {}
        .data ALIGN(0x20): {}
        .bss ALIGN(0x20): {}
        .sdata ALIGN(0x20): {}
        .sbss ALIGN(0x20): {}
        .sdata2 ALIGN(0x20): {}
        .sbss2 ALIGN(0x20): {}

        .stack ALIGN(0x20):{}
    } > text
    _stack_end = ($LAST_SECTION_SYMBOL + SIZEOF($LAST_SECTION_NAME));
    _stack_addr = (_stack_end + 0x2000 + 0x7) & ~0x7;
    _db_stack_addr = (_stack_addr + 0x2000);
    _db_stack_end = _stack_addr;
    __ArenaLo = (_db_stack_addr + 0x1F) & ~0x1F;
    __ArenaHi = 0x81700000;
}

FORCEACTIVE
{
    $FORCEACTIVE
}
