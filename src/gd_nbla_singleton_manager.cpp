// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <gd_nbla_singleton_manager.hpp>


nbla_SingletonManager::nbla_SingletonManager() {}
nbla_SingletonManager::~nbla_SingletonManager() {}

void nbla_SingletonManager::_bind_methods() {
	ClassDB::bind_static_method("nbla_SingletonManager", D_METHOD("clear"), &nbla_SingletonManager::clear);
}

void nbla_SingletonManager::clear() {
    nbla::SingletonManager::clear();
}
