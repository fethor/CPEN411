/* sim-safe.c - sample functional simulator implementation */

/* SimpleScalar(TM) Tool Suite
 * Copyright (C) 1994-2003 by Todd M. Austin, Ph.D. and SimpleScalar, LLC.
 * All Rights Reserved. 
 * 
 * THIS IS A LEGAL DOCUMENT, BY USING SIMPLESCALAR,
 * YOU ARE AGREEING TO THESE TERMS AND CONDITIONS.
 * 
 * No portion of this work may be used by any commercial entity, or for any
 * commercial purpose, without the prior, written permission of SimpleScalar,
 * LLC (info@simplescalar.com). Nonprofit and noncommercial use is permitted
 * as described below.
 * 
 * 1. SimpleScalar is provided AS IS, with no warranty of any kind, express
 * or implied. The user of the program accepts full responsibility for the
 * application of the program and the use of any results.
 * 
 * 2. Nonprofit and noncommercial use is encouraged. SimpleScalar may be
 * downloaded, compiled, executed, copied, and modified solely for nonprofit,
 * educational, noncommercial research, and noncommercial scholarship
 * purposes provided that this notice in its entirety accompanies all copies.
 * Copies of the modified software can be delivered to persons who use it
 * solely for nonprofit, educational, noncommercial research, and
 * noncommercial scholarship purposes provided that this notice in its
 * entirety accompanies all copies.
 * 
 * 3. ALL COMMERCIAL USE, AND ALL USE BY FOR PROFIT ENTITIES, IS EXPRESSLY
 * PROHIBITED WITHOUT A LICENSE FROM SIMPLESCALAR, LLC (info@simplescalar.com).
 * 
 * 4. No nonprofit user may place any restrictions on the use of this software,
 * including as modified by the user, by any other authorized user.
 * 
 * 5. Noncommercial and nonprofit users may distribute copies of SimpleScalar
 * in compiled or executable form as set forth in Section 2, provided that
 * either: (A) it is accompanied by the corresponding machine-readable source
 * code, or (B) it is accompanied by a written offer, with no time limit, to
 * give anyone a machine-readable copy of the corresponding source code in
 * return for reimbursement of the cost of distribution. This written offer
 * must permit verbatim duplication by anyone, or (C) it is distributed by
 * someone who received only the executable form, and is accompanied by a
 * copy of the written offer of source code.
 * 
 * 6. SimpleScalar was developed by Todd M. Austin, Ph.D. The tool suite is
 * currently maintained by SimpleScalar LLC (info@simplescalar.com). US Mail:
 * 2395 Timbercrest Court, Ann Arbor, MI 48105.
 * 
 * Copyright (C) 1994-2003 by Todd M. Austin, Ph.D. and SimpleScalar, LLC.
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "host.h"
#include "misc.h"
#include "machine.h"
#include "regs.h"
#include "memory.h"
#include "loader.h"
#include "syscall.h"
#include "options.h"
#include "stats.h"
#include "sim.h"
#include "math.h"

//my code
static counter_t g_icache_miss;
static counter_t g_iicache_miss;
static counter_t g_bcache_miss_load;
static counter_t g_bcache_miss_store;
static counter_t g_bnum_stores;
static counter_t g_bnum_loads;
static counter_t g_bnum_wbevents;

/*
 * This file implements a functional simulator.  This functional simulator is
 * the simplest, most user-friendly simulator in the simplescalar tool set.
 * Unlike sim-fast, this functional simulator checks for all instruction
 * errors, and the implementation is crafted for clarity rather than speed.
 */

/* simulated registers */
static struct regs_t regs;

/* simulated memory */
static struct mem_t *mem = NULL;

/* track number of refs */
static counter_t sim_num_refs = 0;

/* maximum number of inst's to execute */
static unsigned int max_insts;

