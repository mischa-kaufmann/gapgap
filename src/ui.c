int ui_main_loop(Editor *editor)
{
    bool running = true;
    int ch;

    while (running == true)
    {
        /* Draw screen */
        ui_draw(editor);

        /* Get input */
        ch = getch();

        /* Handle input */
        switch (ch)
        {
            /* === QUIT === */
            case 'q':
                if (editor->modified == true)
                {
                    /* TODO: Ask to save */
                }
                running = false;
                break;

            /* === NAVIGATION === */
            case KEY_UP:
            case 'k':
                editor_move_up(editor);
                break;

            case KEY_DOWN:
            case 'j':
                editor_move_down(editor);
                break;

            case KEY_LEFT:
            case 'h':
                editor_move_left(editor);
                break;

            case KEY_RIGHT:
            case 'l':
                editor_move_right(editor);
                break;

            case KEY_HOME:
            case '0':
                editor_move_line_start(editor);
                break;

            case KEY_END:
            case '$':
                editor_move_line_end(editor);
                break;

            case KEY_PPAGE:  /* Page Up */
                editor_page_up(editor);
                break;

            case KEY_NPAGE:  /* Page Down */
                editor_page_down(editor);
                break;

            /* === GOTO LINE === */
            case 'g':
                ui_goto_line(editor);
                break;

            case 'G':
                editor_goto_line(editor, editor->total_lines - 1);
                break;

            /* === EDITING === */
            case 'i':
                /* Enter insert mode */
                ui_insert_mode(editor);
                break;

            case 'o':
                /* Insert line below and enter insert mode */
                editor_insert_line_below(editor);
                ui_insert_mode(editor);
                break;

            case 'O':
                /* Insert line above and enter insert mode */
                editor_insert_line_above(editor);
                ui_insert_mode(editor);
                break;

            case 'x':
                /* Delete character under cursor */
                editor_delete_char(editor);
                break;

            case 'd':
                /* Delete line (simplified: dd not implemented) */
                editor_delete_line(editor);
                break;

            /* === FILE OPERATIONS === */
            case 's':
                /* Save file */
                if (editor->filepath != NULL)
                {
                    editor_save_file(editor, editor->filepath);
                }
                else
                {
                    ui_save_as(editor);
                }
                break;

            case 'S':
                /* Save as */
                ui_save_as(editor);
                break;

            /* === INFO === */
            case '?':
                ui_show_help();
                break;

            default:
                /* Unknown key - ignore */
                break;
        }
    }

    return 0;
}
