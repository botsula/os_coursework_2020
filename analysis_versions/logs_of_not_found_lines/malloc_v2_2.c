Comparison of files: malloc_v2_2.c and malloc_v2_0.c
line 1 is a new one:    Copyright (C) 1996,1997,1998,1999,2000,2001 Free Software Foundation, Inc.
line 7 is a new one:    modify it under the terms of the GNU Lesser General Public
line 8 is a new one:    License as published by the Free Software Foundation; either
line 9 is a new one:    version 2.1 of the License, or (at your option) any later version.
line 14 is a new one:    Lesser General Public License for more details.
line 16 is a new one:    You should have received a copy of the GNU Lesser General Public
line 17 is a new one:    License along with the GNU C Library; if not, write to the Free
line 18 is a new one:    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
line 19 is a new one:    02111-1307 USA.  */
line 21 is a new one: /* $Id$
line 184 is a new one:   REALLOC_ZERO_BYTES_FREES (default: defined)
line 186 is a new one:      to free(p).  (The C standard requires this behaviour, therefore
line 187 is a new one:      it is the default.)  Otherwise, since malloc returns a unique
line 188 is a new one:      pointer for malloc(0), so does realloc(p, 0).
line 204 is a new one:   USE_ARENAS                (default: the same as HAVE_MMAP)
line 205 is a new one:      Enable support for multiple arenas, allocated using mmap().
line 230 is a new one:      The degree to which the routine mapped to MORECORE zeroes out
line 231 is a new one:      memory: never (0), only for newly allocated space (1) or always
line 232 is a new one:      (2).  The distinction between (1) and (2) is necessary because on
line 233 is a new one:      some systems, if the application first decrements and then
line 234 is a new one:      increments the break value, the contents of the reallocated space
line 235 is a new one:      are unspecified.
line 312 is a new one: extern char* getenv();
line 325 is a new one: #include <errno.h>
line 379 is a new one:   REALLOC_ZERO_BYTES_FREES should be set if a call to realloc with
line 380 is a new one:   zero bytes should be the same as a call to free.  The C standard
line 381 is a new one:   requires this. Otherwise, since this malloc returns a unique pointer
line 382 is a new one:   for malloc(0), so does realloc(p, 0).
line 386 is a new one: #define REALLOC_ZERO_BYTES_FREES
line 417 is a new one: void* memmove(void*, const void*, size_t);
line 421 is a new one: Void_t* memmove();
line 427 is a new one:    for fast inline execution when n is small.  If the regions to be
line 428 is a new one:    copied do overlap, the destination lies always _below_ the source.  */
line 449 is a new one: /* If the regions overlap, dest is always _below_ src.  */
line 451 is a new one: #define MALLOC_COPY(dest,src,nbytes,overlap)                                  \
line 466 is a new one:   } else if(overlap)                                                          \
line 467 is a new one:     memmove(dest, src, mcsz);                                                 \
line 469 is a new one:     memcpy(dest, src, mcsz);                                                  \
line 493 is a new one: /* If the regions overlap, dest is always _below_ src.  */
line 495 is a new one: #define MALLOC_COPY(dest,src,nbytes,overlap)                                  \
line 521 is a new one:   Define HAVE_MMAP to optionally make malloc() use mmap() to allocate
line 522 is a new one:   very large blocks.  These will be returned to the operating system
line 523 is a new one:   immediately after a free().  HAVE_MMAP is also a prerequisite to
line 524 is a new one:   support multiple `arenas' (see USE_ARENAS below).
line 540 is a new one: #define HAVE_MREMAP defined(__linux__)
line 543 is a new one: /* Define USE_ARENAS to enable support for multiple `arenas'.  These
line 544 is a new one:    are allocated using mmap(), are necessary for threads and
line 545 is a new one:    occasionally useful to overcome address space limitations affecting
line 546 is a new one:    sbrk(). */
line 548 is a new one: #ifndef USE_ARENAS
line 549 is a new one: #define USE_ARENAS HAVE_MMAP
line 561 is a new one: #if !defined(MAP_FAILED)
line 562 is a new one: #define MAP_FAILED ((char*)-1)
line 661 is a new one: #include <bp-checks.h>
line 854 is a new one: /* Macro to set errno.  */
line 855 is a new one: #ifndef __set_errno
line 856 is a new one: # define __set_errno(val) errno = (val)
line 895 is a new one: static size_t __libc_pagesize;
line 897 is a new one: #define access	__access
line 903 is a new one: #define malloc_getpagesize __libc_pagesize
line 1011 is a new one: } /* end of extern "C" */
line 1017 is a new one: #if USE_ARENAS && !HAVE_MMAP
line 1018 is a new one: "Can't have multiple arenas without mmap"
line 1220 is a new one:    address aligned to HEAP_MAX_SIZE.  Not used unless compiling with
line 1221 is a new one:    USE_ARENAS. */
line 1246 is a new one: #if USE_ARENAS
line 1271 is a new one: #if USE_ARENAS
line 1294 is a new one: /* Allow the default to be overwritten on the compiler command line.  */
line 1295 is a new one: #ifndef MALLOC_ALIGNMENT
line 1296 is a new one: # define MALLOC_ALIGNMENT      (SIZE_SZ + SIZE_SZ)
line 1303 is a new one: #define chunk2mem(p) ((Void_t*)((char*)(p) + 2*SIZE_SZ))
line 1304 is a new one: #define mem2chunk(mem) chunk_at_offset((mem), -2*SIZE_SZ)
line 1306 is a new one: /* pad request bytes into a usable size, return non-zero on overflow */
line 1308 is a new one: #define request2size(req, nb) \
line 1309 is a new one:  ((nb = (req) + (SIZE_SZ + MALLOC_ALIGN_MASK)),\
line 1310 is a new one:   ((long)nb <= 0 || nb < (INTERNAL_SIZE_T) (req) \
line 1311 is a new one:    ? (__set_errno (ENOMEM), 1) \
line 1312 is a new one:    : ((nb < (MINSIZE + MALLOC_ALIGN_MASK) \
line 1313 is a new one: 	   ? (nb = MINSIZE) : (nb &= ~MALLOC_ALIGN_MASK)), 0)))
line 1329 is a new one: #define PREV_INUSE 0x1UL
line 1333 is a new one: #define IS_MMAPPED 0x2UL
line 1342 is a new one: #define next_chunk(p) chunk_at_offset((p), (p)->size & ~PREV_INUSE)
line 1346 is a new one: #define prev_chunk(p) chunk_at_offset((p), -(p)->prev_size)
line 1351 is a new one: #define chunk_at_offset(p, s)  BOUNDED_1((mchunkptr)(((char*)(p)) + (s)))
line 1362 is a new one: #define inuse(p) (next_chunk(p)->size & PREV_INUSE)
line 1374 is a new one: #define set_inuse(p) (next_chunk(p)->size |= PREV_INUSE)
line 1376 is a new one: #define clear_inuse(p) (next_chunk(p)->size &= ~PREV_INUSE)
line 1380 is a new one: #define inuse_bit_at_offset(p, s) \
line 1381 is a new one:   (chunk_at_offset((p), (s))->size & PREV_INUSE)
line 1383 is a new one: #define set_inuse_bit_at_offset(p, s) \
line 1384 is a new one:   (chunk_at_offset((p), (s))->size |= PREV_INUSE)
line 1386 is a new one: #define clear_inuse_bit_at_offset(p, s) \
line 1387 is a new one:   (chunk_at_offset((p), (s))->size &= ~(PREV_INUSE))
line 1410 is a new one: #define set_foot(p, s)   (chunk_at_offset(p, s)->prev_size = (s))
line 1418 is a new one: #define bin_at(a, i)   BOUNDED_1(_bin_at(a, i))
line 1419 is a new one: #define _bin_at(a, i)  ((mbinptr)((char*)&(((a)->av)[2*(i)+2]) - 2*SIZE_SZ))
line 1420 is a new one: #define init_bin(a, i) ((a)->av[2*(i)+2] = (a)->av[2*(i)+3] = bin_at((a), (i)))
line 1421 is a new one: #define next_bin(b)    ((mbinptr)((char*)(b) + 2 * sizeof(((arena*)0)->av[0])))
line 1422 is a new one: #define prev_bin(b)    ((mbinptr)((char*)(b) - 2 * sizeof(((arena*)0)->av[0])))
line 1505 is a new one: #define IAV(i) _bin_at(&main_arena, i), _bin_at(&main_arena, i)
line 1543 is a new one: static int stat_n_heaps;
line 1561 is a new one: static unsigned long max_sbrked_mem;
line 1565 is a new one: static unsigned long max_total_mem;
line 1573 is a new one: static unsigned int n_mmaps;
line 1574 is a new one: static unsigned int max_n_mmaps;
line 1575 is a new one: static unsigned long mmapped_mem;
line 1576 is a new one: static unsigned long max_mmapped_mem;
line 1578 is a new one: /* Mapped memory in non-main arenas (reliable only for NO_THREADS). */
line 1579 is a new one: static unsigned long arena_mem;
line 1597 is a new one: /* Magic value for the thread-specific arena pointer when
line 1598 is a new one:    malloc_atfork() is in use.  */
line 1600 is a new one: #define ATFORK_ARENA_PTR ((Void_t*)-1)
line 1634 is a new one:   tsd_setspecific(arena_key, ATFORK_ARENA_PTR);
line 1683 is a new one: #include <string.h>
line 1684 is a new one: extern char **_environ;
line 1686 is a new one: static char *
line 1688 is a new one: next_env_entry (char ***position)
line 1690 is a new one:   char **current = *position;
line 1691 is a new one:   char *result = NULL;
line 1693 is a new one:   while (*current != NULL)
line 1695 is a new one:       if (__builtin_expect ((*current)[0] == 'M', 0)
line 1696 is a new one: 	  && (*current)[1] == 'A'
line 1697 is a new one: 	  && (*current)[2] == 'L'
line 1698 is a new one: 	  && (*current)[3] == 'L'
line 1699 is a new one: 	  && (*current)[4] == 'O'
line 1700 is a new one: 	  && (*current)[5] == 'C'
line 1701 is a new one: 	  && (*current)[6] == '_')
line 1702 is a new one: 	{
line 1703 is a new one: 	  result = &(*current)[7];
line 1705 is a new one: 	  /* Save current position for next visit.  */
line 1706 is a new one: 	  *position = ++current;
line 1708 is a new one: 	  break;
line 1709 is a new one: 	}
line 1711 is a new one:       ++current;
line 1714 is a new one:   return result;
line 1726 is a new one: # if __STD_C
line 1729 is a new one:   char* s;
line 1732 is a new one:   int secure;
line 1737 is a new one:   __libc_pagesize = __getpagesize();
line 1765 is a new one:   secure = __libc_enable_secure;
line 1767 is a new one:   s = NULL;
line 1768 is a new one:   if (_environ != NULL)
line 1770 is a new one:       char **runp = _environ;
line 1771 is a new one:       char *envline;
line 1773 is a new one:       while (__builtin_expect ((envline = next_env_entry (&runp)) != NULL, 0))
line 1774 is a new one: 	{
line 1775 is a new one: 	  size_t len = strcspn (envline, "=");
line 1777 is a new one: 	  if (envline[len] != '=')
line 1778 is a new one: 	    /* This is a "MALLOC_" variable at the end of the string
line 1779 is a new one: 	       without a '=' character.  Ignore it since otherwise we
line 1780 is a new one: 	       will access invalid memory below.  */
line 1781 is a new one: 	    continue;
line 1783 is a new one: 	  switch (len)
line 1784 is a new one: 	    {
line 1785 is a new one: 	    case 6:
line 1786 is a new one: 	      if (memcmp (envline, "CHECK_", 6) == 0)
line 1787 is a new one: 		s = &envline[7];
line 1788 is a new one: 	      break;
line 1789 is a new one: 	    case 8:
line 1790 is a new one: 	      if (! secure && memcmp (envline, "TOP_PAD_", 8) == 0)
line 1791 is a new one: 		mALLOPt(M_TOP_PAD, atoi(&envline[9]));
line 1792 is a new one: 	      break;
line 1793 is a new one: 	    case 9:
line 1794 is a new one: 	      if (! secure && memcmp (envline, "MMAP_MAX_", 9) == 0)
line 1795 is a new one: 		mALLOPt(M_MMAP_MAX, atoi(&envline[10]));
line 1796 is a new one: 	      break;
line 1797 is a new one: 	    case 15:
line 1798 is a new one: 	      if (! secure)
line 1799 is a new one: 		{
line 1800 is a new one: 		  if (memcmp (envline, "TRIM_THRESHOLD_", 15) == 0)
line 1801 is a new one: 		    mALLOPt(M_TRIM_THRESHOLD, atoi(&envline[16]));
line 1802 is a new one: 		  else if (memcmp (envline, "MMAP_THRESHOLD_", 15) == 0)
line 1803 is a new one: 		    mALLOPt(M_MMAP_THRESHOLD, atoi(&envline[16]));
line 1804 is a new one: 		}
line 1805 is a new one: 	      break;
line 1806 is a new one: 	    default:
line 1807 is a new one: 	      break;
line 1808 is a new one: 	    }
line 1809 is a new one: 	}
line 1812 is a new one:   if (! secure)
line 1814 is a new one:       if((s = getenv("MALLOC_TRIM_THRESHOLD_")))
line 1815 is a new one: 	mALLOPt(M_TRIM_THRESHOLD, atoi(s));
line 1816 is a new one:       if((s = getenv("MALLOC_TOP_PAD_")))
line 1817 is a new one: 	mALLOPt(M_TOP_PAD, atoi(s));
line 1818 is a new one:       if((s = getenv("MALLOC_MMAP_THRESHOLD_")))
line 1819 is a new one: 	mALLOPt(M_MMAP_THRESHOLD, atoi(s));
line 1820 is a new one:       if((s = getenv("MALLOC_MMAP_MAX_")))
line 1821 is a new one: 	mALLOPt(M_MMAP_MAX, atoi(s));
line 1850 is a new one: malloc_hook_ini(sz, caller)
line 1851 is a new one:      size_t sz; const __malloc_ptr_t caller;
line 1875 is a new one: memalign_hook_ini(size_t alignment, size_t sz, const __malloc_ptr_t caller)
line 1877 is a new one: memalign_hook_ini(alignment, sz, caller)
line 1878 is a new one:      size_t alignment; size_t sz; const __malloc_ptr_t caller;
line 1883 is a new one:   return mEMALIGn(alignment, sz);
line 1895 is a new one:  __MALLOC_P ((size_t __alignment, size_t __size, const __malloc_ptr_t))
line 1899 is a new one: /* Whether we are using malloc checking.  */
line 1900 is a new one: static int using_malloc_checking;
line 1902 is a new one: /* A flag that is set by malloc_set_state, to signal that malloc checking
line 1903 is a new one:    must not be enabled on the request from the user (via the MALLOC_CHECK_
line 1904 is a new one:    environment variable).  It is reset by __malloc_check_init to tell
line 1905 is a new one:    malloc_set_state that the user has requested malloc checking.
line 1907 is a new one:    The purpose of this flag is to make sure that malloc checking is not
line 1908 is a new one:    enabled when the heap to be restored was constructed without malloc
line 1909 is a new one:    checking, and thus does not contain the required magic bytes.
line 1910 is a new one:    Otherwise the heap would be corrupted by calls to free and realloc.  If
line 1911 is a new one:    it turns out that the heap was created with malloc checking and the
line 1912 is a new one:    user has requested it malloc_set_state just calls __malloc_check_init
line 1913 is a new one:    again to enable it.  On the other hand, reusing such a heap without
line 1914 is a new one:    further malloc checking is safe.  */
line 1915 is a new one: static int disallow_malloc_check;
line 1921 is a new one:   if (disallow_malloc_check) {
line 1922 is a new one:     disallow_malloc_check = 0;
line 1925 is a new one:   using_malloc_checking = 1;
line 1930 is a new one:   if(check_action & 1)
line 1962 is a new one: __inline__
line 2000 is a new one:   if ((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2001 is a new one:     max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2009 is a new one: munmap_chunk(mchunkptr p)
line 2011 is a new one: munmap_chunk(p) mchunkptr p;
line 2036 is a new one: mremap_chunk(mchunkptr p, size_t new_size)
line 2038 is a new one: mremap_chunk(p, new_size) mchunkptr p; size_t new_size;
line 2057 is a new one:   if (cp == MAP_FAILED) return 0;
line 2071 is a new one:   if ((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2072 is a new one:     max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2085 is a new one: #if USE_ARENAS
line 2118 is a new one:   if(p1 != MAP_FAILED) {
line 2119 is a new one:     p2 = (char *)(((unsigned long)p1 + (HEAP_MAX_SIZE-1)) & ~(HEAP_MAX_SIZE-1));
line 2120 is a new one:     ul = p2 - p1;
line 2121 is a new one:     if (ul)
line 2122 is a new one:       munmap(p1, ul);
line 2123 is a new one:     munmap(p2 + HEAP_MAX_SIZE, HEAP_MAX_SIZE - ul);
line 2125 is a new one:     /* Try to take the chance that an allocation of only HEAP_MAX_SIZE
line 2126 is a new one:        is already aligned. */
line 2127 is a new one:     p2 = (char *)MMAP(0, HEAP_MAX_SIZE, PROT_NONE, MAP_PRIVATE|MAP_NORESERVE);
line 2128 is a new one:     if(p2 == MAP_FAILED)
line 2130 is a new one:     if((unsigned long)p2 & (HEAP_MAX_SIZE-1)) {
line 2131 is a new one:       munmap(p2, HEAP_MAX_SIZE);
line 2135 is a new one:   if(MMAP(p2, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED)
line 2136 is a new one:      == (char *) MAP_FAILED) {
line 2164 is a new one:     if(MMAP((char *)h + h->size, diff, PROT_READ|PROT_WRITE,
line 2165 is a new one: 	    MAP_PRIVATE|MAP_FIXED) == (char *) MAP_FAILED)
line 2171 is a new one:     /* Try to re-map the extra heap space freshly to save memory, and
line 2172 is a new one:        make it inaccessible. */
line 2173 is a new one:     if((char *)MMAP((char *)h + new_size, -diff, PROT_NONE,
line 2174 is a new one:                     MAP_PRIVATE|MAP_FIXED) == (char *) MAP_FAILED)
line 2189 is a new one:    readily available, create a new one.  In this latter case, `size'
line 2190 is a new one:    is just a hint as to how much memory will be required immediately
line 2191 is a new one:    in the new arena. */
line 2251 is a new one:   if(!h) {
line 2252 is a new one:     /* Maybe size is too large to fit in a single heap.  So, just try
line 2253 is a new one:        to create a minimally-sized arena and let chunk_alloc() attempt
line 2254 is a new one:        to deal with the large request via mmap_chunk(). */
line 2255 is a new one:     h = new_heap(sizeof(*h) + sizeof(*a) + MALLOC_ALIGNMENT);
line 2256 is a new one:     if(!h)
line 2264 is a new one:   arena_mem += h->size;
line 2266 is a new one:   if((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2267 is a new one:     max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2302 is a new one: #else /* !USE_ARENAS */
line 2304 is a new one: /* There is only one arena, main_arena. */
line 2309 is a new one: #endif /* USE_ARENAS */
line 2339 is a new one: #if USE_ARENAS
line 2343 is a new one:     if(p != top(ar_ptr))
line 2344 is a new one:       assert((char *)p + sz <= (char *)heap + heap->size);
line 2547 is a new one: __inline__
line 2562 is a new one: #if USE_ARENAS
line 2631 is a new one:       top(&main_arena) = chunk_at_offset(brk, 0);
line 2642 is a new one:     if ((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2643 is a new one:       max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2646 is a new one: #if USE_ARENAS
line 2661 is a new one:       arena_mem += old_heap->size - old_heap_size;
line 2663 is a new one:       if(mmapped_mem + arena_mem + sbrked_mem > max_total_mem)
line 2664 is a new one:         max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2678 is a new one:     arena_mem += heap->size;
line 2680 is a new one:     if((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2681 is a new one:       max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2689 is a new one: #endif /* USE_ARENAS */
line 2790 is a new one:   __malloc_ptr_t (*hook) __MALLOC_PMT ((size_t, __const __malloc_ptr_t)) =
line 2791 is a new one:       __malloc_hook;
line 2792 is a new one:   if (hook != NULL) {
line 2796 is a new one:     result = (*hook)(bytes, RETURN_ADDRESS (0));
line 2798 is a new one:     result = (*hook)(bytes, NULL);
line 2804 is a new one:   if(request2size(bytes, nb))
line 2818 is a new one: #if USE_ARENAS
line 2819 is a new one:       /* ... or sbrk() has failed and there is still a chance to mmap() */
line 2820 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, nb);
line 2822 is a new one:       if(ar_ptr) {
line 2823 is a new one:         victim = chunk_alloc(ar_ptr, nb);
line 2824 is a new one:         (void)mutex_unlock(&ar_ptr->mutex);
line 2829 is a new one:   } else
line 2831 is a new one:   return BOUNDED_N(chunk2mem(victim), bytes);
line 2864 is a new one:     q = _bin_at(ar_ptr, idx);
line 2972 is a new one:       q = bin = _bin_at(ar_ptr, idx);
line 3046 is a new one:     /* If the request is big and there are not yet too many regions,
line 3047 is a new one:        and we would otherwise need to extend, try to use mmap instead.  */
line 3049 is a new one:         n_mmaps < n_mmaps_max &&
line 3059 is a new one:       /* A last attempt: when we are out of address space in a
line 3060 is a new one:          non-main arena, try mmap anyway, as long as it is allowed at
line 3061 is a new one:          all.  */
line 3062 is a new one:       if (ar_ptr != &main_arena &&
line 3063 is a new one:           n_mmaps_max > 0 &&
line 3064 is a new one:           (victim = mmap_chunk(nb)) != 0)
line 3115 is a new one:   void (*hook) __MALLOC_PMT ((__malloc_ptr_t, __const __malloc_ptr_t)) =
line 3116 is a new one:     __free_hook;
line 3118 is a new one:   if (hook != NULL) {
line 3120 is a new one:     (*hook)(mem, RETURN_ADDRESS (0));
line 3122 is a new one:     (*hook)(mem, NULL);
line 3187 is a new one:       p = chunk_at_offset(p, -(long)prevsz);
line 3195 is a new one: #if USE_ARENAS
line 3200 is a new one: #if USE_ARENAS
line 3220 is a new one:     p = chunk_at_offset(p, -(long)prevsz);
line 3252 is a new one: #if USE_ARENAS
line 3257 is a new one:     heap_info *heap = heap_for_ptr(top(ar_ptr));
line 3321 is a new one:   __malloc_ptr_t (*hook) __MALLOC_PMT ((__malloc_ptr_t, size_t,
line 3322 is a new one:                                         __const __malloc_ptr_t)) =
line 3323 is a new one:     __realloc_hook;
line 3324 is a new one:   if (hook != NULL) {
line 3328 is a new one:     result = (*hook)(oldmem, bytes, RETURN_ADDRESS (0));
line 3330 is a new one:     result = (*hook)(oldmem, bytes, NULL);
line 3337 is a new one:   if (bytes == 0 && oldmem != NULL) { fREe(oldmem); return 0; }
line 3346 is a new one:   if(request2size(bytes, nb))
line 3356 is a new one:     if(newp)
line 3357 is a new one:       return BOUNDED_N(chunk2mem(newp), bytes);
line 3364 is a new one:     MALLOC_COPY(newmem, oldmem, oldsize - 2*SIZE_SZ, 0);
line 3390 is a new one:   return newp ? BOUNDED_N(chunk2mem(newp), bytes) : NULL;
line 3422 is a new one:     Void_t* oldmem = BOUNDED_N(chunk2mem(oldp), oldsize);
line 3458 is a new one:     oldsize -= SIZE_SZ;
line 3479 is a new one:             MALLOC_COPY(BOUNDED_N(chunk2mem(newp), oldsize), oldmem, oldsize,
line 3480 is a new one:                         1);
line 3495 is a new one:           MALLOC_COPY(BOUNDED_N(chunk2mem(newp), oldsize), oldmem, oldsize, 1);
line 3506 is a new one:         MALLOC_COPY(BOUNDED_N(chunk2mem(newp), oldsize), oldmem, oldsize, 1);
line 3521 is a new one:       } else {
line 3522 is a new one: #if USE_ARENAS
line 3523 is a new one:         /* ... or sbrk() has failed and there is still a chance to mmap() */
line 3524 is a new one:         arena* ar_ptr2 = arena_get2(ar_ptr->next ? ar_ptr : 0, nb);
line 3525 is a new one:         if(ar_ptr2) {
line 3526 is a new one:           newp = chunk_alloc(ar_ptr2, nb);
line 3527 is a new one:           (void)mutex_unlock(&ar_ptr2->mutex);
line 3546 is a new one:     MALLOC_COPY(BOUNDED_N(chunk2mem(newp), oldsize), oldmem, oldsize, 0);
line 3606 is a new one:   __malloc_ptr_t (*hook) __MALLOC_PMT ((size_t, size_t,
line 3607 is a new one:                                         __const __malloc_ptr_t)) =
line 3608 is a new one:     __memalign_hook;
line 3609 is a new one:   if (hook != NULL) {
line 3613 is a new one:     result = (*hook)(alignment, bytes, RETURN_ADDRESS (0));
line 3615 is a new one:     result = (*hook)(alignment, bytes, NULL);
line 3629 is a new one:   if(request2size(bytes, nb))
line 3643 is a new one: #if USE_ARENAS
line 3644 is a new one:       /* ... or sbrk() has failed and there is still a chance to mmap() */
line 3645 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, nb);
line 3646 is a new one:       if(ar_ptr) {
line 3647 is a new one:         p = chunk_align(ar_ptr, nb, alignment);
line 3648 is a new one:         (void)mutex_unlock(&ar_ptr->mutex);
line 3654 is a new one:   return BOUNDED_N(chunk2mem(p), bytes);
line 3666 is a new one:   unsigned long m;            /* memory returned by malloc call */
line 3680 is a new one:   m = (unsigned long)chunk2mem(p);
line 3682 is a new one:   if ((m % alignment) == 0) /* aligned */
line 3701 is a new one:     brk = (char*)mem2chunk(((m + alignment - 1)) & -(long)alignment);
line 3704 is a new one:     newp = chunk_at_offset(brk, 0);
line 3759 is a new one:   if(__malloc_initialized < 0)
line 3760 is a new one:     ptmalloc_init ();
line 3776 is a new one:   size_t pagesize;
line 3777 is a new one:   if(__malloc_initialized < 0)
line 3778 is a new one:     ptmalloc_init ();
line 3779 is a new one:   pagesize = malloc_getpagesize;
line 3801 is a new one:   __malloc_ptr_t (*hook) __MALLOC_PMT ((size_t, __const __malloc_ptr_t)) =
line 3802 is a new one:     __malloc_hook;
line 3803 is a new one:   if (hook != NULL) {
line 3806 is a new one:     mem = (*hook)(sz, RETURN_ADDRESS (0));
line 3808 is a new one:     mem = (*hook)(sz, NULL);
line 3821 is a new one:   if(request2size(n * elem_size, sz))
line 3827 is a new one:   /* Check if expand_top called, in which case there may be
line 3828 is a new one:      no need to clear. */
line 3832 is a new one: #if MORECORE_CLEARS < 2
line 3833 is a new one:   /* Only newly allocated memory is guaranteed to be cleared.  */
line 3834 is a new one:   if (ar_ptr == &main_arena &&
line 3835 is a new one:       oldtopsize < sbrk_base + max_sbrked_mem - (char *)oldtop)
line 3836 is a new one:     oldtopsize = (sbrk_base + max_sbrked_mem - (char *)oldtop);
line 3851 is a new one: #if USE_ARENAS
line 3852 is a new one:       /* ... or sbrk() has failed and there is still a chance to mmap() */
line 3854 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, sz);
line 3856 is a new one:       if(ar_ptr) {
line 3857 is a new one:         p = chunk_alloc(ar_ptr, sz);
line 3858 is a new one:         (void)mutex_unlock(&ar_ptr->mutex);
line 3864 is a new one:   mem = BOUNDED_N(chunk2mem(p), n * elem_size);
line 3881 is a new one:   csz -= SIZE_SZ;
line 3882 is a new one:   MALLOC_ZERO(BOUNDED_N(chunk2mem(p), csz), csz);
line 3900 is a new one:   fREe(mem);
line 4001 is a new one: #if USE_ARENAS
line 4031 is a new one:     arena_mem -= heap->size;
line 4052 is a new one:   arena_mem -= extra;
line 4060 is a new one: #endif /* USE_ARENAS */
line 4151 is a new one: #if USE_ARENAS && MALLOC_DEBUG > 1
line 4227 is a new one: #if USE_ARENAS && MALLOC_DEBUG > 1
line 4275 is a new one:   if(vptr == ATFORK_ARENA_PTR)
line 4276 is a new one:     vptr = (Void_t*)&main_arena;
line 4311 is a new one: #if USE_ARENAS
line 4342 is a new one:    functions, with two exceptions: If malloc checking was in use when
line 4343 is a new one:    malloc_get_state() was called, then malloc_set_state() calls
line 4344 is a new one:    __malloc_check_init() if possible; if malloc checking was not in
line 4345 is a new one:    use in the recorded state but the user requested malloc checking,
line 4346 is a new one:    then the hooks are reset to 0.  */
line 4349 is a new one: #define MALLOC_STATE_VERSION (0*0x100l + 1l) /* major*0x100 + minor */
line 4368 is a new one:   int           using_malloc_checking;
line 4378 is a new one:   ms = (struct malloc_state*)mALLOc(sizeof(*ms));
line 4379 is a new one:   if (!ms)
line 4413 is a new one:   ms->using_malloc_checking = using_malloc_checking;
line 4415 is a new one:   ms->using_malloc_checking = 0;
line 4433 is a new one:   disallow_malloc_check = 1;
line 4472 is a new one:   if (ms->version >= 1) {
line 4474 is a new one:     /* Check whether it is safe to enable malloc checking, or whether
line 4475 is a new one:        it is necessary to disable it.  */
line 4476 is a new one:     if (ms->using_malloc_checking && !using_malloc_checking &&
line 4477 is a new one:         !disallow_malloc_check)
line 4478 is a new one:       __malloc_check_init ();
line 4479 is a new one:     else if (!ms->using_malloc_checking && using_malloc_checking) {
line 4480 is a new one:       __malloc_hook = 0;
line 4481 is a new one:       __free_hook = 0;
line 4482 is a new one:       __realloc_hook = 0;
line 4483 is a new one:       __memalign_hook = 0;
line 4484 is a new one:       using_malloc_checking = 0;
line 4515 is a new one:   unsigned char* m_ptr = (unsigned char*)BOUNDED_N(chunk2mem(p), sz);
line 4605 is a new one:   if(check_action & 1)
line 4607 is a new one:   if(check_action & 2)
line 4637 is a new one:   if(request2size(sz+1, nb))
line 4660 is a new one:     if(check_action & 1)
line 4662 is a new one:     if(check_action & 2)
line 4696 is a new one:     if(check_action & 1)
line 4698 is a new one:     if(check_action & 2)
line 4704 is a new one:   if(request2size(bytes+1, nb)) {
line 4721 is a new one:           MALLOC_COPY(BOUNDED_N(chunk2mem(newp), nb),
line 4722 is a new one: 		      oldmem, oldsize - 2*SIZE_SZ, 0);
line 4739 is a new one:       memset((char*)BOUNDED_N(chunk2mem(newp), bytes) + oldsize,
line 4740 is a new one: 	     0, nb - (oldsize+SIZE_SZ));
line 4766 is a new one:   if(request2size(bytes+1, nb))
line 4790 is a new one:   if(request2size(sz, nb))
line 4792 is a new one:   victim = chunk_alloc(&main_arena, nb);
line 4794 is a new one:   return victim ? BOUNDED_N(chunk2mem(victim), sz) : 0;
line 4832 is a new one:   if(vptr == ATFORK_ARENA_PTR) {
line 4833 is a new one:     /* We are the only thread that may allocate at all.  */
line 4834 is a new one:     if(save_malloc_hook != malloc_check) {
line 4835 is a new one:       if(request2size(sz, nb))
line 4838 is a new one:       return victim ? BOUNDED_N(chunk2mem(victim), sz) : 0;
line 4840 is a new one:       if(top_check()<0 || request2size(sz+1, nb))
line 4843 is a new one:       return victim ? chunk2mem_check(victim, sz) : 0;
line 4869 is a new one:   p = mem2chunk(mem);         /* do not bother to replicate free_check here */
line 4881 is a new one:   if(vptr != ATFORK_ARENA_PTR)
line 4884 is a new one:   if(vptr != ATFORK_ARENA_PTR)
line 4895 is a new one: /* We need a wrapper function for one of the additions of POSIX.  */
line 4897 is a new one: __posix_memalign (void **memptr, size_t alignment, size_t size)
line 4899 is a new one:   void *mem;
line 4901 is a new one:   /* Test whether the SIZE argument is valid.  It must be a power of
line 4902 is a new one:      two multiple of sizeof (void *).  */
line 4903 is a new one:   if (size % sizeof (void *) != 0 || (size & (size - 1)) != 0)
line 4904 is a new one:     return EINVAL;
line 4906 is a new one:   mem = __libc_memalign (alignment, size);
line 4908 is a new one:   if (mem != NULL)
line 4910 is a new one:       *memptr = mem;
line 4914 is a new one:   return ENOMEM;
line 4916 is a new one: weak_alias (__posix_memalign, posix_memalign)
