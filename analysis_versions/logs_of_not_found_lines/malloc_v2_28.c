Comparison of files: malloc_v2_28.c and malloc_v2_26.c
line 1 is a new one:    Copyright (C) 1996-2018 Free Software Foundation, Inc.
line 225 is a new one: #include <assert.h>
line 246 is a new one: /* For SINGLE_THREAD_P.  */
line 247 is a new one: #include <sysdep-cancel.h>
line 281 is a new one: #ifndef NDEBUG
line 282 is a new one: # define __assert_fail(assertion, file, line, function)			\
line 283 is a new one: 	 __malloc_assert(assertion, file, line, function)
line 998 is a new one: static void malloc_printerr(const char *str) __attribute__ ((noreturn));
line 1000 is a new one: static void* mem2mem_check(void *p, size_t sz);
line 1001 is a new one: static void top_check(void);
line 1002 is a new one: static void munmap_chunk(mchunkptr p);
line 1004 is a new one: static mchunkptr mremap_chunk(mchunkptr p, size_t new_size);
line 1207 is a new one: /* Same, except also perform an argument and result check.  First, we check
line 1208 is a new one:    that the padding done by request2size didn't result in an integer
line 1209 is a new one:    overflow.  Then we check (using REQUEST_OUT_OF_RANGE) that the resulting
line 1210 is a new one:    size isn't so large that a later alignment would lead to another integer
line 1211 is a new one:    overflow.  */
line 1212 is a new one: #define checked_request2size(req, sz) \
line 1213 is a new one: ({				    \
line 1214 is a new one:   (sz) = request2size (req);	    \
line 1215 is a new one:   if (((sz) < (req))		    \
line 1216 is a new one:       || REQUEST_OUT_OF_RANGE (sz)) \
line 1217 is a new one:     {				    \
line 1218 is a new one:       __set_errno (ENOMEM);	    \
line 1219 is a new one:       return 0;			    \
line 1220 is a new one:     }				    \
line 1221 is a new one: })
line 1273 is a new one: /* Size of the chunk below P.  Only valid if !prev_inuse (P).  */
line 1276 is a new one: /* Set the size of the chunk below P.  Only valid if !prev_inuse (P).  */
line 1279 is a new one: /* Ptr to previous physical malloc_chunk.  Only valid if !prev_inuse (P).  */
line 1389 is a new one:       malloc_printerr ("corrupted size vs. prev_size");			      \
line 1393 is a new one:       malloc_printerr ("corrupted double-linked list");			      \
line 1401 is a new one: 	      malloc_printerr ("corrupted double-linked list (not small)");   \
line 1618 is a new one:    Precondition: there are no existing fastbin chunks in the main arena.
line 1619 is a new one:    Since do_check_malloc_state () checks this, we call malloc_consolidate ()
line 1620 is a new one:    before changing max_fast.  Note other arenas will leak their fast bin
line 1621 is a new one:    entries if max_fast is reduced.
line 1628 is a new one: static inline INTERNAL_SIZE_T
line 1629 is a new one: get_max_fast (void)
line 1631 is a new one:   /* Tell the GCC optimizers that global_max_fast is never larger
line 1632 is a new one:      than MAX_FAST_SIZE.  This avoids out-of-bounds array accesses in
line 1633 is a new one:      _int_malloc after constant propagation of the size parameter.
line 1634 is a new one:      (The code never executes because malloc preserves the
line 1635 is a new one:      global_max_fast invariant, but the optimizers may not recognize
line 1636 is a new one:      this.)  */
line 1637 is a new one:   if (global_max_fast > MAX_FAST_SIZE)
line 1638 is a new one:     __builtin_unreachable ();
line 1639 is a new one:   return global_max_fast;
line 1647 is a new one:    have_fastchunks indicates that there are probably some fastbin chunks.
line 1648 is a new one:    It is set true on entering a chunk into any fastbin, and cleared early in
line 1649 is a new one:    malloc_consolidate.  The value is approximate since it may be set when there
line 1650 is a new one:    are no fastbin chunks, or it may be clear even if there are fastbin chunks
line 1651 is a new one:    available.  Given it's sole purpose is to reduce number of redundant calls to
line 1652 is a new one:    malloc_consolidate, it does not affect correctness.  As a result we can safely
line 1653 is a new one:    use relaxed atomic accesses.
line 1665 is a new one:   /* Set if the fastbin chunks contain recently inserted free blocks.  */
line 1666 is a new one:   /* Note this is a bool but not all targets support atomics on booleans.  */
line 1667 is a new one:   int have_fastchunks;
line 1786 is a new one:    This is called from ptmalloc_init () or from _int_new_arena ()
line 1787 is a new one:    when creating a new arena.
line 1809 is a new one:   atomic_store_relaxed (&av->have_fastchunks, false);
line 1859 is a new one: /* This function is called from the arena shutdown hook, to free the
line 1860 is a new one:    thread cache (if it exists).  */
line 1861 is a new one: static void tcache_thread_shutdown (void);
line 1968 is a new one:   INTERNAL_SIZE_T sz = chunksize_nomask (p) & ~(PREV_INUSE | NON_MAIN_ARENA);
line 1983 is a new one:       assert (prev_size (next_chunk (p)) == sz);
line 2043 is a new one:   INTERNAL_SIZE_T sz = chunksize_nomask (p) & ~(PREV_INUSE | NON_MAIN_ARENA);
line 2119 is a new one:   /* Check the arena is initialized. */
line 2120 is a new one:   assert (av->top != 0);
line 2122 is a new one:   /* No memory has been allocated yet, so doing more tests is not possible.  */
line 2123 is a new one:   if (av->top == initial_top (av))
line 2538 is a new one: 	    /* Oops!  Someone else killed our space..  Can't touch anything.  */
line 2539 is a new one: 	    malloc_printerr ("break adjusted to free malloc space");
line 2829 is a new one:     malloc_printerr ("munmap_chunk(): invalid pointer");
line 2903 is a new one: static __thread bool tcache_shutting_down = false;
line 2908 is a new one: static __always_inline void
line 2920 is a new one: static __always_inline void *
line 2932 is a new one: tcache_thread_shutdown (void)
line 2940 is a new one:   /* Disable the tcache and prevent it from being reinitialized.  */
line 2942 is a new one:   tcache_shutting_down = true;
line 2944 is a new one:   /* Free all of the entries and the tcache itself back to the arena
line 2945 is a new one:      heap for coalescing.  */
line 2994 is a new one: # define MAYBE_INIT_TCACHE() \
line 2998 is a new one: #else  /* !USE_TCACHE */
line 2999 is a new one: # define MAYBE_INIT_TCACHE()
line 3002 is a new one: tcache_thread_shutdown (void)
line 3004 is a new one:   /* Nothing to do if there is no thread cache.  */
line 3007 is a new one: #endif /* !USE_TCACHE  */
line 3021 is a new one:   size_t tbytes;
line 3022 is a new one:   checked_request2size (bytes, tbytes);
line 3038 is a new one:   if (SINGLE_THREAD_P)
line 3040 is a new one:       victim = _int_malloc (&main_arena, bytes);
line 3041 is a new one:       assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
line 3042 is a new one: 	      &main_arena == arena_for_chunk (mem2chunk (victim)));
line 3043 is a new one:       return victim;
line 3157 is a new one:       malloc_printerr ("realloc(): invalid pointer");
line 3202 is a new one:   if (SINGLE_THREAD_P)
line 3204 is a new one:       newp = _int_realloc (ar_ptr, oldp, oldsize, nb);
line 3205 is a new one:       assert (!newp || chunk_is_mmapped (mem2chunk (newp)) ||
line 3206 is a new one: 	      ar_ptr == arena_for_chunk (mem2chunk (newp)));
line 3208 is a new one:       return newp;
line 3286 is a new one:   if (SINGLE_THREAD_P)
line 3288 is a new one:       p = _int_memalign (&main_arena, alignment, bytes);
line 3289 is a new one:       assert (!p || chunk_is_mmapped (mem2chunk (p)) ||
line 3290 is a new one: 	      &main_arena == arena_for_chunk (mem2chunk (p)));
line 3387 is a new one:   if (SINGLE_THREAD_P)
line 3388 is a new one:     av = &main_arena;
line 3390 is a new one:     arena_get (av, sz);
line 3424 is a new one:   if (!SINGLE_THREAD_P)
line 3426 is a new one:       if (mem == 0 && av != NULL)
line 3428 is a new one: 	  LIBC_PROBE (memory_calloc_retry, 1, sz);
line 3429 is a new one: 	  av = arena_get_retry (av, sz);
line 3430 is a new one: 	  mem = _int_malloc (av, sz);
line 3433 is a new one:       if (av != NULL)
line 3434 is a new one: 	__libc_lock_unlock (av->mutex);
line 3568 is a new one:       mchunkptr pp;
line 3569 is a new one:       victim = *fb;
line 3571 is a new one:       if (victim != NULL)
line 3573 is a new one: 	  if (SINGLE_THREAD_P)
line 3574 is a new one: 	    *fb = victim->fd;
line 3576 is a new one: 	    REMOVE_FB (fb, pp, victim);
line 3577 is a new one: 	  if (__glibc_likely (victim != NULL))
line 3579 is a new one: 	      size_t victim_idx = fastbin_index (chunksize (victim));
line 3580 is a new one: 	      if (__builtin_expect (victim_idx != idx, 0))
line 3581 is a new one: 		malloc_printerr ("malloc(): memory corruption (fast)");
line 3582 is a new one: 	      check_remalloced_chunk (av, victim, nb);
line 3584 is a new one: 	      /* While we're here, if we see other chunks of the same size,
line 3585 is a new one: 		 stash them in the tcache.  */
line 3586 is a new one: 	      size_t tc_idx = csize2tidx (nb);
line 3587 is a new one: 	      if (tcache && tc_idx < mp_.tcache_bins)
line 3589 is a new one: 		  mchunkptr tc_victim;
line 3591 is a new one: 		  /* While bin not empty and tcache not full, copy chunks.  */
line 3592 is a new one: 		  while (tcache->counts[tc_idx] < mp_.tcache_count
line 3593 is a new one: 			 && (tc_victim = *fb) != NULL)
line 3595 is a new one: 		      if (SINGLE_THREAD_P)
line 3596 is a new one: 			*fb = tc_victim->fd;
line 3597 is a new one: 		      else
line 3598 is a new one: 			{
line 3599 is a new one: 			  REMOVE_FB (fb, pp, tc_victim);
line 3600 is a new one: 			  if (__glibc_unlikely (tc_victim == NULL))
line 3601 is a new one: 			    break;
line 3602 is a new one: 			}
line 3604 is a new one: 		    }
line 3607 is a new one: 	      void *p = chunk2mem (victim);
line 3608 is a new one: 	      alloc_perturb (p, bytes);
line 3609 is a new one: 	      return p;
line 3630 is a new one: 	  if (__glibc_unlikely (bck->fd != victim))
line 3631 is a new one: 	    malloc_printerr ("malloc(): smallbin double linked list corrupted");
line 3632 is a new one:           set_inuse_bit_at_offset (victim, nb);
line 3633 is a new one:           bin->bk = bck;
line 3634 is a new one:           bck->fd = bin;
line 3636 is a new one:           if (av != &main_arena)
line 3637 is a new one: 	    set_non_main_arena (victim);
line 3685 is a new one:       if (atomic_load_relaxed (&av->have_fastchunks))
line 3721 is a new one:             malloc_printerr ("malloc(): memory corruption");
line 3761 is a new one:           if (__glibc_unlikely (bck->fd != victim))
line 3762 is a new one:             malloc_printerr ("malloc(): corrupted unsorted chunks 3");
line 3928 is a new one: 		  if (__glibc_unlikely (fwd->bk != bck))
line 3929 is a new one: 		    malloc_printerr ("malloc(): corrupted unsorted chunks");
line 4032 is a new one: 		  if (__glibc_unlikely (fwd->bk != bck))
line 4033 is a new one: 		    malloc_printerr ("malloc(): corrupted unsorted chunks 2");
line 4095 is a new one:       else if (atomic_load_relaxed (&av->have_fastchunks))
line 4142 is a new one:     malloc_printerr ("free(): invalid pointer");
line 4146 is a new one:     malloc_printerr ("free(): invalid size");
line 4185 is a new one: 	bool fail = true;
line 4187 is a new one: 	   of system_mem might result in a false positive.  Redo the test after
line 4188 is a new one: 	   getting the lock.  */
line 4189 is a new one: 	if (!have_lock)
line 4191 is a new one: 	    __libc_lock_lock (av->mutex);
line 4192 is a new one: 	    fail = (chunksize_nomask (chunk_at_offset (p, size)) <= 2 * SIZE_SZ
line 4193 is a new one: 		    || chunksize (chunk_at_offset (p, size)) >= av->system_mem);
line 4197 is a new one: 	if (fail)
line 4198 is a new one: 	  malloc_printerr ("free(): invalid next size (fast)");
line 4203 is a new one:     atomic_store_relaxed (&av->have_fastchunks, true);
line 4210 is a new one:     if (SINGLE_THREAD_P)
line 4212 is a new one: 	/* Check that the top of the bin is not the record we are going to
line 4213 is a new one: 	   add (i.e., double free).  */
line 4215 is a new one: 	  malloc_printerr ("double free or corruption (fasttop)");
line 4216 is a new one: 	p->fd = old;
line 4217 is a new one: 	*fb = p;
line 4220 is a new one:       do
line 4222 is a new one: 	  /* Check that the top of the bin is not the record we are going to
line 4223 is a new one: 	     add (i.e., double free).  */
line 4224 is a new one: 	  if (__builtin_expect (old == p, 0))
line 4225 is a new one: 	    malloc_printerr ("double free or corruption (fasttop)");
line 4226 is a new one: 	  p->fd = old2 = old;
line 4228 is a new one:       while ((old = catomic_compare_and_exchange_val_rel (fb, p, old2))
line 4229 is a new one: 	     != old2);
line 4231 is a new one:     /* Check that size of fastbin chunk at the top is the same as
line 4232 is a new one:        size of the chunk that we are adding.  We can dereference OLD
line 4233 is a new one:        only if we have the lock, otherwise it might have already been
line 4234 is a new one:        allocated again.  */
line 4235 is a new one:     if (have_lock && old != NULL
line 4236 is a new one: 	&& __builtin_expect (fastbin_index (chunksize (old)) != idx, 0))
line 4237 is a new one:       malloc_printerr ("invalid fastbin entry (free)");
line 4246 is a new one:     /* If we're single-threaded, don't lock the arena.  */
line 4247 is a new one:     if (SINGLE_THREAD_P)
line 4248 is a new one:       have_lock = true;
line 4250 is a new one:     if (!have_lock)
line 4258 is a new one:       malloc_printerr ("double free or corruption (top)");
line 4263 is a new one: 	malloc_printerr ("double free or corruption (out)");
line 4266 is a new one:       malloc_printerr ("double free or corruption (!prev)");
line 4271 is a new one:       malloc_printerr ("free(): invalid next size (normal)");
line 4303 is a new one: 	malloc_printerr ("free(): corrupted unsorted chunks");
line 4346 is a new one:       if (atomic_load_relaxed (&av->have_fastchunks))
line 4365 is a new one:     if (!have_lock)
line 4405 is a new one:   atomic_store_relaxed (&av->have_fastchunks, false);
line 4407 is a new one:   unsorted_bin = unsorted_chunks(av);
line 4410 is a new one:     Remove each chunk from fast bin and consolidate it, placing it
line 4411 is a new one:     then in unsorted bin. Among other reasons for doing this,
line 4412 is a new one:     placing in unsorted bin avoids needing to calculate actual bins
line 4413 is a new one:     until malloc is sure that chunks aren't immediately going to be
line 4414 is a new one:     reused anyway.
line 4417 is a new one:   maxfb = &fastbin (av, NFASTBINS - 1);
line 4418 is a new one:   fb = &fastbin (av, 0);
line 4419 is a new one:   do {
line 4420 is a new one:     p = atomic_exchange_acq (fb, NULL);
line 4421 is a new one:     if (p != 0) {
line 4422 is a new one:       do {
line 4424 is a new one: 	  unsigned int idx = fastbin_index (chunksize (p));
line 4425 is a new one: 	  if ((&fastbin (av, idx)) != fb)
line 4426 is a new one: 	    malloc_printerr ("malloc_consolidate(): invalid chunk size");
line 4429 is a new one: 	check_inuse_chunk(av, p);
line 4430 is a new one: 	nextp = p->fd;
line 4432 is a new one: 	/* Slightly streamlined version of consolidation code in free() */
line 4433 is a new one: 	size = chunksize (p);
line 4434 is a new one: 	nextchunk = chunk_at_offset(p, size);
line 4435 is a new one: 	nextsize = chunksize(nextchunk);
line 4437 is a new one: 	if (!prev_inuse(p)) {
line 4438 is a new one: 	  prevsize = prev_size (p);
line 4439 is a new one: 	  size += prevsize;
line 4440 is a new one: 	  p = chunk_at_offset(p, -((long) prevsize));
line 4441 is a new one: 	  unlink(av, p, bck, fwd);
line 4444 is a new one: 	if (nextchunk != av->top) {
line 4445 is a new one: 	  nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
line 4447 is a new one: 	  if (!nextinuse) {
line 4449 is a new one: 	    unlink(av, nextchunk, bck, fwd);
line 4450 is a new one: 	  } else
line 4451 is a new one: 	    clear_inuse_bit_at_offset(nextchunk, 0);
line 4453 is a new one: 	  first_unsorted = unsorted_bin->fd;
line 4454 is a new one: 	  unsorted_bin->fd = p;
line 4455 is a new one: 	  first_unsorted->bk = p;
line 4457 is a new one: 	  if (!in_smallbin_range (size)) {
line 4458 is a new one: 	    p->fd_nextsize = NULL;
line 4459 is a new one: 	    p->bk_nextsize = NULL;
line 4462 is a new one: 	  set_head(p, size | PREV_INUSE);
line 4463 is a new one: 	  p->bk = unsorted_bin;
line 4464 is a new one: 	  p->fd = first_unsorted;
line 4465 is a new one: 	  set_foot(p, size);
line 4468 is a new one: 	else {
line 4469 is a new one: 	  size += nextsize;
line 4470 is a new one: 	  set_head(p, size | PREV_INUSE);
line 4471 is a new one: 	  av->top = p;
line 4474 is a new one:       } while ( (p = nextp) != 0);
line 4477 is a new one:   } while (fb++ != maxfb);
line 4508 is a new one:     malloc_printerr ("realloc(): invalid old size");
line 4519 is a new one:     malloc_printerr ("realloc(): invalid next size");
line 4671 is a new one:   if (nb > SIZE_MAX - alignment - MINSIZE)
line 4751 is a new one:   /* Ensure all blocks are consolidated.  */
line 4968 is a new one:   int old_flags2 = stderr->_flags2;
line 4969 is a new one:   stderr->_flags2 |= _IO_FLAGS2_NOTCANCEL;
line 4997 is a new one:   stderr->_flags2 = old_flags2;
line 5133 is a new one:   /* We must consolidate main arena before changing max_fast
line 5134 is a new one:      (see definition of set_max_fast).  */
line 5333 is a new one: malloc_printerr (const char *str)
line 5335 is a new one:   __libc_message (do_abort, "%s\n", str);
line 5336 is a new one:   __builtin_unreachable ();
line 5470 is a new one:       size_t heap_size = 0;
line 5471 is a new one:       size_t heap_mprotect_size = 0;
line 5472 is a new one:       size_t heap_count = 0;
line 5475 is a new one: 	  /* Iterate over the arena heaps from back to front.  */
line 5477 is a new one: 	  do
line 5479 is a new one: 	      heap_size += heap->size;
line 5480 is a new one: 	      heap_mprotect_size += heap->mprotect_size;
line 5481 is a new one: 	      heap = heap->prev;
line 5482 is a new one: 	      ++heap_count;
line 5484 is a new one: 	  while (heap != NULL);
line 5522 is a new one: 		   "<aspace type=\"mprotect\" size=\"%zu\"/>\n"
line 5523 is a new one: 		   "<aspace type=\"subheaps\" size=\"%zu\"/>\n",
line 5524 is a new one: 		   heap_size, heap_mprotect_size, heap_count);
line 5525 is a new one: 	  total_aspace += heap_size;
line 5526 is a new one: 	  total_aspace_mprotect += heap_mprotect_size;
