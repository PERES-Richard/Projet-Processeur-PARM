.data
    A: .word 0xf
    B: .word 0xff
.end

.text
    LSLS R7, R7, 31
    LSRS R7, R7, 31
    ASRS R7, R7, 31
    ADDS R7, R7, R7
    SUBS R7, R7, R7  
    ADDS R7, R7, 7
    SUBS R7, R7, 7
    MOVS R7, 255
    ANDS R7, R7
    EORS R7, R7
    LSLS R7, R7
    LSRS R7, R7
    ASRS R7, R7
    ADCS R7, R7
    SBCS R7, R7
    RORS R7, R7
    TST R7, R7
    RSBS R7, R7, 0
    CMP R7, R7
    CMN R7, R7
    ORRS R7, R7
    MULS R7, R7, R7
    BICS R7, R7
    MVNS R7, R7

    STR R7, 255
    LDR R7, 255
    ADD 127
    SUB 127
.end