/* register simulator-specific options */
void
sim_reg_options(struct opt_odb_t *odb)
{
  opt_reg_header(odb, 
"sim-safe: This simulator implements a functional simulator.  This\n"
"functional simulator is the simplest, most user-friendly simulator in the\n"
"simplescalar tool set.  Unlike sim-fast, this functional simulator checks\n"
"for all instruction errors, and the implementation is crafted for clarity\n"
"rather than speed.\n"
		 );

  /* instruction limit */
  opt_reg_uint(odb, "-max:inst", "maximum number of inst's to execute",
	       &max_insts, /* default */0,
	       /* print */TRUE, /* format */NULL);

}

/* check simulator-specific option values */
void
sim_check_options(struct opt_odb_t *odb, int argc, char **argv)
{
  /* nada */
}

/* register simulator-specific statistics */
void
sim_reg_stats(struct stat_sdb_t *sdb)
{
  stat_reg_counter(sdb, "sim_num_insn",
		   "total number of instructions executed",
		   &sim_num_insn, sim_num_insn, NULL);
  stat_reg_counter(sdb, "sim_num_refs",
		   "total number of loads and stores executed",
		   &sim_num_refs, 0, NULL);
  stat_reg_int(sdb, "sim_elapsed_time",
	       "total simulation time in seconds",
	       &sim_elapsed_time, 0, NULL);
  stat_reg_formula(sdb, "sim_inst_rate",
		   "simulation speed (in insts/sec)",
		   "sim_num_insn / sim_elapsed_time", NULL);
  ld_reg_stats(sdb);
  mem_reg_stats(mem, sdb);

  //my code
stat_reg_counter(sdb, "sim_num_icache_miss",
  "total number of instruction icache misses",
  &g_icache_miss, 0, NULL);
stat_reg_formula(sdb, "sim_icache_miss_rate",
  "instruction icache miss rate (percentage)",
  "100*(sim_num_icache_miss / sim_num_insn)", NULL);

stat_reg_counter(sdb, "sim_num_iicache_miss",
  "total number of instruction iicache misses",
  &g_iicache_miss, 0, NULL);
stat_reg_formula(sdb, "sim_iicache_miss_rate",
  "instruction iicache miss rate (percentage)",
  "100*(sim_num_iicache_miss / sim_num_insn)", NULL);

  // part b)
stat_reg_counter(sdb, "sim_num_bcache_miss_load",
  "total number of instruction bcache load misses",
  &g_bcache_miss_load, 0, NULL);
stat_reg_counter(sdb, "g_bnum_loads",
  "total number of instruction bcache load",
  &g_bnum_loads, 0, NULL);

  stat_reg_counter(sdb, "sim_num_bcache_miss_store",
  "total number of instruction bcache store misses",
  &g_bcache_miss_store, 0, NULL);
  stat_reg_counter(sdb, "g_bnum_stores",
  "total number of instruction bcache stores",
  &g_bnum_stores, 0, NULL);

stat_reg_formula(sdb, "sim_bcache_load_miss_rate",
  "instruction bcache load miss rate (percentage)",
  "100*(sim_num_bcache_miss_load / g_bnum_loads)", NULL);


stat_reg_formula(sdb, "sim_bcache_store_miss_rate",
  "instruction bcache store miss rate (percentage)",
  "100*(sim_num_bcache_miss_store / g_bnum_stores)", NULL);

stat_reg_counter(sdb, "sim_bnum_wb_events",
  "total number of instruction bcache writeback events",
  &g_bnum_wbevents, 0, NULL);
stat_reg_formula(sdb, "sim_bnum_wb_rate",
  "instruction wb eviction rate (percentage)",
  "100*(sim_bnum_wb_events / g_bnum_stores)", NULL);

}

/* initialize the simulator */
void
sim_init(void)
{
  sim_num_refs = 0;

  /* allocate and initialize register file */
  regs_init(&regs);

  /* allocate and initialize memory space */
  mem = mem_create("mem");
  mem_init(mem);
}

