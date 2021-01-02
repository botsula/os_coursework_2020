Comparison of files: malloc_v2_30.c and malloc_v2_28.c
line 1 is a new one:    Copyright (C) 1996-2019 Free Software Foundation, Inc.
line 324 is a new one: /* Maximum chunks in tcache bins for tunables.  This value must fit the range
line 325 is a new one:    of tcache->counts[] entries, else they may overflow.  */
line 326 is a new one: # define MAX_TCACHE_COUNT UINT16_MAX
line 1200 is a new one: /* Check if REQ overflows when padded and aligned and if the resulting value
line 1201 is a new one:    is less than PTRDIFF_T.  Returns TRUE and the requested size or MINSIZE in
line 1202 is a new one:    case the value is less than MINSIZE on SZ or false if any of the previous
line 1203 is a new one:    check fail.  */
line 1204 is a new one: static inline bool
line 1205 is a new one: checked_request2size (size_t req, size_t *sz) __nonnull (1)
line 1207 is a new one:   if (__glibc_unlikely (req > PTRDIFF_MAX))
line 1208 is a new one:     return false;
line 1209 is a new one:   *sz = request2size (req);
line 1210 is a new one:   return true;
line 1448 is a new one: /* Take a chunk off a bin list.  */
line 1450 is a new one: unlink_chunk (mstate av, mchunkptr p)
line 1452 is a new one:   if (chunksize (p) != prev_size (next_chunk (p)))
line 1453 is a new one:     malloc_printerr ("corrupted size vs. prev_size");
line 1455 is a new one:   mchunkptr fd = p->fd;
line 1456 is a new one:   mchunkptr bk = p->bk;
line 1458 is a new one:   if (__builtin_expect (fd->bk != p || bk->fd != p, 0))
line 1459 is a new one:     malloc_printerr ("corrupted double-linked list");
line 1461 is a new one:   fd->bk = bk;
line 1462 is a new one:   bk->fd = fd;
line 1463 is a new one:   if (!in_smallbin_range (chunksize_nomask (p)) && p->fd_nextsize != NULL)
line 1465 is a new one:       if (p->fd_nextsize->bk_nextsize != p
line 1466 is a new one: 	  || p->bk_nextsize->fd_nextsize != p)
line 1467 is a new one: 	malloc_printerr ("corrupted double-linked list (not small)");
line 1469 is a new one:       if (fd->fd_nextsize == NULL)
line 1471 is a new one: 	  if (p->fd_nextsize == p)
line 1472 is a new one: 	    fd->fd_nextsize = fd->bk_nextsize = fd;
line 1475 is a new one: 	      fd->fd_nextsize = p->fd_nextsize;
line 1476 is a new one: 	      fd->bk_nextsize = p->bk_nextsize;
line 1477 is a new one: 	      p->fd_nextsize->bk_nextsize = fd;
line 1478 is a new one: 	      p->bk_nextsize->fd_nextsize = fd;
line 1483 is a new one: 	  p->fd_nextsize->bk_nextsize = p->bk_nextsize;
line 1484 is a new one: 	  p->bk_nextsize->fd_nextsize = p->fd_nextsize;
line 2819 is a new one:   uintptr_t mem = (uintptr_t) chunk2mem (p);
line 2827 is a new one:   if (__glibc_unlikely ((block | total_size) & (pagesize - 1)) != 0
line 2828 is a new one:       || __glibc_unlikely (!powerof2 (mem & (pagesize - 1))))
line 2852 is a new one:   uintptr_t block = (uintptr_t) p - offset;
line 2853 is a new one:   uintptr_t mem = (uintptr_t) chunk2mem(p);
line 2854 is a new one:   size_t total_size = offset + size;
line 2855 is a new one:   if (__glibc_unlikely ((block | total_size) & (pagesize - 1)) != 0
line 2856 is a new one:       || __glibc_unlikely (!powerof2 (mem & (pagesize - 1))))
line 2857 is a new one:     malloc_printerr("mremap_chunk(): invalid pointer");
line 2863 is a new one:   if (total_size == new_size)
line 2866 is a new one:   cp = (char *) __mremap ((char *) block, total_size, new_size,
line 2896 is a new one:   /* This field exists to detect double frees.  */
line 2897 is a new one:   struct tcache_perthread_struct *key;
line 2907 is a new one:   uint16_t counts[TCACHE_MAX_BINS];
line 2921 is a new one:   /* Mark this chunk as "in the tcache" so the test in _int_free will
line 2922 is a new one:      detect a double free.  */
line 2923 is a new one:   e->key = tcache;
line 2938 is a new one:   e->key = NULL;
line 3026 is a new one:   _Static_assert (PTRDIFF_MAX <= SIZE_MAX / 2,
line 3027 is a new one:                   "PTRDIFF_MAX is not more than half of SIZE_MAX");
line 3036 is a new one:   if (!checked_request2size (bytes, &tbytes))
line 3039 is a new one:       return NULL;
line 3048 is a new one:       && tcache->counts[tc_idx] > 0)
line 3176 is a new one:   if (!checked_request2size (bytes, &nb))
line 3179 is a new one:       return NULL;
line 3349 is a new one:   size_t rounded_bytes;
line 3350 is a new one:   /* ALIGN_UP with overflow check.  */
line 3351 is a new one:   if (__glibc_unlikely (__builtin_add_overflow (bytes,
line 3352 is a new one: 						pagesize - 1,
line 3353 is a new one: 						&rounded_bytes)))
line 3358 is a new one:   rounded_bytes = rounded_bytes & -(pagesize - 1);
line 3368 is a new one:   INTERNAL_SIZE_T sz, csz, oldtopsize;
line 3373 is a new one:   ptrdiff_t bytes;
line 3375 is a new one:   if (__glibc_unlikely (__builtin_mul_overflow (n, elem_size, &bytes)))
line 3377 is a new one:        __set_errno (ENOMEM);
line 3378 is a new one:        return NULL;
line 3539 is a new one:      size. Also, checked_request2size returns false for request sizes
line 3544 is a new one:   if (!checked_request2size (bytes, &nb))
line 3547 is a new one:       return NULL;
line 3731 is a new one:           mchunkptr next = chunk_at_offset (victim, size);
line 3733 is a new one:           if (__glibc_unlikely (size <= 2 * SIZE_SZ)
line 3734 is a new one:               || __glibc_unlikely (size > av->system_mem))
line 3735 is a new one:             malloc_printerr ("malloc(): invalid size (unsorted)");
line 3736 is a new one:           if (__glibc_unlikely (chunksize_nomask (next) < 2 * SIZE_SZ)
line 3737 is a new one:               || __glibc_unlikely (chunksize_nomask (next) > av->system_mem))
line 3738 is a new one:             malloc_printerr ("malloc(): invalid next size (unsorted)");
line 3739 is a new one:           if (__glibc_unlikely ((prev_size (next) & ~(SIZE_BITS)) != size))
line 3740 is a new one:             malloc_printerr ("malloc(): mismatching next->prev_size (unsorted)");
line 3741 is a new one:           if (__glibc_unlikely (bck->fd != victim)
line 3742 is a new one:               || __glibc_unlikely (victim->fd != unsorted_chunks (av)))
line 3743 is a new one:             malloc_printerr ("malloc(): unsorted double linked list corrupted");
line 3744 is a new one:           if (__glibc_unlikely (prev_inuse (next)))
line 3745 is a new one:             malloc_printerr ("malloc(): invalid next->prev_inuse (unsorted)");
line 3866 is a new one:                           if (__glibc_unlikely (fwd->bk_nextsize->fd_nextsize != fwd))
line 3867 is a new one:                             malloc_printerr ("malloc(): largebin double linked list corrupted (nextsize)");
line 3872 is a new one:                       if (bck->fd != fwd)
line 3873 is a new one:                         malloc_printerr ("malloc(): largebin double linked list corrupted (bk)");
line 3938 is a new one:               unlink_chunk (av, victim);
line 4040 is a new one:               unlink_chunk (av, victim);
line 4105 is a new one:       if (__glibc_unlikely (size > av->system_mem))
line 4106 is a new one:         malloc_printerr ("malloc(): corrupted top size");
line 4183 is a new one:     if (tcache != NULL && tc_idx < mp_.tcache_bins)
line 4185 is a new one: 	/* Check to see if it's already in the tcache.  */
line 4186 is a new one: 	tcache_entry *e = (tcache_entry *) chunk2mem (p);
line 4188 is a new one: 	/* This test succeeds on double free.  However, we don't 100%
line 4189 is a new one: 	   trust it (it also matches random payload data at a 1 in
line 4190 is a new one: 	   2^<size_t> chance), so verify it's not an unlikely
line 4191 is a new one: 	   coincidence before aborting.  */
line 4192 is a new one: 	if (__glibc_unlikely (e->key == tcache))
line 4194 is a new one: 	    tcache_entry *tmp;
line 4195 is a new one: 	    LIBC_PROBE (memory_tcache_double_free, 2, e, tc_idx);
line 4196 is a new one: 	    for (tmp = tcache->entries[tc_idx];
line 4197 is a new one: 		 tmp;
line 4198 is a new one: 		 tmp = tmp->next)
line 4199 is a new one: 	      if (tmp == e)
line 4200 is a new one: 		malloc_printerr ("free(): double free detected in tcache 2");
line 4201 is a new one: 	    /* If we get here, it was a coincidence.  We've wasted a
line 4202 is a new one: 	       few cycles, but don't abort.  */
line 4205 is a new one: 	if (tcache->counts[tc_idx] < mp_.tcache_count)
line 4207 is a new one: 	    tcache_put (p, tc_idx);
line 4208 is a new one: 	    return;
line 4330 is a new one:       if (__glibc_unlikely (chunksize(p) != prevsize))
line 4331 is a new one:         malloc_printerr ("corrupted size vs. prev_size while consolidating");
line 4332 is a new one:       unlink_chunk (av, p);
line 4341 is a new one: 	unlink_chunk (av, nextchunk);
line 4491 is a new one: 	  if (__glibc_unlikely (chunksize(p) != prevsize))
line 4492 is a new one: 	    malloc_printerr ("corrupted size vs. prev_size in fastbins");
line 4493 is a new one: 	  unlink_chunk (av, p);
line 4501 is a new one: 	    unlink_chunk (av, nextchunk);
line 4593 is a new one:           unlink_chunk (av, next);
line 4616 is a new one: 	      memcpy (newmem, chunk2mem (oldp), oldsize - SIZE_SZ);
line 4670 is a new one:   if (!checked_request2size (bytes, &nb))
line 4673 is a new one:       return NULL;
line 5009 is a new one: static __always_inline int
line 5019 is a new one: static __always_inline int
line 5029 is a new one: static __always_inline int
line 5044 is a new one: static __always_inline int
line 5054 is a new one: static __always_inline int
line 5060 is a new one: static __always_inline int
line 5068 is a new one: static __always_inline int
line 5076 is a new one: static __always_inline int
line 5085 is a new one: static __always_inline int
line 5097 is a new one: static __always_inline int
line 5100 is a new one:   if (value <= MAX_TCACHE_COUNT)
line 5102 is a new one:       LIBC_PROBE (memory_tunable_tcache_count, 2, value, mp_.tcache_count);
line 5103 is a new one:       mp_.tcache_count = value;
line 5108 is a new one: static __always_inline int
