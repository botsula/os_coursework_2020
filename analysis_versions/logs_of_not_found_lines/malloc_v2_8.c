Comparison of files: malloc_v2_8.c and malloc_v2_6.c
line 1 is a new one:    Copyright (C) 1996-2006, 2007, 2008 Free Software Foundation, Inc.
line 1188 is a new one:   return 0.
line 1594 is a new one: static int      mTRIm(mstate, size_t);
line 2810 is a new one:       unsigned int binbit = get_binmap(av,i);
line 2811 is a new one:       int empty = last(b) == b;
line 3503 is a new one:   /* No need to remap if the number of pages does not change.  */
line 3504 is a new one:   if (size + offset == new_size)
line 3505 is a new one:     return p;
line 3555 is a new one:       ar_ptr = &main_arena;
line 3556 is a new one:       (void)mutex_lock(&ar_ptr->mutex);
line 3557 is a new one:       victim = _int_malloc(ar_ptr, bytes);
line 3767 is a new one:       ar_ptr = &main_arena;
line 3768 is a new one:       (void)mutex_lock(&ar_ptr->mutex);
line 3769 is a new one:       p = _int_memalign(ar_ptr, alignment, bytes);
line 3774 is a new one:       mstate prev = ar_ptr->next ? ar_ptr : 0;
line 3776 is a new one:       ar_ptr = arena_get2(prev, bytes);
line 3895 is a new one:       heap_info *heap = heap_for_ptr (oldtop);
line 3896 is a new one:       if (oldtopsize < (char *) heap + heap->mprotect_size - (char *) oldtop)
line 3897 is a new one: 	oldtopsize = (char *) heap + heap->mprotect_size - (char *) oldtop;
line 4024 is a new one:   int result = 0;
line 4029 is a new one:   mstate ar_ptr = &main_arena;
line 4030 is a new one:   do
line 4032 is a new one:       (void) mutex_lock (&ar_ptr->mutex);
line 4033 is a new one:       result |= mTRIm (ar_ptr, s);
line 4034 is a new one:       (void) mutex_unlock (&ar_ptr->mutex);
line 4036 is a new one:       ar_ptr = ar_ptr->next;
line 4038 is a new one:   while (ar_ptr != &main_arena);
line 4495 is a new one:       exhausted by current request, it is replenished. (The main
line 4535 is a new one:       if (p != NULL && __builtin_expect (perturb_byte, 0))
line 5509 is a new one: static int mTRIm(mstate av, size_t pad)
line 5511 is a new one: static int mTRIm(av, pad) mstate av; size_t pad;
line 5515 is a new one:   malloc_consolidate (av);
line 5517 is a new one:   const size_t ps = mp_.pagesize;
line 5518 is a new one:   int psindex = bin_index (ps);
line 5519 is a new one:   const size_t psm1 = ps - 1;
line 5521 is a new one:   int result = 0;
line 5522 is a new one:   for (int i = 1; i < NBINS; ++i)
line 5523 is a new one:     if (i == 1 || i >= psindex)
line 5525 is a new one:         mbinptr bin = bin_at (av, i);
line 5527 is a new one:         for (mchunkptr p = last (bin); p != bin; p = p->bk)
line 5529 is a new one: 	    INTERNAL_SIZE_T size = chunksize (p);
line 5531 is a new one: 	    if (size > psm1 + sizeof (struct malloc_chunk))
line 5533 is a new one: 		/* See whether the chunk contains at least one unused page.  */
line 5534 is a new one: 		char *paligned_mem = (char *) (((uintptr_t) p
line 5535 is a new one: 						+ sizeof (struct malloc_chunk)
line 5536 is a new one: 						+ psm1) & ~psm1);
line 5538 is a new one: 		assert ((char *) chunk2mem (p) + 4 * SIZE_SZ <= paligned_mem);
line 5539 is a new one: 		assert ((char *) p + size > paligned_mem);
line 5541 is a new one: 		/* This is the size we could potentially free.  */
line 5542 is a new one: 		size -= paligned_mem - (char *) p;
line 5544 is a new one: 		if (size > psm1)
line 5546 is a new one: #ifdef MALLOC_DEBUG
line 5547 is a new one: 		    /* When debugging we simulate destroying the memory
line 5548 is a new one: 		       content.  */
line 5549 is a new one: 		    memset (paligned_mem, 0x89, size & ~psm1);
line 5551 is a new one: 		    madvise (paligned_mem, size & ~psm1, MADV_DONTNEED);
line 5553 is a new one: 		    result = 1;
line 5560 is a new one:   return result | (av == &main_arena ? sYSTRIm (pad, av) : 0);
