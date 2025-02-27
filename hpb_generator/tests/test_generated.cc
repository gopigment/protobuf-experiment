// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include <cstdint>
#include <iterator>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "google/protobuf/compiler/hpb/tests/child_model.upb.proto.h"
#include "google/protobuf/compiler/hpb/tests/no_package.upb.proto.h"
#include "google/protobuf/compiler/hpb/tests/test_extension.upb.proto.h"
#include "google/protobuf/compiler/hpb/tests/test_model.upb.proto.h"
#include "google/protobuf/hpb/hpb.h"
#include "google/protobuf/hpb/repeated_field.h"
#include "google/protobuf/hpb/requires.h"
#include "upb/mem/arena.h"
#include "upb/mem/arena.hpp"

namespace {

using ::hpb::internal::Requires;
using ::hpb_unittest::protos::ChildModel1;
using ::hpb_unittest::protos::container_ext;
using ::hpb_unittest::protos::ContainerExtension;
using ::hpb_unittest::protos::other_ext;
using ::hpb_unittest::protos::RED;
using ::hpb_unittest::protos::TestEnum;
using ::hpb_unittest::protos::TestModel;
using ::hpb_unittest::protos::TestModel_Category;
using ::hpb_unittest::protos::TestModel_Category_IMAGES;
using ::hpb_unittest::protos::TestModel_Category_NEWS;
using ::hpb_unittest::protos::TestModel_Category_VIDEO;
using ::hpb_unittest::protos::theme;
using ::hpb_unittest::protos::ThemeExtension;
using ::testing::ElementsAre;

TEST(CppGeneratedCode, Constructor) { TestModel test_model; }

TEST(CppGeneratedCode, MessageEnum) { EXPECT_EQ(5, TestModel_Category_IMAGES); }

TEST(CppGeneratedCode, ImportedEnum) { EXPECT_EQ(3, TestEnum::DEVICE_MONITOR); }

TEST(CppGeneratedCode, Enum) { EXPECT_EQ(1, RED); }

TEST(CppGeneratedCode, EnumNoPackage) { EXPECT_EQ(1, ::hpb_CELSIUS); }

TEST(CppGeneratedCode, MessageEnumType) {
  TestModel_Category category1 = TestModel_Category_IMAGES;
  TestModel::Category category2 = TestModel::IMAGES;
  EXPECT_EQ(category1, category2);
}

TEST(CppGeneratedCode, MessageEnumValue) {
  EXPECT_EQ(TestModel_Category_IMAGES, TestModel::IMAGES);
}

TEST(CppGeneratedCode, ArenaConstructor) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(false, testModel.has_b1());
}

TEST(CppGeneratedCode, Booleans) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_FALSE(testModel.b1());
  testModel.set_b1(true);
  EXPECT_TRUE(testModel.b1());
  testModel.set_b1(false);
  EXPECT_FALSE(testModel.b1());
  testModel.set_b1(true);
  EXPECT_TRUE(testModel.b1());
  testModel.clear_b1();
  EXPECT_FALSE(testModel.has_b1());
}

TEST(CppGeneratedCode, ScalarInt32) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  // Test int32 defaults.
  EXPECT_EQ(testModel.value(), 0);
  EXPECT_FALSE(testModel.has_value());
  // Floating point defaults.
  EXPECT_EQ(std::numeric_limits<float>::infinity(),
            testModel.float_value_with_default());
  EXPECT_EQ(-std::numeric_limits<double>::infinity(),
            testModel.double_value_with_default());

  // Set value.
  testModel.set_value(5);
  EXPECT_TRUE(testModel.has_value());
  EXPECT_EQ(testModel.value(), 5);
  // Change value.
  testModel.set_value(10);
  EXPECT_TRUE(testModel.has_value());
  EXPECT_EQ(testModel.value(), 10);
  // Clear value.
  testModel.clear_value();
  EXPECT_FALSE(testModel.has_value());
  EXPECT_EQ(testModel.value(), 0);
}

const char kTestStr1[] = "abcdefg";
const char kTestStr2[] = "just another test string";

TEST(CppGeneratedCode, Strings) {
  TestModel testModel;
  testModel.set_str1(kTestStr1);
  testModel.set_str2(kTestStr2);
  EXPECT_EQ(testModel.str1(), kTestStr1);
  EXPECT_EQ(testModel.str2(), kTestStr2);
  EXPECT_TRUE(testModel.has_str1());
  EXPECT_TRUE(testModel.has_str2());

  testModel.clear_str1();
  EXPECT_FALSE(testModel.has_str1());
  EXPECT_TRUE(testModel.has_str2());
}

TEST(CppGeneratedCode, ScalarUInt32) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  // Test defaults.
  EXPECT_EQ(testModel.optional_uint32(), 0);
  EXPECT_FALSE(testModel.has_optional_uint32());
  // Set value.
  testModel.set_optional_uint32(0xA0001000);
  EXPECT_TRUE(testModel.has_optional_uint32());
  EXPECT_EQ(testModel.optional_uint32(), 0xA0001000);
  // Change value.
  testModel.set_optional_uint32(0x70002000);
  EXPECT_TRUE(testModel.has_optional_uint32());
  EXPECT_EQ(testModel.optional_uint32(), 0x70002000);
  // Clear value.
  testModel.clear_optional_uint32();
  EXPECT_FALSE(testModel.has_optional_uint32());
  EXPECT_EQ(testModel.optional_uint32(), 0);
}

TEST(CppGeneratedCode, ScalarInt64) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  // Test defaults.
  EXPECT_EQ(testModel.optional_int64(), 0);
  EXPECT_FALSE(testModel.has_optional_int64());
  // Set value.
  testModel.set_optional_int64(static_cast<int64_t>(0xFF00CCDDA0001000));
  EXPECT_TRUE(testModel.has_optional_int64());
  EXPECT_EQ(testModel.optional_int64(), 0xFF00CCDDA0001000);
  // Change value.
  testModel.set_optional_int64(static_cast<int64_t>(0xFF00CCDD70002000));
  EXPECT_TRUE(testModel.has_optional_int64());
  EXPECT_EQ(testModel.optional_int64(), 0xFF00CCDD70002000);
  // Clear value.
  testModel.clear_optional_int64();
  EXPECT_FALSE(testModel.has_optional_int64());
  EXPECT_EQ(testModel.optional_int64(), 0);
  // Set after clear.
  testModel.set_optional_int64(static_cast<int64_t>(0xFF00CCDDA0001000));
  EXPECT_TRUE(testModel.has_optional_int64());
  EXPECT_EQ(testModel.optional_int64(), 0xFF00CCDDA0001000);
}

