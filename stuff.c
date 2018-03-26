// the instruction type
typedef struct Inst {
    unsigned     uid;       // instruction number
    unsigned     pc;	    // instruction address
    unsigned	 next_pc;   // next instruction address
    md_inst_t    inst;      // instruction bits from memory
    enum md_opcode op;	    // opcode
    int          taken;     // if branch, is it taken?
    int          status;    // where is the instruction in the pipeline?
    struct Inst *src[3];    // src operand instructions
    int          dst[2];    // registers written by this instruction
    int          stalled;   // instruction is stalled
    unsigned     donecycle; // cycle when destination operand(s) generated
    struct Inst *next;      // used for custom memory allocation/deallocation
} inst_t;


gdb --args ../sim-scalar-cpen411 -max:inst 200000000 cc1.ss -O2 integrate.i

b sim-scalar-cpen411.c:695