/* load program into simulated state */
void
sim_load_prog(char *fname,		/* program to load */
	      int argc, char **argv,	/* program arguments */
	      char **envp)		/* program environment */
{
  /* load program text and data, set up environment, memory, and regs */
  ld_load_prog(fname, argc, argv, envp, &regs, mem, TRUE);
}

/* print simulator-specific configuration information */
void
sim_aux_config(FILE *stream)		/* output stream */
{
  /* nothing currently */
}

/* dump simulator-specific auxiliary simulator statistics */
void
sim_aux_stats(FILE *stream)		/* output stream */
{
  /* nada */
}

/* un-initialize simulator-specific state */
void
sim_uninit(void)
{
  /* nada */
}


/*
 * configure the execution engine
 */

/*
 * precise architected register accessors
 */

/* next program counter */
#define SET_NPC(EXPR)		(regs.regs_NPC = (EXPR))

/* current program counter */
#define CPC			(regs.regs_PC)

/* general purpose registers */
#define GPR(N)			(regs.regs_R[N])
#define SET_GPR(N,EXPR)		(regs.regs_R[N] = (EXPR))

#if defined(TARGET_PISA)

/* floating point registers, L->word, F->single-prec, D->double-prec */
#define FPR_L(N)		(regs.regs_F.l[(N)])
#define SET_FPR_L(N,EXPR)	(regs.regs_F.l[(N)] = (EXPR))
#define FPR_F(N)		(regs.regs_F.f[(N)])
#define SET_FPR_F(N,EXPR)	(regs.regs_F.f[(N)] = (EXPR))
#define FPR_D(N)		(regs.regs_F.d[(N) >> 1])
#define SET_FPR_D(N,EXPR)	(regs.regs_F.d[(N) >> 1] = (EXPR))

/* miscellaneous register accessors */
#define SET_HI(EXPR)		(regs.regs_C.hi = (EXPR))
#define HI			(regs.regs_C.hi)
#define SET_LO(EXPR)		(regs.regs_C.lo = (EXPR))
#define LO			(regs.regs_C.lo)
#define FCC			(regs.regs_C.fcc)
#define SET_FCC(EXPR)		(regs.regs_C.fcc = (EXPR))

#elif defined(TARGET_ALPHA)

/* floating point registers, L->word, F->single-prec, D->double-prec */
#define FPR_Q(N)		(regs.regs_F.q[N])
#define SET_FPR_Q(N,EXPR)	(regs.regs_F.q[N] = (EXPR))
#define FPR(N)			(regs.regs_F.d[(N)])
#define SET_FPR(N,EXPR)		(regs.regs_F.d[(N)] = (EXPR))

/* miscellaneous register accessors */
#define FPCR			(regs.regs_C.fpcr)
#define SET_FPCR(EXPR)		(regs.regs_C.fpcr = (EXPR))
#define UNIQ			(regs.regs_C.uniq)
#define SET_UNIQ(EXPR)		(regs.regs_C.uniq = (EXPR))

#else
#error No ISA target defined...
#endif

/* precise architected memory state accessor macros */
#define READ_BYTE(SRC, FAULT)						\
  ((FAULT) = md_fault_none, addr = (SRC), MEM_READ_BYTE(mem, addr))
#define READ_HALF(SRC, FAULT)						\
  ((FAULT) = md_fault_none, addr = (SRC), MEM_READ_HALF(mem, addr))
#define READ_WORD(SRC, FAULT)						\
  ((FAULT) = md_fault_none, addr = (SRC), MEM_READ_WORD(mem, addr))
#ifdef HOST_HAS_QWORD
#define READ_QWORD(SRC, FAULT)						\
  ((FAULT) = md_fault_none, addr = (SRC), MEM_READ_QWORD(mem, addr))
#endif /* HOST_HAS_QWORD */

