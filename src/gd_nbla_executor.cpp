// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <gd_nbla_executor.hpp>


using namespace nbla::utils;


nbla_Executor::nbla_Executor()
    : _executor(nullptr) {
}


nbla_Executor::~nbla_Executor() {}


void nbla_Executor::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_batch_size", "size"), &nbla_Executor::set_batch_size);
	ClassDB::bind_method(D_METHOD("get_data_variables"), &nbla_Executor::get_data_variables);
	ClassDB::bind_method(D_METHOD("execute"), &nbla_Executor::execute);
}


void nbla_Executor::set_batch_size(int size) {
    this->_executor->set_batch_size(size);
}


Array nbla_Executor::get_data_variables() {
    Array ary_variable;

    std::vector<nnp::Executor::DataVariable> variables = this->_executor->get_data_variables();

    for(std::vector<nnp::Executor::DataVariable>::iterator i = variables.begin(); i != variables.end(); i++) {
        Ref<nbla_DataVariable> v = memnew(nbla_DataVariable(*i));
        ary_variable.append(v);
    }

    return ary_variable;
}


void nbla_Executor::execute() {
    this->_executor->execute();
}
