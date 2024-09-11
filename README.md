# merkletree
Implementation of a Merkle tree in C. Blake 2b is used for the hash function to hash data aswell as hash nodes within the tree.

**Usage:**
Create a new struct and fill the hash_size with a desired value:

```
struct MTree tree;
tree.hash_size = 16;
```
Initialize the tree with an array full of data which is supposed to become the trees leaves. The elements of the array need to uniformly have the same memory size and it should be known or atleast be inferred by the sizeof-operator. Also the number of elements of the array need to be known.
```
int array[] = { 0, 1, 2, 3, 4};
if(mtree_init(&tree, array, sizeof(int), 5) ) {
    //error handling ...
}
```
There is a print function to print the hashes to the command line ```mtree_print_tree(struct MTree *tree)``` but it's not very nicely formatted and just prints the hashes in their hex-representation form.
Recursively free/destroy the tree with:

```
mtree_free(&tree);
```
The tree-structure itself will not be destroyed but all associated node and leaf data and the internally used buffers. So you can call mtree_free on a structure initialized on the stack (also see the example main).