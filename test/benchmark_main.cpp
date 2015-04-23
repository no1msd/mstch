#include "mstch/mstch.hpp"

#include <chrono>
#include <iostream>

unsigned long current_msec() {
  return std::chrono::system_clock::now().time_since_epoch() /
      std::chrono::milliseconds(1);
}

int main() {
  std::string comment_tmp{
      "<div class=\"comments\"><h3>{{header}}</h3><ul>"
      "{{#comments}}<li class=\"comment\"><h5>{{name}}</h5>"
      "<p>{{body}}</p></li>{{/comments}}</ul></div>"
  };
  auto comment_view = mstch::map{
      {"header", std::string{"My Post Comments"}},
      {"comments", mstch::array{
          mstch::map{{"name", std::string{"Joe"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::map{{"name", std::string{"Sam"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::map{{"name", std::string{"Heather"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::map{{"name", std::string{"Kathy"}}, {"body", std::string{"Thanks for this post!"}}},
          mstch::map{{"name", std::string{"George"}}, {"body", std::string{"Thanks for this post!"}}}
      }}
  };

  std::vector<unsigned long> times;
  for (int j = 0; j < 10; j++) {
    unsigned long start = current_msec();
    for (int i = 0; i < 5000; i++)
      mstch::render(comment_tmp, comment_view);
    times.push_back(current_msec() - start);
  }

  float avg = 0;
  for (auto i: times)
    avg += i;
  avg /= times.size();

  std::cout << avg << std::endl;

  return 0;
}
