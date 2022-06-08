import fs from "fs";
import path from "path";
import { XMLParser } from "fast-xml-parser";
import { sizeof, write_t } from "../../lib/write.js";

class map_t {
  spr;
  width;
  height;
  data;
  
  constructor(spr, width, height, data)
  {
    this.spr = spr;
    this.width = width;
    this.height = height;
    this.data = data;
  }
};

function write_map(map, path)
{
  const write = new write_t();
  
  write.emit_sz32(map.spr);
  write.emit_u32(map.width);
  write.emit_u32(map.height);
  
  for (let i = 0; i < map.data.length; i++)
    write.emit_u32(map.data[i]);
  
  fs.writeFileSync(path, Buffer.from(write.data()));
}

function tmx_to_map(tmx_path)
{
  const xml_data = fs.readFileSync(tmx_path);
  
  const options = {
    ignoreAttributes: false,
    attributeNamePrefix: ""
  };
  
  const parser = new XMLParser(options);
  let tmx_map = parser.parse(xml_data);
  
  const layer_data = tmx_map.map.layer.data["#text"].replace(/\s/g, '').split(',').map((x) => parseInt(x));
  const layer_width = parseInt(tmx_map.map.layer.width);
  const layer_height = parseInt(tmx_map.map.layer.height);
  
  const spr = path.parse(tmx_map.map.tileset.source).name;
  
  return new map_t(spr, layer_width, layer_height, layer_data);
}

function main()
{
  if (process.argv.length != 4) {
    console.log("usage:", path.parse(process.argv[1]).name, "[tmx] [map]");
    process.exit(1);
  }
  
  const tmx_path = process.argv[2];
  const map_path = process.argv[3];
  
  const map = tmx_to_map(tmx_path);
  
  write_map(map, map_path);
}

main();
