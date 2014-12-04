/*
 * ChMacAddroid - Android app that changes a network devices MAC address
 * Copyright (C) 2014 Matthew Finkel <Matthew.Finkel@gmail.com>
 *
 * This file is part of ChMacAddroid
 *
 * ChMacAddroid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ChMacAddroid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ChMacAddroid, in the COPYING file.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <errno.h>
#include "chmacaddr.h"

/** Kick it off
 * Check if we can drop capabilities, then prevent regaining
 * any capabilities we drop in the future. Last, we drop all
 * capabilities we don't need.
 * Return -1 on failure.
 * Return 0 on success.
 */
int
main(int argc, char * argv[])
{
    int drop_caps = chmaddr_can_drop_caps();
    if (drop_caps != 1) {
        fprintf(stderr, "Neither SYS_ADMIN nor SETPCAP are not "
                        "available. grrrr! %s\n", strerror(errno));
        return -1;
    }

    if (chmaddr_lock_it_down()) {
        return -1;
    }

    if (chmaddr_drop_unneeded_caps()) {
        return -1;
    }

    return chmaddr_make_it_so(argc, (const char **)argv);
}

