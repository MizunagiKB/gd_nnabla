// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef NBLA_EXECUTOR_H
#define NBLA_EXECUTOR_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla_utils/nnp.hpp>

#include <gd_nbla_data_variable.hpp>


using namespace nbla::utils;
using namespace godot;


class nbla_Executor : public RefCounted {
    GDCLASS(nbla_Executor, RefCounted);

public:
    nbla_Executor();
    virtual ~nbla_Executor();

protected:
    static void _bind_methods();

public:
    std::shared_ptr<nbla::utils::nnp::Executor> _executor;

    void set_batch_size(int size);
    Array get_data_variables();
    void execute();
};


#endif // NBLA_EXECUTOR_H
