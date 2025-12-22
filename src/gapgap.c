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

    // Main loop
    running = true;
    while (running == true)
    {
        // Draw screen
        ui_draw(&editor);

        // Get input
        ch = getch();

        // Handle input
        switch (ch)
        {
            // === QUIT ===
            case 'q':
                if (editor.modified == true)
                {
                    // TODO: Ask to save
                }
                running = false;
                break;

            // === NAVIGATION ===
            case KEY_UP:
            case 'k':
                editor_move_up(&editor);
                break;

            case KEY_DOWN:
            case 'j':
                editor_move_down(&editor);
                break;

            case KEY_LEFT:
            case 'h':
                editor_move_left(&editor);
                break;

            case KEY_RIGHT:
            case 'l':
                editor_move_right(&editor);
                break;

            case KEY_HOME:
            case '0':
                editor_move_line_start(&editor);
                break;

            case KEY_END:
            case '$':
                editor_move_line_end(&editor);
                break;

            case KEY_PPAGE:  // Page Up
                editor_page_up(&editor);
                break;

            case KEY_NPAGE:  // Page Down
                editor_page_down(&editor);
                break;

            // === GOTO LINE ===
            case 'g':
                ui_goto_line(&editor);
                break;

            case 'G':
                editor_goto_line(&editor, editor.total_lines - 1);
                break;

            // === EDITING ===
            case 'i':
                // Enter insert mode
                ui_insert_mode(&editor);
                break;

            case 'o':
                // Insert line below and enter insert mode
                editor_insert_line_below(&editor);
                ui_insert_mode(&editor);
                break;

            case 'O':
                // Insert line above and enter insert mode
                editor_insert_line_above(&editor);
                ui_insert_mode(&editor);
                break;

            case 'x':
                // Delete character under cursor
                editor_delete_char(&editor);
                break;

            case 'd':
                // Delete line (simplified: dd not implemented)
                editor_delete_line(&editor);
                break;

            // === FILE OPERATIONS ===
            case 's':
                // Save file
                if (editor.filepath != NULL)
                {
                    editor_save_file(&editor, editor.filepath);
                }
                else
                {
                    ui_save_as(&editor);
                }
                break;

            case 'S':
                // Save as
                ui_save_as(&editor);
                break;

            // === INFO ===
            case '?':
                ui_show_help();
                break;

            default:
                // Unknown key - ignore
                break;
        }
    }

    // Cleanup
    ui_cleanup();
    editor_cleanup(&editor);

    return 0;
}