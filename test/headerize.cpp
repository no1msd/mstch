#include <iostream>
#include <fstream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

void wrap_string(std::istream& input, std::ostream& output,
    const std::string& variable_name)
{
  output << "const std::string " << variable_name << "{\n";
  std::string line;
  while (std::getline(input, line)) {
    boost::replace_all(line, "\\", "\\\\");
    boost::replace_all(line, "\"", "\\\"");
    output << "  \"" << line;
    if (!input.eof())
      output << "\\n";
    output << "\"\n";
  }
  output << "};\n";
}

int main(int argc, char* argv[]) {
  namespace po = boost::program_options;

  po::options_description desc("Allowed options");
  desc.add_options()
      ("help", "show help")
      ("output", po::value<std::string>(), "output file")
      ("namespace", po::value<std::string>(), "namespace to use")
      ("input-string,S", po::value<std::vector<std::string>>(),
          "files to parse as strings")
      ("input-code,C", po::value<std::vector<std::string>>(),
          "files to parse as code");
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  if (!vm.count("output")) {
    std::cerr << "Output file not set" << std::endl;
    return 1;
  }

  std::ofstream output(vm["output"].as<std::string>(), std::ios::out);

  if (vm.count("namespace"))
    output << "namespace " << vm["namespace"].as<std::string>() << " {\n";

  if (vm.count("input-string"))
    for (auto& filename: vm["input-string"].as<std::vector<std::string>>()) {
      std::ifstream input(filename, std::ios::in);
      wrap_string(input, output, boost::replace_all_copy(filename, ".", "_"));
      input.close();
    }

  if (vm.count("input-code"))
    for (auto& filename: vm["input-code"].as<std::vector<std::string>>()) {
      std::ifstream input(filename, std::ios::in);
      output << std::string{(std::istreambuf_iterator<char>(input)),
          std::istreambuf_iterator<char>()} << std::endl;
      input.close();
    }

  if (vm.count("namespace"))
    output << "}\n";

  output.close();

  return 0;
}
