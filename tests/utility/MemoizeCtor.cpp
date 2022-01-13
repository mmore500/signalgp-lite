#include "Catch/single_include/catch2/catch.hpp"

#include "sgpl/utility/MemoizeCtor.hpp"

struct CtorTester {

  inline static thread_local size_t ctor_count{};

  template<typename... Args>
  explicit CtorTester(Args&&...) {
    ++ctor_count;
  };

  CtorTester(const CtorTester&) = default;

  CtorTester(CtorTester&&) = default;

};

TEST_CASE("Test MemoizeCtor") {

  REQUIRE( CtorTester::ctor_count == 0 );

  sgpl::MemoizeCtor<CtorTester>{1.0};
  REQUIRE( CtorTester::ctor_count == 1 );

  sgpl::MemoizeCtor<CtorTester>{1.0};
  sgpl::MemoizeCtor<CtorTester>::lookup(1.0);
  REQUIRE( CtorTester::ctor_count == 1 );

  sgpl::MemoizeCtor<CtorTester>::lookup('a');
  REQUIRE( CtorTester::ctor_count == 2 );

  sgpl::MemoizeCtor<CtorTester>{'b'};
  sgpl::MemoizeCtor<CtorTester>::lookup('b');
  REQUIRE( CtorTester::ctor_count == 3 );

  sgpl::MemoizeCtor<CtorTester>{1};
  REQUIRE( CtorTester::ctor_count == 4);

  sgpl::MemoizeCtor<CtorTester>{1};
  REQUIRE( CtorTester::ctor_count == 4);

  int i{1};
  sgpl::MemoizeCtor<CtorTester>{i};
  sgpl::MemoizeCtor<CtorTester>::lookup(i);
  REQUIRE( CtorTester::ctor_count == 4);

  const int j{1};
  sgpl::MemoizeCtor<CtorTester>{j};
  sgpl::MemoizeCtor<CtorTester>::lookup(j);
  REQUIRE( CtorTester::ctor_count == 4);

}
