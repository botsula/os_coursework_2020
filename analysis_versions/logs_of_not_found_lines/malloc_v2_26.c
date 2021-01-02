Comparison of files: malloc_v2_26.c and malloc_v2_24.c
line 1 is a new one:    Copyright (C) 1996-2017 Free Software Foundation, Inc.
line 238 is a new one: #include <libc-pointer-arith.h>
line 240 is a new one: /* For DIAG_PUSH/POP_NEEDS_COMMENT et al.  */
line 241 is a new one: #include <libc-diag.h>
line 301 is a new one: #if USE_TCACHE
line 302 is a new one: /* We want 64 entries.  This is an arbitrary limit, which tunables can reduce.  */
line 303 is a new one: # define TCACHE_MAX_BINS		64
line 304 is a new one: # define MAX_TCACHE_SIZE	tidx2usize (TCACHE_MAX_BINS-1)
line 306 is a new one: /* Only used to pre-fill the tunables.  */
line 307 is a new one: # define tidx2usize(idx)	(((size_t) idx) * MALLOC_ALIGNMENT + MINSIZE - SIZE_SZ)
line 309 is a new one: /* When "x" is from chunksize().  */
line 310 is a new one: # define csize2tidx(x) (((x) - MINSIZE + MALLOC_ALIGNMENT - 1) / MALLOC_ALIGNMENT)
line 311 is a new one: /* When "x" is a user-provided size.  */
line 312 is a new one: # define usize2tidx(x) csize2tidx (request2size (x))
line 314 is a new one: /* With rounding and alignment, the bins are...
line 315 is a new one:    idx 0   bytes 0..24 (64-bit) or 0..12 (32-bit)
line 316 is a new one:    idx 1   bytes 25..40 or 13..20
line 317 is a new one:    idx 2   bytes 41..56 or 21..28
line 318 is a new one:    etc.  */
line 320 is a new one: /* This is another arbitrary limit, which tunables can change.  Each
line 321 is a new one:    tcache bin will hold at most this number of chunks.  */
line 322 is a new one: # define TCACHE_FILL_COUNT 7
line 543 is a new one:   Large chunks that were internally obtained via mmap will always be
line 544 is a new one:   grown using malloc-copy-free sequences unless the system supports
line 545 is a new one:   MREMAP (currently only linux).
line 1068 is a new one:   INTERNAL_SIZE_T      mchunk_prev_size;  /* Size of previous chunk (if free).  */
line 1069 is a new one:   INTERNAL_SIZE_T      mchunk_size;       /* Size in bytes, including overhead. */
line 1098 is a new one: 	    |             Size of previous chunk, if unallocated (P clear)  |
line 1100 is a new one: 	    |             Size of chunk, in bytes                     |A|M|P|
line 1107 is a new one: 	    |             (size of chunk, but used for application data)    |
line 1109 is a new one: 	    |             Size of next chunk, in bytes                |A|0|1|
line 1123 is a new one: 	    |             Size of previous chunk, if unallocated (P clear)  |
line 1125 is a new one:     `head:' |             Size of chunk, in bytes                     |A|0|P|
line 1137 is a new one: 	    |             Size of next chunk, in bytes                |A|0|0|
line 1151 is a new one:     The A (NON_MAIN_ARENA) bit is cleared for chunks on the initial,
line 1152 is a new one:     main arena, described by the main_arena variable.  When additional
line 1153 is a new one:     threads are spawned, each thread receives its own arena (up to a
line 1154 is a new one:     configurable limit, after which arenas are reused for multiple
line 1155 is a new one:     threads), and the chunks in these arenas have the A bit set.  To
line 1156 is a new one:     find the arena for a chunk on such a non-main arena, heap_for_ptr
line 1157 is a new one:     performs a bit mask operation and indirection through the ar_ptr
line 1158 is a new one:     member of the per-heap header heap_info (see arena.c).
line 1165 is a new one:     The three exceptions to all this are:
line 1175 is a new one: 	allocated one-by-one, each must contain its own trailing size
line 1176 is a new one: 	field.  If the M bit is set, the other bits are ignored
line 1177 is a new one: 	(because mmapped chunks are neither in an arena, nor adjacent
line 1178 is a new one: 	to a freed chunk).  The M bit is also used for chunks which
line 1179 is a new one: 	originally came from a dumped heap via malloc_set_state in
line 1180 is a new one: 	hooks.c.
line 1182 is a new one:      3. Chunks in fastbins are treated as allocated chunks from the
line 1183 is a new one: 	point of view of the chunk allocator.  They are consolidated
line 1184 is a new one: 	with their neighbors only in bulk, in malloc_consolidate.
line 1248 is a new one: #define prev_inuse(p)       ((p)->mchunk_size & PREV_INUSE)
line 1255 is a new one: #define chunk_is_mmapped(p) ((p)->mchunk_size & IS_MMAPPED)
line 1263 is a new one: /* Check for chunk from main arena.  */
line 1264 is a new one: #define chunk_main_arena(p) (((p)->mchunk_size & NON_MAIN_ARENA) == 0)
line 1266 is a new one: /* Mark a chunk as not being on the main arena.  */
line 1267 is a new one: #define set_non_main_arena(p) ((p)->mchunk_size |= NON_MAIN_ARENA)
line 1281 is a new one: #define chunksize(p) (chunksize_nomask (p) & ~(SIZE_BITS))
line 1283 is a new one: /* Like chunksize, but do not mask SIZE_BITS.  */
line 1284 is a new one: #define chunksize_nomask(p)         ((p)->mchunk_size)
line 1287 is a new one: #define next_chunk(p) ((mchunkptr) (((char *) (p)) + chunksize (p)))
line 1289 is a new one: /* Size of the chunk below P.  Only valid if prev_inuse (P).  */
line 1290 is a new one: #define prev_size(p) ((p)->mchunk_prev_size)
line 1292 is a new one: /* Set the size of the chunk below P.  Only valid if prev_inuse (P).  */
line 1293 is a new one: #define set_prev_size(p, sz) ((p)->mchunk_prev_size = (sz))
line 1295 is a new one: /* Ptr to previous physical malloc_chunk.  Only valid if prev_inuse (P).  */
line 1296 is a new one: #define prev_chunk(p) ((mchunkptr) (((char *) (p)) - prev_size (p)))
line 1303 is a new one:   ((((mchunkptr) (((char *) (p)) + chunksize (p)))->mchunk_size) & PREV_INUSE)
line 1307 is a new one:   ((mchunkptr) (((char *) (p)) + chunksize (p)))->mchunk_size |= PREV_INUSE
line 1310 is a new one:   ((mchunkptr) (((char *) (p)) + chunksize (p)))->mchunk_size &= ~(PREV_INUSE)
line 1315 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->mchunk_size & PREV_INUSE)
line 1318 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->mchunk_size |= PREV_INUSE)
line 1321 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->mchunk_size &= ~(PREV_INUSE))
line 1325 is a new one: #define set_head_size(p, s)  ((p)->mchunk_size = (((p)->mchunk_size & SIZE_BITS) | (s)))
line 1328 is a new one: #define set_head(p, s)       ((p)->mchunk_size = (s))
line 1331 is a new one: #define set_foot(p, s)       (((mchunkptr) ((char *) (p) + (s)))->mchunk_prev_size = (s))
line 1334 is a new one: #pragma GCC poison mchunk_size
line 1335 is a new one: #pragma GCC poison mchunk_prev_size
line 1404 is a new one:     if (__builtin_expect (chunksize(P) != prev_size (next_chunk(P)), 0))      \
line 1405 is a new one:       malloc_printerr (check_action, "corrupted size vs. prev_size", P, AV);  \
line 1413 is a new one:         if (!in_smallbin_range (chunksize_nomask (P))			      \
line 1680 is a new one:   __libc_lock_define (, mutex);
line 1742 is a new one: #if USE_TCACHE
line 1743 is a new one:   /* Maximum number of buckets to use.  */
line 1744 is a new one:   size_t tcache_bins;
line 1745 is a new one:   size_t tcache_max_bytes;
line 1746 is a new one:   /* Maximum number of chunks in each bucket.  */
line 1747 is a new one:   size_t tcache_count;
line 1748 is a new one:   /* Maximum number of chunks to remove from the unsorted list, which
line 1749 is a new one:      aren't used to prefill the cache.  */
line 1750 is a new one:   size_t tcache_unsorted_limit;
line 1790 is a new one: #if USE_TCACHE
line 1791 is a new one:   ,
line 1792 is a new one:   .tcache_count = TCACHE_FILL_COUNT,
line 1793 is a new one:   .tcache_bins = TCACHE_MAX_BINS,
line 1794 is a new one:   .tcache_max_bytes = tidx2usize (TCACHE_MAX_BINS-1),
line 1795 is a new one:   .tcache_unsorted_limit = 0 /* No limit.  */
line 1983 is a new one:       assert (((prev_size (p) + sz) & (GLRO (dl_pagesize) - 1)) == 0);
line 2011 is a new one:       assert (prev_size (p) == sz);
line 2076 is a new one:       if (chunk_main_arena (p))
line 2368 is a new one: 		  set_prev_size (p, correction);
line 2374 is a new one: 		  set_prev_size (p, 0);
line 2724 is a new one: 		      set_head (chunk_at_offset (old_top, old_size),
line 2725 is a new one: 				(2 * SIZE_SZ) | PREV_INUSE);
line 2726 is a new one: 		      set_head (chunk_at_offset (old_top, old_size + 2 * SIZE_SZ),
line 2727 is a new one: 				(2 * SIZE_SZ) | PREV_INUSE);
line 2855 is a new one:   uintptr_t block = (uintptr_t) p - prev_size (p);
line 2856 is a new one:   size_t total_size = prev_size (p) + size;
line 2885 is a new one:   INTERNAL_SIZE_T offset = prev_size (p);
line 2909 is a new one:   assert (prev_size (p) == offset);
line 2922 is a new one: #if USE_TCACHE
line 2924 is a new one: /* We overlay this structure on the user-data portion of a chunk when
line 2925 is a new one:    the chunk is stored in the per-thread cache.  */
line 2926 is a new one: typedef struct tcache_entry
line 2928 is a new one:   struct tcache_entry *next;
line 2929 is a new one: } tcache_entry;
line 2931 is a new one: /* There is one of these for each thread, which contains the
line 2932 is a new one:    per-thread cache (hence "tcache_perthread_struct").  Keeping
line 2933 is a new one:    overall size low is mildly important.  Note that COUNTS and ENTRIES
line 2934 is a new one:    are redundant (we could have just counted the linked list each
line 2935 is a new one:    time), this is for performance reasons.  */
line 2936 is a new one: typedef struct tcache_perthread_struct
line 2938 is a new one:   char counts[TCACHE_MAX_BINS];
line 2939 is a new one:   tcache_entry *entries[TCACHE_MAX_BINS];
line 2940 is a new one: } tcache_perthread_struct;
line 2942 is a new one: static __thread char tcache_shutting_down = 0;
line 2943 is a new one: static __thread tcache_perthread_struct *tcache = NULL;
line 2945 is a new one: /* Caller must ensure that we know tc_idx is valid and there's room
line 2946 is a new one:    for more chunks.  */
line 2948 is a new one: tcache_put (mchunkptr chunk, size_t tc_idx)
line 2950 is a new one:   tcache_entry *e = (tcache_entry *) chunk2mem (chunk);
line 2951 is a new one:   assert (tc_idx < TCACHE_MAX_BINS);
line 2952 is a new one:   e->next = tcache->entries[tc_idx];
line 2953 is a new one:   tcache->entries[tc_idx] = e;
line 2954 is a new one:   ++(tcache->counts[tc_idx]);
line 2957 is a new one: /* Caller must ensure that we know tc_idx is valid and there's
line 2958 is a new one:    available chunks to remove.  */
line 2960 is a new one: tcache_get (size_t tc_idx)
line 2962 is a new one:   tcache_entry *e = tcache->entries[tc_idx];
line 2963 is a new one:   assert (tc_idx < TCACHE_MAX_BINS);
line 2964 is a new one:   assert (tcache->entries[tc_idx] > 0);
line 2965 is a new one:   tcache->entries[tc_idx] = e->next;
line 2966 is a new one:   --(tcache->counts[tc_idx]);
line 2967 is a new one:   return (void *) e;
line 2970 is a new one: static void __attribute__ ((section ("__libc_thread_freeres_fn")))
line 2971 is a new one: tcache_thread_freeres (void)
line 2974 is a new one:   tcache_perthread_struct *tcache_tmp = tcache;
line 2976 is a new one:   if (!tcache)
line 2979 is a new one:   tcache = NULL;
line 2981 is a new one:   for (i = 0; i < TCACHE_MAX_BINS; ++i)
line 2983 is a new one:       while (tcache_tmp->entries[i])
line 2985 is a new one: 	  tcache_entry *e = tcache_tmp->entries[i];
line 2986 is a new one: 	  tcache_tmp->entries[i] = e->next;
line 2987 is a new one: 	  __libc_free (e);
line 2991 is a new one:   __libc_free (tcache_tmp);
line 2993 is a new one:   tcache_shutting_down = 1;
line 2995 is a new one: text_set_element (__libc_thread_subfreeres, tcache_thread_freeres);
line 2998 is a new one: tcache_init(void)
line 3001 is a new one:   void *victim = 0;
line 3002 is a new one:   const size_t bytes = sizeof (tcache_perthread_struct);
line 3004 is a new one:   if (tcache_shutting_down)
line 3017 is a new one:     __libc_lock_unlock (ar_ptr->mutex);
line 3019 is a new one:   /* In a low memory situation, we may not be able to allocate memory
line 3020 is a new one:      - in which case, we just keep trying later.  However, we
line 3021 is a new one:      typically do this very early, so either there is sufficient
line 3022 is a new one:      memory, or there isn't enough memory to do non-trivial
line 3023 is a new one:      allocations anyway.  */
line 3024 is a new one:   if (victim)
line 3026 is a new one:       tcache = (tcache_perthread_struct *) victim;
line 3027 is a new one:       memset (tcache, 0, sizeof (tcache_perthread_struct));
line 3032 is a new one: #define MAYBE_INIT_TCACHE() \
line 3033 is a new one:   if (__glibc_unlikely (tcache == NULL)) \
line 3034 is a new one:     tcache_init();
line 3037 is a new one: #define MAYBE_INIT_TCACHE()
line 3050 is a new one: #if USE_TCACHE
line 3051 is a new one:   /* int_free also calls request2size, be careful to not pad twice.  */
line 3052 is a new one:   size_t tbytes = request2size (bytes);
line 3053 is a new one:   size_t tc_idx = csize2tidx (tbytes);
line 3055 is a new one:   MAYBE_INIT_TCACHE ();
line 3057 is a new one:   DIAG_PUSH_NEEDS_COMMENT;
line 3058 is a new one:   if (tc_idx < mp_.tcache_bins
line 3059 is a new one:       /*&& tc_idx < TCACHE_MAX_BINS*/ /* to appease gcc */
line 3060 is a new one:       && tcache
line 3061 is a new one:       && tcache->entries[tc_idx] != NULL)
line 3063 is a new one:       return tcache_get (tc_idx);
line 3065 is a new one:   DIAG_POP_NEEDS_COMMENT;
line 3081 is a new one:     __libc_lock_unlock (ar_ptr->mutex);
line 3113 is a new one:           && chunksize_nomask (p) > mp_.mmap_threshold
line 3114 is a new one:           && chunksize_nomask (p) <= DEFAULT_MMAP_THRESHOLD_MAX
line 3126 is a new one:   MAYBE_INIT_TCACHE ();
line 3166 is a new one:       MAYBE_INIT_TCACHE ();
line 3167 is a new one:       ar_ptr = arena_for_chunk (oldp);
line 3228 is a new one:   __libc_lock_lock (ar_ptr->mutex);
line 3232 is a new one:   __libc_lock_unlock (ar_ptr->mutex);
line 3314 is a new one:     __libc_lock_unlock (ar_ptr->mutex);
line 3393 is a new one:   MAYBE_INIT_TCACHE ();
line 3437 is a new one:     __libc_lock_unlock (av->mutex);
line 3525 is a new one: #if USE_TCACHE
line 3526 is a new one:   size_t tcache_unsorted_count;	    /* count of unsorted chunks processed */
line 3558 is a new one: #define REMOVE_FB(fb, victim, pp)			\
line 3559 is a new one:   do							\
line 3560 is a new one:     {							\
line 3561 is a new one:       victim = pp;					\
line 3562 is a new one:       if (victim == NULL)				\
line 3563 is a new one: 	break;						\
line 3564 is a new one:     }							\
line 3565 is a new one:   while ((pp = catomic_compare_and_exchange_val_acq (fb, victim->fd, victim)) \
line 3566 is a new one: 	 != victim);					\
line 3573 is a new one:       REMOVE_FB (fb, victim, pp);
line 3584 is a new one: #if USE_TCACHE
line 3585 is a new one: 	  /* While we're here, if we see other chunks of the same size,
line 3586 is a new one: 	     stash them in the tcache.  */
line 3587 is a new one: 	  size_t tc_idx = csize2tidx (nb);
line 3588 is a new one: 	  if (tcache && tc_idx < mp_.tcache_bins)
line 3590 is a new one: 	      mchunkptr tc_victim;
line 3592 is a new one: 	      /* While bin not empty and tcache not full, copy chunks over.  */
line 3593 is a new one: 	      while (tcache->counts[tc_idx] < mp_.tcache_count
line 3594 is a new one: 		     && (pp = *fb) != NULL)
line 3596 is a new one: 		  REMOVE_FB (fb, tc_victim, pp);
line 3597 is a new one: 		  if (tc_victim != 0)
line 3598 is a new one: 		    {
line 3599 is a new one: 		      tcache_put (tc_victim, tc_idx);
line 3600 is a new one: 	            }
line 3640 is a new one: 		set_non_main_arena (victim);
line 3642 is a new one: #if USE_TCACHE
line 3643 is a new one: 	  /* While we're here, if we see other chunks of the same size,
line 3644 is a new one: 	     stash them in the tcache.  */
line 3645 is a new one: 	  size_t tc_idx = csize2tidx (nb);
line 3646 is a new one: 	  if (tcache && tc_idx < mp_.tcache_bins)
line 3648 is a new one: 	      mchunkptr tc_victim;
line 3650 is a new one: 	      /* While bin not empty and tcache not full, copy chunks over.  */
line 3651 is a new one: 	      while (tcache->counts[tc_idx] < mp_.tcache_count
line 3652 is a new one: 		     && (tc_victim = last (bin)) != bin)
line 3654 is a new one: 		  if (tc_victim != 0)
line 3655 is a new one: 		    {
line 3656 is a new one: 		      bck = tc_victim->bk;
line 3657 is a new one: 		      set_inuse_bit_at_offset (tc_victim, nb);
line 3658 is a new one: 		      if (av != &main_arena)
line 3659 is a new one: 			set_non_main_arena (tc_victim);
line 3660 is a new one: 		      bin->bk = bck;
line 3661 is a new one: 		      bck->fd = bin;
line 3663 is a new one: 		      tcache_put (tc_victim, tc_idx);
line 3664 is a new one: 	            }
line 3706 is a new one: #if USE_TCACHE
line 3707 is a new one:   INTERNAL_SIZE_T tcache_nb = 0;
line 3708 is a new one:   size_t tc_idx = csize2tidx (nb);
line 3709 is a new one:   if (tcache && tc_idx < mp_.tcache_bins)
line 3710 is a new one:     tcache_nb = nb;
line 3711 is a new one:   int return_cached = 0;
line 3713 is a new one:   tcache_unsorted_count = 0;
line 3722 is a new one:           if (__builtin_expect (chunksize_nomask (victim) <= 2 * SIZE_SZ, 0)
line 3723 is a new one:               || __builtin_expect (chunksize_nomask (victim)
line 3724 is a new one: 				   > av->system_mem, 0))
line 3775 is a new one: 		set_non_main_arena (victim);
line 3776 is a new one: #if USE_TCACHE
line 3777 is a new one: 	      /* Fill cache first, return to user only if cache fills.
line 3778 is a new one: 		 We may return one of these chunks later.  */
line 3779 is a new one: 	      if (tcache_nb
line 3780 is a new one: 		  && tcache->counts[tc_idx] < mp_.tcache_count)
line 3782 is a new one: 		  tcache_put (victim, tc_idx);
line 3783 is a new one: 		  return_cached = 1;
line 3784 is a new one: 		  continue;
line 3786 is a new one: 	      else
line 3793 is a new one: #if USE_TCACHE
line 3818 is a new one:                   assert (chunk_main_arena (bck->bk));
line 3819 is a new one:                   if ((unsigned long) (size)
line 3820 is a new one: 		      < (unsigned long) chunksize_nomask (bck->bk))
line 3831 is a new one:                       assert (chunk_main_arena (fwd));
line 3832 is a new one:                       while ((unsigned long) size < chunksize_nomask (fwd))
line 3835 is a new one: 			  assert (chunk_main_arena (fwd));
line 3838 is a new one:                       if ((unsigned long) size
line 3839 is a new one: 			  == (unsigned long) chunksize_nomask (fwd))
line 3862 is a new one: #if USE_TCACHE
line 3863 is a new one:       /* If we've processed as many chunks as we're allowed while
line 3864 is a new one: 	 filling the cache, return one of the cached ones.  */
line 3865 is a new one:       ++tcache_unsorted_count;
line 3866 is a new one:       if (return_cached
line 3867 is a new one: 	  && mp_.tcache_unsorted_limit > 0
line 3868 is a new one: 	  && tcache_unsorted_count > mp_.tcache_unsorted_limit)
line 3870 is a new one: 	  return tcache_get (tc_idx);
line 3879 is a new one: #if USE_TCACHE
line 3880 is a new one:       /* If all the small chunks we found ended up cached, return one now.  */
line 3881 is a new one:       if (return_cached)
line 3883 is a new one: 	  return tcache_get (tc_idx);
line 3897 is a new one:           if ((victim = first (bin)) != bin
line 3898 is a new one: 	      && (unsigned long) chunksize_nomask (victim)
line 3899 is a new one: 	        >= (unsigned long) (nb))
line 3908 is a new one:               if (victim != last (bin)
line 3909 is a new one: 		  && chunksize_nomask (victim)
line 3910 is a new one: 		    == chunksize_nomask (victim->fd))
line 3921 is a new one: 		    set_non_main_arena (victim);
line 4026 is a new one: 		    set_non_main_arena (victim);
line 4158 is a new one:         __libc_lock_unlock (av->mutex);
line 4172 is a new one: #if USE_TCACHE
line 4173 is a new one:   {
line 4174 is a new one:     size_t tc_idx = csize2tidx (size);
line 4176 is a new one:     if (tcache
line 4177 is a new one: 	&& tc_idx < mp_.tcache_bins
line 4178 is a new one: 	&& tcache->counts[tc_idx] < mp_.tcache_count)
line 4180 is a new one: 	tcache_put (p, tc_idx);
line 4181 is a new one: 	return;
line 4202 is a new one:     if (__builtin_expect (chunksize_nomask (chunk_at_offset (p, size))
line 4203 is a new one: 			  <= 2 * SIZE_SZ, 0)
line 4212 is a new one: 		  __libc_lock_lock (av->mutex);
line 4214 is a new one: 		  chunksize_nomask (chunk_at_offset (p, size)) <= 2 * SIZE_SZ
line 4223 is a new one: 	    __libc_lock_unlock (av->mutex);
line 4269 is a new one:       __libc_lock_lock (av->mutex);
line 4298 is a new one:     if (__builtin_expect (chunksize_nomask (nextchunk) <= 2 * SIZE_SZ, 0)
line 4309 is a new one:       prevsize = prev_size (p);
line 4402 is a new one:       __libc_lock_unlock (av->mutex);
line 4474 is a new one: 	  size = chunksize (p);
line 4479 is a new one: 	    prevsize = prev_size (p);
line 4554 is a new one:   if (__builtin_expect (chunksize_nomask (oldp) <= 2 * SIZE_SZ, 0)
line 4570 is a new one:   if (__builtin_expect (chunksize_nomask (next) <= 2 * SIZE_SZ, 0)
line 4756 is a new one:           set_prev_size (newp, prev_size (p) + leadsize);
line 4869 is a new one:       __libc_lock_lock (ar_ptr->mutex);
line 4871 is a new one:       __libc_lock_unlock (ar_ptr->mutex);
line 5000 is a new one:       __libc_lock_lock (ar_ptr->mutex);
line 5002 is a new one:       __libc_lock_unlock (ar_ptr->mutex);
line 5032 is a new one:       __libc_lock_lock (ar_ptr->mutex);
line 5043 is a new one:       __libc_lock_unlock (ar_ptr->mutex);
line 5062 is a new one: static inline int
line 5063 is a new one: __always_inline
line 5064 is a new one: do_set_trim_threshold (size_t value)
line 5066 is a new one:   LIBC_PROBE (memory_mallopt_trim_threshold, 3, value, mp_.trim_threshold,
line 5067 is a new one: 	      mp_.no_dyn_threshold);
line 5068 is a new one:   mp_.trim_threshold = value;
line 5069 is a new one:   mp_.no_dyn_threshold = 1;
line 5070 is a new one:   return 1;
line 5073 is a new one: static inline int
line 5074 is a new one: __always_inline
line 5075 is a new one: do_set_top_pad (size_t value)
line 5077 is a new one:   LIBC_PROBE (memory_mallopt_top_pad, 3, value, mp_.top_pad,
line 5078 is a new one: 	      mp_.no_dyn_threshold);
line 5079 is a new one:   mp_.top_pad = value;
line 5080 is a new one:   mp_.no_dyn_threshold = 1;
line 5081 is a new one:   return 1;
line 5084 is a new one: static inline int
line 5085 is a new one: __always_inline
line 5086 is a new one: do_set_mmap_threshold (size_t value)
line 5088 is a new one:   /* Forbid setting the threshold too high.  */
line 5089 is a new one:   if (value <= HEAP_MAX_SIZE / 2)
line 5091 is a new one:       LIBC_PROBE (memory_mallopt_mmap_threshold, 3, value, mp_.mmap_threshold,
line 5092 is a new one: 		  mp_.no_dyn_threshold);
line 5093 is a new one:       mp_.mmap_threshold = value;
line 5095 is a new one:       return 1;
line 5100 is a new one: static inline int
line 5101 is a new one: __always_inline
line 5102 is a new one: do_set_mmaps_max (int32_t value)
line 5104 is a new one:   LIBC_PROBE (memory_mallopt_mmap_max, 3, value, mp_.n_mmaps_max,
line 5105 is a new one: 	      mp_.no_dyn_threshold);
line 5106 is a new one:   mp_.n_mmaps_max = value;
line 5107 is a new one:   mp_.no_dyn_threshold = 1;
line 5108 is a new one:   return 1;
line 5111 is a new one: static inline int
line 5112 is a new one: __always_inline
line 5113 is a new one: do_set_mallopt_check (int32_t value)
line 5115 is a new one:   LIBC_PROBE (memory_mallopt_check_action, 2, value, check_action);
line 5116 is a new one:   check_action = value;
line 5117 is a new one:   return 1;
line 5120 is a new one: static inline int
line 5121 is a new one: __always_inline
line 5122 is a new one: do_set_perturb_byte (int32_t value)
line 5124 is a new one:   LIBC_PROBE (memory_mallopt_perturb, 2, value, perturb_byte);
line 5125 is a new one:   perturb_byte = value;
line 5126 is a new one:   return 1;
line 5129 is a new one: static inline int
line 5130 is a new one: __always_inline
line 5131 is a new one: do_set_arena_test (size_t value)
line 5133 is a new one:   LIBC_PROBE (memory_mallopt_arena_test, 2, value, mp_.arena_test);
line 5134 is a new one:   mp_.arena_test = value;
line 5135 is a new one:   return 1;
line 5138 is a new one: static inline int
line 5139 is a new one: __always_inline
line 5140 is a new one: do_set_arena_max (size_t value)
line 5142 is a new one:   LIBC_PROBE (memory_mallopt_arena_max, 2, value, mp_.arena_max);
line 5143 is a new one:   mp_.arena_max = value;
line 5144 is a new one:   return 1;
line 5147 is a new one: #if USE_TCACHE
line 5148 is a new one: static inline int
line 5149 is a new one: __always_inline
line 5150 is a new one: do_set_tcache_max (size_t value)
line 5152 is a new one:   if (value >= 0 && value <= MAX_TCACHE_SIZE)
line 5154 is a new one:       LIBC_PROBE (memory_tunable_tcache_max_bytes, 2, value, mp_.tcache_max_bytes);
line 5155 is a new one:       mp_.tcache_max_bytes = value;
line 5156 is a new one:       mp_.tcache_bins = csize2tidx (request2size(value)) + 1;
line 5158 is a new one:   return 1;
line 5161 is a new one: static inline int
line 5162 is a new one: __always_inline
line 5163 is a new one: do_set_tcache_count (size_t value)
line 5165 is a new one:   LIBC_PROBE (memory_tunable_tcache_count, 2, value, mp_.tcache_count);
line 5166 is a new one:   mp_.tcache_count = value;
line 5167 is a new one:   return 1;
line 5170 is a new one: static inline int
line 5171 is a new one: __always_inline
line 5172 is a new one: do_set_tcache_unsorted_limit (size_t value)
line 5174 is a new one:   LIBC_PROBE (memory_tunable_tcache_unsorted_limit, 2, value, mp_.tcache_unsorted_limit);
line 5175 is a new one:   mp_.tcache_unsorted_limit = value;
line 5176 is a new one:   return 1;
line 5188 is a new one:   __libc_lock_lock (av->mutex);
line 5207 is a new one:       do_set_trim_threshold (value);
line 5211 is a new one:       do_set_top_pad (value);
line 5215 is a new one:       res = do_set_mmap_threshold (value);
line 5219 is a new one:       do_set_mmaps_max (value);
line 5223 is a new one:       do_set_mallopt_check (value);
line 5227 is a new one:       do_set_perturb_byte (value);
line 5232 is a new one: 	do_set_arena_test (value);
line 5237 is a new one: 	do_set_arena_max (value);
line 5240 is a new one:   __libc_lock_unlock (av->mutex);
line 5399 is a new one:     __libc_message ((action & 2) ? (do_abort | do_backtrace) : do_message,
line 5400 is a new one: 		    "%s\n", str);
line 5410 is a new one:       __libc_message ((action & 2) ? (do_abort | do_backtrace) : do_message,
line 5411 is a new one: 		      "*** Error in `%s': %s: 0x%s ***\n",
line 5489 is a new one:       __libc_lock_lock (ar_ptr->mutex);
line 5532 is a new one: 		size_t r_size = chunksize_nomask (r);
line 5534 is a new one: 		sizes[NFASTBINS - 1 + i].total += r_size;
line 5536 is a new one: 		  = MIN (sizes[NFASTBINS - 1 + i].from, r_size);
line 5538 is a new one: 						   r_size);
line 5549 is a new one:       __libc_lock_unlock (ar_ptr->mutex);
line 5640 is a new one: #if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_26)
line 5641 is a new one: compat_symbol (libc, __libc_free, cfree, GLIBC_2_0);
