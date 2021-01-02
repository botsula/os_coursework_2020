Comparison of files: malloc_v2_22.c and malloc_v2_20.c
line 1 is a new one:    Copyright (C) 1996-2015 Free Software Foundation, Inc.
line 243 is a new one: /* For ALIGN_UP.  */
line 244 is a new one: #include <libc-internal.h>
line 1061 is a new one: static void malloc_printerr(int action, const char *str, void *ptr, mstate av);
line 1413 is a new one: #define unlink(AV, P, BK, FD) {                                            \
line 1417 is a new one:       malloc_printerr (check_action, "corrupted double-linked list", P, AV);  \
line 1423 is a new one: 	    if (__builtin_expect (P->fd_nextsize->bk_nextsize != P, 0)	      \
line 1424 is a new one: 		|| __builtin_expect (P->bk_nextsize->fd_nextsize != P, 0))    \
line 1425 is a new one: 	      malloc_printerr (check_action,				      \
line 1426 is a new one: 			       "corrupted double-linked list (not small)",    \
line 1427 is a new one: 			       P, AV);					      \
line 1659 is a new one: /* ARENA_CORRUPTION_BIT is set if a memory corruption was detected on the
line 1660 is a new one:    arena.  Such an arena is no longer used to allocate chunks.  Chunks
line 1661 is a new one:    allocated in that arena before detecting corruption are not freed.  */
line 1663 is a new one: #define ARENA_CORRUPTION_BIT (4U)
line 1665 is a new one: #define arena_is_corrupt(A)	(((A)->flags & ARENA_CORRUPTION_BIT))
line 1666 is a new one: #define set_arena_corrupt(A)	((A)->flags |= ARENA_CORRUPTION_BIT)
line 2126 is a new one:   assert (powerof2(GLRO (dl_pagesize)));
line 2281 is a new one:   size_t pagesize = GLRO (dl_pagesize);
line 2292 is a new one:   if (av == NULL
line 2293 is a new one:       || ((unsigned long) (nb) >= (unsigned long) (mp_.mmap_threshold)
line 2294 is a new one: 	  && (mp_.n_mmaps < mp_.n_mmaps_max)))
line 2308 is a new one:         size = ALIGN_UP (nb + SIZE_SZ, pagesize);
line 2310 is a new one:         size = ALIGN_UP (nb + SIZE_SZ + MALLOC_ALIGN_MASK, pagesize);
line 2367 is a new one:   /* There are no usable arenas and mmap also failed.  */
line 2368 is a new one:   if (av == NULL)
line 2387 is a new one:            ((unsigned long) old_end & (pagesize - 1)) == 0));
line 2467 is a new one:       size = ALIGN_UP (size, pagesize);
line 2501 is a new one:             size = ALIGN_UP (size + old_size, pagesize);
line 2545 is a new one:               malloc_printerr (3, "break adjusted to free malloc space", brk,
line 2546 is a new one: 			       av);
line 2608 is a new one:                   correction += (ALIGN_UP (end_misalign, pagesize)) - end_misalign;
line 2759 is a new one:   size_t pagesize;
line 2762 is a new one:   pagesize = GLRO (dl_pagesize);
line 2770 is a new one:   extra = (top_area - pad) & ~(pagesize - 1);
line 2836 is a new one:                        chunk2mem (p), NULL);
line 2855 is a new one:   size_t pagesize = GLRO (dl_pagesize);
line 2864 is a new one:   new_size = ALIGN_UP (new_size + offset + SIZE_SZ, pagesize);
line 2904 is a new one:   arena_get (ar_ptr, bytes);
line 2907 is a new one:   /* Retry with another arena only if we were able to find a usable arena
line 2908 is a new one:      before.  */
line 2909 is a new one:   if (!victim && ar_ptr != NULL)
line 2913 is a new one:       victim = _int_malloc (ar_ptr, bytes);
line 2916 is a new one:   if (ar_ptr != NULL)
line 2995 is a new one:     ar_ptr = NULL;
line 2997 is a new one:     ar_ptr = arena_for_chunk (oldp);
line 3006 is a new one:       malloc_printerr (check_action, "realloc(): invalid pointer", oldmem,
line 3007 is a new one: 		       ar_ptr);
line 3114 is a new one:   if (!p && ar_ptr != NULL)
line 3118 is a new one:       p = _int_memalign (ar_ptr, alignment, bytes);
line 3121 is a new one:   if (ar_ptr != NULL)
line 3139 is a new one:   size_t pagesize = GLRO (dl_pagesize);
line 3140 is a new one:   return _mid_memalign (pagesize, bytes, address);
line 3150 is a new one:   size_t pagesize = GLRO (dl_pagesize);
line 3151 is a new one:   size_t rounded_bytes = ALIGN_UP (bytes, pagesize);
line 3154 is a new one:   if (bytes > SIZE_MAX - 2 * pagesize - MINSIZE)
line 3160 is a new one:   return _mid_memalign (pagesize, rounded_bytes, address);
line 3202 is a new one:   if (av)
line 3204 is a new one:       /* Check if we hand out the top chunk, in which case there may be no
line 3205 is a new one: 	 need to clear. */
line 3207 is a new one:       oldtop = top (av);
line 3208 is a new one:       oldtopsize = chunksize (top (av));
line 3210 is a new one:       /* Only newly allocated memory is guaranteed to be cleared.  */
line 3211 is a new one:       if (av == &main_arena &&
line 3212 is a new one: 	  oldtopsize < mp_.sbrk_base + av->max_system_mem - (char *) oldtop)
line 3213 is a new one: 	oldtopsize = (mp_.sbrk_base + av->max_system_mem - (char *) oldtop);
line 3215 is a new one:       if (av != &main_arena)
line 3217 is a new one: 	  heap_info *heap = heap_for_ptr (oldtop);
line 3218 is a new one: 	  if (oldtopsize < (char *) heap + heap->mprotect_size - (char *) oldtop)
line 3219 is a new one: 	    oldtopsize = (char *) heap + heap->mprotect_size - (char *) oldtop;
line 3225 is a new one:       /* No usable arenas.  */
line 3226 is a new one:       oldtop = 0;
line 3227 is a new one:       oldtopsize = 0;
line 3235 is a new one:   if (mem == 0 && av != NULL)
line 3239 is a new one:       mem = _int_malloc (av, sz);
line 3242 is a new one:   if (av != NULL)
line 3245 is a new one:   /* Allocation failed even after a retry.  */
line 3344 is a new one:   /* There are no usable arenas.  Fall back to sysmalloc to get a chunk from
line 3345 is a new one:      mmap.  */
line 3346 is a new one:   if (__glibc_unlikely (av == NULL))
line 3348 is a new one:       void *p = sysmalloc (nb, av);
line 3349 is a new one:       if (p != NULL)
line 3350 is a new one: 	alloc_perturb (p, bytes);
line 3351 is a new one:       return p;
line 3379 is a new one:               malloc_printerr (check_action, errstr, chunk2mem (victim), av);
line 3468 is a new one:                              chunk2mem (victim), av);
line 3615 is a new one:               unlink (av, victim, bck, fwd);
line 3720 is a new one:               unlink (av, victim, bck, fwd);
line 3860 is a new one:       malloc_printerr (check_action, errstr, chunk2mem (p), av);
line 3998 is a new one:       unlink(av, p, bck, fwd);
line 4007 is a new one: 	unlink(av, nextchunk, bck, fwd);
line 4168 is a new one: 	    unlink(av, p, bck, fwd);
line 4176 is a new one: 	      unlink(av, nextchunk, bck, fwd);
line 4245 is a new one:       malloc_printerr (check_action, errstr, chunk2mem (oldp), av);
line 4291 is a new one:           unlink (av, next, bck, fwd);
line 4486 is a new one:   /* Don't touch corrupt arenas.  */
line 4487 is a new one:   if (arena_is_corrupt (av))
line 4980 is a new one: malloc_printerr (int action, const char *str, void *ptr, mstate ar_ptr)
line 4982 is a new one:   /* Avoid using this arena in future.  We do not attempt to synchronize this
line 4983 is a new one:      with anything else because we minimally want to ensure that __libc_message
line 4984 is a new one:      gets its resources safely without stumbling on the current corruption.  */
line 4985 is a new one:   if (ar_ptr)
line 4986 is a new one:     set_arena_corrupt (ar_ptr);
line 5015 is a new one:       || !powerof2 (alignment / sizeof (void *))
line 5035 is a new one: __malloc_info (int options, FILE *fp)
line 5208 is a new one: weak_alias (__malloc_info, malloc_info)