TEST(CppGeneratedCode, ScalarFloat) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  // Test defaults.
  EXPECT_EQ(testModel.optional_float(), 0.0f);
  EXPECT_FALSE(testModel.has_optional_float());
  EXPECT_EQ(std::numeric_limits<float>::infinity(),
            testModel.float_value_with_default());
  EXPECT_EQ(-std::numeric_limits<double>::infinity(),
            testModel.double_value_with_default());
  // Set value.
  testModel.set_optional_float(3.14159265f);
  EXPECT_TRUE(testModel.has_optional_float());
  EXPECT_NEAR(testModel.optional_float(), 3.14159265f, 1e-9f);
  // Change value.
  testModel.set_optional_float(-2.0f);
  EXPECT_TRUE(testModel.has_optional_float());
  EXPECT_NEAR(testModel.optional_float(), -2, 1e-9f);
  // Clear value.
  testModel.clear_optional_float();
  EXPECT_FALSE(testModel.has_optional_float());
  EXPECT_EQ(testModel.optional_float(), 0.0f);
  // Set after clear.
  testModel.set_optional_float(3.14159265f);
  EXPECT_TRUE(testModel.has_optional_float());
  EXPECT_NEAR(testModel.optional_float(), 3.14159265f, 1e-9f);
}

TEST(CppGeneratedCode, ScalarDouble) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);
  // Test defaults.
  EXPECT_EQ(testModel.optional_double(), 0.0);
  EXPECT_FALSE(testModel.has_optional_double());
  // Set value.
  testModel.set_optional_double(3.141592653589793);
  EXPECT_TRUE(testModel.has_optional_double());
  EXPECT_NEAR(testModel.optional_double(), 3.141592653589793, 1e-16f);
  // Change value.
  testModel.set_optional_double(-1.0);
  EXPECT_TRUE(testModel.has_optional_double());
  EXPECT_NEAR(testModel.optional_double(), -1.0, 1e-16f);
  // Clear value.
  testModel.clear_optional_double();
  EXPECT_FALSE(testModel.has_optional_double());
  EXPECT_EQ(testModel.optional_double(), 0.0f);
  // Set after clear.
  testModel.set_optional_double(3.141592653589793);
  EXPECT_TRUE(testModel.has_optional_double());
  EXPECT_NEAR(testModel.optional_double(), 3.141592653589793, 1e-16f);
}

TEST(CppGeneratedCode, Enums) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);

  // Check enum default value.
  EXPECT_EQ(TestModel_Category_IMAGES, 5);

  // Test defaults.
  EXPECT_FALSE(testModel.has_category());
  EXPECT_EQ(testModel.category(), TestModel_Category_IMAGES);
  // Set value.
  testModel.set_category(TestModel_Category_NEWS);
  EXPECT_TRUE(testModel.has_category());
  EXPECT_EQ(testModel.category(), TestModel_Category_NEWS);
  // Change value.
  testModel.set_category(TestModel_Category_VIDEO);
  EXPECT_TRUE(testModel.has_category());
  EXPECT_EQ(testModel.category(), TestModel_Category_VIDEO);
  // Clear value.
  testModel.clear_category();
  EXPECT_FALSE(testModel.has_category());
  EXPECT_EQ(testModel.category(), TestModel_Category_IMAGES);
  // Set after clear.
  testModel.set_category(TestModel_Category_VIDEO);
  EXPECT_TRUE(testModel.has_category());
  EXPECT_EQ(testModel.category(), TestModel_Category_VIDEO);
}

TEST(CppGeneratedCode, FieldWithDefaultValue) {
  ::hpb::Arena arena;
  auto testModel = ::hpb::CreateMessage<TestModel>(arena);

  EXPECT_FALSE(testModel.has_int_value_with_default());
  EXPECT_EQ(testModel.int_value_with_default(), 65);
  testModel.set_int_value_with_default(10);
  EXPECT_EQ(testModel.int_value_with_default(), 10);

  EXPECT_FALSE(testModel.has_string_value_with_default());
  EXPECT_EQ(testModel.string_value_with_default(), "hello");
  testModel.set_string_value_with_default("new string");
  EXPECT_EQ(testModel.string_value_with_default(), "new string");
}

TEST(CppGeneratedCode, OneOfFields) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);

  EXPECT_FALSE(test_model.has_oneof_member1());
  EXPECT_FALSE(test_model.has_oneof_member2());
  EXPECT_EQ(TestModel::CHILD_ONEOF1_NOT_SET, test_model.child_oneof1_case());

  test_model.set_oneof_member1("one of string");
  EXPECT_TRUE(test_model.has_oneof_member1());
  EXPECT_FALSE(test_model.has_oneof_member2());
  EXPECT_EQ(test_model.oneof_member1(), "one of string");
  EXPECT_EQ(TestModel::kOneofMember1, test_model.child_oneof1_case());

  test_model.set_oneof_member2(true);
  EXPECT_FALSE(test_model.has_oneof_member1());
  EXPECT_TRUE(test_model.has_oneof_member2());
  EXPECT_EQ(test_model.oneof_member2(), true);
  EXPECT_EQ(TestModel::kOneofMember2, test_model.child_oneof1_case());

  test_model.clear_oneof_member2();
  EXPECT_FALSE(test_model.has_oneof_member1());
  EXPECT_FALSE(test_model.has_oneof_member2());
  EXPECT_EQ(test_model.oneof_member1(), "");
  EXPECT_EQ(test_model.oneof_member2(), false);
  EXPECT_EQ(TestModel::CHILD_ONEOF1_NOT_SET, test_model.child_oneof1_case());
}

TEST(CppGeneratedCode, Messages) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(false, test_model.has_child_model_1());
  auto child_model = test_model.child_model_1();
  EXPECT_EQ(false, child_model->has_child_b1());
  EXPECT_EQ(false, child_model->child_b1());
  auto mutable_child = test_model.mutable_child_model_1();
  mutable_child->set_child_b1(true);
  EXPECT_EQ(true, mutable_child->has_child_b1());
  EXPECT_EQ(true, mutable_child->child_b1());
  // The View should not change due to mutation since it
  // is default_instance.
  EXPECT_EQ(false, child_model->has_child_b1());
  // Readonly View should now show change.
  child_model = test_model.child_model_1();
  EXPECT_EQ(true, child_model->has_child_b1());
  EXPECT_EQ(true, child_model->child_b1());
  // Clear message field.
  EXPECT_EQ(true, test_model.has_child_model_1());
  test_model.clear_child_model_1();
  EXPECT_EQ(false, test_model.has_child_model_1());
}

