import fs from "fs";
import path from "path";
import { XMLParser } from "fast-xml-parser";
import { sizeof, write_t } from "../../lib/write.js";

class spr_t {
  src;
  img_width;
  img_height;
  spr_width;
  spr_height;
  tile_count;
  columns;
  
  constructor(src, img_width, img_height, spr_width, spr_height, tile_count, columns)
  {
    this.src = src;
    this.img_width = img_width;
    this.img_height = img_height;
    this.spr_width = spr_width;
    this.spr_height = spr_height;
    this.tile_count = tile_count;
    this.columns = columns;
  }
};

function write_spr(spr, spr_path)
{
  const write = new write_t();
  
  write.emit_sz32(spr.src);
  write.emit_u32(spr.img_width);
  write.emit_u32(spr.img_height);
  write.emit_u32(spr.spr_width);
  write.emit_u32(spr.spr_height);
  write.emit_u32(spr.tile_count);
  write.emit_u32(spr.columns);
  
  fs.writeFileSync(spr_path, Buffer.from(write.data()));
}

function tsx_to_spr(tsx_path)
{
  const xml_data = fs.readFileSync(tsx_path);
  
  const options = {
    ignoreAttributes: false,
    attributeNamePrefix: ""
  };
  
  const parser = new XMLParser(options);
  let tsx_spr = parser.parse(xml_data).tileset;
  
  const src = path.parse(tsx_spr.image.source).name;
  
  return new spr_t(
    src,
    tsx_spr.image.width, tsx_spr.image.height,
    tsx_spr.tilewidth, tsx_spr.tileheight,
    tsx_spr.tilecount,
    tsx_spr.columns);
}

function main()
{
  if (process.argv.length != 4) {
    console.log("usage:", path.parse(process.argv[1]).name, "[tsx] [map]");
    process.exit(1);
  }
  
  const tsx_path = process.argv[2];
  const spr_path = process.argv[3];
  
  const spr = tsx_to_spr(tsx_path);
  
  write_spr(spr, spr_path);
}

main();
