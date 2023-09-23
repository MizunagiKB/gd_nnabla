# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2023 MizunagiKB <mizukb@live.jp>
import io
import sys
import yaml
import jinja2

jinja2_env = jinja2.Environment(loader=jinja2.FileSystemLoader("./src.gen"))


def generate_cpp(category: str, dict_group: dict, io_s: io.StringIO):
    for fn in dict_group[category].keys():
        x = dict_group[category][fn]
        fn_snake_name = x["snake_name"]

        if fn_snake_name in ("sync_batch_normalization"):
            continue

        list_params = []
        for k, v in x["inputs"].items():
            list_params.append('"{:s}"'.format(k))

        if "arguments" in x:
            for k, v in x["arguments"].items():
                list_params.append('"{:s}"'.format(k))

        tpl = jinja2_env.get_template("cpp.jinja2")
        v = tpl.render({"fn": fn_snake_name, "params": ", ".join(list_params)})

        io_s.write(v + "\n")


def generate_hpp(category: str, dict_group: dict, io_s: io.StringIO):
    for fn in dict_group[category].keys():
        x = dict_group[category][fn]
        fn_snake_name = x["snake_name"]

        if fn_snake_name in ("sync_batch_normalization"):
            continue

        list_i = []
        for k, v in x["inputs"].items():
            list_i.append("Ref<nbla_DataVariable> {:s}".format(k))

        list_a = []
        if "arguments" in x:
            for k, v in x["arguments"].items():
                type_name = ""
                match v["type"]:
                    case "bool":
                        type_name = "bool"
                    case "double":
                        type_name = "double"
                    case "float":
                        type_name = "float"
                    case "int64":
                        type_name = "int"
                    case "repeated int64":
                        type_name = "PackedInt64Array"
                    case "repeated float":
                        type_name = "PackedFloat32Array"
                    case "Shape":
                        type_name = "PackedInt32Array"
                    case "string":
                        type_name = "String"
                    case _:
                        type_name = v["type"]
                        print(k, v)
                        sys.exit()
                list_a.append("{:s} {:s}".format(type_name, k))

        tpl = jinja2_env.get_template("hpp.jinja2")
        v = tpl.render(
            {
                "fn": fn_snake_name,
                "inputs": ", ".join(list_i),
                "arguments": ", ".join(list_a),
            }
        )

        io_s.write(v + "\n")


def main():
    # dir_name, _ = os.path.split(sys.argv[0])
    with open(
        "./thirdparty/nnabla/build-tools/code_generator/functions.yaml",
        "r",
    ) as rf:
        dict_function = yaml.safe_load(rf)

        io_hpp = io.StringIO()
        io_cpp = io.StringIO()

        for category in dict_function.keys():
            io_hpp.write("// {:s}\n".format(category))
            generate_hpp(category, dict_function, io_hpp)
            io_cpp.write("// {:s}\n".format(category))
            generate_cpp(category, dict_function, io_cpp)

        with open("./src/gd_nbla_function.hpp.inc", "w") as wf:
            wf.write(io_hpp.getvalue())

        with open("./src/gd_nbla_function.cpp.inc", "w") as wf:
            wf.write(io_cpp.getvalue())


if __name__ == "__main__":
    main()