TEST(CppGeneratedCode, NestedMessages) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  auto nested_child = test_model.nested_child_1();
  EXPECT_EQ(0, nested_child->nested_child_name().size());
  auto mutable_nested_child = test_model.mutable_nested_child_1();
  EXPECT_EQ(false, mutable_nested_child->has_nested_child_name());
  mutable_nested_child->set_nested_child_name(kTestStr1);
  EXPECT_EQ(true, mutable_nested_child->has_nested_child_name());
}

TEST(CppGeneratedCode, RepeatedMessages) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.child_models_size());
  // Should be able to clear repeated field when empty.
  test_model.mutable_child_models()->clear();
  EXPECT_EQ(0, test_model.child_models_size());
  // Add 2 children.
  auto new_child = test_model.add_child_models();
  EXPECT_EQ(true, new_child.ok());
  new_child.value()->set_child_str1(kTestStr1);
  new_child = test_model.add_child_models();
  EXPECT_EQ(true, new_child.ok());
  new_child.value()->set_child_str1(kTestStr2);
  EXPECT_EQ(2, test_model.child_models_size());
  // Mutable access.
  auto mutable_first = test_model.mutable_child_models(0);
  EXPECT_EQ(mutable_first->child_str1(), kTestStr1);
  mutable_first->set_child_str1("change1");
  auto mutable_second = test_model.mutable_child_models(1);
  EXPECT_EQ(mutable_second->child_str1(), kTestStr2);
  mutable_second->set_child_str1("change2");
  // Check mutations using views.
  auto view_first = test_model.child_models(0);
  EXPECT_EQ(view_first->child_str1(), "change1");
  auto view_second = test_model.child_models(1);
  EXPECT_EQ(view_second->child_str1(), "change2");
}

TEST(CppGeneratedCode, RepeatedScalar) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.value_array_size());
  // Should be able to clear repeated field when empty.
  test_model.mutable_value_array()->clear();
  EXPECT_EQ(0, test_model.value_array_size());
  // Add 2 children.
  EXPECT_EQ(true, test_model.add_value_array(5));
  EXPECT_EQ(true, test_model.add_value_array(6));
  EXPECT_EQ(2, test_model.value_array_size());
  EXPECT_EQ(5, test_model.value_array(0));
  EXPECT_EQ(6, test_model.value_array(1));
  EXPECT_EQ(true, test_model.resize_value_array(3));
  EXPECT_EQ(3, test_model.value_array_size());
  test_model.set_value_array(2, 7);
  EXPECT_EQ(5, test_model.value_array(0));
  EXPECT_EQ(6, test_model.value_array(1));
  EXPECT_EQ(7, test_model.value_array(2));
}

TEST(CppGeneratedCode, RepeatedFieldClear) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  test_model.mutable_value_array()->push_back(5);
  test_model.mutable_value_array()->push_back(16);
  test_model.mutable_value_array()->push_back(27);
  ASSERT_EQ(test_model.mutable_value_array()->size(), 3);
  test_model.mutable_value_array()->clear();
  EXPECT_EQ(test_model.mutable_value_array()->size(), 0);
}

TEST(CppGeneratedCode, RepeatedFieldProxyForScalars) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.value_array().size());
  EXPECT_EQ(0, test_model.mutable_value_array()->size());

  test_model.mutable_value_array()->push_back(5);
  test_model.mutable_value_array()->push_back(16);
  test_model.mutable_value_array()->push_back(27);

  ASSERT_EQ(test_model.mutable_value_array()->size(), 3);
  EXPECT_EQ((*test_model.mutable_value_array())[0], 5);
  EXPECT_EQ((*test_model.mutable_value_array())[1], 16);
  EXPECT_EQ((*test_model.mutable_value_array())[2], 27);

  const auto value_array = test_model.value_array();
  ASSERT_EQ(value_array.size(), 3);
  EXPECT_EQ(value_array[0], 5);
  EXPECT_EQ(value_array[1], 16);
  EXPECT_EQ(value_array[2], 27);

  EXPECT_THAT(value_array, ElementsAre(5, 16, 27));

  EXPECT_THAT(std::vector(value_array.begin(), value_array.end()),
              ElementsAre(5, 16, 27));
  EXPECT_THAT(std::vector(value_array.cbegin(), value_array.cend()),
              ElementsAre(5, 16, 27));
  EXPECT_THAT(std::vector(value_array.rbegin(), value_array.rend()),
              ElementsAre(27, 16, 5));
  EXPECT_THAT(std::vector(value_array.crbegin(), value_array.crend()),
              ElementsAre(27, 16, 5));
}

