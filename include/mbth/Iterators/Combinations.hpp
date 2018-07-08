#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

namespace mbth::Iterators {
namespace Detail {
template <typename Container>
class BitChooseIterator {
public:
    using const_reference = typename Container::const_reference;

    BitChooseIterator(const Container& container, const std::vector<bool>& bits)
        : container_{container}
        , bits_{bits}
        , currentIndex_{nextIndex(0)}
    {
    }

    BitChooseIterator& operator++()
    {
        currentIndex_ = nextIndex(currentIndex_ + 1);
        return *this;
    }

    const BitChooseIterator operator++(int) { return operator++(); }

    bool operator==(const BitChooseIterator& rhs) const
    {
        return currentIndex_ == rhs.currentIndex_;
    }

    bool operator!=(const BitChooseIterator& rhs) const
    {
        return !(*this == rhs);
    }

    const_reference operator*() const { return container_[currentIndex_]; }

    BitChooseIterator end() const
    {
        auto it = *this;
        it.currentIndex_ = bits_.size();
        return it;
    }

private:
    const Container& container_;
    const std::vector<bool>& bits_;
    std::size_t currentIndex_;

    std::size_t nextIndex(std::size_t start)
    {
        for (std::size_t i = start; i < bits_.size(); ++i) {
            if (bits_[i]) {
                return i;
            }
        }
        return bits_.size();
    }
};

template <typename Container>
class BitChooseRange {
public:
    using Iterator = BitChooseIterator<Container>;

    BitChooseRange(const Container& container, const std::vector<bool>& bits)
        : begin_{container, bits}
    {
    }

    Iterator begin() { return begin_; }
    Iterator end() { return begin_.end(); }

private:
    Iterator begin_;
};

template <typename Container>
auto makeChooseRange(const Container& container, const std::vector<bool>& bits)
{
    return BitChooseRange<Container>(container, bits);
}

// TODO: more efficient implementation
template <typename Container>
class CombinationsIterator {
public:
    CombinationsIterator(const Container& container, std::size_t k)
        : container_{container}
        , n_{container.size()}
        , k_{k}
        , mask_(n_)
    {
        assert(n_ >= k_);
        std::fill_n(std::rbegin(mask_), k_, true);
    }

    CombinationsIterator& operator++()
    {
        std::next_permutation(std::begin(mask_), std::end(mask_));
        count_ += 1;
        return *this;
    }

    const CombinationsIterator operator++(int) { return operator++(); }

    bool operator==(const CombinationsIterator& rhs) const
    {
        return count_ == rhs.count_;
    }

    bool operator!=(const CombinationsIterator& rhs) const
    {
        return !(*this == rhs);
    }

    BitChooseRange<Container> operator*() const
    {
        return makeChooseRange(container_, mask_);
    }

    CombinationsIterator end() const
    {
        std::size_t p = 1;
        std::size_t q = 1;
        for (std::size_t i = k_; i != 0; --i) {
            p *= n_ - (k_ - i);
            q *= i;
        }

        CombinationsIterator it(container_, k_);
        it.count_ = p / q;
        return it;
    }

private:
    const Container& container_;
    const std::size_t n_;
    const std::size_t k_;
    std::size_t count_ = 0;
    std::vector<bool> mask_;
};

template <typename Container>
class CombinationsRange {
public:
    using Iterator = CombinationsIterator<Container>;

    CombinationsRange(const Container& container, std::size_t k)
        : begin_{container, k}
    {
    }

    Iterator begin() { return begin_; }
    Iterator end() { return begin_.end(); }

private:
    Iterator begin_;
};

template <typename Container>
auto makeCombinationsRange(const Container& container, std::size_t k)
{
    return CombinationsRange<Container>(container, k);
}
} // namespace Detail

template <typename Container>
auto combinations(const Container& container, std::size_t k)
{
    return Detail::makeCombinationsRange(container, k);
}
} // namespace mbth::Iterators
