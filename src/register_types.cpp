// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include <gd_nbla_context.hpp>
#include <gd_nbla_data_variable.hpp>
#include <gd_nbla_executor.hpp>
#include <gd_nbla_fopts.hpp>
#include <gd_nbla_function.hpp>
#include <gd_nbla_nnp.hpp>
#include <gd_nbla_pfopts.hpp>
#include <gd_nbla_pfunction.hpp>
#include <gd_nbla_singleton_manager.hpp>


using namespace godot;


void initialize_gd_nnabla_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

    ClassDB::register_class<nbla_Context>();
    ClassDB::register_class<nbla_DataVariable>();
    ClassDB::register_class<nbla_Executor>();

    ClassDB::register_class<nbla_Function>();

    ClassDB::register_class<nbla_Nnp>();
    ClassDB::register_class<nbla_ParameterDirectory>();

    ClassDB::register_class<nbla_PFAffineOpts>();
    ClassDB::register_class<nbla_PFBatchNormalizationOpts>();
    ClassDB::register_class<nbla_PFConvolutionOpts>();
    ClassDB::register_class<nbla_PFDeconvolutionOpts>();
    ClassDB::register_class<nbla_PFunction>();

    ClassDB::register_class<nbla_SingletonManager>();
}


void uninitialize_gd_nnabla_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}


extern "C" {

// Initialization.
GDExtensionBool GDE_EXPORT gd_nnabla_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_gd_nnabla_module);
    init_obj.register_terminator(uninitialize_gd_nnabla_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}

}
