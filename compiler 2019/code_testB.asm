.data
    A: .word 0xf
    B: .word 0xff
    MAX: .word 0x0
.end

.text
    LDR R0,A
    LDR R1,B
  if:
    CMP R0,R1
       BMI else
    STR R0,MAX
       B endif
  else:
    STR R1,MAX
  endif:
.end