TEST(CppGeneratedCode, RepeatedScalarIterator) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  test_model.mutable_value_array()->push_back(5);
  test_model.mutable_value_array()->push_back(16);
  test_model.mutable_value_array()->push_back(27);
  int sum = 0;
  // Access by value.
  const ::hpb::RepeatedField<int32_t>::CProxy rep1 = test_model.value_array();
  for (auto i : rep1) {
    sum += i;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
  // Access by const reference.
  sum = 0;
  for (const auto& i : *test_model.mutable_value_array()) {
    sum += i;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
  // Access by forwarding reference.
  sum = 0;
  for (auto&& i : *test_model.mutable_value_array()) {
    sum += i;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
  // Test iterator operators.
  auto begin = test_model.value_array().begin();
  auto end = test_model.value_array().end();
  sum = 0;
  for (auto it = begin; it != end; ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
  auto it = begin;
  ++it;
  EXPECT_TRUE(begin < it);
  EXPECT_TRUE(begin <= it);
  it = end;
  EXPECT_TRUE(it == end);
  EXPECT_TRUE(it > begin);
  EXPECT_TRUE(it >= begin);
  EXPECT_TRUE(it != begin);
  // difference type
  it = end;
  --it;
  --it;
  EXPECT_EQ(end - it, 2);
  it = begin;
  EXPECT_EQ(it[0], 5);
  EXPECT_EQ(it[1], 16);
  EXPECT_EQ(it[2], 27);
  // ValueProxy.
  sum = 0;
  for (::hpb::RepeatedField<int32_t>::ValueCProxy c :
       test_model.value_array()) {
    sum += c;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
  sum = 0;
  for (::hpb::RepeatedField<int32_t>::ValueProxy c :
       *test_model.mutable_value_array()) {
    sum += c;
  }
  EXPECT_EQ(sum, 5 + 16 + 27);
}

TEST(CppGeneratedCode, RepeatedFieldProxyForStrings) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.repeated_string().size());
  EXPECT_EQ(0, test_model.mutable_repeated_string()->size());

  test_model.mutable_repeated_string()->push_back("a");
  test_model.mutable_repeated_string()->push_back("b");
  test_model.mutable_repeated_string()->push_back("c");

  ASSERT_EQ(test_model.repeated_string().size(), 3);
  EXPECT_EQ(test_model.repeated_string()[0], "a");
  EXPECT_EQ(test_model.repeated_string()[1], "b");
  EXPECT_EQ(test_model.repeated_string()[2], "c");

  EXPECT_THAT(test_model.repeated_string(), ElementsAre("a", "b", "c"));
  EXPECT_THAT(*test_model.mutable_repeated_string(),
              ElementsAre("a", "b", "c"));

  ASSERT_EQ(test_model.mutable_repeated_string()->size(), 3);
  EXPECT_EQ((*test_model.mutable_repeated_string())[0], "a");
  EXPECT_EQ((*test_model.mutable_repeated_string())[1], "b");
  EXPECT_EQ((*test_model.mutable_repeated_string())[2], "c");

  // The const accessor can't be used to modify the element
  EXPECT_FALSE((std::is_assignable<decltype(test_model.repeated_string()[1]),
                                   absl::string_view>::value));
  // But the mutable one is fine.
  (*test_model.mutable_repeated_string())[1] = "other";
  EXPECT_THAT(test_model.repeated_string(), ElementsAre("a", "other", "c"));

  test_model.mutable_repeated_string()->clear();
  EXPECT_EQ(test_model.mutable_repeated_string()->size(), 0);
}

TEST(CppGeneratedCode, RepeatedFieldProxyForMessages) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.child_models().size());
  ChildModel1 child1;
  child1.set_child_str1(kTestStr1);
  test_model.mutable_child_models()->push_back(child1);
  ChildModel1 child2;
  child2.set_child_str1(kTestStr2);
  test_model.mutable_child_models()->push_back(std::move(child2));

  int i = 0;
  for (auto child : test_model.child_models()) {
    EXPECT_FALSE(Requires<decltype(child)>(
        [](auto&& x) -> decltype(x.set_child_str1("")) {}));
    if (i++ == 0) {
      EXPECT_EQ(child.child_str1(), kTestStr1);
    } else {
      EXPECT_EQ(child.child_str1(), kTestStr2);
    }
  }

  i = 0;
  for (const auto& child : *test_model.mutable_child_models()) {
    if (i++ == 0) {
      EXPECT_EQ(child.child_str1(), kTestStr1);
    } else {
      EXPECT_EQ(child.child_str1(), kTestStr2);
    }
  }

  using testing::_;
  EXPECT_THAT(test_model.child_models(), ElementsAre(_, _));

  EXPECT_EQ(test_model.child_models().size(), 2);
  EXPECT_EQ(test_model.child_models()[0].child_str1(), kTestStr1);
  EXPECT_EQ(test_model.child_models()[1].child_str1(), kTestStr2);
  EXPECT_EQ((*test_model.mutable_child_models())[0].child_str1(), kTestStr1);
  EXPECT_EQ((*test_model.mutable_child_models())[1].child_str1(), kTestStr2);
  (*test_model.mutable_child_models())[0].set_child_str1("change1");
  EXPECT_EQ((*test_model.mutable_child_models())[0].child_str1(), "change1");
  test_model.mutable_child_models()->clear();
  EXPECT_EQ(test_model.mutable_child_models()->size(), 0);
}

TEST(CppGeneratedCode, EmptyRepeatedFieldProxyForMessages) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.child_models().size());
  ChildModel1 child1;
  child1.set_child_str1(kTestStr1);

  EXPECT_EQ(test_model.child_models().size(), 0);
  EXPECT_EQ(std::distance(test_model.child_models().begin(),
                          test_model.child_models().end()),
            0);
}

TEST(CppGeneratedCode, RepeatedFieldProxyForMessagesIndexOperator) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.child_models().size());
  ChildModel1 child1;
  child1.set_child_str1(kTestStr1);
  test_model.mutable_child_models()->push_back(child1);
  ChildModel1 child2;

  child2.set_child_str1(kTestStr2);
  test_model.mutable_child_models()->push_back(std::move(child2));
  ASSERT_EQ(test_model.child_models().size(), 2);

  // test_model.child_models()[0].set_child_str1("change1");
  (*test_model.mutable_child_models())[0].set_child_str1("change1");
  EXPECT_EQ((*test_model.mutable_child_models())[0].child_str1(), "change1");
}

TEST(CppGeneratedCode, RepeatedStrings) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.repeated_string_size());
  // Should be able to clear repeated field when empty.
  test_model.mutable_repeated_string()->clear();
  EXPECT_EQ(0, test_model.repeated_string_size());
  // Add 2 children.
  EXPECT_EQ(true, test_model.add_repeated_string("Hello"));
  EXPECT_EQ(true, test_model.add_repeated_string("World"));
  EXPECT_EQ(2, test_model.repeated_string_size());
  EXPECT_EQ("Hello", test_model.repeated_string(0));
  EXPECT_EQ("World", test_model.repeated_string(1));
  EXPECT_EQ(true, test_model.resize_repeated_string(3));
  EXPECT_EQ(3, test_model.repeated_string_size());
  test_model.set_repeated_string(2, "Test");
  EXPECT_EQ("Hello", test_model.repeated_string(0));
  EXPECT_EQ("World", test_model.repeated_string(1));
  EXPECT_EQ("Test", test_model.repeated_string(2));
}

