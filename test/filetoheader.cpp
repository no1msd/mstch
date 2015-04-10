#include <iostream>
#include <fstream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

void wrap_data(std::istream& input, std::ostream& output, const std::string& variable_name) {
    output << "const auto " << variable_name << " = ";
    std::string line;
    while (std::getline(input, line)) {
        output << line;
        if(!input.eof()) output << std::endl;
    }
    output << ";" << std::endl;
}

void wrap_string(std::istream& input, std::ostream& output, const std::string& variable_name) {
    output << "const std::string " << variable_name << "{" << std::endl;;
    std::string line;
    while (std::getline(input, line)) {
        boost::replace_all(line, "\\", "\\\\");
        boost::replace_all(line, "\"", "\\\"");
        output << "    \"" << line;
        if(!input.eof()) output << "\\n";
        output << "\"" << std::endl;
    }
    output << "};" << std::endl;
}

int main(int argc, char* argv[]) {
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "show help")
            ("output", po::value<std::string>(), "output file")
            ("namespace", po::value<std::string>(), "namespace to use")
            ("input-string,S", po::value<std::vector<std::string>>(), "files to parse as strings")
            ("input-data,D", po::value<std::vector<std::string>>(), "files to parse as data");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (!vm.count("output")) {
        std::cout << "Output file not set" << std::endl;
        return 1;
    }

    std::ofstream output(vm["output"].as<std::string>(), std::ios::out);

    if(vm.count("namespace"))
        output << "namespace " << vm["namespace"].as<std::string>() << " {" << std::endl;

    for(auto& string_filename: vm["input-string"].as<std::vector<std::string>>()) {
        std::ifstream input(string_filename, std::ios::in);
        wrap_string(input, output, boost::replace_all_copy(string_filename, ".", "_"));
        input.close();
    }

    for(auto& data_filename: vm["input-data"].as<std::vector<std::string>>()) {
        std::ifstream input(data_filename, std::ios::in);
        wrap_data(input, output, boost::replace_all_copy(data_filename, ".", "_"));
        input.close();
    }

    if(vm.count("namespace"))
        output << "}" << std::endl;

    output.close();

    return 0;
}
