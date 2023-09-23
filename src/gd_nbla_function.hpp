// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef NBLA_FUNCTION_H
#define NBLA_FUNCTION_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_data_variable.hpp>
#include <gd_nbla_fopts.hpp>
#include <gd_nbla_parameter_directory.hpp>


using namespace godot;


class nbla_Function : public RefCounted {
    GDCLASS(nbla_Function, RefCounted);

public:
    nbla_Function();
    virtual ~nbla_Function();

protected:
    static void _bind_methods();

public:
    #include "gd_nbla_function.hpp.inc"
};


#endif // NBLA_FUNCTION_H
