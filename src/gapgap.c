// gapgap.c
// A line-based text editor with double gap buffer architecture
// CS50x Final Project - Mischa Kaufmann
//
// Unity Build: This file includes all other .c files
// Compile with: gcc -o gapgap gapgap.c -lncurses

// ============================================================================
// STANDARD LIBRARY
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ============================================================================
// EXTERNAL LIBRARIES
// ============================================================================

#include <ncurses.h>

// ============================================================================
// PROJECT HEADERS
// ============================================================================

#include "gapgap_config.h"
#include "gapgap_types.h"

// ============================================================================
// PROJECT SOURCE FILES (Unity Build)
// ============================================================================

#include "arena.c"
#include "gap_buffer.c"
#include "line_chunk.c"
#include "line_index.c"
#include "editor.c"
#include "io.c"
#include "ui.c"

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char *argv[])
{
    Editor editor;
    int ch;
    bool running;

    // Initialize editor
    if (editor_init(&editor) == false)
    {
        fprintf(stderr, "Error: Could not initialize editor\n");
        return 1;
    }

    // Load file if argument given
    if (argc >= 2)
    {
        if (editor_load_file(&editor, argv[1]) == false)
        {
            fprintf(stderr, "Error: Could not load file: %s\n", argv[1]);
            editor_cleanup(&editor);
            return 1;
        }
    }
    else
    {
        // Start with empty document (one empty line)
        editor_new_document(&editor);
    }

    // Initialize ncurses UI
    if (ui_init() == false)
    {
        fprintf(stderr, "Error: Could not initialize UI\n");
        editor_cleanup(&editor);
        return 1;
    }

    // Get terminal size
    editor.view_height = LINES - 1;  // Reserve 1 line for status bar
    editor.view_width = COLS;

    // Run main UI loop
    ui_main_loop(&editor);

    // Cleanup
    ui_cleanup();
    editor_cleanup(&editor);

    return 0;
};