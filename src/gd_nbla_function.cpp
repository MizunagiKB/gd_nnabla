// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/functions.hpp>
#include <nbla/function/affine.hpp>
#include <nbla/parametric_functions.hpp>

#include <gd_nbla_function.hpp>


namespace f = nbla::functions;
namespace pf = nbla::parametric_functions;


nbla_Function::nbla_Function() {}
nbla_Function::~nbla_Function() {}


void nbla_Function::_bind_methods() {
    #include "gd_nbla_function.cpp.inc"
}
