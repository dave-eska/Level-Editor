#include"tile.h"

#include<algorithm>
#include<vector>
#include<fstream>
#include<string>
#include<iostream>

#include<raylib.h>

#include<json/value.h>
#include<json/json.h>

#include"global_func.h"

bool compareTiles(Tile& tile1, Tile& tile2){
    return tile1.getZ() < tile2.getZ();
}

std::vector<Tile> loadLevelFromFile(std::string file_path){
    std::vector<Tile> vec;
    std::string text=readFile(file_path);
    Json::Value root;
    Json::Reader jsonreader;

    jsonreader.parse(text, root);

    Vector3 pos;
    int x = 0;
    int y = 0;
    int z = 0;

    Vector2 starting_pos={root["x"].asFloat(), root["y"].asFloat()};
    // Vector2 relative_pos{0, 0}; // we can remake this later, just simplifying things for now

    for (const auto& layer : root["layers"]) {
        y = 0;
        x = 0;
        for (const auto& e : layer.asString()) {
            if (e == '\n') {
                y++;
                x=0;
            } else if (isdigit(e)) {
                Tile tile = Tile(e-'0', {starting_pos.x+x*TILE_SIZE, starting_pos.y+(y*TILE_SIZE)}, z);
                vec.push_back(tile);
                x++;
            }
        }
        z++;
    }
   
    for(Tile e:vec){
        if(e.getName()=="itemarea"){
            int probability=GetRandomValue(0,5);
            if(probability == 2 or probability == 3){
                vec.push_back(Tile(probability, {e.getX(), e.getY()}, e.getZ()+1));
            }
        }
    }

    std::sort(vec.begin(), vec.end(), compareTiles);

    return vec;
}


void Tile::Draw(bool is_debugging){
    DrawTexturePro(texture, {0,0,32,32}, {body.x,body.y,TILE_SIZE,TILE_SIZE}, {0,0}, 0, WHITE);

    if(is_debugging){
        DrawTextureEx(debugbox, {body.x, body.y}, 0, 3, WHITE);
        DrawText(name.c_str(), body.x+7, body.y, 20, BLACK);

        //Position
        DrawText(std::to_string((int)body.x).c_str(), body.x+7, body.y+20, 20, BLACK);
        DrawText(std::to_string((int)body.y).c_str(), body.x+7, body.y+40, 20, BLACK);
        DrawText(std::to_string((int)z_level).c_str(), body.x+7, body.y+60, 20, BLACK);
    }
}

Tile::Tile(){
}

Tile::Tile(int id, Vector2 pos, int z_level){
    //Debug Variables
    isTouchingMouse=false;
    isRunningAnimation=false;

    debugbox=LoadTexture("res/img/debugbox.png");

    std::vector<std::string> file_names=getAllFileNamesInDirectory("res/items/");
    Json::Reader jsonreader;

    for(auto &e:file_names){
        std::ifstream file("res/items/"+e);
        Json::Value jsonvalue;
        jsonreader.parse(file, jsonvalue);

        //Cheecking if id is the same
        if(jsonvalue["id"].asInt()==id){
            body = {
                pos.x,
                pos.y,
                TILE_SIZE,
                TILE_SIZE
            };
            this->z_level=z_level;
            this->name = jsonvalue["name"].asString();
            this->id = jsonvalue["id"].asInt();
            this->type = jsonvalue["type"].asString();
            this->hasAnimation = jsonvalue["animation"].asBool();
            this->hasCollision = jsonvalue["collision"].asBool();

            if(jsonvalue.isMember("texture")){
                texture=LoadTexture(jsonvalue["texture"].asString().c_str());
            }else{
                int probability=GetRandomValue(1,2);
                if(probability==1) texture=LoadTexture(jsonvalue["texture1"].asString().c_str());
                if(probability==2) texture=LoadTexture(jsonvalue["texture2"].asString().c_str());
            }
        }
    }
}
