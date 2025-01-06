// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_TSM_RESULT_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_TSM_RESULT_HPP_

#include <vector>

namespace s21{

struct TsmResult final{
    std::vector<unsigned int> vertices_;
    double distance_;
};

} // namespace s21

#endif // _A2_SIMPLE_NAVIGATOR_SRC_ALGORITHMS_TSM_RESULT_HPP_