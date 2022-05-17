#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

auto get_file_size(const std::filesystem::path& path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path))
    {
        auto file_size = std::filesystem::file_size(path);

        if (file_size != static_cast <uintmax_t> (-1))
        {
            return file_size;
        }
    }

    return static_cast <uintmax_t> (-1);
}

auto get_directory_size(const std::filesystem::path& path)
{
    uintmax_t size = 0ULL;

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        for (auto const& entry : std::filesystem::recursive_directory_iterator(path))
        {
            if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
            {
                auto file_size = std::filesystem::file_size(entry);

                if (file_size != static_cast <uintmax_t> (-1))
                {
                    size += file_size;
                }
            }
        }
    }

    return size;
}

void print_content(const std::filesystem::path& path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            auto file_name = entry.path().filename().string();

            std::cout << file_name << std::endl;
        }
    }
}

int main()
{
    std::cout << get_file_size("./") << std::endl;

    std::cout << get_directory_size(std::filesystem::current_path()) << std::endl;

    print_content(std::filesystem::current_path());

}