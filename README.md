# AVL Tree Implementation in C++

This is a simple implementation of an AVL (Adelson-Velsky and Landis) tree in C++. AVL trees are self-balancing binary search trees, which ensure that the tree remains approximately balanced after insertions and deletions.

## Table of Contents
- [Introduction](#introduction)

- [Functions](#functions)


## Introduction
An AVL tree is a binary tree in which the height of the left and right subtrees of any node differ by at most one. It achieves this balance by performing rotations after insertions and deletions. This implementation provides basic operations such as insertion, removal, searching, and checking if the tree is AVL balanced.


## Functions
Here's a brief overview of the functions provided by the AVL class:

- `insert(T val)`: Insert a value into the AVL tree.
- `remove(T val)`: Remove a value from the AVL tree.
- `search(T val)`: Search for a value in the AVL tree.
- `isAVL()`: Check if the tree is an AVL tree.
- `findmin()`: Find the minimum value in the tree.
- `print()`: Print the tree in inorder, preorder, and postorder.
- `printAllPaths()`: Print all root-to-leaf paths in the tree.
