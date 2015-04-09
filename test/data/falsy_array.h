auto data = mstch::object{
  {"list", mstch::array{
  	mstch::array{std::string{""}, std::string{"emptyString"}},
  	mstch::array{mstch::array{}, std::string{"emptyArray"}},
  	mstch::array{0, std::string{"zero"}},
  	mstch::array{mstch::node{}, std::string{"null"}}
  }}
};