#define WRITE_BYTE(SRC, DST, FAULT)					\
  ((FAULT) = md_fault_none, addr = (DST), MEM_WRITE_BYTE(mem, addr, (SRC)))
#define WRITE_HALF(SRC, DST, FAULT)					\
  ((FAULT) = md_fault_none, addr = (DST), MEM_WRITE_HALF(mem, addr, (SRC)))
#define WRITE_WORD(SRC, DST, FAULT)					\
  ((FAULT) = md_fault_none, addr = (DST), MEM_WRITE_WORD(mem, addr, (SRC)))
#ifdef HOST_HAS_QWORD
#define WRITE_QWORD(SRC, DST, FAULT)					\
  ((FAULT) = md_fault_none, addr = (DST), MEM_WRITE_QWORD(mem, addr, (SRC)))
#endif /* HOST_HAS_QWORD */

/* system call handler macro */
#define SYSCALL(INST)	sys_syscall(&regs, mem_access, mem, INST, TRUE)

#define DNA         (0)

/* general register dependence decoders */
#define DGPR(N)         (N)
#define DGPR_D(N)       ((N) &~1)

/* floating point register dependence decoders */
#define DFPR_L(N)       (((N)+32)&~1)
#define DFPR_F(N)       (((N)+32)&~1)
#define DFPR_D(N)       (((N)+32)&~1)

/* miscellaneous register dependence decoders */
#define DHI         (0+32+32)
#define DLO         (1+32+32)
#define DFCC            (2+32+32)
#define DTMP            (3+32+32)

struct block {
  int           m_valid; // is block valid?
  counter_t     LRU; //least recently used bit (will just be equal to the current cycle time or something like that)
  md_addr_t     m_tag;   // tag used to determine whether we have a cache hit
  int           m_modified;
  };

struct cache
  {
  unsigned      m_total_blocks;
  unsigned      m_set_shift;
  unsigned      m_set_mask;
  unsigned      m_tag_shift;
  unsigned      m_associativity; // the amount of bits required !!! BITSSS
  struct block *m_tag_array;
  };


void cache_access( struct cache *c, unsigned addr, counter_t *miss_counter )
  {
  unsigned  index, tag;
  index = (addr>>c->m_set_shift)&c->m_set_mask;
  tag = (addr>>c->m_tag_shift);
  counter_t LRU = sim_num_insn;
  int save, change =0;
  int a, i;
  int assertion = c->m_total_blocks/(pow(2,(c->m_associativity)));
  assert( index < assertion );
  
for (i =0;i < pow(2,c->m_associativity); i++){
  if((c->m_tag_array[index*(i+1)].m_valid&&(c->m_tag_array[index*(i+1)].m_tag==tag))){
    c->m_tag_array[index*(i+1)].LRU = sim_num_insn;
    break;
  }
  else if (c->m_tag_array[index*(i+1)].m_tag==tag){
    c->m_tag_array[index*(i+1)].LRU = sim_num_insn;
    save = i;
    change =1;
    break; 
  }
  if (i+1 == pow(2,c->m_associativity)){
    change =1;
    for (a =0; a < pow(2,c->m_associativity); a++){
      if (LRU==0){
        save = a;
        break;
      }
      else if (c->m_tag_array[index*(a+1)].LRU < LRU){
        LRU = c->m_tag_array[index*(a+1)].LRU;
        save = a;
      }
    }
    break;
  }
}

if(change) {
  *miss_counter = *miss_counter + 1;
  c->m_tag_array[index*(save+1)].m_valid = 1;
  c->m_tag_array[index*(save+1)].m_tag = tag;
  c->m_tag_array[index*(save+1)].LRU = sim_num_insn;
}

}


