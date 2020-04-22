#!/usr/bin/python3
import sys, xml.etree.ElementTree as ET

try:
    file_entity = sys.argv[1]
    elements_to_get_rid_of = sys.argv[2:]
except IndexError:
    print(f"Usage: {sys.argv[0]} file entity")
    sys.exit(1)
tree = ET.parse(file_entity)
root = tree.getroot()
for entity in root.findall("gc_entity"):
    attribs = entity.find('map_linker').attrib
    attribs['name'] = entity.find("renderer").get("src")
    #print(f"x:{attribs['x']} y:{attribs['y']} name:{attribs['name']}")
    if (attribs['name'] in elements_to_get_rid_of):
        continue
    attribs['centered'] = "true"

tree.write(file_entity)