TEST(CppGeneratedCode, MessageMapInt32KeyMessageValue) {
  const int key_test_value = 3;
  ::hpb::Arena arena;
  ::hpb::Arena child_arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.child_map_size());
  test_model.clear_child_map();
  EXPECT_EQ(0, test_model.child_map_size());
  auto child_model1 = ::hpb::CreateMessage<ChildModel1>(child_arena);
  child_model1.set_child_str1("abc");
  test_model.set_child_map(key_test_value, child_model1);
  auto map_result = test_model.get_child_map(key_test_value);
  EXPECT_EQ(true, map_result.ok());
  EXPECT_EQ("abc", map_result.value()->child_str1());
  // Now mutate original child model to verify that value semantics are
  // preserved.
  child_model1.set_child_str1("abc V2");
  EXPECT_EQ("abc", map_result.value()->child_str1());
  test_model.delete_child_map(key_test_value);
  auto map_result_after_delete = test_model.get_child_map(key_test_value);
  EXPECT_EQ(false, map_result_after_delete.ok());
}

TEST(CppGeneratedCode, MessageMapStringKeyAndStringValue) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.str_to_str_map_size());
  test_model.clear_str_to_str_map();
  EXPECT_EQ(0, test_model.str_to_str_map_size());
  test_model.set_str_to_str_map("first", "abc");
  test_model.set_str_to_str_map("second", "def");
  auto result = test_model.get_str_to_str_map("second");
  EXPECT_EQ(true, result.ok());
  EXPECT_EQ("def", result.value());
  test_model.delete_str_to_str_map("first");
  auto result_after_delete = test_model.get_str_to_str_map("first");
  EXPECT_EQ(false, result_after_delete.ok());
}

TEST(CppGeneratedCode, MessageMapStringKeyAndInt32Value) {
  ::hpb::Arena arena;
  auto test_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_EQ(0, test_model.str_to_int_map_size());
  test_model.clear_str_to_int_map();
  EXPECT_EQ(0, test_model.str_to_int_map_size());
  test_model.set_str_to_int_map("first", 10);
  EXPECT_EQ(1, test_model.str_to_int_map_size());
  test_model.set_str_to_int_map("second", 20);
  EXPECT_EQ(2, test_model.str_to_int_map_size());
  auto result = test_model.get_str_to_int_map("second");
  EXPECT_EQ(true, result.ok());
  EXPECT_EQ(20, result.value());
  test_model.delete_str_to_int_map("first");
  auto result_after_delete = test_model.get_str_to_int_map("first");
  EXPECT_EQ(false, result_after_delete.ok());
}

TEST(CppGeneratedCode, HasExtension) {
  TestModel model;
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
}

TEST(CppGeneratedCode, HasExtensionPtr) {
  TestModel model;
  EXPECT_EQ(false, ::hpb::HasExtension(model.recursive_child(), theme));
}

TEST(CppGeneratedCode, ClearExtensionWithEmptyExtension) {
  TestModel model;
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
  ::hpb::ClearExtension(&model, theme);
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
}

TEST(CppGeneratedCode, ClearExtensionWithEmptyExtensionPtr) {
  TestModel model;
  ::hpb::Ptr<TestModel> recursive_child = model.mutable_recursive_child();
  ::hpb::ClearExtension(recursive_child, theme);
  EXPECT_EQ(false, ::hpb::HasExtension(recursive_child, theme));
}

TEST(CppGeneratedCode, SetExtension) {
  TestModel model;
  void* prior_message;
  {
    // Use a nested scope to make sure the arenas are fused correctly.
    ThemeExtension extension1;
    extension1.set_ext_name("Hello World");
    prior_message = ::hpb::internal::GetInternalMsg(&extension1);
    EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
    EXPECT_EQ(true,
              ::hpb::SetExtension(&model, theme, std::move(extension1)).ok());
  }
  EXPECT_EQ(true, ::hpb::HasExtension(&model, theme));
  auto ext = ::protos::GetExtension(&model, theme);
  EXPECT_TRUE(ext.ok());
  EXPECT_EQ(::hpb::internal::GetInternalMsg(*ext), prior_message);
}

TEST(CppGeneratedCode, SetExtensionWithPtr) {
  ::hpb::Arena arena_model;
  ::hpb::Ptr<TestModel> model = ::hpb::CreateMessage<TestModel>(arena_model);
  void* prior_message;
  {
    // Use a nested scope to make sure the arenas are fused correctly.
    ::hpb::Arena arena;
    ::hpb::Ptr<ThemeExtension> extension1 =
        ::hpb::CreateMessage<ThemeExtension>(arena);
    extension1->set_ext_name("Hello World");
    prior_message = ::hpb::internal::GetInternalMsg(extension1);
    EXPECT_EQ(false, ::hpb::HasExtension(model, theme));
    auto res = ::hpb::SetExtension(model, theme, extension1);
    EXPECT_EQ(true, res.ok());
  }
  EXPECT_EQ(true, ::hpb::HasExtension(model, theme));
  auto ext = ::protos::GetExtension(model, theme);
  EXPECT_TRUE(ext.ok());
  EXPECT_NE(::hpb::internal::GetInternalMsg(*ext), prior_message);
}

#ifndef _MSC_VER
TEST(CppGeneratedCode, SetExtensionShouldNotCompileForWrongType) {
  ::hpb::Arena arena;
  ::hpb::Ptr<TestModel> model = ::hpb::CreateMessage<TestModel>(arena);
  ThemeExtension extension1;
  ContainerExtension extension2;

  const auto canSetExtension = [&](auto l) {
    return Requires<decltype(model)>(l);
  };
  EXPECT_TRUE(canSetExtension(
      [](auto p) -> decltype(::hpb::SetExtension(p, theme, extension1)) {}));
  // Wrong extension value type should fail to compile.
  EXPECT_TRUE(!canSetExtension(
      [](auto p) -> decltype(::hpb::SetExtension(p, theme, extension2)) {}));
  // Wrong extension id with correct extension type should fail to compile.
  EXPECT_TRUE(
      !canSetExtension([](auto p) -> decltype(::hpb::SetExtension(
                                      p, container_ext, extension1)) {}));
}
#endif

TEST(CppGeneratedCode, SetExtensionWithPtrSameArena) {
  ::hpb::Arena arena;
  ::hpb::Ptr<TestModel> model = ::hpb::CreateMessage<TestModel>(arena);
  void* prior_message;
  {
    // Use a nested scope to make sure the arenas are fused correctly.
    ::hpb::Ptr<ThemeExtension> extension1 =
        ::hpb::CreateMessage<ThemeExtension>(arena);
    extension1->set_ext_name("Hello World");
    prior_message = ::hpb::internal::GetInternalMsg(extension1);
    EXPECT_EQ(false, ::hpb::HasExtension(model, theme));
    auto res = ::hpb::SetExtension(model, theme, extension1);
    EXPECT_EQ(true, res.ok());
  }
  EXPECT_EQ(true, ::hpb::HasExtension(model, theme));
  auto ext = ::protos::GetExtension(model, theme);
  EXPECT_TRUE(ext.ok());
  EXPECT_NE(::hpb::internal::GetInternalMsg(*ext), prior_message);
}

