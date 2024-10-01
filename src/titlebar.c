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
#include "ced/titlebar.h"
#include <string.h>
#include <stdio.h>

void render_titlebar(Titlebar* titlebar) {
    char output[titlebar->columns];

    char *modetext;

    switch (titlebar->mode) {
        case 0: modetext = "-NORMAL-"; break;
        case 1: modetext = "-INSERT-"; break;
        case 2: modetext = "-COMMAND-"; break;
    }

    float percentread = (titlebar->loc > 0) ?
                        (titlebar->y * 100.0f) / titlebar->loc :
                        0.0f;

    snprintf(output, sizeof(output), " %9s %20s %4d %3d%% %4d:%4d%*s",
            modetext,
            titlebar->filename,
            titlebar->loc,
            (int) percentread,
            titlebar->y,
            titlebar->x,
            titlebar->columns - 51, " ");
            mvaddstr(0, 0, output);
}
