## Virtual Memory
xv6 uses two-level page table:  
![page_table_hw](pic/page_table_hw.png)

Page table in xv6:
```c
// A virtual address 'la' has a three-part structure as follows:
//
// +--------10------+-------10-------+---------12----------+
// | Page Directory |   Page Table   | Offset within Page  |
// |      Index     |      Index     |                     |
// +----------------+----------------+---------------------+
//  \--- PDX(va) --/ \--- PTX(va) --/

// page directory index
#define PDX(va)         (((uint)(va) >> PDXSHIFT) & 0x3FF)


// page table index
#define MAX_PTX         0x3FF
#define PTX(va)         (((uint)(va) >> PTXSHIFT) & MAX_PTX)

#define PPN(pa)         ((uint)(pa) >> PTXSHIFT)
#define OFFSET(va)      ((uint)(va) & 0xFFF)


// construct virtual address from indexes and offset
#define PGADDR(d, t, o) ((uint)((d) << PDXSHIFT | (t) << PTXSHIFT | (o)))

// Page directory and page table constants.
#define NPDENTRIES      1024    // # directory entries per page directory
#define NPTENTRIES      1024    // # PTEs per page table
#define PGSIZE          4096    // bytes mapped by a page

#define PTXSHIFT        12      // offset of PTX in a linear address
#define PDXSHIFT        22      // offset of PDX in a linear address

#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

// Page table/directory entry flags.
#define PTE_P           0x001   // Present
#define PTE_W           0x002   // Writeable
#define PTE_U           0x004   // User
#define PTE_PS          0x080   // Page Size
//changed: Added PTE_E. You have 12 bits for flags according
//to page 30 of the textbook
#define PTE_E           0x400
```
We need to account for KERNBASE while doing physical to virtual conversions and vice versa due to following layout:

- `V2P(a)` (virtual to physical)
   ```cpp
    #define V2P(a) (((uint) (a)) - KERNBASE)
    ```
- `P2V(a)` (physical to virtual)
  ```cpp
    #define P2V(a) ((void *)(((char *) (a)) + KERNBASE))
    ```

![page_table_kernel](pic/kernel.png)

In vm.c: walkpgdir returns the page table entry when given a virtual address and the page table directory:
```c
// Return the address of the PTE in page table pgdir
// that corresponds to virtual address va.  If alloc!=0,
// create any required page table pages.
static pte_t *
walkpgdir(pde_t *pgdir, const void *va, int alloc)
{
  pde_t *pde;
  pte_t *pgtab;

  pde = &pgdir[PDX(va)];
  if(*pde & PTE_P){
    //if (!alloc)
      //cprintf("page directory is good\n");
    pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
  } else {
    if(!alloc || (pgtab = (pte_t*)kalloc()) == 0)
      return 0;
    // Make sure all those PTE_P bits are zero.
    memset(pgtab, 0, PGSIZE);
    // The permissions here are overly generous, but they can
    // be further restricted by the permissions in the page table
    // entries, if necessary.
    *pde = V2P(pgtab) | PTE_P | PTE_W | PTE_U;
  }
  return &pgtab[PTX(va)];
}
```


## Handle NULL Dereference.
Currently, if you dereference a null pointer, 
you will not see an exception ; rather, you will see whatever code is the first bit of code in the program that is running.
Now, we want to cause seg fault when user program accesses NULL. One way is to achieve this is by moving entry point of code loading to second page. 
Thus, Accessing NULL will cause seg fault. To achieve this, one may want to change few things in MakeFile as well - See Hint of project description.

## Handle Read-only Code
Page table entries have PTE_W flag that can be used to set or unset write permissions. Think about where should you write your syscalls - Have a look at vm.c.

## A brief review of bitmasks:
  C provides a bunch of bitwise operators, for example:
```c
uint x, y;
// values get set
uint and_result = x & y; // we get '1' wherever bits match
uint or_result = x | y; // we get '1' wherever either bit was a '1'
```
Ok, so how do these help manage flags?  
We can use "masks" to isolate one or more flags.
Suppose we want to get flag "U" from a page table entry:
```c
// "places" for each of 12 bits: 8 4 2 1   8 4 2 1   8 4 2 1
// PTE_U as a series of 12 bits: 0 0 0 0   0 0 0 0   0 1 0 0
#define PTE_U 0x004

uint *pte; // we've got an entry.
uint pte_u = *pte & PTE_U; // pte_u is set to '1' if 3rd bit of *pte is '1', or '0' if 3rd bit is '0'

if (*pte & PTE_U) {
  // code runs if 3rd bit of *pte is '1', otherwise skipped.
}
```

On the other hand, to "set" a bit, we can use OR operation:

```c
*pte = *pte | PTE_U; // PTE_U only has a '1' at 3rd bit. So 3rd bit of *pte is now '1', all other bits remain the same.
```

xv6 works with virtual addresses in some places, physical addresses in others.
  Be careful to check what type of address you're using at any given time, and what type of address any functions you call require.

## Some Important Functions
1. PGROUNDUP/ PGROUNDDOWN - Round an address up/down in such a way that it becomes multiple of page boundaries - like std::ceil and std::floor. 
2. walkpgdir - Iterate on page table entries and sets permissions over them.
3. mappages - Creates mapping of Virtual Addresses to Physical Address. If 2nd level entry is not present(allocated), then allocate it.
4. lcr3 - Way to inform HW so that it can initiate reloading of Page Table Entries.

## Resources
1. https://www.cse.iitb.ac.in/~mythili/os/notes/old-xv6/xv6-memory.pdf
2. https://www.youtube.com/watch?v=es1JjdlCBms

