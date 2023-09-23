// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <gd_nbla_nnp.hpp>


nbla_Nnp::nbla_Nnp()
    : _nnp(nullptr) {
}


nbla_Nnp::~nbla_Nnp() {
    this->clear();
}


void nbla_Nnp::_bind_methods() {
	ClassDB::bind_static_method("nbla_Nnp", D_METHOD("new_object", "context"), &nbla_Nnp::new_object);

	ClassDB::bind_method(D_METHOD("clear"), &nbla_Nnp::clear);
	ClassDB::bind_method(D_METHOD("add", "pathname"), &nbla_Nnp::add);
    ClassDB::bind_method(D_METHOD("get_executor", "executor_name"), &nbla_Nnp::get_executor);
}


Ref<nbla_Nnp> nbla_Nnp::new_object(const Ref<nbla_Context> ref_nbla_context) {
    Ref<nbla_Nnp> ref_result;
    ref_result.instantiate();
    ref_result->_nnp = memnew(nbla::utils::nnp::Nnp(*ref_nbla_context->_context));

    return ref_result;
}


void nbla_Nnp::clear() {
    if(this->_nnp != nullptr) {
        memdelete(this->_nnp);
        this->_nnp = nullptr;
    }
}


bool nbla_Nnp::add(const String pathname) {
    if(this->_nnp == nullptr) return false;

    PackedByteArray buffer = FileAccess::get_file_as_bytes(pathname);
    if(buffer.size() == 0) return false;

    return this->_nnp->add(reinterpret_cast<char*>(buffer.ptrw()), buffer.size());

    return false;
}

Ref<nbla_Executor> nbla_Nnp::get_executor(const String executor_name) {
    if(this->_nnp == nullptr) return Ref<nbla_Executor>();

    Ref<nbla_Executor> ref_gdnn_executor;
    ref_gdnn_executor.instantiate();
    ref_gdnn_executor->_executor = this->_nnp->get_executor(
         std::string(executor_name.utf8())
    );

    return ref_gdnn_executor;
}
