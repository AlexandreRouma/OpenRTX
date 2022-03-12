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

#ifndef XMODEM_H
#define XMODEM_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Send an XMODEM packet over the serial port.
 *
 * @param data: pointer to payload data.
 * @param size: data size, must be either 128 or 1024 byte.
 * @param blockNum: packet sequence number.
 */
void xmodem_sendPacket(const void *data, size_t size, uint8_t blockNum);

/**
 * Send data using the XMODEM protocol, blocking function.
 * Data transfer begins when the start command from the receiving endpoint is
 * detected.
 *
 * @param size: data size.
 * @param callback: pointer to a callback function in charge of providing data
 * for the new packets being sent.
 */
ssize_t xmodem_sendData(size_t size, int (*callback)(uint8_t *, size_t));

#ifdef __cplusplus
}
#endif

#endif /* XMODEM_H */