TEST(CppGeneratedCode, SetExtensionFusingFailureShouldCopy) {
  // Use an initial block to disallow fusing.
  char initial_block[1000];
  hpb::Arena arena(initial_block, sizeof(initial_block));

  hpb::Ptr<TestModel> model = ::hpb::CreateMessage<TestModel>(arena);

  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  ASSERT_FALSE(
      upb_Arena_Fuse(arena.ptr(), ::hpb::internal::GetArena(&extension1)));
  EXPECT_FALSE(::hpb::HasExtension(model, theme));
  auto status = ::hpb::SetExtension(model, theme, std::move(extension1));
  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(::hpb::HasExtension(model, theme));
  EXPECT_TRUE(::protos::GetExtension(model, theme).ok());
}

TEST(CppGeneratedCode, SetExtensionShouldClone) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
  EXPECT_EQ(true, ::hpb::SetExtension(&model, theme, extension1).ok());
  extension1.set_ext_name("Goodbye");
  EXPECT_EQ(true, ::hpb::HasExtension(&model, theme));
  auto ext = ::protos::GetExtension(&model, theme);
  EXPECT_TRUE(ext.ok());
  EXPECT_EQ((*ext)->ext_name(), "Hello World");
}

TEST(CppGeneratedCode, SetExtensionShouldCloneConst) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
  EXPECT_EQ(true,
            ::hpb::SetExtension(&model, theme, std::as_const(extension1)).ok());
  extension1.set_ext_name("Goodbye");
  EXPECT_EQ(true, ::hpb::HasExtension(&model, theme));
  auto ext = ::protos::GetExtension(&model, theme);
  EXPECT_TRUE(ext.ok());
  EXPECT_EQ((*ext)->ext_name(), "Hello World");
}

TEST(CppGeneratedCode, SetExtensionOnMutableChild) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(false, ::hpb::HasExtension(model.mutable_recursive_child(), theme));
  EXPECT_EQ(true, ::hpb::SetExtension(model.mutable_recursive_child(), theme,
                                      extension1)
                      .ok());
  EXPECT_EQ(true, ::hpb::HasExtension(model.mutable_recursive_child(), theme));
}

TEST(CppGeneratedCode, GetExtension) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(false, ::hpb::HasExtension(&model, theme));
  EXPECT_EQ(true, ::hpb::SetExtension(&model, theme, extension1).ok());
  EXPECT_EQ("Hello World",
            ::protos::GetExtension(&model, theme).value()->ext_name());
}

TEST(CppGeneratedCode, GetExtensionOnMutableChild) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  ::hpb::Ptr<TestModel> mutable_recursive_child =
      model.mutable_recursive_child();
  EXPECT_EQ(false, ::hpb::HasExtension(mutable_recursive_child, theme));
  EXPECT_EQ(
      true,
      ::hpb::SetExtension(mutable_recursive_child, theme, extension1).ok());
  EXPECT_EQ("Hello World",
            ::protos::GetExtension(mutable_recursive_child, theme)
                .value()
                ->ext_name());
}

TEST(CppGeneratedCode, GetExtensionOnImmutableChild) {
  TestModel model;
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  ::hpb::Ptr<TestModel> mutable_recursive_child =
      model.mutable_recursive_child();
  EXPECT_EQ(false, ::hpb::HasExtension(mutable_recursive_child, theme));
  EXPECT_EQ(
      true,
      ::hpb::SetExtension(mutable_recursive_child, theme, extension1).ok());
  ::hpb::Ptr<const TestModel> recursive_child = model.recursive_child();
  EXPECT_EQ("Hello World",
            ::protos::GetExtension(recursive_child, theme).value()->ext_name());
}

TEST(CppGeneratedCode, SerializeUsingArena) {
  TestModel model;
  model.set_str1("Hello World");
  ::upb::Arena arena;
  absl::StatusOr<absl::string_view> bytes = ::hpb::Serialize(&model, arena);
  EXPECT_EQ(true, bytes.ok());
  TestModel parsed_model = ::hpb::Parse<TestModel>(bytes.value()).value();
  EXPECT_EQ("Hello World", parsed_model.str1());
}

TEST(CppGeneratedCode, SerializeProxyUsingArena) {
  ::upb::Arena message_arena;
  TestModel::Proxy model_proxy = ::hpb::CreateMessage<TestModel>(message_arena);
  model_proxy.set_str1("Hello World");
  ::upb::Arena arena;
  absl::StatusOr<absl::string_view> bytes =
      ::hpb::Serialize(&model_proxy, arena);
  EXPECT_EQ(true, bytes.ok());
  TestModel parsed_model = ::hpb::Parse<TestModel>(bytes.value()).value();
  EXPECT_EQ("Hello World", parsed_model.str1());
}

TEST(CppGeneratedCode, SerializeNestedMessageUsingArena) {
  TestModel model;
  model.mutable_recursive_child()->set_str1("Hello World");
  ::upb::Arena arena;
  ::hpb::Ptr<const TestModel> child = model.recursive_child();
  absl::StatusOr<absl::string_view> bytes = ::hpb::Serialize(child, arena);
  EXPECT_EQ(true, bytes.ok());
  TestModel parsed_model = ::hpb::Parse<TestModel>(bytes.value()).value();
  EXPECT_EQ("Hello World", parsed_model.str1());
}

TEST(CppGeneratedCode, Parse) {
  TestModel model;
  model.set_str1("Test123");
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(true, ::hpb::SetExtension(&model, theme, extension1).ok());
  ::upb::Arena arena;
  auto bytes = ::hpb::Serialize(&model, arena);
  EXPECT_EQ(true, bytes.ok());
  TestModel parsed_model = ::hpb::Parse<TestModel>(bytes.value()).value();
  EXPECT_EQ("Test123", parsed_model.str1());
  EXPECT_EQ(true, ::protos::GetExtension(&parsed_model, theme).ok());
}

