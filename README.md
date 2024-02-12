# levenshtein Distance Algorithm Implementations in C

This repository contains two implementations of the Levenshtein distance algorithm in C, demonstrating both the original recursive approach and a more efficient dynamic programming-based approach.

# Roadmap

    ## lavenshtein.c:
        * Contains the original recursive implementation of the Levenshtein algorithm.
        * While correct, this method can be inefficient and slow for larger strings, limiting its practical applications.

    ## wagner_fischer.c:
        * Implements the Wagner-Fischer algorithm, a more efficient approach based on dynamic programming.
        * Utilizes the concepts of the original Levenshtein algorithm but reduces the recursive calls, leading to significant performance improvements.
