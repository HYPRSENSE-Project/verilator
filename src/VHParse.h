// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Common implementations
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of either the GNU Lesser General Public License Version 3
// or the Perl Artistic License Version 2.0.
// SPDX-FileCopyrightText: 2026-2026 Eyck Jentzsch
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#ifndef VERILATOR_VHPARSE_H_
#define VERILATOR_VHPARSE_H_

#include "config_build.h"
#include "verilatedos.h"

#include "V3Error.h"
#include "V3Global.h"

class AstNetlist;
class VInFilter;
class VHParseImp;

//============================================================================

class VHParse final {
    VHParseImp* m_impp;

    // CONSTRUCTORS
    VL_UNCOPYABLE(VHParse);

public:
    // We must allow reading multiple files into one parser
    VHParse(AstNetlist* rootp, VInFilter* filterp) VL_MT_DISABLED;
    ~VHParse() VL_MT_DISABLED;

    // METHODS
    // Preprocess and read the Verilog file specified into the netlist database
    void parseFile(FileLine* fileline, const string& modname, bool inLibrary, bool inLibMap,
                   const string& libname, const string& errmsg,
                   const std::string& notFoundName = "") VL_MT_DISABLED;
};

#endif  // Guard