void bcache_access( struct cache *c, unsigned addr,counter_t *load_miss,counter_t *store_miss, counter_t *wb_event, enum md_opcode op)
{
unsigned  index, tag;
index = (addr>>c->m_set_shift)&c->m_set_mask;
tag = (addr>>c->m_tag_shift);
counter_t LRU = sim_num_insn;
int save =0, change =0, mod =0;
int a, i;
int assertion = c->m_total_blocks/(pow(2,(c->m_associativity)));

if (MD_OP_FLAGS(op) & F_STORE)
  mod = 1;

assert( index < assertion );

for (i =0;i < pow(2,c->m_associativity); i++){
if((c->m_tag_array[index*(i+1)].m_valid&&(c->m_tag_array[index*(i+1)].m_tag==tag))){
  c->m_tag_array[index*(i+1)].LRU = sim_num_insn;
  c->m_tag_array[index*(i+1)].m_modified = mod;
  break;
}
else if (c->m_tag_array[index*(i+1)].m_tag==tag){
  c->m_tag_array[index*(i+1)].LRU = sim_num_insn;
  c->m_tag_array[index*(i+1)].m_modified = mod;
  save = i;
  change =1;
  break; 
}
if (i+1 == pow(2,c->m_associativity)){
  change =1;
  for (a =0; a < pow(2,c->m_associativity); a++){
    if (LRU==0){
      save = a;
      break;
    }
    else if (c->m_tag_array[index*(a+1)].LRU < LRU){
      LRU = c->m_tag_array[index*(a+1)].LRU;
      save = a;
    }
  }
  break;
}
}

if(change) {
  assert (save < pow(2,c->m_associativity));
  if (c->m_tag_array[index*(save+1)].m_modified) *wb_event = *wb_event +1;
  if (mod){
    *store_miss = *store_miss + 1;
  }
  else {
    *load_miss = *load_miss +1;
  }
  c->m_tag_array[index*(save+1)].m_valid = 1;
  c->m_tag_array[index*(save+1)].m_tag = tag;
  c->m_tag_array[index*(save+1)].LRU = sim_num_insn;
  c->m_tag_array[index*(save+1)].m_modified = mod;
  }

}