TEST(CppGeneratedCode, ParseIntoPtrToModel) {
  TestModel model;
  model.set_str1("Test123");
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(true, ::hpb::SetExtension(&model, theme, extension1).ok());
  ::upb::Arena arena;
  auto bytes = ::hpb::Serialize(&model, arena);
  EXPECT_EQ(true, bytes.ok());
  ::hpb::Ptr<TestModel> parsed_model = ::hpb::CreateMessage<TestModel>(arena);
  EXPECT_TRUE(::hpb::Parse(parsed_model, bytes.value()));
  EXPECT_EQ("Test123", parsed_model->str1());
  // Should return an extension even if we don't pass ExtensionRegistry
  // by promoting unknown.
  EXPECT_EQ(true, ::protos::GetExtension(parsed_model, theme).ok());
}

TEST(CppGeneratedCode, ParseWithExtensionRegistry) {
  TestModel model;
  model.set_str1("Test123");
  ThemeExtension extension1;
  extension1.set_ext_name("Hello World");
  EXPECT_EQ(true, ::hpb::SetExtension(&model, theme, extension1).ok());
  EXPECT_EQ(true, ::hpb::SetExtension(&model, ThemeExtension::theme_extension,
                                      extension1)
                      .ok());
  ::upb::Arena arena;
  auto bytes = ::hpb::Serialize(&model, arena);
  EXPECT_EQ(true, bytes.ok());
  ::hpb::ExtensionRegistry extensions(
      {&theme, &other_ext, &ThemeExtension::theme_extension}, arena);
  TestModel parsed_model =
      ::hpb::Parse<TestModel>(bytes.value(), extensions).value();
  EXPECT_EQ("Test123", parsed_model.str1());
  EXPECT_EQ(true, ::protos::GetExtension(&parsed_model, theme).ok());
  EXPECT_EQ(true, ::protos::GetExtension(&parsed_model,
                                         ThemeExtension::theme_extension)
                      .ok());
  EXPECT_EQ("Hello World", ::protos::GetExtension(
                               &parsed_model, ThemeExtension::theme_extension)
                               .value()
                               ->ext_name());
}

TEST(CppGeneratedCode, NameCollisions) {
  TestModel model;
  model.set_template_("test");
  EXPECT_EQ("test", model.template_());
  model.set_arena__("test");
  EXPECT_EQ("test", model.arena__());
}

TEST(CppGeneratedCode, SharedPointer) {
  std::shared_ptr<TestModel> model = std::make_shared<TestModel>();
  ::upb::Arena arena;
  auto bytes = ::hpb::Serialize(model.get(), arena);
  EXPECT_TRUE(::hpb::Parse(model.get(), bytes.value()));
}

TEST(CppGeneratedCode, UniquePointer) {
  auto model = std::make_unique<TestModel>();
  ::upb::Arena arena;
  auto bytes = ::hpb::Serialize(model.get(), arena);
  EXPECT_TRUE(::hpb::Parse(model.get(), bytes.value()));
}

TEST(CppGeneratedCode, Assignment) {
  TestModel model;
  model.set_category(5);
  model.mutable_child_model_1()->set_child_str1("text in child");
  TestModel model2 = model;
  EXPECT_EQ(5, model2.category());
  EXPECT_EQ(model2.child_model_1()->child_str1(), "text in child");
}

TEST(CppGeneratedCode, PtrAssignment) {
  TestModel model;
  model.mutable_child_model_1()->set_child_str1("text in child");
  ChildModel1 child_from_const_ptr = *model.child_model_1();
  EXPECT_EQ(child_from_const_ptr.child_str1(), "text in child");
  ChildModel1 child_from_ptr = *model.mutable_child_model_1();
  EXPECT_EQ(child_from_ptr.child_str1(), "text in child");
}

TEST(CppGeneratedCode, CopyConstructor) {
  TestModel model;
  model.set_category(6);
  TestModel model2(model);
  EXPECT_EQ(6, model2.category());
}

TEST(CppGeneratedCode, PtrConstructor) {
  TestModel model;
  model.mutable_child_model_1()->set_child_str1("text in child");
  ChildModel1 child_from_ptr(*model.mutable_child_model_1());
  EXPECT_EQ(child_from_ptr.child_str1(), "text in child");
  ChildModel1 child_from_const_ptr(*model.child_model_1());
  EXPECT_EQ(child_from_const_ptr.child_str1(), "text in child");
}

TEST(CppGeneratedCode, MutableToProxy) {
  TestModel model;
  ::hpb::Ptr<ChildModel1> child = model.mutable_child_model_1();
  (void)child;
}

TEST(CppGeneratedCode, ProxyToCProxy) {
  TestModel model;
  ::hpb::Ptr<ChildModel1> child = model.mutable_child_model_1();
  ::hpb::Ptr<const ChildModel1> child2 = child;
  (void)child2;
}

TEST(CppGeneratedCode, MutableAccessorsAreHiddenInCProxy) {
  TestModel model;
  ::hpb::Ptr<TestModel> proxy = &model;
  ::hpb::Ptr<const TestModel> cproxy = proxy;

  const auto test_const_accessors = [](auto p) {
    // We don't want to run it, just check it compiles.
    if (false) {
      (void)p->has_str1();
      (void)p->str1();
      (void)p->has_value();
      (void)p->value();
      (void)p->has_oneof_member1();
      (void)p->oneof_member1();
      (void)p->value_array();
      (void)p->value_array_size();
      (void)p->value_array(1);
      (void)p->has_nested_child_1();
      (void)p->nested_child_1();
      (void)p->child_models();
      (void)p->child_models_size();
      (void)p->child_models(1);
      (void)p->child_map_size();
      (void)p->get_child_map(1);
    }
  };

  test_const_accessors(proxy);
  test_const_accessors(cproxy);

  const auto test_mutable_accessors = [](auto p, bool expected) {
    const auto r = [&](auto l) { return Requires<decltype(p)>(l) == expected; };
    EXPECT_TRUE(r([](auto p) -> decltype(p->set_str1("")) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->clear_str1()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->set_value(1)) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->clear_value()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->set_oneof_member1("")) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->clear_oneof_member1()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->mutable_nested_child_1()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->clear_nested_child_1()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->add_value_array(1)) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->mutable_value_array()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->resize_value_array(1)) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->set_value_array(1, 1)) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->add_child_models()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->mutable_child_models(1)) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->clear_child_map()) {}));
    EXPECT_TRUE(r([](auto p) -> decltype(p->delete_child_map(1)) {}));
    EXPECT_TRUE(r(
        [](auto p) -> decltype(p->set_child_map(1, *p->get_child_map(1))) {}));
  };
  test_mutable_accessors(proxy, true);
  test_mutable_accessors(cproxy, false);
}

