#!/usr/bin/python3
import sys, xml.etree.ElementTree as ET

try:
    file_entity = sys.argv[1]
except IndexError:
    print(f"Usage: {sys.argv[0]} file entity")
    sys.exit(1)
tree = ET.parse(file_entity)
root = tree.getroot()
for entity in root.findall("./tiles_data/tile"):
    attribs = entity.attrib
    #print(f"check for x:{attribs['x']} y:{attribs['y']}")
    if (attribs['texture'] != ""):
        continue
    #print(f"x:{attribs['x']} y:{attribs['y']}")
    attribs['solid'] = "true"

tree.write(file_entity)