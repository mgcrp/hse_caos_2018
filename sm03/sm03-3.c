int bitcount(STYPE value) {
    UTYPE mask = 0;
    // Mask value: 00..00
    mask = ~mask;
    // Mask value: 11..11
    mask >>= 1;
    // Mask value: 01..11
    mask = ~mask;
    // Mask value: 10..00
    int bit_cnt = 0;
    while (mask) {
        if (mask & (UTYPE)value) {
            ++bit_cnt;
        }
        mask >>= 1;
    }
    return bit_cnt;
}