bool ProxyToCProxyMethod(::hpb::Ptr<const ChildModel1> child) {
  return child->child_str1() == "text in child";
}

TEST(CppGeneratedCode, PassProxyToCProxy) {
  TestModel model;
  model.mutable_child_model_1()->set_child_str1("text in child");
  EXPECT_TRUE(ProxyToCProxyMethod(model.mutable_child_model_1()));
}

TEST(CppGeneratedCode, PtrImplicitConversion) {
  TestModel model;
  model.set_int64(5);
  ::hpb::Ptr<TestModel> model_ptr = &model;
  EXPECT_EQ(model_ptr->int64(), 5);
}

TEST(CppGeneratedCode, ClearSubMessage) {
  // Fill model.
  TestModel model;
  model.set_int64(5);
  auto new_child = model.mutable_child_model_1();
  new_child->set_child_str1("text in child");
  ThemeExtension extension1;
  extension1.set_ext_name("name in extension");
  EXPECT_TRUE(::hpb::SetExtension(&model, theme, extension1).ok());
  EXPECT_TRUE(model.mutable_child_model_1()->has_child_str1());
  // Clear using Ptr<T>
  ::hpb::ClearMessage(model.mutable_child_model_1());
  EXPECT_FALSE(model.mutable_child_model_1()->has_child_str1());
}

TEST(CppGeneratedCode, ClearMessage) {
  // Fill model.
  TestModel model;
  model.set_int64(5);
  model.set_str2("Hello");
  auto new_child = model.add_child_models();
  ASSERT_TRUE(new_child.ok());
  new_child.value()->set_child_str1("text in child");
  ThemeExtension extension1;
  extension1.set_ext_name("name in extension");
  EXPECT_TRUE(::hpb::SetExtension(&model, theme, extension1).ok());
  // Clear using T*
  ::hpb::ClearMessage(&model);
  // Verify that scalars, repeated fields and extensions are cleared.
  EXPECT_FALSE(model.has_int64());
  EXPECT_FALSE(model.has_str2());
  EXPECT_TRUE(model.child_models().empty());
  EXPECT_FALSE(::hpb::HasExtension(&model, theme));
}

TEST(CppGeneratedCode, CanInvokeClearMessageWithPtr) {
  // Fill model.
  TestModel model;
  model.set_int64(5);
  auto new_child = model.add_child_models();
  // Clear using Ptr<T>
  auto ptr = ::hpb::Ptr<TestModel>(&model);
  ::hpb::ClearMessage(ptr);
  // Successful clear
  EXPECT_FALSE(model.has_int64());
}

TEST(CppGeneratedCode, CanInvokeClearMessageWithRawPtr) {
  // Fill model.
  TestModel model;
  model.set_int64(5);
  auto new_child = model.add_child_models();
  // Clear using T*
  ::hpb::ClearMessage(&model);
  // Successful clear
  EXPECT_FALSE(model.has_int64());
}

template <typename T>
bool CanCallClearMessage() {
  return Requires<T>([](auto x) -> decltype(::hpb::ClearMessage(x)) {});
}

TEST(CppGeneratedCode, CannotInvokeClearMessageWithConstPtr) {
  EXPECT_TRUE(CanCallClearMessage<::hpb::Ptr<TestModel>>());
  EXPECT_FALSE(CanCallClearMessage<::hpb::Ptr<const TestModel>>());
}

TEST(CppGeneratedCode, CannotInvokeClearMessageWithConstRawPtr) {
  EXPECT_TRUE(CanCallClearMessage<TestModel*>());
  EXPECT_FALSE(CanCallClearMessage<const TestModel*>());
}

TEST(CppGeneratedCode, DeepCopy) {
  // Fill model.
  TestModel model;
  model.set_int64(5);
  model.set_str2("Hello");
  auto new_child = model.add_child_models();
  ASSERT_TRUE(new_child.ok());
  new_child.value()->set_child_str1("text in child");
  ThemeExtension extension1;
  extension1.set_ext_name("name in extension");
  EXPECT_TRUE(::hpb::SetExtension(&model, theme, extension1).ok());
  TestModel target;
  target.set_b1(true);
  ::hpb::DeepCopy(&model, &target);
  EXPECT_FALSE(target.b1()) << "Target was not cleared before copying content ";
  EXPECT_EQ(target.str2(), "Hello");
  EXPECT_TRUE(::hpb::HasExtension(&target, theme));
}

TEST(CppGeneratedCode, HasExtensionAndRegistry) {
  // Fill model.
  TestModel source;
  source.set_int64(5);
  source.set_str2("Hello");
  auto new_child = source.add_child_models();
  ASSERT_TRUE(new_child.ok());
  new_child.value()->set_child_str1("text in child");
  ThemeExtension extension1;
  extension1.set_ext_name("name in extension");
  ASSERT_TRUE(::hpb::SetExtension(&source, theme, extension1).ok());

  // Now that we have a source model with extension data, serialize.
  ::hpb::Arena arena;
  std::string data = std::string(::hpb::Serialize(&source, arena).value());

  // Test with ExtensionRegistry
  ::hpb::ExtensionRegistry extensions({&theme}, arena);
  TestModel parsed_model = ::hpb::Parse<TestModel>(data, extensions).value();
  EXPECT_TRUE(::hpb::HasExtension(&parsed_model, theme));
}

TEST(CppGeneratedCode, FieldNumberConstants) {
  static_assert(TestModel::kChildMapFieldNumber == 225);
  EXPECT_EQ(225, TestModel::kChildMapFieldNumber);
}

TEST(CppGeneratedCode, ExtensionFieldNumberConstant) {
  EXPECT_EQ(12003, ::hpb::ExtensionNumber(ThemeExtension::theme_extension));
}

TEST(CppGeneratedCode, ClearConstMessageShouldFailForConstChild) {
  TestModel model;
  EXPECT_FALSE(CanCallClearMessage<decltype(model.child_model_1())>());
  EXPECT_TRUE(CanCallClearMessage<decltype(model.mutable_child_model_1())>());
}

}  // namespace
