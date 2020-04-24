#!/usr/bin/python3
import sys, xml.etree.ElementTree as ET

try:
    file_entity = sys.argv[1]
    file_map = sys.argv[2]
    elements_to_get_rid_of = sys.argv[3:]
except IndexError:
    print(f"Usage: {sys.argv[0]} file entity file map items to get rid of")
    sys.exit(1)
treemap = ET.parse(file_map)
rootmap = treemap.getroot()
tree = ET.parse(file_entity)
root = tree.getroot()
for entity in root.findall("gc_entity"):
    attribs = entity.find('map_linker').attrib
    attribs['name'] = entity.find("renderer").get("src")
    #print(f"x:{attribs['x']} y:{attribs['y']} name:{attribs['name']}")
    if not (attribs['name'] in elements_to_get_rid_of):
        continue
    for tile in rootmap.findall("./tiles_data/tile"):
        tile_info = tile.attrib
    # print(f"x:{tile_info['x']} y:{tile_info['y']} texture:{tile_info['texture']}")

        if not (tile_info['x'] == attribs['x'] and tile_info['y'] == attribs['y']):
            continue
        if (tile_info['texture'] == "grass_top" or tile_info['texture'] == "stone"):
            continue
        root.remove(entity)
        break
tree.write(file_entity)