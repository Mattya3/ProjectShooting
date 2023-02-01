#include <element/texture/ImageManager.hpp>
#include <DataOf2D.hpp>
namespace sbfw {
namespace texture {
std::pair<int, DataOf2D> ImageManager::provide_png(std::string fname) {

    using std::filesystem::current_path;
    std::string filename =
        (current_path() / std::filesystem::path("img/" + fname)).c_str();

    if(!std::filesystem::exists(filename)) {
        std::cerr << "Not found " << filename << '\n';
        exit(1);
    }
    auto it = loaded_pngs.find(fname);
    if(it != loaded_pngs.end()) {
        return std::make_pair(it->second, pngdata.get_len(it->second));
    } else {
        ++id;
        auto nit = loaded_pngs.emplace(fname, id);
        pngdata.load_png(filename, id);
        return std::make_pair(id, pngdata.get_len(id));
    }
}}

}