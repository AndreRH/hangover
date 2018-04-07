/*
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef ISTREAM_WRAPPER_H
#define ISTREAM_WRAPPER_H

#include <objidl.h>

struct istream_wrapper;

struct istream_wrapper *istream_wrapper_create(uint64_t guest_iface);
struct istream_wrapper *istream_wrapper_from_IStream(IStream *iface);
void istream_wrapper_destroy(struct istream_wrapper *wrapper);
uint64_t istream_wrapper_guest_iface(struct istream_wrapper *wrapper);
IStream * istream_wrapper_host_iface(struct istream_wrapper *wrapper);

#endif
