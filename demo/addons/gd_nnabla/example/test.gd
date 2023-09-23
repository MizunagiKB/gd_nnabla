# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
extends Node2D


func read_pgm_mnist(filename, data):
    pass


func _ready():
    # GDNNablaSingletonManager.clear()

    var nnp_file = "res://model_simple.nnp"
    var input_bin = ""
    var executor_name = "runtime"   

    var backend: PackedStringArray
    backend.append("cpu:float")
    var cpu_ctx = nbla_Context.new_object(backend, "CpuCachedArray", "0")
    var ctx = cpu_ctx;

    var nnp = nbla_Nnp.new_object(cpu_ctx)
    var result = nnp.add(nnp_file)
    print(result)

    var executor = nnp.get_executor(executor_name)

    executor.set_batch_size(1)
    var x: nbla_DataVariable = executor.get_data_variables()[0]
    var data = x.get_byte(cpu_ctx)

    read_pgm_mnist(input_bin, data)

    executor.execute()
    var y: nbla_DataVariable = executor.get_data_variables()[0]
    var y_data = y.get_float32(cpu_ctx)

    var prediction: int = 0;
    var max_score: float = -1e10;

    for i in range(10):
        if y_data[i] > max_score:
            prediction = i;
            max_score = y_data[i];

    print(prediction)
    print(max_score)


    nbla_SingletonManager.clear()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
    pass
