// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef GD_NNABLA_NNP_H
#define GD_NNABLA_NNP_H

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla_utils/nnp.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_executor.hpp>


using namespace godot;


class nbla_Nnp : public RefCounted {
    GDCLASS(nbla_Nnp, RefCounted);

public:
    nbla_Nnp();
    virtual ~nbla_Nnp();

protected:
    static void _bind_methods();

public:
    nbla::utils::nnp::Nnp* _nnp;

public:
    static Ref<nbla_Nnp> new_object(const Ref<nbla_Context> context);

    void clear();

    bool add(const String pathname);
    Ref<nbla_Executor> get_executor(const String executor_name);
};


#endif // GD_NNABLA_NNP_H
