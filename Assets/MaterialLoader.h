#pragma once
#include "Material.h"
#include <string>
#include "AssetManager.h"
#include "AssetLoader.h"

void AssetLoader<Material>::load(std::string file, Material& location);