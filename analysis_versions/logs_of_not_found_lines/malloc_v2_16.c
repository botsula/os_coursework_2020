Comparison of files: malloc_v2_16.c and malloc_v2_14.c
line 1 is a new one:    Copyright (C) 1996-2009, 2010, 2011, 2012 Free Software Foundation, Inc.
line 17 is a new one:    License along with the GNU C Library; see the file COPYING.LIB.  If
line 18 is a new one:    not, see <http://www.gnu.org/licenses/>.  */
line 75 is a new one:     free(void* p);
line 76 is a new one:     realloc(void* p, size_t n);
line 83 is a new one:     independent_calloc(size_t n_elements, size_t size, void* chunks[]);
line 84 is a new one:     independent_comalloc(size_t n_elements, size_t sizes[], void* chunks[]);
line 86 is a new one:     cfree(void* p);
line 88 is a new one:     malloc_usable_size(void* p);
line 146 is a new one:   Thread-safety: thread-safe
line 155 is a new one:     below. It has been tested most extensively on Solaris and Linux.
line 207 is a new one:   void* is the pointer type that malloc should say it returns
line 210 is a new one: #ifndef void
line 211 is a new one: #define void      void
line 212 is a new one: #endif /*void*/
line 220 is a new one: #include <_itoa.h>
line 224 is a new one: #include <ldsodefs.h>
line 228 is a new one: #include <errno.h>
line 230 is a new one: #include <shlib-compat.h>
line 341 is a new one: # if !SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_16)
line 342 is a new one: /* This is the correct definition when there is no past ABI to constrain it.
line 344 is a new one:    Among configurations with a past ABI constraint, it differs from
line 345 is a new one:    2*SIZE_SZ only on powerpc32.  For the time being, changing this is
line 346 is a new one:    causing more compatibility problems due to malloc_get_state and
line 347 is a new one:    malloc_set_state than will returning blocks not adequately aligned for
line 348 is a new one:    long double objects under -mlong-double-128.  */
line 350 is a new one: #  define MALLOC_ALIGNMENT       (2 * SIZE_SZ < __alignof__ (long double) \
line 351 is a new one: 				  ? __alignof__ (long double) : 2 * SIZE_SZ)
line 353 is a new one: #  define MALLOC_ALIGNMENT       (2 * SIZE_SZ)
line 394 is a new one: /* Definition for getting more memory from the OS.  */
line 397 is a new one: void * __default_morecore (ptrdiff_t);
line 398 is a new one: void *(*__morecore)(ptrdiff_t) = __default_morecore;
line 401 is a new one: #include <string.h>
line 476 is a new one:    sbrk fails, and mmap is used as a backup.  The value must be a
line 477 is a new one:    multiple of page size.  This backup strategy generally applies only
line 478 is a new one:    when systems have "holes" in address space, so sbrk cannot perform
line 479 is a new one:    contiguous expansion, but there is still space available on system.
line 480 is a new one:    On systems for which this is known to be useful (i.e. most linux
line 481 is a new one:    kernels), this occurs only when programs allocate huge amounts of
line 482 is a new one:    memory.  Between this, and the fact that mmap regions tend to be
line 483 is a new one:    limited, the size should be large, to avoid too many mmap calls and
line 484 is a new one:    thus avoid running out of kernel resources.  */
line 539 is a new one: void*  __libc_malloc(size_t);
line 540 is a new one: libc_hidden_proto (__libc_malloc)
line 543 is a new one:   free(void* p)
line 553 is a new one: void     __libc_free(void*);
line 554 is a new one: libc_hidden_proto (__libc_free)
line 561 is a new one: void*  __libc_calloc(size_t, size_t);
line 564 is a new one:   realloc(void* p, size_t n)
line 590 is a new one: void*  __libc_realloc(void*, size_t);
line 591 is a new one: libc_hidden_proto (__libc_realloc)
line 605 is a new one: void*  __libc_memalign(size_t, size_t);
line 606 is a new one: libc_hidden_proto (__libc_memalign)
line 613 is a new one: void*  __libc_valloc(size_t);
line 638 is a new one: int      __libc_mallopt(int, int);
line 639 is a new one: libc_hidden_proto (__libc_mallopt)
line 665 is a new one: struct mallinfo __libc_mallinfo(void);
line 673 is a new one: void*  __libc_pvalloc(size_t);
line 699 is a new one: int      __malloc_trim(size_t);
line 702 is a new one:   malloc_usable_size(void* p);
line 716 is a new one: size_t   __malloc_usable_size(void*);
line 738 is a new one: void     __malloc_stats(void);
line 746 is a new one: void*  __malloc_get_state(void);
line 749 is a new one:   malloc_set_state(void* state);
line 754 is a new one: int      __malloc_set_state(void*);
line 1027 is a new one:   Setting to 0 disables use of mmap for servicing large requests.
line 1055 is a new one: static void*  _int_malloc(mstate, size_t);
line 1057 is a new one: static void*  _int_realloc(mstate, mchunkptr, INTERNAL_SIZE_T,
line 1058 is a new one: 			   INTERNAL_SIZE_T);
line 1059 is a new one: static void*  _int_memalign(mstate, size_t, size_t);
line 1060 is a new one: static void*  _int_valloc(mstate, size_t);
line 1061 is a new one: static void*  _int_pvalloc(mstate, size_t);
line 1064 is a new one: static void* internal_function mem2mem_check(void *p, size_t sz);
line 1071 is a new one: static void*   malloc_check(size_t sz, const void *caller);
line 1072 is a new one: static void      free_check(void* mem, const void *caller);
line 1073 is a new one: static void*   realloc_check(void* oldmem, size_t bytes,
line 1074 is a new one: 			       const void *caller);
line 1075 is a new one: static void*   memalign_check(size_t alignment, size_t bytes,
line 1076 is a new one: 				const void *caller);
line 1077 is a new one: /* These routines are never needed in this configuration.  */
line 1078 is a new one: static void*   malloc_atfork(size_t sz, const void *caller);
line 1079 is a new one: static void      free_atfork(void* mem, const void *caller);
line 1105 is a new one: # define MAP_NORESERVE 0
line 1109 is a new one:  __mmap((addr), (size), (prot), (flags)|MAP_ANONYMOUS|MAP_PRIVATE, -1, 0)
line 1230 is a new one: #define chunk2mem(p)   ((void*)((char*)(p) + 2*SIZE_SZ))
line 1271 is a new one:     __set_errno (ENOMEM);					  \
line 1367 is a new one:    * If mmap doesn't support MAP_ANONYMOUS, a dummy file descriptor
line 1368 is a new one:      for mmap.
line 1475 is a new one:     Bin 0 does not exist.  Bin 1 is the unordered list; if that would be
line 1476 is a new one:     a valid chunk size the small bins are bumped up one.
line 1482 is a new one: #define SMALLBIN_CORRECTION (MALLOC_ALIGNMENT > 2 * SIZE_SZ)
line 1483 is a new one: #define MIN_LARGE_SIZE    ((NSMALLBINS - SMALLBIN_CORRECTION) * SMALLBIN_WIDTH)
line 1489 is a new one:   ((SMALLBIN_WIDTH == 16 ? (((unsigned)(sz)) >> 4) : (((unsigned)(sz)) >> 3)) \
line 1490 is a new one:    + SMALLBIN_CORRECTION)
line 1500 is a new one: #define largebin_index_32_big(sz)                                            \
line 1501 is a new one: (((((unsigned long)(sz)) >>  6) <= 45)?  49 + (((unsigned long)(sz)) >>  6): \
line 1506 is a new one:                                         126)
line 1520 is a new one:   (SIZE_SZ == 8 ? largebin_index_64 (sz)                                     \
line 1521 is a new one:    : MALLOC_ALIGNMENT == 16 ? largebin_index_32_big (sz)                     \
line 1522 is a new one:    : largebin_index_32 (sz))
line 1559 is a new one:     sysmalloc. (This is somewhat delicate, since it relies on
line 1762 is a new one: static struct malloc_state main_arena =
line 1764 is a new one:     .mutex = MUTEX_INITIALIZER,
line 1765 is a new one:     .next = &main_arena
line 1766 is a new one:   };
line 1770 is a new one: static struct malloc_par mp_ =
line 1772 is a new one:     .top_pad        = DEFAULT_TOP_PAD,
line 1773 is a new one:     .n_mmaps_max    = DEFAULT_MMAP_MAX,
line 1774 is a new one:     .mmap_threshold = DEFAULT_MMAP_THRESHOLD,
line 1775 is a new one:     .trim_threshold = DEFAULT_TRIM_THRESHOLD,
line 1777 is a new one: # define NARENAS_FROM_NCORES(n) ((n) * (sizeof(long) == 4 ? 2 : 8))
line 1778 is a new one:     .arena_test     = NARENAS_FROM_NCORES (1)
line 1780 is a new one:   };
line 1829 is a new one: static void*  sysmalloc(INTERNAL_SIZE_T, mstate);
line 1830 is a new one: static int      systrim(size_t, mstate);
line 1841 is a new one: # define weak_variable weak_function
line 1845 is a new one: static void* malloc_hook_ini __MALLOC_P ((size_t sz,
line 1847 is a new one: static void* realloc_hook_ini __MALLOC_P ((void* ptr, size_t sz,
line 1849 is a new one: static void* memalign_hook_ini __MALLOC_P ((size_t alignment, size_t sz,
line 1948 is a new one:     assert(((p->prev_size + sz) & (GLRO(dl_pagesize)-1)) == 0);
line 2109 is a new one:   assert((GLRO(dl_pagesize) & (GLRO(dl_pagesize)-1)) == 0);
line 2245 is a new one: static void* sysmalloc(INTERNAL_SIZE_T nb, mstate av)
line 2267 is a new one:   size_t          pagemask  = GLRO(dl_pagesize) - 1;
line 2289 is a new one:       See the front_misalign handling below, for glibc there is no
line 2290 is a new one:       need for further alignments unless we have have high alignment.
line 2292 is a new one:     if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2293 is a new one:       size = (nb + SIZE_SZ + pagemask) & ~pagemask;
line 2295 is a new one:       size = (nb + SIZE_SZ + MALLOC_ALIGN_MASK + pagemask) & ~pagemask;
line 2301 is a new one:       mm = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, 0));
line 2313 is a new one: 	if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2315 is a new one: 	    /* For glibc, chunk2mem increases the address by 2*SIZE_SZ and
line 2316 is a new one: 	       MALLOC_ALIGN_MASK is 2*SIZE_SZ-1.  Each mmap'ed area is page
line 2317 is a new one: 	       aligned and therefore definitely MALLOC_ALIGN_MASK-aligned.  */
line 2318 is a new one: 	    assert (((INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK) == 0);
line 2319 is a new one: 	    front_misalign = 0;
line 2322 is a new one: 	  front_misalign = (INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK;
line 2398 is a new one:       /* Setup fencepost and free the old top chunk with a multiple of
line 2399 is a new one: 	 MALLOC_ALIGNMENT in size. */
line 2403 is a new one:       old_size = (old_size - MINSIZE) & ~MALLOC_ALIGN_MASK;
line 2480 is a new one:       char *mbrk = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, 0));
line 2602 is a new one: 	if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2603 is a new one: 	  /* MORECORE/mmap must correctly align */
line 2604 is a new one: 	  assert(((unsigned long)chunk2mem(brk) & MALLOC_ALIGN_MASK) == 0);
line 2606 is a new one: 	  front_misalign = (INTERNAL_SIZE_T)chunk2mem(brk) & MALLOC_ALIGN_MASK;
line 2607 is a new one: 	  if (front_misalign > 0) {
line 2609 is a new one: 	    /*
line 2610 is a new one: 	      Skip over some bytes to arrive at an aligned position.
line 2611 is a new one: 	      We don't need to specially mark these wasted front bytes.
line 2612 is a new one: 	      They will never be accessed anyway because
line 2613 is a new one: 	      prev_inuse of av->top (and any chunk created from its start)
line 2614 is a new one: 	      is always true after initialization.
line 2615 is a new one: 	    */
line 2617 is a new one: 	    aligned_brk += MALLOC_ALIGNMENT - front_misalign;
line 2695 is a new one:   __set_errno (ENOMEM);
line 2701 is a new one:   systrim is an inverse of sorts to sysmalloc.  It gives memory back
line 2709 is a new one: static int systrim(size_t pad, mstate av)
line 2718 is a new one:   pagesz = GLRO(dl_pagesize);
line 2781 is a new one:   if (__builtin_expect (((block | total_size) & (GLRO(dl_pagesize) - 1)) != 0, 0))
line 2791 is a new one:   /* If munmap failed the process virtual memory address space is in a
line 2792 is a new one:      bad shape.  Just leave the block hanging around, the process will
line 2793 is a new one:      terminate shortly anyway since not much can be done.  */
line 2794 is a new one:   __munmap((char *)block, total_size);
line 2803 is a new one:   size_t page_mask = GLRO(dl_pagesize) - 1;
line 2809 is a new one:   assert(((size + offset) & (GLRO(dl_pagesize)-1)) == 0);
line 2818 is a new one:   cp = (char *)__mremap((char *)p - offset, size + offset, new_size,
line 2819 is a new one: 			MREMAP_MAYMOVE);
line 2841 is a new one: void*
line 2842 is a new one: __libc_malloc(size_t bytes)
line 2845 is a new one:   void *victim;
line 2847 is a new one:   __malloc_ptr_t (*hook) (size_t, const __malloc_ptr_t)
line 2881 is a new one: libc_hidden_def(__libc_malloc)
line 2884 is a new one: __libc_free(void* mem)
line 2889 is a new one:   void (*hook) (__malloc_ptr_t, const __malloc_ptr_t)
line 2918 is a new one: libc_hidden_def (__libc_free)
line 2920 is a new one: void*
line 2921 is a new one: __libc_realloc(void* oldmem, size_t bytes)
line 2926 is a new one:   void* newp;             /* chunk to return */
line 2928 is a new one:   __malloc_ptr_t (*hook) (__malloc_ptr_t, size_t, const __malloc_ptr_t) =
line 2934 is a new one:   if (bytes == 0 && oldmem != NULL) { __libc_free(oldmem); return 0; }
line 2938 is a new one:   if (oldmem == 0) return __libc_malloc(bytes);
line 2960 is a new one:     void* newmem;
line 2969 is a new one:     newmem = __libc_malloc(bytes);
line 2988 is a new one: #if !defined PER_THREAD
line 2990 is a new one:   tsd_setspecific(arena_key, (void *)ar_ptr);
line 3002 is a new one:       newp = __libc_malloc(bytes);
line 3012 is a new one: libc_hidden_def (__libc_realloc)
line 3014 is a new one: void*
line 3015 is a new one: __libc_memalign(size_t alignment, size_t bytes)
line 3018 is a new one:   void *p;
line 3021 is a new one: 					const __malloc_ptr_t)) =
line 3027 is a new one:   if (alignment <= MALLOC_ALIGNMENT) return __libc_malloc(bytes);
line 3060 is a new one: /* For ISO C11.  */
line 3061 is a new one: weak_alias (__libc_memalign, aligned_alloc)
line 3062 is a new one: libc_hidden_def (__libc_memalign)
line 3064 is a new one: void*
line 3065 is a new one: __libc_valloc(size_t bytes)
line 3068 is a new one:   void *p;
line 3073 is a new one:   size_t pagesz = GLRO(dl_pagesize);
line 3076 is a new one: 					const __malloc_ptr_t)) =
line 3108 is a new one: void*
line 3109 is a new one: __libc_pvalloc(size_t bytes)
line 3112 is a new one:   void *p;
line 3117 is a new one:   size_t pagesz = GLRO(dl_pagesize);
line 3118 is a new one:   size_t page_mask = GLRO(dl_pagesize) - 1;
line 3122 is a new one: 					const __malloc_ptr_t)) =
line 3153 is a new one: void*
line 3154 is a new one: __libc_calloc(size_t n, size_t elem_size)
line 3159 is a new one:   void* mem;
line 3170 is a new one:       __set_errno (ENOMEM);
line 3175 is a new one:   __malloc_ptr_t (*hook) __MALLOC_PMT ((size_t, const __malloc_ptr_t)) =
line 3290 is a new one: static void*
line 3769 is a new one:       void *p = sysmalloc(nb, av);
line 3812 is a new one:   /* We know that each chunk is at least MINSIZE bytes in size or a
line 3813 is a new one:      multiple of MALLOC_ALIGNMENT.  */
line 3814 is a new one:   if (__builtin_expect (size < MINSIZE || !aligned_OK (size), 0))
line 4030 is a new one: 	  systrim(mp_.top_pad, av);
line 4048 is a new one:     If the chunk was allocated via mmap, release via munmap().
line 4172 is a new one: void*
line 4178 is a new one:   void*          newmem;          /* corresponding user mem */
line 4210 is a new one:   next = chunk_at_offset(oldp, oldsize);
line 4211 is a new one:   INTERNAL_SIZE_T nextsize = chunksize(next);
line 4212 is a new one:   if (__builtin_expect (next->size <= 2 * SIZE_SZ, 0)
line 4213 is a new one:       || __builtin_expect (nextsize >= av->system_mem, 0))
line 4215 is a new one:       errstr = "realloc(): invalid next size";
line 4219 is a new one:   if ((unsigned long)(oldsize) >= (unsigned long)(nb)) {
line 4220 is a new one:     /* already big enough; split below */
line 4221 is a new one:     newp = oldp;
line 4222 is a new one:     newsize = oldsize;
line 4226 is a new one:     /* Try to expand forward into top */
line 4227 is a new one:     if (next == av->top &&
line 4228 is a new one: 	(unsigned long)(newsize = oldsize + nextsize) >=
line 4229 is a new one: 	(unsigned long)(nb + MINSIZE)) {
line 4230 is a new one:       set_head_size(oldp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4231 is a new one:       av->top = chunk_at_offset(oldp, nb);
line 4232 is a new one:       set_head(av->top, (newsize - nb) | PREV_INUSE);
line 4233 is a new one:       check_inuse_chunk(av, oldp);
line 4237 is a new one:     /* Try to expand forward into next chunk;  split off remainder below */
line 4238 is a new one:     else if (next != av->top &&
line 4239 is a new one: 	     !inuse(next) &&
line 4240 is a new one: 	     (unsigned long)(newsize = oldsize + nextsize) >=
line 4241 is a new one: 	     (unsigned long)(nb)) {
line 4243 is a new one:       unlink(next, bck, fwd);
line 4246 is a new one:     /* allocate, copy, free */
line 4249 is a new one:       if (newmem == 0)
line 4250 is a new one: 	return 0; /* propagate failure */
line 4252 is a new one:       newp = mem2chunk(newmem);
line 4253 is a new one:       newsize = chunksize(newp);
line 4256 is a new one: 	Avoid copy if newp is next chunk after oldp.
line 4258 is a new one:       if (newp == next) {
line 4259 is a new one: 	newsize += oldsize;
line 4264 is a new one: 	  Unroll copy of <= 36 bytes (72 if 8byte sizes)
line 4265 is a new one: 	  We know that contents have an odd number of
line 4266 is a new one: 	  INTERNAL_SIZE_T-sized words; minimally 3.
line 4269 is a new one: 	copysize = oldsize - SIZE_SZ;
line 4270 is a new one: 	s = (INTERNAL_SIZE_T*)(chunk2mem(oldp));
line 4271 is a new one: 	d = (INTERNAL_SIZE_T*)(newmem);
line 4272 is a new one: 	ncopies = copysize / sizeof(INTERNAL_SIZE_T);
line 4273 is a new one: 	assert(ncopies >= 3);
line 4275 is a new one: 	if (ncopies > 9)
line 4276 is a new one: 	  MALLOC_COPY(d, s, copysize);
line 4279 is a new one: 	  *(d+0) = *(s+0);
line 4280 is a new one: 	  *(d+1) = *(s+1);
line 4281 is a new one: 	  *(d+2) = *(s+2);
line 4282 is a new one: 	  if (ncopies > 4) {
line 4283 is a new one: 	    *(d+3) = *(s+3);
line 4284 is a new one: 	    *(d+4) = *(s+4);
line 4285 is a new one: 	    if (ncopies > 6) {
line 4286 is a new one: 	      *(d+5) = *(s+5);
line 4287 is a new one: 	      *(d+6) = *(s+6);
line 4288 is a new one: 	      if (ncopies > 8) {
line 4289 is a new one: 		*(d+7) = *(s+7);
line 4290 is a new one: 		*(d+8) = *(s+8);
line 4297 is a new one: 	check_inuse_chunk(av, newp);
line 4298 is a new one: 	return chunk2mem(newp);
line 4303 is a new one:   /* If possible, free extra space in old or extended chunk */
line 4305 is a new one:   assert((unsigned long)(newsize) >= (unsigned long)(nb));
line 4307 is a new one:   remainder_size = newsize - nb;
line 4309 is a new one:   if (remainder_size < MINSIZE) { /* not enough extra to split off */
line 4310 is a new one:     set_head_size(newp, newsize | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4313 is a new one:   else { /* split remainder */
line 4314 is a new one:     remainder = chunk_at_offset(newp, nb);
line 4315 is a new one:     set_head_size(newp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4316 is a new one:     set_head(remainder, remainder_size | PREV_INUSE |
line 4318 is a new one:     /* Mark remainder as inuse so free() won't complain */
line 4319 is a new one:     set_inuse_bit_at_offset(remainder, remainder_size);
line 4320 is a new one:     _int_free(av, remainder, 1);
line 4323 is a new one:   check_inuse_chunk(av, newp);
line 4324 is a new one:   return chunk2mem(newp);
line 4331 is a new one: static void*
line 4436 is a new one: static void*
line 4441 is a new one:   return _int_memalign(av, GLRO(dl_pagesize), bytes);
line 4449 is a new one: static void*
line 4456 is a new one:   pagesz = GLRO(dl_pagesize);
line 4465 is a new one: static int mtrim(mstate av, size_t pad)
line 4470 is a new one:   const size_t ps = GLRO(dl_pagesize);
line 4513 is a new one:   return result | (av == &main_arena ? systrim (pad, av) : 0);
line 4521 is a new one: __malloc_trim(size_t s)
line 4532 is a new one:       result |= mtrim (ar_ptr, s);
line 4547 is a new one: static size_t
line 4548 is a new one: musable(void* mem)
line 4563 is a new one: __malloc_usable_size(void* m)
line 4567 is a new one:   result = musable(m);
line 4573 is a new one:   Accumulate malloc statistics for arena AV into M.
line 4577 is a new one: int_mallinfo(mstate av, struct mallinfo *m)
line 4618 is a new one:   m->smblks += nfastblocks;
line 4619 is a new one:   m->ordblks += nblocks;
line 4620 is a new one:   m->fordblks += avail;
line 4621 is a new one:   m->uordblks += av->system_mem - avail;
line 4622 is a new one:   m->arena += av->system_mem;
line 4623 is a new one:   m->fsmblks += fastavail;
line 4626 is a new one:       m->hblks = mp_.n_mmaps;
line 4627 is a new one:       m->hblkhd = mp_.mmapped_mem;
line 4628 is a new one:       m->usmblks = mp_.max_total_mem;
line 4629 is a new one:       m->keepcost = chunksize(av->top);
line 4634 is a new one: struct mallinfo __libc_mallinfo()
line 4642 is a new one:   memset(&m, 0, sizeof (m));
line 4643 is a new one:   ar_ptr = &main_arena;
line 4644 is a new one:   do {
line 4646 is a new one:     int_mallinfo(ar_ptr, &m);
line 4650 is a new one:   } while (ar_ptr != &main_arena);
line 4660 is a new one: __malloc_stats()
line 4675 is a new one:     struct mallinfo mi;
line 4677 is a new one:     memset(&mi, 0, sizeof(mi));
line 4679 is a new one:     int_mallinfo(ar_ptr, &mi);
line 4721 is a new one: int __libc_mallopt(int param_number, int value)
line 4788 is a new one: libc_hidden_def (__libc_mallopt)
line 4851 is a new one:   request, then mmap is used as a noncontiguous system allocator. This
line 4852 is a new one:   is a useful backup strategy for systems with holes in address spaces
line 4853 is a new one:   -- in this case sbrk cannot contiguously expand the heap, but mmap
line 4854 is a new one:   may be able to map noncontiguous space.
line 4956 is a new one: #include <sys/param.h>
line 4974 is a new one: 					const __malloc_ptr_t)) =
line 4979 is a new one:     mem = __libc_memalign (alignment, size);
