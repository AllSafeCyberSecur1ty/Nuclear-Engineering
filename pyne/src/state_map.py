# -*- coding: utf-8 -*-
"""
This script generates the state_map.h file from nuc_data.h5
"""
import tables as tb

from pyne import nuc_data


def generate_state_id_map(nuc_data):
    f = tb.open_file(nuc_data)

    with open("state_map.cpp", "w") as sm:
        sm.write("//Mapping file for state ids to nuc ids\n")
        sm.write("//This File was autogenerated!!\n")
        sm.write("#ifndef PYNE_4HFU6PUEQJB3ZJ4UIFLVU4SPCM\n")
        sm.write("#define PYNE_4HFU6PUEQJB3ZJ4UIFLVU4SPCM\n")
        sm.write("namespace pyne {\n")
        sm.write("namespace nucname {\n")
        lastnuc = 0
        count = 0
        for item in f.root.decay.level_list:
            if item["metastable"] > 0 and item["nuc_id"] != lastnuc:
                lastnuc = item["nuc_id"]
                count = count + 1
        sm.write("#define TOTAL_STATE_MAPS " + str(count) + "\n")
        sm.write("std::map<int, int> state_id_map;\n")
        sm.write("int map_nuc_ids [TOTAL_STATE_MAPS] = {")
        for item in f.root.decay.level_list:
            if item["metastable"] > 0 and item["nuc_id"] != lastnuc:
                lastnuc = item["nuc_id"]
                sm.write(str(item["nuc_id"]) + ",\n")
        sm.write("};\n")
        sm.write("int map_metastable [TOTAL_STATE_MAPS] = {")
        for item in f.root.decay.level_list:
            if item["metastable"] > 0 and item["nuc_id"] != lastnuc:
                lastnuc = item["nuc_id"]
                sm.write(str(item["metastable"]) + ",\n")
        sm.write("};\n")
        sm.write("}\n")
        sm.write("}\n")
        sm.write("#endif")


if __name__ == "__main__":
    generate_state_id_map(nuc_data)
