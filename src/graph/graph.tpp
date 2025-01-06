// Copyright 2024 stranger

namespace s21{

template<typename T>
GraphType Graph<T>::type() const{
    for(unsigned int i = 0; i < vertices_; ++i){
        for(unsigned int j = 0; j < vertices_; ++j){
            if(data_[vertices_ * i + j] != data_[vertices_ * j + i]) return GraphType::Directed;
        }
    }

    return GraphType::Undirected;
}

template<typename T>
bool Graph<T>::loadGraphFromFile(const std::filesystem::path& path){
    if(!std::filesystem::exists(path.c_str())) return false;

    std::fstream f_stream(path, std::ios::in);
    std::stringstream content;
    content << f_stream.rdbuf();
    f_stream.close();

    std::stringstream s_stream(content.str(), std::ios::in);

    std::size_t vertex_number{};
    s_stream >> vertex_number;

    if(s_stream.fail()) return false;

    vertices_ = vertex_number;
    capacity_ = vertex_number * vertex_number;

    if(data_ != nullptr) delete[] data_;

    data_ = new T[capacity_]{};

    std::copy(std::istream_iterator<T>(s_stream), std::istream_iterator<T>(), data_);

    return true;
}

template<typename T>
bool Graph<T>::exportGraphToDot(const std::filesystem::path& path) const{
    if(vertices_ == 0) return false;

    std::filesystem::path filename = path;

    if(filename.extension() != ".dot") filename.replace_extension(std::filesystem::path(".dot"));

    std::fstream f_stream(filename, std::ios::out);

    std::string graphname(filename.stem());
    graphname.erase(std::remove(graphname.begin(), graphname.end(), '\"'), graphname.end());

    if(this->type() == GraphType::Directed){
        f_stream << "digraph " <<  graphname << "{\n";

        for(unsigned int i = 0; i < vertices_; ++i){
            f_stream << "\t" << i + 1 << ";\n";
        }

        for(unsigned int i = 0; i < vertices_; ++i){
            for(unsigned int j = i; j < vertices_; ++j){
                if(data_[vertices_ * i + j] != 0){
                    f_stream << "\t" << i + 1 << " -> " << j + 1 << ";\n";
                }
                else if(data_[vertices_ * j + i] != 0){
                    f_stream << "\t" << j + 1 << " -> " << i + 1 << ";\n";
                }
            }
        }
    }
    else{
        f_stream << "graph " <<  graphname << "{\n";

        for(unsigned int i = 0; i < vertices_; ++i){
            f_stream << "\t" << i + 1 << ";\n";
        }

        for(unsigned int i = 0; i < vertices_; ++i){
            for(unsigned int j = i; j < vertices_; ++j){
                if(data_[vertices_ * i + j] != 0 && data_[vertices_ * j + i] != 0){
                    f_stream << "\t" << i + 1 << " -- " << j + 1 << ";\n";
                }
            }
        }
    }

    f_stream << "}";

    return true;
}

} // namespace s21
