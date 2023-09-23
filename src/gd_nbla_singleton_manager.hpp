// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef GD_NBLA_SINGLETON_MANAGER_H
#define GD_NBLA_SINGLETON_MANAGER_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/singleton_manager.hpp>


using namespace godot;


class nbla_SingletonManager : public RefCounted {
    GDCLASS(nbla_SingletonManager, RefCounted);

public:
    nbla_SingletonManager();
    virtual ~nbla_SingletonManager();

protected:
    static void _bind_methods();

public:
    static void clear();
};


#endif // GD_NBLA_SINGLETON_MANAGER_H
