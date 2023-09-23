// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef NBLA_PARAMETER_DIRECTORY_H
#define NBLA_PARAMETER_DIRECTORY_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/parametric_functions.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_data_variable.hpp>


using namespace godot;


class nbla_ParameterDirectory : public RefCounted {
    GDCLASS(nbla_ParameterDirectory, RefCounted);

public:
    nbla_ParameterDirectory();
    virtual ~nbla_ParameterDirectory();

protected:
    static void _bind_methods();

public:
    nbla::ParameterDirectory _parameter;
};


#endif // NBLA_PARAMETER_DIRECTORY_H
