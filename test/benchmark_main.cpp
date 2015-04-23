#include <iostream>

#include <mstch/mstch.hpp>

int main() {
    std::string view{"{{#names}}Hi {{name}}!\n{{/names}}"};
    mstch::map context{
        {"names", mstch::array{
            mstch::map{{"name", std::string{"Chris"}}},
            mstch::map{{"name", std::string{"Mark"}}},
            mstch::map{{"name", std::string{"Scott"}}},
        }}
    };

            std::cout << mstch::render(view, context) << std::endl;

            return 0;
    }