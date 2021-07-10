#ifndef TEST_CORE_HPP
#define TEST_CORE_HPP

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <tuple>

template<class PARAM>
class TestCore : public ::testing::TestWithParam<PARAM> {
protected:
    size_t nobs, ndim;
    std::vector<double> data;
protected:
    void assemble(const PARAM& param) {
        std::mt19937_64 rng(42);
        std::normal_distribution distr;

        nobs = std::get<0>(param);
        ndim = std::get<1>(param);
        data.resize(nobs * ndim);
        for (auto& d : data) {
            d = distr(rng);
        }

        return;
    }

    void sanity_checks(const std::vector<int>& neighbors, const std::vector<double>& distances, int k) { // for finding by vector
        EXPECT_EQ(neighbors.size(), distances.size());
        EXPECT_EQ(neighbors.size(), std::min(k, (int)nobs));
        for (size_t i = 1; i < distances.size(); ++i) { // check for sortedness.
            EXPECT_TRUE(distances[i] >= distances[i-1]);
        }
    }

    void sanity_checks(const std::vector<int>& neighbors, const std::vector<double>& distances, int k, int index) const { // for finding by index
        EXPECT_EQ(neighbors.size(), distances.size());
        EXPECT_EQ(neighbors.size(), std::min(k, (int)nobs - 1));

        for (size_t i = 1; i < distances.size(); ++i) { // check for sortedness.
            EXPECT_TRUE(distances[i] >= distances[i-1]);
        }

        for (auto i : neighbors) { // self is not in there.
            EXPECT_TRUE(i != index);
        }
    }
};

#endif