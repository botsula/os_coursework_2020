Comparison of files: malloc_v2_20.c and malloc_v2_18.c
line 1 is a new one:    Copyright (C) 1996-2014 Free Software Foundation, Inc.
line 24 is a new one:   There have been substantial changes made after the integration into
line 240 is a new one: /* For MIN, MAX, powerof2.  */
line 272 is a new one: #ifndef MALLOC_DEBUG
line 273 is a new one: #define MALLOC_DEBUG 0
line 359 is a new one: #  define MALLOC_ALIGNMENT       (2 *SIZE_SZ < __alignof__ (long double)      \
line 360 is a new one:                                   ? __alignof__ (long double) : 2 *SIZE_SZ)
line 362 is a new one: #  define MALLOC_ALIGNMENT       (2 *SIZE_SZ)
line 472 is a new one: # define MORECORE_CLEARS 1
line 1056 is a new one: static void*  _mid_memalign(size_t, size_t, void *);
line 1156 is a new one:     Chunks always begin on even word boundaries, so the mem portion
line 1241 is a new one:   ((unsigned long) (req) >=						      \
line 1242 is a new one:    (unsigned long) (INTERNAL_SIZE_T) (-2 * MINSIZE))
line 1254 is a new one:   if (REQUEST_OUT_OF_RANGE (req)) {					      \
line 1255 is a new one:       __set_errno (ENOMEM);						      \
line 1256 is a new one:       return 0;								      \
line 1257 is a new one:     }									      \
line 1258 is a new one:   (sz) = request2size (req);
line 1261 is a new one:    --------------- Physical chunk operations ---------------
line 1289 is a new one:    Bits to mask off when extracting size
line 1291 is a new one:    Note: IS_MMAPPED is intentionally not masked off from size field in
line 1292 is a new one:    macros for which mmapped chunks should never be seen. This should
line 1293 is a new one:    cause helpful core dumps to occur if it is tried by accident by
line 1294 is a new one:    people extending or adapting this malloc.
line 1296 is a new one: #define SIZE_BITS (PREV_INUSE | IS_MMAPPED | NON_MAIN_ARENA)
line 1303 is a new one: #define next_chunk(p) ((mchunkptr) (((char *) (p)) + ((p)->size & ~SIZE_BITS)))
line 1306 is a new one: #define prev_chunk(p) ((mchunkptr) (((char *) (p)) - ((p)->prev_size)))
line 1309 is a new one: #define chunk_at_offset(p, s)  ((mchunkptr) (((char *) (p)) + (s)))
line 1312 is a new one: #define inuse(p)							      \
line 1313 is a new one:   ((((mchunkptr) (((char *) (p)) + ((p)->size & ~SIZE_BITS)))->size) & PREV_INUSE)
line 1316 is a new one: #define set_inuse(p)							      \
line 1317 is a new one:   ((mchunkptr) (((char *) (p)) + ((p)->size & ~SIZE_BITS)))->size |= PREV_INUSE
line 1319 is a new one: #define clear_inuse(p)							      \
line 1320 is a new one:   ((mchunkptr) (((char *) (p)) + ((p)->size & ~SIZE_BITS)))->size &= ~(PREV_INUSE)
line 1324 is a new one: #define inuse_bit_at_offset(p, s)					      \
line 1325 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->size & PREV_INUSE)
line 1327 is a new one: #define set_inuse_bit_at_offset(p, s)					      \
line 1328 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->size |= PREV_INUSE)
line 1330 is a new one: #define clear_inuse_bit_at_offset(p, s)					      \
line 1331 is a new one:   (((mchunkptr) (((char *) (p)) + (s)))->size &= ~(PREV_INUSE))
line 1341 is a new one: #define set_foot(p, s)       (((mchunkptr) ((char *) (p) + (s)))->prev_size = (s))
line 1345 is a new one:    -------------------- Internal data structures --------------------
line 1350 is a new one:  * If USE_MALLOC_LOCK is defined, the mALLOC_MUTEx declared above.
line 1351 is a new one:  * If mmap doesn't support MAP_ANONYMOUS, a dummy file descriptor
line 1360 is a new one:    Bins
line 1395 is a new one: typedef struct malloc_chunk *mbinptr;
line 1400 is a new one:              - offsetof (struct malloc_chunk, fd))
line 1403 is a new one: #define next_bin(b)  ((mbinptr) ((char *) (b) + (sizeof (mchunkptr) << 1)))
line 1411 is a new one:     FD = P->fd;								      \
line 1412 is a new one:     BK = P->bk;								      \
line 1413 is a new one:     if (__builtin_expect (FD->bk != P || BK->fd != P, 0))		      \
line 1414 is a new one:       malloc_printerr (check_action, "corrupted double-linked list", P);      \
line 1415 is a new one:     else {								      \
line 1416 is a new one:         FD->bk = BK;							      \
line 1417 is a new one:         BK->fd = FD;							      \
line 1418 is a new one:         if (!in_smallbin_range (P->size)				      \
line 1419 is a new one:             && __builtin_expect (P->fd_nextsize != NULL, 0)) {		      \
line 1420 is a new one:             assert (P->fd_nextsize->bk_nextsize == P);			      \
line 1421 is a new one:             assert (P->bk_nextsize->fd_nextsize == P);			      \
line 1422 is a new one:             if (FD->fd_nextsize == NULL) {				      \
line 1423 is a new one:                 if (P->fd_nextsize == P)				      \
line 1424 is a new one:                   FD->fd_nextsize = FD->bk_nextsize = FD;		      \
line 1425 is a new one:                 else {							      \
line 1426 is a new one:                     FD->fd_nextsize = P->fd_nextsize;			      \
line 1427 is a new one:                     FD->bk_nextsize = P->bk_nextsize;			      \
line 1428 is a new one:                     P->fd_nextsize->bk_nextsize = FD;			      \
line 1429 is a new one:                     P->bk_nextsize->fd_nextsize = FD;			      \
line 1430 is a new one:                   }							      \
line 1431 is a new one:               } else {							      \
line 1432 is a new one:                 P->fd_nextsize->bk_nextsize = P->bk_nextsize;		      \
line 1433 is a new one:                 P->bk_nextsize->fd_nextsize = P->fd_nextsize;		      \
line 1434 is a new one:               }								      \
line 1435 is a new one:           }								      \
line 1436 is a new one:       }									      \
line 1440 is a new one:    Indexing
line 1470 is a new one:   ((unsigned long) (sz) < (unsigned long) MIN_LARGE_SIZE)
line 1473 is a new one:   ((SMALLBIN_WIDTH == 16 ? (((unsigned) (sz)) >> 4) : (((unsigned) (sz)) >> 3))\
line 1477 is a new one:   (((((unsigned long) (sz)) >> 6) <= 38) ?  56 + (((unsigned long) (sz)) >> 6) :\
line 1478 is a new one:    ((((unsigned long) (sz)) >> 9) <= 20) ?  91 + (((unsigned long) (sz)) >> 9) :\
line 1479 is a new one:    ((((unsigned long) (sz)) >> 12) <= 10) ? 110 + (((unsigned long) (sz)) >> 12) :\
line 1480 is a new one:    ((((unsigned long) (sz)) >> 15) <= 4) ? 119 + (((unsigned long) (sz)) >> 15) :\
line 1481 is a new one:    ((((unsigned long) (sz)) >> 18) <= 2) ? 124 + (((unsigned long) (sz)) >> 18) :\
line 1482 is a new one:    126)
line 1485 is a new one:   (((((unsigned long) (sz)) >> 6) <= 45) ?  49 + (((unsigned long) (sz)) >> 6) :\
line 1486 is a new one:    ((((unsigned long) (sz)) >> 9) <= 20) ?  91 + (((unsigned long) (sz)) >> 9) :\
line 1487 is a new one:    ((((unsigned long) (sz)) >> 12) <= 10) ? 110 + (((unsigned long) (sz)) >> 12) :\
line 1488 is a new one:    ((((unsigned long) (sz)) >> 15) <= 4) ? 119 + (((unsigned long) (sz)) >> 15) :\
line 1489 is a new one:    ((((unsigned long) (sz)) >> 18) <= 2) ? 124 + (((unsigned long) (sz)) >> 18) :\
line 1490 is a new one:    126)
line 1496 is a new one:   (((((unsigned long) (sz)) >> 6) <= 48) ?  48 + (((unsigned long) (sz)) >> 6) :\
line 1497 is a new one:    ((((unsigned long) (sz)) >> 9) <= 20) ?  91 + (((unsigned long) (sz)) >> 9) :\
line 1498 is a new one:    ((((unsigned long) (sz)) >> 12) <= 10) ? 110 + (((unsigned long) (sz)) >> 12) :\
line 1499 is a new one:    ((((unsigned long) (sz)) >> 15) <= 4) ? 119 + (((unsigned long) (sz)) >> 15) :\
line 1500 is a new one:    ((((unsigned long) (sz)) >> 18) <= 2) ? 124 + (((unsigned long) (sz)) >> 18) :\
line 1501 is a new one:    126)
line 1509 is a new one:   ((in_smallbin_range (sz)) ? smallbin_index (sz) : largebin_index (sz))
line 1513 is a new one:    Unsorted chunks
line 1527 is a new one: #define unsorted_chunks(M)          (bin_at (M, 1))
line 1530 is a new one:    Top
line 1548 is a new one: #define initial_top(M)              (unsorted_chunks (M))
line 1551 is a new one:    Binmap
line 1567 is a new one: #define idx2bit(i)       ((1U << ((i) & ((1U << BINMAPSHIFT) - 1))))
line 1569 is a new one: #define mark_bin(m, i)    ((m)->binmap[idx2block (i)] |= idx2bit (i))
line 1570 is a new one: #define unmark_bin(m, i)  ((m)->binmap[idx2block (i)] &= ~(idx2bit (i)))
line 1571 is a new one: #define get_binmap(m, i)  ((m)->binmap[idx2block (i)] & idx2bit (i))
line 1574 is a new one:    Fastbins
line 1590 is a new one: typedef struct malloc_chunk *mfastbinptr;
line 1595 is a new one:   ((((unsigned int) (sz)) >> (SIZE_SZ == 8 ? 4 : 3)) - 2)
line 1601 is a new one: #define NFASTBINS  (fastbin_index (request2size (MAX_FAST_SIZE)) + 1)
line 1604 is a new one:    FASTBIN_CONSOLIDATION_THRESHOLD is the size of a chunk in free()
line 1605 is a new one:    that triggers automatic consolidation of possibly-surrounding
line 1606 is a new one:    fastbin chunks. This is a heuristic, so the exact value should not
line 1607 is a new one:    matter too much. It is defined at half the default trim threshold as a
line 1608 is a new one:    compromise heuristic to only attempt consolidation if it is likely
line 1609 is a new one:    to lead to trimming. However, it is not dynamically tunable, since
line 1610 is a new one:    consolidation reduces fragmentation surrounding large chunks even
line 1611 is a new one:    if trimming is not used.
line 1617 is a new one:    Since the lowest 2 bits in max_fast don't matter in size comparisons,
line 1618 is a new one:    they are used as flags.
line 1622 is a new one:    FASTCHUNKS_BIT held in max_fast indicates that there are probably
line 1623 is a new one:    some fastbin chunks. It is set true on entering a chunk into any
line 1624 is a new one:    fastbin, and cleared only in malloc_consolidate.
line 1626 is a new one:    The truth value is inverted so that have_fastchunks will be true
line 1627 is a new one:    upon startup (since statics are zero-filled), simplifying
line 1628 is a new one:    initialization checks.
line 1633 is a new one: #define have_fastchunks(M)     (((M)->flags & FASTCHUNKS_BIT) == 0)
line 1638 is a new one:    NONCONTIGUOUS_BIT indicates that MORECORE does not return contiguous
line 1639 is a new one:    regions.  Otherwise, contiguity is exploited in merging together,
line 1640 is a new one:    when possible, results from consecutive MORECORE calls.
line 1642 is a new one:    The initial value comes from MORECORE_CONTIGUOUS, but is
line 1643 is a new one:    changed dynamically if mmap is ever used as an sbrk substitute.
line 1648 is a new one: #define contiguous(M)          (((M)->flags & NONCONTIGUOUS_BIT) == 0)
line 1649 is a new one: #define noncontiguous(M)       (((M)->flags & NONCONTIGUOUS_BIT) != 0)
line 1650 is a new one: #define set_noncontiguous(M)   ((M)->flags |= NONCONTIGUOUS_BIT)
line 1662 is a new one:                      ? SMALLBIN_WIDTH : ((s + SIZE_SZ) & ~MALLOC_ALIGN_MASK))
line 1670 is a new one: struct malloc_state
line 1679 is a new one:   mfastbinptr fastbinsY[NFASTBINS];
line 1682 is a new one:   mchunkptr top;
line 1685 is a new one:   mchunkptr last_remainder;
line 1688 is a new one:   mchunkptr bins[NBINS * 2 - 2];
line 1691 is a new one:   unsigned int binmap[BINMAPSIZE];
line 1704 is a new one: struct malloc_par
line 1707 is a new one:   unsigned long trim_threshold;
line 1708 is a new one:   INTERNAL_SIZE_T top_pad;
line 1709 is a new one:   INTERNAL_SIZE_T mmap_threshold;
line 1710 is a new one:   INTERNAL_SIZE_T arena_test;
line 1711 is a new one:   INTERNAL_SIZE_T arena_max;
line 1714 is a new one:   int n_mmaps;
line 1715 is a new one:   int n_mmaps_max;
line 1716 is a new one:   int max_n_mmaps;
line 1720 is a new one:   int no_dyn_threshold;
line 1723 is a new one:   INTERNAL_SIZE_T mmapped_mem;
line 1726 is a new one:   INTERNAL_SIZE_T max_mmapped_mem;
line 1727 is a new one:   INTERNAL_SIZE_T max_total_mem;  /* only kept for NO_THREADS */
line 1730 is a new one:   char *sbrk_base;
line 1741 is a new one:   .mutex = MUTEX_INITIALIZER,
line 1742 is a new one:   .next = &main_arena
line 1749 is a new one:   .top_pad = DEFAULT_TOP_PAD,
line 1750 is a new one:   .n_mmaps_max = DEFAULT_MMAP_MAX,
line 1751 is a new one:   .mmap_threshold = DEFAULT_MMAP_THRESHOLD,
line 1752 is a new one:   .trim_threshold = DEFAULT_TRIM_THRESHOLD,
line 1753 is a new one: #define NARENAS_FROM_NCORES(n) ((n) * (sizeof (long) == 4 ? 2 : 8))
line 1754 is a new one:   .arena_test = NARENAS_FROM_NCORES (1)
line 1767 is a new one:    Initialize a malloc_state struct.
line 1769 is a new one:    This is called only from within malloc_consolidate, which needs
line 1770 is a new one:    be called in the same contexts anyway.  It is never called directly
line 1771 is a new one:    outside of malloc_consolidate because some optimizing compilers try
line 1772 is a new one:    to inline it at all call points, which turns out not to be an
line 1773 is a new one:    optimization at all. (Inlining it in malloc_consolidate is fine though.)
line 1777 is a new one: malloc_init_state (mstate av)
line 1783 is a new one:   for (i = 1; i < NBINS; ++i)
line 1785 is a new one:       bin = bin_at (av, i);
line 1786 is a new one:       bin->fd = bin->bk = bin;
line 1792 is a new one:   set_noncontiguous (av);
line 1794 is a new one:     set_max_fast (DEFAULT_MXFAST);
line 1797 is a new one:   av->top = initial_top (av);
line 1804 is a new one: static void *sysmalloc (INTERNAL_SIZE_T, mstate);
line 1805 is a new one: static int      systrim (size_t, mstate);
line 1806 is a new one: static void     malloc_consolidate (mstate);
line 1820 is a new one: static void *malloc_hook_ini (size_t sz,
line 1821 is a new one:                               const void *caller) __THROW;
line 1822 is a new one: static void *realloc_hook_ini (void *ptr, size_t sz,
line 1823 is a new one:                                const void *caller) __THROW;
line 1824 is a new one: static void *memalign_hook_ini (size_t alignment, size_t sz,
line 1825 is a new one:                                 const void *caller) __THROW;
line 1829 is a new one:                                    const void *) = NULL;
line 1831 is a new one:   (size_t __size, const void *) = malloc_hook_ini;
line 1833 is a new one:   (void *__ptr, size_t __size, const void *)
line 1834 is a new one:   = realloc_hook_ini;
line 1836 is a new one:   (size_t __alignment, size_t __size, const void *)
line 1837 is a new one:   = memalign_hook_ini;
line 1844 is a new one: # define DEFAULT_CHECK_ACTION 3
line 1854 is a new one: static inline void
line 1855 is a new one: alloc_perturb (char *p, size_t n)
line 1857 is a new one:   if (__glibc_unlikely (perturb_byte))
line 1858 is a new one:     memset (p, perturb_byte ^ 0xff, n);
line 1861 is a new one: static inline void
line 1862 is a new one: free_perturb (char *p, size_t n)
line 1864 is a new one:   if (__glibc_unlikely (perturb_byte))
line 1865 is a new one:     memset (p, perturb_byte, n);
line 1870 is a new one: #include <stap-probe.h>
line 1876 is a new one:    Debugging support
line 1878 is a new one:    These routines make a number of assertions about the states
line 1879 is a new one:    of data structures that should be true at all times. If any
line 1880 is a new one:    are not true, it's very likely that a user program has somehow
line 1881 is a new one:    trashed memory. (It's also possible that there is a coding error
line 1882 is a new one:    in malloc. In which case, please report it!)
line 1885 is a new one: #if !MALLOC_DEBUG
line 1887 is a new one: # define check_chunk(A, P)
line 1888 is a new one: # define check_free_chunk(A, P)
line 1889 is a new one: # define check_inuse_chunk(A, P)
line 1890 is a new one: # define check_remalloced_chunk(A, P, N)
line 1891 is a new one: # define check_malloced_chunk(A, P, N)
line 1892 is a new one: # define check_malloc_state(A)
line 1896 is a new one: # define check_chunk(A, P)              do_check_chunk (A, P)
line 1897 is a new one: # define check_free_chunk(A, P)         do_check_free_chunk (A, P)
line 1898 is a new one: # define check_inuse_chunk(A, P)        do_check_inuse_chunk (A, P)
line 1899 is a new one: # define check_remalloced_chunk(A, P, N) do_check_remalloced_chunk (A, P, N)
line 1900 is a new one: # define check_malloced_chunk(A, P, N)   do_check_malloced_chunk (A, P, N)
line 1901 is a new one: # define check_malloc_state(A)         do_check_malloc_state (A)
line 1904 is a new one:    Properties of all chunks
line 1908 is a new one: do_check_chunk (mstate av, mchunkptr p)
line 1910 is a new one:   unsigned long sz = chunksize (p);
line 1912 is a new one:   char *max_address = (char *) (av->top) + chunksize (av->top);
line 1913 is a new one:   char *min_address = max_address - av->system_mem;
line 1915 is a new one:   if (!chunk_is_mmapped (p))
line 1917 is a new one:       /* Has legal address ... */
line 1918 is a new one:       if (p != av->top)
line 1919 is a new one:         {
line 1920 is a new one:           if (contiguous (av))
line 1921 is a new one:             {
line 1922 is a new one:               assert (((char *) p) >= min_address);
line 1923 is a new one:               assert (((char *) p + sz) <= ((char *) (av->top)));
line 1924 is a new one:             }
line 1925 is a new one:         }
line 1927 is a new one:         {
line 1928 is a new one:           /* top size is always at least MINSIZE */
line 1929 is a new one:           assert ((unsigned long) (sz) >= MINSIZE);
line 1930 is a new one:           /* top predecessor always marked inuse */
line 1931 is a new one:           assert (prev_inuse (p));
line 1932 is a new one:         }
line 1936 is a new one:       /* address is outside main heap  */
line 1937 is a new one:       if (contiguous (av) && av->top != initial_top (av))
line 1938 is a new one:         {
line 1939 is a new one:           assert (((char *) p) < min_address || ((char *) p) >= max_address);
line 1940 is a new one:         }
line 1941 is a new one:       /* chunk is page-aligned */
line 1942 is a new one:       assert (((p->prev_size + sz) & (GLRO (dl_pagesize) - 1)) == 0);
line 1943 is a new one:       /* mem is aligned */
line 1944 is a new one:       assert (aligned_OK (chunk2mem (p)));
line 1949 is a new one:    Properties of free chunks
line 1953 is a new one: do_check_free_chunk (mstate av, mchunkptr p)
line 1955 is a new one:   INTERNAL_SIZE_T sz = p->size & ~(PREV_INUSE | NON_MAIN_ARENA);
line 1956 is a new one:   mchunkptr next = chunk_at_offset (p, sz);
line 1958 is a new one:   do_check_chunk (av, p);
line 1961 is a new one:   assert (!inuse (p));
line 1962 is a new one:   assert (!chunk_is_mmapped (p));
line 1965 is a new one:   if ((unsigned long) (sz) >= MINSIZE)
line 1967 is a new one:       assert ((sz & MALLOC_ALIGN_MASK) == 0);
line 1968 is a new one:       assert (aligned_OK (chunk2mem (p)));
line 1969 is a new one:       /* ... matching footer field */
line 1970 is a new one:       assert (next->prev_size == sz);
line 1971 is a new one:       /* ... and is fully consolidated */
line 1972 is a new one:       assert (prev_inuse (p));
line 1973 is a new one:       assert (next == av->top || inuse (next));
line 1975 is a new one:       /* ... and has minimally sane links */
line 1976 is a new one:       assert (p->fd->bk == p);
line 1977 is a new one:       assert (p->bk->fd == p);
line 1980 is a new one:     assert (sz == SIZE_SZ);
line 1984 is a new one:    Properties of inuse chunks
line 1988 is a new one: do_check_inuse_chunk (mstate av, mchunkptr p)
line 1992 is a new one:   do_check_chunk (av, p);
line 1998 is a new one:   assert (inuse (p));
line 2000 is a new one:   next = next_chunk (p);
line 2003 is a new one:      Since more things can be checked with free chunks than inuse ones,
line 2004 is a new one:      if an inuse chunk borders them and debug is on, it's worth doing them.
line 2005 is a new one:    */
line 2006 is a new one:   if (!prev_inuse (p))
line 2008 is a new one:       /* Note that we cannot even look at prev unless it is not inuse */
line 2009 is a new one:       mchunkptr prv = prev_chunk (p);
line 2010 is a new one:       assert (next_chunk (prv) == p);
line 2011 is a new one:       do_check_free_chunk (av, prv);
line 2014 is a new one:   if (next == av->top)
line 2016 is a new one:       assert (prev_inuse (next));
line 2017 is a new one:       assert (chunksize (next) >= MINSIZE);
line 2019 is a new one:   else if (!inuse (next))
line 2020 is a new one:     do_check_free_chunk (av, next);
line 2024 is a new one:    Properties of chunks recycled from fastbins
line 2028 is a new one: do_check_remalloced_chunk (mstate av, mchunkptr p, INTERNAL_SIZE_T s)
line 2030 is a new one:   INTERNAL_SIZE_T sz = p->size & ~(PREV_INUSE | NON_MAIN_ARENA);
line 2032 is a new one:   if (!chunk_is_mmapped (p))
line 2034 is a new one:       assert (av == arena_for_chunk (p));
line 2035 is a new one:       if (chunk_non_main_arena (p))
line 2036 is a new one:         assert (av != &main_arena);
line 2038 is a new one:         assert (av == &main_arena);
line 2041 is a new one:   do_check_inuse_chunk (av, p);
line 2044 is a new one:   assert ((sz & MALLOC_ALIGN_MASK) == 0);
line 2045 is a new one:   assert ((unsigned long) (sz) >= MINSIZE);
line 2047 is a new one:   assert (aligned_OK (chunk2mem (p)));
line 2049 is a new one:   assert ((long) (sz) - (long) (s) >= 0);
line 2050 is a new one:   assert ((long) (sz) - (long) (s + MINSIZE) < 0);
line 2054 is a new one:    Properties of nonrecycled chunks at the point they are malloced
line 2058 is a new one: do_check_malloced_chunk (mstate av, mchunkptr p, INTERNAL_SIZE_T s)
line 2061 is a new one:   do_check_remalloced_chunk (av, p, s);
line 2064 is a new one:      ... plus,  must obey implementation invariant that prev_inuse is
line 2065 is a new one:      always true of any allocated chunk; i.e., that each allocated
line 2066 is a new one:      chunk borders either a previously allocated and still in-use
line 2067 is a new one:      chunk, or the base of its memory arena. This is ensured
line 2068 is a new one:      by making all allocations from the `lowest' part of any found
line 2069 is a new one:      chunk.  This does not necessarily hold however for chunks
line 2070 is a new one:      recycled via fastbins.
line 2071 is a new one:    */
line 2073 is a new one:   assert (prev_inuse (p));
line 2078 is a new one:    Properties of malloc_state.
line 2080 is a new one:    This may be useful for debugging malloc, as well as detecting user
line 2081 is a new one:    programmer errors that somehow write into malloc_state.
line 2083 is a new one:    If you are extending or experimenting with this malloc, you can
line 2084 is a new one:    probably figure out how to hack this routine to print out or
line 2085 is a new one:    display chunk addresses, sizes, bins, and other instrumentation.
line 2089 is a new one: do_check_malloc_state (mstate av)
line 2101 is a new one:   assert (sizeof (INTERNAL_SIZE_T) <= sizeof (char *));
line 2104 is a new one:   assert ((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT - 1)) == 0);
line 2107 is a new one:   if (av->top == 0 || av->top == initial_top (av))
line 2111 is a new one:   assert ((GLRO (dl_pagesize) & (GLRO (dl_pagesize) - 1)) == 0);
line 2114 is a new one:   if (av == &main_arena && contiguous (av))
line 2115 is a new one:     assert ((char *) mp_.sbrk_base + av->system_mem ==
line 2116 is a new one:             (char *) av->top + chunksize (av->top));
line 2121 is a new one:   assert ((get_max_fast () & ~1) <= request2size (MAX_FAST_SIZE));
line 2123 is a new one:   max_fast_bin = fastbin_index (get_max_fast ());
line 2125 is a new one:   for (i = 0; i < NFASTBINS; ++i)
line 2127 is a new one:       p = fastbin (av, i);
line 2129 is a new one:       /* The following test can only be performed for the main arena.
line 2130 is a new one:          While mallopt calls malloc_consolidate to get rid of all fast
line 2131 is a new one:          bins (especially those larger than the new maximum) this does
line 2132 is a new one:          only happen for the main arena.  Trying to do this for any
line 2133 is a new one:          other arena would mean those arenas have to be locked and
line 2134 is a new one:          malloc_consolidate be called for them.  This is excessive.  And
line 2135 is a new one:          even if this is acceptable to somebody it still cannot solve
line 2136 is a new one:          the problem completely since if the arena is locked a
line 2137 is a new one:          concurrent malloc call might create a new arena which then
line 2138 is a new one:          could use the newly invalid fast bins.  */
line 2140 is a new one:       /* all bins past max_fast are empty */
line 2141 is a new one:       if (av == &main_arena && i > max_fast_bin)
line 2142 is a new one:         assert (p == 0);
line 2144 is a new one:       while (p != 0)
line 2145 is a new one:         {
line 2146 is a new one:           /* each chunk claims to be inuse */
line 2147 is a new one:           do_check_inuse_chunk (av, p);
line 2148 is a new one:           total += chunksize (p);
line 2149 is a new one:           /* chunk belongs in this bin */
line 2150 is a new one:           assert (fastbin_index (chunksize (p)) == i);
line 2151 is a new one:           p = p->fd;
line 2152 is a new one:         }
line 2156 is a new one:     assert (have_fastchunks (av));
line 2157 is a new one:   else if (!have_fastchunks (av))
line 2158 is a new one:     assert (total == 0);
line 2161 is a new one:   for (i = 1; i < NBINS; ++i)
line 2163 is a new one:       b = bin_at (av, i);
line 2165 is a new one:       /* binmap is accurate (except for bin 1 == unsorted_chunks) */
line 2166 is a new one:       if (i >= 2)
line 2167 is a new one:         {
line 2168 is a new one:           unsigned int binbit = get_binmap (av, i);
line 2169 is a new one:           int empty = last (b) == b;
line 2170 is a new one:           if (!binbit)
line 2171 is a new one:             assert (empty);
line 2172 is a new one:           else if (!empty)
line 2173 is a new one:             assert (binbit);
line 2174 is a new one:         }
line 2176 is a new one:       for (p = last (b); p != b; p = p->bk)
line 2177 is a new one:         {
line 2178 is a new one:           /* each chunk claims to be free */
line 2179 is a new one:           do_check_free_chunk (av, p);
line 2180 is a new one:           size = chunksize (p);
line 2181 is a new one:           total += size;
line 2182 is a new one:           if (i >= 2)
line 2183 is a new one:             {
line 2184 is a new one:               /* chunk belongs in bin */
line 2185 is a new one:               idx = bin_index (size);
line 2186 is a new one:               assert (idx == i);
line 2187 is a new one:               /* lists are sorted */
line 2188 is a new one:               assert (p->bk == b ||
line 2189 is a new one:                       (unsigned long) chunksize (p->bk) >= (unsigned long) chunksize (p));
line 2191 is a new one:               if (!in_smallbin_range (size))
line 2192 is a new one:                 {
line 2193 is a new one:                   if (p->fd_nextsize != NULL)
line 2194 is a new one:                     {
line 2195 is a new one:                       if (p->fd_nextsize == p)
line 2196 is a new one:                         assert (p->bk_nextsize == p);
line 2197 is a new one:                       else
line 2198 is a new one:                         {
line 2199 is a new one:                           if (p->fd_nextsize == first (b))
line 2200 is a new one:                             assert (chunksize (p) < chunksize (p->fd_nextsize));
line 2201 is a new one:                           else
line 2202 is a new one:                             assert (chunksize (p) > chunksize (p->fd_nextsize));
line 2204 is a new one:                           if (p == first (b))
line 2205 is a new one:                             assert (chunksize (p) > chunksize (p->bk_nextsize));
line 2206 is a new one:                           else
line 2207 is a new one:                             assert (chunksize (p) < chunksize (p->bk_nextsize));
line 2208 is a new one:                         }
line 2209 is a new one:                     }
line 2210 is a new one:                   else
line 2211 is a new one:                     assert (p->bk_nextsize == NULL);
line 2212 is a new one:                 }
line 2213 is a new one:             }
line 2214 is a new one:           else if (!in_smallbin_range (size))
line 2215 is a new one:             assert (p->fd_nextsize == NULL && p->bk_nextsize == NULL);
line 2216 is a new one:           /* chunk is followed by a legal chain of inuse chunks */
line 2217 is a new one:           for (q = next_chunk (p);
line 2218 is a new one:                (q != av->top && inuse (q) &&
line 2219 is a new one:                 (unsigned long) (chunksize (q)) >= MINSIZE);
line 2220 is a new one:                q = next_chunk (q))
line 2221 is a new one:             do_check_inuse_chunk (av, q);
line 2222 is a new one:         }
line 2226 is a new one:   check_chunk (av, av->top);
line 2238 is a new one:    sysmalloc handles malloc cases requiring more memory from the system.
line 2239 is a new one:    On entry, it is assumed that av->top does not have enough
line 2240 is a new one:    space to service request for nb bytes, thus requiring that av->top
line 2241 is a new one:    be extended or replaced.
line 2244 is a new one: static void *
line 2245 is a new one: sysmalloc (INTERNAL_SIZE_T nb, mstate av)
line 2247 is a new one:   mchunkptr old_top;              /* incoming value of av->top */
line 2249 is a new one:   char *old_end;                  /* its end address */
line 2251 is a new one:   long size;                      /* arg to first MORECORE or mmap call */
line 2252 is a new one:   char *brk;                      /* return value from MORECORE */
line 2254 is a new one:   long correction;                /* arg to 2nd MORECORE call */
line 2255 is a new one:   char *snd_brk;                  /* 2nd return val */
line 2259 is a new one:   char *aligned_brk;              /* aligned offset into brk */
line 2261 is a new one:   mchunkptr p;                    /* the allocated/returned chunk */
line 2262 is a new one:   mchunkptr remainder;            /* remainder from allocation */
line 2263 is a new one:   unsigned long remainder_size;   /* its size */
line 2266 is a new one:   size_t pagemask = GLRO (dl_pagesize) - 1;
line 2267 is a new one:   bool tried_mmap = false;
line 2271 is a new one:      If have mmap, and the request size meets the mmap threshold, and
line 2272 is a new one:      the system supports mmap, and there are few enough currently
line 2273 is a new one:      allocated mmapped regions, try to directly map this request
line 2274 is a new one:      rather than expanding top.
line 2275 is a new one:    */
line 2277 is a new one:   if ((unsigned long) (nb) >= (unsigned long) (mp_.mmap_threshold) &&
line 2278 is a new one:       (mp_.n_mmaps < mp_.n_mmaps_max))
line 2280 is a new one:       char *mm;           /* return value from mmap call*/
line 2282 is a new one:     try_mmap:
line 2284 is a new one:          Round up size to nearest page.  For mmapped chunks, the overhead
line 2285 is a new one:          is one SIZE_SZ unit larger than for normal chunks, because there
line 2286 is a new one:          is no following chunk whose prev_size field could be used.
line 2288 is a new one:          See the front_misalign handling below, for glibc there is no
line 2289 is a new one:          need for further alignments unless we have have high alignment.
line 2290 is a new one:        */
line 2291 is a new one:       if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2292 is a new one:         size = (nb + SIZE_SZ + pagemask) & ~pagemask;
line 2294 is a new one:         size = (nb + SIZE_SZ + MALLOC_ALIGN_MASK + pagemask) & ~pagemask;
line 2295 is a new one:       tried_mmap = true;
line 2297 is a new one:       /* Don't try if size wraps around 0 */
line 2298 is a new one:       if ((unsigned long) (size) > (unsigned long) (nb))
line 2299 is a new one:         {
line 2300 is a new one:           mm = (char *) (MMAP (0, size, PROT_READ | PROT_WRITE, 0));
line 2302 is a new one:           if (mm != MAP_FAILED)
line 2303 is a new one:             {
line 2304 is a new one:               /*
line 2305 is a new one:                  The offset to the start of the mmapped region is stored
line 2306 is a new one:                  in the prev_size field of the chunk. This allows us to adjust
line 2307 is a new one:                  returned start address to meet alignment requirements here
line 2308 is a new one:                  and in memalign(), and still be able to compute proper
line 2309 is a new one:                  address argument for later munmap in free() and realloc().
line 2310 is a new one:                */
line 2312 is a new one:               if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2313 is a new one:                 {
line 2314 is a new one:                   /* For glibc, chunk2mem increases the address by 2*SIZE_SZ and
line 2315 is a new one:                      MALLOC_ALIGN_MASK is 2*SIZE_SZ-1.  Each mmap'ed area is page
line 2316 is a new one:                      aligned and therefore definitely MALLOC_ALIGN_MASK-aligned.  */
line 2317 is a new one:                   assert (((INTERNAL_SIZE_T) chunk2mem (mm) & MALLOC_ALIGN_MASK) == 0);
line 2318 is a new one:                   front_misalign = 0;
line 2319 is a new one:                 }
line 2320 is a new one:               else
line 2321 is a new one:                 front_misalign = (INTERNAL_SIZE_T) chunk2mem (mm) & MALLOC_ALIGN_MASK;
line 2322 is a new one:               if (front_misalign > 0)
line 2323 is a new one:                 {
line 2324 is a new one:                   correction = MALLOC_ALIGNMENT - front_misalign;
line 2325 is a new one:                   p = (mchunkptr) (mm + correction);
line 2326 is a new one:                   p->prev_size = correction;
line 2327 is a new one:                   set_head (p, (size - correction) | IS_MMAPPED);
line 2328 is a new one:                 }
line 2329 is a new one:               else
line 2330 is a new one:                 {
line 2331 is a new one:                   p = (mchunkptr) mm;
line 2332 is a new one:                   set_head (p, size | IS_MMAPPED);
line 2333 is a new one:                 }
line 2335 is a new one:               /* update statistics */
line 2337 is a new one:               int new = atomic_exchange_and_add (&mp_.n_mmaps, 1) + 1;
line 2338 is a new one:               atomic_max (&mp_.max_n_mmaps, new);
line 2340 is a new one:               unsigned long sum;
line 2341 is a new one:               sum = atomic_exchange_and_add (&mp_.mmapped_mem, size) + size;
line 2342 is a new one:               atomic_max (&mp_.max_mmapped_mem, sum);
line 2344 is a new one:               check_chunk (av, p);
line 2346 is a new one:               return chunk2mem (p);
line 2347 is a new one:             }
line 2348 is a new one:         }
line 2353 is a new one:   old_top = av->top;
line 2354 is a new one:   old_size = chunksize (old_top);
line 2355 is a new one:   old_end = (char *) (chunk_at_offset (old_top, old_size));
line 2357 is a new one:   brk = snd_brk = (char *) (MORECORE_FAILURE);
line 2362 is a new one:    */
line 2364 is a new one:   assert ((old_top == initial_top (av) && old_size == 0) ||
line 2365 is a new one:           ((unsigned long) (old_size) >= MINSIZE &&
line 2366 is a new one:            prev_inuse (old_top) &&
line 2367 is a new one:            ((unsigned long) old_end & pagemask) == 0));
line 2370 is a new one:   assert ((unsigned long) (old_size) < (unsigned long) (nb + MINSIZE));
line 2375 is a new one:       heap_info *old_heap, *heap;
line 2376 is a new one:       size_t old_heap_size;
line 2378 is a new one:       /* First try to extend the current heap. */
line 2379 is a new one:       old_heap = heap_for_ptr (old_top);
line 2380 is a new one:       old_heap_size = old_heap->size;
line 2381 is a new one:       if ((long) (MINSIZE + nb - old_size) > 0
line 2382 is a new one:           && grow_heap (old_heap, MINSIZE + nb - old_size) == 0)
line 2383 is a new one:         {
line 2384 is a new one:           av->system_mem += old_heap->size - old_heap_size;
line 2385 is a new one:           arena_mem += old_heap->size - old_heap_size;
line 2386 is a new one:           set_head (old_top, (((char *) old_heap + old_heap->size) - (char *) old_top)
line 2387 is a new one:                     | PREV_INUSE);
line 2388 is a new one:         }
line 2389 is a new one:       else if ((heap = new_heap (nb + (MINSIZE + sizeof (*heap)), mp_.top_pad)))
line 2390 is a new one:         {
line 2391 is a new one:           /* Use a newly allocated heap.  */
line 2392 is a new one:           heap->ar_ptr = av;
line 2393 is a new one:           heap->prev = old_heap;
line 2394 is a new one:           av->system_mem += heap->size;
line 2395 is a new one:           arena_mem += heap->size;
line 2396 is a new one:           /* Set up the new top.  */
line 2397 is a new one:           top (av) = chunk_at_offset (heap, sizeof (*heap));
line 2398 is a new one:           set_head (top (av), (heap->size - sizeof (*heap)) | PREV_INUSE);
line 2400 is a new one:           /* Setup fencepost and free the old top chunk with a multiple of
line 2401 is a new one:              MALLOC_ALIGNMENT in size. */
line 2402 is a new one:           /* The fencepost takes at least MINSIZE bytes, because it might
line 2403 is a new one:              become the top chunk again later.  Note that a footer is set
line 2404 is a new one:              up, too, although the chunk is marked in use. */
line 2405 is a new one:           old_size = (old_size - MINSIZE) & ~MALLOC_ALIGN_MASK;
line 2406 is a new one:           set_head (chunk_at_offset (old_top, old_size + 2 * SIZE_SZ), 0 | PREV_INUSE);
line 2407 is a new one:           if (old_size >= MINSIZE)
line 2408 is a new one:             {
line 2409 is a new one:               set_head (chunk_at_offset (old_top, old_size), (2 * SIZE_SZ) | PREV_INUSE);
line 2410 is a new one:               set_foot (chunk_at_offset (old_top, old_size), (2 * SIZE_SZ));
line 2411 is a new one:               set_head (old_top, old_size | PREV_INUSE | NON_MAIN_ARENA);
line 2412 is a new one:               _int_free (av, old_top, 1);
line 2413 is a new one:             }
line 2414 is a new one:           else
line 2415 is a new one:             {
line 2416 is a new one:               set_head (old_top, (old_size + 2 * SIZE_SZ) | PREV_INUSE);
line 2417 is a new one:               set_foot (old_top, (old_size + 2 * SIZE_SZ));
line 2418 is a new one:             }
line 2419 is a new one:         }
line 2420 is a new one:       else if (!tried_mmap)
line 2421 is a new one:         /* We can at least try to use to mmap memory.  */
line 2422 is a new one:         goto try_mmap;
line 2424 is a new one:   else     /* av == main_arena */
line 2427 is a new one:     { /* Request enough space for nb + pad + overhead */
line 2428 is a new one:       size = nb + mp_.top_pad + MINSIZE;
line 2431 is a new one:          If contiguous, we can subtract out existing space that we hope to
line 2432 is a new one:          combine with new space. We add it back later only if
line 2433 is a new one:          we don't actually get contiguous space.
line 2434 is a new one:        */
line 2436 is a new one:       if (contiguous (av))
line 2437 is a new one:         size -= old_size;
line 2440 is a new one:          Round to a multiple of page size.
line 2441 is a new one:          If MORECORE is not contiguous, this ensures that we only call it
line 2442 is a new one:          with whole-page arguments.  And if MORECORE is contiguous and
line 2443 is a new one:          this is not first time through, this preserves page-alignment of
line 2444 is a new one:          previous calls. Otherwise, we correct to page-align below.
line 2445 is a new one:        */
line 2447 is a new one:       size = (size + pagemask) & ~pagemask;
line 2450 is a new one:          Don't try to call MORECORE if argument is so big as to appear
line 2451 is a new one:          negative. Note that since mmap takes size_t arg, it may succeed
line 2452 is a new one:          below even if we cannot call MORECORE.
line 2453 is a new one:        */
line 2455 is a new one:       if (size > 0)
line 2456 is a new one:         {
line 2457 is a new one:           brk = (char *) (MORECORE (size));
line 2458 is a new one:           LIBC_PROBE (memory_sbrk_more, 2, brk, size);
line 2459 is a new one:         }
line 2461 is a new one:       if (brk != (char *) (MORECORE_FAILURE))
line 2462 is a new one:         {
line 2463 is a new one:           /* Call the `morecore' hook if necessary.  */
line 2464 is a new one:           void (*hook) (void) = atomic_forced_read (__after_morecore_hook);
line 2465 is a new one:           if (__builtin_expect (hook != NULL, 0))
line 2466 is a new one:             (*hook)();
line 2467 is a new one:         }
line 2469 is a new one:         {
line 2470 is a new one:           /*
line 2471 is a new one:              If have mmap, try using it as a backup when MORECORE fails or
line 2472 is a new one:              cannot be used. This is worth doing on systems that have "holes" in
line 2473 is a new one:              address space, so sbrk cannot extend to give contiguous space, but
line 2474 is a new one:              space is available elsewhere.  Note that we ignore mmap max count
line 2475 is a new one:              and threshold limits, since the space will not be used as a
line 2476 is a new one:              segregated mmap region.
line 2477 is a new one:            */
line 2479 is a new one:           /* Cannot merge with old top, so add its size back in */
line 2480 is a new one:           if (contiguous (av))
line 2481 is a new one:             size = (size + old_size + pagemask) & ~pagemask;
line 2483 is a new one:           /* If we are relying on mmap as backup, then use larger units */
line 2484 is a new one:           if ((unsigned long) (size) < (unsigned long) (MMAP_AS_MORECORE_SIZE))
line 2485 is a new one:             size = MMAP_AS_MORECORE_SIZE;
line 2487 is a new one:           /* Don't try if size wraps around 0 */
line 2488 is a new one:           if ((unsigned long) (size) > (unsigned long) (nb))
line 2489 is a new one:             {
line 2490 is a new one:               char *mbrk = (char *) (MMAP (0, size, PROT_READ | PROT_WRITE, 0));
line 2492 is a new one:               if (mbrk != MAP_FAILED)
line 2493 is a new one:                 {
line 2494 is a new one:                   /* We do not need, and cannot use, another sbrk call to find end */
line 2495 is a new one:                   brk = mbrk;
line 2496 is a new one:                   snd_brk = brk + size;
line 2498 is a new one:                   /*
line 2499 is a new one:                      Record that we no longer have a contiguous sbrk region.
line 2500 is a new one:                      After the first time mmap is used as backup, we do not
line 2501 is a new one:                      ever rely on contiguous space since this could incorrectly
line 2502 is a new one:                      bridge regions.
line 2503 is a new one:                    */
line 2504 is a new one:                   set_noncontiguous (av);
line 2505 is a new one:                 }
line 2506 is a new one:             }
line 2507 is a new one:         }
line 2509 is a new one:       if (brk != (char *) (MORECORE_FAILURE))
line 2510 is a new one:         {
line 2511 is a new one:           if (mp_.sbrk_base == 0)
line 2512 is a new one:             mp_.sbrk_base = brk;
line 2513 is a new one:           av->system_mem += size;
line 2515 is a new one:           /*
line 2516 is a new one:              If MORECORE extends previous space, we can likewise extend top size.
line 2517 is a new one:            */
line 2519 is a new one:           if (brk == old_end && snd_brk == (char *) (MORECORE_FAILURE))
line 2520 is a new one:             set_head (old_top, (size + old_size) | PREV_INUSE);
line 2522 is a new one:           else if (contiguous (av) && old_size && brk < old_end)
line 2523 is a new one:             {
line 2524 is a new one:               /* Oops!  Someone else killed our space..  Can't touch anything.  */
line 2525 is a new one:               malloc_printerr (3, "break adjusted to free malloc space", brk);
line 2526 is a new one:             }
line 2528 is a new one:           /*
line 2529 is a new one:              Otherwise, make adjustments:
line 2531 is a new one:            * If the first time through or noncontiguous, we need to call sbrk
line 2532 is a new one:               just to find out where the end of memory lies.
line 2534 is a new one:            * We need to ensure that all returned chunks from malloc will meet
line 2535 is a new one:               MALLOC_ALIGNMENT
line 2537 is a new one:            * If there was an intervening foreign sbrk, we need to adjust sbrk
line 2538 is a new one:               request size to account for fact that we will not be able to
line 2539 is a new one:               combine new space with existing space in old_top.
line 2541 is a new one:            * Almost all systems internally allocate whole pages at a time, in
line 2542 is a new one:               which case we might as well use the whole last page of request.
line 2543 is a new one:               So we allocate enough more memory to hit a page boundary now,
line 2544 is a new one:               which in turn causes future contiguous calls to page-align.
line 2545 is a new one:            */
line 2547 is a new one:           else
line 2548 is a new one:             {
line 2549 is a new one:               front_misalign = 0;
line 2550 is a new one:               end_misalign = 0;
line 2551 is a new one:               correction = 0;
line 2552 is a new one:               aligned_brk = brk;
line 2554 is a new one:               /* handle contiguous cases */
line 2555 is a new one:               if (contiguous (av))
line 2556 is a new one:                 {
line 2557 is a new one:                   /* Count foreign sbrk as system_mem.  */
line 2558 is a new one:                   if (old_size)
line 2559 is a new one:                     av->system_mem += brk - old_end;
line 2561 is a new one:                   /* Guarantee alignment of first new chunk made from this space */
line 2563 is a new one:                   front_misalign = (INTERNAL_SIZE_T) chunk2mem (brk) & MALLOC_ALIGN_MASK;
line 2564 is a new one:                   if (front_misalign > 0)
line 2565 is a new one:                     {
line 2566 is a new one:                       /*
line 2567 is a new one:                          Skip over some bytes to arrive at an aligned position.
line 2568 is a new one:                          We don't need to specially mark these wasted front bytes.
line 2569 is a new one:                          They will never be accessed anyway because
line 2570 is a new one:                          prev_inuse of av->top (and any chunk created from its start)
line 2571 is a new one:                          is always true after initialization.
line 2572 is a new one:                        */
line 2574 is a new one:                       correction = MALLOC_ALIGNMENT - front_misalign;
line 2575 is a new one:                       aligned_brk += correction;
line 2576 is a new one:                     }
line 2578 is a new one:                   /*
line 2579 is a new one:                      If this isn't adjacent to existing space, then we will not
line 2580 is a new one:                      be able to merge with old_top space, so must add to 2nd request.
line 2581 is a new one:                    */
line 2583 is a new one:                   correction += old_size;
line 2585 is a new one:                   /* Extend the end address to hit a page boundary */
line 2586 is a new one:                   end_misalign = (INTERNAL_SIZE_T) (brk + size + correction);
line 2587 is a new one:                   correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;
line 2589 is a new one:                   assert (correction >= 0);
line 2590 is a new one:                   snd_brk = (char *) (MORECORE (correction));
line 2592 is a new one:                   /*
line 2593 is a new one:                      If can't allocate correction, try to at least find out current
line 2594 is a new one:                      brk.  It might be enough to proceed without failing.
line 2596 is a new one:                      Note that if second sbrk did NOT fail, we assume that space
line 2597 is a new one:                      is contiguous with first sbrk. This is a safe assumption unless
line 2598 is a new one:                      program is multithreaded but doesn't use locks and a foreign sbrk
line 2599 is a new one:                      occurred between our first and second calls.
line 2600 is a new one:                    */
line 2602 is a new one:                   if (snd_brk == (char *) (MORECORE_FAILURE))
line 2603 is a new one:                     {
line 2604 is a new one:                       correction = 0;
line 2605 is a new one:                       snd_brk = (char *) (MORECORE (0));
line 2606 is a new one:                     }
line 2607 is a new one:                   else
line 2608 is a new one:                     {
line 2609 is a new one:                       /* Call the `morecore' hook if necessary.  */
line 2610 is a new one:                       void (*hook) (void) = atomic_forced_read (__after_morecore_hook);
line 2611 is a new one:                       if (__builtin_expect (hook != NULL, 0))
line 2612 is a new one:                         (*hook)();
line 2613 is a new one:                     }
line 2614 is a new one:                 }
line 2616 is a new one:               /* handle non-contiguous cases */
line 2617 is a new one:               else
line 2618 is a new one:                 {
line 2619 is a new one:                   if (MALLOC_ALIGNMENT == 2 * SIZE_SZ)
line 2620 is a new one:                     /* MORECORE/mmap must correctly align */
line 2621 is a new one:                     assert (((unsigned long) chunk2mem (brk) & MALLOC_ALIGN_MASK) == 0);
line 2622 is a new one:                   else
line 2623 is a new one:                     {
line 2624 is a new one:                       front_misalign = (INTERNAL_SIZE_T) chunk2mem (brk) & MALLOC_ALIGN_MASK;
line 2625 is a new one:                       if (front_misalign > 0)
line 2626 is a new one:                         {
line 2627 is a new one:                           /*
line 2628 is a new one:                              Skip over some bytes to arrive at an aligned position.
line 2629 is a new one:                              We don't need to specially mark these wasted front bytes.
line 2630 is a new one:                              They will never be accessed anyway because
line 2631 is a new one:                              prev_inuse of av->top (and any chunk created from its start)
line 2632 is a new one:                              is always true after initialization.
line 2633 is a new one:                            */
line 2635 is a new one:                           aligned_brk += MALLOC_ALIGNMENT - front_misalign;
line 2636 is a new one:                         }
line 2637 is a new one:                     }
line 2639 is a new one:                   /* Find out current end of memory */
line 2640 is a new one:                   if (snd_brk == (char *) (MORECORE_FAILURE))
line 2641 is a new one:                     {
line 2642 is a new one:                       snd_brk = (char *) (MORECORE (0));
line 2643 is a new one:                     }
line 2644 is a new one:                 }
line 2646 is a new one:               /* Adjust top based on results of second sbrk */
line 2647 is a new one:               if (snd_brk != (char *) (MORECORE_FAILURE))
line 2648 is a new one:                 {
line 2649 is a new one:                   av->top = (mchunkptr) aligned_brk;
line 2650 is a new one:                   set_head (av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
line 2651 is a new one:                   av->system_mem += correction;
line 2653 is a new one:                   /*
line 2654 is a new one:                      If not the first time through, we either have a
line 2655 is a new one:                      gap due to foreign sbrk or a non-contiguous region.  Insert a
line 2656 is a new one:                      double fencepost at old_top to prevent consolidation with space
line 2657 is a new one:                      we don't own. These fenceposts are artificial chunks that are
line 2658 is a new one:                      marked as inuse and are in any case too small to use.  We need
line 2659 is a new one:                      two to make sizes and alignments work out.
line 2660 is a new one:                    */
line 2662 is a new one:                   if (old_size != 0)
line 2663 is a new one:                     {
line 2664 is a new one:                       /*
line 2665 is a new one:                          Shrink old_top to insert fenceposts, keeping size a
line 2666 is a new one:                          multiple of MALLOC_ALIGNMENT. We know there is at least
line 2667 is a new one:                          enough space in old_top to do this.
line 2668 is a new one:                        */
line 2669 is a new one:                       old_size = (old_size - 4 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
line 2670 is a new one:                       set_head (old_top, old_size | PREV_INUSE);
line 2672 is a new one:                       /*
line 2673 is a new one:                          Note that the following assignments completely overwrite
line 2674 is a new one:                          old_top when old_size was previously MINSIZE.  This is
line 2675 is a new one:                          intentional. We need the fencepost, even if old_top otherwise gets
line 2676 is a new one:                          lost.
line 2677 is a new one:                        */
line 2678 is a new one:                       chunk_at_offset (old_top, old_size)->size =
line 2679 is a new one:                         (2 * SIZE_SZ) | PREV_INUSE;
line 2681 is a new one:                       chunk_at_offset (old_top, old_size + 2 * SIZE_SZ)->size =
line 2682 is a new one:                         (2 * SIZE_SZ) | PREV_INUSE;
line 2684 is a new one:                       /* If possible, release the rest. */
line 2685 is a new one:                       if (old_size >= MINSIZE)
line 2686 is a new one:                         {
line 2687 is a new one:                           _int_free (av, old_top, 1);
line 2688 is a new one:                         }
line 2689 is a new one:                     }
line 2690 is a new one:                 }
line 2691 is a new one:             }
line 2692 is a new one:         }
line 2693 is a new one:     } /* if (av !=  &main_arena) */
line 2695 is a new one:   if ((unsigned long) av->system_mem > (unsigned long) (av->max_system_mem))
line 2697 is a new one:   check_malloc_state (av);
line 2701 is a new one:   size = chunksize (p);
line 2704 is a new one:   if ((unsigned long) (size) >= (unsigned long) (nb + MINSIZE))
line 2707 is a new one:       remainder = chunk_at_offset (p, nb);
line 2709 is a new one:       set_head (p, nb | PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 2710 is a new one:       set_head (remainder, remainder_size | PREV_INUSE);
line 2711 is a new one:       check_malloced_chunk (av, p, nb);
line 2712 is a new one:       return chunk2mem (p);
line 2722 is a new one:    systrim is an inverse of sorts to sysmalloc.  It gives memory back
line 2723 is a new one:    to the system (via negative arguments to sbrk) if there is unused
line 2724 is a new one:    memory at the `high' end of the malloc pool. It is called
line 2725 is a new one:    automatically by free() when top space exceeds the trim
line 2726 is a new one:    threshold. It is also called by the public malloc_trim routine.  It
line 2727 is a new one:    returns 1 if it actually released any memory, else 0.
line 2730 is a new one: static int
line 2731 is a new one: systrim (size_t pad, mstate av)
line 2733 is a new one:   long top_size;         /* Amount of top-most memory */
line 2734 is a new one:   long extra;            /* Amount to release */
line 2735 is a new one:   long released;         /* Amount actually released */
line 2736 is a new one:   char *current_brk;     /* address returned by pre-check sbrk call */
line 2737 is a new one:   char *new_brk;         /* address returned by post-check sbrk call */
line 2739 is a new one:   long top_area;
line 2741 is a new one:   pagesz = GLRO (dl_pagesize);
line 2742 is a new one:   top_size = chunksize (av->top);
line 2744 is a new one:   top_area = top_size - MINSIZE - 1;
line 2745 is a new one:   if (top_area <= pad)
line 2749 is a new one:   extra = (top_area - pad) & ~(pagesz - 1);
line 2751 is a new one:   if (extra == 0)
line 2755 is a new one:      Only proceed if end of memory is where we last set it.
line 2756 is a new one:      This avoids problems if there were foreign sbrk calls.
line 2757 is a new one:    */
line 2758 is a new one:   current_brk = (char *) (MORECORE (0));
line 2759 is a new one:   if (current_brk == (char *) (av->top) + top_size)
line 2762 is a new one:          Attempt to release memory. We ignore MORECORE return value,
line 2763 is a new one:          and instead call again to find out where new end of memory is.
line 2764 is a new one:          This avoids problems if first call releases less than we asked,
line 2765 is a new one:          of if failure somehow altered brk value. (We could still
line 2766 is a new one:          encounter problems if it altered brk in some very bad way,
line 2767 is a new one:          but the only thing we can do is adjust anyway, which will cause
line 2768 is a new one:          some downstream failure.)
line 2769 is a new one:        */
line 2771 is a new one:       MORECORE (-extra);
line 2773 is a new one:       void (*hook) (void) = atomic_forced_read (__after_morecore_hook);
line 2775 is a new one:         (*hook)();
line 2776 is a new one:       new_brk = (char *) (MORECORE (0));
line 2778 is a new one:       LIBC_PROBE (memory_sbrk_less, 2, new_brk, extra);
line 2780 is a new one:       if (new_brk != (char *) MORECORE_FAILURE)
line 2781 is a new one:         {
line 2782 is a new one:           released = (long) (current_brk - new_brk);
line 2784 is a new one:           if (released != 0)
line 2785 is a new one:             {
line 2786 is a new one:               /* Success. Adjust top. */
line 2787 is a new one:               av->system_mem -= released;
line 2788 is a new one:               set_head (av->top, (top_size - released) | PREV_INUSE);
line 2789 is a new one:               check_malloc_state (av);
line 2790 is a new one:               return 1;
line 2791 is a new one:             }
line 2792 is a new one:         }
line 2799 is a new one: munmap_chunk (mchunkptr p)
line 2801 is a new one:   INTERNAL_SIZE_T size = chunksize (p);
line 2803 is a new one:   assert (chunk_is_mmapped (p));
line 2812 is a new one:   if (__builtin_expect (((block | total_size) & (GLRO (dl_pagesize) - 1)) != 0, 0))
line 2815 is a new one:                        chunk2mem (p));
line 2819 is a new one:   atomic_decrement (&mp_.n_mmaps);
line 2820 is a new one:   atomic_add (&mp_.mmapped_mem, -total_size);
line 2825 is a new one:   __munmap ((char *) block, total_size);
line 2832 is a new one: mremap_chunk (mchunkptr p, size_t new_size)
line 2834 is a new one:   size_t page_mask = GLRO (dl_pagesize) - 1;
line 2836 is a new one:   INTERNAL_SIZE_T size = chunksize (p);
line 2839 is a new one:   assert (chunk_is_mmapped (p));
line 2840 is a new one:   assert (((size + offset) & (GLRO (dl_pagesize) - 1)) == 0);
line 2849 is a new one:   cp = (char *) __mremap ((char *) p - offset, size + offset, new_size,
line 2850 is a new one:                           MREMAP_MAYMOVE);
line 2852 is a new one:   if (cp == MAP_FAILED)
line 2855 is a new one:   p = (mchunkptr) (cp + offset);
line 2857 is a new one:   assert (aligned_OK (chunk2mem (p)));
line 2859 is a new one:   assert ((p->prev_size == offset));
line 2860 is a new one:   set_head (p, (new_size - offset) | IS_MMAPPED);
line 2862 is a new one:   INTERNAL_SIZE_T new;
line 2863 is a new one:   new = atomic_exchange_and_add (&mp_.mmapped_mem, new_size - size - offset)
line 2864 is a new one:         + new_size - size - offset;
line 2865 is a new one:   atomic_max (&mp_.max_mmapped_mem, new);
line 2872 is a new one: void *
line 2873 is a new one: __libc_malloc (size_t bytes)
line 2879 is a new one:     = atomic_forced_read (__malloc_hook);
line 2883 is a new one:   arena_lookup (ar_ptr);
line 2885 is a new one:   arena_lock (ar_ptr, bytes);
line 2886 is a new one:   if (!ar_ptr)
line 2889 is a new one:   victim = _int_malloc (ar_ptr, bytes);
line 2890 is a new one:   if (!victim)
line 2892 is a new one:       LIBC_PROBE (memory_malloc_retry, 1, bytes);
line 2893 is a new one:       ar_ptr = arena_get_retry (ar_ptr, bytes);
line 2894 is a new one:       if (__builtin_expect (ar_ptr != NULL, 1))
line 2895 is a new one:         {
line 2896 is a new one:           victim = _int_malloc (ar_ptr, bytes);
line 2897 is a new one:           (void) mutex_unlock (&ar_ptr->mutex);
line 2898 is a new one:         }
line 2901 is a new one:     (void) mutex_unlock (&ar_ptr->mutex);
line 2902 is a new one:   assert (!victim || chunk_is_mmapped (mem2chunk (victim)) ||
line 2903 is a new one:           ar_ptr == arena_for_chunk (mem2chunk (victim)));
line 2906 is a new one: libc_hidden_def (__libc_malloc)
line 2909 is a new one: __libc_free (void *mem)
line 2915 is a new one:     = atomic_forced_read (__free_hook);
line 2918 is a new one:       (*hook)(mem, RETURN_ADDRESS (0));
line 2925 is a new one:   p = mem2chunk (mem);
line 2927 is a new one:   if (chunk_is_mmapped (p))                       /* release mmapped memory. */
line 2929 is a new one:       /* see if the dynamic brk/mmap threshold needs adjusting */
line 2930 is a new one:       if (!mp_.no_dyn_threshold
line 2931 is a new one:           && p->size > mp_.mmap_threshold
line 2932 is a new one:           && p->size <= DEFAULT_MMAP_THRESHOLD_MAX)
line 2933 is a new one:         {
line 2934 is a new one:           mp_.mmap_threshold = chunksize (p);
line 2935 is a new one:           mp_.trim_threshold = 2 * mp_.mmap_threshold;
line 2936 is a new one:           LIBC_PROBE (memory_mallopt_free_dyn_thresholds, 2,
line 2937 is a new one:                       mp_.mmap_threshold, mp_.trim_threshold);
line 2938 is a new one:         }
line 2939 is a new one:       munmap_chunk (p);
line 2943 is a new one:   ar_ptr = arena_for_chunk (p);
line 2944 is a new one:   _int_free (ar_ptr, p, 0);
line 2948 is a new one: void *
line 2949 is a new one: __libc_realloc (void *oldmem, size_t bytes)
line 2952 is a new one:   INTERNAL_SIZE_T nb;         /* padded request size */
line 2954 is a new one:   void *newp;             /* chunk to return */
line 2957 is a new one:     atomic_forced_read (__realloc_hook);
line 2962 is a new one:   if (bytes == 0 && oldmem != NULL)
line 2964 is a new one:       __libc_free (oldmem); return 0;
line 2969 is a new one:   if (oldmem == 0)
line 2970 is a new one:     return __libc_malloc (bytes);
line 2973 is a new one:   const mchunkptr oldp = mem2chunk (oldmem);
line 2975 is a new one:   const INTERNAL_SIZE_T oldsize = chunksize (oldp);
line 2988 is a new one:   checked_request2size (bytes, nb);
line 2990 is a new one:   if (chunk_is_mmapped (oldp))
line 2992 is a new one:       void *newmem;
line 2995 is a new one:       newp = mremap_chunk (oldp, nb);
line 2996 is a new one:       if (newp)
line 2997 is a new one:         return chunk2mem (newp);
line 2999 is a new one:       /* Note the extra SIZE_SZ overhead. */
line 3000 is a new one:       if (oldsize - SIZE_SZ >= nb)
line 3001 is a new one:         return oldmem;                         /* do nothing */
line 3003 is a new one:       /* Must alloc, copy, free. */
line 3004 is a new one:       newmem = __libc_malloc (bytes);
line 3006 is a new one:         return 0;              /* propagate failure */
line 3008 is a new one:       memcpy (newmem, oldmem, oldsize - 2 * SIZE_SZ);
line 3009 is a new one:       munmap_chunk (oldp);
line 3010 is a new one:       return newmem;
line 3013 is a new one:   ar_ptr = arena_for_chunk (oldp);
line 3014 is a new one:   (void) mutex_lock (&ar_ptr->mutex);
line 3017 is a new one:   newp = _int_realloc (ar_ptr, oldp, oldsize, nb);
line 3019 is a new one:   (void) mutex_unlock (&ar_ptr->mutex);
line 3020 is a new one:   assert (!newp || chunk_is_mmapped (mem2chunk (newp)) ||
line 3021 is a new one:           ar_ptr == arena_for_chunk (mem2chunk (newp)));
line 3026 is a new one:       LIBC_PROBE (memory_realloc_retry, 2, bytes, oldmem);
line 3027 is a new one:       newp = __libc_malloc (bytes);
line 3029 is a new one:         {
line 3030 is a new one:           memcpy (newp, oldmem, oldsize - SIZE_SZ);
line 3031 is a new one:           _int_free (ar_ptr, oldp, 0);
line 3032 is a new one:         }
line 3039 is a new one: void *
line 3040 is a new one: __libc_memalign (size_t alignment, size_t bytes)
line 3042 is a new one:   void *address = RETURN_ADDRESS (0);
line 3043 is a new one:   return _mid_memalign (alignment, bytes, address);
line 3046 is a new one: static void *
line 3047 is a new one: _mid_memalign (size_t alignment, size_t bytes, void *address)
line 3053 is a new one:     atomic_forced_read (__memalign_hook);
line 3055 is a new one:     return (*hook)(alignment, bytes, address);
line 3057 is a new one:   /* If we need less alignment than we give anyway, just relay to malloc.  */
line 3058 is a new one:   if (alignment <= MALLOC_ALIGNMENT)
line 3059 is a new one:     return __libc_malloc (bytes);
line 3062 is a new one:   if (alignment < MINSIZE)
line 3063 is a new one:     alignment = MINSIZE;
line 3065 is a new one:   /* If the alignment is greater than SIZE_MAX / 2 + 1 it cannot be a
line 3066 is a new one:      power of 2 and will cause overflow in the check below.  */
line 3067 is a new one:   if (alignment > SIZE_MAX / 2 + 1)
line 3069 is a new one:       __set_errno (EINVAL);
line 3073 is a new one:   /* Check for overflow.  */
line 3074 is a new one:   if (bytes > SIZE_MAX - alignment - MINSIZE)
line 3081 is a new one:   /* Make sure alignment is power of 2.  */
line 3082 is a new one:   if (!powerof2 (alignment))
line 3084 is a new one:       size_t a = MALLOC_ALIGNMENT * 2;
line 3085 is a new one:       while (a < alignment)
line 3086 is a new one:         a <<= 1;
line 3087 is a new one:       alignment = a;
line 3090 is a new one:   arena_get (ar_ptr, bytes + alignment + MINSIZE);
line 3091 is a new one:   if (!ar_ptr)
line 3094 is a new one:   p = _int_memalign (ar_ptr, alignment, bytes);
line 3095 is a new one:   if (!p)
line 3097 is a new one:       LIBC_PROBE (memory_memalign_retry, 2, bytes, alignment);
line 3098 is a new one:       ar_ptr = arena_get_retry (ar_ptr, bytes);
line 3099 is a new one:       if (__builtin_expect (ar_ptr != NULL, 1))
line 3100 is a new one:         {
line 3101 is a new one:           p = _int_memalign (ar_ptr, alignment, bytes);
line 3102 is a new one:           (void) mutex_unlock (&ar_ptr->mutex);
line 3103 is a new one:         }
line 3106 is a new one:     (void) mutex_unlock (&ar_ptr->mutex);
line 3107 is a new one:   assert (!p || chunk_is_mmapped (mem2chunk (p)) ||
line 3108 is a new one:           ar_ptr == arena_for_chunk (mem2chunk (p)));
line 3115 is a new one: void *
line 3116 is a new one: __libc_valloc (size_t bytes)
line 3118 is a new one:   if (__malloc_initialized < 0)
line 3121 is a new one:   void *address = RETURN_ADDRESS (0);
line 3122 is a new one:   size_t pagesz = GLRO (dl_pagesize);
line 3123 is a new one:   return _mid_memalign (pagesz, bytes, address);
line 3126 is a new one: void *
line 3127 is a new one: __libc_pvalloc (size_t bytes)
line 3129 is a new one:   if (__malloc_initialized < 0)
line 3132 is a new one:   void *address = RETURN_ADDRESS (0);
line 3133 is a new one:   size_t pagesz = GLRO (dl_pagesize);
line 3134 is a new one:   size_t page_mask = GLRO (dl_pagesize) - 1;
line 3137 is a new one:   /* Check for overflow.  */
line 3138 is a new one:   if (bytes > SIZE_MAX - 2 * pagesz - MINSIZE)
line 3144 is a new one:   return _mid_memalign (pagesz, rounded_bytes, address);
line 3147 is a new one: void *
line 3148 is a new one: __libc_calloc (size_t n, size_t elem_size)
line 3156 is a new one:   INTERNAL_SIZE_T *d;
line 3162 is a new one:   if (__builtin_expect ((n | elem_size) >= HALF_INTERNAL_SIZE_T, 0))
line 3164 is a new one:       if (elem_size != 0 && bytes / elem_size != n)
line 3165 is a new one:         {
line 3166 is a new one:           __set_errno (ENOMEM);
line 3167 is a new one:           return 0;
line 3168 is a new one:         }
line 3172 is a new one:     atomic_forced_read (__malloc_hook);
line 3175 is a new one:       sz = bytes;
line 3176 is a new one:       mem = (*hook)(sz, RETURN_ADDRESS (0));
line 3177 is a new one:       if (mem == 0)
line 3178 is a new one:         return 0;
line 3180 is a new one:       return memset (mem, 0, sz);
line 3185 is a new one:   arena_get (av, sz);
line 3186 is a new one:   if (!av)
line 3192 is a new one:   oldtop = top (av);
line 3193 is a new one:   oldtopsize = chunksize (top (av));
line 3194 is a new one: # if MORECORE_CLEARS < 2
line 3197 is a new one:       oldtopsize < mp_.sbrk_base + av->max_system_mem - (char *) oldtop)
line 3198 is a new one:     oldtopsize = (mp_.sbrk_base + av->max_system_mem - (char *) oldtop);
line 3204 is a new one:         oldtopsize = (char *) heap + heap->mprotect_size - (char *) oldtop;
line 3207 is a new one:   mem = _int_malloc (av, sz);
line 3210 is a new one:   assert (!mem || chunk_is_mmapped (mem2chunk (mem)) ||
line 3211 is a new one:           av == arena_for_chunk (mem2chunk (mem)));
line 3213 is a new one:   if (mem == 0)
line 3215 is a new one:       LIBC_PROBE (memory_calloc_retry, 1, sz);
line 3216 is a new one:       av = arena_get_retry (av, sz);
line 3217 is a new one:       if (__builtin_expect (av != NULL, 1))
line 3218 is a new one:         {
line 3219 is a new one:           mem = _int_malloc (av, sz);
line 3220 is a new one:           (void) mutex_unlock (&av->mutex);
line 3221 is a new one:         }
line 3222 is a new one:       if (mem == 0)
line 3223 is a new one:         return 0;
line 3226 is a new one:     (void) mutex_unlock (&av->mutex);
line 3227 is a new one:   p = mem2chunk (mem);
line 3233 is a new one:         return memset (mem, 0, sz);
line 3238 is a new one:   csz = chunksize (p);
line 3241 is a new one:   if (perturb_byte == 0 && (p == oldtop && csz > oldtopsize))
line 3243 is a new one:       /* clear only the bytes from non-freshly-sbrked memory */
line 3244 is a new one:       csz = oldtopsize;
line 3251 is a new one:   d = (INTERNAL_SIZE_T *) mem;
line 3253 is a new one:   nclears = clearsize / sizeof (INTERNAL_SIZE_T);
line 3254 is a new one:   assert (nclears >= 3);
line 3257 is a new one:     return memset (d, 0, clearsize);
line 3261 is a new one:       *(d + 0) = 0;
line 3262 is a new one:       *(d + 1) = 0;
line 3263 is a new one:       *(d + 2) = 0;
line 3264 is a new one:       if (nclears > 4)
line 3265 is a new one:         {
line 3266 is a new one:           *(d + 3) = 0;
line 3267 is a new one:           *(d + 4) = 0;
line 3268 is a new one:           if (nclears > 6)
line 3269 is a new one:             {
line 3270 is a new one:               *(d + 5) = 0;
line 3271 is a new one:               *(d + 6) = 0;
line 3272 is a new one:               if (nclears > 8)
line 3273 is a new one:                 {
line 3274 is a new one:                   *(d + 7) = 0;
line 3275 is a new one:                   *(d + 8) = 0;
line 3276 is a new one:                 }
line 3277 is a new one:             }
line 3278 is a new one:         }
line 3285 is a new one:    ------------------------------ malloc ------------------------------
line 3288 is a new one: static void *
line 3289 is a new one: _int_malloc (mstate av, size_t bytes)
line 3292 is a new one:   unsigned int idx;                 /* associated bin index */
line 3293 is a new one:   mbinptr bin;                      /* associated bin */
line 3295 is a new one:   mchunkptr victim;                 /* inspected/selected chunk */
line 3297 is a new one:   int victim_index;                 /* its bin index */
line 3299 is a new one:   mchunkptr remainder;              /* remainder from a split */
line 3300 is a new one:   unsigned long remainder_size;     /* its size */
line 3302 is a new one:   unsigned int block;               /* bit map traverser */
line 3303 is a new one:   unsigned int bit;                 /* bit map traverser */
line 3304 is a new one:   unsigned int map;                 /* current word of binmap */
line 3306 is a new one:   mchunkptr fwd;                    /* misc temp for linking */
line 3307 is a new one:   mchunkptr bck;                    /* misc temp for linking */
line 3312 is a new one:      Convert request size to internal form by adding SIZE_SZ bytes
line 3313 is a new one:      overhead plus possibly more to obtain necessary alignment and/or
line 3314 is a new one:      to obtain a size of at least MINSIZE, the smallest allocatable
line 3315 is a new one:      size. Also, checked_request2size traps (returning 0) request sizes
line 3316 is a new one:      that are so large that they wrap around zero when padded and
line 3317 is a new one:      aligned.
line 3318 is a new one:    */
line 3320 is a new one:   checked_request2size (bytes, nb);
line 3323 is a new one:      If the size qualifies as a fastbin, first check corresponding bin.
line 3324 is a new one:      This code is safe to execute even if av is not yet initialized, so we
line 3325 is a new one:      can try it without checking, which saves some time on this fast path.
line 3326 is a new one:    */
line 3328 is a new one:   if ((unsigned long) (nb) <= (unsigned long) (get_max_fast ()))
line 3330 is a new one:       idx = fastbin_index (nb);
line 3331 is a new one:       mfastbinptr *fb = &fastbin (av, idx);
line 3332 is a new one:       mchunkptr pp = *fb;
line 3333 is a new one:       do
line 3334 is a new one:         {
line 3335 is a new one:           victim = pp;
line 3336 is a new one:           if (victim == NULL)
line 3337 is a new one:             break;
line 3338 is a new one:         }
line 3339 is a new one:       while ((pp = catomic_compare_and_exchange_val_acq (fb, victim->fd, victim))
line 3340 is a new one:              != victim);
line 3341 is a new one:       if (victim != 0)
line 3342 is a new one:         {
line 3343 is a new one:           if (__builtin_expect (fastbin_index (chunksize (victim)) != idx, 0))
line 3344 is a new one:             {
line 3345 is a new one:               errstr = "malloc(): memory corruption (fast)";
line 3346 is a new one:             errout:
line 3347 is a new one:               malloc_printerr (check_action, errstr, chunk2mem (victim));
line 3348 is a new one:               return NULL;
line 3349 is a new one:             }
line 3350 is a new one:           check_remalloced_chunk (av, victim, nb);
line 3351 is a new one:           void *p = chunk2mem (victim);
line 3352 is a new one:           alloc_perturb (p, bytes);
line 3353 is a new one:           return p;
line 3354 is a new one:         }
line 3358 is a new one:      If a small request, check regular bin.  Since these "smallbins"
line 3359 is a new one:      hold one size each, no searching within bins is necessary.
line 3360 is a new one:      (For a large request, we need to wait until unsorted chunks are
line 3361 is a new one:      processed to find best fit. But for small ones, fits are exact
line 3362 is a new one:      anyway, so we can check now, which is faster.)
line 3363 is a new one:    */
line 3365 is a new one:   if (in_smallbin_range (nb))
line 3367 is a new one:       idx = smallbin_index (nb);
line 3368 is a new one:       bin = bin_at (av, idx);
line 3370 is a new one:       if ((victim = last (bin)) != bin)
line 3371 is a new one:         {
line 3372 is a new one:           if (victim == 0) /* initialization check */
line 3373 is a new one:             malloc_consolidate (av);
line 3374 is a new one:           else
line 3375 is a new one:             {
line 3376 is a new one:               bck = victim->bk;
line 3377 is a new one: 	if (__glibc_unlikely (bck->fd != victim))
line 3378 is a new one:                 {
line 3379 is a new one:                   errstr = "malloc(): smallbin double linked list corrupted";
line 3380 is a new one:                   goto errout;
line 3381 is a new one:                 }
line 3382 is a new one:               set_inuse_bit_at_offset (victim, nb);
line 3383 is a new one:               bin->bk = bck;
line 3384 is a new one:               bck->fd = bin;
line 3386 is a new one:               if (av != &main_arena)
line 3387 is a new one:                 victim->size |= NON_MAIN_ARENA;
line 3388 is a new one:               check_malloced_chunk (av, victim, nb);
line 3389 is a new one:               void *p = chunk2mem (victim);
line 3390 is a new one:               alloc_perturb (p, bytes);
line 3391 is a new one:               return p;
line 3392 is a new one:             }
line 3393 is a new one:         }
line 3405 is a new one:    */
line 3409 is a new one:       idx = largebin_index (nb);
line 3410 is a new one:       if (have_fastchunks (av))
line 3411 is a new one:         malloc_consolidate (av);
line 3415 is a new one:      Process recently freed or remaindered chunks, taking one only if
line 3416 is a new one:      it is exact fit, or, if this a small request, the chunk is remainder from
line 3417 is a new one:      the most recent non-exact fit.  Place other traversed chunks in
line 3418 is a new one:      bins.  Note that this step is the only place in any routine where
line 3419 is a new one:      chunks are placed in bins.
line 3421 is a new one:      The outer loop here is needed because we might not realize until
line 3422 is a new one:      near the end of malloc that we should have consolidated, so must
line 3423 is a new one:      do so and retry. This happens at most once, and only when we would
line 3424 is a new one:      otherwise need to expand memory to service a "small" request.
line 3425 is a new one:    */
line 3427 is a new one:   for (;; )
line 3429 is a new one:       int iters = 0;
line 3430 is a new one:       while ((victim = unsorted_chunks (av)->bk) != unsorted_chunks (av))
line 3431 is a new one:         {
line 3432 is a new one:           bck = victim->bk;
line 3433 is a new one:           if (__builtin_expect (victim->size <= 2 * SIZE_SZ, 0)
line 3434 is a new one:               || __builtin_expect (victim->size > av->system_mem, 0))
line 3435 is a new one:             malloc_printerr (check_action, "malloc(): memory corruption",
line 3436 is a new one:                              chunk2mem (victim));
line 3437 is a new one:           size = chunksize (victim);
line 3439 is a new one:           /*
line 3440 is a new one:              If a small request, try to use last remainder if it is the
line 3441 is a new one:              only chunk in unsorted bin.  This helps promote locality for
line 3442 is a new one:              runs of consecutive small requests. This is the only
line 3443 is a new one:              exception to best-fit, and applies only when there is
line 3444 is a new one:              no exact fit for a small chunk.
line 3445 is a new one:            */
line 3447 is a new one:           if (in_smallbin_range (nb) &&
line 3448 is a new one:               bck == unsorted_chunks (av) &&
line 3449 is a new one:               victim == av->last_remainder &&
line 3450 is a new one:               (unsigned long) (size) > (unsigned long) (nb + MINSIZE))
line 3451 is a new one:             {
line 3452 is a new one:               /* split and reattach remainder */
line 3453 is a new one:               remainder_size = size - nb;
line 3454 is a new one:               remainder = chunk_at_offset (victim, nb);
line 3455 is a new one:               unsorted_chunks (av)->bk = unsorted_chunks (av)->fd = remainder;
line 3456 is a new one:               av->last_remainder = remainder;
line 3457 is a new one:               remainder->bk = remainder->fd = unsorted_chunks (av);
line 3458 is a new one:               if (!in_smallbin_range (remainder_size))
line 3459 is a new one:                 {
line 3460 is a new one:                   remainder->fd_nextsize = NULL;
line 3461 is a new one:                   remainder->bk_nextsize = NULL;
line 3462 is a new one:                 }
line 3464 is a new one:               set_head (victim, nb | PREV_INUSE |
line 3465 is a new one:                         (av != &main_arena ? NON_MAIN_ARENA : 0));
line 3466 is a new one:               set_head (remainder, remainder_size | PREV_INUSE);
line 3467 is a new one:               set_foot (remainder, remainder_size);
line 3469 is a new one:               check_malloced_chunk (av, victim, nb);
line 3470 is a new one:               void *p = chunk2mem (victim);
line 3471 is a new one:               alloc_perturb (p, bytes);
line 3472 is a new one:               return p;
line 3473 is a new one:             }
line 3475 is a new one:           /* remove from unsorted list */
line 3476 is a new one:           unsorted_chunks (av)->bk = bck;
line 3477 is a new one:           bck->fd = unsorted_chunks (av);
line 3479 is a new one:           /* Take now instead of binning if exact fit */
line 3481 is a new one:           if (size == nb)
line 3482 is a new one:             {
line 3483 is a new one:               set_inuse_bit_at_offset (victim, size);
line 3484 is a new one:               if (av != &main_arena)
line 3485 is a new one:                 victim->size |= NON_MAIN_ARENA;
line 3486 is a new one:               check_malloced_chunk (av, victim, nb);
line 3487 is a new one:               void *p = chunk2mem (victim);
line 3488 is a new one:               alloc_perturb (p, bytes);
line 3489 is a new one:               return p;
line 3490 is a new one:             }
line 3492 is a new one:           /* place chunk in bin */
line 3494 is a new one:           if (in_smallbin_range (size))
line 3495 is a new one:             {
line 3496 is a new one:               victim_index = smallbin_index (size);
line 3497 is a new one:               bck = bin_at (av, victim_index);
line 3498 is a new one:               fwd = bck->fd;
line 3499 is a new one:             }
line 3500 is a new one:           else
line 3501 is a new one:             {
line 3502 is a new one:               victim_index = largebin_index (size);
line 3503 is a new one:               bck = bin_at (av, victim_index);
line 3504 is a new one:               fwd = bck->fd;
line 3506 is a new one:               /* maintain large bins in sorted order */
line 3507 is a new one:               if (fwd != bck)
line 3508 is a new one:                 {
line 3509 is a new one:                   /* Or with inuse bit to speed comparisons */
line 3510 is a new one:                   size |= PREV_INUSE;
line 3511 is a new one:                   /* if smaller than smallest, bypass loop below */
line 3512 is a new one:                   assert ((bck->bk->size & NON_MAIN_ARENA) == 0);
line 3513 is a new one:                   if ((unsigned long) (size) < (unsigned long) (bck->bk->size))
line 3514 is a new one:                     {
line 3515 is a new one:                       fwd = bck;
line 3516 is a new one:                       bck = bck->bk;
line 3518 is a new one:                       victim->fd_nextsize = fwd->fd;
line 3519 is a new one:                       victim->bk_nextsize = fwd->fd->bk_nextsize;
line 3520 is a new one:                       fwd->fd->bk_nextsize = victim->bk_nextsize->fd_nextsize = victim;
line 3521 is a new one:                     }
line 3522 is a new one:                   else
line 3523 is a new one:                     {
line 3524 is a new one:                       assert ((fwd->size & NON_MAIN_ARENA) == 0);
line 3525 is a new one:                       while ((unsigned long) size < fwd->size)
line 3526 is a new one:                         {
line 3527 is a new one:                           fwd = fwd->fd_nextsize;
line 3528 is a new one:                           assert ((fwd->size & NON_MAIN_ARENA) == 0);
line 3529 is a new one:                         }
line 3531 is a new one:                       if ((unsigned long) size == (unsigned long) fwd->size)
line 3532 is a new one:                         /* Always insert in the second position.  */
line 3533 is a new one:                         fwd = fwd->fd;
line 3534 is a new one:                       else
line 3535 is a new one:                         {
line 3536 is a new one:                           victim->fd_nextsize = fwd;
line 3537 is a new one:                           victim->bk_nextsize = fwd->bk_nextsize;
line 3538 is a new one:                           fwd->bk_nextsize = victim;
line 3539 is a new one:                           victim->bk_nextsize->fd_nextsize = victim;
line 3540 is a new one:                         }
line 3541 is a new one:                       bck = fwd->bk;
line 3542 is a new one:                     }
line 3543 is a new one:                 }
line 3544 is a new one:               else
line 3545 is a new one:                 victim->fd_nextsize = victim->bk_nextsize = victim;
line 3546 is a new one:             }
line 3548 is a new one:           mark_bin (av, victim_index);
line 3549 is a new one:           victim->bk = bck;
line 3550 is a new one:           victim->fd = fwd;
line 3551 is a new one:           fwd->bk = victim;
line 3552 is a new one:           bck->fd = victim;
line 3554 is a new one: #define MAX_ITERS       10000
line 3555 is a new one:           if (++iters >= MAX_ITERS)
line 3556 is a new one:             break;
line 3557 is a new one:         }
line 3560 is a new one:          If a large request, scan through the chunks of current bin in
line 3561 is a new one:          sorted order to find smallest that fits.  Use the skip list for this.
line 3562 is a new one:        */
line 3564 is a new one:       if (!in_smallbin_range (nb))
line 3565 is a new one:         {
line 3566 is a new one:           bin = bin_at (av, idx);
line 3568 is a new one:           /* skip scan if empty or largest chunk is too small */
line 3569 is a new one:           if ((victim = first (bin)) != bin &&
line 3570 is a new one:               (unsigned long) (victim->size) >= (unsigned long) (nb))
line 3571 is a new one:             {
line 3572 is a new one:               victim = victim->bk_nextsize;
line 3573 is a new one:               while (((unsigned long) (size = chunksize (victim)) <
line 3574 is a new one:                       (unsigned long) (nb)))
line 3575 is a new one:                 victim = victim->bk_nextsize;
line 3577 is a new one:               /* Avoid removing the first entry for a size so that the skip
line 3578 is a new one:                  list does not have to be rerouted.  */
line 3579 is a new one:               if (victim != last (bin) && victim->size == victim->fd->size)
line 3580 is a new one:                 victim = victim->fd;
line 3582 is a new one:               remainder_size = size - nb;
line 3583 is a new one:               unlink (victim, bck, fwd);
line 3585 is a new one:               /* Exhaust */
line 3586 is a new one:               if (remainder_size < MINSIZE)
line 3587 is a new one:                 {
line 3588 is a new one:                   set_inuse_bit_at_offset (victim, size);
line 3589 is a new one:                   if (av != &main_arena)
line 3590 is a new one:                     victim->size |= NON_MAIN_ARENA;
line 3591 is a new one:                 }
line 3592 is a new one:               /* Split */
line 3593 is a new one:               else
line 3594 is a new one:                 {
line 3595 is a new one:                   remainder = chunk_at_offset (victim, nb);
line 3596 is a new one:                   /* We cannot assume the unsorted list is empty and therefore
line 3597 is a new one:                      have to perform a complete insert here.  */
line 3598 is a new one:                   bck = unsorted_chunks (av);
line 3599 is a new one:                   fwd = bck->fd;
line 3600 is a new one: 	  if (__glibc_unlikely (fwd->bk != bck))
line 3601 is a new one:                     {
line 3602 is a new one:                       errstr = "malloc(): corrupted unsorted chunks";
line 3603 is a new one:                       goto errout;
line 3604 is a new one:                     }
line 3605 is a new one:                   remainder->bk = bck;
line 3606 is a new one:                   remainder->fd = fwd;
line 3607 is a new one:                   bck->fd = remainder;
line 3608 is a new one:                   fwd->bk = remainder;
line 3609 is a new one:                   if (!in_smallbin_range (remainder_size))
line 3610 is a new one:                     {
line 3611 is a new one:                       remainder->fd_nextsize = NULL;
line 3612 is a new one:                       remainder->bk_nextsize = NULL;
line 3613 is a new one:                     }
line 3614 is a new one:                   set_head (victim, nb | PREV_INUSE |
line 3615 is a new one:                             (av != &main_arena ? NON_MAIN_ARENA : 0));
line 3616 is a new one:                   set_head (remainder, remainder_size | PREV_INUSE);
line 3617 is a new one:                   set_foot (remainder, remainder_size);
line 3618 is a new one:                 }
line 3619 is a new one:               check_malloced_chunk (av, victim, nb);
line 3620 is a new one:               void *p = chunk2mem (victim);
line 3621 is a new one:               alloc_perturb (p, bytes);
line 3622 is a new one:               return p;
line 3623 is a new one:             }
line 3624 is a new one:         }
line 3627 is a new one:          Search for a chunk by scanning bins, starting with next largest
line 3628 is a new one:          bin. This search is strictly by best-fit; i.e., the smallest
line 3629 is a new one:          (with ties going to approximately the least recently used) chunk
line 3630 is a new one:          that fits is selected.
line 3632 is a new one:          The bitmap avoids needing to check that most blocks are nonempty.
line 3633 is a new one:          The particular case of skipping all bins during warm-up phases
line 3634 is a new one:          when no chunks have been returned yet is faster than it might look.
line 3635 is a new one:        */
line 3637 is a new one:       ++idx;
line 3638 is a new one:       bin = bin_at (av, idx);
line 3639 is a new one:       block = idx2block (idx);
line 3640 is a new one:       map = av->binmap[block];
line 3641 is a new one:       bit = idx2bit (idx);
line 3643 is a new one:       for (;; )
line 3644 is a new one:         {
line 3645 is a new one:           /* Skip rest of block if there are no more set bits in this block.  */
line 3646 is a new one:           if (bit > map || bit == 0)
line 3647 is a new one:             {
line 3648 is a new one:               do
line 3649 is a new one:                 {
line 3650 is a new one:                   if (++block >= BINMAPSIZE) /* out of bins */
line 3651 is a new one:                     goto use_top;
line 3652 is a new one:                 }
line 3653 is a new one:               while ((map = av->binmap[block]) == 0);
line 3655 is a new one:               bin = bin_at (av, (block << BINMAPSHIFT));
line 3656 is a new one:               bit = 1;
line 3657 is a new one:             }
line 3659 is a new one:           /* Advance to bin with set bit. There must be one. */
line 3660 is a new one:           while ((bit & map) == 0)
line 3661 is a new one:             {
line 3662 is a new one:               bin = next_bin (bin);
line 3663 is a new one:               bit <<= 1;
line 3664 is a new one:               assert (bit != 0);
line 3665 is a new one:             }
line 3667 is a new one:           /* Inspect the bin. It is likely to be non-empty */
line 3668 is a new one:           victim = last (bin);
line 3670 is a new one:           /*  If a false alarm (empty bin), clear the bit. */
line 3671 is a new one:           if (victim == bin)
line 3672 is a new one:             {
line 3673 is a new one:               av->binmap[block] = map &= ~bit; /* Write through */
line 3674 is a new one:               bin = next_bin (bin);
line 3675 is a new one:               bit <<= 1;
line 3676 is a new one:             }
line 3678 is a new one:           else
line 3679 is a new one:             {
line 3680 is a new one:               size = chunksize (victim);
line 3682 is a new one:               /*  We know the first chunk in this bin is big enough to use. */
line 3683 is a new one:               assert ((unsigned long) (size) >= (unsigned long) (nb));
line 3685 is a new one:               remainder_size = size - nb;
line 3687 is a new one:               /* unlink */
line 3688 is a new one:               unlink (victim, bck, fwd);
line 3690 is a new one:               /* Exhaust */
line 3691 is a new one:               if (remainder_size < MINSIZE)
line 3692 is a new one:                 {
line 3693 is a new one:                   set_inuse_bit_at_offset (victim, size);
line 3694 is a new one:                   if (av != &main_arena)
line 3695 is a new one:                     victim->size |= NON_MAIN_ARENA;
line 3696 is a new one:                 }
line 3698 is a new one:               /* Split */
line 3699 is a new one:               else
line 3700 is a new one:                 {
line 3701 is a new one:                   remainder = chunk_at_offset (victim, nb);
line 3703 is a new one:                   /* We cannot assume the unsorted list is empty and therefore
line 3704 is a new one:                      have to perform a complete insert here.  */
line 3705 is a new one:                   bck = unsorted_chunks (av);
line 3706 is a new one:                   fwd = bck->fd;
line 3707 is a new one: 	  if (__glibc_unlikely (fwd->bk != bck))
line 3708 is a new one:                     {
line 3709 is a new one:                       errstr = "malloc(): corrupted unsorted chunks 2";
line 3710 is a new one:                       goto errout;
line 3711 is a new one:                     }
line 3712 is a new one:                   remainder->bk = bck;
line 3713 is a new one:                   remainder->fd = fwd;
line 3714 is a new one:                   bck->fd = remainder;
line 3715 is a new one:                   fwd->bk = remainder;
line 3717 is a new one:                   /* advertise as last remainder */
line 3718 is a new one:                   if (in_smallbin_range (nb))
line 3719 is a new one:                     av->last_remainder = remainder;
line 3720 is a new one:                   if (!in_smallbin_range (remainder_size))
line 3721 is a new one:                     {
line 3722 is a new one:                       remainder->fd_nextsize = NULL;
line 3723 is a new one:                       remainder->bk_nextsize = NULL;
line 3724 is a new one:                     }
line 3725 is a new one:                   set_head (victim, nb | PREV_INUSE |
line 3726 is a new one:                             (av != &main_arena ? NON_MAIN_ARENA : 0));
line 3727 is a new one:                   set_head (remainder, remainder_size | PREV_INUSE);
line 3728 is a new one:                   set_foot (remainder, remainder_size);
line 3729 is a new one:                 }
line 3730 is a new one:               check_malloced_chunk (av, victim, nb);
line 3731 is a new one:               void *p = chunk2mem (victim);
line 3732 is a new one:               alloc_perturb (p, bytes);
line 3733 is a new one:               return p;
line 3734 is a new one:             }
line 3735 is a new one:         }
line 3737 is a new one:     use_top:
line 3739 is a new one:          If large enough, split off the chunk bordering the end of memory
line 3740 is a new one:          (held in av->top). Note that this is in accord with the best-fit
line 3741 is a new one:          search rule.  In effect, av->top is treated as larger (and thus
line 3742 is a new one:          less well fitting) than any other available chunk since it can
line 3743 is a new one:          be extended to be as large as necessary (up to system
line 3744 is a new one:          limitations).
line 3746 is a new one:          We require that av->top always exists (i.e., has size >=
line 3747 is a new one:          MINSIZE) after initialization, so if it would otherwise be
line 3748 is a new one:          exhausted by current request, it is replenished. (The main
line 3749 is a new one:          reason for ensuring it exists is that we may need MINSIZE space
line 3750 is a new one:          to put in fenceposts in sysmalloc.)
line 3751 is a new one:        */
line 3753 is a new one:       victim = av->top;
line 3754 is a new one:       size = chunksize (victim);
line 3756 is a new one:       if ((unsigned long) (size) >= (unsigned long) (nb + MINSIZE))
line 3757 is a new one:         {
line 3758 is a new one:           remainder_size = size - nb;
line 3759 is a new one:           remainder = chunk_at_offset (victim, nb);
line 3760 is a new one:           av->top = remainder;
line 3761 is a new one:           set_head (victim, nb | PREV_INUSE |
line 3762 is a new one:                     (av != &main_arena ? NON_MAIN_ARENA : 0));
line 3763 is a new one:           set_head (remainder, remainder_size | PREV_INUSE);
line 3765 is a new one:           check_malloced_chunk (av, victim, nb);
line 3766 is a new one:           void *p = chunk2mem (victim);
line 3767 is a new one:           alloc_perturb (p, bytes);
line 3768 is a new one:           return p;
line 3769 is a new one:         }
line 3771 is a new one:       /* When we are using atomic ops to free fast chunks we can get
line 3772 is a new one:          here for all block sizes.  */
line 3773 is a new one:       else if (have_fastchunks (av))
line 3774 is a new one:         {
line 3775 is a new one:           malloc_consolidate (av);
line 3776 is a new one:           /* restore original bin index */
line 3777 is a new one:           if (in_smallbin_range (nb))
line 3778 is a new one:             idx = smallbin_index (nb);
line 3779 is a new one:           else
line 3780 is a new one:             idx = largebin_index (nb);
line 3781 is a new one:         }
line 3784 is a new one:          Otherwise, relay to handle system-dependent cases
line 3785 is a new one:        */
line 3787 is a new one:         {
line 3788 is a new one:           void *p = sysmalloc (nb, av);
line 3789 is a new one:           if (p != NULL)
line 3790 is a new one:             alloc_perturb (p, bytes);
line 3791 is a new one:           return p;
line 3792 is a new one:         }
line 3797 is a new one:    ------------------------------ free ------------------------------
line 3801 is a new one: _int_free (mstate av, mchunkptr p, int have_lock)
line 3804 is a new one:   mfastbinptr *fb;             /* associated fastbin */
line 3805 is a new one:   mchunkptr nextchunk;         /* next contiguous chunk */
line 3807 is a new one:   int nextinuse;               /* true if nextchunk is used */
line 3809 is a new one:   mchunkptr bck;               /* misc temp for linking */
line 3810 is a new one:   mchunkptr fwd;               /* misc temp for linking */
line 3815 is a new one:   size = chunksize (p);
line 3826 is a new one:       if (!have_lock && locked)
line 3827 is a new one:         (void) mutex_unlock (&av->mutex);
line 3828 is a new one:       malloc_printerr (check_action, errstr, chunk2mem (p));
line 3833 is a new one:   if (__glibc_unlikely (size < MINSIZE || !aligned_OK (size)))
line 3882 is a new one:     free_perturb (chunk2mem(p), size - 2 * SIZE_SZ);
line 3888 is a new one:     /* Atomically link P to its fastbin: P->FD = *FB; *FB = P;  */
line 3889 is a new one:     mchunkptr old = *fb, old2;
line 3893 is a new one: 	/* Check that the top of the bin is not the record we are going to add
line 3894 is a new one: 	   (i.e., double free).  */
line 3900 is a new one: 	/* Check that size of fastbin chunk at the top is the same as
line 3901 is a new one: 	   size of the chunk that we are adding.  We can dereference OLD
line 3902 is a new one: 	   only if we have the lock, otherwise it might have already been
line 3903 is a new one: 	   deallocated.  See use of OLD_IDX below for the actual check.  */
line 3904 is a new one: 	if (have_lock && old != NULL)
line 3906 is a new one: 	p->fd = old2 = old;
line 3908 is a new one:     while ((old = catomic_compare_and_exchange_val_rel (fb, p, old2)) != old2);
line 3910 is a new one:     if (have_lock && old != NULL && __builtin_expect (old_idx != idx, 0))
line 3931 is a new one:     if (__glibc_unlikely (p == av->top))
line 3945 is a new one:     if (__glibc_unlikely (!prev_inuse(nextchunk)))
line 3959 is a new one:     free_perturb (chunk2mem(p), size - 2 * SIZE_SZ);
line 3988 is a new one:       if (__glibc_unlikely (fwd->bk != bck))
line 4213 is a new one:       malloc_printerr (check_action, errstr, chunk2mem (oldp));
line 4217 is a new one:   check_inuse_chunk (av, oldp);
line 4220 is a new one:   assert (!chunk_is_mmapped (oldp));
line 4222 is a new one:   next = chunk_at_offset (oldp, oldsize);
line 4223 is a new one:   INTERNAL_SIZE_T nextsize = chunksize (next);
line 4231 is a new one:   if ((unsigned long) (oldsize) >= (unsigned long) (nb))
line 4233 is a new one:       /* already big enough; split below */
line 4235 is a new one:       newsize = oldsize;
line 4240 is a new one:       /* Try to expand forward into top */
line 4241 is a new one:       if (next == av->top &&
line 4242 is a new one:           (unsigned long) (newsize = oldsize + nextsize) >=
line 4243 is a new one:           (unsigned long) (nb + MINSIZE))
line 4244 is a new one:         {
line 4245 is a new one:           set_head_size (oldp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4246 is a new one:           av->top = chunk_at_offset (oldp, nb);
line 4247 is a new one:           set_head (av->top, (newsize - nb) | PREV_INUSE);
line 4248 is a new one:           check_inuse_chunk (av, oldp);
line 4249 is a new one:           return chunk2mem (oldp);
line 4250 is a new one:         }
line 4252 is a new one:       /* Try to expand forward into next chunk;  split off remainder below */
line 4253 is a new one:       else if (next != av->top &&
line 4254 is a new one:                !inuse (next) &&
line 4255 is a new one:                (unsigned long) (newsize = oldsize + nextsize) >=
line 4256 is a new one:                (unsigned long) (nb))
line 4257 is a new one:         {
line 4258 is a new one:           newp = oldp;
line 4259 is a new one:           unlink (next, bck, fwd);
line 4260 is a new one:         }
line 4262 is a new one:       /* allocate, copy, free */
line 4264 is a new one:         {
line 4265 is a new one:           newmem = _int_malloc (av, nb - MALLOC_ALIGN_MASK);
line 4266 is a new one:           if (newmem == 0)
line 4267 is a new one:             return 0; /* propagate failure */
line 4269 is a new one:           newp = mem2chunk (newmem);
line 4270 is a new one:           newsize = chunksize (newp);
line 4272 is a new one:           /*
line 4273 is a new one:              Avoid copy if newp is next chunk after oldp.
line 4274 is a new one:            */
line 4275 is a new one:           if (newp == next)
line 4276 is a new one:             {
line 4277 is a new one:               newsize += oldsize;
line 4278 is a new one:               newp = oldp;
line 4279 is a new one:             }
line 4280 is a new one:           else
line 4281 is a new one:             {
line 4282 is a new one:               /*
line 4283 is a new one:                  Unroll copy of <= 36 bytes (72 if 8byte sizes)
line 4284 is a new one:                  We know that contents have an odd number of
line 4285 is a new one:                  INTERNAL_SIZE_T-sized words; minimally 3.
line 4286 is a new one:                */
line 4288 is a new one:               copysize = oldsize - SIZE_SZ;
line 4289 is a new one:               s = (INTERNAL_SIZE_T *) (chunk2mem (oldp));
line 4290 is a new one:               d = (INTERNAL_SIZE_T *) (newmem);
line 4291 is a new one:               ncopies = copysize / sizeof (INTERNAL_SIZE_T);
line 4292 is a new one:               assert (ncopies >= 3);
line 4294 is a new one:               if (ncopies > 9)
line 4295 is a new one:                 memcpy (d, s, copysize);
line 4297 is a new one:               else
line 4298 is a new one:                 {
line 4299 is a new one:                   *(d + 0) = *(s + 0);
line 4300 is a new one:                   *(d + 1) = *(s + 1);
line 4301 is a new one:                   *(d + 2) = *(s + 2);
line 4302 is a new one:                   if (ncopies > 4)
line 4303 is a new one:                     {
line 4304 is a new one:                       *(d + 3) = *(s + 3);
line 4305 is a new one:                       *(d + 4) = *(s + 4);
line 4306 is a new one:                       if (ncopies > 6)
line 4307 is a new one:                         {
line 4308 is a new one:                           *(d + 5) = *(s + 5);
line 4309 is a new one:                           *(d + 6) = *(s + 6);
line 4310 is a new one:                           if (ncopies > 8)
line 4311 is a new one:                             {
line 4312 is a new one:                               *(d + 7) = *(s + 7);
line 4313 is a new one:                               *(d + 8) = *(s + 8);
line 4314 is a new one:                             }
line 4315 is a new one:                         }
line 4316 is a new one:                     }
line 4317 is a new one:                 }
line 4319 is a new one:               _int_free (av, oldp, 1);
line 4320 is a new one:               check_inuse_chunk (av, newp);
line 4321 is a new one:               return chunk2mem (newp);
line 4322 is a new one:             }
line 4323 is a new one:         }
line 4328 is a new one:   assert ((unsigned long) (newsize) >= (unsigned long) (nb));
line 4332 is a new one:   if (remainder_size < MINSIZE)   /* not enough extra to split off */
line 4334 is a new one:       set_head_size (newp, newsize | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4335 is a new one:       set_inuse_bit_at_offset (newp, newsize);
line 4337 is a new one:   else   /* split remainder */
line 4339 is a new one:       remainder = chunk_at_offset (newp, nb);
line 4340 is a new one:       set_head_size (newp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4341 is a new one:       set_head (remainder, remainder_size | PREV_INUSE |
line 4342 is a new one:                 (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4343 is a new one:       /* Mark remainder as inuse so free() won't complain */
line 4344 is a new one:       set_inuse_bit_at_offset (remainder, remainder_size);
line 4345 is a new one:       _int_free (av, remainder, 1);
line 4348 is a new one:   check_inuse_chunk (av, newp);
line 4349 is a new one:   return chunk2mem (newp);
line 4353 is a new one:    ------------------------------ memalign ------------------------------
line 4356 is a new one: static void *
line 4357 is a new one: _int_memalign (mstate av, size_t alignment, size_t bytes)
line 4360 is a new one:   char *m;                        /* memory returned by malloc call */
line 4361 is a new one:   mchunkptr p;                    /* corresponding chunk */
line 4362 is a new one:   char *brk;                      /* alignment point within p */
line 4363 is a new one:   mchunkptr newp;                 /* chunk to return */
line 4366 is a new one:   mchunkptr remainder;            /* spare room at end to split off */
line 4367 is a new one:   unsigned long remainder_size;   /* its size */
line 4372 is a new one:   checked_request2size (bytes, nb);
line 4375 is a new one:      Strategy: find a spot within that chunk that meets the alignment
line 4376 is a new one:      request, and then possibly free the leading and trailing space.
line 4377 is a new one:    */
line 4382 is a new one:   m = (char *) (_int_malloc (av, nb + alignment + MINSIZE));
line 4384 is a new one:   if (m == 0)
line 4385 is a new one:     return 0;           /* propagate failure */
line 4387 is a new one:   p = mem2chunk (m);
line 4389 is a new one:   if ((((unsigned long) (m)) % alignment) != 0)   /* misaligned */
line 4391 is a new one:     { /*
line 4392 is a new one:                 Find an aligned spot inside chunk.  Since we need to give back
line 4393 is a new one:                 leading space in a chunk of at least MINSIZE, if the first
line 4394 is a new one:                 calculation places us at a spot with less than MINSIZE leader,
line 4395 is a new one:                 we can move to the next aligned spot -- we've allocated enough
line 4396 is a new one:                 total room so that this is always possible.
line 4397 is a new one:                  */
line 4398 is a new one:       brk = (char *) mem2chunk (((unsigned long) (m + alignment - 1)) &
line 4399 is a new one:                                 - ((signed long) alignment));
line 4400 is a new one:       if ((unsigned long) (brk - (char *) (p)) < MINSIZE)
line 4401 is a new one:         brk += alignment;
line 4403 is a new one:       newp = (mchunkptr) brk;
line 4404 is a new one:       leadsize = brk - (char *) (p);
line 4405 is a new one:       newsize = chunksize (p) - leadsize;
line 4407 is a new one:       /* For mmapped chunks, just adjust offset */
line 4408 is a new one:       if (chunk_is_mmapped (p))
line 4409 is a new one:         {
line 4410 is a new one:           newp->prev_size = p->prev_size + leadsize;
line 4411 is a new one:           set_head (newp, newsize | IS_MMAPPED);
line 4412 is a new one:           return chunk2mem (newp);
line 4413 is a new one:         }
line 4415 is a new one:       /* Otherwise, give back leader, use the rest */
line 4416 is a new one:       set_head (newp, newsize | PREV_INUSE |
line 4417 is a new one:                 (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4418 is a new one:       set_inuse_bit_at_offset (newp, newsize);
line 4419 is a new one:       set_head_size (p, leadsize | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4420 is a new one:       _int_free (av, p, 1);
line 4421 is a new one:       p = newp;
line 4423 is a new one:       assert (newsize >= nb &&
line 4424 is a new one:               (((unsigned long) (chunk2mem (p))) % alignment) == 0);
line 4428 is a new one:   if (!chunk_is_mmapped (p))
line 4430 is a new one:       size = chunksize (p);
line 4431 is a new one:       if ((unsigned long) (size) > (unsigned long) (nb + MINSIZE))
line 4432 is a new one:         {
line 4433 is a new one:           remainder_size = size - nb;
line 4434 is a new one:           remainder = chunk_at_offset (p, nb);
line 4435 is a new one:           set_head (remainder, remainder_size | PREV_INUSE |
line 4436 is a new one:                     (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4437 is a new one:           set_head_size (p, nb);
line 4438 is a new one:           _int_free (av, remainder, 1);
line 4439 is a new one:         }
line 4442 is a new one:   check_inuse_chunk (av, p);
line 4443 is a new one:   return chunk2mem (p);
line 4448 is a new one:    ------------------------------ malloc_trim ------------------------------
line 4451 is a new one: static int
line 4452 is a new one: mtrim (mstate av, size_t pad)
line 4457 is a new one:   const size_t ps = GLRO (dl_pagesize);
line 4465 is a new one:         mbinptr bin = bin_at (av, i);
line 4467 is a new one:         for (mchunkptr p = last (bin); p != bin; p = p->bk)
line 4468 is a new one:           {
line 4469 is a new one:             INTERNAL_SIZE_T size = chunksize (p);
line 4471 is a new one:             if (size > psm1 + sizeof (struct malloc_chunk))
line 4472 is a new one:               {
line 4473 is a new one:                 /* See whether the chunk contains at least one unused page.  */
line 4474 is a new one:                 char *paligned_mem = (char *) (((uintptr_t) p
line 4475 is a new one:                                                 + sizeof (struct malloc_chunk)
line 4476 is a new one:                                                 + psm1) & ~psm1);
line 4478 is a new one:                 assert ((char *) chunk2mem (p) + 4 * SIZE_SZ <= paligned_mem);
line 4479 is a new one:                 assert ((char *) p + size > paligned_mem);
line 4481 is a new one:                 /* This is the size we could potentially free.  */
line 4482 is a new one:                 size -= paligned_mem - (char *) p;
line 4484 is a new one:                 if (size > psm1)
line 4485 is a new one:                   {
line 4486 is a new one: #if MALLOC_DEBUG
line 4487 is a new one:                     /* When debugging we simulate destroying the memory
line 4488 is a new one:                        content.  */
line 4489 is a new one:                     memset (paligned_mem, 0x89, size & ~psm1);
line 4491 is a new one:                     __madvise (paligned_mem, size & ~psm1, MADV_DONTNEED);
line 4493 is a new one:                     result = 1;
line 4494 is a new one:                   }
line 4495 is a new one:               }
line 4496 is a new one:           }
line 4509 is a new one: __malloc_trim (size_t s)
line 4513 is a new one:   if (__malloc_initialized < 0)
line 4532 is a new one:    ------------------------- malloc_usable_size -------------------------
line 4536 is a new one: musable (void *mem)
line 4539 is a new one:   if (mem != 0)
line 4541 is a new one:       p = mem2chunk (mem);
line 4543 is a new one:       if (__builtin_expect (using_malloc_checking == 1, 0))
line 4544 is a new one:         return malloc_check_get_size (p);
line 4546 is a new one:       if (chunk_is_mmapped (p))
line 4547 is a new one:         return chunksize (p) - 2 * SIZE_SZ;
line 4548 is a new one:       else if (inuse (p))
line 4549 is a new one:         return chunksize (p) - SIZE_SZ;
line 4556 is a new one: __malloc_usable_size (void *m)
line 4560 is a new one:   result = musable (m);
line 4565 is a new one:    ------------------------------ mallinfo ------------------------------
line 4566 is a new one:    Accumulate malloc statistics for arena AV into M.
line 4570 is a new one: int_mallinfo (mstate av, struct mallinfo *m)
line 4581 is a new one:   if (av->top == 0)
line 4582 is a new one:     malloc_consolidate (av);
line 4584 is a new one:   check_malloc_state (av);
line 4587 is a new one:   avail = chunksize (av->top);
line 4594 is a new one:   for (i = 0; i < NFASTBINS; ++i)
line 4596 is a new one:       for (p = fastbin (av, i); p != 0; p = p->fd)
line 4597 is a new one:         {
line 4598 is a new one:           ++nfastblocks;
line 4599 is a new one:           fastavail += chunksize (p);
line 4600 is a new one:         }
line 4606 is a new one:   for (i = 1; i < NBINS; ++i)
line 4608 is a new one:       b = bin_at (av, i);
line 4609 is a new one:       for (p = last (b); p != b; p = p->bk)
line 4610 is a new one:         {
line 4611 is a new one:           ++nblocks;
line 4612 is a new one:           avail += chunksize (p);
line 4613 is a new one:         }
line 4627 is a new one:       m->keepcost = chunksize (av->top);
line 4632 is a new one: struct mallinfo
line 4633 is a new one: __libc_mallinfo ()
line 4638 is a new one:   if (__malloc_initialized < 0)
line 4641 is a new one:   memset (&m, 0, sizeof (m));
line 4646 is a new one:       int_mallinfo (ar_ptr, &m);
line 4657 is a new one:    ------------------------------ malloc_stats ------------------------------
line 4667 is a new one:   if (__malloc_initialized < 0)
line 4672 is a new one:   for (i = 0, ar_ptr = &main_arena;; i++)
line 4674 is a new one:       struct mallinfo mi;
line 4676 is a new one:       memset (&mi, 0, sizeof (mi));
line 4678 is a new one:       int_mallinfo (ar_ptr, &mi);
line 4679 is a new one:       fprintf (stderr, "Arena %d:\n", i);
line 4680 is a new one:       fprintf (stderr, "system bytes     = %10u\n", (unsigned int) mi.arena);
line 4681 is a new one:       fprintf (stderr, "in use bytes     = %10u\n", (unsigned int) mi.uordblks);
line 4683 is a new one:       if (i > 0)
line 4684 is a new one:         dump_heap (heap_for_ptr (top (ar_ptr)));
line 4686 is a new one:       system_b += mi.arena;
line 4687 is a new one:       in_use_b += mi.uordblks;
line 4690 is a new one:       if (ar_ptr == &main_arena)
line 4691 is a new one:         break;
line 4693 is a new one:   fprintf (stderr, "Total (incl. mmap):\n");
line 4694 is a new one:   fprintf (stderr, "system bytes     = %10u\n", system_b);
line 4695 is a new one:   fprintf (stderr, "in use bytes     = %10u\n", in_use_b);
line 4696 is a new one:   fprintf (stderr, "max mmap regions = %10u\n", (unsigned int) mp_.max_n_mmaps);
line 4697 is a new one:   fprintf (stderr, "max mmap bytes   = %10lu\n",
line 4698 is a new one:            (unsigned long) mp_.max_mmapped_mem);
line 4705 is a new one:    ------------------------------ mallopt ------------------------------
line 4709 is a new one: __libc_mallopt (int param_number, int value)
line 4714 is a new one:   if (__malloc_initialized < 0)
line 4716 is a new one:   (void) mutex_lock (&av->mutex);
line 4720 is a new one:   LIBC_PROBE (memory_mallopt, 2, param_number, value);
line 4722 is a new one:   switch (param_number)
line 4724 is a new one:     case M_MXFAST:
line 4725 is a new one:       if (value >= 0 && value <= MAX_FAST_SIZE)
line 4726 is a new one:         {
line 4727 is a new one:           LIBC_PROBE (memory_mallopt_mxfast, 2, value, get_max_fast ());
line 4728 is a new one:           set_max_fast (value);
line 4729 is a new one:         }
line 4731 is a new one:         res = 0;
line 4732 is a new one:       break;
line 4734 is a new one:     case M_TRIM_THRESHOLD:
line 4735 is a new one:       LIBC_PROBE (memory_mallopt_trim_threshold, 3, value,
line 4736 is a new one:                   mp_.trim_threshold, mp_.no_dyn_threshold);
line 4737 is a new one:       mp_.trim_threshold = value;
line 4738 is a new one:       mp_.no_dyn_threshold = 1;
line 4739 is a new one:       break;
line 4741 is a new one:     case M_TOP_PAD:
line 4742 is a new one:       LIBC_PROBE (memory_mallopt_top_pad, 3, value,
line 4743 is a new one:                   mp_.top_pad, mp_.no_dyn_threshold);
line 4744 is a new one:       mp_.top_pad = value;
line 4745 is a new one:       mp_.no_dyn_threshold = 1;
line 4746 is a new one:       break;
line 4748 is a new one:     case M_MMAP_THRESHOLD:
line 4749 is a new one:       /* Forbid setting the threshold too high. */
line 4750 is a new one:       if ((unsigned long) value > HEAP_MAX_SIZE / 2)
line 4751 is a new one:         res = 0;
line 4753 is a new one:         {
line 4754 is a new one:           LIBC_PROBE (memory_mallopt_mmap_threshold, 3, value,
line 4755 is a new one:                       mp_.mmap_threshold, mp_.no_dyn_threshold);
line 4756 is a new one:           mp_.mmap_threshold = value;
line 4757 is a new one:           mp_.no_dyn_threshold = 1;
line 4758 is a new one:         }
line 4759 is a new one:       break;
line 4761 is a new one:     case M_MMAP_MAX:
line 4762 is a new one:       LIBC_PROBE (memory_mallopt_mmap_max, 3, value,
line 4763 is a new one:                   mp_.n_mmaps_max, mp_.no_dyn_threshold);
line 4764 is a new one:       mp_.n_mmaps_max = value;
line 4765 is a new one:       mp_.no_dyn_threshold = 1;
line 4766 is a new one:       break;
line 4768 is a new one:     case M_CHECK_ACTION:
line 4769 is a new one:       LIBC_PROBE (memory_mallopt_check_action, 2, value, check_action);
line 4770 is a new one:       check_action = value;
line 4771 is a new one:       break;
line 4773 is a new one:     case M_PERTURB:
line 4774 is a new one:       LIBC_PROBE (memory_mallopt_perturb, 2, value, perturb_byte);
line 4775 is a new one:       perturb_byte = value;
line 4776 is a new one:       break;
line 4778 is a new one:     case M_ARENA_TEST:
line 4779 is a new one:       if (value > 0)
line 4780 is a new one:         {
line 4781 is a new one:           LIBC_PROBE (memory_mallopt_arena_test, 2, value, mp_.arena_test);
line 4782 is a new one:           mp_.arena_test = value;
line 4783 is a new one:         }
line 4784 is a new one:       break;
line 4786 is a new one:     case M_ARENA_MAX:
line 4787 is a new one:       if (value > 0)
line 4788 is a new one:         {
line 4789 is a new one:           LIBC_PROBE (memory_mallopt_arena_max, 2, value, mp_.arena_max);
line 4790 is a new one:           mp_.arena_max = value;
line 4791 is a new one:         }
line 4792 is a new one:       break;
line 4794 is a new one:   (void) mutex_unlock (&av->mutex);
line 4801 is a new one:    -------------------- Alternative MORECORE functions --------------------
line 4806 is a new one:    General Requirements for MORECORE.
line 4808 is a new one:    The MORECORE function must have the following properties:
line 4810 is a new one:    If MORECORE_CONTIGUOUS is false:
line 4812 is a new one:  * MORECORE must allocate in multiples of pagesize. It will
line 4815 is a new one:  * MORECORE(0) must return an address that is at least
line 4818 is a new one:    else (i.e. If MORECORE_CONTIGUOUS is true):
line 4820 is a new one:  * Consecutive calls to MORECORE with positive arguments
line 4824 is a new one:  * MORECORE need not allocate in multiples of pagesize.
line 4827 is a new one:  * MORECORE need not page-align.
line 4829 is a new one:    In either case:
line 4831 is a new one:  * MORECORE may allocate more memory than requested. (Or even less,
line 4834 is a new one:  * MORECORE must not allocate memory when given argument zero, but
line 4840 is a new one:  * Even though consecutive calls to MORECORE need not return contiguous
line 4844 is a new one:  * MORECORE need not handle negative arguments -- it may instead
line 4851 is a new one:    There is some variation across systems about the type of the
line 4852 is a new one:    argument to sbrk/MORECORE. If size_t is unsigned, then it cannot
line 4853 is a new one:    actually be size_t, because sbrk supports negative args, so it is
line 4854 is a new one:    normally the signed type of the same width as size_t (sometimes
line 4855 is a new one:    declared as "intptr_t", and sometimes "ptrdiff_t").  It doesn't much
line 4856 is a new one:    matter though. Internally, we use "long" as arguments, which should
line 4857 is a new one:    work across all reasonable possibilities.
line 4859 is a new one:    Additionally, if MORECORE ever returns failure for a positive
line 4860 is a new one:    request, then mmap is used as a noncontiguous system allocator. This
line 4861 is a new one:    is a useful backup strategy for systems with holes in address spaces
line 4862 is a new one:    -- in this case sbrk cannot contiguously expand the heap, but mmap
line 4863 is a new one:    may be able to map noncontiguous space.
line 4865 is a new one:    If you'd like mmap to ALWAYS be used, you can define MORECORE to be
line 4866 is a new one:    a function that always returns MORECORE_FAILURE.
line 4868 is a new one:    If you are using this malloc with something other than sbrk (or its
line 4869 is a new one:    emulation) to supply memory regions, you probably want to set
line 4870 is a new one:    MORECORE_CONTIGUOUS as false.  As an example, here is a custom
line 4871 is a new one:    allocator kindly contributed for pre-OSX macOS.  It uses virtually
line 4872 is a new one:    but not necessarily physically contiguous non-paged memory (locked
line 4873 is a new one:    in, present and won't get swapped out).  You can use it by
line 4874 is a new one:    uncommenting this section, adding some #includes, and setting up the
line 4875 is a new one:    appropriate defines above:
line 4877 is a new one:  *#define MORECORE osMoreCore
line 4878 is a new one:  *#define MORECORE_CONTIGUOUS 0
line 4880 is a new one:    There is also a shutdown routine that should somehow be called for
line 4881 is a new one:    cleanup upon program exit.
line 4883 is a new one:  *#define MAX_POOL_ENTRIES 100
line 4884 is a new one:  *#define MINIMUM_MORECORE_SIZE  (64 * 1024)
line 4885 is a new one:    static int next_os_pool;
line 4886 is a new one:    void *our_os_pools[MAX_POOL_ENTRIES];
line 4888 is a new one:    void *osMoreCore(int size)
line 4889 is a new one:    {
line 4896 is a new one:          size = MINIMUM_MORECORE_SIZE;
line 4898 is a new one:          ptr = PoolAllocateResident(size + RM_PAGE_SIZE, 0);
line 4901 is a new one:         return (void *) MORECORE_FAILURE;
line 4919 is a new one:    }
line 4921 is a new one:    // cleanup any allocated memory pools
line 4922 is a new one:    // called as last thing before shutting down driver
line 4924 is a new one:    void osCleanupMem(void)
line 4925 is a new one:    {
line 4931 is a new one:          PoolDeallocate(*ptr);
line 4932 is a new one:  * ptr = 0;
line 4934 is a new one:    }
line 4944 is a new one: malloc_printerr (int action, const char *str, void *ptr)
line 4955 is a new one:         *--cp = '0';
line 4958 is a new one:                       __libc_argv[0] ? : "<unknown>", str, cp);
line 4978 is a new one:   void *address = RETURN_ADDRESS (0);
line 4979 is a new one:   mem = _mid_memalign (alignment, size, address);
line 4981 is a new one:   if (mem != NULL)
line 4983 is a new one:       *memptr = mem;
line 5011 is a new one:   if (__malloc_initialized < 0)
line 5020 is a new one:       fprintf (fp, "<heap nr=\"%d\">\n<sizes>\n", n++);
line 5022 is a new one:       size_t nblocks = 0;
line 5023 is a new one:       size_t nfastblocks = 0;
line 5024 is a new one:       size_t avail = 0;
line 5025 is a new one:       size_t fastavail = 0;
line 5026 is a new one:       struct
line 5028 is a new one: 	size_t from;
line 5029 is a new one: 	size_t to;
line 5030 is a new one: 	size_t total;
line 5031 is a new one: 	size_t count;
line 5032 is a new one:       } sizes[NFASTBINS + NBINS - 1];
line 5035 is a new one:       mutex_lock (&ar_ptr->mutex);
line 5037 is a new one:       for (size_t i = 0; i < NFASTBINS; ++i)
line 5039 is a new one: 	  mchunkptr p = fastbin (ar_ptr, i);
line 5040 is a new one: 	  if (p != NULL)
line 5042 is a new one: 	      size_t nthissize = 0;
line 5043 is a new one: 	      size_t thissize = chunksize (p);
line 5045 is a new one: 	      while (p != NULL)
line 5046 is a new one: 		{
line 5047 is a new one: 		  ++nthissize;
line 5048 is a new one: 		  p = p->fd;
line 5049 is a new one: 		}
line 5051 is a new one: 	      fastavail += nthissize * thissize;
line 5052 is a new one: 	      nfastblocks += nthissize;
line 5053 is a new one: 	      sizes[i].from = thissize - (MALLOC_ALIGNMENT - 1);
line 5054 is a new one: 	      sizes[i].to = thissize;
line 5055 is a new one: 	      sizes[i].count = nthissize;
line 5057 is a new one: 	  else
line 5058 is a new one: 	    sizes[i].from = sizes[i].to = sizes[i].count = 0;
line 5060 is a new one: 	  sizes[i].total = sizes[i].count * sizes[i].to;
line 5064 is a new one:       mbinptr bin;
line 5065 is a new one:       struct malloc_chunk *r;
line 5067 is a new one:       for (size_t i = 1; i < NBINS; ++i)
line 5069 is a new one: 	  bin = bin_at (ar_ptr, i);
line 5070 is a new one: 	  r = bin->fd;
line 5071 is a new one: 	  sizes[NFASTBINS - 1 + i].from = ~((size_t) 0);
line 5072 is a new one: 	  sizes[NFASTBINS - 1 + i].to = sizes[NFASTBINS - 1 + i].total
line 5073 is a new one: 					  = sizes[NFASTBINS - 1 + i].count = 0;
line 5075 is a new one: 	  if (r != NULL)
line 5076 is a new one: 	    while (r != bin)
line 5078 is a new one: 		++sizes[NFASTBINS - 1 + i].count;
line 5079 is a new one: 		sizes[NFASTBINS - 1 + i].total += r->size;
line 5080 is a new one: 		sizes[NFASTBINS - 1 + i].from
line 5081 is a new one: 		  = MIN (sizes[NFASTBINS - 1 + i].from, r->size);
line 5082 is a new one: 		sizes[NFASTBINS - 1 + i].to = MAX (sizes[NFASTBINS - 1 + i].to,
line 5083 is a new one: 						   r->size);
line 5085 is a new one: 		r = r->fd;
line 5088 is a new one: 	  if (sizes[NFASTBINS - 1 + i].count == 0)
line 5089 is a new one: 	    sizes[NFASTBINS - 1 + i].from = 0;
line 5090 is a new one: 	  nblocks += sizes[NFASTBINS - 1 + i].count;
line 5091 is a new one: 	  avail += sizes[NFASTBINS - 1 + i].total;
line 5094 is a new one:       mutex_unlock (&ar_ptr->mutex);
line 5096 is a new one:       total_nfastblocks += nfastblocks;
line 5097 is a new one:       total_fastavail += fastavail;
line 5099 is a new one:       total_nblocks += nblocks;
line 5100 is a new one:       total_avail += avail;
line 5102 is a new one:       for (size_t i = 0; i < nsizes; ++i)
line 5103 is a new one: 	if (sizes[i].count != 0 && i != NFASTBINS)
line 5104 is a new one: 	  fprintf (fp, "							      \
line 5105 is a new one:   <size from=\"%zu\" to=\"%zu\" total=\"%zu\" count=\"%zu\"/>\n",
line 5106 is a new one: 		   sizes[i].from, sizes[i].to, sizes[i].total, sizes[i].count);
line 5108 is a new one:       if (sizes[NFASTBINS].count != 0)
line 5110 is a new one:   <unsorted from=\"%zu\" to=\"%zu\" total=\"%zu\" count=\"%zu\"/>\n",
line 5111 is a new one: 		 sizes[NFASTBINS].from, sizes[NFASTBINS].to,
line 5112 is a new one: 		 sizes[NFASTBINS].total, sizes[NFASTBINS].count);
line 5114 is a new one:       total_system += ar_ptr->system_mem;
line 5115 is a new one:       total_max_system += ar_ptr->max_system_mem;
line 5117 is a new one:       fprintf (fp,
line 5118 is a new one: 	       "</sizes>\n<total type=\"fast\" count=\"%zu\" size=\"%zu\"/>\n"
line 5119 is a new one: 	       "<total type=\"rest\" count=\"%zu\" size=\"%zu\"/>\n"
line 5120 is a new one: 	       "<system type=\"current\" size=\"%zu\"/>\n"
line 5121 is a new one: 	       "<system type=\"max\" size=\"%zu\"/>\n",
line 5122 is a new one: 	       nfastblocks, fastavail, nblocks, avail,
line 5123 is a new one: 	       ar_ptr->system_mem, ar_ptr->max_system_mem);
line 5125 is a new one:       if (ar_ptr != &main_arena)
line 5127 is a new one: 	  heap_info *heap = heap_for_ptr (top (ar_ptr));
line 5128 is a new one: 	  fprintf (fp,
line 5129 is a new one: 		   "<aspace type=\"total\" size=\"%zu\"/>\n"
line 5130 is a new one: 		   "<aspace type=\"mprotect\" size=\"%zu\"/>\n",
line 5131 is a new one: 		   heap->size, heap->mprotect_size);
line 5132 is a new one: 	  total_aspace += heap->size;
line 5133 is a new one: 	  total_aspace_mprotect += heap->mprotect_size;
line 5137 is a new one: 	  fprintf (fp,
line 5138 is a new one: 		   "<aspace type=\"total\" size=\"%zu\"/>\n"
line 5139 is a new one: 		   "<aspace type=\"mprotect\" size=\"%zu\"/>\n",
line 5140 is a new one: 		   ar_ptr->system_mem, ar_ptr->system_mem);
line 5141 is a new one: 	  total_aspace += ar_ptr->system_mem;
line 5142 is a new one: 	  total_aspace_mprotect += ar_ptr->system_mem;
line 5145 is a new one:       fputs ("</heap>\n", fp);
line 5153 is a new one: 	   "<total type=\"mmap\" count=\"%d\" size=\"%zu\"/>\n"
line 5160 is a new one: 	   mp_.n_mmaps, mp_.mmapped_mem,
line 5189 is a new one:    History:
line 5191 is a new one:    [see ftp://g.oswego.edu/pub/misc/malloc.c for the history of dlmalloc]
