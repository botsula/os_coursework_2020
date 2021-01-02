Comparison of files: malloc_v2_18.c and malloc_v2_16.c
line 1 is a new one:    Copyright (C) 1996-2013 Free Software Foundation, Inc.
line 170 is a new one:     HAVE_MREMAP                0
line 216 is a new one: #include <unistd.h>   /* for __libc_enable_secure */
line 219 is a new one: #include <malloc-sysdep.h>
line 494 is a new one:   large blocks.
line 1073 is a new one: #ifndef NO_THREADS
line 1842 is a new one: static void* malloc_hook_ini (size_t sz,
line 1843 is a new one: 			      const void *caller) __THROW;
line 1844 is a new one: static void* realloc_hook_ini (void* ptr, size_t sz,
line 1845 is a new one: 			       const void *caller) __THROW;
line 1846 is a new one: static void* memalign_hook_ini (size_t alignment, size_t sz,
line 1847 is a new one: 				const void *caller) __THROW;
line 1850 is a new one: void weak_variable (*__free_hook) (void *__ptr,
line 1851 is a new one: 				   const void *) = NULL;
line 1852 is a new one: void *weak_variable (*__malloc_hook)
line 1853 is a new one:      (size_t __size, const void *) = malloc_hook_ini;
line 1854 is a new one: void *weak_variable (*__realloc_hook)
line 1855 is a new one:      (void *__ptr, size_t __size, const void *)
line 1857 is a new one: void *weak_variable (*__memalign_hook)
line 1858 is a new one:      (size_t __alignment, size_t __size, const void *)
line 2844 is a new one:   void *(*hook) (size_t, const void *)
line 2856 is a new one:     ar_ptr = arena_get_retry(ar_ptr, bytes);
line 2857 is a new one:     if (__builtin_expect(ar_ptr != NULL, 1)) {
line 2875 is a new one:   void (*hook) (void *, const void *)
line 2914 is a new one:   void *(*hook) (void *, size_t, const void *) =
line 3006 is a new one:   void *(*hook) (size_t, size_t, const void *) =
line 3022 is a new one:     ar_ptr = arena_get_retry (ar_ptr, bytes);
line 3023 is a new one:     if (__builtin_expect(ar_ptr != NULL, 1)) {
line 3048 is a new one:   void *(*hook) (size_t, size_t, const void *) =
line 3058 is a new one:     ar_ptr = arena_get_retry (ar_ptr, bytes);
line 3059 is a new one:     if (__builtin_expect(ar_ptr != NULL, 1)) {
line 3064 is a new one:     (void)mutex_unlock (&ar_ptr->mutex);
line 3084 is a new one:   void *(*hook) (size_t, size_t, const void *) =
line 3092 is a new one:     ar_ptr = arena_get_retry (ar_ptr, bytes + 2*pagesz + MINSIZE);
line 3093 is a new one:     if (__builtin_expect(ar_ptr != NULL, 1)) {
line 3127 is a new one:   void *(*hook) (size_t, const void *) =
line 3168 is a new one:     av = arena_get_retry (av, sz);
line 3169 is a new one:     if (__builtin_expect(av != NULL, 1)) {
line 3170 is a new one:       mem = _int_malloc(av, sz);
line 3175 is a new one:     (void)mutex_unlock(&av->mutex);
line 4445 is a new one: 		    __madvise (paligned_mem, size & ~psm1, MADV_DONTNEED);
line 4495 is a new one:     if (__builtin_expect(using_malloc_checking == 1, 0))
line 4496 is a new one:       return malloc_check_get_size(p);
line 4604 is a new one: __malloc_stats (void)
line 4701 is a new one: 	mp_.mmap_threshold = value;
line 4702 is a new one: 	mp_.no_dyn_threshold = 1;
line 4707 is a new one:     mp_.n_mmaps_max = value;
line 4894 is a new one:       __libc_message (action & 2, "*** Error in `%s': %s: 0x%s ***\n",
line 4918 is a new one:   void *(*hook) (size_t, size_t, const void *) =
