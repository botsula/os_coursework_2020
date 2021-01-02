Comparison of files: malloc_v2_6.c and malloc_v2_4.c
line 1 is a new one:    Copyright (C) 1996-2006, 2007 Free Software Foundation, Inc.
line 257 is a new one: #include <bits/wordsize.h>
line 1414 is a new one:   MMAP_THRESHOLD_MAX and _MIN are the bounds on the dynamically
line 1415 is a new one:   adjusted MMAP_THRESHOLD.
line 1418 is a new one: #ifndef DEFAULT_MMAP_THRESHOLD_MIN
line 1419 is a new one: #define DEFAULT_MMAP_THRESHOLD_MIN (128 * 1024)
line 1422 is a new one: #ifndef DEFAULT_MMAP_THRESHOLD_MAX
line 1423 is a new one:   /* For 32-bit platforms we cannot increase the maximum mmap
line 1424 is a new one:      threshold much because it is also the minimum value for the
line 1425 is a new one:      maximum heap size and its alignment.  Going above 512k (i.e., 1M
line 1426 is a new one:      for new heaps) wastes too much address space.  */
line 1427 is a new one: # if __WORDSIZE == 32
line 1428 is a new one: #  define DEFAULT_MMAP_THRESHOLD_MAX (512 * 1024)
line 1430 is a new one: #  define DEFAULT_MMAP_THRESHOLD_MAX (4 * 1024 * 1024 * sizeof(long))
line 1475 is a new one:   Update in 2006:
line 1476 is a new one:   The above was written in 2001. Since then the world has changed a lot.
line 1477 is a new one:   Memory got bigger. Applications got bigger. The virtual address space
line 1478 is a new one:   layout in 32 bit linux changed.
line 1480 is a new one:   In the new situation, brk() and mmap space is shared and there are no
line 1481 is a new one:   artificial limits on brk size imposed by the kernel. What is more,
line 1482 is a new one:   applications have started using transient allocations larger than the
line 1483 is a new one:   128Kb as was imagined in 2001.
line 1485 is a new one:   The price for mmap is also high now; each time glibc mmaps from the
line 1486 is a new one:   kernel, the kernel is forced to zero out the memory it gives to the
line 1487 is a new one:   application. Zeroing memory is expensive and eats a lot of cache and
line 1488 is a new one:   memory bandwidth. This has nothing to do with the efficiency of the
line 1489 is a new one:   virtual memory system, by doing mmap the kernel just has no choice but
line 1490 is a new one:   to zero.
line 1492 is a new one:   In 2001, the kernel had a maximum size for brk() which was about 800
line 1493 is a new one:   megabytes on 32 bit x86, at that point brk() would hit the first
line 1494 is a new one:   mmaped shared libaries and couldn't expand anymore. With current 2.6
line 1495 is a new one:   kernels, the VA space layout is different and brk() and mmap
line 1496 is a new one:   both can span the entire heap at will.
line 1498 is a new one:   Rather than using a static threshold for the brk/mmap tradeoff,
line 1499 is a new one:   we are now using a simple dynamic one. The goal is still to avoid
line 1500 is a new one:   fragmentation. The old goals we kept are
line 1501 is a new one:   1) try to get the long lived large allocations to use mmap()
line 1502 is a new one:   2) really large allocations should always use mmap()
line 1503 is a new one:   and we're adding now:
line 1504 is a new one:   3) transient allocations should use brk() to avoid forcing the kernel
line 1505 is a new one:      having to zero memory over and over again
line 1507 is a new one:   The implementation works with a sliding threshold, which is by default
line 1508 is a new one:   limited to go between 128Kb and 32Mb (64Mb for 64 bitmachines) and starts
line 1509 is a new one:   out at 128Kb as per the 2001 default.
line 1511 is a new one:   This allows us to satisfy requirement 1) under the assumption that long
line 1512 is a new one:   lived allocations are made early in the process' lifespan, before it has
line 1513 is a new one:   started doing dynamic allocations of the same size (which will
line 1514 is a new one:   increase the threshold).
line 1516 is a new one:   The upperbound on the threshold satisfies requirement 2)
line 1518 is a new one:   The threshold goes up in value when the application frees memory that was
line 1519 is a new one:   allocated with the mmap allocator. The idea is that once the application
line 1520 is a new one:   starts freeing memory of a certain size, it's highly probable that this is
line 1521 is a new one:   a size the application uses for transient allocations. This estimator
line 1522 is a new one:   is there to satisfy the new third requirement.
line 1529 is a new one: #define DEFAULT_MMAP_THRESHOLD DEFAULT_MMAP_THRESHOLD_MIN
line 1616 is a new one: #  if USE___THREAD || !defined SHARED
line 1780 is a new one:   /* Only used for large blocks: pointer to next larger size.  */
line 1781 is a new one:   struct malloc_chunk* fd_nextsize; /* double links -- used only if free. */
line 1782 is a new one:   struct malloc_chunk* bk_nextsize;
line 1883 is a new one: #define MIN_CHUNK_SIZE        (offsetof(struct malloc_chunk, fd_nextsize))
line 2063 is a new one: #define bin_at(m, i) \
line 2064 is a new one:   (mbinptr) (((char *) &((m)->bins[((i) - 1) * 2]))			      \
line 2065 is a new one: 	     - offsetof (struct malloc_chunk, fd))
line 2083 is a new one:     if (!in_smallbin_range (P->size)				       \
line 2084 is a new one: 	&& __builtin_expect (P->fd_nextsize != NULL, 0)) {	       \
line 2085 is a new one:       assert (P->fd_nextsize->bk_nextsize == P);		       \
line 2086 is a new one:       assert (P->bk_nextsize->fd_nextsize == P);		       \
line 2087 is a new one:       if (FD->fd_nextsize == NULL) {				       \
line 2088 is a new one: 	if (P->fd_nextsize == P)				       \
line 2089 is a new one: 	  FD->fd_nextsize = FD->bk_nextsize = FD;		       \
line 2090 is a new one: 	else {							       \
line 2091 is a new one: 	  FD->fd_nextsize = P->fd_nextsize;			       \
line 2092 is a new one: 	  FD->bk_nextsize = P->bk_nextsize;			       \
line 2093 is a new one: 	  P->fd_nextsize->bk_nextsize = FD;			       \
line 2094 is a new one: 	  P->bk_nextsize->fd_nextsize = FD;			       \
line 2095 is a new one: 	}							       \
line 2096 is a new one:       }	else {							       \
line 2097 is a new one: 	P->fd_nextsize->bk_nextsize = P->bk_nextsize;		       \
line 2098 is a new one: 	P->bk_nextsize->fd_nextsize = P->fd_nextsize;		       \
line 2099 is a new one:       }								       \
line 2100 is a new one:     }								       \
line 2127 is a new one: #define SMALLBIN_WIDTH    MALLOC_ALIGNMENT
line 2128 is a new one: #define MIN_LARGE_SIZE    (NSMALLBINS * SMALLBIN_WIDTH)
line 2133 is a new one: #define smallbin_index(sz) \
line 2134 is a new one:   (SMALLBIN_WIDTH == 16 ? (((unsigned)(sz)) >> 4) : (((unsigned)(sz)) >> 3))
line 2136 is a new one: #define largebin_index_32(sz)                                                \
line 2137 is a new one: (((((unsigned long)(sz)) >>  6) <= 38)?  56 + (((unsigned long)(sz)) >>  6): \
line 2144 is a new one: // XXX It remains to be seen whether it is good to keep the widths of
line 2145 is a new one: // XXX the buckets the same or whether it should be scaled by a factor
line 2146 is a new one: // XXX of two as well.
line 2147 is a new one: #define largebin_index_64(sz)                                                \
line 2148 is a new one: (((((unsigned long)(sz)) >>  6) <= 48)?  48 + (((unsigned long)(sz)) >>  6): \
line 2155 is a new one: #define largebin_index(sz) \
line 2156 is a new one:   (SIZE_SZ == 8 ? largebin_index_64 (sz) : largebin_index_32 (sz))
line 2338 is a new one:   mchunkptr        bins[NBINS * 2 - 2];
line 2361 is a new one:   /* the mmap_threshold is dynamic, until the user sets
line 2362 is a new one:      it manually, at which point we need to disable any
line 2363 is a new one:      dynamic behavior. */
line 2364 is a new one:   int              no_dyn_threshold;
line 2571 is a new one:       assert(((char*)p) < min_address || ((char*)p) >= max_address);
line 2776 is a new one:     /* The following test can only be performed for the main arena.
line 2777 is a new one:        While mallopt calls malloc_consolidate to get rid of all fast
line 2778 is a new one:        bins (especially those larger than the new maximum) this does
line 2779 is a new one:        only happen for the main arena.  Trying to do this for any
line 2780 is a new one:        other arena would mean those arenas have to be locked and
line 2781 is a new one:        malloc_consolidate be called for them.  This is excessive.  And
line 2782 is a new one:        even if this is acceptable to somebody it still cannot solve
line 2783 is a new one:        the problem completely since if the arena is locked a
line 2784 is a new one:        concurrent malloc call might create a new arena which then
line 2785 is a new one:        could use the newly invalid fast bins.  */
line 2788 is a new one:     if (av == &main_arena && i > max_fast_bin)
line 2833 is a new one: 	if (!in_smallbin_range(size))
line 2834 is a new one: 	  {
line 2835 is a new one: 	    if (p->fd_nextsize != NULL)
line 2836 is a new one: 	      {
line 2837 is a new one: 		if (p->fd_nextsize == p)
line 2838 is a new one: 		  assert (p->bk_nextsize == p);
line 2839 is a new one: 		else
line 2840 is a new one: 		  {
line 2841 is a new one: 		    if (p->fd_nextsize == first (b))
line 2842 is a new one: 		      assert (chunksize (p) < chunksize (p->fd_nextsize));
line 2843 is a new one: 		    else
line 2844 is a new one: 		      assert (chunksize (p) > chunksize (p->fd_nextsize));
line 2846 is a new one: 		    if (p == first (b))
line 2847 is a new one: 		      assert (chunksize (p) > chunksize (p->bk_nextsize));
line 2848 is a new one: 		    else
line 2849 is a new one: 		      assert (chunksize (p) < chunksize (p->bk_nextsize));
line 2850 is a new one: 		  }
line 2851 is a new one: 	      }
line 2852 is a new one: 	    else
line 2853 is a new one: 	      assert (p->bk_nextsize == NULL);
line 2854 is a new one: 	  }
line 2855 is a new one:       } else if (!in_smallbin_range(size))
line 2856 is a new one: 	assert (p->fd_nextsize == NULL && p->bk_nextsize == NULL);
line 2931 is a new one:   bool            tried_mmap = false;
line 2948 is a new one:   try_mmap:
line 2954 is a new one: #if 1
line 2955 is a new one:     /* See the front_misalign handling below, for glibc there is no
line 2956 is a new one:        need for further alignments.  */
line 2957 is a new one:     size = (nb + SIZE_SZ + pagemask) & ~pagemask;
line 2961 is a new one:     tried_mmap = true;
line 2978 is a new one: #if 1
line 2979 is a new one: 	/* For glibc, chunk2mem increases the address by 2*SIZE_SZ and
line 2980 is a new one: 	   MALLOC_ALIGN_MASK is 2*SIZE_SZ-1.  Each mmap'ed area is page
line 2981 is a new one: 	   aligned and therefore definitely MALLOC_ALIGN_MASK-aligned.  */
line 2982 is a new one:         assert (((INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK) == 0);
line 2991 is a new one:         else
line 2993 is a new one: 	  {
line 2994 is a new one: 	    p = (mchunkptr)mm;
line 2995 is a new one: 	    set_head(p, size|IS_MMAPPED);
line 2996 is a new one: 	  }
line 3053 is a new one:     if ((long) (MINSIZE + nb - old_size) > 0
line 3054 is a new one: 	&& grow_heap(old_heap, MINSIZE + nb - old_size) == 0) {
line 3094 is a new one:     else if (!tried_mmap)
line 3095 is a new one:       /* We can at least try to use to mmap memory.  */
line 3096 is a new one:       goto try_mmap;
line 3597 is a new one:     /* see if the dynamic brk/mmap threshold needs adjusting */
line 3598 is a new one:     if (!mp_.no_dyn_threshold
line 3599 is a new one: 	&& p->size > mp_.mmap_threshold
line 3600 is a new one:         && p->size <= DEFAULT_MMAP_THRESHOLD_MAX)
line 3602 is a new one: 	mp_.mmap_threshold = chunksize (p);
line 3603 is a new one: 	mp_.trim_threshold = 2 * mp_.mmap_threshold;
line 3710 is a new one:   if (newp == NULL)
line 3712 is a new one:       /* Try harder to allocate memory in other arenas.  */
line 3713 is a new one:       newp = public_mALLOc(bytes);
line 3714 is a new one:       if (newp != NULL)
line 3715 is a new one: 	{
line 3716 is a new one: 	  MALLOC_COPY (newp, oldmem, oldsize - 2 * SIZE_SZ);
line 3718 is a new one: 	  if(!mutex_trylock(&ar_ptr->mutex))
line 3719 is a new one: 	    ++(ar_ptr->stat_lock_direct);
line 3720 is a new one: 	  else {
line 3721 is a new one: 	    (void)mutex_lock(&ar_ptr->mutex);
line 3722 is a new one: 	    ++(ar_ptr->stat_lock_wait);
line 3723 is a new one: 	  }
line 3725 is a new one: 	  (void)mutex_lock(&ar_ptr->mutex);
line 3727 is a new one: 	  _int_free(ar_ptr, oldmem);
line 3728 is a new one: 	  (void)mutex_unlock(&ar_ptr->mutex);
line 4179 is a new one:     int iters = 0;
line 4207 is a new one: 	if (!in_smallbin_range(remainder_size))
line 4208 is a new one: 	  {
line 4209 is a new one: 	    remainder->fd_nextsize = NULL;
line 4210 is a new one: 	    remainder->bk_nextsize = NULL;
line 4211 is a new one: 	  }
line 4260 is a new one: 	  if ((unsigned long)(size) < (unsigned long)(bck->bk->size)) {
line 4264 is a new one: 	    victim->fd_nextsize = fwd->fd;
line 4265 is a new one: 	    victim->bk_nextsize = fwd->fd->bk_nextsize;
line 4266 is a new one: 	    fwd->fd->bk_nextsize = victim->bk_nextsize->fd_nextsize = victim;
line 4270 is a new one: 	    while ((unsigned long) size < fwd->size)
line 4271 is a new one: 	      {
line 4272 is a new one: 		fwd = fwd->fd_nextsize;
line 4273 is a new one: 		assert((fwd->size & NON_MAIN_ARENA) == 0);
line 4274 is a new one: 	      }
line 4276 is a new one: 	    if ((unsigned long) size == (unsigned long) fwd->size)
line 4277 is a new one: 	      /* Always insert in the second position.  */
line 4278 is a new one: 	      fwd = fwd->fd;
line 4279 is a new one: 	    else
line 4280 is a new one: 	      {
line 4281 is a new one: 		victim->fd_nextsize = fwd;
line 4282 is a new one: 		victim->bk_nextsize = fwd->bk_nextsize;
line 4283 is a new one: 		fwd->bk_nextsize = victim;
line 4284 is a new one: 		victim->bk_nextsize->fd_nextsize = victim;
line 4285 is a new one: 	      }
line 4286 is a new one: 	    bck = fwd->bk;
line 4288 is a new one: 	} else
line 4289 is a new one: 	  victim->fd_nextsize = victim->bk_nextsize = victim;
line 4298 is a new one: #define MAX_ITERS	10000
line 4299 is a new one:       if (++iters >= MAX_ITERS)
line 4300 is a new one: 	break;
line 4305 is a new one:       sorted order to find smallest that fits.  Use the skip list for this.
line 4312 is a new one:       if ((victim = first(bin)) != bin &&
line 4313 is a new one:           (unsigned long)(victim->size) >= (unsigned long)(nb)) {
line 4315 is a new one: 	victim = victim->bk_nextsize;
line 4318 is a new one:           victim = victim->bk_nextsize;
line 4320 is a new one: 	/* Avoid removing the first entry for a size so that the skip
line 4321 is a new one: 	   list does not have to be rerouted.  */
line 4322 is a new one: 	if (victim != last(bin) && victim->size == victim->fd->size)
line 4323 is a new one: 	  victim = victim->fd;
line 4337 is a new one:           /* We cannot assume the unsorted list is empty and therefore
line 4338 is a new one:              have to perform a complete insert here.  */
line 4339 is a new one: 	  bck = unsorted_chunks(av);
line 4340 is a new one: 	  fwd = bck->fd;
line 4341 is a new one: 	  remainder->bk = bck;
line 4342 is a new one: 	  remainder->fd = fwd;
line 4343 is a new one: 	  bck->fd = remainder;
line 4344 is a new one: 	  fwd->bk = remainder;
line 4345 is a new one: 	  if (!in_smallbin_range(remainder_size))
line 4346 is a new one: 	    {
line 4347 is a new one: 	      remainder->fd_nextsize = NULL;
line 4348 is a new one: 	      remainder->bk_nextsize = NULL;
line 4432 is a new one: 	  /* We cannot assume the unsorted list is empty and therefore
line 4433 is a new one: 	     have to perform a complete insert here.  */
line 4434 is a new one: 	  bck = unsorted_chunks(av);
line 4435 is a new one: 	  fwd = bck->fd;
line 4436 is a new one: 	  remainder->bk = bck;
line 4437 is a new one: 	  remainder->fd = fwd;
line 4438 is a new one: 	  bck->fd = remainder;
line 4439 is a new one: 	  fwd->bk = remainder;
line 4444 is a new one: 	  if (!in_smallbin_range(remainder_size))
line 4445 is a new one: 	    {
line 4446 is a new one: 	      remainder->fd_nextsize = NULL;
line 4447 is a new one: 	      remainder->bk_nextsize = NULL;
line 4673 is a new one:       if (!in_smallbin_range(size))
line 4674 is a new one: 	{
line 4675 is a new one: 	  p->fd_nextsize = NULL;
line 4676 is a new one: 	  p->bk_nextsize = NULL;
line 4803 is a new one:     /* It is wrong to limit the fast bins to search using get_max_fast
line 4804 is a new one:        because, except for the main arena, all the others might have
line 4805 is a new one:        blocks in the high fast bins.  It's not worth it anyway, just
line 4806 is a new one:        search all bins all the time.  */
line 4809 is a new one:     maxfb = &(av->fastbins[NFASTBINS - 1]);
line 4845 is a new one:             if (!in_smallbin_range (size)) {
line 4846 is a new one: 	      p->fd_nextsize = NULL;
line 4847 is a new one: 	      p->bk_nextsize = NULL;
line 5687 is a new one:     mp_.no_dyn_threshold = 1;
line 5692 is a new one:     mp_.no_dyn_threshold = 1;
line 5703 is a new one:       mp_.no_dyn_threshold = 1;
line 5713 is a new one:       mp_.no_dyn_threshold = 1;
