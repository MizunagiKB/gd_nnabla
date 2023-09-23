// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <gd_nbla_context.hpp>


nbla_Context::nbla_Context()
    : _context(nullptr) {
}


nbla_Context::~nbla_Context() {
    this->clear();
}


void nbla_Context::_bind_methods() {
	ClassDB::bind_static_method("nbla_Context", D_METHOD("new_object", "backend", "array_class", "device_id"), &nbla_Context::new_object);

	ClassDB::bind_method(D_METHOD("clear"), &nbla_Context::clear);

	ClassDB::bind_method(D_METHOD("set_backend", "backend"), &nbla_Context::set_backend);
	ClassDB::bind_method(D_METHOD("get_backend"), &nbla_Context::get_backend);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "backend", PROPERTY_HINT_TYPE_STRING), "set_backend", "get_backend");

	ClassDB::bind_method(D_METHOD("set_array_class", "array_class"), &nbla_Context::set_array_class);
	ClassDB::bind_method(D_METHOD("get_array_class"), &nbla_Context::get_array_class);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "array_class"), "set_array_class", "get_array_class");

	ClassDB::bind_method(D_METHOD("set_device_id", "device_id"), &nbla_Context::set_device_id);
	ClassDB::bind_method(D_METHOD("get_device_id"), &nbla_Context::get_device_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "device_id"), "set_device_id", "get_device_id");
}


Ref<nbla_Context> nbla_Context::new_object(PackedStringArray backend, String array_class, String device_id) {
    Ref<nbla_Context> ref_context;
    ref_context.instantiate();
 
    std::vector<std::string> vec_backend;
    for(int i = 0; i < backend.size(); i++) {
        vec_backend.push_back(std::string(backend[i].utf8()));
    }

    ref_context->_context = memnew(
        nbla::Context(
            vec_backend,
            std::string(array_class.utf8()),
            std::string(device_id.utf8())
        )
    );

    return ref_context;
}


void nbla_Context::clear() {
    if(this->_context != nullptr) {
        memdelete(this->_context);
        this->_context = nullptr;
    }
}


void nbla_Context::set_backend(const PackedStringArray backend) {
    if(this->_context == nullptr) return;

    std::vector<std::string> vec_backend;
    for(int i = 0; i < backend.size(); i++) {
        vec_backend.push_back(std::string(backend[i].utf8()));
    }

    this->_context->set_backend(vec_backend);
}


PackedStringArray nbla_Context::get_backend() const {
    if(this->_context == nullptr) return PackedStringArray();

    PackedStringArray ary;

    ary.resize(this->_context->backend.size());

    for(int i = 0; i < this->_context->backend.size(); i++) {
        ary.set(i, String(this->_context->backend[i].c_str()));
    }

    return ary;
}


void nbla_Context::set_array_class(const String array_class) {
    if(this->_context == nullptr) return;

    this->_context->set_array_class(std::string(array_class.utf8()));
}


String nbla_Context::get_array_class() const {
    if(this->_context == nullptr) return String();

    return String(this->_context->array_class.c_str());
}


void nbla_Context::set_device_id(const String device_id) {
    if(this->_context == nullptr) return;

    this->_context->set_device_id(std::string(device_id.utf8()));
}


String nbla_Context::get_device_id() const {
    if(this->_context == nullptr) return String();

    return String(this->_context->device_id.c_str());
}
