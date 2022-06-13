/***************************************************************************
 *   Copyright (C) 2022 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <interfaces/filesystem.h>
#include <bd/lfs_testbd.h>
#include <state.h>
#include <stdio.h>

// Filesystem used: LittleFS
#define LFS_READ_SIZE 16
#define LFS_PROG_SIZE LFS_READ_SIZE
#define LFS_BLOCK_SIZE 512
#define LFS_BLOCK_COUNT 1024
#define LFS_BLOCK_CYCLES -1
#define LFS_CACHE_SIZE (64 % LFS_PROG_SIZE == 0 ? 64 : LFS_PROG_SIZE)
#define LFS_LOOKAHEAD_SIZE 16
#define LFS_ERASE_VALUE 0xff
#define LFS_ERASE_CYCLES 0
#define LFS_BADBLOCK_BEHAVIOR LFS_TESTBD_BADBLOCK_PROGERROR

// variables used by the filesystem
static lfs_t          lfs;
static lfs_testbd_t   bd;
static const uint32_t lfs_testbd_cycles = 0;

// configuration of the filesystem is provided by this struct
static const struct lfs_config cfg =
{
    // block device operations
    .context        = &bd,
    .read           = lfs_testbd_read,
    .prog           = lfs_testbd_prog,
    .erase          = lfs_testbd_erase,
    .sync           = lfs_testbd_sync,

    // block device configuration
    .read_size      = LFS_READ_SIZE,
    .prog_size      = LFS_PROG_SIZE,
    .block_size     = LFS_BLOCK_SIZE,
    .block_count    = LFS_BLOCK_COUNT,
    .block_cycles   = LFS_BLOCK_CYCLES,
    .cache_size     = LFS_CACHE_SIZE,
    .lookahead_size = LFS_LOOKAHEAD_SIZE,
};

static const struct lfs_testbd_config bdcfg =
{
    .erase_value        = LFS_ERASE_VALUE,
    .erase_cycles       = LFS_ERASE_CYCLES,
    .badblock_behavior  = LFS_BADBLOCK_BEHAVIOR,
    .power_cycles       = lfs_testbd_cycles,
};

int filesystem_init()
{
    lfs_testbd_createcfg(&cfg, "./lfs_test.bin", &bdcfg);

    // Mount the filesystem
    int err = lfs_mount(&lfs, &cfg);

    if(err >= 0)
        state.filesystem_ready = true;
    else
        state.filesystem_ready = false;

    return err;
}

int filesystem_format()
{
    return lfs_format(&lfs, &cfg);
}

void filesystem_terminate()
{
    lfs_unmount(&lfs);
}
