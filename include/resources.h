#pragma once
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(algos_resources);
namespace algos_resources{
  auto getResourceFile(std::string path){
    auto fs = cmrc::algos_resources::get_filesystem();
    if(!fs.exists(path)){
      throw std::runtime_error("Failed to load " + path + " from resources");
    }
    return fs.open(path);
  }
}