/* start simulation, program loaded, processor precise state initialized */
void
sim_main(void)
{
  md_inst_t inst;
  register md_addr_t addr;
  enum md_opcode op;
  register int is_write;
  enum md_fault_type fault;

  fprintf(stderr, "sim: ** starting functional simulation **\n");

  /* set up initial default next PC */
  regs.regs_NPC = regs.regs_PC + sizeof(md_inst_t);


  //my code

  //32KB direct map with 64B data
  struct cache *icache = (struct cache *) calloc( sizeof(struct cache), 1 );
  icache->m_total_blocks = 512;
  icache->m_set_shift = 6;
  icache->m_set_mask = (1<<9)-1;
  icache->m_tag_shift = 15;
  icache->m_associativity = 0;  
  icache->m_tag_array = (struct block *) calloc( sizeof(struct block), 512 );

  //32KB 4-way with 32B blocks
  int iiblock_size_bits = log2(32); //log2(blocksize) is the size of the beginning shift to ignore bytes
  int iitotal_blocks = (32*pow(2,10))/32; //32KB / 32B = 1024 blocks
  int iiassociativity_bits = log2(4); //4-way has 2 bits which is log2(4)
  int iiindex_bits = log2(iitotal_blocks)-iiassociativity_bits; //bits of amount of blocks minus the bits for associativity for indexing
  struct cache *iicache = (struct cache *) calloc( sizeof(struct cache), 1 ); 
  iicache->m_total_blocks = iitotal_blocks;
  iicache->m_associativity = iiassociativity_bits;
  iicache->m_set_shift = iiblock_size_bits;
  iicache->m_set_mask = (1<<iiindex_bits)-1;
  iicache->m_tag_shift = iiindex_bits + iiblock_size_bits;  
  iicache->m_tag_array = (struct block *) calloc( sizeof(struct block), iitotal_blocks );
  //size of the index, block bits, everything else is for tag

  //32KB 8-way with 64B blocks
  int bblock_size_bits = log2(64); //log2(blocksize) is the size of the beginning shift to ignore bytes
  int btotal_blocks = (32*pow(2,10))/64; //
  int bassociativity_bits = log2(8); //8-way has 3 bits which is log2(8)
  int bindex_bits = log2(btotal_blocks)-bassociativity_bits; //bits of amount of blocks minus the bits for associativity for indexing
  struct cache *bcache = (struct cache *) calloc( sizeof(struct cache), 1 ); 
  bcache->m_total_blocks = btotal_blocks;
  bcache->m_associativity = bassociativity_bits;
  bcache->m_set_shift = bblock_size_bits;
  bcache->m_set_mask = (1<<bindex_bits)-1;
  bcache->m_tag_shift = bindex_bits + bblock_size_bits;  
  bcache->m_tag_array = (struct block *) calloc(btotal_blocks , sizeof(struct block));
  //size of the index, block bits, everything else is for tag
  

  while (TRUE)
    {
      /* maintain $r0 semantics */
      regs.regs_R[MD_REG_ZERO] = 0;
#ifdef TARGET_ALPHA
      regs.regs_F.d[MD_REG_ZERO] = 0.0;
#endif /* TARGET_ALPHA */

      /* get the next instruction to execute */
      //cache_access(icache, regs.regs_PC, &g_icache_miss);
      //cache_access(iicache, regs.regs_PC, &g_iicache_miss);
      
      MD_FETCH_INST(inst, mem, regs.regs_PC);

      /* keep an instruction count */
      sim_num_insn++;

      /* set default reference address and access mode */
      addr = 0; is_write = FALSE;

      /* set default fault - none */
      fault = md_fault_none;

      /* decode the instruction */
      MD_SET_OPCODE(op, inst);

      /* execute the instruction */
      switch (op)
	{
#define DEFINST(OP,MSK,NAME,OPFORM,RES,FLAGS,O1,O2,I1,I2,I3)		\
	case OP:							\
          SYMCAT(OP,_IMPL);						\
          break;
#define DEFLINK(OP,MSK,NAME,MASK,SHIFT)					\
        case OP:							\
          panic("attempted to execute a linking opcode");
#define CONNECT(OP)
#define DECLARE_FAULT(FAULT)						\
	  { fault = (FAULT); break; }
#include "machine.def"
	default:
	  panic("attempted to execute a bogus opcode");
      }

      if (fault != md_fault_none)
	fatal("fault (%d) detected @ 0x%08p", fault, regs.regs_PC);

      if (verbose)
	{
	  myfprintf(stderr, "%10n [xor: 0x%08x] @ 0x%08p: ",
		    sim_num_insn, md_xor_regs(&regs), regs.regs_PC);
	  md_print_insn(inst, regs.regs_PC, stderr);
	  if (MD_OP_FLAGS(op) & F_MEM)
	    myfprintf(stderr, "  mem: 0x%08p", addr);
	  fprintf(stderr, "\n");
	  /* fflush(stderr); */
  }
  
  if (MD_OP_FLAGS(op) & F_LOAD)
    g_bnum_loads++;
  
  if (MD_OP_FLAGS(op) & F_STORE)
    g_bnum_stores++;

  

      if (MD_OP_FLAGS(op) & F_MEM)
	{
	  sim_num_refs++;
	  if (MD_OP_FLAGS(op) & F_STORE)
	    is_write = TRUE;
  }
  bcache_access(bcache, regs.regs_PC, &g_bcache_miss_load, &g_bcache_miss_store, &g_bnum_wbevents, op);

      /* go to the next instruction */
      regs.regs_PC = regs.regs_NPC;
      regs.regs_NPC += sizeof(md_inst_t);

      /* finish early? */
      if (max_insts && sim_num_insn >= max_insts)
	return;
    }
}
