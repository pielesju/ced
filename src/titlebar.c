/* titlebar.c
 * CED - Code EDitor
 * Copyright (C) 2024 Julian Pieles
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "titlebar.h"

void render_titlebar(Titlebar* titlebar) {
    attron(A_REVERSE);
    for (int x = 0; x < COLS; x++) {
        mvprintw(0, x, " ");
    }

    switch (titlebar->mode) {
        case 0: mvprintw(0, 1, "-NORMAL-"); break;
        case 1: mvprintw(0, 1, "-INSERT-"); break;
    }

    mvprintw(0, 19, "%s", titlebar->filename);
    mvprintw(0, COLS - 19, "%d", titlebar->loc);

    float percentread = ((titlebar->y * 1.0) / (titlebar->loc * 1.0)) * 100.0;

    mvprintw(0, COLS - 13, "%d%% %d:%d",
    (int)percentread,
    titlebar->x - 4, titlebar->y);
    attroff(A_REVERSE);
}
