// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <gd_nbla_data_variable.hpp>


nbla_DataVariable::nbla_DataVariable()
    : _data_variable({nullptr, nullptr, nullptr}) {
}


nbla_DataVariable::nbla_DataVariable(const nnp::Executor::DataVariable data_variable)
    : _data_variable(data_variable) {
}


nbla_DataVariable::nbla_DataVariable(std::string variable_name, std::string data_name, nbla::CgVariablePtr variable)
    : _data_variable({variable_name, data_name, variable}) {
}


nbla_DataVariable::~nbla_DataVariable() {}


void nbla_DataVariable::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_batch_size"), &nbla_DataVariable::size);
	ClassDB::bind_method(D_METHOD("set_byte", "ctx", "array"), &nbla_DataVariable::set_byte);
	ClassDB::bind_method(D_METHOD("get_byte", "ctx"), &nbla_DataVariable::get_byte);
	ClassDB::bind_method(D_METHOD("set_float32", "ctx", "array"), &nbla_DataVariable::set_float32);
	ClassDB::bind_method(D_METHOD("get_float32", "ctx"), &nbla_DataVariable::get_float32);
}


int nbla_DataVariable::size() const {
    return this->_data_variable.variable->variable()->size();
}


void nbla_DataVariable::set_byte(const Ref<nbla_Context> ref_ctx, PackedByteArray ary) {
    if(this->_data_variable.variable == nullptr) return;

    nbla::VariablePtr variable_ptr = this->_data_variable.variable->variable();
    if(variable_ptr->size() != ary.size()) return;

    uint8_t* ptr_data = variable_ptr->cast_data_and_get_pointer<uint8_t>(*ref_ctx->_context);
    ::memcpy(ptr_data, ary.ptr(), sizeof(uint8_t) * variable_ptr->size());
}


PackedByteArray nbla_DataVariable::get_byte(const Ref<nbla_Context> ref_ctx) const {
    PackedByteArray ary;

    if(this->_data_variable.variable == nullptr) return ary;

    nbla::VariablePtr variable_ptr = this->_data_variable.variable->variable();
    ary.resize(variable_ptr->size());

    const uint8_t* ptr_data = variable_ptr->get_data_pointer<uint8_t>(*ref_ctx->_context);
    for(int i = 0; i < variable_ptr->size(); i++) {
        ary.set(i, ptr_data[i]);
    }

    return ary;
}


void nbla_DataVariable::set_float32(const Ref<nbla_Context> ref_ctx, PackedFloat32Array ary) {
    if(this->_data_variable.variable == nullptr) return;

    nbla::VariablePtr variable_ptr = this->_data_variable.variable->variable();
    if(variable_ptr->size() != ary.size()) return;

    float* ptr_data = variable_ptr->cast_data_and_get_pointer<float>(*ref_ctx->_context);
    ::memcpy(ptr_data, ary.ptr(), sizeof(float) * variable_ptr->size());
}


PackedFloat32Array nbla_DataVariable::get_float32(const Ref<nbla_Context> ref_ctx) const {
    PackedFloat32Array ary;

    if(this->_data_variable.variable == nullptr) return ary;

    nbla::VariablePtr variable_ptr = this->_data_variable.variable->variable();
    ary.resize(variable_ptr->size());

    const float* ptr_data = variable_ptr->get_data_pointer<float>(*ref_ctx->_context);
    for(int i = 0; i < variable_ptr->size(); i++) {
        ary.set(i, ptr_data[i]);
    }

    return ary;
}




