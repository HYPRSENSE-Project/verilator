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
// SPDX-FileCopyrightText: 2026-2026 Wilson Snyder
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#include "VHParse.h"

#include <algorithm>
#include <array>
#include <ast_helper.h>
#include <ast_nodes.h>
#include <elaborator.h>
#include <filesystem>
#include <parser.h>
#include <validator.h>
#include <variant>


struct VHParseImp {
    VHParseImp(AstNetlist* rootp, VInFilter* filterp):rootp(rootp), filterp(filterp), elab(parser){
        // for(auto i : std::array<std::string, 2>{"contrib/ieee/std_logic_1164.vhdl", "contrib/ieee/numeric_bit.vhdl"}) {
        //     files.push_back(parser.parse_file(root_path / i, parser::encoding::UTF_8, "ieee"));
        // }
    }

    ~VHParseImp(){
        elab.add_design_files(files);
        elab.resolve_references();
        auto elab_diags = elab.get_diagnostics();
        //TODO: create proper verilator error messages
        assert(elab_diags.size() == 0);
        auto validation_diags = vhdl_fe::validate_resolved_ast({files.front()});
        assert(validation_diags.size() == 0);
    }

    void parseFile(FileLine* fileline, const string& modname, bool inLibrary, bool inLibMap,
                   const string& libname, const string& errmsg,
                   const std::string& notFoundName = "") VL_MT_DISABLED {
        files.push_back(parser.parse_file(fileline->filename(), parser::encoding::UTF_8, libname));
    }

private:
    AstNetlist* rootp;
    VInFilter* filterp;
    std::vector<ast::design_file*> files;
    parser::parser parser;
    vhdl_fe::elaborator elab;
};
//======================================================================
// V3Parse functions

VHParse::VHParse(AstNetlist* rootp, VInFilter* filterp) {
    m_impp = new VHParseImp{rootp, filterp};
}

VHParse::~VHParse() {  //
    VL_DO_CLEAR(delete m_impp, m_impp = nullptr);
}

void VHParse::parseFile(FileLine* fileline, const string& modname, bool inLibrary, bool inLibMap,
                        const string& libname, const string& errmsg,
                        const std::string& notFoundName) {
    m_impp->parseFile(fileline, modname, inLibrary, inLibMap, libname, errmsg, notFoundName);
}
