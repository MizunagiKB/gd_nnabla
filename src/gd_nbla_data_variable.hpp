// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef GD_NNABLA_DATA_VARIABLE_H
#define GD_NNABLA_DATA_VARIABLE_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla_utils/nnp.hpp>

#include <gd_nbla_context.hpp>


using namespace nbla::utils;
using namespace godot;


class nbla_DataVariable : public RefCounted {
    GDCLASS(nbla_DataVariable, RefCounted);

public:
    nbla_DataVariable();
    nbla_DataVariable(const nnp::Executor::DataVariable data_variable);
    nbla_DataVariable(std::string variable_name, std::string data_name, nbla::CgVariablePtr variable);
    virtual ~nbla_DataVariable();

protected:
    static void _bind_methods();

public:
    nnp::Executor::DataVariable _data_variable;

public:
    int size() const;

    void set_byte(const Ref<nbla_Context> ref_ctx, PackedByteArray ary);
    PackedByteArray get_byte(const Ref<nbla_Context> ref_ctx) const;

    void set_float32(const Ref<nbla_Context> ref_ctx, PackedFloat32Array ary);
    PackedFloat32Array get_float32(const Ref<nbla_Context> ref_ctx) const;
};


#endif // GD_NNABLA_DATA_VARIABLE_H
