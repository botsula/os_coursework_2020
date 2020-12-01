# OS Coursework 2020
Coursework for Operational Systems course, UCU, 2020.


## malloc implementation


#### 💣 State: Upgrading the library for properly work with ```mmap```.

**Current version** :

- ✅ supports creation of small memory blocks (***sbrk()***)
- ✅ includes ***free()*** module
- ✅ linked-blocks structure (close to glibc malloc implementation)
- ❌ support of big memory blocks (mmap)

---
Folder main structure:

```
/mymalloc/library    # contains versions of library
/mymalloc/main       # test module
```
To bulid a shared library:
```
gcc -shared -fPIC -o malloc2.so malloc2.c
```
To include it into your project:
```
 LD_PRELOAD=$PWD/library/malloc2.so ./main
```

(based on [link](https://medium.com/@andrestc/implementing-malloc-and-free-ba7e7704a473))