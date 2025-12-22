
// gapgap_config.h
// Configuration constants for gapgap text editor
// CS50x Final Project - Mischa Kaufmann

#ifndef GAPGAP_CONFIG_H
#define GAPGAP_CONFIG_H

// Line Configuration
#define MAX_LINE_LENGTH      128      // 2^7, cache-friendly
#define INITIAL_GAP_SIZE     MAX_LINE_LENGTH

// Chunk Configuration
#define LINES_PER_CHUNK      4096     // 2^12, O(4096) worst case for insert/delete
#define MAX_CHUNKS           1024     // Max ~4M lines (1024 * 4096)

// Arena Configuration
#define ARENA_INITIAL_SIZE   (1024 * 1024 * 64)  // 64 MB initial
#define ARENA_ALIGNMENT      16

// UI Configuration (ncurses)
#define TAB_WIDTH            4
#define SCROLL_MARGIN        5        // Lines before edge to start scrolling

// File I/O
#define IO_BUFFER_SIZE       8192     // Read buffer for file loading
#define PROGRESS_INTERVAL    10000    // Show progress every N lines

#endif // GAPGAP_CONFIG_H