Comparison of files: malloc_v2_24.c and malloc_v2_22.c
line 1 is a new one:    Copyright (C) 1996-2016 Free Software Foundation, Inc.
line 243 is a new one: /* For ALIGN_UP et. al.  */
line 246 is a new one: #include <malloc/malloc-internal.h>
line 286 is a new one:    : __malloc_assert (#expr, __FILE__, __LINE__, __func__))
line 354 is a new one: # define MALLOC_ALIGNMENT       (2 * SIZE_SZ < __alignof__ (long double) \
line 355 is a new one: 				 ? __alignof__ (long double) : 2 * SIZE_SZ)
line 493 is a new one: /* We may need to support __malloc_initialize_hook for backwards
line 494 is a new one:    compatibility.  */
line 496 is a new one: #if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_24)
line 497 is a new one: # define HAVE_MALLOC_INIT_HOOK 1
line 499 is a new one: # define HAVE_MALLOC_INIT_HOOK 0
line 649 is a new one:   usmblks:   always 0
line 1704 is a new one:   /* Linked list for free arenas.  Access to this field is serialized
line 1705 is a new one:      by free_list_lock in arena.c.  */
line 1708 is a new one:   /* Number of threads attached to this arena.  0 if the arena is on
line 1709 is a new one:      the free list.  Access to this field is serialized by
line 1710 is a new one:      free_list_lock in arena.c.  */
line 1711 is a new one:   INTERNAL_SIZE_T attached_threads;
line 1752 is a new one:   .mutex = _LIBC_LOCK_INITIALIZER,
line 1753 is a new one:   .next = &main_arena,
line 1754 is a new one:   .attached_threads = 1
line 1757 is a new one: /* These variables are used for undumping support.  Chunked are marked
line 1758 is a new one:    as using mmap, but we leave them alone if they fall into this
line 1759 is a new one:    range.  NB: The chunk size for these chunks only includes the
line 1760 is a new one:    initial size field (of SIZE_SZ bytes), there is no trailing size
line 1761 is a new one:    field (unlike with regular mmapped chunks).  */
line 1762 is a new one: static mchunkptr dumped_main_arena_start; /* Inclusive.  */
line 1763 is a new one: static mchunkptr dumped_main_arena_end;   /* Exclusive.  */
line 1765 is a new one: /* True if the pointer falls into the dumped arena.  Use this after
line 1766 is a new one:    chunk_is_mmapped indicates a chunk is mmapped.  */
line 1767 is a new one: #define DUMPED_MAIN_ARENA_CHUNK(p) \
line 1768 is a new one:   ((p) >= dumped_main_arena_start && (p) < dumped_main_arena_end)
line 1852 is a new one: #if HAVE_MALLOC_INIT_HOOK
line 1854 is a new one: compat_symbol (libc, __malloc_initialize_hook,
line 1855 is a new one: 	       __malloc_initialize_hook, GLIBC_2_0);
line 1964 is a new one:   else if (!DUMPED_MAIN_ARENA_CHUNK (p))
line 2782 is a new one:   /* Release in pagesize units and round down to the nearest page.  */
line 2783 is a new one:   extra = ALIGN_DOWN(top_area - pad, pagesize);
line 2839 is a new one:   /* Do nothing if the chunk is a faked mmapped chunk in the dumped
line 2840 is a new one:      main arena.  We never free this memory.  */
line 2841 is a new one:   if (DUMPED_MAIN_ARENA_CHUNK (p))
line 2964 is a new one:       /* See if the dynamic brk/mmap threshold needs adjusting.
line 2965 is a new one: 	 Dumped fake mmapped chunks do not affect the threshold.  */
line 2968 is a new one:           && p->size <= DEFAULT_MMAP_THRESHOLD_MAX
line 2969 is a new one: 	  && !DUMPED_MAIN_ARENA_CHUNK (p))
line 3019 is a new one:   /* Little security check which won't hurt performance: the allocator
line 3020 is a new one:      never wrapps around at the end of the address space.  Therefore
line 3021 is a new one:      we can exclude some size values which might appear here by
line 3022 is a new one:      accident or by "design" from some intruder.  We need to bypass
line 3023 is a new one:      this check for dumped fake mmap chunks from the old main arena
line 3024 is a new one:      because the new malloc may provide additional alignment.  */
line 3025 is a new one:   if ((__builtin_expect ((uintptr_t) oldp > (uintptr_t) -oldsize, 0)
line 3026 is a new one:        || __builtin_expect (misaligned_chunk (oldp), 0))
line 3027 is a new one:       && !DUMPED_MAIN_ARENA_CHUNK (oldp))
line 3038 is a new one:       /* If this is a faked mmapped chunk from the dumped main arena,
line 3039 is a new one: 	 always make a copy (and do not free the old chunk).  */
line 3040 is a new one:       if (DUMPED_MAIN_ARENA_CHUNK (oldp))
line 3042 is a new one: 	  /* Must alloc, copy, free. */
line 3043 is a new one: 	  void *newmem = __libc_malloc (bytes);
line 3044 is a new one: 	  if (newmem == 0)
line 3045 is a new one: 	    return NULL;
line 3046 is a new one: 	  /* Copy as many bytes as are available from the old chunk
line 3047 is a new one: 	     and fit into the new size.  NB: The overhead for faked
line 3048 is a new one: 	     mmapped chunks is only SIZE_SZ, not 2 * SIZE_SZ as for
line 3049 is a new one: 	     regular mmapped chunks.  */
line 3050 is a new one: 	  if (bytes > oldsize - SIZE_SZ)
line 3051 is a new one: 	    bytes = oldsize - SIZE_SZ;
line 3052 is a new one: 	  memcpy (newmem, oldmem, bytes);
line 3053 is a new one: 	  return newmem;
line 4194 is a new one:       p = atomic_exchange_acq (fb, NULL);
line 4625 is a new one: 	  if (DUMPED_MAIN_ARENA_CHUNK (p))
line 4626 is a new one: 	    return chunksize (p) - SIZE_SZ;
line 4628 is a new one: 	    return chunksize (p) - 2 * SIZE_SZ;
line 4708 is a new one:       m->usmblks = 0;
line 4715 is a new one: __libc_mallinfo (void)
