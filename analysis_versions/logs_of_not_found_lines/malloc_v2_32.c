Comparison of files: malloc_v2_32.c and malloc_v2_30.c
line 1 is a new one:    Copyright (C) 1996-2020 Free Software Foundation, Inc.
line 18 is a new one:    not, see <https://www.gnu.org/licenses/>.  */
line 329 is a new one: /* Safe-Linking:
line 330 is a new one:    Use randomness from ASLR (mmap_base) to protect single-linked lists
line 331 is a new one:    of Fast-Bins and TCache.  That is, mask the "next" pointers of the
line 332 is a new one:    lists' chunks, and also perform allocation alignment checks on them.
line 333 is a new one:    This mechanism reduces the risk of pointer hijacking, as was done with
line 334 is a new one:    Safe-Unlinking in the double-linked lists of Small-Bins.
line 335 is a new one:    It assumes a minimum page size of 4096 bytes (12 bits).  Systems with
line 336 is a new one:    larger pages provide less entropy, although the pointer mangling
line 337 is a new one:    still works.  */
line 338 is a new one: #define PROTECT_PTR(pos, ptr) \
line 339 is a new one:   ((__typeof (ptr)) ((((size_t) pos) >> 12) ^ ((size_t) ptr)))
line 340 is a new one: #define REVEAL_PTR(ptr)  PROTECT_PTR (&ptr, ptr)
line 1634 is a new one:   global_max_fast = (((size_t) (s) <= MALLOC_ALIGN_MASK - SIZE_SZ)	\
line 1635 is a new one:                      ? MIN_CHUNK_SIZE / 2 : ((s + SIZE_SZ) & ~MALLOC_ALIGN_MASK))
line 2171 is a new one: 	  if (__glibc_unlikely (misaligned_chunk (p)))
line 2172 is a new one: 	    malloc_printerr ("do_check_malloc_state(): "
line 2173 is a new one: 			     "unaligned fastbin chunk detected");
line 2179 is a new one: 	  p = REVEAL_PTR (p->fd);
line 2940 is a new one:   e->next = PROTECT_PTR (&e->next, tcache->entries[tc_idx]);
line 2951 is a new one:   if (__glibc_unlikely (!aligned_OK (e)))
line 2952 is a new one:     malloc_printerr ("malloc(): unaligned tcache chunk detected");
line 2953 is a new one:   tcache->entries[tc_idx] = REVEAL_PTR (e->next);
line 2979 is a new one: 	  if (__glibc_unlikely (!aligned_OK (e)))
line 2980 is a new one: 	    malloc_printerr ("tcache_thread_shutdown(): "
line 2981 is a new one: 			     "unaligned tcache chunk detected");
line 2982 is a new one: 	  tcache_tmp->entries[i] = REVEAL_PTR (e->next);
line 3592 is a new one:       pp = REVEAL_PTR (victim->fd);                                     \
line 3593 is a new one:       if (__glibc_unlikely (pp != NULL && misaligned_chunk (pp)))       \
line 3594 is a new one: 	malloc_printerr ("malloc(): unaligned fastbin chunk detected"); \
line 3596 is a new one:   while ((pp = catomic_compare_and_exchange_val_acq (fb, pp, victim)) \
line 3608 is a new one: 	  if (__glibc_unlikely (misaligned_chunk (victim)))
line 3609 is a new one: 	    malloc_printerr ("malloc(): unaligned fastbin chunk detected 2");
line 3612 is a new one: 	    *fb = REVEAL_PTR (victim->fd);
line 3633 is a new one: 		      if (__glibc_unlikely (misaligned_chunk (tc_victim)))
line 3634 is a new one: 			malloc_printerr ("malloc(): unaligned fastbin chunk detected 3");
line 3636 is a new one: 			*fb = REVEAL_PTR (tc_victim->fd);
line 4226 is a new one: 		 tmp = REVEAL_PTR (tmp->next))
line 4228 is a new one: 		if (__glibc_unlikely (!aligned_OK (tmp)))
line 4229 is a new one: 		  malloc_printerr ("free(): unaligned chunk detected in tcache 2");
line 4230 is a new one: 		if (tmp == e)
line 4231 is a new one: 		  malloc_printerr ("free(): double free detected in tcache 2");
line 4232 is a new one: 		/* If we get here, it was a coincidence.  We've wasted a
line 4233 is a new one: 		   few cycles, but don't abort.  */
line 4298 is a new one: 	p->fd = PROTECT_PTR (&p->fd, old);
line 4308 is a new one: 	  old2 = old;
line 4309 is a new one: 	  p->fd = PROTECT_PTR (&p->fd, old);
line 4507 is a new one: 	  if (__glibc_unlikely (misaligned_chunk (p)))
line 4508 is a new one: 	    malloc_printerr ("malloc_consolidate(): "
line 4509 is a new one: 			     "unaligned fastbin chunk detected");
line 4517 is a new one: 	nextp = REVEAL_PTR (p->fd);
line 4935 is a new one:       for (p = fastbin (av, i);
line 4936 is a new one: 	   p != 0;
line 4937 is a new one: 	   p = REVEAL_PTR (p->fd))
line 4939 is a new one: 	  if (__glibc_unlikely (misaligned_chunk (p)))
line 4940 is a new one: 	    malloc_printerr ("int_mallinfo(): "
line 4941 is a new one: 			     "unaligned fastbin chunk detected");
line 5130 is a new one:   if (value <= MAX_TCACHE_SIZE)
line 5161 is a new one: static inline int
line 5162 is a new one: __always_inline
line 5163 is a new one: do_set_mxfast (size_t value)
line 5165 is a new one:   if (value <= MAX_FAST_SIZE)
line 5167 is a new one:       LIBC_PROBE (memory_mallopt_mxfast, 2, value, get_max_fast ());
line 5168 is a new one:       set_max_fast (value);
line 5190 is a new one:   /* Many of these helper functions take a size_t.  We do not worry
line 5191 is a new one:      about overflow here, because negative int values will wrap to
line 5192 is a new one:      very large size_t values and the helpers have sufficient range
line 5193 is a new one:      checking for such conversions.  Many of these helpers are also
line 5194 is a new one:      used by the tunables macros in arena.c.  */
line 5199 is a new one:       res = do_set_mxfast (value);
line 5203 is a new one:       res = do_set_trim_threshold (value);
line 5207 is a new one:       res = do_set_top_pad (value);
line 5215 is a new one:       res = do_set_mmaps_max (value);
line 5219 is a new one:       res = do_set_mallopt_check (value);
line 5223 is a new one:       res = do_set_perturb_byte (value);
line 5228 is a new one: 	res = do_set_arena_test (value);
line 5233 is a new one: 	res = do_set_arena_max (value);
line 5465 is a new one:       /* Account for top chunk.  The top-most available chunk is
line 5466 is a new one: 	 treated specially and is never in any bin. See "initial_top"
line 5467 is a new one: 	 comments.  */
line 5468 is a new one:       avail = chunksize (ar_ptr->top);
line 5469 is a new one:       nblocks = 1;  /* Top always exists.  */
line 5481 is a new one: 		  if (__glibc_unlikely (misaligned_chunk (p)))
line 5482 is a new one: 		    malloc_printerr ("__malloc_info(): "
line 5483 is a new one: 				     "unaligned fastbin chunk detected");
line 5485 is a new one: 		  p = REVEAL_PTR (p->fd);
line 5559 is a new one: 	  fprintf (fp, "\
