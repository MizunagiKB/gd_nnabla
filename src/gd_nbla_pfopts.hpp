// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#ifndef NBLA_PFOPTS_H
#define NBLA_PFOPTS_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <nbla/parametric_functions.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_data_variable.hpp>


using namespace godot;


class nbla_PFAffineOpts : public RefCounted {
    GDCLASS(nbla_PFAffineOpts, RefCounted);

public:
    nbla_PFAffineOpts() {}
    virtual ~nbla_PFAffineOpts() {}

protected:
    static void _bind_methods() {}

public:
    nbla::parametric_functions::AffineOpts _affine_opts;
};


class nbla_PFBatchNormalizationOpts : public RefCounted {
    GDCLASS(nbla_PFBatchNormalizationOpts, RefCounted);

public:
    nbla_PFBatchNormalizationOpts() {}
    virtual ~nbla_PFBatchNormalizationOpts() {}

protected:
    static void _bind_methods() {}

public:
    nbla::parametric_functions::BatchNormalizationOpts _batch_opts;
};


class nbla_PFConvolutionOpts : public RefCounted {
    GDCLASS(nbla_PFConvolutionOpts, RefCounted);

public:
    nbla_PFConvolutionOpts() {}
    virtual ~nbla_PFConvolutionOpts() {}

protected:
    static void _bind_methods() {}

public:
    nbla::parametric_functions::ConvolutionOpts _conv_opts;
};


class nbla_PFDeconvolutionOpts : public RefCounted {
    GDCLASS(nbla_PFDeconvolutionOpts, RefCounted);

public:
    nbla_PFDeconvolutionOpts() {}
    virtual ~nbla_PFDeconvolutionOpts() {}

protected:
    static void _bind_methods() {}

public:
    nbla::parametric_functions::DeconvolutionOpts _conv_opts;
};


#endif // NBLA_PFOPTS_H
