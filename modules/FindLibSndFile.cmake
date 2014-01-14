# Base Io build system
# Written by Jeremy Tregunna <jeremy.tregunna@me.com>
#
# Find libsndfile.

# (This is a BSD License)
# 
# Copyright (c) 2002, 2003 Steve Dekorte
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
# 
# ¥  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
# ¥  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
# ¥  Neither the name of the author nor the names of other contributors may be used to endorse or promote products derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


FIND_PATH(LIBSNDFILE_INCLUDE_DIR sndfile.h)

SET(LIBSNDFILE_NAMES ${LIBSNDFILE_NAMES} sndfile libsndfile)
FIND_LIBRARY(LIBSNDFILE_LIBRARY NAMES ${LIBSNDFILE_NAMES} PATH)

IF(LIBSNDFILE_INCLUDE_DIR AND LIBSNDFILE_LIBRARY)
	SET(LIBSNDFILE_FOUND TRUE)
ENDIF(LIBSNDFILE_INCLUDE_DIR AND LIBSNDFILE_LIBRARY)

IF(LIBSNDFILE_FOUND)
	IF(NOT LibSndFile_FIND_QUIETLY)
		MESSAGE(STATUS "Found LibSndFile: ${LIBSNDFILE_LIBRARY}")
	ENDIF (NOT LibSndFile_FIND_QUIETLY)
ELSE(LIBSNDFILE_FOUND)
	IF(LibSndFile_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find sndfile")
	ENDIF(LibSndFile_FIND_REQUIRED)
ENDIF (LIBSNDFILE_FOUND)
