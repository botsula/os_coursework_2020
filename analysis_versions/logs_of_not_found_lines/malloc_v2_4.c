Comparison of files: malloc_v2_4.c and malloc_v2_2.c
line 1 is a new one:    Copyright (C) 1996-2002,2003,2004,2005,2006 Free Software Foundation, Inc.
line 3 is a new one:    Contributed by Wolfram Gloger <wg@malloc.de>
line 4 is a new one:    and Doug Lea <dl@cs.oswego.edu>, 2001.
line 7 is a new one:    modify it under the terms of the GNU Lesser General Public License as
line 8 is a new one:    published by the Free Software Foundation; either version 2.1 of the
line 9 is a new one:    License, or (at your option) any later version.
line 17 is a new one:    License along with the GNU C Library; see the file COPYING.LIB.  If not,
line 18 is a new one:    write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
line 19 is a new one:    Boston, MA 02111-1307, USA.  */
line 22 is a new one:   This is a version (aka ptmalloc2) of malloc/free/realloc written by
line 23 is a new one:   Doug Lea and adapted to multiple threads/arenas by Wolfram Gloger.
line 25 is a new one: * Version ptmalloc2-20011215
line 26 is a new one:   based on:
line 27 is a new one:   VERSION 2.7.0 Sun Mar 11 14:14:06 2001  Doug Lea  (dl at gee)
line 29 is a new one:    Note: There may be an updated version of this malloc obtainable at
line 30 is a new one:            http://www.malloc.de/malloc/ptmalloc2.tar.gz
line 31 is a new one:          Check before installing!
line 33 is a new one: * Quickstart
line 35 is a new one:   In order to compile this implementation, a Makefile is provided with
line 36 is a new one:   the ptmalloc2 distribution, which has pre-defined targets for some
line 37 is a new one:   popular systems (e.g. "make posix" for Posix threads).  All that is
line 38 is a new one:   typically required with regard to compiler flags is the selection of
line 39 is a new one:   the thread package via defining one out of USE_PTHREADS, USE_THR or
line 40 is a new one:   USE_SPROC.  Check the thread-m.h file for what effects this has.
line 41 is a new one:   Many/most systems will additionally require USE_TSD_DATA_HACK to be
line 42 is a new one:   defined, so this is the default for "make posix".
line 50 is a new one:   allocator for malloc-intensive programs.
line 52 is a new one:   The main properties of the algorithms are:
line 53 is a new one:   * For large (>= 512 bytes) requests, it is a pure best-fit allocator,
line 54 is a new one:     with ties normally decided via FIFO (i.e. least recently used).
line 55 is a new one:   * For small (<= 64 bytes by default) requests, it is a caching
line 56 is a new one:     allocator, that maintains pools of quickly recycled chunks.
line 57 is a new one:   * In between, and for combinations of large and small requests, it does
line 58 is a new one:     the best it can trying to meet both goals at once.
line 59 is a new one:   * For very large requests (>= 128KB by default), it relies on system
line 60 is a new one:     memory mapping facilities, if supported.
line 62 is a new one:   For a longer but slightly out of date high-level description, see
line 63 is a new one:      http://gee.cs.oswego.edu/dl/html/malloc.html
line 65 is a new one:   You may already by default be using a C library containing a malloc
line 66 is a new one:   that is  based on some version of this malloc (for example in
line 67 is a new one:   linux). You might still want to use the one in this file in order to
line 68 is a new one:   customize settings or to avoid overheads associated with library
line 69 is a new one:   versions.
line 71 is a new one: * Contents, described in more detail in "description of public routines" below.
line 73 is a new one:   Standard (ANSI/SVID/...)  functions:
line 74 is a new one:     malloc(size_t n);
line 75 is a new one:     calloc(size_t n_elements, size_t element_size);
line 76 is a new one:     free(Void_t* p);
line 77 is a new one:     realloc(Void_t* p, size_t n);
line 78 is a new one:     memalign(size_t alignment, size_t n);
line 79 is a new one:     valloc(size_t n);
line 80 is a new one:     mallinfo()
line 81 is a new one:     mallopt(int parameter_number, int parameter_value)
line 83 is a new one:   Additional functions:
line 84 is a new one:     independent_calloc(size_t n_elements, size_t size, Void_t* chunks[]);
line 85 is a new one:     independent_comalloc(size_t n_elements, size_t sizes[], Void_t* chunks[]);
line 86 is a new one:     pvalloc(size_t n);
line 87 is a new one:     cfree(Void_t* p);
line 88 is a new one:     malloc_trim(size_t pad);
line 89 is a new one:     malloc_usable_size(Void_t* p);
line 90 is a new one:     malloc_stats();
line 94 is a new one:   Supported pointer representation:       4 or 8 bytes
line 95 is a new one:   Supported size_t  representation:       4 or 8 bytes
line 97 is a new one:        You can adjust this by defining INTERNAL_SIZE_T
line 99 is a new one:   Alignment:                              2 * sizeof(size_t) (default)
line 100 is a new one:        (i.e., 8 byte alignment with 4byte size_t). This suffices for
line 101 is a new one:        nearly all current machines and C compilers. However, you can
line 102 is a new one:        define MALLOC_ALIGNMENT to be wider than this if necessary.
line 104 is a new one:   Minimum overhead per allocated chunk:   4 or 8 bytes
line 105 is a new one:        Each malloced chunk has a hidden word of overhead holding size
line 113 is a new one:        needed; 4 (8) for a trailing size field and 8 (16) bytes for
line 114 is a new one:        free list pointers. Thus, the minimum allocatable size is
line 115 is a new one:        16/24/32 bytes.
line 120 is a new one:        The maximum overhead wastage (i.e., number of extra bytes
line 121 is a new one:        allocated than were requested in malloc) is less than or equal
line 122 is a new one:        to the minimum size, except for requests >= mmap_threshold that
line 123 is a new one:        are serviced via mmap(), where the worst case wastage is 2 *
line 124 is a new one:        sizeof(size_t) bytes plus the remainder from a system page (the
line 125 is a new one:        minimal mmap unit); typically 4096 or 8192 bytes.
line 127 is a new one:   Maximum allocated size:  4-byte size_t: 2^32 minus about two pages
line 128 is a new one:                            8-byte size_t: 2^64 minus about two pages
line 130 is a new one:        It is assumed that (possibly signed) size_t values suffice to
line 133 is a new one:        an unsigned type. The ISO C standard says that it must be
line 134 is a new one:        unsigned, but a few systems are known not to adhere to this.
line 135 is a new one:        Additionally, even when size_t is unsigned, sbrk (which is by
line 136 is a new one:        default used to obtain memory from system) accepts signed
line 137 is a new one:        arguments, and may not be able to handle size_t-wide arguments
line 138 is a new one:        with negative sign bit.  Generally, values that would
line 139 is a new one:        appear as negative after accounting for overhead and alignment
line 140 is a new one:        are supported only via mmap(), which does not have this
line 141 is a new one:        limitation.
line 143 is a new one:        Requests for sizes outside the allowed range will perform an optional
line 144 is a new one:        failure action and then return null. (Requests may also
line 145 is a new one:        also fail because a system is out of memory.)
line 147 is a new one:   Thread-safety: thread-safe unless NO_THREADS is defined
line 149 is a new one:   Compliance: I believe it is compliant with the 1997 Single Unix Specification
line 150 is a new one:        (See http://www.opennc.org). Also SVID/XPG, ANSI C, and probably
line 151 is a new one:        others as well.
line 158 is a new one:     Linux. It is also reported to work on WIN32 platforms.
line 159 is a new one:     People also report using it in stand-alone embedded systems.
line 161 is a new one:     The implementation is in straight, hand-tuned ANSI C.  It is not
line 162 is a new one:     at all modular. (Sorry!)  It uses a lot of macros.  To be at all
line 163 is a new one:     usable, this code should be compiled using an optimizing compiler
line 164 is a new one:     (for example gcc -O3) that can simplify expressions and control
line 165 is a new one:     paths. (FAQ: some macros import variables as arguments rather than
line 166 is a new one:     declare locals because people reported that some debuggers
line 167 is a new one:     otherwise get confused.)
line 169 is a new one:     OPTION                     DEFAULT VALUE
line 171 is a new one:     Compilation Environment options:
line 173 is a new one:     __STD_C                    derived from C compiler defines
line 174 is a new one:     WIN32                      NOT defined
line 175 is a new one:     HAVE_MEMCPY                defined
line 176 is a new one:     USE_MEMCPY                 1 if HAVE_MEMCPY is defined
line 177 is a new one:     HAVE_MMAP                  defined as 1
line 178 is a new one:     MMAP_CLEARS                1
line 179 is a new one:     HAVE_MREMAP                0 unless linux defined
line 180 is a new one:     USE_ARENAS                 the same as HAVE_MMAP
line 181 is a new one:     malloc_getpagesize         derived from system #includes, or 4096 if not
line 182 is a new one:     HAVE_USR_INCLUDE_MALLOC_H  NOT defined
line 183 is a new one:     LACKS_UNISTD_H             NOT defined unless WIN32
line 184 is a new one:     LACKS_SYS_PARAM_H          NOT defined unless WIN32
line 185 is a new one:     LACKS_SYS_MMAN_H           NOT defined unless WIN32
line 187 is a new one:     Changing default word sizes:
line 189 is a new one:     INTERNAL_SIZE_T            size_t
line 190 is a new one:     MALLOC_ALIGNMENT           MAX (2 * sizeof(INTERNAL_SIZE_T),
line 191 is a new one: 				    __alignof__ (long double))
line 193 is a new one:     Configuration and functionality options:
line 195 is a new one:     USE_DL_PREFIX              NOT defined
line 196 is a new one:     USE_PUBLIC_MALLOC_WRAPPERS NOT defined
line 197 is a new one:     USE_MALLOC_LOCK            NOT defined
line 198 is a new one:     MALLOC_DEBUG               NOT defined
line 199 is a new one:     REALLOC_ZERO_BYTES_FREES   1
line 200 is a new one:     MALLOC_FAILURE_ACTION      errno = ENOMEM, if __STD_C defined, else no-op
line 201 is a new one:     TRIM_FASTBINS              0
line 203 is a new one:     Options for customizing MORECORE:
line 205 is a new one:     MORECORE                   sbrk
line 206 is a new one:     MORECORE_FAILURE           -1
line 207 is a new one:     MORECORE_CONTIGUOUS        1
line 208 is a new one:     MORECORE_CANNOT_TRIM       NOT defined
line 209 is a new one:     MORECORE_CLEARS            1
line 210 is a new one:     MMAP_AS_MORECORE_SIZE      (1024 * 1024)
line 212 is a new one:     Tuning options that are also dynamically changeable via mallopt:
line 214 is a new one:     DEFAULT_MXFAST             64
line 215 is a new one:     DEFAULT_TRIM_THRESHOLD     128 * 1024
line 216 is a new one:     DEFAULT_TOP_PAD            0
line 217 is a new one:     DEFAULT_MMAP_THRESHOLD     128 * 1024
line 218 is a new one:     DEFAULT_MMAP_MAX           65536
line 220 is a new one:     There are several other #defined constants and macros that you
line 221 is a new one:     probably don't want to touch unless you are extending or adapting malloc.  */
line 224 is a new one:   __STD_C should be nonzero if using ANSI-standard C compiler, a C++
line 225 is a new one:   compiler, or a C compiler sufficiently close to ANSI to get away
line 226 is a new one:   with it.
line 230 is a new one: #if defined(__STDC__) || defined(__cplusplus)
line 239 is a new one:   Void_t* is the pointer type that malloc should say it returns
line 243 is a new one: #if (__STD_C || defined(WIN32))
line 251 is a new one: #include <stddef.h>   /* for size_t */
line 252 is a new one: #include <stdlib.h>   /* for getenv(), abort() */
line 254 is a new one: #include <sys/types.h>
line 257 is a new one: #include <malloc-machine.h>
line 260 is a new one: #include <stdio-common/_itoa.h>
line 267 is a new one: /* define LACKS_UNISTD_H if your system does not have a <unistd.h>. */
line 269 is a new one: /* #define  LACKS_UNISTD_H */
line 275 is a new one: /* define LACKS_SYS_PARAM_H if your system does not have a <sys/param.h>. */
line 277 is a new one: /* #define  LACKS_SYS_PARAM_H */
line 281 is a new one: #include <errno.h>    /* needed for optional MALLOC_FAILURE_ACTION */
line 283 is a new one: /* For uintptr_t.  */
line 284 is a new one: #include <stdint.h>
line 286 is a new one: /* For va_arg, va_start, va_end.  */
line 287 is a new one: #include <stdarg.h>
line 289 is a new one: /* For writev and struct iovec.  */
line 290 is a new one: #include <sys/uio.h>
line 291 is a new one: /* For syslog.  */
line 292 is a new one: #include <sys/syslog.h>
line 294 is a new one: /* For various dynamic linking things.  */
line 295 is a new one: #include <dlfcn.h>
line 299 is a new one:   Debugging:
line 301 is a new one:   Because freed chunks may be overwritten with bookkeeping fields, this
line 302 is a new one:   malloc will often die when freed memory is overwritten by user
line 303 is a new one:   programs.  This can be very effective (albeit in an annoying way)
line 304 is a new one:   in helping track down dangling pointers.
line 306 is a new one:   If you compile with -DMALLOC_DEBUG, a number of assertion checks are
line 307 is a new one:   enabled that will catch more memory errors. You probably won't be
line 308 is a new one:   able to make much sense of the actual assertion errors, but they
line 309 is a new one:   should help you locate incorrectly overwritten memory.  The checking
line 310 is a new one:   is fairly extensive, and will slow down execution
line 311 is a new one:   noticeably. Calling malloc_stats or mallinfo with MALLOC_DEBUG set
line 312 is a new one:   will attempt to check every non-mmapped allocated and free chunk in
line 313 is a new one:   the course of computing the summmaries. (By nature, mmapped regions
line 314 is a new one:   cannot be checked very much automatically.)
line 316 is a new one:   Setting MALLOC_DEBUG may also be helpful if you are trying to modify
line 317 is a new one:   this code. The assertions in the check routines spell out in more
line 318 is a new one:   detail the assumptions and invariants underlying the algorithms.
line 320 is a new one:   Setting MALLOC_DEBUG does NOT provide an automated mechanism for
line 321 is a new one:   checking that all accesses to malloced memory stay within their
line 322 is a new one:   bounds. However, there are several add-ons and adaptations of this
line 323 is a new one:   or other mallocs available that do this.
line 329 is a new one: #undef	assert
line 336 is a new one:   of chunk sizes.
line 338 is a new one:   The default version is the same as size_t.
line 340 is a new one:   While not strictly necessary, it is best to define this as an
line 341 is a new one:   unsigned type, even if size_t is a signed type. This may avoid some
line 342 is a new one:   artificial size limitations on some systems.
line 344 is a new one:   On a 64-bit machine, you may be able to reduce malloc overhead by
line 345 is a new one:   defining INTERNAL_SIZE_T to be a 32 bit `unsigned int' at the
line 346 is a new one:   expense of not being able to handle more than 2^32 of malloced
line 347 is a new one:   space. If this limitation is acceptable, you are encouraged to set
line 348 is a new one:   this unless you are on a platform requiring 16byte alignments. In
line 349 is a new one:   this case the alignment requirements turn out to negate any
line 350 is a new one:   potential advantages of decreasing size_t word size.
line 352 is a new one:   Implementors: Beware of the possible combinations of:
line 353 is a new one:      - INTERNAL_SIZE_T might be signed or unsigned, might be 32 or 64 bits,
line 354 is a new one:        and might be the same width as int or as long
line 355 is a new one:      - size_t might have different width and signedness as INTERNAL_SIZE_T
line 356 is a new one:      - int and long might be 32 or 64 bits, and might be the same width
line 357 is a new one:   To deal with this, most comparisons and difference computations
line 358 is a new one:   among INTERNAL_SIZE_Ts should cast them to unsigned long, being
line 359 is a new one:   aware of the fact that casting an unsigned int to a wider long does
line 360 is a new one:   not sign-extend. (This also makes checking for negative numbers
line 361 is a new one:   awkward.) Some of these casts result in harmless compiler warnings
line 362 is a new one:   on some systems.
line 369 is a new one: /* The corresponding word size */
line 374 is a new one:   MALLOC_ALIGNMENT is the minimum alignment for malloc'ed chunks.
line 375 is a new one:   It must be a power of two at least 2 * SIZE_SZ, even on machines
line 376 is a new one:   for which smaller alignments would suffice. It may be defined as
line 377 is a new one:   larger than this though. Note however that code and data structures
line 378 is a new one:   are optimized for the case of 8-byte alignment.
line 383 is a new one: /* XXX This is the correct definition.  It differs from 2*SIZE_SZ only on
line 384 is a new one:    powerpc32.  For the time being, changing this is causing more
line 385 is a new one:    compatibility problems due to malloc_get_state/malloc_set_state than
line 386 is a new one:    will returning blocks not adequately aligned for long double objects
line 387 is a new one:    under -mlong-double-128.
line 389 is a new one: #define MALLOC_ALIGNMENT       (2 * SIZE_SZ < __alignof__ (long double) \
line 390 is a new one: 				? __alignof__ (long double) : 2 * SIZE_SZ)
line 392 is a new one: #define MALLOC_ALIGNMENT       (2 * SIZE_SZ)
line 395 is a new one: /* The corresponding bit mask value */
line 401 is a new one:   REALLOC_ZERO_BYTES_FREES should be set if a call to
line 402 is a new one:   realloc with zero bytes should be the same as a call to free.
line 403 is a new one:   This is required by the C standard. Otherwise, since this malloc
line 404 is a new one:   returns a unique pointer for malloc(0), so does realloc(p, 0).
line 407 is a new one: #ifndef REALLOC_ZERO_BYTES_FREES
line 408 is a new one: #define REALLOC_ZERO_BYTES_FREES 1
line 412 is a new one:   TRIM_FASTBINS controls whether free() of a very small chunk can
line 413 is a new one:   immediately lead to trimming. Setting to true (1) can reduce memory
line 414 is a new one:   footprint, but will almost always slow down programs that use a lot
line 415 is a new one:   of small chunks.
line 417 is a new one:   Define this only if you are willing to give up some speed to more
line 418 is a new one:   aggressively reduce system-level memory footprint when releasing
line 419 is a new one:   memory in programs that use many small chunks.  You can get
line 420 is a new one:   essentially the same effect by setting MXFAST to 0, but this can
line 421 is a new one:   lead to even greater slowdowns in programs using many small chunks.
line 422 is a new one:   TRIM_FASTBINS is an in-between compile-time option, that disables
line 423 is a new one:   only those chunks bordering topmost memory from being placed in
line 424 is a new one:   fastbins.
line 427 is a new one: #ifndef TRIM_FASTBINS
line 428 is a new one: #define TRIM_FASTBINS  0
line 433 is a new one:   USE_DL_PREFIX will prefix all public routines with the string 'dl'.
line 434 is a new one:   This is necessary when you only want to use this malloc in one part
line 435 is a new one:   of a program, using your regular system malloc elsewhere.
line 438 is a new one: /* #define USE_DL_PREFIX */
line 442 is a new one:    Two-phase name translation.
line 443 is a new one:    All of the actual routines are given mangled names.
line 444 is a new one:    When wrappers are used, they become the public callable versions.
line 445 is a new one:    When DL_PREFIX is used, the callable names are prefixed.
line 448 is a new one: #ifdef USE_DL_PREFIX
line 449 is a new one: #define public_cALLOc    dlcalloc
line 450 is a new one: #define public_fREe      dlfree
line 451 is a new one: #define public_cFREe     dlcfree
line 452 is a new one: #define public_mALLOc    dlmalloc
line 453 is a new one: #define public_mEMALIGn  dlmemalign
line 454 is a new one: #define public_rEALLOc   dlrealloc
line 455 is a new one: #define public_vALLOc    dlvalloc
line 456 is a new one: #define public_pVALLOc   dlpvalloc
line 457 is a new one: #define public_mALLINFo  dlmallinfo
line 458 is a new one: #define public_mALLOPt   dlmallopt
line 459 is a new one: #define public_mTRIm     dlmalloc_trim
line 460 is a new one: #define public_mSTATs    dlmalloc_stats
line 461 is a new one: #define public_mUSABLe   dlmalloc_usable_size
line 462 is a new one: #define public_iCALLOc   dlindependent_calloc
line 463 is a new one: #define public_iCOMALLOc dlindependent_comalloc
line 464 is a new one: #define public_gET_STATe dlget_state
line 465 is a new one: #define public_sET_STATe dlset_state
line 466 is a new one: #else /* USE_DL_PREFIX */
line 469 is a new one: /* Special defines for the GNU C library.  */
line 470 is a new one: #define public_cALLOc    __libc_calloc
line 471 is a new one: #define public_fREe      __libc_free
line 472 is a new one: #define public_cFREe     __libc_cfree
line 473 is a new one: #define public_mALLOc    __libc_malloc
line 474 is a new one: #define public_mEMALIGn  __libc_memalign
line 475 is a new one: #define public_rEALLOc   __libc_realloc
line 476 is a new one: #define public_vALLOc    __libc_valloc
line 477 is a new one: #define public_pVALLOc   __libc_pvalloc
line 478 is a new one: #define public_mALLINFo  __libc_mallinfo
line 479 is a new one: #define public_mALLOPt   __libc_mallopt
line 480 is a new one: #define public_mTRIm     __malloc_trim
line 481 is a new one: #define public_mSTATs    __malloc_stats
line 482 is a new one: #define public_mUSABLe   __malloc_usable_size
line 483 is a new one: #define public_iCALLOc   __libc_independent_calloc
line 484 is a new one: #define public_iCOMALLOc __libc_independent_comalloc
line 485 is a new one: #define public_gET_STATe __malloc_get_state
line 486 is a new one: #define public_sET_STATe __malloc_set_state
line 487 is a new one: #define malloc_getpagesize __getpagesize()
line 488 is a new one: #define open             __open
line 489 is a new one: #define mmap             __mmap
line 490 is a new one: #define munmap           __munmap
line 491 is a new one: #define mremap           __mremap
line 492 is a new one: #define mprotect         __mprotect
line 493 is a new one: #define MORECORE         (*__morecore)
line 499 is a new one: #else /* !_LIBC */
line 500 is a new one: #define public_cALLOc    calloc
line 501 is a new one: #define public_fREe      free
line 502 is a new one: #define public_cFREe     cfree
line 503 is a new one: #define public_mALLOc    malloc
line 504 is a new one: #define public_mEMALIGn  memalign
line 505 is a new one: #define public_rEALLOc   realloc
line 506 is a new one: #define public_vALLOc    valloc
line 507 is a new one: #define public_pVALLOc   pvalloc
line 508 is a new one: #define public_mALLINFo  mallinfo
line 509 is a new one: #define public_mALLOPt   mallopt
line 510 is a new one: #define public_mTRIm     malloc_trim
line 511 is a new one: #define public_mSTATs    malloc_stats
line 512 is a new one: #define public_mUSABLe   malloc_usable_size
line 513 is a new one: #define public_iCALLOc   independent_calloc
line 514 is a new one: #define public_iCOMALLOc independent_comalloc
line 515 is a new one: #define public_gET_STATe malloc_get_state
line 516 is a new one: #define public_sET_STATe malloc_set_state
line 518 is a new one: #endif /* USE_DL_PREFIX */
line 521 is a new one: #define __builtin_expect(expr, val)	(expr)
line 523 is a new one: #define fwrite(buf, size, count, fp) _IO_fwrite (buf, size, count, fp)
line 530 is a new one:   macro versions are defined below.
line 534 is a new one:   versions are faster than libc versions on some systems.
line 536 is a new one:   Even if USE_MEMCPY is set to 1, loops to copy/clear small chunks
line 537 is a new one:   (of <= 36 bytes) are manually unrolled in realloc and calloc.
line 540 is a new one: #define HAVE_MEMCPY
line 554 is a new one: # include <string.h>
line 556 is a new one: #ifdef WIN32
line 557 is a new one: /* On Win32 memset and memcpy are already declared in windows.h */
line 571 is a new one:   MALLOC_FAILURE_ACTION is the action to take before "return 0" when
line 572 is a new one:   malloc fails to be able to return memory, either because memory is
line 573 is a new one:   exhausted or because of illegal arguments.
line 575 is a new one:   By default, sets errno if running on STD_C platform, else does nothing.
line 578 is a new one: #ifndef MALLOC_FAILURE_ACTION
line 580 is a new one: #define MALLOC_FAILURE_ACTION \
line 581 is a new one:    errno = ENOMEM;
line 584 is a new one: #define MALLOC_FAILURE_ACTION
line 589 is a new one:   MORECORE-related declarations. By default, rely on sbrk
line 593 is a new one: #ifdef LACKS_UNISTD_H
line 594 is a new one: #if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__)
line 604 is a new one:   MORECORE is the name of the routine to call to obtain more memory
line 605 is a new one:   from the system.  See below for general guidance on writing
line 606 is a new one:   alternative MORECORE functions, as well as a version for WIN32 and a
line 607 is a new one:   sample version for pre-OSX macos.
line 615 is a new one:   MORECORE_FAILURE is the value returned upon failure of MORECORE
line 616 is a new one:   as well as mmap. Since it cannot be an otherwise valid memory address,
line 617 is a new one:   and must reflect values of standard sys calls, you probably ought not
line 618 is a new one:   try to redefine it.
line 622 is a new one: #define MORECORE_FAILURE (-1)
line 626 is a new one:   If MORECORE_CONTIGUOUS is true, take advantage of fact that
line 627 is a new one:   consecutive calls to MORECORE with positive arguments always return
line 628 is a new one:   contiguous increasing addresses.  This is true of unix sbrk.  Even
line 629 is a new one:   if not defined, when regions happen to be contiguous, malloc will
line 630 is a new one:   permit allocations spanning regions obtained from different
line 631 is a new one:   calls. But defining this when applicable enables some stronger
line 632 is a new one:   consistency checks and space efficiencies.
line 635 is a new one: #ifndef MORECORE_CONTIGUOUS
line 636 is a new one: #define MORECORE_CONTIGUOUS 1
line 640 is a new one:   Define MORECORE_CANNOT_TRIM if your version of MORECORE
line 641 is a new one:   cannot release space back to the system when given negative
line 642 is a new one:   arguments. This is generally necessary only if you are using
line 643 is a new one:   a hand-crafted MORECORE function that cannot handle negative arguments.
line 646 is a new one: /* #define MORECORE_CANNOT_TRIM */
line 648 is a new one: /*  MORECORE_CLEARS           (default 1)
line 663 is a new one:   Define HAVE_MMAP as true to optionally make malloc() use mmap() to
line 664 is a new one:   allocate very large blocks.  These will be returned to the
line 665 is a new one:   operating system immediately after a free(). Also, if mmap
line 666 is a new one:   is available, it is used as a backup strategy in cases where
line 667 is a new one:   MORECORE fails to provide space from system.
line 669 is a new one:   This malloc is best tuned to work with mmap for large requests.
line 670 is a new one:   If you do not have mmap, operations involving very large chunks (1MB
line 671 is a new one:   or so) may be slower than you'd like.
line 675 is a new one: #define HAVE_MMAP 1
line 678 is a new one:    Standard unix mmap using /dev/zero clears memory so calloc doesn't
line 679 is a new one:    need to.
line 682 is a new one: #ifndef MMAP_CLEARS
line 683 is a new one: #define MMAP_CLEARS 1
line 686 is a new one: #else /* no mmap */
line 687 is a new one: #ifndef MMAP_CLEARS
line 688 is a new one: #define MMAP_CLEARS 0
line 694 is a new one:    MMAP_AS_MORECORE_SIZE is the minimum mmap size argument to use if
line 695 is a new one:    sbrk fails, and mmap is used as a backup (which is done only if
line 696 is a new one:    HAVE_MMAP).  The value must be a multiple of page size.  This
line 697 is a new one:    backup strategy generally applies only when systems have "holes" in
line 698 is a new one:    address space, so sbrk cannot perform contiguous expansion, but
line 699 is a new one:    there is still space available on system.  On systems for which
line 700 is a new one:    this is known to be useful (i.e. most linux kernels), this occurs
line 701 is a new one:    only when programs allocate huge amounts of memory.  Between this,
line 702 is a new one:    and the fact that mmap regions tend to be limited, the size should
line 703 is a new one:    be large, to avoid too many mmap calls and thus avoid running out
line 704 is a new one:    of kernel resources.
line 707 is a new one: #ifndef MMAP_AS_MORECORE_SIZE
line 708 is a new one: #define MMAP_AS_MORECORE_SIZE (1024 * 1024)
line 718 is a new one: #ifdef linux
line 719 is a new one: #define HAVE_MREMAP 1
line 721 is a new one: #define HAVE_MREMAP 0
line 737 is a new one:   The system page size. To the extent possible, this malloc manages
line 738 is a new one:   memory from the system in page-size units.  Note that this value is
line 739 is a new one:   cached during initialization into a field of malloc_state. So even
line 740 is a new one:   if malloc_getpagesize is a function, it is only called once.
line 742 is a new one:   The following mechanics for getpagesize were adapted from bsd/gnu
line 743 is a new one:   getpagesize.h. If none of the system-probes here apply, a value of
line 744 is a new one:   4096 is used, which should be OK: If they don't apply, then using
line 745 is a new one:   the actual value probably doesn't impact performance.
line 768 is a new one: #      ifdef WIN32 /* use supplied emulation of getpagesize */
line 769 is a new one: #        define malloc_getpagesize getpagesize()
line 771 is a new one: #        ifndef LACKS_SYS_PARAM_H
line 772 is a new one: #          include <sys/param.h>
line 774 is a new one: #        ifdef EXEC_PAGESIZE
line 775 is a new one: #          define malloc_getpagesize EXEC_PAGESIZE
line 777 is a new one: #          ifdef NBPG
line 778 is a new one: #            ifndef CLSIZE
line 779 is a new one: #              define malloc_getpagesize NBPG
line 781 is a new one: #              define malloc_getpagesize (NBPG * CLSIZE)
line 784 is a new one: #            ifdef NBPC
line 785 is a new one: #              define malloc_getpagesize NBPC
line 787 is a new one: #              ifdef PAGESIZE
line 788 is a new one: #                define malloc_getpagesize PAGESIZE
line 789 is a new one: #              else /* just guess */
line 790 is a new one: #                define malloc_getpagesize (4096)
line 791 is a new one: #              endif
line 802 is a new one:   routine that returns a struct containing usage properties and
line 803 is a new one:   statistics. It should work on any SVID/XPG compliant system that has
line 804 is a new one:   a /usr/include/malloc.h defining struct mallinfo. (If you'd like to
line 805 is a new one:   install such a thing yourself, cut out the preliminary declarations
line 806 is a new one:   as described above and below and save them in a malloc.h file. But
line 807 is a new one:   there's no compelling reason to bother to do this.)
line 811 is a new one:   bunch of fields that are not even meaningful in this version of
line 812 is a new one:   malloc.  These fields are are instead filled by mallinfo() with
line 813 is a new one:   other numbers that might be of interest.
line 819 is a new one:   mallinfo() to work.  The original SVID version of this struct,
line 820 is a new one:   defined on most systems with mallinfo, declares all fields as
line 821 is a new one:   ints. But some others define as unsigned long. If your system
line 822 is a new one:   defines the fields using a type of different width than listed here,
line 823 is a new one:   you must #include your system version and #define
line 824 is a new one:   HAVE_USR_INCLUDE_MALLOC_H.
line 829 is a new one: #ifdef HAVE_USR_INCLUDE_MALLOC_H
line 830 is a new one: #include "/usr/include/malloc.h"
line 834 is a new one: /* ---------- description of public routines ------------ */
line 837 is a new one:   malloc(size_t n)
line 838 is a new one:   Returns a pointer to a newly allocated chunk of at least n bytes, or null
line 839 is a new one:   if no space is available. Additionally, on failure, errno is
line 840 is a new one:   set to ENOMEM on ANSI C systems.
line 842 is a new one:   If n is zero, malloc returns a minumum-sized chunk. (The minimum
line 843 is a new one:   size is 16 bytes on most 32bit systems, and 24 or 32 bytes on 64bit
line 844 is a new one:   systems.)  On most systems, size_t is an unsigned type, so calls
line 845 is a new one:   with negative arguments are interpreted as requests for huge amounts
line 846 is a new one:   of space, which will often fail. The maximum supported value of n
line 847 is a new one:   differs across systems, but is in all cases less than the maximum
line 848 is a new one:   representable value of a size_t.
line 851 is a new one: Void_t*  public_mALLOc(size_t);
line 853 is a new one: Void_t*  public_mALLOc();
line 855 is a new one: #ifdef libc_hidden_proto
line 856 is a new one: libc_hidden_proto (public_mALLOc)
line 860 is a new one:   free(Void_t* p)
line 861 is a new one:   Releases the chunk of memory pointed to by p, that had been previously
line 862 is a new one:   allocated using malloc or a related routine such as realloc.
line 863 is a new one:   It has no effect if p is null. It can have arbitrary (i.e., bad!)
line 864 is a new one:   effects if p has already been freed.
line 866 is a new one:   Unless disabled (using mallopt), freeing very large spaces will
line 867 is a new one:   when possible, automatically trigger operations that give
line 868 is a new one:   back unused memory to the system, thus reducing program footprint.
line 871 is a new one: void     public_fREe(Void_t*);
line 873 is a new one: void     public_fREe();
line 875 is a new one: #ifdef libc_hidden_proto
line 876 is a new one: libc_hidden_proto (public_fREe)
line 880 is a new one:   calloc(size_t n_elements, size_t element_size);
line 881 is a new one:   Returns a pointer to n_elements * element_size bytes, with all locations
line 882 is a new one:   set to zero.
line 885 is a new one: Void_t*  public_cALLOc(size_t, size_t);
line 887 is a new one: Void_t*  public_cALLOc();
line 891 is a new one:   realloc(Void_t* p, size_t n)
line 892 is a new one:   Returns a pointer to a chunk of size n that contains the same data
line 893 is a new one:   as does chunk p up to the minimum of (n, p's size) bytes, or null
line 894 is a new one:   if no space is available.
line 896 is a new one:   The returned pointer may or may not be the same as p. The algorithm
line 897 is a new one:   prefers extending p when possible, otherwise it employs the
line 898 is a new one:   equivalent of a malloc-copy-free sequence.
line 900 is a new one:   If p is null, realloc is equivalent to malloc.
line 902 is a new one:   If space is not available, realloc returns null, errno is set (if on
line 903 is a new one:   ANSI) and p is NOT freed.
line 905 is a new one:   if n is for fewer bytes than already held by p, the newly unused
line 906 is a new one:   space is lopped off and freed if possible.  Unless the #define
line 907 is a new one:   REALLOC_ZERO_BYTES_FREES is set, realloc with a size argument of
line 908 is a new one:   zero (re)allocates a minimum-sized chunk.
line 910 is a new one:   Large chunks that were internally obtained via mmap will always
line 911 is a new one:   be reallocated using malloc-copy-free sequences unless
line 912 is a new one:   the system supports MREMAP (currently only linux).
line 914 is a new one:   The old unix realloc convention of allowing the last-free'd chunk
line 915 is a new one:   to be used as an argument to realloc is not supported.
line 918 is a new one: Void_t*  public_rEALLOc(Void_t*, size_t);
line 920 is a new one: Void_t*  public_rEALLOc();
line 922 is a new one: #ifdef libc_hidden_proto
line 923 is a new one: libc_hidden_proto (public_rEALLOc)
line 928 is a new one:   Returns a pointer to a newly allocated chunk of n bytes, aligned
line 929 is a new one:   in accord with the alignment argument.
line 931 is a new one:   The alignment argument should be a power of two. If the argument is
line 932 is a new one:   not a power of two, the nearest greater power is used.
line 933 is a new one:   8-byte alignment is guaranteed by normal malloc calls, so don't
line 934 is a new one:   bother calling memalign with an argument of 8 or less.
line 936 is a new one:   Overreliance on memalign is a sure way to fragment space.
line 939 is a new one: Void_t*  public_mEMALIGn(size_t, size_t);
line 941 is a new one: Void_t*  public_mEMALIGn();
line 943 is a new one: #ifdef libc_hidden_proto
line 944 is a new one: libc_hidden_proto (public_mEMALIGn)
line 949 is a new one:   Equivalent to memalign(pagesize, n), where pagesize is the page
line 950 is a new one:   size of the system. If the pagesize is unknown, 4096 is used.
line 953 is a new one: Void_t*  public_vALLOc(size_t);
line 955 is a new one: Void_t*  public_vALLOc();
line 962 is a new one:   Sets tunable parameters The format is to provide a
line 963 is a new one:   (parameter-number, parameter-value) pair.  mallopt then sets the
line 964 is a new one:   corresponding parameter to the argument value if it can (i.e., so
line 965 is a new one:   long as the value is meaningful), and returns 1 if successful else
line 966 is a new one:   0.  SVID/XPG/ANSI defines four standard param numbers for mallopt,
line 967 is a new one:   normally defined in malloc.h.  Only one of these (M_MXFAST) is used
line 968 is a new one:   in this malloc. The others (M_NLBLKS, M_GRAIN, M_KEEP) don't apply,
line 969 is a new one:   so setting them has no effect. But this malloc also supports four
line 970 is a new one:   other options in mallopt. See below for details.  Briefly, supported
line 971 is a new one:   parameters are as follows (listed defaults are for "typical"
line 972 is a new one:   configurations).
line 974 is a new one:   Symbol            param #   default    allowed param values
line 975 is a new one:   M_MXFAST          1         64         0-80  (0 disables fastbins)
line 976 is a new one:   M_TRIM_THRESHOLD -1         128*1024   any   (-1U disables trimming)
line 977 is a new one:   M_TOP_PAD        -2         0          any
line 978 is a new one:   M_MMAP_THRESHOLD -3         128*1024   any   (or 0 if no MMAP support)
line 979 is a new one:   M_MMAP_MAX       -4         65536      any   (0 disables use of mmap)
line 982 is a new one: int      public_mALLOPt(int, int);
line 984 is a new one: int      public_mALLOPt();
line 990 is a new one:   Returns (by copy) a struct containing various summary statistics:
line 992 is a new one:   arena:     current total non-mmapped bytes allocated from system
line 993 is a new one:   ordblks:   the number of free chunks
line 994 is a new one:   smblks:    the number of fastbin blocks (i.e., small chunks that
line 995 is a new one:                have been freed but not use resused or consolidated)
line 996 is a new one:   hblks:     current number of mmapped regions
line 997 is a new one:   hblkhd:    total bytes held in mmapped regions
line 998 is a new one:   usmblks:   the maximum total allocated space. This will be greater
line 999 is a new one:                 than current total if trimming has occurred.
line 1000 is a new one:   fsmblks:   total bytes held in fastbin blocks
line 1001 is a new one:   uordblks:  current total allocated space (normal or mmapped)
line 1002 is a new one:   fordblks:  total free space
line 1003 is a new one:   keepcost:  the maximum number of bytes that could ideally be released
line 1004 is a new one:                back to system via malloc_trim. ("ideally" means that
line 1005 is a new one:                it ignores page restrictions etc.)
line 1007 is a new one:   Because these fields are ints, but internal bookkeeping may
line 1008 is a new one:   be kept as longs, the reported values may wrap around zero and
line 1009 is a new one:   thus be inaccurate.
line 1012 is a new one: struct mallinfo public_mALLINFo(void);
line 1014 is a new one: struct mallinfo public_mALLINFo();
line 1019 is a new one:   independent_calloc(size_t n_elements, size_t element_size, Void_t* chunks[]);
line 1021 is a new one:   independent_calloc is similar to calloc, but instead of returning a
line 1022 is a new one:   single cleared space, it returns an array of pointers to n_elements
line 1023 is a new one:   independent elements that can hold contents of size elem_size, each
line 1024 is a new one:   of which starts out cleared, and can be independently freed,
line 1025 is a new one:   realloc'ed etc. The elements are guaranteed to be adjacently
line 1026 is a new one:   allocated (this is not guaranteed to occur with multiple callocs or
line 1027 is a new one:   mallocs), which may also improve cache locality in some
line 1028 is a new one:   applications.
line 1030 is a new one:   The "chunks" argument is optional (i.e., may be null, which is
line 1031 is a new one:   probably the most typical usage). If it is null, the returned array
line 1032 is a new one:   is itself dynamically allocated and should also be freed when it is
line 1033 is a new one:   no longer needed. Otherwise, the chunks array must be of at least
line 1034 is a new one:   n_elements in length. It is filled in with the pointers to the
line 1035 is a new one:   chunks.
line 1037 is a new one:   In either case, independent_calloc returns this pointer array, or
line 1038 is a new one:   null if the allocation failed.  If n_elements is zero and "chunks"
line 1039 is a new one:   is null, it returns a chunk representing an array with zero elements
line 1040 is a new one:   (which should be freed if not wanted).
line 1042 is a new one:   Each element must be individually freed when it is no longer
line 1043 is a new one:   needed. If you'd like to instead be able to free all at once, you
line 1044 is a new one:   should instead use regular calloc and assign pointers into this
line 1045 is a new one:   space to represent elements.  (In this case though, you cannot
line 1046 is a new one:   independently free elements.)
line 1048 is a new one:   independent_calloc simplifies and speeds up implementations of many
line 1049 is a new one:   kinds of pools.  It may also be useful when constructing large data
line 1050 is a new one:   structures that initially have a fixed number of fixed-sized nodes,
line 1051 is a new one:   but the number is not known at compile time, and some of the nodes
line 1052 is a new one:   may later need to be freed. For example:
line 1054 is a new one:   struct Node { int item; struct Node* next; };
line 1056 is a new one:   struct Node* build_list() {
line 1057 is a new one:     struct Node** pool;
line 1058 is a new one:     int n = read_number_of_nodes_needed();
line 1059 is a new one:     if (n <= 0) return 0;
line 1060 is a new one:     pool = (struct Node**)(independent_calloc(n, sizeof(struct Node), 0);
line 1061 is a new one:     if (pool == 0) die();
line 1062 is a new one:     // organize into a linked list...
line 1063 is a new one:     struct Node* first = pool[0];
line 1064 is a new one:     for (i = 0; i < n-1; ++i)
line 1065 is a new one:       pool[i]->next = pool[i+1];
line 1066 is a new one:     free(pool);     // Can now free the array (or not, if it is needed later)
line 1067 is a new one:     return first;
line 1071 is a new one: Void_t** public_iCALLOc(size_t, size_t, Void_t**);
line 1073 is a new one: Void_t** public_iCALLOc();
line 1077 is a new one:   independent_comalloc(size_t n_elements, size_t sizes[], Void_t* chunks[]);
line 1079 is a new one:   independent_comalloc allocates, all at once, a set of n_elements
line 1080 is a new one:   chunks with sizes indicated in the "sizes" array.    It returns
line 1081 is a new one:   an array of pointers to these elements, each of which can be
line 1082 is a new one:   independently freed, realloc'ed etc. The elements are guaranteed to
line 1083 is a new one:   be adjacently allocated (this is not guaranteed to occur with
line 1084 is a new one:   multiple callocs or mallocs), which may also improve cache locality
line 1085 is a new one:   in some applications.
line 1087 is a new one:   The "chunks" argument is optional (i.e., may be null). If it is null
line 1088 is a new one:   the returned array is itself dynamically allocated and should also
line 1089 is a new one:   be freed when it is no longer needed. Otherwise, the chunks array
line 1090 is a new one:   must be of at least n_elements in length. It is filled in with the
line 1091 is a new one:   pointers to the chunks.
line 1093 is a new one:   In either case, independent_comalloc returns this pointer array, or
line 1094 is a new one:   null if the allocation failed.  If n_elements is zero and chunks is
line 1095 is a new one:   null, it returns a chunk representing an array with zero elements
line 1096 is a new one:   (which should be freed if not wanted).
line 1098 is a new one:   Each element must be individually freed when it is no longer
line 1099 is a new one:   needed. If you'd like to instead be able to free all at once, you
line 1100 is a new one:   should instead use a single regular malloc, and assign pointers at
line 1101 is a new one:   particular offsets in the aggregate space. (In this case though, you
line 1102 is a new one:   cannot independently free elements.)
line 1104 is a new one:   independent_comallac differs from independent_calloc in that each
line 1105 is a new one:   element may have a different size, and also that it does not
line 1106 is a new one:   automatically clear elements.
line 1108 is a new one:   independent_comalloc can be used to speed up allocation in cases
line 1109 is a new one:   where several structs or objects must always be allocated at the
line 1110 is a new one:   same time.  For example:
line 1112 is a new one:   struct Head { ... }
line 1113 is a new one:   struct Foot { ... }
line 1115 is a new one:   void send_message(char* msg) {
line 1116 is a new one:     int msglen = strlen(msg);
line 1117 is a new one:     size_t sizes[3] = { sizeof(struct Head), msglen, sizeof(struct Foot) };
line 1118 is a new one:     void* chunks[3];
line 1119 is a new one:     if (independent_comalloc(3, sizes, chunks) == 0)
line 1120 is a new one:       die();
line 1121 is a new one:     struct Head* head = (struct Head*)(chunks[0]);
line 1122 is a new one:     char*        body = (char*)(chunks[1]);
line 1123 is a new one:     struct Foot* foot = (struct Foot*)(chunks[2]);
line 1124 is a new one:     // ...
line 1127 is a new one:   In general though, independent_comalloc is worth using only for
line 1128 is a new one:   larger values of n_elements. For small values, you probably won't
line 1129 is a new one:   detect enough difference from series of malloc calls to bother.
line 1131 is a new one:   Overuse of independent_comalloc can increase overall memory usage,
line 1132 is a new one:   since it cannot reuse existing noncontiguous small chunks that
line 1133 is a new one:   might be available for some of the elements.
line 1136 is a new one: Void_t** public_iCOMALLOc(size_t, size_t*, Void_t**);
line 1138 is a new one: Void_t** public_iCOMALLOc();
line 1146 is a new one:   Equivalent to valloc(minimum-page-that-holds(n)), that is,
line 1147 is a new one:   round up n to nearest pagesize.
line 1148 is a new one:  */
line 1150 is a new one: Void_t*  public_pVALLOc(size_t);
line 1152 is a new one: Void_t*  public_pVALLOc();
line 1157 is a new one:   Equivalent to free(p).
line 1159 is a new one:   cfree is needed/defined on some systems that pair it with calloc,
line 1160 is a new one:   for odd historical reasons (such as: cfree is used in example
line 1161 is a new one:   code in the first edition of K&R).
line 1164 is a new one: void     public_cFREe(Void_t*);
line 1166 is a new one: void     public_cFREe();
line 1172 is a new one:   If possible, gives memory back to the system (via negative
line 1173 is a new one:   arguments to sbrk) if there is unused memory at the `high' end of
line 1174 is a new one:   the malloc pool. You can call this after freeing large blocks of
line 1175 is a new one:   memory to potentially reduce the system-level memory requirements
line 1176 is a new one:   of a program. However, it cannot guarantee to reduce memory. Under
line 1177 is a new one:   some allocation patterns, some large free blocks of memory will be
line 1178 is a new one:   locked between two used chunks, so they cannot be given back to
line 1179 is a new one:   the system.
line 1181 is a new one:   The `pad' argument to malloc_trim represents the amount of free
line 1182 is a new one:   trailing space to leave untrimmed. If this argument is zero,
line 1183 is a new one:   only the minimum amount of memory to maintain internal data
line 1184 is a new one:   structures will be left (one page or less). Non-zero arguments
line 1185 is a new one:   can be supplied to maintain enough trailing space to service
line 1186 is a new one:   future expected allocations without having to re-obtain memory
line 1187 is a new one:   from the system.
line 1189 is a new one:   Malloc_trim returns 1 if it actually released any memory, else 0.
line 1190 is a new one:   On systems that do not support "negative sbrks", it will always
line 1191 is a new one:   rreturn 0.
line 1194 is a new one: int      public_mTRIm(size_t);
line 1196 is a new one: int      public_mTRIm();
line 1202 is a new one:   Returns the number of bytes you can actually use in
line 1203 is a new one:   an allocated chunk, which may be more than you requested (although
line 1204 is a new one:   often not) due to alignment and minimum size constraints.
line 1205 is a new one:   You can use this many bytes without worrying about
line 1206 is a new one:   overwriting other allocated objects. This is not a particularly great
line 1207 is a new one:   programming practice. malloc_usable_size can be more useful in
line 1208 is a new one:   debugging and assertions, for example:
line 1210 is a new one:   p = malloc(n);
line 1211 is a new one:   assert(malloc_usable_size(p) >= 256);
line 1215 is a new one: size_t   public_mUSABLe(Void_t*);
line 1217 is a new one: size_t   public_mUSABLe();
line 1222 is a new one:   Prints on stderr the amount of space obtained from the system (both
line 1223 is a new one:   via sbrk and mmap), the maximum amount (which may be more than
line 1224 is a new one:   current if malloc_trim and/or munmap got called), and the current
line 1225 is a new one:   number of bytes allocated via malloc (or realloc, etc) but not yet
line 1226 is a new one:   freed. Note that this is the number of bytes allocated, not the
line 1227 is a new one:   number requested. It will be larger than the number requested
line 1228 is a new one:   because of alignment and bookkeeping overhead. Because it includes
line 1229 is a new one:   alignment wastage as being in use, this figure may be greater than
line 1230 is a new one:   zero even when no user-level chunks are allocated.
line 1232 is a new one:   The reported current and maximum system memory can be inaccurate if
line 1233 is a new one:   a program makes other calls to system memory allocation functions
line 1234 is a new one:   (normally sbrk) outside of malloc.
line 1236 is a new one:   malloc_stats prints only the most commonly interesting statistics.
line 1237 is a new one:   More information can be obtained by calling mallinfo.
line 1241 is a new one: void     public_mSTATs(void);
line 1243 is a new one: void     public_mSTATs();
line 1247 is a new one:   malloc_get_state(void);
line 1249 is a new one:   Returns the state of all malloc variables in an opaque data
line 1250 is a new one:   structure.
line 1253 is a new one: Void_t*  public_gET_STATe(void);
line 1255 is a new one: Void_t*  public_gET_STATe();
line 1259 is a new one:   malloc_set_state(Void_t* state);
line 1261 is a new one:   Restore the state of all malloc variables from data obtained with
line 1262 is a new one:   malloc_get_state().
line 1265 is a new one: int      public_sET_STATe(Void_t*);
line 1267 is a new one: int      public_sET_STATe();
line 1272 is a new one:   posix_memalign(void **memptr, size_t alignment, size_t size);
line 1274 is a new one:   POSIX wrapper like memalign(), checking for validity of size.
line 1276 is a new one: int      __posix_memalign(void **, size_t, size_t);
line 1279 is a new one: /* mallopt tuning options */
line 1282 is a new one:   M_MXFAST is the maximum request size used for "fastbins", special bins
line 1283 is a new one:   that hold returned chunks without consolidating their spaces. This
line 1284 is a new one:   enables future requests for chunks of the same size to be handled
line 1285 is a new one:   very quickly, but can increase fragmentation, and thus increase the
line 1286 is a new one:   overall memory footprint of a program.
line 1288 is a new one:   This malloc manages fastbins very conservatively yet still
line 1289 is a new one:   efficiently, so fragmentation is rarely a problem for values less
line 1290 is a new one:   than or equal to the default.  The maximum supported value of MXFAST
line 1291 is a new one:   is 80. You wouldn't want it any higher than this anyway.  Fastbins
line 1292 is a new one:   are designed especially for use with many small structs, objects or
line 1293 is a new one:   strings -- the default handles structs/objects/arrays with sizes up
line 1294 is a new one:   to 8 4byte fields, or small strings representing words, tokens,
line 1295 is a new one:   etc. Using fastbins for larger objects normally worsens
line 1296 is a new one:   fragmentation without improving speed.
line 1298 is a new one:   M_MXFAST is set in REQUEST size units. It is internally used in
line 1299 is a new one:   chunksize units, which adds padding and alignment.  You can reduce
line 1300 is a new one:   M_MXFAST to 0 to disable all use of fastbins.  This causes the malloc
line 1301 is a new one:   algorithm to be a closer approximation of fifo-best-fit in all cases,
line 1302 is a new one:   not just for larger requests, but will generally cause it to be
line 1303 is a new one:   slower.
line 1307 is a new one: /* M_MXFAST is a standard SVID/XPG tuning option, usually listed in malloc.h */
line 1308 is a new one: #ifndef M_MXFAST
line 1309 is a new one: #define M_MXFAST            1
line 1312 is a new one: #ifndef DEFAULT_MXFAST
line 1313 is a new one: #define DEFAULT_MXFAST     64
line 1318 is a new one:   M_TRIM_THRESHOLD is the maximum amount of unused top-most memory
line 1319 is a new one:   to keep before releasing via malloc_trim in free().
line 1321 is a new one:   Automatic trimming is mainly useful in long-lived programs.
line 1322 is a new one:   Because trimming via sbrk can be slow on some systems, and can
line 1323 is a new one:   sometimes be wasteful (in cases where programs immediately
line 1324 is a new one:   afterward allocate more large chunks) the value should be high
line 1325 is a new one:   enough so that your overall system performance would improve by
line 1326 is a new one:   releasing this much memory.
line 1328 is a new one:   The trim threshold and the mmap control parameters (see below)
line 1329 is a new one:   can be traded off with one another. Trimming and mmapping are
line 1330 is a new one:   two different ways of releasing unused memory back to the
line 1331 is a new one:   system. Between these two, it is often possible to keep
line 1332 is a new one:   system-level demands of a long-lived program down to a bare
line 1333 is a new one:   minimum. For example, in one test suite of sessions measuring
line 1334 is a new one:   the XF86 X server on Linux, using a trim threshold of 128K and a
line 1335 is a new one:   mmap threshold of 192K led to near-minimal long term resource
line 1336 is a new one:   consumption.
line 1338 is a new one:   If you are using this malloc in a long-lived program, it should
line 1339 is a new one:   pay to experiment with these values.  As a rough guide, you
line 1340 is a new one:   might set to a value close to the average size of a process
line 1341 is a new one:   (program) running on your system.  Releasing this much memory
line 1342 is a new one:   would allow such a process to run in memory.  Generally, it's
line 1343 is a new one:   worth it to tune for trimming rather tham memory mapping when a
line 1344 is a new one:   program undergoes phases where several large chunks are
line 1345 is a new one:   allocated and released in ways that can reuse each other's
line 1346 is a new one:   storage, perhaps mixed with phases where there are no such
line 1347 is a new one:   chunks at all.  And in well-behaved long-lived programs,
line 1348 is a new one:   controlling release of large blocks via trimming versus mapping
line 1349 is a new one:   is usually faster.
line 1351 is a new one:   However, in most programs, these parameters serve mainly as
line 1352 is a new one:   protection against the system-level effects of carrying around
line 1353 is a new one:   massive amounts of unneeded memory. Since frequent calls to
line 1354 is a new one:   sbrk, mmap, and munmap otherwise degrade performance, the default
line 1355 is a new one:   parameters are set to relatively high values that serve only as
line 1356 is a new one:   safeguards.
line 1358 is a new one:   The trim value It must be greater than page size to have any useful
line 1359 is a new one:   effect.  To disable trimming completely, you can set to
line 1360 is a new one:   (unsigned long)(-1)
line 1362 is a new one:   Trim settings interact with fastbin (MXFAST) settings: Unless
line 1363 is a new one:   TRIM_FASTBINS is defined, automatic trimming never takes place upon
line 1364 is a new one:   freeing a chunk with size less than or equal to MXFAST. Trimming is
line 1365 is a new one:   instead delayed until subsequent freeing of larger chunks. However,
line 1366 is a new one:   you can still force an attempted trim by calling malloc_trim.
line 1368 is a new one:   Also, trimming is not generally possible in cases where
line 1369 is a new one:   the main arena is obtained via mmap.
line 1371 is a new one:   Note that the trick some people use of mallocing a huge space and
line 1372 is a new one:   then freeing it at program startup, in an attempt to reserve system
line 1373 is a new one:   memory, doesn't have the intended effect under automatic trimming,
line 1374 is a new one:   since that memory will immediately be returned to the system.
line 1377 is a new one: #define M_TRIM_THRESHOLD       -1
line 1384 is a new one:   M_TOP_PAD is the amount of extra `padding' space to allocate or
line 1385 is a new one:   retain whenever sbrk is called. It is used in two ways internally:
line 1387 is a new one:   * When sbrk is called to extend the top of the arena to satisfy
line 1388 is a new one:   a new malloc request, this much padding is added to the sbrk
line 1389 is a new one:   request.
line 1391 is a new one:   * When malloc_trim is called automatically from free(),
line 1392 is a new one:   it is used as the `pad' argument.
line 1394 is a new one:   In both cases, the actual amount of padding is rounded
line 1395 is a new one:   so that the end of the arena is always a system page boundary.
line 1397 is a new one:   The main reason for using padding is to avoid calling sbrk so
line 1398 is a new one:   often. Having even a small pad greatly reduces the likelihood
line 1399 is a new one:   that nearly every malloc request during program start-up (or
line 1400 is a new one:   after trimming) will invoke sbrk, which needlessly wastes
line 1401 is a new one:   time.
line 1403 is a new one:   Automatic rounding-up to page-size units is normally sufficient
line 1404 is a new one:   to avoid measurable overhead, so the default is 0.  However, in
line 1405 is a new one:   systems where sbrk is relatively slow, it can pay to increase
line 1406 is a new one:   this value, at the expense of carrying around more memory than
line 1407 is a new one:   the program needs.
line 1410 is a new one: #define M_TOP_PAD              -2
line 1417 is a new one:   M_MMAP_THRESHOLD is the request size threshold for using mmap()
line 1418 is a new one:   to service a request. Requests of at least this size that cannot
line 1419 is a new one:   be allocated using already-existing space will be serviced via mmap.
line 1420 is a new one:   (If enough normal freed space already exists it is used instead.)
line 1422 is a new one:   Using mmap segregates relatively large chunks of memory so that
line 1423 is a new one:   they can be individually obtained and released from the host
line 1424 is a new one:   system. A request serviced through mmap is never reused by any
line 1425 is a new one:   other request (at least not directly; the system may just so
line 1426 is a new one:   happen to remap successive requests to the same locations).
line 1428 is a new one:   Segregating space in this way has the benefits that:
line 1430 is a new one:    1. Mmapped space can ALWAYS be individually released back
line 1431 is a new one:       to the system, which helps keep the system level memory
line 1432 is a new one:       demands of a long-lived program low.
line 1433 is a new one:    2. Mapped memory can never become `locked' between
line 1435 is a new one:       means that even trimming via malloc_trim would not release them.
line 1436 is a new one:    3. On some systems with "holes" in address spaces, mmap can obtain
line 1437 is a new one:       memory that sbrk cannot.
line 1439 is a new one:   However, it has the disadvantages that:
line 1441 is a new one:    1. The space cannot be reclaimed, consolidated, and then
line 1442 is a new one:       used to service later requests, as happens with normal chunks.
line 1443 is a new one:    2. It can lead to more wastage because of mmap page alignment
line 1444 is a new one:       requirements
line 1445 is a new one:    3. It causes malloc performance to be more dependent on host
line 1446 is a new one:       system memory management support routines which may vary in
line 1447 is a new one:       implementation quality and may impose arbitrary
line 1448 is a new one:       limitations. Generally, servicing a request via normal
line 1449 is a new one:       malloc steps is faster than going through a system's mmap.
line 1451 is a new one:   The advantages of mmap nearly always outweigh disadvantages for
line 1452 is a new one:   "large" chunks, but the value of "large" varies across systems.  The
line 1453 is a new one:   default is an empirically derived value that works well in most
line 1454 is a new one:   systems.
line 1457 is a new one: #define M_MMAP_THRESHOLD      -3
line 1464 is a new one:   M_MMAP_MAX is the maximum number of requests to simultaneously
line 1465 is a new one:   service using mmap. This parameter exists because
line 1466 is a new one:   some systems have a limited number of internal tables for
line 1467 is a new one:   use by mmap, and using more than a few of them may degrade
line 1468 is a new one:   performance.
line 1470 is a new one:   The default is set to a value that serves only as a safeguard.
line 1471 is a new one:   Setting to 0 disables use of mmap for servicing large requests.  If
line 1472 is a new one:   HAVE_MMAP is not set, the default value is 0, and attempts to set it
line 1473 is a new one:   to non-zero values in mallopt will fail.
line 1476 is a new one: #define M_MMAP_MAX             -4
line 1480 is a new one: #define DEFAULT_MMAP_MAX       (65536)
line 1490 is a new one: #include <malloc.h>
line 1492 is a new one: #ifndef BOUNDED_N
line 1493 is a new one: #define BOUNDED_N(ptr, sz) (ptr)
line 1495 is a new one: #ifndef RETURN_ADDRESS
line 1496 is a new one: #define RETURN_ADDRESS(X_) (NULL)
line 1506 is a new one: /* Forward declarations.  */
line 1507 is a new one: struct malloc_chunk;
line 1510 is a new one: /* Internal routines.  */
line 1514 is a new one: Void_t*         _int_malloc(mstate, size_t);
line 1515 is a new one: void            _int_free(mstate, Void_t*);
line 1516 is a new one: Void_t*         _int_realloc(mstate, Void_t*, size_t);
line 1517 is a new one: Void_t*         _int_memalign(mstate, size_t, size_t);
line 1518 is a new one: Void_t*         _int_valloc(mstate, size_t);
line 1519 is a new one: static Void_t*  _int_pvalloc(mstate, size_t);
line 1520 is a new one: /*static Void_t*  cALLOc(size_t, size_t);*/
line 1522 is a new one: static Void_t** _int_icalloc(mstate, size_t, size_t, Void_t**);
line 1523 is a new one: static Void_t** _int_icomalloc(mstate, size_t, size_t*, Void_t**);
line 1525 is a new one: static int      mTRIm(size_t);
line 1526 is a new one: static size_t   mUSABLe(Void_t*);
line 1527 is a new one: static void     mSTATs(void);
line 1528 is a new one: static int      mALLOPt(int, int);
line 1529 is a new one: static struct mallinfo mALLINFo(mstate);
line 1530 is a new one: static void malloc_printerr(int action, const char *str, void *ptr);
line 1532 is a new one: static Void_t* internal_function mem2mem_check(Void_t *p, size_t sz);
line 1533 is a new one: static int internal_function top_check(void);
line 1534 is a new one: static void internal_function munmap_chunk(mchunkptr p);
line 1536 is a new one: static mchunkptr internal_function mremap_chunk(mchunkptr p, size_t new_size);
line 1547 is a new one: #  if USE___THREAD || (defined USE_TLS && !defined SHARED)
line 1548 is a new one:     /* These routines are never needed in this configuration.  */
line 1549 is a new one: #   define NO_STARTER
line 1552 is a new one: # ifdef NO_STARTER
line 1553 is a new one: #  undef NO_STARTER
line 1556 is a new one: static Void_t*   memalign_starter(size_t aln, size_t sz, const Void_t *caller);
line 1565 is a new one: Void_t*         _int_malloc();
line 1566 is a new one: void            _int_free();
line 1567 is a new one: Void_t*         _int_realloc();
line 1568 is a new one: Void_t*         _int_memalign();
line 1569 is a new one: Void_t*         _int_valloc();
line 1570 is a new one: Void_t*         _int_pvalloc();
line 1571 is a new one: /*static Void_t*  cALLOc();*/
line 1572 is a new one: static Void_t** _int_icalloc();
line 1573 is a new one: static Void_t** _int_icomalloc();
line 1574 is a new one: static int      mTRIm();
line 1575 is a new one: static size_t   mUSABLe();
line 1576 is a new one: static void     mSTATs();
line 1577 is a new one: static int      mALLOPt();
line 1578 is a new one: static struct mallinfo mALLINFo();
line 1585 is a new one: /* ------------- Optional versions of memcopy ---------------- */
line 1591 is a new one:   Note: memcpy is ONLY invoked with non-overlapping regions,
line 1592 is a new one:   so the (usually slower) memmove is not needed.
line 1595 is a new one: #define MALLOC_COPY(dest, src, nbytes)  memcpy(dest, src, nbytes)
line 1596 is a new one: #define MALLOC_ZERO(dest, nbytes)       memset(dest, 0,   nbytes)
line 1605 is a new one:   unsigned long mctmp = (nbytes)/sizeof(INTERNAL_SIZE_T);                     \
line 1606 is a new one:   long mcn;                                                                   \
line 1620 is a new one: #define MALLOC_COPY(dest,src,nbytes)                                          \
line 1624 is a new one:   unsigned long mctmp = (nbytes)/sizeof(INTERNAL_SIZE_T);                     \
line 1625 is a new one:   long mcn;                                                                   \
line 1641 is a new one: /* ------------------ MMAP support ------------------  */
line 1647 is a new one: #ifndef LACKS_SYS_MMAN_H
line 1652 is a new one: # define MAP_ANONYMOUS MAP_ANON
line 1655 is a new one: # define MAP_FAILED ((char*)-1)
line 1667 is a new one:    Nearly all versions of mmap support MAP_ANONYMOUS,
line 1668 is a new one:    so the following is unlikely to be needed, but is
line 1669 is a new one:    supplied just in case.
line 1693 is a new one:   -----------------------  Chunk representations -----------------------
line 1698 is a new one:   This struct declaration is misleading (but accurate and necessary).
line 1699 is a new one:   It declares a "view" into memory allowing access to necessary
line 1700 is a new one:   fields at known offsets from a given base. See explanation below.
line 1703 is a new one: struct malloc_chunk {
line 1705 is a new one:   INTERNAL_SIZE_T      prev_size;  /* Size of previous chunk (if free).  */
line 1706 is a new one:   INTERNAL_SIZE_T      size;       /* Size in bytes, including overhead. */
line 1708 is a new one:   struct malloc_chunk* fd;         /* double links -- used only if free. */
line 1733 is a new one:             |             Size of chunk, in bytes                       |M|P|
line 1737 is a new one:             .             (malloc_usable_size() bytes)                      .
line 1748 is a new one:     Chunks always begin on even word boundries, so the mem portion
line 1750 is a new one:     thus at least double-word aligned.
line 1775 is a new one:     The very first chunk allocated always has this bit set,
line 1776 is a new one:     preventing access to non-existent (or non-owned) memory. If
line 1777 is a new one:     prev_inuse is set for any given chunk, then you CANNOT determine
line 1778 is a new one:     the size of the previous chunk, and might even get a memory
line 1779 is a new one:     addressing fault when trying to do so.
line 1782 is a new one:     as the prev_size of the NEXT chunk. This makes it easier to
line 1783 is a new one:     deal with alignments etc but can be very confusing when trying
line 1784 is a new one:     to extend or adapt this code.
line 1788 is a new one:      1. The special chunk `top' doesn't bother using the
line 1789 is a new one:         trailing size field since there is no next contiguous chunk
line 1790 is a new one:         that would have to index off it. After initialization, `top'
line 1791 is a new one:         is forced to always exist.  If it would become less than
line 1792 is a new one:         MINSIZE bytes long, it is replenished.
line 1795 is a new one:         bit M (IS_MMAPPED) set in their size fields.  Because they are
line 1796 is a new one:         allocated one-by-one, each must contain its own trailing size field.
line 1801 is a new one:   ---------- Size and alignment checks and conversions ----------
line 1806 is a new one: #define chunk2mem(p)   ((Void_t*)((char*)(p) + 2*SIZE_SZ))
line 1807 is a new one: #define mem2chunk(mem) ((mchunkptr)((char*)(mem) - 2*SIZE_SZ))
line 1809 is a new one: /* The smallest possible chunk */
line 1810 is a new one: #define MIN_CHUNK_SIZE        (sizeof(struct malloc_chunk))
line 1812 is a new one: /* The smallest size we can malloc is an aligned minimal chunk */
line 1814 is a new one: #define MINSIZE  \
line 1815 is a new one:   (unsigned long)(((MIN_CHUNK_SIZE+MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))
line 1819 is a new one: #define aligned_OK(m)  (((unsigned long)(m) & MALLOC_ALIGN_MASK) == 0)
line 1821 is a new one: #define misaligned_chunk(p) \
line 1822 is a new one:   ((uintptr_t)(MALLOC_ALIGNMENT == 2 * SIZE_SZ ? (p) : chunk2mem (p)) \
line 1823 is a new one:    & MALLOC_ALIGN_MASK)
line 1827 is a new one:    Check if a request is so large that it would wrap around zero when
line 1828 is a new one:    padded and aligned. To simplify some other code, the bound is made
line 1829 is a new one:    low enough so that adding MINSIZE will also not wrap around zero.
line 1832 is a new one: #define REQUEST_OUT_OF_RANGE(req)                                 \
line 1833 is a new one:   ((unsigned long)(req) >=                                        \
line 1834 is a new one:    (unsigned long)(INTERNAL_SIZE_T)(-2 * MINSIZE))
line 1836 is a new one: /* pad request bytes into a usable size -- internal version */
line 1838 is a new one: #define request2size(req)                                         \
line 1839 is a new one:   (((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE)  ?             \
line 1840 is a new one:    MINSIZE :                                                      \
line 1841 is a new one:    ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)
line 1843 is a new one: /*  Same, except also perform argument check */
line 1845 is a new one: #define checked_request2size(req, sz)                             \
line 1846 is a new one:   if (REQUEST_OUT_OF_RANGE(req)) {                                \
line 1847 is a new one:     MALLOC_FAILURE_ACTION;                                        \
line 1848 is a new one:     return 0;                                                     \
line 1849 is a new one:   }                                                               \
line 1850 is a new one:   (sz) = request2size(req);
line 1853 is a new one:   --------------- Physical chunk operations ---------------
line 1858 is a new one: #define PREV_INUSE 0x1
line 1861 is a new one: #define prev_inuse(p)       ((p)->size & PREV_INUSE)
line 1865 is a new one: #define IS_MMAPPED 0x2
line 1871 is a new one: /* size field is or'ed with NON_MAIN_ARENA if the chunk was obtained
line 1872 is a new one:    from a non-main arena.  This is only set immediately before handing
line 1873 is a new one:    the chunk to the user, if necessary.  */
line 1874 is a new one: #define NON_MAIN_ARENA 0x4
line 1876 is a new one: /* check for chunk from non-main arena */
line 1877 is a new one: #define chunk_non_main_arena(p) ((p)->size & NON_MAIN_ARENA)
line 1881 is a new one:   Bits to mask off when extracting size
line 1883 is a new one:   Note: IS_MMAPPED is intentionally not masked off from size field in
line 1884 is a new one:   macros for which mmapped chunks should never be seen. This should
line 1885 is a new one:   cause helpful core dumps to occur if it is tried by accident by
line 1886 is a new one:   people extending or adapting this malloc.
line 1888 is a new one: #define SIZE_BITS (PREV_INUSE|IS_MMAPPED|NON_MAIN_ARENA)
line 1891 is a new one: #define chunksize(p)         ((p)->size & ~(SIZE_BITS))
line 1895 is a new one: #define next_chunk(p) ((mchunkptr)( ((char*)(p)) + ((p)->size & ~SIZE_BITS) ))
line 1898 is a new one: #define prev_chunk(p) ((mchunkptr)( ((char*)(p)) - ((p)->prev_size) ))
line 1901 is a new one: #define chunk_at_offset(p, s)  ((mchunkptr)(((char*)(p)) + (s)))
line 1904 is a new one: #define inuse(p)\
line 1905 is a new one: ((((mchunkptr)(((char*)(p))+((p)->size & ~SIZE_BITS)))->size) & PREV_INUSE)
line 1907 is a new one: /* set/clear chunk as being inuse without otherwise disturbing */
line 1908 is a new one: #define set_inuse(p)\
line 1909 is a new one: ((mchunkptr)(((char*)(p)) + ((p)->size & ~SIZE_BITS)))->size |= PREV_INUSE
line 1911 is a new one: #define clear_inuse(p)\
line 1912 is a new one: ((mchunkptr)(((char*)(p)) + ((p)->size & ~SIZE_BITS)))->size &= ~(PREV_INUSE)
line 1916 is a new one: #define inuse_bit_at_offset(p, s)\
line 1917 is a new one:  (((mchunkptr)(((char*)(p)) + (s)))->size & PREV_INUSE)
line 1919 is a new one: #define set_inuse_bit_at_offset(p, s)\
line 1920 is a new one:  (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE)
line 1922 is a new one: #define clear_inuse_bit_at_offset(p, s)\
line 1923 is a new one:  (((mchunkptr)(((char*)(p)) + (s)))->size &= ~(PREV_INUSE))
line 1927 is a new one: #define set_head_size(p, s)  ((p)->size = (((p)->size & SIZE_BITS) | (s)))
line 1929 is a new one: /* Set size/use field */
line 1930 is a new one: #define set_head(p, s)       ((p)->size = (s))
line 1933 is a new one: #define set_foot(p, s)       (((mchunkptr)((char*)(p) + (s)))->prev_size = (s))
line 1937 is a new one:   -------------------- Internal data structures --------------------
line 1939 is a new one:    All internal state is held in an instance of malloc_state defined
line 1940 is a new one:    below. There are no other static variables, except in two optional
line 1941 is a new one:    cases:
line 1942 is a new one:    * If USE_MALLOC_LOCK is defined, the mALLOC_MUTEx declared above.
line 1943 is a new one:    * If HAVE_MMAP is true, but mmap doesn't support
line 1944 is a new one:      MAP_ANONYMOUS, a dummy file descriptor for mmap.
line 1946 is a new one:    Beware of lots of tricks that minimize the total bookkeeping space
line 1947 is a new one:    requirements. The result is a little over 1K bytes (for 4byte
line 1948 is a new one:    pointers and size_t.)
line 1952 is a new one:   Bins
line 1954 is a new one:     An array of bin headers for free chunks. Each bin is doubly
line 1955 is a new one:     linked.  The bins are approximately proportionally (log) spaced.
line 1956 is a new one:     There are a lot of these bins (128). This may look excessive, but
line 1957 is a new one:     works very well in practice.  Most bins hold sizes that are
line 1958 is a new one:     unusual as malloc request sizes, but are more usual for fragments
line 1959 is a new one:     and consolidated sets of chunks, which is what these bins hold, so
line 1960 is a new one:     they can be found quickly.  All procedures maintain the invariant
line 1961 is a new one:     that no consolidated chunk physically borders another one, so each
line 1962 is a new one:     chunk in a list is known to be preceeded and followed by either
line 1963 is a new one:     inuse chunks or the ends of memory.
line 1965 is a new one:     Chunks in bins are kept in size order, with ties going to the
line 1966 is a new one:     approximately least recently used chunk. Ordering isn't needed
line 1967 is a new one:     for the small bins, which all contain the same-sized chunks, but
line 1968 is a new one:     facilitates best-fit allocation for larger chunks. These lists
line 1969 is a new one:     are just sequential. Keeping them in order almost never requires
line 1970 is a new one:     enough traversal to warrant using fancier ordered data
line 1971 is a new one:     structures.
line 1973 is a new one:     Chunks of the same size are linked with the most
line 1974 is a new one:     recently freed at the front, and allocations are taken from the
line 1975 is a new one:     back.  This results in LRU (FIFO) allocation order, which tends
line 1976 is a new one:     to give each chunk an equal opportunity to be consolidated with
line 1977 is a new one:     adjacent freed chunks, resulting in larger free chunks and less
line 1978 is a new one:     fragmentation.
line 1980 is a new one:     To simplify use in double-linked lists, each bin header acts
line 1981 is a new one:     as a malloc_chunk. This avoids special-casing for headers.
line 1982 is a new one:     But to conserve space and improve locality, we allocate
line 1983 is a new one:     only the fd/bk pointers of bins, and then use repositioning tricks
line 1984 is a new one:     to treat these as the fields of a malloc_chunk*.
line 1989 is a new one: /* addressing -- note that bin_at(0) does not exist */
line 1990 is a new one: #define bin_at(m, i) ((mbinptr)((char*)&((m)->bins[(i)<<1]) - (SIZE_SZ<<1)))
line 1992 is a new one: /* analog of ++bin */
line 1993 is a new one: #define next_bin(b)  ((mbinptr)((char*)(b) + (sizeof(mchunkptr)<<1)))
line 1995 is a new one: /* Reminders about list directionality within bins */
line 1996 is a new one: #define first(b)     ((b)->fd)
line 1997 is a new one: #define last(b)      ((b)->bk)
line 1999 is a new one: /* Take a chunk off a bin list */
line 2000 is a new one: #define unlink(P, BK, FD) {                                            \
line 2001 is a new one:   FD = P->fd;                                                          \
line 2002 is a new one:   BK = P->bk;                                                          \
line 2003 is a new one:   if (__builtin_expect (FD->bk != P || BK->fd != P, 0))                \
line 2004 is a new one:     malloc_printerr (check_action, "corrupted double-linked list", P); \
line 2005 is a new one:   else {                                                               \
line 2006 is a new one:     FD->bk = BK;                                                       \
line 2007 is a new one:     BK->fd = FD;                                                       \
line 2008 is a new one:   }                                                                    \
line 2012 is a new one:   Indexing
line 2015 is a new one:     8 bytes apart. Larger bins are approximately logarithmically spaced:
line 2028 is a new one:     The bins top out around 1MB because we expect to service large
line 2029 is a new one:     requests via mmap.
line 2032 is a new one: #define NBINS             128
line 2033 is a new one: #define NSMALLBINS         64
line 2034 is a new one: #define SMALLBIN_WIDTH      8
line 2035 is a new one: #define MIN_LARGE_SIZE    512
line 2037 is a new one: #define in_smallbin_range(sz)  \
line 2038 is a new one:   ((unsigned long)(sz) < (unsigned long)MIN_LARGE_SIZE)
line 2040 is a new one: #define smallbin_index(sz)     (((unsigned)(sz)) >> 3)
line 2042 is a new one: #define largebin_index(sz)                                                   \
line 2043 is a new one: (((((unsigned long)(sz)) >>  6) <= 32)?  56 + (((unsigned long)(sz)) >>  6): \
line 2044 is a new one:  ((((unsigned long)(sz)) >>  9) <= 20)?  91 + (((unsigned long)(sz)) >>  9): \
line 2045 is a new one:  ((((unsigned long)(sz)) >> 12) <= 10)? 110 + (((unsigned long)(sz)) >> 12): \
line 2046 is a new one:  ((((unsigned long)(sz)) >> 15) <=  4)? 119 + (((unsigned long)(sz)) >> 15): \
line 2047 is a new one:  ((((unsigned long)(sz)) >> 18) <=  2)? 124 + (((unsigned long)(sz)) >> 18): \
line 2048 is a new one:                                         126)
line 2050 is a new one: #define bin_index(sz) \
line 2051 is a new one:  ((in_smallbin_range(sz)) ? smallbin_index(sz) : largebin_index(sz))
line 2055 is a new one:   Unsorted chunks
line 2057 is a new one:     All remainders from chunk splits, as well as all returned chunks,
line 2058 is a new one:     are first placed in the "unsorted" bin. They are then placed
line 2059 is a new one:     in regular bins after malloc gives them ONE chance to be used before
line 2060 is a new one:     binning. So, basically, the unsorted_chunks list acts as a queue,
line 2061 is a new one:     with chunks being placed on it in free (and malloc_consolidate),
line 2062 is a new one:     and taken off (to be either used or placed in bins) in malloc.
line 2064 is a new one:     The NON_MAIN_ARENA flag is never set for unsorted chunks, so it
line 2065 is a new one:     does not have to be taken into account in size comparisons.
line 2068 is a new one: /* The otherwise unindexable 1-bin is used to hold unsorted chunks. */
line 2069 is a new one: #define unsorted_chunks(M)          (bin_at(M, 1))
line 2072 is a new one:   Top
line 2074 is a new one:     The top-most available chunk (i.e., the one bordering the end of
line 2075 is a new one:     available memory) is treated specially. It is never included in
line 2076 is a new one:     any bin, is used only if no other chunk is available, and is
line 2077 is a new one:     released back to the system if it is very large (see
line 2078 is a new one:     M_TRIM_THRESHOLD).  Because top initially
line 2079 is a new one:     points to its own bin with initial zero size, thus forcing
line 2080 is a new one:     extension on the first malloc request, we avoid having any special
line 2081 is a new one:     code in malloc to check whether it even exists yet. But we still
line 2082 is a new one:     need to do so when getting memory from system, so we make
line 2083 is a new one:     initial_top treat the bin as a legal but unusable chunk during the
line 2084 is a new one:     interval between initialization and the first call to
line 2085 is a new one:     sYSMALLOc. (This is somewhat delicate, since it relies on
line 2086 is a new one:     the 2 preceding words to be zero during this interval as well.)
line 2089 is a new one: /* Conveniently, the unsorted bin can be used as dummy top on first call */
line 2090 is a new one: #define initial_top(M)              (unsorted_chunks(M))
line 2093 is a new one:   Binmap
line 2096 is a new one:     structure is used for bin-by-bin searching.  `binmap' is a
line 2097 is a new one:     bitvector recording whether bins are definitely empty so they can
line 2098 is a new one:     be skipped over during during traversals.  The bits are NOT always
line 2099 is a new one:     cleared as soon as bins are empty, but instead only
line 2100 is a new one:     when they are noticed to be empty during traversal in malloc.
line 2103 is a new one: /* Conservatively use 32 bits per map word, even if on 64bit system */
line 2104 is a new one: #define BINMAPSHIFT      5
line 2105 is a new one: #define BITSPERMAP       (1U << BINMAPSHIFT)
line 2106 is a new one: #define BINMAPSIZE       (NBINS / BITSPERMAP)
line 2108 is a new one: #define idx2block(i)     ((i) >> BINMAPSHIFT)
line 2109 is a new one: #define idx2bit(i)       ((1U << ((i) & ((1U << BINMAPSHIFT)-1))))
line 2111 is a new one: #define mark_bin(m,i)    ((m)->binmap[idx2block(i)] |=  idx2bit(i))
line 2112 is a new one: #define unmark_bin(m,i)  ((m)->binmap[idx2block(i)] &= ~(idx2bit(i)))
line 2113 is a new one: #define get_binmap(m,i)  ((m)->binmap[idx2block(i)] &   idx2bit(i))
line 2116 is a new one:   Fastbins
line 2118 is a new one:     An array of lists holding recently freed small chunks.  Fastbins
line 2119 is a new one:     are not doubly linked.  It is faster to single-link them, and
line 2120 is a new one:     since chunks are never removed from the middles of these lists,
line 2121 is a new one:     double linking is not necessary. Also, unlike regular bins, they
line 2122 is a new one:     are not even processed in FIFO order (they use faster LIFO) since
line 2123 is a new one:     ordering doesn't much matter in the transient contexts in which
line 2124 is a new one:     fastbins are normally used.
line 2126 is a new one:     Chunks in fastbins keep their inuse bit set, so they cannot
line 2127 is a new one:     be consolidated with other free chunks. malloc_consolidate
line 2128 is a new one:     releases all chunks in fastbins and consolidates them with
line 2129 is a new one:     other free chunks.
line 2132 is a new one: typedef struct malloc_chunk* mfastbinptr;
line 2134 is a new one: /* offset 2 to use otherwise unindexable first 2 bins */
line 2135 is a new one: #define fastbin_index(sz)        ((((unsigned int)(sz)) >> 3) - 2)
line 2137 is a new one: /* The maximum fastbin request size we support */
line 2138 is a new one: #define MAX_FAST_SIZE     80
line 2140 is a new one: #define NFASTBINS  (fastbin_index(request2size(MAX_FAST_SIZE))+1)
line 2143 is a new one:   FASTBIN_CONSOLIDATION_THRESHOLD is the size of a chunk in free()
line 2144 is a new one:   that triggers automatic consolidation of possibly-surrounding
line 2145 is a new one:   fastbin chunks. This is a heuristic, so the exact value should not
line 2146 is a new one:   matter too much. It is defined at half the default trim threshold as a
line 2147 is a new one:   compromise heuristic to only attempt consolidation if it is likely
line 2148 is a new one:   to lead to trimming. However, it is not dynamically tunable, since
line 2149 is a new one:   consolidation reduces fragmentation surrounding large chunks even
line 2150 is a new one:   if trimming is not used.
line 2153 is a new one: #define FASTBIN_CONSOLIDATION_THRESHOLD  (65536UL)
line 2156 is a new one:   Since the lowest 2 bits in max_fast don't matter in size comparisons,
line 2157 is a new one:   they are used as flags.
line 2161 is a new one:   FASTCHUNKS_BIT held in max_fast indicates that there are probably
line 2162 is a new one:   some fastbin chunks. It is set true on entering a chunk into any
line 2163 is a new one:   fastbin, and cleared only in malloc_consolidate.
line 2165 is a new one:   The truth value is inverted so that have_fastchunks will be true
line 2166 is a new one:   upon startup (since statics are zero-filled), simplifying
line 2167 is a new one:   initialization checks.
line 2170 is a new one: #define FASTCHUNKS_BIT        (1U)
line 2172 is a new one: #define have_fastchunks(M)     (((M)->flags &  FASTCHUNKS_BIT) == 0)
line 2173 is a new one: #define clear_fastchunks(M)    ((M)->flags |=  FASTCHUNKS_BIT)
line 2174 is a new one: #define set_fastchunks(M)      ((M)->flags &= ~FASTCHUNKS_BIT)
line 2177 is a new one:   NONCONTIGUOUS_BIT indicates that MORECORE does not return contiguous
line 2178 is a new one:   regions.  Otherwise, contiguity is exploited in merging together,
line 2179 is a new one:   when possible, results from consecutive MORECORE calls.
line 2181 is a new one:   The initial value comes from MORECORE_CONTIGUOUS, but is
line 2182 is a new one:   changed dynamically if mmap is ever used as an sbrk substitute.
line 2185 is a new one: #define NONCONTIGUOUS_BIT     (2U)
line 2187 is a new one: #define contiguous(M)          (((M)->flags &  NONCONTIGUOUS_BIT) == 0)
line 2188 is a new one: #define noncontiguous(M)       (((M)->flags &  NONCONTIGUOUS_BIT) != 0)
line 2189 is a new one: #define set_noncontiguous(M)   ((M)->flags |=  NONCONTIGUOUS_BIT)
line 2190 is a new one: #define set_contiguous(M)      ((M)->flags &= ~NONCONTIGUOUS_BIT)
line 2193 is a new one:    Set value of max_fast.
line 2194 is a new one:    Use impossibly small value if 0.
line 2195 is a new one:    Precondition: there are no existing fastbin chunks.
line 2196 is a new one:    Setting the value clears fastchunk bit but preserves noncontiguous bit.
line 2199 is a new one: #define set_max_fast(s) \
line 2200 is a new one:   global_max_fast = ((s) == 0)? SMALLBIN_WIDTH: request2size(s)
line 2201 is a new one: #define get_max_fast() global_max_fast
line 2205 is a new one:    ----------- Internal state representation and initialization -----------
line 2209 is a new one:   /* Serialize access.  */
line 2212 is a new one:   /* Flags (formerly in max_fast).  */
line 2213 is a new one:   int flags;
line 2216 is a new one:   /* Statistics for locking.  Only used if THREAD_STATS is defined.  */
line 2220 is a new one:   /* Fastbins */
line 2221 is a new one:   mfastbinptr      fastbins[NFASTBINS];
line 2223 is a new one:   /* Base of the topmost chunk -- not otherwise kept in a bin */
line 2224 is a new one:   mchunkptr        top;
line 2226 is a new one:   /* The remainder from the most recent split of a small request */
line 2227 is a new one:   mchunkptr        last_remainder;
line 2229 is a new one:   /* Normal bins packed as described above */
line 2230 is a new one:   mchunkptr        bins[NBINS * 2];
line 2232 is a new one:   /* Bitmap of bins */
line 2233 is a new one:   unsigned int     binmap[BINMAPSIZE];
line 2235 is a new one:   /* Linked list */
line 2236 is a new one:   struct malloc_state *next;
line 2238 is a new one:   /* Memory allocated from the system in this arena.  */
line 2239 is a new one:   INTERNAL_SIZE_T system_mem;
line 2240 is a new one:   INTERNAL_SIZE_T max_system_mem;
line 2243 is a new one: struct malloc_par {
line 2244 is a new one:   /* Tunable parameters */
line 2245 is a new one:   unsigned long    trim_threshold;
line 2246 is a new one:   INTERNAL_SIZE_T  top_pad;
line 2247 is a new one:   INTERNAL_SIZE_T  mmap_threshold;
line 2249 is a new one:   /* Memory map support */
line 2250 is a new one:   int              n_mmaps;
line 2251 is a new one:   int              n_mmaps_max;
line 2252 is a new one:   int              max_n_mmaps;
line 2254 is a new one:   /* Cache malloc_getpagesize */
line 2255 is a new one:   unsigned int     pagesize;
line 2257 is a new one:   /* Statistics */
line 2258 is a new one:   INTERNAL_SIZE_T  mmapped_mem;
line 2259 is a new one:   /*INTERNAL_SIZE_T  sbrked_mem;*/
line 2260 is a new one:   /*INTERNAL_SIZE_T  max_sbrked_mem;*/
line 2261 is a new one:   INTERNAL_SIZE_T  max_mmapped_mem;
line 2262 is a new one:   INTERNAL_SIZE_T  max_total_mem; /* only kept for NO_THREADS */
line 2264 is a new one:   /* First address handed out by MORECORE/sbrk.  */
line 2265 is a new one:   char*            sbrk_base;
line 2268 is a new one: /* There are several instances of this struct ("arenas") in this
line 2269 is a new one:    malloc.  If you are adapting this malloc in a way that does NOT use
line 2270 is a new one:    a static or mmapped malloc_state, you MUST explicitly zero-fill it
line 2271 is a new one:    before using. This malloc relies on the property that malloc_state
line 2272 is a new one:    is initialized to all zeroes (as is true of C statics).  */
line 2274 is a new one: static struct malloc_state main_arena;
line 2276 is a new one: /* There is only one instance of the malloc parameters.  */
line 2278 is a new one: static struct malloc_par mp_;
line 2281 is a new one: /* Maximum size of memory handled in fastbins.  */
line 2282 is a new one: static INTERNAL_SIZE_T global_max_fast;
line 2285 is a new one:   Initialize a malloc_state struct.
line 2287 is a new one:   This is called only from within malloc_consolidate, which needs
line 2288 is a new one:   be called in the same contexts anyway.  It is never called directly
line 2289 is a new one:   outside of malloc_consolidate because some optimizing compilers try
line 2290 is a new one:   to inline it at all call points, which turns out not to be an
line 2291 is a new one:   optimization at all. (Inlining it in malloc_consolidate is fine though.)
line 2295 is a new one: static void malloc_init_state(mstate av)
line 2297 is a new one: static void malloc_init_state(av) mstate av;
line 2300 is a new one:   int     i;
line 2301 is a new one:   mbinptr bin;
line 2303 is a new one:   /* Establish circular links for normal bins */
line 2304 is a new one:   for (i = 1; i < NBINS; ++i) {
line 2305 is a new one:     bin = bin_at(av,i);
line 2306 is a new one:     bin->fd = bin->bk = bin;
line 2309 is a new one: #if MORECORE_CONTIGUOUS
line 2310 is a new one:   if (av != &main_arena)
line 2312 is a new one:     set_noncontiguous(av);
line 2313 is a new one:   if (av == &main_arena)
line 2314 is a new one:     set_max_fast(DEFAULT_MXFAST);
line 2315 is a new one:   av->flags |= FASTCHUNKS_BIT;
line 2317 is a new one:   av->top            = initial_top(av);
line 2321 is a new one:    Other internal utilities operating on mstates
line 2325 is a new one: static Void_t*  sYSMALLOc(INTERNAL_SIZE_T, mstate);
line 2326 is a new one: static int      sYSTRIm(size_t, mstate);
line 2327 is a new one: static void     malloc_consolidate(mstate);
line 2329 is a new one: static Void_t** iALLOc(mstate, size_t, size_t*, int, Void_t**);
line 2332 is a new one: static Void_t*  sYSMALLOc();
line 2333 is a new one: static int      sYSTRIm();
line 2334 is a new one: static void     malloc_consolidate();
line 2335 is a new one: static Void_t** iALLOc();
line 2339 is a new one: /* -------------- Early definitions for debugging hooks ---------------- */
line 2341 is a new one: /* Define and initialize the hook variables.  These weak definitions must
line 2342 is a new one:    appear before any use of the variables in a function (arena.c uses one).  */
line 2343 is a new one: #ifndef weak_variable
line 2345 is a new one: #define weak_variable /**/
line 2353 is a new one: /* Forward declarations.  */
line 2354 is a new one: static Void_t* malloc_hook_ini __MALLOC_P ((size_t sz,
line 2355 is a new one: 					    const __malloc_ptr_t caller));
line 2356 is a new one: static Void_t* realloc_hook_ini __MALLOC_P ((Void_t* ptr, size_t sz,
line 2357 is a new one: 					     const __malloc_ptr_t caller));
line 2358 is a new one: static Void_t* memalign_hook_ini __MALLOC_P ((size_t alignment, size_t sz,
line 2359 is a new one: 					      const __malloc_ptr_t caller));
line 2361 is a new one: void weak_variable (*__malloc_initialize_hook) (void) = NULL;
line 2362 is a new one: void weak_variable (*__free_hook) (__malloc_ptr_t __ptr,
line 2363 is a new one: 				   const __malloc_ptr_t) = NULL;
line 2365 is a new one:      (size_t __size, const __malloc_ptr_t) = malloc_hook_ini;
line 2367 is a new one:      (__malloc_ptr_t __ptr, size_t __size, const __malloc_ptr_t)
line 2370 is a new one:      (size_t __alignment, size_t __size, const __malloc_ptr_t)
line 2372 is a new one: void weak_variable (*__after_morecore_hook) (void) = NULL;
line 2375 is a new one: /* ---------------- Error behavior ------------------------------------ */
line 2378 is a new one: #define DEFAULT_CHECK_ACTION 3
line 2381 is a new one: static int check_action = DEFAULT_CHECK_ACTION;
line 2384 is a new one: /* ------------------ Testing support ----------------------------------*/
line 2386 is a new one: static int perturb_byte;
line 2388 is a new one: #define alloc_perturb(p, n) memset (p, (perturb_byte ^ 0xff) & 0xff, n)
line 2389 is a new one: #define free_perturb(p, n) memset (p, perturb_byte & 0xff, n)
line 2392 is a new one: /* ------------------- Support for multiple arenas -------------------- */
line 2393 is a new one: #include "arena.c"
line 2405 is a new one: #if ! MALLOC_DEBUG
line 2410 is a new one: #define check_remalloced_chunk(A,P,N)
line 2412 is a new one: #define check_malloc_state(A)
line 2416 is a new one: #define check_chunk(A,P)              do_check_chunk(A,P)
line 2417 is a new one: #define check_free_chunk(A,P)         do_check_free_chunk(A,P)
line 2418 is a new one: #define check_inuse_chunk(A,P)        do_check_inuse_chunk(A,P)
line 2419 is a new one: #define check_remalloced_chunk(A,P,N) do_check_remalloced_chunk(A,P,N)
line 2420 is a new one: #define check_malloced_chunk(A,P,N)   do_check_malloced_chunk(A,P,N)
line 2421 is a new one: #define check_malloc_state(A)         do_check_malloc_state(A)
line 2424 is a new one:   Properties of all chunks
line 2428 is a new one: static void do_check_chunk(mstate av, mchunkptr p)
line 2430 is a new one: static void do_check_chunk(av, p) mstate av; mchunkptr p;
line 2433 is a new one:   unsigned long sz = chunksize(p);
line 2434 is a new one:   /* min and max possible addresses assuming contiguous allocation */
line 2435 is a new one:   char* max_address = (char*)(av->top) + chunksize(av->top);
line 2436 is a new one:   char* min_address = max_address - av->system_mem;
line 2438 is a new one:   if (!chunk_is_mmapped(p)) {
line 2440 is a new one:     /* Has legal address ... */
line 2441 is a new one:     if (p != av->top) {
line 2442 is a new one:       if (contiguous(av)) {
line 2443 is a new one:         assert(((char*)p) >= min_address);
line 2444 is a new one:         assert(((char*)p + sz) <= ((char*)(av->top)));
line 2448 is a new one:       /* top size is always at least MINSIZE */
line 2449 is a new one:       assert((unsigned long)(sz) >= MINSIZE);
line 2450 is a new one:       /* top predecessor always marked inuse */
line 2451 is a new one:       assert(prev_inuse(p));
line 2457 is a new one:     /* address is outside main heap  */
line 2458 is a new one:     if (contiguous(av) && av->top != initial_top(av)) {
line 2459 is a new one:       assert(((char*)p) < min_address || ((char*)p) > max_address);
line 2461 is a new one:     /* chunk is page-aligned */
line 2462 is a new one:     assert(((p->prev_size + sz) & (mp_.pagesize-1)) == 0);
line 2463 is a new one:     /* mem is aligned */
line 2464 is a new one:     assert(aligned_OK(chunk2mem(p)));
line 2466 is a new one:     /* force an appropriate assert violation if debug set */
line 2467 is a new one:     assert(!chunk_is_mmapped(p));
line 2473 is a new one:   Properties of free chunks
line 2477 is a new one: static void do_check_free_chunk(mstate av, mchunkptr p)
line 2479 is a new one: static void do_check_free_chunk(av, p) mstate av; mchunkptr p;
line 2482 is a new one:   INTERNAL_SIZE_T sz = p->size & ~(PREV_INUSE|NON_MAIN_ARENA);
line 2485 is a new one:   do_check_chunk(av, p);
line 2487 is a new one:   /* Chunk must claim to be free ... */
line 2489 is a new one:   assert (!chunk_is_mmapped(p));
line 2491 is a new one:   /* Unless a special marker, must have OK fields */
line 2492 is a new one:   if ((unsigned long)(sz) >= MINSIZE)
line 2494 is a new one:     assert((sz & MALLOC_ALIGN_MASK) == 0);
line 2495 is a new one:     assert(aligned_OK(chunk2mem(p)));
line 2496 is a new one:     /* ... matching footer field */
line 2497 is a new one:     assert(next->prev_size == sz);
line 2498 is a new one:     /* ... and is fully consolidated */
line 2499 is a new one:     assert(prev_inuse(p));
line 2500 is a new one:     assert (next == av->top || inuse(next));
line 2502 is a new one:     /* ... and has minimally sane links */
line 2503 is a new one:     assert(p->fd->bk == p);
line 2504 is a new one:     assert(p->bk->fd == p);
line 2506 is a new one:   else /* markers are always of size SIZE_SZ */
line 2507 is a new one:     assert(sz == SIZE_SZ);
line 2511 is a new one:   Properties of inuse chunks
line 2515 is a new one: static void do_check_inuse_chunk(mstate av, mchunkptr p)
line 2517 is a new one: static void do_check_inuse_chunk(av, p) mstate av; mchunkptr p;
line 2520 is a new one:   mchunkptr next;
line 2522 is a new one:   do_check_chunk(av, p);
line 2524 is a new one:   if (chunk_is_mmapped(p))
line 2525 is a new one:     return; /* mmapped chunks have no next/prev */
line 2530 is a new one:   next = next_chunk(p);
line 2536 is a new one:   if (!prev_inuse(p))  {
line 2537 is a new one:     /* Note that we cannot even look at prev unless it is not inuse */
line 2540 is a new one:     do_check_free_chunk(av, prv);
line 2543 is a new one:   if (next == av->top) {
line 2548 is a new one:     do_check_free_chunk(av, next);
line 2552 is a new one:   Properties of chunks recycled from fastbins
line 2556 is a new one: static void do_check_remalloced_chunk(mstate av, mchunkptr p, INTERNAL_SIZE_T s)
line 2558 is a new one: static void do_check_remalloced_chunk(av, p, s)
line 2559 is a new one: mstate av; mchunkptr p; INTERNAL_SIZE_T s;
line 2562 is a new one:   INTERNAL_SIZE_T sz = p->size & ~(PREV_INUSE|NON_MAIN_ARENA);
line 2564 is a new one:   if (!chunk_is_mmapped(p)) {
line 2565 is a new one:     assert(av == arena_for_chunk(p));
line 2566 is a new one:     if (chunk_non_main_arena(p))
line 2567 is a new one:       assert(av != &main_arena);
line 2569 is a new one:       assert(av == &main_arena);
line 2572 is a new one:   do_check_inuse_chunk(av, p);
line 2576 is a new one:   assert((unsigned long)(sz) >= MINSIZE);
line 2579 is a new one:   /* chunk is less than MINSIZE more than request */
line 2580 is a new one:   assert((long)(sz) - (long)(s) >= 0);
line 2581 is a new one:   assert((long)(sz) - (long)(s + MINSIZE) < 0);
line 2585 is a new one:   Properties of nonrecycled chunks at the point they are malloced
line 2589 is a new one: static void do_check_malloced_chunk(mstate av, mchunkptr p, INTERNAL_SIZE_T s)
line 2591 is a new one: static void do_check_malloced_chunk(av, p, s)
line 2592 is a new one: mstate av; mchunkptr p; INTERNAL_SIZE_T s;
line 2595 is a new one:   /* same as recycled case ... */
line 2596 is a new one:   do_check_remalloced_chunk(av, p, s);
line 2599 is a new one:     ... plus,  must obey implementation invariant that prev_inuse is
line 2600 is a new one:     always true of any allocated chunk; i.e., that each allocated
line 2601 is a new one:     chunk borders either a previously allocated and still in-use
line 2602 is a new one:     chunk, or the base of its memory arena. This is ensured
line 2603 is a new one:     by making all allocations from the the `lowest' part of any found
line 2604 is a new one:     chunk.  This does not necessarily hold however for chunks
line 2605 is a new one:     recycled via fastbins.
line 2613 is a new one:   Properties of malloc_state.
line 2615 is a new one:   This may be useful for debugging malloc, as well as detecting user
line 2616 is a new one:   programmer errors that somehow write into malloc_state.
line 2618 is a new one:   If you are extending or experimenting with this malloc, you can
line 2619 is a new one:   probably figure out how to hack this routine to print out or
line 2620 is a new one:   display chunk addresses, sizes, bins, and other instrumentation.
line 2623 is a new one: static void do_check_malloc_state(mstate av)
line 2629 is a new one:   unsigned int binbit;
line 2630 is a new one:   int empty;
line 2631 is a new one:   unsigned int idx;
line 2632 is a new one:   INTERNAL_SIZE_T size;
line 2633 is a new one:   unsigned long total = 0;
line 2634 is a new one:   int max_fast_bin;
line 2636 is a new one:   /* internal size_t must be no wider than pointer type */
line 2637 is a new one:   assert(sizeof(INTERNAL_SIZE_T) <= sizeof(char*));
line 2639 is a new one:   /* alignment is a power of 2 */
line 2640 is a new one:   assert((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT-1)) == 0);
line 2642 is a new one:   /* cannot run remaining checks until fully initialized */
line 2643 is a new one:   if (av->top == 0 || av->top == initial_top(av))
line 2646 is a new one:   /* pagesize is a power of 2 */
line 2647 is a new one:   assert((mp_.pagesize & (mp_.pagesize-1)) == 0);
line 2649 is a new one:   /* A contiguous main_arena is consistent with sbrk_base.  */
line 2650 is a new one:   if (av == &main_arena && contiguous(av))
line 2651 is a new one:     assert((char*)mp_.sbrk_base + av->system_mem ==
line 2652 is a new one: 	   (char*)av->top + chunksize(av->top));
line 2654 is a new one:   /* properties of fastbins */
line 2656 is a new one:   /* max_fast is in allowed range */
line 2657 is a new one:   assert((get_max_fast () & ~1) <= request2size(MAX_FAST_SIZE));
line 2659 is a new one:   max_fast_bin = fastbin_index(get_max_fast ());
line 2661 is a new one:   for (i = 0; i < NFASTBINS; ++i) {
line 2662 is a new one:     p = av->fastbins[i];
line 2664 is a new one:     /* all bins past max_fast are empty */
line 2665 is a new one:     if (i > max_fast_bin)
line 2666 is a new one:       assert(p == 0);
line 2668 is a new one:     while (p != 0) {
line 2669 is a new one:       /* each chunk claims to be inuse */
line 2670 is a new one:       do_check_inuse_chunk(av, p);
line 2671 is a new one:       total += chunksize(p);
line 2672 is a new one:       /* chunk belongs in this bin */
line 2673 is a new one:       assert(fastbin_index(chunksize(p)) == i);
line 2674 is a new one:       p = p->fd;
line 2678 is a new one:   if (total != 0)
line 2679 is a new one:     assert(have_fastchunks(av));
line 2680 is a new one:   else if (!have_fastchunks(av))
line 2681 is a new one:     assert(total == 0);
line 2683 is a new one:   /* check normal bins */
line 2684 is a new one:   for (i = 1; i < NBINS; ++i) {
line 2685 is a new one:     b = bin_at(av,i);
line 2687 is a new one:     /* binmap is accurate (except for bin 1 == unsorted_chunks) */
line 2688 is a new one:     if (i >= 2) {
line 2689 is a new one:       binbit = get_binmap(av,i);
line 2690 is a new one:       empty = last(b) == b;
line 2691 is a new one:       if (!binbit)
line 2692 is a new one:         assert(empty);
line 2693 is a new one:       else if (!empty)
line 2694 is a new one:         assert(binbit);
line 2697 is a new one:     for (p = last(b); p != b; p = p->bk) {
line 2698 is a new one:       /* each chunk claims to be free */
line 2699 is a new one:       do_check_free_chunk(av, p);
line 2700 is a new one:       size = chunksize(p);
line 2701 is a new one:       total += size;
line 2702 is a new one:       if (i >= 2) {
line 2703 is a new one:         /* chunk belongs in bin */
line 2704 is a new one:         idx = bin_index(size);
line 2705 is a new one:         assert(idx == i);
line 2706 is a new one:         /* lists are sorted */
line 2707 is a new one:         assert(p->bk == b ||
line 2708 is a new one:                (unsigned long)chunksize(p->bk) >= (unsigned long)chunksize(p));
line 2710 is a new one:       /* chunk is followed by a legal chain of inuse chunks */
line 2712 is a new one:            (q != av->top && inuse(q) &&
line 2713 is a new one:              (unsigned long)(chunksize(q)) >= MINSIZE);
line 2715 is a new one:         do_check_inuse_chunk(av, q);
line 2719 is a new one:   /* top chunk is OK */
line 2720 is a new one:   check_chunk(av, av->top);
line 2722 is a new one:   /* sanity checks for statistics */
line 2725 is a new one:   assert(total <= (unsigned long)(mp_.max_total_mem));
line 2726 is a new one:   assert(mp_.n_mmaps >= 0);
line 2728 is a new one:   assert(mp_.n_mmaps <= mp_.n_mmaps_max);
line 2729 is a new one:   assert(mp_.n_mmaps <= mp_.max_n_mmaps);
line 2731 is a new one:   assert((unsigned long)(av->system_mem) <=
line 2732 is a new one:          (unsigned long)(av->max_system_mem));
line 2734 is a new one:   assert((unsigned long)(mp_.mmapped_mem) <=
line 2735 is a new one:          (unsigned long)(mp_.max_mmapped_mem));
line 2738 is a new one:   assert((unsigned long)(mp_.max_total_mem) >=
line 2739 is a new one:          (unsigned long)(mp_.mmapped_mem) + (unsigned long)(av->system_mem));
line 2745 is a new one: /* ----------------- Support for debugging hooks -------------------- */
line 2746 is a new one: #include "hooks.c"
line 2749 is a new one: /* ----------- Routines dealing with system allocation -------------- */
line 2752 is a new one:   sysmalloc handles malloc cases requiring more memory from the system.
line 2753 is a new one:   On entry, it is assumed that av->top does not have enough
line 2754 is a new one:   space to service request for nb bytes, thus requiring that av->top
line 2755 is a new one:   be extended or replaced.
line 2759 is a new one: static Void_t* sYSMALLOc(INTERNAL_SIZE_T nb, mstate av)
line 2761 is a new one: static Void_t* sYSMALLOc(nb, av) INTERNAL_SIZE_T nb; mstate av;
line 2764 is a new one:   mchunkptr       old_top;        /* incoming value of av->top */
line 2765 is a new one:   INTERNAL_SIZE_T old_size;       /* its size */
line 2766 is a new one:   char*           old_end;        /* its end address */
line 2768 is a new one:   long            size;           /* arg to first MORECORE or mmap call */
line 2769 is a new one:   char*           brk;            /* return value from MORECORE */
line 2771 is a new one:   long            correction;     /* arg to 2nd MORECORE call */
line 2772 is a new one:   char*           snd_brk;        /* 2nd return val */
line 2774 is a new one:   INTERNAL_SIZE_T front_misalign; /* unusable bytes at front of new space */
line 2775 is a new one:   INTERNAL_SIZE_T end_misalign;   /* partial page left at end of new space */
line 2776 is a new one:   char*           aligned_brk;    /* aligned offset into brk */
line 2778 is a new one:   mchunkptr       p;              /* the allocated/returned chunk */
line 2779 is a new one:   mchunkptr       remainder;      /* remainder from allocation */
line 2780 is a new one:   unsigned long   remainder_size; /* its size */
line 2782 is a new one:   unsigned long   sum;            /* for updating stats */
line 2784 is a new one:   size_t          pagemask  = mp_.pagesize - 1;
line 2790 is a new one:     If have mmap, and the request size meets the mmap threshold, and
line 2791 is a new one:     the system supports mmap, and there are few enough currently
line 2792 is a new one:     allocated mmapped regions, try to directly map this request
line 2793 is a new one:     rather than expanding top.
line 2796 is a new one:   if ((unsigned long)(nb) >= (unsigned long)(mp_.mmap_threshold) &&
line 2797 is a new one:       (mp_.n_mmaps < mp_.n_mmaps_max)) {
line 2799 is a new one:     char* mm;             /* return value from mmap call*/
line 2802 is a new one:       Round up size to nearest page.  For mmapped chunks, the overhead
line 2803 is a new one:       is one SIZE_SZ unit larger than for normal chunks, because there
line 2804 is a new one:       is no following chunk whose prev_size field could be used.
line 2806 is a new one:     size = (nb + SIZE_SZ + MALLOC_ALIGN_MASK + pagemask) & ~pagemask;
line 2808 is a new one:     /* Don't try if size wraps around 0 */
line 2809 is a new one:     if ((unsigned long)(size) > (unsigned long)(nb)) {
line 2811 is a new one:       mm = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE));
line 2813 is a new one:       if (mm != MAP_FAILED) {
line 2815 is a new one:         /*
line 2816 is a new one:           The offset to the start of the mmapped region is stored
line 2817 is a new one:           in the prev_size field of the chunk. This allows us to adjust
line 2818 is a new one:           returned start address to meet alignment requirements here
line 2819 is a new one:           and in memalign(), and still be able to compute proper
line 2820 is a new one:           address argument for later munmap in free() and realloc().
line 2821 is a new one:         */
line 2823 is a new one:         front_misalign = (INTERNAL_SIZE_T)chunk2mem(mm) & MALLOC_ALIGN_MASK;
line 2824 is a new one:         if (front_misalign > 0) {
line 2825 is a new one:           correction = MALLOC_ALIGNMENT - front_misalign;
line 2826 is a new one:           p = (mchunkptr)(mm + correction);
line 2827 is a new one:           p->prev_size = correction;
line 2828 is a new one:           set_head(p, (size - correction) |IS_MMAPPED);
line 2830 is a new one:         else {
line 2831 is a new one:           p = (mchunkptr)mm;
line 2832 is a new one:           set_head(p, size|IS_MMAPPED);
line 2835 is a new one:         /* update statistics */
line 2837 is a new one:         if (++mp_.n_mmaps > mp_.max_n_mmaps)
line 2838 is a new one:           mp_.max_n_mmaps = mp_.n_mmaps;
line 2840 is a new one:         sum = mp_.mmapped_mem += size;
line 2841 is a new one:         if (sum > (unsigned long)(mp_.max_mmapped_mem))
line 2842 is a new one:           mp_.max_mmapped_mem = sum;
line 2844 is a new one:         sum += av->system_mem;
line 2845 is a new one:         if (sum > (unsigned long)(mp_.max_total_mem))
line 2846 is a new one:           mp_.max_total_mem = sum;
line 2849 is a new one:         check_chunk(av, p);
line 2851 is a new one:         return chunk2mem(p);
line 2857 is a new one:   /* Record incoming configuration of top */
line 2859 is a new one:   old_top  = av->top;
line 2860 is a new one:   old_size = chunksize(old_top);
line 2861 is a new one:   old_end  = (char*)(chunk_at_offset(old_top, old_size));
line 2863 is a new one:   brk = snd_brk = (char*)(MORECORE_FAILURE);
line 2866 is a new one:      If not the first time through, we require old_size to be
line 2867 is a new one:      at least MINSIZE and to have prev_inuse set.
line 2870 is a new one:   assert((old_top == initial_top(av) && old_size == 0) ||
line 2871 is a new one:          ((unsigned long) (old_size) >= MINSIZE &&
line 2872 is a new one:           prev_inuse(old_top) &&
line 2873 is a new one: 	  ((unsigned long)old_end & pagemask) == 0));
line 2875 is a new one:   /* Precondition: not enough current space to satisfy nb request */
line 2876 is a new one:   assert((unsigned long)(old_size) < (unsigned long)(nb + MINSIZE));
line 2878 is a new one:   /* Precondition: all fastbins are consolidated */
line 2879 is a new one:   assert(!have_fastchunks(av));
line 2882 is a new one:   if (av != &main_arena) {
line 2890 is a new one:     if (grow_heap(old_heap, MINSIZE + nb - old_size) == 0) {
line 2891 is a new one:       av->system_mem += old_heap->size - old_heap_size;
line 2897 is a new one:       set_head(old_top, (((char *)old_heap + old_heap->size) - (char *)old_top)
line 2898 is a new one: 	       | PREV_INUSE);
line 2900 is a new one:     else if ((heap = new_heap(nb + (MINSIZE + sizeof(*heap)), mp_.top_pad))) {
line 2901 is a new one:       /* Use a newly allocated heap.  */
line 2902 is a new one:       heap->ar_ptr = av;
line 2903 is a new one:       heap->prev = old_heap;
line 2904 is a new one:       av->system_mem += heap->size;
line 2905 is a new one:       arena_mem += heap->size;
line 2907 is a new one:       if((unsigned long)(mmapped_mem + arena_mem + sbrked_mem) > max_total_mem)
line 2908 is a new one: 	max_total_mem = mmapped_mem + arena_mem + sbrked_mem;
line 2910 is a new one:       /* Set up the new top.  */
line 2911 is a new one:       top(av) = chunk_at_offset(heap, sizeof(*heap));
line 2912 is a new one:       set_head(top(av), (heap->size - sizeof(*heap)) | PREV_INUSE);
line 2914 is a new one:       /* Setup fencepost and free the old top chunk. */
line 2915 is a new one:       /* The fencepost takes at least MINSIZE bytes, because it might
line 2916 is a new one: 	 become the top chunk again later.  Note that a footer is set
line 2917 is a new one: 	 up, too, although the chunk is marked in use. */
line 2918 is a new one:       old_size -= MINSIZE;
line 2919 is a new one:       set_head(chunk_at_offset(old_top, old_size + 2*SIZE_SZ), 0|PREV_INUSE);
line 2920 is a new one:       if (old_size >= MINSIZE) {
line 2921 is a new one: 	set_head(chunk_at_offset(old_top, old_size), (2*SIZE_SZ)|PREV_INUSE);
line 2922 is a new one: 	set_foot(chunk_at_offset(old_top, old_size), (2*SIZE_SZ));
line 2923 is a new one: 	set_head(old_top, old_size|PREV_INUSE|NON_MAIN_ARENA);
line 2924 is a new one: 	_int_free(av, chunk2mem(old_top));
line 2926 is a new one: 	set_head(old_top, (old_size + 2*SIZE_SZ)|PREV_INUSE);
line 2927 is a new one: 	set_foot(old_top, (old_size + 2*SIZE_SZ));
line 2931 is a new one:   } else { /* av == main_arena */
line 2934 is a new one:   /* Request enough space for nb + pad + overhead */
line 2936 is a new one:   size = nb + mp_.top_pad + MINSIZE;
line 2939 is a new one:     If contiguous, we can subtract out existing space that we hope to
line 2940 is a new one:     combine with new space. We add it back later only if
line 2941 is a new one:     we don't actually get contiguous space.
line 2944 is a new one:   if (contiguous(av))
line 2945 is a new one:     size -= old_size;
line 2948 is a new one:     Round to a multiple of page size.
line 2949 is a new one:     If MORECORE is not contiguous, this ensures that we only call it
line 2950 is a new one:     with whole-page arguments.  And if MORECORE is contiguous and
line 2951 is a new one:     this is not first time through, this preserves page-alignment of
line 2952 is a new one:     previous calls. Otherwise, we correct to page-align below.
line 2955 is a new one:   size = (size + pagemask) & ~pagemask;
line 2958 is a new one:     Don't try to call MORECORE if argument is so big as to appear
line 2959 is a new one:     negative. Note that since mmap takes size_t arg, it may succeed
line 2960 is a new one:     below even if we cannot call MORECORE.
line 2963 is a new one:   if (size > 0)
line 2964 is a new one:     brk = (char*)(MORECORE(size));
line 2966 is a new one:   if (brk != (char*)(MORECORE_FAILURE)) {
line 2972 is a new one:     If have mmap, try using it as a backup when MORECORE fails or
line 2973 is a new one:     cannot be used. This is worth doing on systems that have "holes" in
line 2974 is a new one:     address space, so sbrk cannot extend to give contiguous space, but
line 2975 is a new one:     space is available elsewhere.  Note that we ignore mmap max count
line 2976 is a new one:     and threshold limits, since the space will not be used as a
line 2977 is a new one:     segregated mmap region.
line 2981 is a new one:     /* Cannot merge with old top, so add its size back in */
line 2982 is a new one:     if (contiguous(av))
line 2983 is a new one:       size = (size + old_size + pagemask) & ~pagemask;
line 2985 is a new one:     /* If we are relying on mmap as backup, then use larger units */
line 2986 is a new one:     if ((unsigned long)(size) < (unsigned long)(MMAP_AS_MORECORE_SIZE))
line 2987 is a new one:       size = MMAP_AS_MORECORE_SIZE;
line 2989 is a new one:     /* Don't try if size wraps around 0 */
line 2990 is a new one:     if ((unsigned long)(size) > (unsigned long)(nb)) {
line 2992 is a new one:       char *mbrk = (char*)(MMAP(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE));
line 2994 is a new one:       if (mbrk != MAP_FAILED) {
line 2996 is a new one:         /* We do not need, and cannot use, another sbrk call to find end */
line 2997 is a new one:         brk = mbrk;
line 2998 is a new one:         snd_brk = brk + size;
line 3000 is a new one:         /*
line 3001 is a new one:            Record that we no longer have a contiguous sbrk region.
line 3002 is a new one:            After the first time mmap is used as backup, we do not
line 3003 is a new one:            ever rely on contiguous space since this could incorrectly
line 3004 is a new one:            bridge regions.
line 3005 is a new one:         */
line 3006 is a new one:         set_noncontiguous(av);
line 3012 is a new one:   if (brk != (char*)(MORECORE_FAILURE)) {
line 3013 is a new one:     if (mp_.sbrk_base == 0)
line 3014 is a new one:       mp_.sbrk_base = brk;
line 3015 is a new one:     av->system_mem += size;
line 3018 is a new one:       If MORECORE extends previous space, we can likewise extend top size.
line 3021 is a new one:     if (brk == old_end && snd_brk == (char*)(MORECORE_FAILURE))
line 3022 is a new one:       set_head(old_top, (size + old_size) | PREV_INUSE);
line 3024 is a new one:     else if (contiguous(av) && old_size && brk < old_end) {
line 3025 is a new one:       /* Oops!  Someone else killed our space..  Can't touch anything.  */
line 3026 is a new one:       assert(0);
line 3030 is a new one:       Otherwise, make adjustments:
line 3032 is a new one:       * If the first time through or noncontiguous, we need to call sbrk
line 3033 is a new one:         just to find out where the end of memory lies.
line 3035 is a new one:       * We need to ensure that all returned chunks from malloc will meet
line 3036 is a new one:         MALLOC_ALIGNMENT
line 3038 is a new one:       * If there was an intervening foreign sbrk, we need to adjust sbrk
line 3039 is a new one:         request size to account for fact that we will not be able to
line 3040 is a new one:         combine new space with existing space in old_top.
line 3042 is a new one:       * Almost all systems internally allocate whole pages at a time, in
line 3043 is a new one:         which case we might as well use the whole last page of request.
line 3044 is a new one:         So we allocate enough more memory to hit a page boundary now,
line 3045 is a new one:         which in turn causes future contiguous calls to page-align.
line 3049 is a new one:       front_misalign = 0;
line 3050 is a new one:       end_misalign = 0;
line 3051 is a new one:       correction = 0;
line 3052 is a new one:       aligned_brk = brk;
line 3054 is a new one:       /* handle contiguous cases */
line 3055 is a new one:       if (contiguous(av)) {
line 3057 is a new one: 	/* Count foreign sbrk as system_mem.  */
line 3058 is a new one: 	if (old_size)
line 3059 is a new one: 	  av->system_mem += brk - old_end;
line 3061 is a new one:         /* Guarantee alignment of first new chunk made from this space */
line 3063 is a new one:         front_misalign = (INTERNAL_SIZE_T)chunk2mem(brk) & MALLOC_ALIGN_MASK;
line 3064 is a new one:         if (front_misalign > 0) {
line 3066 is a new one:           /*
line 3067 is a new one:             Skip over some bytes to arrive at an aligned position.
line 3068 is a new one:             We don't need to specially mark these wasted front bytes.
line 3069 is a new one:             They will never be accessed anyway because
line 3070 is a new one:             prev_inuse of av->top (and any chunk created from its start)
line 3071 is a new one:             is always true after initialization.
line 3072 is a new one:           */
line 3074 is a new one:           correction = MALLOC_ALIGNMENT - front_misalign;
line 3075 is a new one:           aligned_brk += correction;
line 3078 is a new one:         /*
line 3079 is a new one:           If this isn't adjacent to existing space, then we will not
line 3080 is a new one:           be able to merge with old_top space, so must add to 2nd request.
line 3081 is a new one:         */
line 3083 is a new one:         correction += old_size;
line 3085 is a new one:         /* Extend the end address to hit a page boundary */
line 3086 is a new one:         end_misalign = (INTERNAL_SIZE_T)(brk + size + correction);
line 3087 is a new one:         correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;
line 3089 is a new one:         assert(correction >= 0);
line 3090 is a new one:         snd_brk = (char*)(MORECORE(correction));
line 3092 is a new one:         /*
line 3093 is a new one:           If can't allocate correction, try to at least find out current
line 3094 is a new one:           brk.  It might be enough to proceed without failing.
line 3096 is a new one:           Note that if second sbrk did NOT fail, we assume that space
line 3097 is a new one:           is contiguous with first sbrk. This is a safe assumption unless
line 3098 is a new one:           program is multithreaded but doesn't use locks and a foreign sbrk
line 3099 is a new one:           occurred between our first and second calls.
line 3100 is a new one:         */
line 3102 is a new one:         if (snd_brk == (char*)(MORECORE_FAILURE)) {
line 3103 is a new one:           correction = 0;
line 3104 is a new one:           snd_brk = (char*)(MORECORE(0));
line 3105 is a new one:         } else
line 3106 is a new one: 	  /* Call the `morecore' hook if necessary.  */
line 3107 is a new one: 	  if (__after_morecore_hook)
line 3108 is a new one: 	    (*__after_morecore_hook) ();
line 3111 is a new one:       /* handle non-contiguous cases */
line 3113 is a new one:         /* MORECORE/mmap must correctly align */
line 3114 is a new one:         assert(((unsigned long)chunk2mem(brk) & MALLOC_ALIGN_MASK) == 0);
line 3116 is a new one:         /* Find out current end of memory */
line 3117 is a new one:         if (snd_brk == (char*)(MORECORE_FAILURE)) {
line 3118 is a new one:           snd_brk = (char*)(MORECORE(0));
line 3122 is a new one:       /* Adjust top based on results of second sbrk */
line 3123 is a new one:       if (snd_brk != (char*)(MORECORE_FAILURE)) {
line 3124 is a new one:         av->top = (mchunkptr)aligned_brk;
line 3125 is a new one:         set_head(av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
line 3126 is a new one:         av->system_mem += correction;
line 3128 is a new one:         /*
line 3129 is a new one:           If not the first time through, we either have a
line 3130 is a new one:           gap due to foreign sbrk or a non-contiguous region.  Insert a
line 3131 is a new one:           double fencepost at old_top to prevent consolidation with space
line 3132 is a new one:           we don't own. These fenceposts are artificial chunks that are
line 3133 is a new one:           marked as inuse and are in any case too small to use.  We need
line 3134 is a new one:           two to make sizes and alignments work out.
line 3135 is a new one:         */
line 3137 is a new one:         if (old_size != 0) {
line 3138 is a new one:           /*
line 3139 is a new one:              Shrink old_top to insert fenceposts, keeping size a
line 3140 is a new one:              multiple of MALLOC_ALIGNMENT. We know there is at least
line 3141 is a new one:              enough space in old_top to do this.
line 3142 is a new one:           */
line 3143 is a new one:           old_size = (old_size - 4*SIZE_SZ) & ~MALLOC_ALIGN_MASK;
line 3144 is a new one:           set_head(old_top, old_size | PREV_INUSE);
line 3146 is a new one:           /*
line 3147 is a new one:             Note that the following assignments completely overwrite
line 3148 is a new one:             old_top when old_size was previously MINSIZE.  This is
line 3149 is a new one:             intentional. We need the fencepost, even if old_top otherwise gets
line 3150 is a new one:             lost.
line 3151 is a new one:           */
line 3152 is a new one:           chunk_at_offset(old_top, old_size            )->size =
line 3153 is a new one:             (2*SIZE_SZ)|PREV_INUSE;
line 3155 is a new one:           chunk_at_offset(old_top, old_size + 2*SIZE_SZ)->size =
line 3156 is a new one:             (2*SIZE_SZ)|PREV_INUSE;
line 3158 is a new one:           /* If possible, release the rest. */
line 3159 is a new one:           if (old_size >= MINSIZE) {
line 3160 is a new one:             _int_free(av, chunk2mem(old_top));
line 3167 is a new one:     /* Update statistics */
line 3169 is a new one:     sum = av->system_mem + mp_.mmapped_mem;
line 3170 is a new one:     if (sum > (unsigned long)(mp_.max_total_mem))
line 3171 is a new one:       mp_.max_total_mem = sum;
line 3176 is a new one:   } /* if (av !=  &main_arena) */
line 3178 is a new one:   if ((unsigned long)av->system_mem > (unsigned long)(av->max_system_mem))
line 3179 is a new one:     av->max_system_mem = av->system_mem;
line 3180 is a new one:   check_malloc_state(av);
line 3182 is a new one:   /* finally, do the allocation */
line 3183 is a new one:   p = av->top;
line 3184 is a new one:   size = chunksize(p);
line 3186 is a new one:   /* check that one of the above allocation paths succeeded */
line 3187 is a new one:   if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE)) {
line 3188 is a new one:     remainder_size = size - nb;
line 3190 is a new one:     av->top = remainder;
line 3191 is a new one:     set_head(p, nb | PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 3193 is a new one:     check_malloced_chunk(av, p, nb);
line 3194 is a new one:     return chunk2mem(p);
line 3197 is a new one:   /* catch all failure paths */
line 3198 is a new one:   MALLOC_FAILURE_ACTION;
line 3204 is a new one:   sYSTRIm is an inverse of sorts to sYSMALLOc.  It gives memory back
line 3205 is a new one:   to the system (via negative arguments to sbrk) if there is unused
line 3206 is a new one:   memory at the `high' end of the malloc pool. It is called
line 3207 is a new one:   automatically by free() when top space exceeds the trim
line 3208 is a new one:   threshold. It is also called by the public malloc_trim routine.  It
line 3209 is a new one:   returns 1 if it actually released any memory, else 0.
line 3213 is a new one: static int sYSTRIm(size_t pad, mstate av)
line 3215 is a new one: static int sYSTRIm(pad, av) size_t pad; mstate av;
line 3220 is a new one:   long  released;        /* Amount actually released */
line 3222 is a new one:   char* new_brk;         /* address returned by post-check sbrk call */
line 3223 is a new one:   size_t pagesz;
line 3225 is a new one:   pagesz = mp_.pagesize;
line 3226 is a new one:   top_size = chunksize(av->top);
line 3228 is a new one:   /* Release in pagesize units, keeping at least one page */
line 3231 is a new one:   if (extra > 0) {
line 3234 is a new one:       Only proceed if end of memory is where we last set it.
line 3235 is a new one:       This avoids problems if there were foreign sbrk calls.
line 3237 is a new one:     current_brk = (char*)(MORECORE(0));
line 3238 is a new one:     if (current_brk == (char*)(av->top) + top_size) {
line 3240 is a new one:       /*
line 3241 is a new one:         Attempt to release memory. We ignore MORECORE return value,
line 3242 is a new one:         and instead call again to find out where new end of memory is.
line 3243 is a new one:         This avoids problems if first call releases less than we asked,
line 3244 is a new one:         of if failure somehow altered brk value. (We could still
line 3245 is a new one:         encounter problems if it altered brk in some very bad way,
line 3246 is a new one:         but the only thing we can do is adjust anyway, which will cause
line 3247 is a new one:         some downstream failure.)
line 3248 is a new one:       */
line 3250 is a new one:       MORECORE(-extra);
line 3253 is a new one: 	(*__after_morecore_hook) ();
line 3254 is a new one:       new_brk = (char*)(MORECORE(0));
line 3256 is a new one:       if (new_brk != (char*)MORECORE_FAILURE) {
line 3257 is a new one:         released = (long)(current_brk - new_brk);
line 3259 is a new one:         if (released != 0) {
line 3260 is a new one:           /* Success. Adjust top. */
line 3261 is a new one:           av->system_mem -= released;
line 3262 is a new one:           set_head(av->top, (top_size - released) | PREV_INUSE);
line 3263 is a new one:           check_malloc_state(av);
line 3264 is a new one:           return 1;
line 3272 is a new one: #ifdef HAVE_MMAP
line 3286 is a new one:   assert(! ((char*)p >= mp_.sbrk_base && (char*)p < mp_.sbrk_base + mp_.sbrked_mem));
line 3287 is a new one:   assert((mp_.n_mmaps > 0));
line 3290 is a new one:   uintptr_t block = (uintptr_t) p - p->prev_size;
line 3291 is a new one:   size_t total_size = p->prev_size + size;
line 3292 is a new one:   /* Unfortunately we have to do the compilers job by hand here.  Normally
line 3293 is a new one:      we would test BLOCK and TOTAL-SIZE separately for compliance with the
line 3294 is a new one:      page size.  But gcc does not recognize the optimization possibility
line 3295 is a new one:      (in the moment at least) so we combine the two values into one before
line 3296 is a new one:      the bit test.  */
line 3297 is a new one:   if (__builtin_expect (((block | total_size) & (mp_.pagesize - 1)) != 0, 0))
line 3299 is a new one:       malloc_printerr (check_action, "munmap_chunk(): invalid pointer",
line 3300 is a new one: 		       chunk2mem (p));
line 3304 is a new one:   mp_.n_mmaps--;
line 3305 is a new one:   mp_.mmapped_mem -= total_size;
line 3307 is a new one:   int ret __attribute__ ((unused)) = munmap((char *)block, total_size);
line 3323 is a new one:   size_t page_mask = mp_.pagesize - 1;
line 3330 is a new one:   assert(! ((char*)p >= mp_.sbrk_base && (char*)p < mp_.sbrk_base + mp_.sbrked_mem));
line 3331 is a new one:   assert((mp_.n_mmaps > 0));
line 3333 is a new one:   assert(((size + offset) & (mp_.pagesize-1)) == 0);
line 3350 is a new one:   mp_.mmapped_mem -= size + offset;
line 3351 is a new one:   mp_.mmapped_mem += new_size;
line 3352 is a new one:   if ((unsigned long)mp_.mmapped_mem > (unsigned long)mp_.max_mmapped_mem)
line 3353 is a new one:     mp_.max_mmapped_mem = mp_.mmapped_mem;
line 3355 is a new one:   if ((unsigned long)(mp_.mmapped_mem + arena_mem + main_arena.system_mem) >
line 3356 is a new one:       mp_.max_total_mem)
line 3357 is a new one:     mp_.max_total_mem = mp_.mmapped_mem + arena_mem + main_arena.system_mem;
line 3366 is a new one: /*------------------------ Public wrappers. --------------------------------*/
line 3369 is a new one: public_mALLOc(size_t bytes)
line 3371 is a new one:   mstate ar_ptr;
line 3372 is a new one:   Void_t *victim;
line 3374 is a new one:   __malloc_ptr_t (*hook) (size_t, __const __malloc_ptr_t) = __malloc_hook;
line 3375 is a new one:   if (hook != NULL)
line 3376 is a new one:     return (*hook)(bytes, RETURN_ADDRESS (0));
line 3378 is a new one:   arena_get(ar_ptr, bytes);
line 3381 is a new one:   victim = _int_malloc(ar_ptr, bytes);
line 3387 is a new one:       victim = _int_malloc(&main_arena, bytes);
line 3392 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, bytes);
line 3395 is a new one:         victim = _int_malloc(ar_ptr, bytes);
line 3402 is a new one:   assert(!victim || chunk_is_mmapped(mem2chunk(victim)) ||
line 3403 is a new one: 	 ar_ptr == arena_for_chunk(mem2chunk(victim)));
line 3406 is a new one: #ifdef libc_hidden_def
line 3407 is a new one: libc_hidden_def(public_mALLOc)
line 3411 is a new one: public_fREe(Void_t* mem)
line 3413 is a new one:   mstate ar_ptr;
line 3416 is a new one:   void (*hook) (__malloc_ptr_t, __const __malloc_ptr_t) = __free_hook;
line 3435 is a new one:   ar_ptr = arena_for_chunk(p);
line 3446 is a new one:   _int_free(ar_ptr, mem);
line 3449 is a new one: #ifdef libc_hidden_def
line 3450 is a new one: libc_hidden_def (public_fREe)
line 3454 is a new one: public_rEALLOc(Void_t* oldmem, size_t bytes)
line 3456 is a new one:   mstate ar_ptr;
line 3462 is a new one:   Void_t* newp;             /* chunk to return */
line 3464 is a new one:   __malloc_ptr_t (*hook) (__malloc_ptr_t, size_t, __const __malloc_ptr_t) =
line 3466 is a new one:   if (hook != NULL)
line 3467 is a new one:     return (*hook)(oldmem, bytes, RETURN_ADDRESS (0));
line 3469 is a new one: #if REALLOC_ZERO_BYTES_FREES
line 3470 is a new one:   if (bytes == 0 && oldmem != NULL) { public_fREe(oldmem); return 0; }
line 3474 is a new one:   if (oldmem == 0) return public_mALLOc(bytes);
line 3479 is a new one:   /* Little security check which won't hurt performance: the
line 3480 is a new one:      allocator never wrapps around at the end of the address space.
line 3481 is a new one:      Therefore we can exclude some size values which might appear
line 3482 is a new one:      here by accident or by "design" from some intruder.  */
line 3483 is a new one:   if (__builtin_expect ((uintptr_t) oldp > (uintptr_t) -oldsize, 0)
line 3484 is a new one:       || __builtin_expect (misaligned_chunk (oldp), 0))
line 3486 is a new one:       malloc_printerr (check_action, "realloc(): invalid pointer", oldmem);
line 3490 is a new one:   checked_request2size(bytes, nb);
line 3499 is a new one:     if(newp) return chunk2mem(newp);
line 3504 is a new one:     newmem = public_mALLOc(bytes);
line 3506 is a new one:     MALLOC_COPY(newmem, oldmem, oldsize - 2*SIZE_SZ);
line 3512 is a new one:   ar_ptr = arena_for_chunk(oldp);
line 3529 is a new one:   newp = _int_realloc(ar_ptr, oldmem, bytes);
line 3532 is a new one:   assert(!newp || chunk_is_mmapped(mem2chunk(newp)) ||
line 3533 is a new one: 	 ar_ptr == arena_for_chunk(mem2chunk(newp)));
line 3536 is a new one: #ifdef libc_hidden_def
line 3537 is a new one: libc_hidden_def (public_rEALLOc)
line 3541 is a new one: public_mEMALIGn(size_t alignment, size_t bytes)
line 3543 is a new one:   mstate ar_ptr;
line 3544 is a new one:   Void_t *p;
line 3547 is a new one: 					__const __malloc_ptr_t)) =
line 3549 is a new one:   if (hook != NULL)
line 3550 is a new one:     return (*hook)(alignment, bytes, RETURN_ADDRESS (0));
line 3553 is a new one:   if (alignment <= MALLOC_ALIGNMENT) return public_mALLOc(bytes);
line 3558 is a new one:   arena_get(ar_ptr, bytes + alignment + MINSIZE);
line 3561 is a new one:   p = _int_memalign(ar_ptr, alignment, bytes);
line 3567 is a new one:       p = _int_memalign(&main_arena, alignment, bytes);
line 3572 is a new one:       ar_ptr = arena_get2(ar_ptr->next ? ar_ptr : 0, bytes);
line 3574 is a new one:         p = _int_memalign(ar_ptr, alignment, bytes);
line 3580 is a new one:   assert(!p || chunk_is_mmapped(mem2chunk(p)) ||
line 3581 is a new one: 	 ar_ptr == arena_for_chunk(mem2chunk(p)));
line 3584 is a new one: #ifdef libc_hidden_def
line 3585 is a new one: libc_hidden_def (public_mEMALIGn)
line 3589 is a new one: public_vALLOc(size_t bytes)
line 3591 is a new one:   mstate ar_ptr;
line 3592 is a new one:   Void_t *p;
line 3598 is a new one: 					__const __malloc_ptr_t)) =
line 3600 is a new one:   if (hook != NULL)
line 3601 is a new one:     return (*hook)(mp_.pagesize, bytes, RETURN_ADDRESS (0));
line 3603 is a new one:   arena_get(ar_ptr, bytes + mp_.pagesize + MINSIZE);
line 3606 is a new one:   p = _int_valloc(ar_ptr, bytes);
line 3612 is a new one: public_pVALLOc(size_t bytes)
line 3614 is a new one:   mstate ar_ptr;
line 3615 is a new one:   Void_t *p;
line 3621 is a new one: 					__const __malloc_ptr_t)) =
line 3623 is a new one:   if (hook != NULL)
line 3624 is a new one:     return (*hook)(mp_.pagesize,
line 3625 is a new one: 		   (bytes + mp_.pagesize - 1) & ~(mp_.pagesize - 1),
line 3626 is a new one: 		   RETURN_ADDRESS (0));
line 3628 is a new one:   arena_get(ar_ptr, bytes + 2*mp_.pagesize + MINSIZE);
line 3629 is a new one:   p = _int_pvalloc(ar_ptr, bytes);
line 3635 is a new one: public_cALLOc(size_t n, size_t elem_size)
line 3637 is a new one:   mstate av;
line 3638 is a new one:   mchunkptr oldtop, p;
line 3639 is a new one:   INTERNAL_SIZE_T bytes, sz, csz, oldtopsize;
line 3641 is a new one:   unsigned long clearsize;
line 3642 is a new one:   unsigned long nclears;
line 3643 is a new one:   INTERNAL_SIZE_T* d;
line 3647 is a new one:   /* size_t is unsigned so the behavior on overflow is defined.  */
line 3648 is a new one:   bytes = n * elem_size;
line 3649 is a new one: #define HALF_INTERNAL_SIZE_T \
line 3650 is a new one:   (((INTERNAL_SIZE_T) 1) << (8 * sizeof (INTERNAL_SIZE_T) / 2))
line 3651 is a new one:   if (__builtin_expect ((n | elem_size) >= HALF_INTERNAL_SIZE_T, 0)) {
line 3652 is a new one:     if (elem_size != 0 && bytes / elem_size != n) {
line 3653 is a new one:       MALLOC_FAILURE_ACTION;
line 3659 is a new one:     sz = bytes;
line 3671 is a new one:   sz = bytes;
line 3673 is a new one:   arena_get(av, sz);
line 3674 is a new one:   if(!av)
line 3677 is a new one:   /* Check if we hand out the top chunk, in which case there may be no
line 3678 is a new one:      need to clear. */
line 3680 is a new one:   oldtop = top(av);
line 3681 is a new one:   oldtopsize = chunksize(top(av));
line 3684 is a new one:   if (av == &main_arena &&
line 3685 is a new one:       oldtopsize < mp_.sbrk_base + av->max_system_mem - (char *)oldtop)
line 3686 is a new one:     oldtopsize = (mp_.sbrk_base + av->max_system_mem - (char *)oldtop);
line 3689 is a new one:   mem = _int_malloc(av, sz);
line 3692 is a new one:   (void)mutex_unlock(&av->mutex);
line 3694 is a new one:   assert(!mem || chunk_is_mmapped(mem2chunk(mem)) ||
line 3695 is a new one: 	 av == arena_for_chunk(mem2chunk(mem)));
line 3697 is a new one:   if (mem == 0) {
line 3699 is a new one:     if(av != &main_arena) {
line 3701 is a new one:       mem = _int_malloc(&main_arena, sz);
line 3707 is a new one:       av = arena_get2(av->next ? av : 0, sz);
line 3709 is a new one:       if(av) {
line 3710 is a new one:         mem = _int_malloc(av, sz);
line 3711 is a new one:         (void)mutex_unlock(&av->mutex);
line 3715 is a new one:     if (mem == 0) return 0;
line 3721 is a new one:   if (chunk_is_mmapped (p))
line 3723 is a new one:       if (__builtin_expect (perturb_byte, 0))
line 3724 is a new one: 	MALLOC_ZERO (mem, sz);
line 3725 is a new one:       return mem;
line 3732 is a new one:   if (perturb_byte == 0 && (p == oldtop && csz > oldtopsize)) {
line 3738 is a new one:   /* Unroll clear of <= 36 bytes (72 if 8byte sizes).  We know that
line 3739 is a new one:      contents have an odd number of INTERNAL_SIZE_T-sized words;
line 3740 is a new one:      minimally 3.  */
line 3741 is a new one:   d = (INTERNAL_SIZE_T*)mem;
line 3742 is a new one:   clearsize = csz - SIZE_SZ;
line 3743 is a new one:   nclears = clearsize / sizeof(INTERNAL_SIZE_T);
line 3744 is a new one:   assert(nclears >= 3);
line 3746 is a new one:   if (nclears > 9)
line 3747 is a new one:     MALLOC_ZERO(d, clearsize);
line 3750 is a new one:     *(d+0) = 0;
line 3751 is a new one:     *(d+1) = 0;
line 3752 is a new one:     *(d+2) = 0;
line 3753 is a new one:     if (nclears > 4) {
line 3754 is a new one:       *(d+3) = 0;
line 3755 is a new one:       *(d+4) = 0;
line 3756 is a new one:       if (nclears > 6) {
line 3757 is a new one: 	*(d+5) = 0;
line 3758 is a new one: 	*(d+6) = 0;
line 3759 is a new one: 	if (nclears > 8) {
line 3760 is a new one: 	  *(d+7) = 0;
line 3761 is a new one: 	  *(d+8) = 0;
line 3772 is a new one: Void_t**
line 3773 is a new one: public_iCALLOc(size_t n, size_t elem_size, Void_t** chunks)
line 3775 is a new one:   mstate ar_ptr;
line 3776 is a new one:   Void_t** m;
line 3778 is a new one:   arena_get(ar_ptr, n*elem_size);
line 3782 is a new one:   m = _int_icalloc(ar_ptr, n, elem_size, chunks);
line 3784 is a new one:   return m;
line 3787 is a new one: Void_t**
line 3788 is a new one: public_iCOMALLOc(size_t n, size_t sizes[], Void_t** chunks)
line 3790 is a new one:   mstate ar_ptr;
line 3791 is a new one:   Void_t** m;
line 3793 is a new one:   arena_get(ar_ptr, 0);
line 3797 is a new one:   m = _int_icomalloc(ar_ptr, n, sizes, chunks);
line 3799 is a new one:   return m;
line 3803 is a new one: public_cFREe(Void_t* m)
line 3805 is a new one:   public_fREe(m);
line 3811 is a new one: public_mTRIm(size_t s)
line 3813 is a new one:   int result;
line 3818 is a new one:   result = mTRIm(s);
line 3823 is a new one: size_t
line 3824 is a new one: public_mUSABLe(Void_t* m)
line 3826 is a new one:   size_t result;
line 3828 is a new one:   result = mUSABLe(m);
line 3833 is a new one: public_mSTATs()
line 3835 is a new one:   mSTATs();
line 3838 is a new one: struct mallinfo public_mALLINFo()
line 3840 is a new one:   struct mallinfo m;
line 3845 is a new one:   m = mALLINFo(&main_arena);
line 3847 is a new one:   return m;
line 3851 is a new one: public_mALLOPt(int p, int v)
line 3853 is a new one:   int result;
line 3854 is a new one:   result = mALLOPt(p, v);
line 3859 is a new one:   ------------------------------ malloc ------------------------------
line 3863 is a new one: _int_malloc(mstate av, size_t bytes)
line 3865 is a new one:   INTERNAL_SIZE_T nb;               /* normalized request size */
line 3866 is a new one:   unsigned int    idx;              /* associated bin index */
line 3867 is a new one:   mbinptr         bin;              /* associated bin */
line 3868 is a new one:   mfastbinptr*    fb;               /* associated fastbin */
line 3870 is a new one:   mchunkptr       victim;           /* inspected/selected chunk */
line 3871 is a new one:   INTERNAL_SIZE_T size;             /* its size */
line 3872 is a new one:   int             victim_index;     /* its bin index */
line 3874 is a new one:   mchunkptr       remainder;        /* remainder from a split */
line 3875 is a new one:   unsigned long   remainder_size;   /* its size */
line 3877 is a new one:   unsigned int    block;            /* bit map traverser */
line 3878 is a new one:   unsigned int    bit;              /* bit map traverser */
line 3879 is a new one:   unsigned int    map;              /* current word of binmap */
line 3881 is a new one:   mchunkptr       fwd;              /* misc temp for linking */
line 3882 is a new one:   mchunkptr       bck;              /* misc temp for linking */
line 3885 is a new one:     Convert request size to internal form by adding SIZE_SZ bytes
line 3886 is a new one:     overhead plus possibly more to obtain necessary alignment and/or
line 3887 is a new one:     to obtain a size of at least MINSIZE, the smallest allocatable
line 3888 is a new one:     size. Also, checked_request2size traps (returning 0) request sizes
line 3889 is a new one:     that are so large that they wrap around zero when padded and
line 3890 is a new one:     aligned.
line 3893 is a new one:   checked_request2size(bytes, nb);
line 3896 is a new one:     If the size qualifies as a fastbin, first check corresponding bin.
line 3897 is a new one:     This code is safe to execute even if av is not yet initialized, so we
line 3898 is a new one:     can try it without checking, which saves some time on this fast path.
line 3901 is a new one:   if ((unsigned long)(nb) <= (unsigned long)(get_max_fast ())) {
line 3902 is a new one:     long int idx = fastbin_index(nb);
line 3903 is a new one:     fb = &(av->fastbins[idx]);
line 3904 is a new one:     if ( (victim = *fb) != 0) {
line 3905 is a new one:       if (__builtin_expect (fastbin_index (chunksize (victim)) != idx, 0))
line 3906 is a new one: 	malloc_printerr (check_action, "malloc(): memory corruption (fast)",
line 3907 is a new one: 			 chunk2mem (victim));
line 3908 is a new one:       *fb = victim->fd;
line 3909 is a new one:       check_remalloced_chunk(av, victim, nb);
line 3910 is a new one:       void *p = chunk2mem(victim);
line 3911 is a new one:       if (__builtin_expect (perturb_byte, 0))
line 3912 is a new one: 	alloc_perturb (p, bytes);
line 3913 is a new one:       return p;
line 3918 is a new one:     If a small request, check regular bin.  Since these "smallbins"
line 3919 is a new one:     hold one size each, no searching within bins is necessary.
line 3920 is a new one:     (For a large request, we need to wait until unsorted chunks are
line 3921 is a new one:     processed to find best fit. But for small ones, fits are exact
line 3922 is a new one:     anyway, so we can check now, which is faster.)
line 3925 is a new one:   if (in_smallbin_range(nb)) {
line 3927 is a new one:     bin = bin_at(av,idx);
line 3929 is a new one:     if ( (victim = last(bin)) != bin) {
line 3930 is a new one:       if (victim == 0) /* initialization check */
line 3931 is a new one:         malloc_consolidate(av);
line 3933 is a new one:         bck = victim->bk;
line 3934 is a new one:         set_inuse_bit_at_offset(victim, nb);
line 3935 is a new one:         bin->bk = bck;
line 3936 is a new one:         bck->fd = bin;
line 3938 is a new one:         if (av != &main_arena)
line 3939 is a new one: 	  victim->size |= NON_MAIN_ARENA;
line 3940 is a new one:         check_malloced_chunk(av, victim, nb);
line 3941 is a new one: 	void *p = chunk2mem(victim);
line 3942 is a new one: 	if (__builtin_expect (perturb_byte, 0))
line 3943 is a new one: 	  alloc_perturb (p, bytes);
line 3944 is a new one: 	return p;
line 3950 is a new one:      If this is a large request, consolidate fastbins before continuing.
line 3951 is a new one:      While it might look excessive to kill all fastbins before
line 3952 is a new one:      even seeing if there is space available, this avoids
line 3953 is a new one:      fragmentation problems normally associated with fastbins.
line 3954 is a new one:      Also, in practice, programs tend to have runs of either small or
line 3955 is a new one:      large requests, but less often mixtures, so consolidation is not
line 3956 is a new one:      invoked all that often in most programs. And the programs that
line 3957 is a new one:      it is called frequently in otherwise tend to fragment.
line 3961 is a new one:     idx = largebin_index(nb);
line 3962 is a new one:     if (have_fastchunks(av))
line 3963 is a new one:       malloc_consolidate(av);
line 3967 is a new one:     Process recently freed or remaindered chunks, taking one only if
line 3968 is a new one:     it is exact fit, or, if this a small request, the chunk is remainder from
line 3969 is a new one:     the most recent non-exact fit.  Place other traversed chunks in
line 3970 is a new one:     bins.  Note that this step is the only place in any routine where
line 3971 is a new one:     chunks are placed in bins.
line 3973 is a new one:     The outer loop here is needed because we might not realize until
line 3974 is a new one:     near the end of malloc that we should have consolidated, so must
line 3975 is a new one:     do so and retry. This happens at most once, and only when we would
line 3976 is a new one:     otherwise need to expand memory to service a "small" request.
line 3981 is a new one:     while ( (victim = unsorted_chunks(av)->bk) != unsorted_chunks(av)) {
line 3982 is a new one:       bck = victim->bk;
line 3983 is a new one:       if (__builtin_expect (victim->size <= 2 * SIZE_SZ, 0)
line 3984 is a new one: 	  || __builtin_expect (victim->size > av->system_mem, 0))
line 3985 is a new one: 	malloc_printerr (check_action, "malloc(): memory corruption",
line 3986 is a new one: 			 chunk2mem (victim));
line 3987 is a new one:       size = chunksize(victim);
line 3989 is a new one:       /*
line 3990 is a new one:          If a small request, try to use last remainder if it is the
line 3991 is a new one:          only chunk in unsorted bin.  This helps promote locality for
line 3992 is a new one:          runs of consecutive small requests. This is the only
line 3993 is a new one:          exception to best-fit, and applies only when there is
line 3994 is a new one:          no exact fit for a small chunk.
line 3995 is a new one:       */
line 3997 is a new one:       if (in_smallbin_range(nb) &&
line 3998 is a new one:           bck == unsorted_chunks(av) &&
line 3999 is a new one:           victim == av->last_remainder &&
line 4000 is a new one:           (unsigned long)(size) > (unsigned long)(nb + MINSIZE)) {
line 4002 is a new one:         /* split and reattach remainder */
line 4003 is a new one:         remainder_size = size - nb;
line 4004 is a new one:         remainder = chunk_at_offset(victim, nb);
line 4005 is a new one:         unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
line 4006 is a new one:         av->last_remainder = remainder;
line 4007 is a new one:         remainder->bk = remainder->fd = unsorted_chunks(av);
line 4009 is a new one:         set_head(victim, nb | PREV_INUSE |
line 4010 is a new one: 		 (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4011 is a new one:         set_head(remainder, remainder_size | PREV_INUSE);
line 4012 is a new one:         set_foot(remainder, remainder_size);
line 4014 is a new one:         check_malloced_chunk(av, victim, nb);
line 4015 is a new one: 	void *p = chunk2mem(victim);
line 4016 is a new one: 	if (__builtin_expect (perturb_byte, 0))
line 4017 is a new one: 	  alloc_perturb (p, bytes);
line 4018 is a new one: 	return p;
line 4021 is a new one:       /* remove from unsorted list */
line 4022 is a new one:       unsorted_chunks(av)->bk = bck;
line 4023 is a new one:       bck->fd = unsorted_chunks(av);
line 4025 is a new one:       /* Take now instead of binning if exact fit */
line 4027 is a new one:       if (size == nb) {
line 4028 is a new one:         set_inuse_bit_at_offset(victim, size);
line 4029 is a new one: 	if (av != &main_arena)
line 4030 is a new one: 	  victim->size |= NON_MAIN_ARENA;
line 4031 is a new one:         check_malloced_chunk(av, victim, nb);
line 4032 is a new one: 	void *p = chunk2mem(victim);
line 4033 is a new one: 	if (__builtin_expect (perturb_byte, 0))
line 4034 is a new one: 	  alloc_perturb (p, bytes);
line 4035 is a new one: 	return p;
line 4038 is a new one:       /* place chunk in bin */
line 4040 is a new one:       if (in_smallbin_range(size)) {
line 4041 is a new one:         victim_index = smallbin_index(size);
line 4042 is a new one:         bck = bin_at(av, victim_index);
line 4043 is a new one:         fwd = bck->fd;
line 4046 is a new one:         victim_index = largebin_index(size);
line 4047 is a new one:         bck = bin_at(av, victim_index);
line 4048 is a new one:         fwd = bck->fd;
line 4050 is a new one:         /* maintain large bins in sorted order */
line 4051 is a new one:         if (fwd != bck) {
line 4052 is a new one: 	  /* Or with inuse bit to speed comparisons */
line 4053 is a new one:           size |= PREV_INUSE;
line 4054 is a new one:           /* if smaller than smallest, bypass loop below */
line 4055 is a new one: 	  assert((bck->bk->size & NON_MAIN_ARENA) == 0);
line 4056 is a new one:           if ((unsigned long)(size) <= (unsigned long)(bck->bk->size)) {
line 4057 is a new one:             fwd = bck;
line 4058 is a new one:             bck = bck->bk;
line 4060 is a new one:           else {
line 4061 is a new one: 	    assert((fwd->size & NON_MAIN_ARENA) == 0);
line 4062 is a new one:             while ((unsigned long)(size) < (unsigned long)(fwd->size)) {
line 4063 is a new one:               fwd = fwd->fd;
line 4064 is a new one: 	      assert((fwd->size & NON_MAIN_ARENA) == 0);
line 4066 is a new one:             bck = fwd->bk;
line 4071 is a new one:       mark_bin(av, victim_index);
line 4072 is a new one:       victim->bk = bck;
line 4073 is a new one:       victim->fd = fwd;
line 4074 is a new one:       fwd->bk = victim;
line 4075 is a new one:       bck->fd = victim;
line 4079 is a new one:       If a large request, scan through the chunks of current bin in
line 4080 is a new one:       sorted order to find smallest that fits.  This is the only step
line 4081 is a new one:       where an unbounded number of chunks might be scanned without doing
line 4082 is a new one:       anything useful with them. However the lists tend to be short.
line 4085 is a new one:     if (!in_smallbin_range(nb)) {
line 4086 is a new one:       bin = bin_at(av, idx);
line 4088 is a new one:       /* skip scan if empty or largest chunk is too small */
line 4089 is a new one:       if ((victim = last(bin)) != bin &&
line 4090 is a new one:           (unsigned long)(first(bin)->size) >= (unsigned long)(nb)) {
line 4092 is a new one:         while (((unsigned long)(size = chunksize(victim)) <
line 4093 is a new one:                 (unsigned long)(nb)))
line 4094 is a new one:           victim = victim->bk;
line 4096 is a new one:         remainder_size = size - nb;
line 4099 is a new one:         /* Exhaust */
line 4100 is a new one:         if (remainder_size < MINSIZE)  {
line 4101 is a new one:           set_inuse_bit_at_offset(victim, size);
line 4102 is a new one: 	  if (av != &main_arena)
line 4103 is a new one: 	    victim->size |= NON_MAIN_ARENA;
line 4105 is a new one:         /* Split */
line 4106 is a new one:         else {
line 4107 is a new one:           remainder = chunk_at_offset(victim, nb);
line 4108 is a new one:           unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
line 4109 is a new one:           remainder->bk = remainder->fd = unsorted_chunks(av);
line 4110 is a new one:           set_head(victim, nb | PREV_INUSE |
line 4111 is a new one: 		   (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4112 is a new one:           set_head(remainder, remainder_size | PREV_INUSE);
line 4113 is a new one:           set_foot(remainder, remainder_size);
line 4115 is a new one: 	check_malloced_chunk(av, victim, nb);
line 4116 is a new one: 	void *p = chunk2mem(victim);
line 4117 is a new one: 	if (__builtin_expect (perturb_byte, 0))
line 4118 is a new one: 	  alloc_perturb (p, bytes);
line 4119 is a new one: 	return p;
line 4124 is a new one:       Search for a chunk by scanning bins, starting with next largest
line 4125 is a new one:       bin. This search is strictly by best-fit; i.e., the smallest
line 4126 is a new one:       (with ties going to approximately the least recently used) chunk
line 4127 is a new one:       that fits is selected.
line 4129 is a new one:       The bitmap avoids needing to check that most blocks are nonempty.
line 4130 is a new one:       The particular case of skipping all bins during warm-up phases
line 4131 is a new one:       when no chunks have been returned yet is faster than it might look.
line 4135 is a new one:     bin = bin_at(av,idx);
line 4136 is a new one:     block = idx2block(idx);
line 4137 is a new one:     map = av->binmap[block];
line 4138 is a new one:     bit = idx2bit(idx);
line 4140 is a new one:     for (;;) {
line 4142 is a new one:       /* Skip rest of block if there are no more set bits in this block.  */
line 4143 is a new one:       if (bit > map || bit == 0) {
line 4144 is a new one:         do {
line 4145 is a new one:           if (++block >= BINMAPSIZE)  /* out of bins */
line 4146 is a new one:             goto use_top;
line 4147 is a new one:         } while ( (map = av->binmap[block]) == 0);
line 4149 is a new one:         bin = bin_at(av, (block << BINMAPSHIFT));
line 4150 is a new one:         bit = 1;
line 4153 is a new one:       /* Advance to bin with set bit. There must be one. */
line 4154 is a new one:       while ((bit & map) == 0) {
line 4155 is a new one:         bin = next_bin(bin);
line 4156 is a new one:         bit <<= 1;
line 4157 is a new one:         assert(bit != 0);
line 4160 is a new one:       /* Inspect the bin. It is likely to be non-empty */
line 4161 is a new one:       victim = last(bin);
line 4163 is a new one:       /*  If a false alarm (empty bin), clear the bit. */
line 4164 is a new one:       if (victim == bin) {
line 4165 is a new one:         av->binmap[block] = map &= ~bit; /* Write through */
line 4166 is a new one:         bin = next_bin(bin);
line 4167 is a new one:         bit <<= 1;
line 4171 is a new one:         size = chunksize(victim);
line 4173 is a new one:         /*  We know the first chunk in this bin is big enough to use. */
line 4174 is a new one:         assert((unsigned long)(size) >= (unsigned long)(nb));
line 4176 is a new one:         remainder_size = size - nb;
line 4178 is a new one:         /* unlink */
line 4179 is a new one:         bck = victim->bk;
line 4180 is a new one:         bin->bk = bck;
line 4181 is a new one:         bck->fd = bin;
line 4183 is a new one:         /* Exhaust */
line 4184 is a new one:         if (remainder_size < MINSIZE) {
line 4185 is a new one:           set_inuse_bit_at_offset(victim, size);
line 4186 is a new one: 	  if (av != &main_arena)
line 4187 is a new one: 	    victim->size |= NON_MAIN_ARENA;
line 4190 is a new one:         /* Split */
line 4191 is a new one:         else {
line 4192 is a new one:           remainder = chunk_at_offset(victim, nb);
line 4194 is a new one:           unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
line 4195 is a new one:           remainder->bk = remainder->fd = unsorted_chunks(av);
line 4196 is a new one:           /* advertise as last remainder */
line 4197 is a new one:           if (in_smallbin_range(nb))
line 4198 is a new one:             av->last_remainder = remainder;
line 4200 is a new one:           set_head(victim, nb | PREV_INUSE |
line 4201 is a new one: 		   (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4202 is a new one:           set_head(remainder, remainder_size | PREV_INUSE);
line 4203 is a new one:           set_foot(remainder, remainder_size);
line 4205 is a new one: 	check_malloced_chunk(av, victim, nb);
line 4206 is a new one: 	void *p = chunk2mem(victim);
line 4207 is a new one: 	if (__builtin_expect (perturb_byte, 0))
line 4208 is a new one: 	  alloc_perturb (p, bytes);
line 4209 is a new one: 	return p;
line 4213 is a new one:   use_top:
line 4215 is a new one:       If large enough, split off the chunk bordering the end of memory
line 4216 is a new one:       (held in av->top). Note that this is in accord with the best-fit
line 4217 is a new one:       search rule.  In effect, av->top is treated as larger (and thus
line 4218 is a new one:       less well fitting) than any other available chunk since it can
line 4219 is a new one:       be extended to be as large as necessary (up to system
line 4220 is a new one:       limitations).
line 4222 is a new one:       We require that av->top always exists (i.e., has size >=
line 4223 is a new one:       MINSIZE) after initialization, so if it would otherwise be
line 4224 is a new one:       exhuasted by current request, it is replenished. (The main
line 4225 is a new one:       reason for ensuring it exists is that we may need MINSIZE space
line 4226 is a new one:       to put in fenceposts in sysmalloc.)
line 4229 is a new one:     victim = av->top;
line 4230 is a new one:     size = chunksize(victim);
line 4232 is a new one:     if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE)) {
line 4233 is a new one:       remainder_size = size - nb;
line 4235 is a new one:       av->top = remainder;
line 4236 is a new one:       set_head(victim, nb | PREV_INUSE |
line 4237 is a new one: 	       (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4240 is a new one:       check_malloced_chunk(av, victim, nb);
line 4241 is a new one:       void *p = chunk2mem(victim);
line 4242 is a new one:       if (__builtin_expect (perturb_byte, 0))
line 4243 is a new one: 	alloc_perturb (p, bytes);
line 4244 is a new one:       return p;
line 4248 is a new one:       If there is space available in fastbins, consolidate and retry,
line 4249 is a new one:       to possibly avoid expanding memory. This can occur only if nb is
line 4250 is a new one:       in smallbin range so we didn't consolidate upon entry.
line 4253 is a new one:     else if (have_fastchunks(av)) {
line 4254 is a new one:       assert(in_smallbin_range(nb));
line 4255 is a new one:       malloc_consolidate(av);
line 4256 is a new one:       idx = smallbin_index(nb); /* restore original bin index */
line 4260 is a new one:        Otherwise, relay to handle system-dependent cases
line 4263 is a new one:       void *p = sYSMALLOc(nb, av);
line 4264 is a new one:       if (__builtin_expect (perturb_byte, 0))
line 4265 is a new one: 	alloc_perturb (p, bytes);
line 4266 is a new one:       return p;
line 4272 is a new one:   ------------------------------ free ------------------------------
line 4276 is a new one: _int_free(mstate av, Void_t* mem)
line 4278 is a new one:   mchunkptr       p;           /* chunk corresponding to mem */
line 4279 is a new one:   INTERNAL_SIZE_T size;        /* its size */
line 4280 is a new one:   mfastbinptr*    fb;          /* associated fastbin */
line 4281 is a new one:   mchunkptr       nextchunk;   /* next contiguous chunk */
line 4282 is a new one:   INTERNAL_SIZE_T nextsize;    /* its size */
line 4283 is a new one:   int             nextinuse;   /* true if nextchunk is used */
line 4284 is a new one:   INTERNAL_SIZE_T prevsize;    /* size of previous contiguous chunk */
line 4285 is a new one:   mchunkptr       bck;         /* misc temp for linking */
line 4286 is a new one:   mchunkptr       fwd;         /* misc temp for linking */
line 4288 is a new one:   const char *errstr = NULL;
line 4291 is a new one:   size = chunksize(p);
line 4293 is a new one:   /* Little security check which won't hurt performance: the
line 4294 is a new one:      allocator never wrapps around at the end of the address space.
line 4295 is a new one:      Therefore we can exclude some size values which might appear
line 4296 is a new one:      here by accident or by "design" from some intruder.  */
line 4297 is a new one:   if (__builtin_expect ((uintptr_t) p > (uintptr_t) -size, 0)
line 4298 is a new one:       || __builtin_expect (misaligned_chunk (p), 0))
line 4300 is a new one:       errstr = "free(): invalid pointer";
line 4301 is a new one:     errout:
line 4302 is a new one:       malloc_printerr (check_action, errstr, mem);
line 4305 is a new one:   /* We know that each chunk is at least MINSIZE bytes in size.  */
line 4306 is a new one:   if (__builtin_expect (size < MINSIZE, 0))
line 4308 is a new one:       errstr = "free(): invalid size";
line 4309 is a new one:       goto errout;
line 4312 is a new one:   check_inuse_chunk(av, p);
line 4315 is a new one:     If eligible, place chunk on a fastbin so it can be found
line 4316 is a new one:     and used quickly in malloc.
line 4319 is a new one:   if ((unsigned long)(size) <= (unsigned long)(get_max_fast ())
line 4321 is a new one: #if TRIM_FASTBINS
line 4322 is a new one:       /*
line 4323 is a new one: 	If TRIM_FASTBINS set, don't place chunks
line 4324 is a new one: 	bordering top into fastbins
line 4325 is a new one:       */
line 4326 is a new one:       && (chunk_at_offset(p, size) != av->top)
line 4328 is a new one:       ) {
line 4330 is a new one:     if (__builtin_expect (chunk_at_offset (p, size)->size <= 2 * SIZE_SZ, 0)
line 4331 is a new one: 	|| __builtin_expect (chunksize (chunk_at_offset (p, size))
line 4332 is a new one: 			     >= av->system_mem, 0))
line 4334 is a new one: 	errstr = "free(): invalid next size (fast)";
line 4335 is a new one: 	goto errout;
line 4338 is a new one:     set_fastchunks(av);
line 4339 is a new one:     fb = &(av->fastbins[fastbin_index(size)]);
line 4340 is a new one:     /* Another simple check: make sure the top of the bin is not the
line 4341 is a new one:        record we are going to add (i.e., double free).  */
line 4342 is a new one:     if (__builtin_expect (*fb == p, 0))
line 4344 is a new one: 	errstr = "double free or corruption (fasttop)";
line 4345 is a new one: 	goto errout;
line 4348 is a new one:     if (__builtin_expect (perturb_byte, 0))
line 4349 is a new one:       free_perturb (mem, size - SIZE_SZ);
line 4351 is a new one:     p->fd = *fb;
line 4352 is a new one:     *fb = p;
line 4356 is a new one:     Consolidate other non-mmapped chunks as they arrive.
line 4359 is a new one:   else if (!chunk_is_mmapped(p)) {
line 4360 is a new one:     nextchunk = chunk_at_offset(p, size);
line 4362 is a new one:     /* Lightweight tests: check whether the block is already the
line 4363 is a new one:        top block.  */
line 4364 is a new one:     if (__builtin_expect (p == av->top, 0))
line 4366 is a new one: 	errstr = "double free or corruption (top)";
line 4367 is a new one: 	goto errout;
line 4369 is a new one:     /* Or whether the next chunk is beyond the boundaries of the arena.  */
line 4370 is a new one:     if (__builtin_expect (contiguous (av)
line 4371 is a new one: 			  && (char *) nextchunk
line 4372 is a new one: 			  >= ((char *) av->top + chunksize(av->top)), 0))
line 4374 is a new one: 	errstr = "double free or corruption (out)";
line 4375 is a new one: 	goto errout;
line 4377 is a new one:     /* Or whether the block is actually not marked used.  */
line 4378 is a new one:     if (__builtin_expect (!prev_inuse(nextchunk), 0))
line 4380 is a new one: 	errstr = "double free or corruption (!prev)";
line 4381 is a new one: 	goto errout;
line 4384 is a new one:     nextsize = chunksize(nextchunk);
line 4385 is a new one:     if (__builtin_expect (nextchunk->size <= 2 * SIZE_SZ, 0)
line 4386 is a new one: 	|| __builtin_expect (nextsize >= av->system_mem, 0))
line 4388 is a new one: 	errstr = "free(): invalid next size (normal)";
line 4389 is a new one: 	goto errout;
line 4392 is a new one:     if (__builtin_expect (perturb_byte, 0))
line 4393 is a new one:       free_perturb (mem, size - SIZE_SZ);
line 4395 is a new one:     /* consolidate backward */
line 4396 is a new one:     if (!prev_inuse(p)) {
line 4397 is a new one:       prevsize = p->prev_size;
line 4398 is a new one:       size += prevsize;
line 4399 is a new one:       p = chunk_at_offset(p, -((long) prevsize));
line 4403 is a new one:     if (nextchunk != av->top) {
line 4404 is a new one:       /* get and clear inuse bit */
line 4405 is a new one:       nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
line 4407 is a new one:       /* consolidate forward */
line 4408 is a new one:       if (!nextinuse) {
line 4409 is a new one: 	unlink(nextchunk, bck, fwd);
line 4410 is a new one: 	size += nextsize;
line 4412 is a new one: 	clear_inuse_bit_at_offset(nextchunk, 0);
line 4414 is a new one:       /*
line 4415 is a new one: 	Place the chunk in unsorted chunk list. Chunks are
line 4416 is a new one: 	not placed into regular bins until after they have
line 4417 is a new one: 	been given one chance to be used in malloc.
line 4418 is a new one:       */
line 4420 is a new one:       bck = unsorted_chunks(av);
line 4421 is a new one:       fwd = bck->fd;
line 4422 is a new one:       p->bk = bck;
line 4423 is a new one:       p->fd = fwd;
line 4424 is a new one:       bck->fd = p;
line 4425 is a new one:       fwd->bk = p;
line 4427 is a new one:       set_head(p, size | PREV_INUSE);
line 4428 is a new one:       set_foot(p, size);
line 4430 is a new one:       check_free_chunk(av, p);
line 4434 is a new one:       If the chunk borders the current high end of memory,
line 4435 is a new one:       consolidate into top
line 4439 is a new one:       size += nextsize;
line 4440 is a new one:       set_head(p, size | PREV_INUSE);
line 4441 is a new one:       av->top = p;
line 4442 is a new one:       check_chunk(av, p);
line 4446 is a new one:       If freeing a large space, consolidate possibly-surrounding
line 4447 is a new one:       chunks. Then, if the total unused topmost memory exceeds trim
line 4448 is a new one:       threshold, ask malloc_trim to reduce top.
line 4450 is a new one:       Unless max_fast is 0, we don't know if there are fastbins
line 4451 is a new one:       bordering top, so we cannot tell for sure whether threshold
line 4452 is a new one:       has been reached unless fastbins are consolidated.  But we
line 4453 is a new one:       don't want to consolidate on each free.  As a compromise,
line 4454 is a new one:       consolidation is performed if FASTBIN_CONSOLIDATION_THRESHOLD
line 4455 is a new one:       is reached.
line 4458 is a new one:     if ((unsigned long)(size) >= FASTBIN_CONSOLIDATION_THRESHOLD) {
line 4459 is a new one:       if (have_fastchunks(av))
line 4460 is a new one: 	malloc_consolidate(av);
line 4462 is a new one:       if (av == &main_arena) {
line 4463 is a new one: #ifndef MORECORE_CANNOT_TRIM
line 4464 is a new one: 	if ((unsigned long)(chunksize(av->top)) >=
line 4465 is a new one: 	    (unsigned long)(mp_.trim_threshold))
line 4466 is a new one: 	  sYSTRIm(mp_.top_pad, av);
line 4469 is a new one: 	/* Always try heap_trim(), even if the top chunk is not
line 4470 is a new one: 	   large, because the corresponding heap might go away.  */
line 4471 is a new one: 	heap_info *heap = heap_for_ptr(top(av));
line 4473 is a new one: 	assert(heap->ar_ptr == av);
line 4474 is a new one: 	heap_trim(heap, mp_.top_pad);
line 4480 is a new one:     If the chunk was allocated via mmap, release via munmap(). Note
line 4481 is a new one:     that if HAVE_MMAP is false but chunk_is_mmapped is true, then
line 4482 is a new one:     user must have overwritten memory. There's nothing we can do to
line 4483 is a new one:     catch this error unless MALLOC_DEBUG is set, in which case
line 4484 is a new one:     check_inuse_chunk (above) will have triggered error.
line 4489 is a new one:     munmap_chunk (p);
line 4495 is a new one:   ------------------------- malloc_consolidate -------------------------
line 4497 is a new one:   malloc_consolidate is a specialized version of free() that tears
line 4498 is a new one:   down chunks held in fastbins.  Free itself cannot be used for this
line 4499 is a new one:   purpose since, among other things, it might place chunks back onto
line 4500 is a new one:   fastbins.  So, instead, we need to use a minor variant of the same
line 4501 is a new one:   code.
line 4503 is a new one:   Also, because this routine needs to be called the first time through
line 4504 is a new one:   malloc anyway, it turns out to be the perfect place to trigger
line 4505 is a new one:   initialization code.
line 4509 is a new one: static void malloc_consolidate(mstate av)
line 4511 is a new one: static void malloc_consolidate(av) mstate av;
line 4514 is a new one:   mfastbinptr*    fb;                 /* current fastbin being consolidated */
line 4515 is a new one:   mfastbinptr*    maxfb;              /* last fastbin (for loop control) */
line 4516 is a new one:   mchunkptr       p;                  /* current chunk being consolidated */
line 4517 is a new one:   mchunkptr       nextp;              /* next chunk to consolidate */
line 4518 is a new one:   mchunkptr       unsorted_bin;       /* bin header */
line 4519 is a new one:   mchunkptr       first_unsorted;     /* chunk to link to */
line 4521 is a new one:   /* These have same use as in free() */
line 4522 is a new one:   mchunkptr       nextchunk;
line 4523 is a new one:   INTERNAL_SIZE_T size;
line 4524 is a new one:   INTERNAL_SIZE_T nextsize;
line 4525 is a new one:   INTERNAL_SIZE_T prevsize;
line 4526 is a new one:   int             nextinuse;
line 4527 is a new one:   mchunkptr       bck;
line 4528 is a new one:   mchunkptr       fwd;
line 4531 is a new one:     If max_fast is 0, we know that av hasn't
line 4532 is a new one:     yet been initialized, in which case do so below
line 4535 is a new one:   if (get_max_fast () != 0) {
line 4536 is a new one:     clear_fastchunks(av);
line 4538 is a new one:     unsorted_bin = unsorted_chunks(av);
line 4541 is a new one:       Remove each chunk from fast bin and consolidate it, placing it
line 4542 is a new one:       then in unsorted bin. Among other reasons for doing this,
line 4543 is a new one:       placing in unsorted bin avoids needing to calculate actual bins
line 4544 is a new one:       until malloc is sure that chunks aren't immediately going to be
line 4545 is a new one:       reused anyway.
line 4548 is a new one:     maxfb = &(av->fastbins[fastbin_index(get_max_fast ())]);
line 4549 is a new one:     fb = &(av->fastbins[0]);
line 4550 is a new one:     do {
line 4551 is a new one:       if ( (p = *fb) != 0) {
line 4552 is a new one:         *fb = 0;
line 4554 is a new one:         do {
line 4555 is a new one:           check_inuse_chunk(av, p);
line 4556 is a new one:           nextp = p->fd;
line 4558 is a new one:           /* Slightly streamlined version of consolidation code in free() */
line 4559 is a new one:           size = p->size & ~(PREV_INUSE|NON_MAIN_ARENA);
line 4560 is a new one:           nextchunk = chunk_at_offset(p, size);
line 4561 is a new one:           nextsize = chunksize(nextchunk);
line 4563 is a new one:           if (!prev_inuse(p)) {
line 4564 is a new one:             prevsize = p->prev_size;
line 4565 is a new one:             size += prevsize;
line 4566 is a new one:             p = chunk_at_offset(p, -((long) prevsize));
line 4567 is a new one:             unlink(p, bck, fwd);
line 4570 is a new one:           if (nextchunk != av->top) {
line 4571 is a new one:             nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
line 4573 is a new one:             if (!nextinuse) {
line 4574 is a new one:               size += nextsize;
line 4575 is a new one:               unlink(nextchunk, bck, fwd);
line 4576 is a new one:             } else
line 4577 is a new one: 	      clear_inuse_bit_at_offset(nextchunk, 0);
line 4579 is a new one:             first_unsorted = unsorted_bin->fd;
line 4580 is a new one:             unsorted_bin->fd = p;
line 4581 is a new one:             first_unsorted->bk = p;
line 4583 is a new one:             set_head(p, size | PREV_INUSE);
line 4584 is a new one:             p->bk = unsorted_bin;
line 4585 is a new one:             p->fd = first_unsorted;
line 4586 is a new one:             set_foot(p, size);
line 4589 is a new one:           else {
line 4590 is a new one:             size += nextsize;
line 4591 is a new one:             set_head(p, size | PREV_INUSE);
line 4592 is a new one:             av->top = p;
line 4595 is a new one:         } while ( (p = nextp) != 0);
line 4598 is a new one:     } while (fb++ != maxfb);
line 4601 is a new one:     malloc_init_state(av);
line 4602 is a new one:     check_malloc_state(av);
line 4607 is a new one:   ------------------------------ realloc ------------------------------
line 4611 is a new one: _int_realloc(mstate av, Void_t* oldmem, size_t bytes)
line 4613 is a new one:   INTERNAL_SIZE_T  nb;              /* padded request size */
line 4615 is a new one:   mchunkptr        oldp;            /* chunk corresponding to oldmem */
line 4616 is a new one:   INTERNAL_SIZE_T  oldsize;         /* its size */
line 4618 is a new one:   mchunkptr        newp;            /* chunk to return */
line 4619 is a new one:   INTERNAL_SIZE_T  newsize;         /* its size */
line 4620 is a new one:   Void_t*          newmem;          /* corresponding user mem */
line 4622 is a new one:   mchunkptr        next;            /* next contiguous chunk after oldp */
line 4624 is a new one:   mchunkptr        remainder;       /* extra space at end of newp */
line 4625 is a new one:   unsigned long    remainder_size;  /* its size */
line 4627 is a new one:   mchunkptr        bck;             /* misc temp for linking */
line 4628 is a new one:   mchunkptr        fwd;             /* misc temp for linking */
line 4630 is a new one:   unsigned long    copysize;        /* bytes to copy */
line 4631 is a new one:   unsigned int     ncopies;         /* INTERNAL_SIZE_T words to copy */
line 4632 is a new one:   INTERNAL_SIZE_T* s;               /* copy source */
line 4633 is a new one:   INTERNAL_SIZE_T* d;               /* copy destination */
line 4635 is a new one:   const char *errstr = NULL;
line 4638 is a new one:   checked_request2size(bytes, nb);
line 4643 is a new one:   /* Simple tests for old block integrity.  */
line 4644 is a new one:   if (__builtin_expect (misaligned_chunk (oldp), 0))
line 4646 is a new one:       errstr = "realloc(): invalid pointer";
line 4647 is a new one:     errout:
line 4648 is a new one:       malloc_printerr (check_action, errstr, oldmem);
line 4651 is a new one:   if (__builtin_expect (oldp->size <= 2 * SIZE_SZ, 0)
line 4652 is a new one:       || __builtin_expect (oldsize >= av->system_mem, 0))
line 4654 is a new one:       errstr = "realloc(): invalid old size";
line 4655 is a new one:       goto errout;
line 4658 is a new one:   check_inuse_chunk(av, oldp);
line 4660 is a new one:   if (!chunk_is_mmapped(oldp)) {
line 4663 is a new one:     INTERNAL_SIZE_T nextsize = chunksize(next);
line 4664 is a new one:     if (__builtin_expect (next->size <= 2 * SIZE_SZ, 0)
line 4665 is a new one: 	|| __builtin_expect (nextsize >= av->system_mem, 0))
line 4667 is a new one: 	errstr = "realloc(): invalid next size";
line 4668 is a new one: 	goto errout;
line 4671 is a new one:     if ((unsigned long)(oldsize) >= (unsigned long)(nb)) {
line 4672 is a new one:       /* already big enough; split below */
line 4674 is a new one:       newsize = oldsize;
line 4678 is a new one:       /* Try to expand forward into top */
line 4679 is a new one:       if (next == av->top &&
line 4680 is a new one:           (unsigned long)(newsize = oldsize + nextsize) >=
line 4681 is a new one:           (unsigned long)(nb + MINSIZE)) {
line 4682 is a new one:         set_head_size(oldp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4683 is a new one:         av->top = chunk_at_offset(oldp, nb);
line 4684 is a new one:         set_head(av->top, (newsize - nb) | PREV_INUSE);
line 4685 is a new one: 	check_inuse_chunk(av, oldp);
line 4686 is a new one:         return chunk2mem(oldp);
line 4689 is a new one:       /* Try to expand forward into next chunk;  split off remainder below */
line 4690 is a new one:       else if (next != av->top &&
line 4691 is a new one:                !inuse(next) &&
line 4692 is a new one:                (unsigned long)(newsize = oldsize + nextsize) >=
line 4693 is a new one:                (unsigned long)(nb)) {
line 4694 is a new one:         newp = oldp;
line 4698 is a new one:       /* allocate, copy, free */
line 4700 is a new one:         newmem = _int_malloc(av, nb - MALLOC_ALIGN_MASK);
line 4701 is a new one:         if (newmem == 0)
line 4702 is a new one:           return 0; /* propagate failure */
line 4704 is a new one:         newp = mem2chunk(newmem);
line 4705 is a new one:         newsize = chunksize(newp);
line 4707 is a new one:         /*
line 4708 is a new one:           Avoid copy if newp is next chunk after oldp.
line 4709 is a new one:         */
line 4710 is a new one:         if (newp == next) {
line 4711 is a new one:           newsize += oldsize;
line 4712 is a new one:           newp = oldp;
line 4714 is a new one:         else {
line 4715 is a new one:           /*
line 4716 is a new one:             Unroll copy of <= 36 bytes (72 if 8byte sizes)
line 4717 is a new one:             We know that contents have an odd number of
line 4718 is a new one:             INTERNAL_SIZE_T-sized words; minimally 3.
line 4719 is a new one:           */
line 4721 is a new one:           copysize = oldsize - SIZE_SZ;
line 4722 is a new one:           s = (INTERNAL_SIZE_T*)(oldmem);
line 4723 is a new one:           d = (INTERNAL_SIZE_T*)(newmem);
line 4724 is a new one:           ncopies = copysize / sizeof(INTERNAL_SIZE_T);
line 4725 is a new one:           assert(ncopies >= 3);
line 4727 is a new one:           if (ncopies > 9)
line 4728 is a new one:             MALLOC_COPY(d, s, copysize);
line 4730 is a new one:           else {
line 4731 is a new one:             *(d+0) = *(s+0);
line 4732 is a new one:             *(d+1) = *(s+1);
line 4733 is a new one:             *(d+2) = *(s+2);
line 4734 is a new one:             if (ncopies > 4) {
line 4735 is a new one:               *(d+3) = *(s+3);
line 4736 is a new one:               *(d+4) = *(s+4);
line 4737 is a new one:               if (ncopies > 6) {
line 4738 is a new one:                 *(d+5) = *(s+5);
line 4739 is a new one:                 *(d+6) = *(s+6);
line 4740 is a new one:                 if (ncopies > 8) {
line 4741 is a new one:                   *(d+7) = *(s+7);
line 4742 is a new one:                   *(d+8) = *(s+8);
line 4743 is a new one:                 }
line 4744 is a new one:               }
line 4745 is a new one:             }
line 4748 is a new one:           _int_free(av, oldmem);
line 4749 is a new one:           check_inuse_chunk(av, newp);
line 4750 is a new one:           return chunk2mem(newp);
line 4755 is a new one:     /* If possible, free extra space in old or extended chunk */
line 4757 is a new one:     assert((unsigned long)(newsize) >= (unsigned long)(nb));
line 4761 is a new one:     if (remainder_size < MINSIZE) { /* not enough extra to split off */
line 4762 is a new one:       set_head_size(newp, newsize | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4763 is a new one:       set_inuse_bit_at_offset(newp, newsize);
line 4765 is a new one:     else { /* split remainder */
line 4766 is a new one:       remainder = chunk_at_offset(newp, nb);
line 4767 is a new one:       set_head_size(newp, nb | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4768 is a new one:       set_head(remainder, remainder_size | PREV_INUSE |
line 4769 is a new one: 	       (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4770 is a new one:       /* Mark remainder as inuse so free() won't complain */
line 4771 is a new one:       set_inuse_bit_at_offset(remainder, remainder_size);
line 4772 is a new one:       _int_free(av, chunk2mem(remainder));
line 4775 is a new one:     check_inuse_chunk(av, newp);
line 4776 is a new one:     return chunk2mem(newp);
line 4780 is a new one:     Handle mmap cases
line 4787 is a new one:     INTERNAL_SIZE_T offset = oldp->prev_size;
line 4788 is a new one:     size_t pagemask = mp_.pagesize - 1;
line 4789 is a new one:     char *cp;
line 4790 is a new one:     unsigned long sum;
line 4792 is a new one:     /* Note the extra SIZE_SZ overhead */
line 4793 is a new one:     newsize = (nb + offset + SIZE_SZ + pagemask) & ~pagemask;
line 4795 is a new one:     /* don't need to remap if still within same page */
line 4796 is a new one:     if (oldsize == newsize - offset)
line 4797 is a new one:       return oldmem;
line 4799 is a new one:     cp = (char*)mremap((char*)oldp - offset, oldsize + offset, newsize, 1);
line 4801 is a new one:     if (cp != MAP_FAILED) {
line 4803 is a new one:       newp = (mchunkptr)(cp + offset);
line 4804 is a new one:       set_head(newp, (newsize - offset)|IS_MMAPPED);
line 4806 is a new one:       assert(aligned_OK(chunk2mem(newp)));
line 4807 is a new one:       assert((newp->prev_size == offset));
line 4809 is a new one:       /* update statistics */
line 4810 is a new one:       sum = mp_.mmapped_mem += newsize - oldsize;
line 4811 is a new one:       if (sum > (unsigned long)(mp_.max_mmapped_mem))
line 4812 is a new one:         mp_.max_mmapped_mem = sum;
line 4814 is a new one:       sum += main_arena.system_mem;
line 4815 is a new one:       if (sum > (unsigned long)(mp_.max_total_mem))
line 4816 is a new one:         mp_.max_total_mem = sum;
line 4819 is a new one:       return chunk2mem(newp);
line 4824 is a new one:     if ((unsigned long)(oldsize) >= (unsigned long)(nb + SIZE_SZ))
line 4825 is a new one:       newmem = oldmem; /* do nothing */
line 4827 is a new one:       /* Must alloc, copy, free. */
line 4828 is a new one:       newmem = _int_malloc(av, nb - MALLOC_ALIGN_MASK);
line 4829 is a new one:       if (newmem != 0) {
line 4830 is a new one:         MALLOC_COPY(newmem, oldmem, oldsize - 2*SIZE_SZ);
line 4831 is a new one:         _int_free(av, oldmem);
line 4837 is a new one:     /* If !HAVE_MMAP, but chunk_is_mmapped, user must have overwritten mem */
line 4838 is a new one:     check_malloc_state(av);
line 4839 is a new one:     MALLOC_FAILURE_ACTION;
line 4846 is a new one:   ------------------------------ memalign ------------------------------
line 4850 is a new one: _int_memalign(mstate av, size_t alignment, size_t bytes)
line 4852 is a new one:   INTERNAL_SIZE_T nb;             /* padded  request size */
line 4853 is a new one:   char*           m;              /* memory returned by malloc call */
line 4854 is a new one:   mchunkptr       p;              /* corresponding chunk */
line 4855 is a new one:   char*           brk;            /* alignment point within p */
line 4856 is a new one:   mchunkptr       newp;           /* chunk to return */
line 4857 is a new one:   INTERNAL_SIZE_T newsize;        /* its size */
line 4858 is a new one:   INTERNAL_SIZE_T leadsize;       /* leading space before alignment point */
line 4859 is a new one:   mchunkptr       remainder;      /* spare room at end to split off */
line 4860 is a new one:   unsigned long   remainder_size; /* its size */
line 4861 is a new one:   INTERNAL_SIZE_T size;
line 4865 is a new one:   if (alignment <= MALLOC_ALIGNMENT) return _int_malloc(av, bytes);
line 4871 is a new one:   /* Make sure alignment is power of 2 (in case MINSIZE is not).  */
line 4872 is a new one:   if ((alignment & (alignment - 1)) != 0) {
line 4873 is a new one:     size_t a = MALLOC_ALIGNMENT * 2;
line 4874 is a new one:     while ((unsigned long)a < (unsigned long)alignment) a <<= 1;
line 4875 is a new one:     alignment = a;
line 4878 is a new one:   checked_request2size(bytes, nb);
line 4881 is a new one:     Strategy: find a spot within that chunk that meets the alignment
line 4882 is a new one:     request, and then possibly free the leading and trailing space.
line 4886 is a new one:   /* Call malloc with worst case padding to hit alignment. */
line 4888 is a new one:   m  = (char*)(_int_malloc(av, nb + alignment + MINSIZE));
line 4890 is a new one:   if (m == 0) return 0; /* propagate failure */
line 4892 is a new one:   p = mem2chunk(m);
line 4894 is a new one:   if ((((unsigned long)(m)) % alignment) != 0) { /* misaligned */
line 4897 is a new one:       Find an aligned spot inside chunk.  Since we need to give back
line 4898 is a new one:       leading space in a chunk of at least MINSIZE, if the first
line 4899 is a new one:       calculation places us at a spot with less than MINSIZE leader,
line 4900 is a new one:       we can move to the next aligned spot -- we've allocated enough
line 4901 is a new one:       total room so that this is always possible.
line 4904 is a new one:     brk = (char*)mem2chunk(((unsigned long)(m + alignment - 1)) &
line 4905 is a new one:                            -((signed long) alignment));
line 4906 is a new one:     if ((unsigned long)(brk - (char*)(p)) < MINSIZE)
line 4907 is a new one:       brk += alignment;
line 4909 is a new one:     newp = (mchunkptr)brk;
line 4913 is a new one:     /* For mmapped chunks, just adjust offset */
line 4914 is a new one:     if (chunk_is_mmapped(p)) {
line 4917 is a new one:       return chunk2mem(newp);
line 4920 is a new one:     /* Otherwise, give back leader, use the rest */
line 4921 is a new one:     set_head(newp, newsize | PREV_INUSE |
line 4922 is a new one: 	     (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4924 is a new one:     set_head_size(p, leadsize | (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4925 is a new one:     _int_free(av, chunk2mem(p));
line 4928 is a new one:     assert (newsize >= nb &&
line 4929 is a new one:             (((unsigned long)(chunk2mem(p))) % alignment) == 0);
line 4933 is a new one:   if (!chunk_is_mmapped(p)) {
line 4934 is a new one:     size = chunksize(p);
line 4935 is a new one:     if ((unsigned long)(size) > (unsigned long)(nb + MINSIZE)) {
line 4936 is a new one:       remainder_size = size - nb;
line 4937 is a new one:       remainder = chunk_at_offset(p, nb);
line 4938 is a new one:       set_head(remainder, remainder_size | PREV_INUSE |
line 4939 is a new one: 	       (av != &main_arena ? NON_MAIN_ARENA : 0));
line 4940 is a new one:       set_head_size(p, nb);
line 4941 is a new one:       _int_free(av, chunk2mem(remainder));
line 4945 is a new one:   check_inuse_chunk(av, p);
line 4946 is a new one:   return chunk2mem(p);
line 4951 is a new one:   ------------------------------ calloc ------------------------------
line 4955 is a new one: Void_t* cALLOc(size_t n_elements, size_t elem_size)
line 4957 is a new one: Void_t* cALLOc(n_elements, elem_size) size_t n_elements; size_t elem_size;
line 4961 is a new one:   unsigned long clearsize;
line 4962 is a new one:   unsigned long nclears;
line 4963 is a new one:   INTERNAL_SIZE_T* d;
line 4965 is a new one:   Void_t* mem = mALLOc(n_elements * elem_size);
line 4967 is a new one:   if (mem != 0) {
line 4970 is a new one: #if MMAP_CLEARS
line 4971 is a new one:     if (!chunk_is_mmapped(p)) /* don't need to clear mmapped space */
line 4974 is a new one:       /*
line 4975 is a new one:         Unroll clear of <= 36 bytes (72 if 8byte sizes)
line 4976 is a new one:         We know that contents have an odd number of
line 4977 is a new one:         INTERNAL_SIZE_T-sized words; minimally 3.
line 4978 is a new one:       */
line 4980 is a new one:       d = (INTERNAL_SIZE_T*)mem;
line 4981 is a new one:       clearsize = chunksize(p) - SIZE_SZ;
line 4982 is a new one:       nclears = clearsize / sizeof(INTERNAL_SIZE_T);
line 4983 is a new one:       assert(nclears >= 3);
line 4985 is a new one:       if (nclears > 9)
line 4986 is a new one:         MALLOC_ZERO(d, clearsize);
line 4989 is a new one:         *(d+0) = 0;
line 4990 is a new one:         *(d+1) = 0;
line 4991 is a new one:         *(d+2) = 0;
line 4992 is a new one:         if (nclears > 4) {
line 4993 is a new one:           *(d+3) = 0;
line 4994 is a new one:           *(d+4) = 0;
line 4995 is a new one:           if (nclears > 6) {
line 4996 is a new one:             *(d+5) = 0;
line 4997 is a new one:             *(d+6) = 0;
line 4998 is a new one:             if (nclears > 8) {
line 4999 is a new one:               *(d+7) = 0;
line 5000 is a new one:               *(d+8) = 0;
line 5001 is a new one:             }
line 5009 is a new one: #endif /* 0 */
line 5013 is a new one:   ------------------------- independent_calloc -------------------------
line 5016 is a new one: Void_t**
line 5018 is a new one: _int_icalloc(mstate av, size_t n_elements, size_t elem_size, Void_t* chunks[])
line 5020 is a new one: _int_icalloc(av, n_elements, elem_size, chunks)
line 5021 is a new one: mstate av; size_t n_elements; size_t elem_size; Void_t* chunks[];
line 5024 is a new one:   size_t sz = elem_size; /* serves as 1-element array */
line 5025 is a new one:   /* opts arg of 3 means all elements are same size, and should be cleared */
line 5026 is a new one:   return iALLOc(av, n_elements, &sz, 3, chunks);
line 5030 is a new one:   ------------------------- independent_comalloc -------------------------
line 5033 is a new one: Void_t**
line 5035 is a new one: _int_icomalloc(mstate av, size_t n_elements, size_t sizes[], Void_t* chunks[])
line 5037 is a new one: _int_icomalloc(av, n_elements, sizes, chunks)
line 5038 is a new one: mstate av; size_t n_elements; size_t sizes[]; Void_t* chunks[];
line 5041 is a new one:   return iALLOc(av, n_elements, sizes, 0, chunks);
line 5046 is a new one:   ------------------------------ ialloc ------------------------------
line 5047 is a new one:   ialloc provides common support for independent_X routines, handling all of
line 5048 is a new one:   the combinations that can result.
line 5050 is a new one:   The opts arg has:
line 5051 is a new one:     bit 0 set if all elements are same size (using sizes[0])
line 5052 is a new one:     bit 1 set if elements should be zeroed
line 5056 is a new one: static Void_t**
line 5058 is a new one: iALLOc(mstate av, size_t n_elements, size_t* sizes, int opts, Void_t* chunks[])
line 5060 is a new one: iALLOc(av, n_elements, sizes, opts, chunks)
line 5061 is a new one: mstate av; size_t n_elements; size_t* sizes; int opts; Void_t* chunks[];
line 5064 is a new one:   INTERNAL_SIZE_T element_size;   /* chunksize of each element, if all same */
line 5065 is a new one:   INTERNAL_SIZE_T contents_size;  /* total size of elements */
line 5066 is a new one:   INTERNAL_SIZE_T array_size;     /* request size of pointer array */
line 5067 is a new one:   Void_t*         mem;            /* malloced aggregate space */
line 5068 is a new one:   mchunkptr       p;              /* corresponding chunk */
line 5069 is a new one:   INTERNAL_SIZE_T remainder_size; /* remaining bytes while splitting */
line 5070 is a new one:   Void_t**        marray;         /* either "chunks" or malloced ptr array */
line 5071 is a new one:   mchunkptr       array_chunk;    /* chunk for malloced ptr array */
line 5072 is a new one:   int             mmx;            /* to disable mmap */
line 5073 is a new one:   INTERNAL_SIZE_T size;
line 5074 is a new one:   INTERNAL_SIZE_T size_flags;
line 5075 is a new one:   size_t          i;
line 5077 is a new one:   /* Ensure initialization/consolidation */
line 5078 is a new one:   if (have_fastchunks(av)) malloc_consolidate(av);
line 5080 is a new one:   /* compute array length, if needed */
line 5081 is a new one:   if (chunks != 0) {
line 5082 is a new one:     if (n_elements == 0)
line 5083 is a new one:       return chunks; /* nothing to do */
line 5084 is a new one:     marray = chunks;
line 5085 is a new one:     array_size = 0;
line 5088 is a new one:     /* if empty req, must still return chunk representing empty array */
line 5089 is a new one:     if (n_elements == 0)
line 5090 is a new one:       return (Void_t**) _int_malloc(av, 0);
line 5091 is a new one:     marray = 0;
line 5092 is a new one:     array_size = request2size(n_elements * (sizeof(Void_t*)));
line 5095 is a new one:   /* compute total element size */
line 5096 is a new one:   if (opts & 0x1) { /* all-same-size */
line 5097 is a new one:     element_size = request2size(*sizes);
line 5098 is a new one:     contents_size = n_elements * element_size;
line 5100 is a new one:   else { /* add up all the sizes */
line 5101 is a new one:     element_size = 0;
line 5102 is a new one:     contents_size = 0;
line 5103 is a new one:     for (i = 0; i != n_elements; ++i)
line 5104 is a new one:       contents_size += request2size(sizes[i]);
line 5107 is a new one:   /* subtract out alignment bytes from total to minimize overallocation */
line 5108 is a new one:   size = contents_size + array_size - MALLOC_ALIGN_MASK;
line 5111 is a new one:      Allocate the aggregate chunk.
line 5112 is a new one:      But first disable mmap so malloc won't use it, since
line 5113 is a new one:      we would not be able to later free/realloc space internal
line 5114 is a new one:      to a segregated mmap region.
line 5116 is a new one:   mmx = mp_.n_mmaps_max;   /* disable mmap */
line 5117 is a new one:   mp_.n_mmaps_max = 0;
line 5118 is a new one:   mem = _int_malloc(av, size);
line 5119 is a new one:   mp_.n_mmaps_max = mmx;   /* reset mmap */
line 5125 is a new one:   remainder_size = chunksize(p);
line 5127 is a new one:   if (opts & 0x2) {       /* optionally clear the elements */
line 5128 is a new one:     MALLOC_ZERO(mem, remainder_size - SIZE_SZ - array_size);
line 5131 is a new one:   size_flags = PREV_INUSE | (av != &main_arena ? NON_MAIN_ARENA : 0);
line 5133 is a new one:   /* If not provided, allocate the pointer array as final part of chunk */
line 5134 is a new one:   if (marray == 0) {
line 5135 is a new one:     array_chunk = chunk_at_offset(p, contents_size);
line 5136 is a new one:     marray = (Void_t**) (chunk2mem(array_chunk));
line 5137 is a new one:     set_head(array_chunk, (remainder_size - contents_size) | size_flags);
line 5138 is a new one:     remainder_size = contents_size;
line 5141 is a new one:   /* split out elements */
line 5142 is a new one:   for (i = 0; ; ++i) {
line 5143 is a new one:     marray[i] = chunk2mem(p);
line 5144 is a new one:     if (i != n_elements-1) {
line 5145 is a new one:       if (element_size != 0)
line 5146 is a new one:         size = element_size;
line 5148 is a new one:         size = request2size(sizes[i]);
line 5149 is a new one:       remainder_size -= size;
line 5150 is a new one:       set_head(p, size | size_flags);
line 5151 is a new one:       p = chunk_at_offset(p, size);
line 5153 is a new one:     else { /* the final element absorbs any overallocation slop */
line 5154 is a new one:       set_head(p, remainder_size | size_flags);
line 5160 is a new one:   if (marray != chunks) {
line 5161 is a new one:     /* final element must have exactly exhausted chunk */
line 5162 is a new one:     if (element_size != 0)
line 5163 is a new one:       assert(remainder_size == element_size);
line 5165 is a new one:       assert(remainder_size == request2size(sizes[i]));
line 5166 is a new one:     check_inuse_chunk(av, mem2chunk(marray));
line 5169 is a new one:   for (i = 0; i != n_elements; ++i)
line 5170 is a new one:     check_inuse_chunk(av, mem2chunk(marray[i]));
line 5173 is a new one:   return marray;
line 5179 is a new one:   ------------------------------ valloc ------------------------------
line 5184 is a new one: _int_valloc(mstate av, size_t bytes)
line 5186 is a new one: _int_valloc(av, bytes) mstate av; size_t bytes;
line 5189 is a new one:   /* Ensure initialization/consolidation */
line 5190 is a new one:   if (have_fastchunks(av)) malloc_consolidate(av);
line 5191 is a new one:   return _int_memalign(av, mp_.pagesize, bytes);
line 5195 is a new one:   ------------------------------ pvalloc ------------------------------
line 5201 is a new one: _int_pvalloc(mstate av, size_t bytes)
line 5203 is a new one: _int_pvalloc(av, bytes) mstate av, size_t bytes;
line 5206 is a new one:   size_t pagesz;
line 5208 is a new one:   /* Ensure initialization/consolidation */
line 5209 is a new one:   if (have_fastchunks(av)) malloc_consolidate(av);
line 5210 is a new one:   pagesz = mp_.pagesize;
line 5211 is a new one:   return _int_memalign(av, pagesz, (bytes + pagesz - 1) & ~(pagesz - 1));
line 5216 is a new one:   ------------------------------ malloc_trim ------------------------------
line 5220 is a new one: int mTRIm(size_t pad)
line 5222 is a new one: int mTRIm(pad) size_t pad;
line 5225 is a new one:   mstate av = &main_arena; /* already locked */
line 5227 is a new one:   /* Ensure initialization/consolidation */
line 5228 is a new one:   malloc_consolidate(av);
line 5230 is a new one: #ifndef MORECORE_CANNOT_TRIM
line 5231 is a new one:   return sYSTRIm(pad, av);
line 5239 is a new one:   ------------------------- malloc_usable_size -------------------------
line 5243 is a new one: size_t mUSABLe(Void_t* mem)
line 5245 is a new one: size_t mUSABLe(mem) Void_t* mem;
line 5249 is a new one:   if (mem != 0) {
line 5251 is a new one:     if (chunk_is_mmapped(p))
line 5252 is a new one:       return chunksize(p) - 2*SIZE_SZ;
line 5253 is a new one:     else if (inuse(p))
line 5260 is a new one:   ------------------------------ mallinfo ------------------------------
line 5263 is a new one: struct mallinfo mALLINFo(mstate av)
line 5270 is a new one:   INTERNAL_SIZE_T fastavail;
line 5271 is a new one:   int nblocks;
line 5272 is a new one:   int nfastblocks;
line 5274 is a new one:   /* Ensure initialization */
line 5275 is a new one:   if (av->top == 0)  malloc_consolidate(av);
line 5277 is a new one:   check_malloc_state(av);
line 5279 is a new one:   /* Account for top */
line 5280 is a new one:   avail = chunksize(av->top);
line 5281 is a new one:   nblocks = 1;  /* top always exists */
line 5283 is a new one:   /* traverse fastbins */
line 5284 is a new one:   nfastblocks = 0;
line 5285 is a new one:   fastavail = 0;
line 5287 is a new one:   for (i = 0; i < NFASTBINS; ++i) {
line 5288 is a new one:     for (p = av->fastbins[i]; p != 0; p = p->fd) {
line 5289 is a new one:       ++nfastblocks;
line 5290 is a new one:       fastavail += chunksize(p);
line 5294 is a new one:   avail += fastavail;
line 5296 is a new one:   /* traverse regular bins */
line 5297 is a new one:   for (i = 1; i < NBINS; ++i) {
line 5298 is a new one:     b = bin_at(av, i);
line 5299 is a new one:     for (p = last(b); p != b; p = p->bk) {
line 5300 is a new one:       ++nblocks;
line 5305 is a new one:   mi.smblks = nfastblocks;
line 5306 is a new one:   mi.ordblks = nblocks;
line 5307 is a new one:   mi.fordblks = avail;
line 5308 is a new one:   mi.uordblks = av->system_mem - avail;
line 5309 is a new one:   mi.arena = av->system_mem;
line 5310 is a new one:   mi.hblks = mp_.n_mmaps;
line 5311 is a new one:   mi.hblkhd = mp_.mmapped_mem;
line 5312 is a new one:   mi.fsmblks = fastavail;
line 5313 is a new one:   mi.keepcost = chunksize(av->top);
line 5314 is a new one:   mi.usmblks = mp_.max_total_mem;
line 5319 is a new one:   ------------------------------ malloc_stats ------------------------------
line 5322 is a new one: void mSTATs()
line 5325 is a new one:   mstate ar_ptr;
line 5327 is a new one:   unsigned int in_use_b = mp_.mmapped_mem, system_b = in_use_b;
line 5335 is a new one:   _IO_flockfile (stderr);
line 5336 is a new one:   int old_flags2 = ((_IO_FILE *) stderr)->_flags2;
line 5337 is a new one:   ((_IO_FILE *) stderr)->_flags2 |= _IO_FLAGS2_NOTCANCEL;
line 5339 is a new one:   for (i=0, ar_ptr = &main_arena;; i++) {
line 5341 is a new one:     mi = mALLINFo(ar_ptr);
line 5345 is a new one: #if MALLOC_DEBUG > 1
line 5346 is a new one:     if (i > 0)
line 5347 is a new one:       dump_heap(heap_for_ptr(top(ar_ptr)));
line 5368 is a new one:   fprintf(stderr, "max system bytes = %10u\n", (unsigned int)mp_.max_total_mem);
line 5371 is a new one:   fprintf(stderr, "max mmap regions = %10u\n", (unsigned int)mp_.max_n_mmaps);
line 5372 is a new one:   fprintf(stderr, "max mmap bytes   = %10lu\n",
line 5373 is a new one: 	  (unsigned long)mp_.max_mmapped_mem);
line 5384 is a new one:   ((_IO_FILE *) stderr)->_flags2 |= old_flags2;
line 5385 is a new one:   _IO_funlockfile (stderr);
line 5391 is a new one:   ------------------------------ mallopt ------------------------------
line 5400 is a new one:   mstate av = &main_arena;
line 5401 is a new one:   int res = 1;
line 5405 is a new one:   (void)mutex_lock(&av->mutex);
line 5406 is a new one:   /* Ensure initialization/consolidation */
line 5407 is a new one:   malloc_consolidate(av);
line 5409 is a new one:   switch(param_number) {
line 5410 is a new one:   case M_MXFAST:
line 5411 is a new one:     if (value >= 0 && value <= MAX_FAST_SIZE) {
line 5412 is a new one:       set_max_fast(value);
line 5415 is a new one:       res = 0;
line 5416 is a new one:     break;
line 5418 is a new one:   case M_TRIM_THRESHOLD:
line 5419 is a new one:     mp_.trim_threshold = value;
line 5420 is a new one:     break;
line 5422 is a new one:   case M_TOP_PAD:
line 5423 is a new one:     mp_.top_pad = value;
line 5424 is a new one:     break;
line 5426 is a new one:   case M_MMAP_THRESHOLD:
line 5428 is a new one:     /* Forbid setting the threshold too high. */
line 5429 is a new one:     if((unsigned long)value > HEAP_MAX_SIZE/2)
line 5430 is a new one:       res = 0;
line 5433 is a new one:       mp_.mmap_threshold = value;
line 5434 is a new one:     break;
line 5436 is a new one:   case M_MMAP_MAX:
line 5437 is a new one: #if !HAVE_MMAP
line 5438 is a new one:     if (value != 0)
line 5439 is a new one:       res = 0;
line 5442 is a new one:       mp_.n_mmaps_max = value;
line 5443 is a new one:     break;
line 5445 is a new one:   case M_CHECK_ACTION:
line 5446 is a new one:     check_action = value;
line 5447 is a new one:     break;
line 5449 is a new one:   case M_PERTURB:
line 5450 is a new one:     perturb_byte = value;
line 5451 is a new one:     break;
line 5453 is a new one:   (void)mutex_unlock(&av->mutex);
line 5459 is a new one:   -------------------- Alternative MORECORE functions --------------------
line 5464 is a new one:   General Requirements for MORECORE.
line 5466 is a new one:   The MORECORE function must have the following properties:
line 5468 is a new one:   If MORECORE_CONTIGUOUS is false:
line 5470 is a new one:     * MORECORE must allocate in multiples of pagesize. It will
line 5471 is a new one:       only be called with arguments that are multiples of pagesize.
line 5473 is a new one:     * MORECORE(0) must return an address that is at least
line 5474 is a new one:       MALLOC_ALIGNMENT aligned. (Page-aligning always suffices.)
line 5476 is a new one:   else (i.e. If MORECORE_CONTIGUOUS is true):
line 5478 is a new one:     * Consecutive calls to MORECORE with positive arguments
line 5479 is a new one:       return increasing addresses, indicating that space has been
line 5480 is a new one:       contiguously extended.
line 5482 is a new one:     * MORECORE need not allocate in multiples of pagesize.
line 5483 is a new one:       Calls to MORECORE need not have args of multiples of pagesize.
line 5485 is a new one:     * MORECORE need not page-align.
line 5487 is a new one:   In either case:
line 5489 is a new one:     * MORECORE may allocate more memory than requested. (Or even less,
line 5490 is a new one:       but this will generally result in a malloc failure.)
line 5492 is a new one:     * MORECORE must not allocate memory when given argument zero, but
line 5493 is a new one:       instead return one past the end address of memory from previous
line 5494 is a new one:       nonzero call. This malloc does NOT call MORECORE(0)
line 5495 is a new one:       until at least one call with positive arguments is made, so
line 5496 is a new one:       the initial value returned is not important.
line 5498 is a new one:     * Even though consecutive calls to MORECORE need not return contiguous
line 5499 is a new one:       addresses, it must be OK for malloc'ed chunks to span multiple
line 5500 is a new one:       regions in those cases where they do happen to be contiguous.
line 5502 is a new one:     * MORECORE need not handle negative arguments -- it may instead
line 5503 is a new one:       just return MORECORE_FAILURE when given negative arguments.
line 5504 is a new one:       Negative arguments are always multiples of pagesize. MORECORE
line 5505 is a new one:       must not misinterpret negative args as large positive unsigned
line 5506 is a new one:       args. You can suppress all such calls from even occurring by defining
line 5507 is a new one:       MORECORE_CANNOT_TRIM,
line 5509 is a new one:   There is some variation across systems about the type of the
line 5510 is a new one:   argument to sbrk/MORECORE. If size_t is unsigned, then it cannot
line 5511 is a new one:   actually be size_t, because sbrk supports negative args, so it is
line 5512 is a new one:   normally the signed type of the same width as size_t (sometimes
line 5513 is a new one:   declared as "intptr_t", and sometimes "ptrdiff_t").  It doesn't much
line 5514 is a new one:   matter though. Internally, we use "long" as arguments, which should
line 5515 is a new one:   work across all reasonable possibilities.
line 5517 is a new one:   Additionally, if MORECORE ever returns failure for a positive
line 5518 is a new one:   request, and HAVE_MMAP is true, then mmap is used as a noncontiguous
line 5519 is a new one:   system allocator. This is a useful backup strategy for systems with
line 5520 is a new one:   holes in address spaces -- in this case sbrk cannot contiguously
line 5521 is a new one:   expand the heap, but mmap may be able to map noncontiguous space.
line 5523 is a new one:   If you'd like mmap to ALWAYS be used, you can define MORECORE to be
line 5524 is a new one:   a function that always returns MORECORE_FAILURE.
line 5526 is a new one:   If you are using this malloc with something other than sbrk (or its
line 5527 is a new one:   emulation) to supply memory regions, you probably want to set
line 5528 is a new one:   MORECORE_CONTIGUOUS as false.  As an example, here is a custom
line 5529 is a new one:   allocator kindly contributed for pre-OSX macOS.  It uses virtually
line 5530 is a new one:   but not necessarily physically contiguous non-paged memory (locked
line 5531 is a new one:   in, present and won't get swapped out).  You can use it by
line 5532 is a new one:   uncommenting this section, adding some #includes, and setting up the
line 5533 is a new one:   appropriate defines above:
line 5535 is a new one:       #define MORECORE osMoreCore
line 5536 is a new one:       #define MORECORE_CONTIGUOUS 0
line 5538 is a new one:   There is also a shutdown routine that should somehow be called for
line 5539 is a new one:   cleanup upon program exit.
line 5541 is a new one:   #define MAX_POOL_ENTRIES 100
line 5542 is a new one:   #define MINIMUM_MORECORE_SIZE  (64 * 1024)
line 5543 is a new one:   static int next_os_pool;
line 5544 is a new one:   void *our_os_pools[MAX_POOL_ENTRIES];
line 5546 is a new one:   void *osMoreCore(int size)
line 5548 is a new one:     void *ptr = 0;
line 5549 is a new one:     static void *sbrk_top = 0;
line 5551 is a new one:     if (size > 0)
line 5553 is a new one:       if (size < MINIMUM_MORECORE_SIZE)
line 5554 is a new one:          size = MINIMUM_MORECORE_SIZE;
line 5555 is a new one:       if (CurrentExecutionLevel() == kTaskLevel)
line 5556 is a new one:          ptr = PoolAllocateResident(size + RM_PAGE_SIZE, 0);
line 5557 is a new one:       if (ptr == 0)
line 5559 is a new one:         return (void *) MORECORE_FAILURE;
line 5561 is a new one:       // save ptrs so they can be freed during cleanup
line 5562 is a new one:       our_os_pools[next_os_pool] = ptr;
line 5563 is a new one:       next_os_pool++;
line 5564 is a new one:       ptr = (void *) ((((unsigned long) ptr) + RM_PAGE_MASK) & ~RM_PAGE_MASK);
line 5565 is a new one:       sbrk_top = (char *) ptr + size;
line 5566 is a new one:       return ptr;
line 5568 is a new one:     else if (size < 0)
line 5570 is a new one:       // we don't currently support shrink behavior
line 5571 is a new one:       return (void *) MORECORE_FAILURE;
line 5575 is a new one:       return sbrk_top;
line 5579 is a new one:   // cleanup any allocated memory pools
line 5580 is a new one:   // called as last thing before shutting down driver
line 5582 is a new one:   void osCleanupMem(void)
line 5584 is a new one:     void **ptr;
line 5586 is a new one:     for (ptr = our_os_pools; ptr < &our_os_pools[MAX_POOL_ENTRIES]; ptr++)
line 5587 is a new one:       if (*ptr)
line 5589 is a new one:          PoolDeallocate(*ptr);
line 5590 is a new one:          *ptr = 0;
line 5597 is a new one: /* Helper code.  */
line 5599 is a new one: extern char **__libc_argv attribute_hidden;
line 5602 is a new one: malloc_printerr(int action, const char *str, void *ptr)
line 5604 is a new one:   if ((action & 5) == 5)
line 5605 is a new one:     __libc_message (action & 2, "%s\n", str);
line 5606 is a new one:   else if (action & 1)
line 5608 is a new one:       char buf[2 * sizeof (uintptr_t) + 1];
line 5610 is a new one:       buf[sizeof (buf) - 1] = '\0';
line 5611 is a new one:       char *cp = _itoa_word ((uintptr_t) ptr, &buf[sizeof (buf) - 1], 16, 0);
line 5612 is a new one:       while (cp > buf)
line 5613 is a new one: 	*--cp = '0';
line 5615 is a new one:       __libc_message (action & 2,
line 5616 is a new one: 		      "*** glibc detected *** %s: %s: 0x%s ***\n",
line 5617 is a new one: 		      __libc_argv[0] ?: "<unknown>", str, cp);
line 5619 is a new one:   else if (action & 2)
line 5620 is a new one:     abort ();
line 5624 is a new one: # include <sys/param.h>
line 5632 is a new one: 					__const __malloc_ptr_t)) =
line 5637 is a new one:   if (alignment % sizeof (void *) != 0
line 5638 is a new one:       || !powerof2 (alignment / sizeof (void *)) != 0
line 5639 is a new one:       || alignment == 0)
line 5642 is a new one:   /* Call the hook here, so that caller is posix_memalign's caller
line 5643 is a new one:      and not posix_memalign itself.  */
line 5644 is a new one:   if (hook != NULL)
line 5645 is a new one:     mem = (*hook)(alignment, size, RETURN_ADDRESS (0));
line 5647 is a new one:     mem = public_mEMALIGn (alignment, size);
line 5649 is a new one:   if (mem != NULL) {
line 5650 is a new one:     *memptr = mem;
line 5658 is a new one: strong_alias (__libc_calloc, __calloc) weak_alias (__libc_calloc, calloc)
line 5659 is a new one: strong_alias (__libc_free, __cfree) weak_alias (__libc_free, cfree)
line 5660 is a new one: strong_alias (__libc_free, __free) strong_alias (__libc_free, free)
line 5661 is a new one: strong_alias (__libc_malloc, __malloc) strong_alias (__libc_malloc, malloc)
line 5662 is a new one: strong_alias (__libc_memalign, __memalign)
line 5663 is a new one: weak_alias (__libc_memalign, memalign)
line 5664 is a new one: strong_alias (__libc_realloc, __realloc) strong_alias (__libc_realloc, realloc)
line 5665 is a new one: strong_alias (__libc_valloc, __valloc) weak_alias (__libc_valloc, valloc)
line 5666 is a new one: strong_alias (__libc_pvalloc, __pvalloc) weak_alias (__libc_pvalloc, pvalloc)
line 5667 is a new one: strong_alias (__libc_mallinfo, __mallinfo)
line 5668 is a new one: weak_alias (__libc_mallinfo, mallinfo)
line 5669 is a new one: strong_alias (__libc_mallopt, __mallopt) weak_alias (__libc_mallopt, mallopt)
line 5679 is a new one: /* ------------------------------------------------------------
line 5682 is a new one: [see ftp://g.oswego.edu/pub/misc/malloc.c for the history of dlmalloc]
line 5686 is a new one:  * Local variables:
line 5687 is a new one:  * c-basic-offset: 2
line 5688 is a new one:  * End:
line 5689 is a new one:  */
