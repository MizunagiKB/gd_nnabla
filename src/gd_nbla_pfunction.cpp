// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/functions.hpp>
#include <nbla/function/affine.hpp>
#include <nbla/parametric_functions.hpp>

#include <gd_nbla_pfunction.hpp>


namespace f = nbla::functions;
namespace pf = nbla::parametric_functions;


nbla_PFunction::nbla_PFunction() {}
nbla_PFunction::~nbla_PFunction() {}


void nbla_PFunction::_bind_methods() {
	ClassDB::bind_static_method("nbla_PFunction", D_METHOD("affine", "x", "base_axis", "n_out", "parameters", "affine_opts"), &nbla_PFunction::affine);
	ClassDB::bind_static_method("nbla_PFunction", D_METHOD("batch_normalization", "x", "batch_stat", "parameters", "affine_opts"), &nbla_PFunction::batch_normalization);
	ClassDB::bind_static_method("nbla_PFunction", D_METHOD("convolution", "x", "base_axis", "n_map_out", "ary_kernel", "parameters", "affine_opts"), &nbla_PFunction::convolution);
	ClassDB::bind_static_method("nbla_PFunction", D_METHOD("deconvolution", "x", "base_axis", "n_map_out", "ary_kernel", "parameters", "affine_opts"), &nbla_PFunction::deconvolution);
}


Ref<nbla_DataVariable> nbla_PFunction::affine(
    Ref<nbla_DataVariable> x,
    int base_axis,
    int n_out,
    Ref<nbla_ParameterDirectory> parameters,
    Ref<nbla_PFAffineOpts> affine_opts) {

    nbla::CgVariablePtr y = pf::affine(
        x->_data_variable.variable,
        base_axis,
        n_out,
        parameters->_parameter,
        affine_opts->_affine_opts
    );

    Ref<nbla_DataVariable> r = memnew(nbla_DataVariable(std::string(), std::string(), y));

    return r;
}


Ref<nbla_DataVariable> nbla_PFunction::batch_normalization(
    Ref<nbla_DataVariable> x,
    bool batch_stat,
    Ref<nbla_ParameterDirectory> parameters,
    Ref<nbla_PFBatchNormalizationOpts> batch_opts) {

    nbla::CgVariablePtr y = pf::batch_normalization(
        x->_data_variable.variable,
        batch_stat,
        parameters->_parameter,
        batch_opts->_batch_opts
    );

    Ref<nbla_DataVariable> r = memnew(nbla_DataVariable(std::string(), std::string(), y));

    return r;
}


Ref<nbla_DataVariable> nbla_PFunction::convolution(
    Ref<nbla_DataVariable> x,
    int base_axis,
    int n_map_out,
    const PackedInt32Array ary_kernel,
    Ref<nbla_ParameterDirectory> parameters,
    Ref<nbla_PFConvolutionOpts> conv_opts) {

    std::vector<int> kernel;
    for(int i = 0; i < ary_kernel.size(); i++) {
        kernel.push_back(ary_kernel[i]);
    }

    nbla::CgVariablePtr y = pf::convolution(
        x->_data_variable.variable,
        base_axis,
        n_map_out,
        kernel,
        parameters->_parameter,
        conv_opts->_conv_opts
    );

    Ref<nbla_DataVariable> r = memnew(nbla_DataVariable(std::string(), std::string(), y));

    return r;
}


Ref<nbla_DataVariable> nbla_PFunction::deconvolution(
    Ref<nbla_DataVariable> x,
    int base_axis,
    int n_map_out,
    const PackedInt32Array ary_kernel,
    Ref<nbla_ParameterDirectory> parameters,
    Ref<nbla_PFDeconvolutionOpts> conv_opts) {

    std::vector<int> kernel;
    for(int i = 0; i < ary_kernel.size(); i++) {
        kernel.push_back(ary_kernel[i]);
    }

    nbla::CgVariablePtr y = pf::deconvolution(
        x->_data_variable.variable,
        base_axis,
        n_map_out,
        kernel,
        parameters->_parameter,
        conv_opts->_conv_opts
    );

    Ref<nbla_DataVariable> r = memnew(nbla_DataVariable(std::string(), std::string(), y));

    return r;
}


#if 0
#include <nbla/context.hpp>
#include <nbla/function/affine.hpp>
#include <nbla/function/convolution.hpp>
#include <nbla/variable.hpp>

using namespace nbla;

int main() {
    // コンテキストの作成
    Context ctx{{"cpu:float"}, "CpuCachedArray", "0"};

    // 入力変数の作成
    auto x = make_shared<Variable>(Shape_t{1, 3, 32, 32});
    auto w_conv = make_shared<Variable>(Shape_t{64, 3, 3, 3});
    auto b_conv = make_shared<Variable>(Shape_t{64});
    auto w_affine = make_shared<Variable>(Shape_t{10, 64});
    auto b_affine = make_shared<Variable>(Shape_t{10});

    // コンボリューション関数の作成
    auto y_conv = F::Convolution(x, w_conv, b_conv, {1, 1}, {1, 1}, {0, 0}, 1, false, ctx);

    // アフィン関数の作成
    auto y_affine = F::Affine(y_conv, w_affine, b_affine, ctx);

    // 順伝播の実行
    y_affine->forward();

    return 0;
}
#endif