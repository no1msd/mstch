const auto grandparent_context_data = mstch::map{
  {"grand_parent_id", std::string{"grand_parent1"}},
  {"parent_contexts", mstch::array{
    mstch::map{
      {"parent_id", std::string{"parent1"}},
      {"child_contexts", mstch::array{
        mstch::map{{"child_id", std::string{"parent1-child1"}}},
        mstch::map{{"child_id", std::string{"parent1-child2"}}}
      }}
    },
    mstch::map{
      {"parent_id", std::string{"parent2"}},
      {"child_contexts", mstch::array{
        mstch::map{{"child_id", std::string{"parent2-child1"}}},
        mstch::map{{"child_id", std::string{"parent2-child2"}}}
      }}
    }
  }}
};