// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef NBLA_PFUNCTION_H
#define NBLA_PFUNCTION_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_data_variable.hpp>
#include <gd_nbla_parameter_directory.hpp>
#include <gd_nbla_pfopts.hpp>


using namespace godot;


class nbla_PFunction : public RefCounted {
    GDCLASS(nbla_PFunction, RefCounted);

public:
    nbla_PFunction();
    virtual ~nbla_PFunction();

protected:
    static void _bind_methods();

    static Ref<nbla_DataVariable> affine(
        Ref<nbla_DataVariable> x,
        int base_axis,
        int n_out,
        Ref<nbla_ParameterDirectory> parameters,
        Ref<nbla_PFAffineOpts> affine_opts);

    static Ref<nbla_DataVariable> batch_normalization(
        Ref<nbla_DataVariable> x,
        bool batch_stat,
        Ref<nbla_ParameterDirectory> parameters,
        Ref<nbla_PFBatchNormalizationOpts> batch_opts);

    static Ref<nbla_DataVariable> convolution(
        Ref<nbla_DataVariable> x,
        int base_axis,
        int n_map_out,
        const PackedInt32Array ary_kernel,
        Ref<nbla_ParameterDirectory> parameters,
        Ref<nbla_PFConvolutionOpts> conv_opts);

    static Ref<nbla_DataVariable> deconvolution(
        Ref<nbla_DataVariable> x,
        int base_axis,
        int n_map_out,
        PackedInt32Array kernel,
        Ref<nbla_ParameterDirectory> parameters,
        Ref<nbla_PFDeconvolutionOpts> conv_opts);
};


#endif // NBLA_PFUNCTION_H
