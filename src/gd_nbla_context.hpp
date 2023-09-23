// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef GD_NNABLA_CONTEXT_H
#define GD_NNABLA_CONTEXT_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/context.hpp>


using namespace godot;


class nbla_Context : public RefCounted {
    GDCLASS(nbla_Context, RefCounted);

public:
    nbla_Context();
    virtual ~nbla_Context();

protected:
    static void _bind_methods();

public:
    nbla::Context* _context;

public:
    static Ref<nbla_Context> new_object(const PackedStringArray backend, String array_class, String device_id);

    void clear();

    void set_backend(const PackedStringArray backend);
    PackedStringArray get_backend() const;

    void set_array_class(const String backend);
    String get_array_class() const;

    void set_device_id(const String backend);
    String get_device_id() const;
};


#endif // GD_NNABLA_CONTEXT_H
