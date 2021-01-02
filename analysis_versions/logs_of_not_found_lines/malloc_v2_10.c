Comparison of files: malloc_v2_10.c and malloc_v2_8.c
line 1 is a new one:    Copyright (C) 1996-2006, 2007, 2008, 2009 Free Software Foundation, Inc.
line 25 is a new one:   There have been substantial changesmade after the integration into
line 26 is a new one:   glibc in all parts of the code.  Do not look for much commonality
line 27 is a new one:   with the ptmalloc2 version.
line 109 is a new one: 			  8-byte ptrs:  24/32 bytes (including, 4/8 overhead)
line 128 is a new one: 			   8-byte size_t: 2^64 minus about two pages
line 214 is a new one:     DEFAULT_MXFAST             64 (for 32bit), 128 (for 64bit)
line 260 is a new one: #ifdef ATOMIC_FASTBINS
line 261 is a new one: #include <atomic.h>
line 265 is a new one: #include <sys/sysinfo.h>
line 331 is a new one: #ifdef NDEBUG
line 332 is a new one: # define assert(expr) ((void) 0)
line 334 is a new one: # define assert(expr) \
line 335 is a new one:   ((expr)								      \
line 336 is a new one:    ? ((void) 0)								      \
line 337 is a new one:    : __malloc_assert (__STRING (expr), __FILE__, __LINE__, __func__))
line 339 is a new one: extern const char *__progname;
line 342 is a new one: __malloc_assert (const char *assertion, const char *file, unsigned int line,
line 343 is a new one: 		 const char *function)
line 345 is a new one:   (void) __fxprintf (NULL, "%s%s%s:%u: %s%sAssertion `%s' failed.\n",
line 346 is a new one: 		     __progname, __progname[0] ? ": " : "",
line 347 is a new one: 		     file, line,
line 348 is a new one: 		     function ? function : "", function ? ": " : "",
line 349 is a new one: 		     assertion);
line 350 is a new one:   fflush (stderr);
line 351 is a new one:   abort ();
line 593 is a new one: /* Force a value to be in a register and stop the compiler referring
line 594 is a new one:    to the source (mostly memory location) again.  */
line 595 is a new one: #define force_reg(val) \
line 596 is a new one:   ({ __typeof (val) _v; asm ("" : "=r" (_v) : "0" (val)); _v; })
line 1024 is a new one: 	       have been freed but not use resused or consolidated)
line 1028 is a new one: 		than current total if trimming has occurred.
line 1033 is a new one: 	       back to system via malloc_trim. ("ideally" means that
line 1034 is a new one: 	       it ignores page restrictions etc.)
line 1342 is a new one: #define DEFAULT_MXFAST     (64 * SIZE_SZ / 4)
line 1615 is a new one: static Void_t*  _int_malloc(mstate, size_t);
line 1616 is a new one: #ifdef ATOMIC_FASTBINS
line 1617 is a new one: static void     _int_free(mstate, mchunkptr, int);
line 1619 is a new one: static void     _int_free(mstate, mchunkptr);
line 1621 is a new one: static Void_t*  _int_realloc(mstate, mchunkptr, INTERNAL_SIZE_T,
line 1622 is a new one: 			     INTERNAL_SIZE_T);
line 1623 is a new one: static Void_t*  _int_memalign(mstate, size_t, size_t);
line 1624 is a new one: static Void_t*  _int_valloc(mstate, size_t);
line 1671 is a new one: static Void_t*  _int_malloc();
line 1672 is a new one: static void     _int_free();
line 1673 is a new one: static Void_t*  _int_realloc();
line 1674 is a new one: static Void_t*  _int_memalign();
line 1675 is a new one: static Void_t*  _int_valloc();
line 1676 is a new one: static Void_t*  _int_pvalloc();
line 1841 is a new one: 	    |             Size of previous chunk, if allocated            | |
line 1842 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1843 is a new one: 	    |             Size of chunk, in bytes                       |M|P|
line 1845 is a new one: 	    |             User data starts here...                          .
line 1846 is a new one: 	    .                                                               .
line 1847 is a new one: 	    .             (malloc_usable_size() bytes)                      .
line 1848 is a new one: 	    .                                                               |
line 1850 is a new one: 	    |             Size of chunk                                     |
line 1851 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1865 is a new one: 	    |             Size of previous chunk                            |
line 1866 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1869 is a new one: 	    |             Forward pointer to next chunk in list             |
line 1870 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1871 is a new one: 	    |             Back pointer to previous chunk in list            |
line 1872 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1873 is a new one: 	    |             Unused space (may be 0 bytes long)                .
line 1874 is a new one: 	    .                                                               .
line 1875 is a new one: 	    .                                                               |
line 1878 is a new one: 	    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
line 1899 is a new one: 	trailing size field since there is no next contiguous chunk
line 1900 is a new one: 	that would have to index off it. After initialization, `top'
line 1901 is a new one: 	is forced to always exist.  If it would become less than
line 1902 is a new one: 	MINSIZE bytes long, it is replenished.
line 1905 is a new one: 	bit M (IS_MMAPPED) set in their size fields.  Because they are
line 1906 is a new one: 	allocated one-by-one, each must contain its own trailing size field.
line 2179 is a new one: 					126)
line 2190 is a new one: 					126)
line 2278 is a new one: #define fastbin(ar_ptr, idx) ((ar_ptr)->fastbinsY[idx])
line 2281 is a new one: #define fastbin_index(sz) \
line 2282 is a new one:   ((((unsigned int)(sz)) >> (SIZE_SZ == 8 ? 4 : 3)) - 2)
line 2286 is a new one: #define MAX_FAST_SIZE     (80 * SIZE_SZ / 4)
line 2321 is a new one: #ifdef ATOMIC_FASTBINS
line 2322 is a new one: #define clear_fastchunks(M)    catomic_or (&(M)->flags, FASTCHUNKS_BIT)
line 2323 is a new one: #define set_fastchunks(M)      catomic_and (&(M)->flags, ~FASTCHUNKS_BIT)
line 2374 is a new one:   mfastbinptr      fastbinsY[NFASTBINS];
line 2391 is a new one: #ifdef PER_THREAD
line 2392 is a new one:   /* Linked list for free arenas.  */
line 2393 is a new one:   struct malloc_state *next_free;
line 2406 is a new one: #ifdef PER_THREAD
line 2407 is a new one:   INTERNAL_SIZE_T  arena_test;
line 2408 is a new one:   INTERNAL_SIZE_T  arena_max;
line 2447 is a new one: #ifdef PER_THREAD
line 2448 is a new one: /*  Non public mallopt parameters.  */
line 2449 is a new one: #define M_ARENA_TEST -7
line 2450 is a new one: #define M_ARENA_MAX  -8
line 2616 is a new one: 	assert(((char*)p) >= min_address);
line 2617 is a new one: 	assert(((char*)p + sz) <= ((char*)(av->top)));
line 2874 is a new one: 	assert(empty);
line 2876 is a new one: 	assert(binbit);
line 2885 is a new one: 	/* chunk belongs in bin */
line 2886 is a new one: 	idx = bin_index(size);
line 2887 is a new one: 	assert(idx == i);
line 2888 is a new one: 	/* lists are sorted */
line 2889 is a new one: 	assert(p->bk == b ||
line 2890 is a new one: 	       (unsigned long)chunksize(p->bk) >= (unsigned long)chunksize(p));
line 2918 is a new one: 	   (q != av->top && inuse(q) &&
line 2919 is a new one: 	     (unsigned long)(chunksize(q)) >= MINSIZE);
line 2920 is a new one: 	   q = next_chunk(q))
line 2921 is a new one: 	do_check_inuse_chunk(av, q);
line 2937 is a new one: 	 (unsigned long)(av->max_system_mem));
line 2940 is a new one: 	 (unsigned long)(mp_.max_mmapped_mem));
line 2944 is a new one: 	 (unsigned long)(mp_.mmapped_mem) + (unsigned long)(av->system_mem));
line 3029 is a new one: 	/*
line 3030 is a new one: 	  The offset to the start of the mmapped region is stored
line 3031 is a new one: 	  in the prev_size field of the chunk. This allows us to adjust
line 3032 is a new one: 	  returned start address to meet alignment requirements here
line 3033 is a new one: 	  and in memalign(), and still be able to compute proper
line 3034 is a new one: 	  address argument for later munmap in free() and realloc().
line 3035 is a new one: 	*/
line 3041 is a new one: 	assert (((INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK) == 0);
line 3043 is a new one: 	front_misalign = (INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK;
line 3044 is a new one: 	if (front_misalign > 0) {
line 3045 is a new one: 	  correction = MALLOC_ALIGNMENT - front_misalign;
line 3046 is a new one: 	  p = (mchunkptr)(mm + correction);
line 3047 is a new one: 	  p->prev_size = correction;
line 3048 is a new one: 	  set_head(p, (size - correction) |IS_MMAPPED);
line 3050 is a new one: 	else
line 3057 is a new one: 	/* update statistics */
line 3059 is a new one: 	if (++mp_.n_mmaps > mp_.max_n_mmaps)
line 3060 is a new one: 	  mp_.max_n_mmaps = mp_.n_mmaps;
line 3062 is a new one: 	sum = mp_.mmapped_mem += size;
line 3063 is a new one: 	if (sum > (unsigned long)(mp_.max_mmapped_mem))
line 3064 is a new one: 	  mp_.max_mmapped_mem = sum;
line 3066 is a new one: 	sum += av->system_mem;
line 3067 is a new one: 	if (sum > (unsigned long)(mp_.max_total_mem))
line 3068 is a new one: 	  mp_.max_total_mem = sum;
line 3071 is a new one: 	check_chunk(av, p);
line 3073 is a new one: 	return chunk2mem(p);
line 3093 is a new one: 	 ((unsigned long) (old_size) >= MINSIZE &&
line 3094 is a new one: 	  prev_inuse(old_top) &&
line 3100 is a new one: #ifndef ATOMIC_FASTBINS
line 3149 is a new one: #ifdef ATOMIC_FASTBINS
line 3150 is a new one: 	_int_free(av, old_top, 1);
line 3152 is a new one: 	_int_free(av, old_top);
line 3200 is a new one:     void (*hook) (void) = force_reg (__after_morecore_hook);
line 3201 is a new one:     if (__builtin_expect (hook != NULL, 0))
line 3202 is a new one:       (*hook) ();
line 3229 is a new one: 	/* We do not need, and cannot use, another sbrk call to find end */
line 3230 is a new one: 	brk = mbrk;
line 3231 is a new one: 	snd_brk = brk + size;
line 3233 is a new one: 	/*
line 3234 is a new one: 	   Record that we no longer have a contiguous sbrk region.
line 3235 is a new one: 	   After the first time mmap is used as backup, we do not
line 3236 is a new one: 	   ever rely on contiguous space since this could incorrectly
line 3237 is a new one: 	   bridge regions.
line 3238 is a new one: 	*/
line 3239 is a new one: 	set_noncontiguous(av);
line 3259 is a new one:       malloc_printerr (3, "break adjusted to free malloc space", brk);
line 3266 is a new one: 	just to find out where the end of memory lies.
line 3269 is a new one: 	MALLOC_ALIGNMENT
line 3272 is a new one: 	request size to account for fact that we will not be able to
line 3273 is a new one: 	combine new space with existing space in old_top.
line 3276 is a new one: 	which case we might as well use the whole last page of request.
line 3277 is a new one: 	So we allocate enough more memory to hit a page boundary now,
line 3278 is a new one: 	which in turn causes future contiguous calls to page-align.
line 3294 is a new one: 	/* Guarantee alignment of first new chunk made from this space */
line 3296 is a new one: 	front_misalign = (INTERNAL_SIZE_T)chunk2mem(brk) & MALLOC_ALIGN_MASK;
line 3297 is a new one: 	if (front_misalign > 0) {
line 3299 is a new one: 	  /*
line 3300 is a new one: 	    Skip over some bytes to arrive at an aligned position.
line 3301 is a new one: 	    We don't need to specially mark these wasted front bytes.
line 3302 is a new one: 	    They will never be accessed anyway because
line 3303 is a new one: 	    prev_inuse of av->top (and any chunk created from its start)
line 3304 is a new one: 	    is always true after initialization.
line 3305 is a new one: 	  */
line 3307 is a new one: 	  correction = MALLOC_ALIGNMENT - front_misalign;
line 3308 is a new one: 	  aligned_brk += correction;
line 3311 is a new one: 	/*
line 3312 is a new one: 	  If this isn't adjacent to existing space, then we will not
line 3313 is a new one: 	  be able to merge with old_top space, so must add to 2nd request.
line 3314 is a new one: 	*/
line 3316 is a new one: 	correction += old_size;
line 3318 is a new one: 	/* Extend the end address to hit a page boundary */
line 3319 is a new one: 	end_misalign = (INTERNAL_SIZE_T)(brk + size + correction);
line 3320 is a new one: 	correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;
line 3322 is a new one: 	assert(correction >= 0);
line 3323 is a new one: 	snd_brk = (char*)(MORECORE(correction));
line 3325 is a new one: 	/*
line 3326 is a new one: 	  If can't allocate correction, try to at least find out current
line 3327 is a new one: 	  brk.  It might be enough to proceed without failing.
line 3329 is a new one: 	  Note that if second sbrk did NOT fail, we assume that space
line 3330 is a new one: 	  is contiguous with first sbrk. This is a safe assumption unless
line 3331 is a new one: 	  program is multithreaded but doesn't use locks and a foreign sbrk
line 3332 is a new one: 	  occurred between our first and second calls.
line 3333 is a new one: 	*/
line 3335 is a new one: 	if (snd_brk == (char*)(MORECORE_FAILURE)) {
line 3336 is a new one: 	  correction = 0;
line 3337 is a new one: 	  snd_brk = (char*)(MORECORE(0));
line 3338 is a new one: 	} else {
line 3340 is a new one: 	  void (*hook) (void) = force_reg (__after_morecore_hook);
line 3341 is a new one: 	  if (__builtin_expect (hook != NULL, 0))
line 3342 is a new one: 	    (*hook) ();
line 3348 is a new one: 	/* MORECORE/mmap must correctly align */
line 3349 is a new one: 	assert(((unsigned long)chunk2mem(brk) & MALLOC_ALIGN_MASK) == 0);
line 3351 is a new one: 	/* Find out current end of memory */
line 3352 is a new one: 	if (snd_brk == (char*)(MORECORE_FAILURE)) {
line 3353 is a new one: 	  snd_brk = (char*)(MORECORE(0));
line 3359 is a new one: 	av->top = (mchunkptr)aligned_brk;
line 3360 is a new one: 	set_head(av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
line 3361 is a new one: 	av->system_mem += correction;
line 3363 is a new one: 	/*
line 3364 is a new one: 	  If not the first time through, we either have a
line 3365 is a new one: 	  gap due to foreign sbrk or a non-contiguous region.  Insert a
line 3366 is a new one: 	  double fencepost at old_top to prevent consolidation with space
line 3367 is a new one: 	  we don't own. These fenceposts are artificial chunks that are
line 3368 is a new one: 	  marked as inuse and are in any case too small to use.  We need
line 3369 is a new one: 	  two to make sizes and alignments work out.
line 3370 is a new one: 	*/
line 3372 is a new one: 	if (old_size != 0) {
line 3373 is a new one: 	  /*
line 3374 is a new one: 	     Shrink old_top to insert fenceposts, keeping size a
line 3375 is a new one: 	     multiple of MALLOC_ALIGNMENT. We know there is at least
line 3376 is a new one: 	     enough space in old_top to do this.
line 3377 is a new one: 	  */
line 3378 is a new one: 	  old_size = (old_size - 4*SIZE_SZ) & ~MALLOC_ALIGN_MASK;
line 3379 is a new one: 	  set_head(old_top, old_size | PREV_INUSE);
line 3381 is a new one: 	  /*
line 3382 is a new one: 	    Note that the following assignments completely overwrite
line 3383 is a new one: 	    old_top when old_size was previously MINSIZE.  This is
line 3384 is a new one: 	    intentional. We need the fencepost, even if old_top otherwise gets
line 3385 is a new one: 	    lost.
line 3386 is a new one: 	  */
line 3387 is a new one: 	  chunk_at_offset(old_top, old_size            )->size =
line 3388 is a new one: 	    (2*SIZE_SZ)|PREV_INUSE;
line 3390 is a new one: 	  chunk_at_offset(old_top, old_size + 2*SIZE_SZ)->size =
line 3391 is a new one: 	    (2*SIZE_SZ)|PREV_INUSE;
line 3393 is a new one: 	  /* If possible, release the rest. */
line 3394 is a new one: 	  if (old_size >= MINSIZE) {
line 3395 is a new one: #ifdef ATOMIC_FASTBINS
line 3396 is a new one: 	    _int_free(av, old_top, 1);
line 3398 is a new one: 	    _int_free(av, old_top);
line 3480 is a new one: 	Attempt to release memory. We ignore MORECORE return value,
line 3481 is a new one: 	and instead call again to find out where new end of memory is.
line 3482 is a new one: 	This avoids problems if first call releases less than we asked,
line 3483 is a new one: 	of if failure somehow altered brk value. (We could still
line 3484 is a new one: 	encounter problems if it altered brk in some very bad way,
line 3485 is a new one: 	but the only thing we can do is adjust anyway, which will cause
line 3486 is a new one: 	some downstream failure.)
line 3491 is a new one:       void (*hook) (void) = force_reg (__after_morecore_hook);
line 3492 is a new one:       if (__builtin_expect (hook != NULL, 0))
line 3493 is a new one: 	(*hook) ();
line 3497 is a new one: 	released = (long)(current_brk - new_brk);
line 3499 is a new one: 	if (released != 0) {
line 3500 is a new one: 	  /* Success. Adjust top. */
line 3501 is a new one: 	  av->system_mem -= released;
line 3502 is a new one: 	  set_head(av->top, (top_size - released) | PREV_INUSE);
line 3503 is a new one: 	  check_malloc_state(av);
line 3504 is a new one: 	  return 1;
line 3583 is a new one: 		      MREMAP_MAYMOVE);
line 3618 is a new one:   __malloc_ptr_t (*hook) (size_t, __const __malloc_ptr_t)
line 3619 is a new one:     = force_reg (__malloc_hook);
line 3620 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 3623 is a new one:   arena_lookup(ar_ptr);
line 3625 is a new one:   // XXX We need double-word CAS and fastbins must be extended to also
line 3626 is a new one:   // XXX hold a generation counter for each entry.
line 3627 is a new one:   if (ar_ptr) {
line 3628 is a new one:     INTERNAL_SIZE_T nb;               /* normalized request size */
line 3629 is a new one:     checked_request2size(bytes, nb);
line 3630 is a new one:     if (nb <= get_max_fast ()) {
line 3631 is a new one:       long int idx = fastbin_index(nb);
line 3632 is a new one:       mfastbinptr* fb = &fastbin (ar_ptr, idx);
line 3633 is a new one:       mchunkptr pp = *fb;
line 3634 is a new one:       mchunkptr v;
line 3635 is a new one:       do
line 3637 is a new one: 	  v = pp;
line 3638 is a new one: 	  if (v == NULL)
line 3639 is a new one: 	    break;
line 3641 is a new one:       while ((pp = catomic_compare_and_exchange_val_acq (fb, v->fd, v)) != v);
line 3642 is a new one:       if (v != 0) {
line 3643 is a new one: 	if (__builtin_expect (fastbin_index (chunksize (v)) != idx, 0))
line 3644 is a new one: 	  malloc_printerr (check_action, "malloc(): memory corruption (fast)",
line 3645 is a new one: 			   chunk2mem (v));
line 3646 is a new one: 	check_remalloced_chunk(ar_ptr, v, nb);
line 3647 is a new one: 	void *p = chunk2mem(v);
line 3656 is a new one:   arena_lock(ar_ptr, bytes);
line 3674 is a new one: 	victim = _int_malloc(ar_ptr, bytes);
line 3675 is a new one: 	(void)mutex_unlock(&ar_ptr->mutex);
line 3695 is a new one:   void (*hook) (__malloc_ptr_t, __const __malloc_ptr_t)
line 3696 is a new one:     = force_reg (__free_hook);
line 3697 is a new one:   if (__builtin_expect (hook != NULL, 0)) {
line 3713 is a new one: 	&& p->size <= DEFAULT_MMAP_THRESHOLD_MAX)
line 3724 is a new one: #ifdef ATOMIC_FASTBINS
line 3725 is a new one:   _int_free(ar_ptr, p, 0);
line 3727 is a new one: # if THREAD_STATS
line 3737 is a new one:   _int_free(ar_ptr, p);
line 3754 is a new one:     force_reg (__realloc_hook);
line 3755 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 3765 is a new one:   /* chunk corresponding to oldmem */
line 3766 is a new one:   const mchunkptr oldp    = mem2chunk(oldmem);
line 3767 is a new one:   /* its size */
line 3768 is a new one:   const INTERNAL_SIZE_T oldsize = chunksize(oldp);
line 3815 is a new one: #if !defined NO_THREADS && !defined PER_THREAD
line 3820 is a new one:   newp = _int_realloc(ar_ptr, oldp, oldsize, nb);
line 3832 is a new one: 	  MALLOC_COPY (newp, oldmem, oldsize - SIZE_SZ);
line 3833 is a new one: #ifdef ATOMIC_FASTBINS
line 3834 is a new one: 	  _int_free(ar_ptr, oldp, 0);
line 3836 is a new one: # if THREAD_STATS
line 3846 is a new one: 	  _int_free(ar_ptr, oldp);
line 3866 is a new one:     force_reg (__memalign_hook);
line 3867 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 3895 is a new one: 	p = _int_memalign(ar_ptr, alignment, bytes);
line 3896 is a new one: 	(void)mutex_unlock(&ar_ptr->mutex);
line 3919 is a new one:   size_t pagesz = mp_.pagesize;
line 3923 is a new one:     force_reg (__memalign_hook);
line 3924 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 3925 is a new one:     return (*hook)(pagesz, bytes, RETURN_ADDRESS (0));
line 3927 is a new one:   arena_get(ar_ptr, bytes + pagesz + MINSIZE);
line 3936 is a new one:       p = _int_memalign(&main_arena, pagesz, bytes);
line 3943 is a new one: 	p = _int_memalign(ar_ptr, pagesz, bytes);
line 3944 is a new one: 	(void)mutex_unlock(&ar_ptr->mutex);
line 3964 is a new one:   size_t pagesz = mp_.pagesize;
line 3966 is a new one:   size_t rounded_bytes = (bytes + page_mask) & ~(page_mask);
line 3970 is a new one:     force_reg (__memalign_hook);
line 3971 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 3972 is a new one:     return (*hook)(pagesz, rounded_bytes, RETURN_ADDRESS (0));
line 3974 is a new one:   arena_get(ar_ptr, bytes + 2*pagesz + MINSIZE);
line 3981 is a new one:       p = _int_memalign(&main_arena, pagesz, rounded_bytes);
line 3986 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0,
line 3987 is a new one: 			  bytes + 2*pagesz + MINSIZE);
line 3989 is a new one: 	p = _int_memalign(ar_ptr, pagesz, rounded_bytes);
line 3990 is a new one: 	(void)mutex_unlock(&ar_ptr->mutex);
line 4024 is a new one:     force_reg (__malloc_hook);
line 4025 is a new one:   if (__builtin_expect (hook != NULL, 0)) {
line 4083 is a new one: 	mem = _int_malloc(av, sz);
line 4084 is a new one: 	(void)mutex_unlock(&av->mutex);
line 4244 is a new one: static Void_t*
line 4283 is a new one:     idx = fastbin_index(nb);
line 4284 is a new one:     mfastbinptr* fb = &fastbin (av, idx);
line 4285 is a new one: #ifdef ATOMIC_FASTBINS
line 4286 is a new one:     mchunkptr pp = *fb;
line 4287 is a new one:     do
line 4289 is a new one: 	victim = pp;
line 4290 is a new one: 	if (victim == NULL)
line 4291 is a new one: 	  break;
line 4293 is a new one:     while ((pp = catomic_compare_and_exchange_val_acq (fb, victim->fd, victim))
line 4294 is a new one: 	   != victim);
line 4296 is a new one:     victim = *fb;
line 4298 is a new one:     if (victim != 0) {
line 4302 is a new one: #ifndef ATOMIC_FASTBINS
line 4329 is a new one: 	bck = victim->bk;
line 4330 is a new one: 	set_inuse_bit_at_offset(victim, nb);
line 4331 is a new one: 	bin->bk = bck;
line 4332 is a new one: 	bck->fd = bin;
line 4387 is a new one: 	 If a small request, try to use last remainder if it is the
line 4388 is a new one: 	 only chunk in unsorted bin.  This helps promote locality for
line 4389 is a new one: 	 runs of consecutive small requests. This is the only
line 4390 is a new one: 	 exception to best-fit, and applies only when there is
line 4391 is a new one: 	 no exact fit for a small chunk.
line 4395 is a new one: 	  bck == unsorted_chunks(av) &&
line 4396 is a new one: 	  victim == av->last_remainder &&
line 4397 is a new one: 	  (unsigned long)(size) > (unsigned long)(nb + MINSIZE)) {
line 4399 is a new one: 	/* split and reattach remainder */
line 4400 is a new one: 	remainder_size = size - nb;
line 4401 is a new one: 	remainder = chunk_at_offset(victim, nb);
line 4402 is a new one: 	unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
line 4403 is a new one: 	av->last_remainder = remainder;
line 4404 is a new one: 	remainder->bk = remainder->fd = unsorted_chunks(av);
line 4411 is a new one: 	set_head(victim, nb | PREV_INUSE |
line 4413 is a new one: 	set_head(remainder, remainder_size | PREV_INUSE);
line 4414 is a new one: 	set_foot(remainder, remainder_size);
line 4430 is a new one: 	set_inuse_bit_at_offset(victim, size);
line 4443 is a new one: 	victim_index = smallbin_index(size);
line 4444 is a new one: 	bck = bin_at(av, victim_index);
line 4445 is a new one: 	fwd = bck->fd;
line 4448 is a new one: 	victim_index = largebin_index(size);
line 4449 is a new one: 	bck = bin_at(av, victim_index);
line 4450 is a new one: 	fwd = bck->fd;
line 4452 is a new one: 	/* maintain large bins in sorted order */
line 4453 is a new one: 	if (fwd != bck) {
line 4455 is a new one: 	  size |= PREV_INUSE;
line 4456 is a new one: 	  /* if smaller than smallest, bypass loop below */
line 4459 is a new one: 	    fwd = bck;
line 4460 is a new one: 	    bck = bck->bk;
line 4511 is a new one: 	  (unsigned long)(victim->size) >= (unsigned long)(nb)) {
line 4514 is a new one: 	while (((unsigned long)(size = chunksize(victim)) <
line 4515 is a new one: 		(unsigned long)(nb)))
line 4516 is a new one: 	  victim = victim->bk_nextsize;
line 4523 is a new one: 	remainder_size = size - nb;
line 4524 is a new one: 	unlink(victim, bck, fwd);
line 4526 is a new one: 	/* Exhaust */
line 4527 is a new one: 	if (remainder_size < MINSIZE)  {
line 4528 is a new one: 	  set_inuse_bit_at_offset(victim, size);
line 4532 is a new one: 	/* Split */
line 4533 is a new one: 	else {
line 4534 is a new one: 	  remainder = chunk_at_offset(victim, nb);
line 4548 is a new one: 	  set_head(victim, nb | PREV_INUSE |
line 4550 is a new one: 	  set_head(remainder, remainder_size | PREV_INUSE);
line 4551 is a new one: 	  set_foot(remainder, remainder_size);
line 4582 is a new one: 	do {
line 4583 is a new one: 	  if (++block >= BINMAPSIZE)  /* out of bins */
line 4584 is a new one: 	    goto use_top;
line 4585 is a new one: 	} while ( (map = av->binmap[block]) == 0);
line 4587 is a new one: 	bin = bin_at(av, (block << BINMAPSHIFT));
line 4588 is a new one: 	bit = 1;
line 4593 is a new one: 	bin = next_bin(bin);
line 4594 is a new one: 	bit <<= 1;
line 4595 is a new one: 	assert(bit != 0);
line 4603 is a new one: 	av->binmap[block] = map &= ~bit; /* Write through */
line 4604 is a new one: 	bin = next_bin(bin);
line 4605 is a new one: 	bit <<= 1;
line 4609 is a new one: 	size = chunksize(victim);
line 4611 is a new one: 	/*  We know the first chunk in this bin is big enough to use. */
line 4612 is a new one: 	assert((unsigned long)(size) >= (unsigned long)(nb));
line 4614 is a new one: 	remainder_size = size - nb;
line 4616 is a new one: 	/* unlink */
line 4617 is a new one: 	unlink(victim, bck, fwd);
line 4619 is a new one: 	/* Exhaust */
line 4620 is a new one: 	if (remainder_size < MINSIZE) {
line 4621 is a new one: 	  set_inuse_bit_at_offset(victim, size);
line 4626 is a new one: 	/* Split */
line 4627 is a new one: 	else {
line 4628 is a new one: 	  remainder = chunk_at_offset(victim, nb);
line 4639 is a new one: 	  /* advertise as last remainder */
line 4640 is a new one: 	  if (in_smallbin_range(nb))
line 4641 is a new one: 	    av->last_remainder = remainder;
line 4647 is a new one: 	  set_head(victim, nb | PREV_INUSE |
line 4649 is a new one: 	  set_head(remainder, remainder_size | PREV_INUSE);
line 4650 is a new one: 	  set_foot(remainder, remainder_size);
line 4694 is a new one: #ifdef ATOMIC_FASTBINS
line 4695 is a new one:     /* When we are using atomic ops to free fast chunks we can get
line 4696 is a new one:        here for all block sizes.  */
line 4699 is a new one:       /* restore original bin index */
line 4700 is a new one:       if (in_smallbin_range(nb))
line 4701 is a new one: 	idx = smallbin_index(nb);
line 4703 is a new one: 	idx = largebin_index(nb);
line 4736 is a new one: #ifdef ATOMIC_FASTBINS
line 4737 is a new one: _int_free(mstate av, mchunkptr p, int have_lock)
line 4739 is a new one: _int_free(mstate av, mchunkptr p)
line 4752 is a new one: #ifdef ATOMIC_FASTBINS
line 4753 is a new one:   int locked = 0;
line 4767 is a new one: #ifdef ATOMIC_FASTBINS
line 4768 is a new one:       if (! have_lock && locked)
line 4769 is a new one: 	(void)mutex_unlock(&av->mutex);
line 4771 is a new one:       malloc_printerr (check_action, errstr, chunk2mem(p));
line 4803 is a new one: #ifdef ATOMIC_FASTBINS
line 4804 is a new one: 	/* We might not have a lock at this point and concurrent modifications
line 4805 is a new one: 	   of system_mem might have let to a false positive.  Redo the test
line 4806 is a new one: 	   after getting the lock.  */
line 4807 is a new one: 	if (have_lock
line 4808 is a new one: 	    || ({ assert (locked == 0);
line 4809 is a new one: 		  mutex_lock(&av->mutex);
line 4810 is a new one: 		  locked = 1;
line 4811 is a new one: 		  chunk_at_offset (p, size)->size <= 2 * SIZE_SZ
line 4812 is a new one: 		    || chunksize (chunk_at_offset (p, size)) >= av->system_mem;
line 4813 is a new one: 	      }))
line 4816 is a new one: 	    errstr = "free(): invalid next size (fast)";
line 4817 is a new one: 	    goto errout;
line 4819 is a new one: #ifdef ATOMIC_FASTBINS
line 4820 is a new one: 	if (! have_lock)
line 4822 is a new one: 	    (void)mutex_unlock(&av->mutex);
line 4823 is a new one: 	    locked = 0;
line 4829 is a new one:       free_perturb (chunk2mem(p), size - SIZE_SZ);
line 4832 is a new one:     fb = &fastbin (av, fastbin_index(size));
line 4834 is a new one: #ifdef ATOMIC_FASTBINS
line 4835 is a new one:     mchunkptr fd;
line 4836 is a new one:     mchunkptr old = *fb;
line 4837 is a new one:     do
line 4839 is a new one: 	/* Another simple check: make sure the top of the bin is not the
line 4840 is a new one: 	   record we are going to add (i.e., double free).  */
line 4841 is a new one: 	if (__builtin_expect (old == p, 0))
line 4843 is a new one: 	    errstr = "double free or corruption (fasttop)";
line 4844 is a new one: 	    goto errout;
line 4846 is a new one: 	p->fd = fd = old;
line 4848 is a new one:     while ((old = catomic_compare_and_exchange_val_rel (fb, p, fd)) != fd);
line 4868 is a new one: #ifdef ATOMIC_FASTBINS
line 4869 is a new one:     if (! have_lock) {
line 4870 is a new one: # if THREAD_STATS
line 4871 is a new one:       if(!mutex_trylock(&av->mutex))
line 4872 is a new one: 	++(av->stat_lock_direct);
line 4874 is a new one: 	(void)mutex_lock(&av->mutex);
line 4875 is a new one: 	++(av->stat_lock_wait);
line 4878 is a new one:       (void)mutex_lock(&av->mutex);
line 4880 is a new one:       locked = 1;
line 4917 is a new one:       free_perturb (chunk2mem(p), size - SIZE_SZ);
line 5007 is a new one: #ifdef ATOMIC_FASTBINS
line 5008 is a new one:     if (! have_lock) {
line 5009 is a new one:       assert (locked);
line 5010 is a new one:       (void)mutex_unlock(&av->mutex);
line 5088 is a new one:     maxfb = &fastbin (av, fastbin_index(get_max_fast ()));
line 5090 is a new one:     maxfb = &fastbin (av, NFASTBINS - 1);
line 5092 is a new one:     fb = &fastbin (av, 0);
line 5094 is a new one: #ifdef ATOMIC_FASTBINS
line 5095 is a new one:       p = atomic_exchange_acq (fb, 0);
line 5097 is a new one:       p = *fb;
line 5099 is a new one:       if (p != 0) {
line 5100 is a new one: #ifndef ATOMIC_FASTBINS
line 5101 is a new one: 	*fb = 0;
line 5103 is a new one: 	do {
line 5104 is a new one: 	  check_inuse_chunk(av, p);
line 5105 is a new one: 	  nextp = p->fd;
line 5107 is a new one: 	  /* Slightly streamlined version of consolidation code in free() */
line 5108 is a new one: 	  size = p->size & ~(PREV_INUSE|NON_MAIN_ARENA);
line 5109 is a new one: 	  nextchunk = chunk_at_offset(p, size);
line 5110 is a new one: 	  nextsize = chunksize(nextchunk);
line 5112 is a new one: 	  if (!prev_inuse(p)) {
line 5113 is a new one: 	    prevsize = p->prev_size;
line 5114 is a new one: 	    size += prevsize;
line 5115 is a new one: 	    p = chunk_at_offset(p, -((long) prevsize));
line 5116 is a new one: 	    unlink(p, bck, fwd);
line 5119 is a new one: 	  if (nextchunk != av->top) {
line 5120 is a new one: 	    nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
line 5122 is a new one: 	    if (!nextinuse) {
line 5123 is a new one: 	      size += nextsize;
line 5124 is a new one: 	      unlink(nextchunk, bck, fwd);
line 5125 is a new one: 	    } else
line 5128 is a new one: 	    first_unsorted = unsorted_bin->fd;
line 5129 is a new one: 	    unsorted_bin->fd = p;
line 5130 is a new one: 	    first_unsorted->bk = p;
line 5132 is a new one: 	    if (!in_smallbin_range (size)) {
line 5137 is a new one: 	    set_head(p, size | PREV_INUSE);
line 5138 is a new one: 	    p->bk = unsorted_bin;
line 5139 is a new one: 	    p->fd = first_unsorted;
line 5140 is a new one: 	    set_foot(p, size);
line 5144 is a new one: 	    size += nextsize;
line 5145 is a new one: 	    set_head(p, size | PREV_INUSE);
line 5146 is a new one: 	    av->top = p;
line 5149 is a new one: 	} while ( (p = nextp) != 0);
line 5165 is a new one: _int_realloc(mstate av, mchunkptr oldp, INTERNAL_SIZE_T oldsize,
line 5166 is a new one: 	     INTERNAL_SIZE_T nb)
line 5187 is a new one:   /* oldmem size */
line 5193 is a new one:       malloc_printerr (check_action, errstr, chunk2mem(oldp));
line 5199 is a new one:   /* All callers already filter out mmap'ed chunks.  */
line 5201 is a new one:   if (!chunk_is_mmapped(oldp))
line 5203 is a new one:   assert (!chunk_is_mmapped(oldp));
line 5225 is a new one: 	  (unsigned long)(newsize = oldsize + nextsize) >=
line 5226 is a new one: 	  (unsigned long)(nb + MINSIZE)) {
line 5227 is a new one: 	set_head_size(oldp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 5228 is a new one: 	av->top = chunk_at_offset(oldp, nb);
line 5229 is a new one: 	set_head(av->top, (newsize - nb) | PREV_INUSE);
line 5231 is a new one: 	return chunk2mem(oldp);
line 5236 is a new one: 	       !inuse(next) &&
line 5237 is a new one: 	       (unsigned long)(newsize = oldsize + nextsize) >=
line 5238 is a new one: 	       (unsigned long)(nb)) {
line 5239 is a new one: 	newp = oldp;
line 5240 is a new one: 	unlink(next, bck, fwd);
line 5245 is a new one: 	newmem = _int_malloc(av, nb - MALLOC_ALIGN_MASK);
line 5246 is a new one: 	if (newmem == 0)
line 5247 is a new one: 	  return 0; /* propagate failure */
line 5249 is a new one: 	newp = mem2chunk(newmem);
line 5250 is a new one: 	newsize = chunksize(newp);
line 5252 is a new one: 	/*
line 5253 is a new one: 	  Avoid copy if newp is next chunk after oldp.
line 5254 is a new one: 	*/
line 5255 is a new one: 	if (newp == next) {
line 5256 is a new one: 	  newsize += oldsize;
line 5257 is a new one: 	  newp = oldp;
line 5259 is a new one: 	else {
line 5260 is a new one: 	  /*
line 5261 is a new one: 	    Unroll copy of <= 36 bytes (72 if 8byte sizes)
line 5262 is a new one: 	    We know that contents have an odd number of
line 5263 is a new one: 	    INTERNAL_SIZE_T-sized words; minimally 3.
line 5264 is a new one: 	  */
line 5266 is a new one: 	  copysize = oldsize - SIZE_SZ;
line 5267 is a new one: 	  s = (INTERNAL_SIZE_T*)(chunk2mem(oldp));
line 5268 is a new one: 	  d = (INTERNAL_SIZE_T*)(newmem);
line 5269 is a new one: 	  ncopies = copysize / sizeof(INTERNAL_SIZE_T);
line 5270 is a new one: 	  assert(ncopies >= 3);
line 5272 is a new one: 	  if (ncopies > 9)
line 5273 is a new one: 	    MALLOC_COPY(d, s, copysize);
line 5276 is a new one: 	    *(d+0) = *(s+0);
line 5277 is a new one: 	    *(d+1) = *(s+1);
line 5278 is a new one: 	    *(d+2) = *(s+2);
line 5279 is a new one: 	    if (ncopies > 4) {
line 5280 is a new one: 	      *(d+3) = *(s+3);
line 5281 is a new one: 	      *(d+4) = *(s+4);
line 5282 is a new one: 	      if (ncopies > 6) {
line 5283 is a new one: 		*(d+5) = *(s+5);
line 5284 is a new one: 		*(d+6) = *(s+6);
line 5285 is a new one: 		if (ncopies > 8) {
line 5286 is a new one: 		  *(d+7) = *(s+7);
line 5287 is a new one: 		  *(d+8) = *(s+8);
line 5288 is a new one: 		}
line 5293 is a new one: #ifdef ATOMIC_FASTBINS
line 5294 is a new one: 	  _int_free(av, oldp, 1);
line 5296 is a new one: 	  _int_free(av, oldp);
line 5298 is a new one: 	  check_inuse_chunk(av, newp);
line 5299 is a new one: 	  return chunk2mem(newp);
line 5321 is a new one: #ifdef ATOMIC_FASTBINS
line 5322 is a new one:       _int_free(av, remainder, 1);
line 5324 is a new one:       _int_free(av, remainder);
line 5351 is a new one:       return chunk2mem(oldp);
line 5366 is a new one: 	mp_.max_mmapped_mem = sum;
line 5370 is a new one: 	mp_.max_total_mem = sum;
line 5379 is a new one:       newmem = chunk2mem(oldp); /* do nothing */
line 5384 is a new one: 	MALLOC_COPY(newmem, chunk2mem(oldp), oldsize - 2*SIZE_SZ);
line 5385 is a new one: #ifdef ATOMIC_FASTBINS
line 5386 is a new one: 	_int_free(av, oldp, 1);
line 5388 is a new one: 	_int_free(av, oldp);
line 5408 is a new one: static Void_t*
line 5464 is a new one: 			   -((signed long) alignment));
line 5484 is a new one: #ifdef ATOMIC_FASTBINS
line 5485 is a new one:     _int_free(av, p, 1);
line 5487 is a new one:     _int_free(av, p);
line 5492 is a new one: 	    (((unsigned long)(chunk2mem(p))) % alignment) == 0);
line 5504 is a new one: #ifdef ATOMIC_FASTBINS
line 5505 is a new one:       _int_free(av, remainder, 1);
line 5507 is a new one:       _int_free(av, remainder);
line 5542 is a new one: 	Unroll clear of <= 36 bytes (72 if 8byte sizes)
line 5543 is a new one: 	We know that contents have an odd number of
line 5544 is a new one: 	INTERNAL_SIZE_T-sized words; minimally 3.
line 5553 is a new one: 	MALLOC_ZERO(d, clearsize);
line 5556 is a new one: 	*(d+0) = 0;
line 5557 is a new one: 	*(d+1) = 0;
line 5558 is a new one: 	*(d+2) = 0;
line 5559 is a new one: 	if (nclears > 4) {
line 5560 is a new one: 	  *(d+3) = 0;
line 5561 is a new one: 	  *(d+4) = 0;
line 5562 is a new one: 	  if (nclears > 6) {
line 5563 is a new one: 	    *(d+5) = 0;
line 5564 is a new one: 	    *(d+6) = 0;
line 5565 is a new one: 	    if (nclears > 8) {
line 5566 is a new one: 	      *(d+7) = 0;
line 5567 is a new one: 	      *(d+8) = 0;
line 5713 is a new one: 	size = element_size;
line 5715 is a new one: 	size = request2size(sizes[i]);
line 5749 is a new one: static Void_t*
line 5766 is a new one: static Void_t*
line 5803 is a new one: 	mbinptr bin = bin_at (av, i);
line 5805 is a new one: 	for (mchunkptr p = last (bin); p != bin; p = p->bk)
line 5895 is a new one:     for (p = fastbin (av, i); p != 0; p = p->fd) {
line 5988 is a new one: 	  stat_lock_direct + stat_lock_loop + stat_lock_wait);
line 6064 is a new one: #ifdef PER_THREAD
line 6065 is a new one:   case M_ARENA_TEST:
line 6066 is a new one:     if (value > 0)
line 6067 is a new one:       mp_.arena_test = value;
line 6070 is a new one:   case M_ARENA_MAX:
line 6071 is a new one:     if (value > 0)
line 6072 is a new one:       mp_.arena_max = value;
line 6177 is a new one: 	 size = MINIMUM_MORECORE_SIZE;
line 6179 is a new one: 	 ptr = PoolAllocateResident(size + RM_PAGE_SIZE, 0);
line 6182 is a new one: 	return (void *) MORECORE_FAILURE;
line 6212 is a new one: 	 PoolDeallocate(*ptr);
line 6213 is a new one: 	 *ptr = 0;
line 6266 is a new one:     force_reg (__memalign_hook);
line 6267 is a new one:   if (__builtin_expect (hook != NULL, 0))
line 6283 is a new one: malloc_info (int options, FILE *fp)
line 6285 is a new one:   /* For now, at least.  */
line 6286 is a new one:   if (options != 0)
line 6289 is a new one:   int n = 0;
line 6290 is a new one:   size_t total_nblocks = 0;
line 6291 is a new one:   size_t total_nfastblocks = 0;
line 6292 is a new one:   size_t total_avail = 0;
line 6293 is a new one:   size_t total_fastavail = 0;
line 6294 is a new one:   size_t total_system = 0;
line 6295 is a new one:   size_t total_max_system = 0;
line 6296 is a new one:   size_t total_aspace = 0;
line 6297 is a new one:   size_t total_aspace_mprotect = 0;
line 6299 is a new one:   void mi_arena (mstate ar_ptr)
line 6301 is a new one:     fprintf (fp, "<heap nr=\"%d\">\n<sizes>\n", n++);
line 6303 is a new one:     size_t nblocks = 0;
line 6304 is a new one:     size_t nfastblocks = 0;
line 6305 is a new one:     size_t avail = 0;
line 6306 is a new one:     size_t fastavail = 0;
line 6307 is a new one:     struct
line 6309 is a new one:       size_t from;
line 6310 is a new one:       size_t to;
line 6311 is a new one:       size_t total;
line 6312 is a new one:       size_t count;
line 6313 is a new one:     } sizes[NFASTBINS + NBINS - 1];
line 6314 is a new one: #define nsizes (sizeof (sizes) / sizeof (sizes[0]))
line 6316 is a new one:     mutex_lock (&ar_ptr->mutex);
line 6318 is a new one:     for (size_t i = 0; i < NFASTBINS; ++i)
line 6320 is a new one: 	mchunkptr p = fastbin (ar_ptr, i);
line 6321 is a new one: 	if (p != NULL)
line 6323 is a new one: 	    size_t nthissize = 0;
line 6324 is a new one: 	    size_t thissize = chunksize (p);
line 6326 is a new one: 	    while (p != NULL)
line 6328 is a new one: 		++nthissize;
line 6329 is a new one: 		p = p->fd;
line 6332 is a new one: 	    fastavail += nthissize * thissize;
line 6333 is a new one: 	    nfastblocks += nthissize;
line 6334 is a new one: 	    sizes[i].from = thissize - (MALLOC_ALIGNMENT - 1);
line 6335 is a new one: 	    sizes[i].to = thissize;
line 6336 is a new one: 	    sizes[i].count = nthissize;
line 6338 is a new one: 	else
line 6339 is a new one: 	  sizes[i].from = sizes[i].to = sizes[i].count = 0;
line 6341 is a new one: 	sizes[i].total = sizes[i].count * sizes[i].to;
line 6344 is a new one:     mbinptr bin = bin_at (ar_ptr, 1);
line 6345 is a new one:     struct malloc_chunk *r = bin->fd;
line 6346 is a new one:     while (r != bin)
line 6348 is a new one: 	++sizes[NFASTBINS].count;
line 6349 is a new one: 	sizes[NFASTBINS].total += r->size;
line 6350 is a new one: 	sizes[NFASTBINS].from = MIN (sizes[NFASTBINS].from, r->size);
line 6351 is a new one: 	sizes[NFASTBINS].to = MAX (sizes[NFASTBINS].to, r->size);
line 6352 is a new one: 	r = r->fd;
line 6354 is a new one:     nblocks += sizes[NFASTBINS].count;
line 6355 is a new one:     avail += sizes[NFASTBINS].total;
line 6357 is a new one:     for (size_t i = 2; i < NBINS; ++i)
line 6359 is a new one: 	bin = bin_at (ar_ptr, i);
line 6360 is a new one: 	r = bin->fd;
line 6361 is a new one: 	sizes[NFASTBINS - 1 + i].from = ~((size_t) 0);
line 6362 is a new one: 	sizes[NFASTBINS - 1 + i].to = sizes[NFASTBINS - 1 + i].total
line 6363 is a new one: 	  = sizes[NFASTBINS - 1 + i].count = 0;
line 6365 is a new one: 	while (r != bin)
line 6367 is a new one: 	    ++sizes[NFASTBINS - 1 + i].count;
line 6368 is a new one: 	    sizes[NFASTBINS - 1 + i].total += r->size;
line 6369 is a new one: 	    sizes[NFASTBINS - 1 + i].from = MIN (sizes[NFASTBINS - 1 + i].from,
line 6370 is a new one: 						 r->size);
line 6371 is a new one: 	    sizes[NFASTBINS - 1 + i].to = MAX (sizes[NFASTBINS - 1 + i].to,
line 6372 is a new one: 					       r->size);
line 6374 is a new one: 	    r = r->fd;
line 6377 is a new one: 	if (sizes[NFASTBINS - 1 + i].count == 0)
line 6378 is a new one: 	  sizes[NFASTBINS - 1 + i].from = 0;
line 6379 is a new one: 	nblocks += sizes[NFASTBINS - 1 + i].count;
line 6380 is a new one: 	avail += sizes[NFASTBINS - 1 + i].total;
line 6383 is a new one:     mutex_unlock (&ar_ptr->mutex);
line 6385 is a new one:     total_nfastblocks += nfastblocks;
line 6386 is a new one:     total_fastavail += fastavail;
line 6388 is a new one:     total_nblocks += nblocks;
line 6389 is a new one:     total_avail += avail;
line 6391 is a new one:     for (size_t i = 0; i < nsizes; ++i)
line 6392 is a new one:       if (sizes[i].count != 0 && i != NFASTBINS)
line 6393 is a new one: 	fprintf (fp, "\
line 6394 is a new one: <size from=\"%zu\" to=\"%zu\" total=\"%zu\" count=\"%zu\"/>\n",
line 6395 is a new one: 		 sizes[i].from, sizes[i].to, sizes[i].total, sizes[i].count);
line 6397 is a new one:     if (sizes[NFASTBINS].count != 0)
line 6398 is a new one:       fprintf (fp, "\
line 6399 is a new one: <unsorted from=\"%zu\" to=\"%zu\" total=\"%zu\" count=\"%zu\"/>\n",
line 6400 is a new one: 	       sizes[NFASTBINS].from, sizes[NFASTBINS].to,
line 6401 is a new one: 	       sizes[NFASTBINS].total, sizes[NFASTBINS].count);
line 6403 is a new one:     total_system += ar_ptr->system_mem;
line 6404 is a new one:     total_max_system += ar_ptr->max_system_mem;
line 6406 is a new one:     fprintf (fp,
line 6407 is a new one: 	     "</sizes>\n<total type=\"fast\" count=\"%zu\" size=\"%zu\"/>\n"
line 6408 is a new one: 	     "<total type=\"rest\" count=\"%zu\" size=\"%zu\"/>\n"
line 6409 is a new one: 	     "<system type=\"current\" size=\"%zu\"/>\n"
line 6410 is a new one: 	     "<system type=\"max\" size=\"%zu\"/>\n",
line 6411 is a new one: 	     nfastblocks, fastavail, nblocks, avail,
line 6412 is a new one: 	     ar_ptr->system_mem, ar_ptr->max_system_mem);
line 6414 is a new one:     if (ar_ptr != &main_arena)
line 6416 is a new one: 	heap_info *heap = heap_for_ptr(top(ar_ptr));
line 6417 is a new one: 	fprintf (fp,
line 6418 is a new one: 		 "<aspace type=\"total\" size=\"%zu\"/>\n"
line 6419 is a new one: 		 "<aspace type=\"mprotect\" size=\"%zu\"/>\n",
line 6420 is a new one: 		 heap->size, heap->mprotect_size);
line 6421 is a new one: 	total_aspace += heap->size;
line 6422 is a new one: 	total_aspace_mprotect += heap->mprotect_size;
line 6426 is a new one: 	fprintf (fp,
line 6427 is a new one: 		 "<aspace type=\"total\" size=\"%zu\"/>\n"
line 6428 is a new one: 		 "<aspace type=\"mprotect\" size=\"%zu\"/>\n",
line 6429 is a new one: 		 ar_ptr->system_mem, ar_ptr->system_mem);
line 6430 is a new one: 	total_aspace += ar_ptr->system_mem;
line 6431 is a new one: 	total_aspace_mprotect += ar_ptr->system_mem;
line 6434 is a new one:     fputs ("</heap>\n", fp);
line 6437 is a new one:   fputs ("<malloc version=\"1\">\n", fp);
line 6439 is a new one:   /* Iterate over all arenas currently in use.  */
line 6443 is a new one:       mi_arena (ar_ptr);
line 6448 is a new one:   fprintf (fp,
line 6449 is a new one: 	   "<total type=\"fast\" count=\"%zu\" size=\"%zu\"/>\n"
line 6450 is a new one: 	   "<total type=\"rest\" count=\"%zu\" size=\"%zu\"/>\n"
line 6451 is a new one: 	   "<system type=\"current\" size=\"%zu\n/>\n"
line 6452 is a new one: 	   "<system type=\"max\" size=\"%zu\n/>\n"
line 6453 is a new one: 	   "<aspace type=\"total\" size=\"%zu\"/>\n"
line 6454 is a new one: 	   "<aspace type=\"mprotect\" size=\"%zu\"/>\n"
line 6455 is a new one: 	   "</malloc>\n",
line 6456 is a new one: 	   total_nfastblocks, total_fastavail, total_nblocks, total_avail,
line 6457 is a new one: 	   total_system, total_max_system,
line 6458 is a new one: 	   total_aspace, total_aspace_mprotect);
