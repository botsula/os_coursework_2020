Comparison of files: malloc_v2_12.c and malloc_v2_10.c
line 1 is a new one:    Copyright (C) 1996-2009, 2010 Free Software Foundation, Inc.
line 150 is a new one:        Also SVID/XPG, ANSI C, and probably others as well.
line 2352 is a new one:   global_max_fast = (((s) == 0)						      \
line 2353 is a new one: 		     ? SMALLBIN_WIDTH: ((s + SIZE_SZ) & ~MALLOC_ALIGN_MASK))
line 3937 is a new one:       p = _int_memalign(ar_ptr, pagesz, bytes);
line 3983 is a new one:       p = _int_memalign(ar_ptr, pagesz, rounded_bytes);
line 4305 is a new one: 	  errstr = "malloc(): memory corruption (fast)";
line 4306 is a new one: 	errout:
line 4307 is a new one: 	  malloc_printerr (check_action, errstr, chunk2mem (victim));
line 4308 is a new one: 	  return NULL;
line 4338 is a new one: 	if (__builtin_expect (bck->fd != victim, 0))
line 4340 is a new one: 	    errstr = "malloc(): smallbin double linked list corrupted";
line 4552 is a new one: 	  if (__builtin_expect (fwd->bk != bck, 0))
line 4554 is a new one: 	      errstr = "malloc(): corrupted unsorted chunks";
line 4555 is a new one: 	      goto errout;
line 4652 is a new one: 	  if (__builtin_expect (fwd->bk != bck, 0))
line 4654 is a new one: 	      errstr = "malloc(): corrupted unsorted chunks 2";
line 4655 is a new one: 	      goto errout;
line 4852 is a new one:       free_perturb (chunk2mem(p), size - 2 * SIZE_SZ);
line 4855 is a new one:     unsigned int idx = fastbin_index(size);
line 4856 is a new one:     fb = &fastbin (av, idx);
line 4861 is a new one:     unsigned int old_idx = ~0u;
line 4871 is a new one: 	if (old != NULL)
line 4872 is a new one: 	  old_idx = fastbin_index(chunksize(old));
line 4877 is a new one:     if (fd != NULL && __builtin_expect (old_idx != idx, 0))
line 4879 is a new one: 	errstr = "invalid fastbin entry (free)";
line 4890 is a new one:     if (*fb != NULL
line 4891 is a new one: 	&& __builtin_expect (fastbin_index(chunksize(*fb)) != idx, 0))
line 4893 is a new one: 	errstr = "invalid fastbin entry (free)";
line 4956 is a new one:       free_perturb (chunk2mem(p), size - 2 * SIZE_SZ);
line 4985 is a new one:       if (__builtin_expect (fwd->bk != bck, 0))
line 4987 is a new one: 	  errstr = "free(): corrupted unsorted chunks";
line 4988 is a new one: 	  goto errout;
line 6390 is a new one:     if (r != NULL)
line 6394 is a new one: 	    ++sizes[NFASTBINS].count;
line 6395 is a new one: 	    sizes[NFASTBINS].total += r->size;
line 6396 is a new one: 	    sizes[NFASTBINS].from = MIN (sizes[NFASTBINS].from, r->size);
line 6397 is a new one: 	    sizes[NFASTBINS].to = MAX (sizes[NFASTBINS].to, r->size);
line 6400 is a new one: 	nblocks += sizes[NFASTBINS].count;
line 6401 is a new one: 	avail += sizes[NFASTBINS].total;
line 6412 is a new one: 	if (r != NULL)
line 6413 is a new one: 	  while (r != bin)
line 6415 is a new one: 	      ++sizes[NFASTBINS - 1 + i].count;
line 6416 is a new one: 	      sizes[NFASTBINS - 1 + i].total += r->size;
line 6417 is a new one: 	      sizes[NFASTBINS - 1 + i].from
line 6418 is a new one: 		= MIN (sizes[NFASTBINS - 1 + i].from, r->size);
line 6419 is a new one: 	      sizes[NFASTBINS - 1 + i].to = MAX (sizes[NFASTBINS - 1 + i].to,
line 6422 is a new one: 	      r = r->fd;
line 6502 is a new one: 	   "<system type=\"current\" size=\"%zu\"/>\n"
line 6503 is a new one: 	   "<system type=\"max\" size=\"%zu\"/>\n"
