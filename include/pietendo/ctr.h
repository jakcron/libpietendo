	/**
	 * @file		ctr.h
	 * @brief       Declaration of the CTR (Nintendo 3DS) library
	 **/
#pragma once

	/**
	 * @namespace   pie::ctr
	 * @brief       Namespace of the CTR (Nintendo 3DS) library
	 */

// definitions
#include <pietendo/ctr/cci.h>
#include <pietendo/ctr/cia.h>
#include <pietendo/ctr/cro.h>
#include <pietendo/ctr/crr.h>
#include <pietendo/ctr/exefs.h>
#include <pietendo/ctr/exheader.h>
#include <pietendo/ctr/firm.h>
#include <pietendo/ctr/ivfc.h>
#include <pietendo/ctr/ncch.h>
#include <pietendo/ctr/romfs.h>
#include <pietendo/ctr/smdh.h>

// Wrapped IStream
#include <pietendo/ctr/IvfcStream.h>

// Utilities
#include <pietendo/ctr/CtrKeyGenerator.h>

// VirtualFileSystem FileSystemSnapshot generators
#include <pietendo/ctr/ExeFsSnapshotGenerator.h>
#include <pietendo/ctr/RomFsSnapshotGenerator.h>
#include <pietendo/ctr/CciFsSnapshotGenerator.h>
#include <pietendo/ctr/CiaFsSnapshotGenerator.h>