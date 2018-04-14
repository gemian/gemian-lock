# - Try to find libev
# Once done this will define
#
#  LIBEV_FOUND - system has libev
#  LIBEV_LIBRARIES - Link these to use libev
#  LIBEV_INCLUDE_DIR - the libev include dir
#  LIBEV_DEFINITIONS - compiler switches required for using libev

# Copyright (c) 2008 Helio Chissini de Castro, <helio@kde.org>
# Copyright (c) 2007, Matthias Kretz, <kretz@kde.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


IF (NOT WIN32)
    IF (LIBEV_INCLUDE_DIR AND LIBEV_LIBRARIES)
        # in cache already
        SET(EV_FIND_QUIETLY TRUE)
    ENDIF (LIBEV_INCLUDE_DIR AND LIBEV_LIBRARIES)

    FIND_PACKAGE(PkgConfig)
    PKG_CHECK_MODULES(PKG_EV ev)

    SET(LIBEV_DEFINITIONS ${PKG_EV_CFLAGS})

    FIND_PATH(LIBEV_INCLUDE_DIR ev.h ${PKG_EV_INCLUDE_DIRS})
    FIND_LIBRARY(LIBEV_LIBRARIES NAMES ev PATHS ${PKG_EV_LIBRARY_DIRS})

    include(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(EV DEFAULT_MSG LIBEV_LIBRARIES LIBEV_INCLUDE_DIR)

    MARK_AS_ADVANCED(LIBEV_INCLUDE_DIR LIBEV_LIBRARIES)
ENDIF (NOT WIN32)
