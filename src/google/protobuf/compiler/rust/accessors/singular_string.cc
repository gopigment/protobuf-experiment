// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include <string>

#include "absl/strings/string_view.h"
#include "google/protobuf/compiler/cpp/helpers.h"
#include "google/protobuf/compiler/rust/accessors/accessor_case.h"
#include "google/protobuf/compiler/rust/accessors/generator.h"
#include "google/protobuf/compiler/rust/accessors/with_presence.h"
#include "google/protobuf/compiler/rust/context.h"
#include "google/protobuf/compiler/rust/naming.h"
#include "google/protobuf/descriptor.h"

namespace google {
namespace protobuf {
namespace compiler {
namespace rust {

void SingularString::InMsgImpl(Context& ctx, const FieldDescriptor& field,
                               AccessorCase accessor_case) const {
  if (field.has_presence()) {
    WithPresenceAccessorsInMsgImpl(ctx, field, accessor_case);
  }

  std::string field_name = FieldNameWithCollisionAvoidance(field);
  ctx.Emit(
      {
          {"field", RsSafeName(field_name)},
          {"raw_field_name", field_name},
          {"getter_thunk", ThunkName(ctx, field, "get")},
          {"setter_thunk", ThunkName(ctx, field, "set")},
          {"proxied_type", RsTypePath(ctx, field)},
          io::Printer::Sub("transform_view",
                           [&] {
                             if (field.type() == FieldDescriptor::TYPE_STRING) {
                               ctx.Emit(R"rs(
              // SAFETY: The runtime doesn't require ProtoStr to be UTF-8.
              unsafe { $pb$::ProtoStr::from_utf8_unchecked(view) }
            )rs");
                             } else {
                               ctx.Emit("view");
                             }
                           })
              .WithSuffix(""),  // This lets `$transform_view$,` work.
          {"view_lifetime", ViewLifetime(accessor_case)},
          {"view_self", ViewReceiver(accessor_case)},
          {"getter",
           [&] {
             ctx.Emit(R"rs(
                pub fn $field$($view_self$) -> $pb$::View<$view_lifetime$, $proxied_type$> {
                  let view = unsafe { $getter_thunk$(self.raw_msg()).as_ref() };
                  $transform_view$
                })rs");
           }},
          {"setter_impl",
           [&] {
             if (ctx.is_cpp()) {
               ctx.Emit(R"rs(
                let s = val.into_proxied($pbi$::Private);
                unsafe {
                  $setter_thunk$(
                    self.as_mutator_message_ref($pbi$::Private).msg(),
                    s.into_inner($pbi$::Private).into_raw()
                  );
                }
              )rs");
             } else {
               ctx.Emit(R"rs(
                let s = val.into_proxied($pbi$::Private);
                let (view, arena) =
                  s.into_inner($pbi$::Private).into_raw_parts();

                let mm_ref =
                  self.as_mutator_message_ref($pbi$::Private);
                let parent_arena = mm_ref.arena();

                parent_arena.fuse(&arena);

                unsafe {
                  $setter_thunk$(
                    self.as_mutator_message_ref($pbi$::Private).msg(),
                    view
                  );
                }
              )rs");
             }
           }},
          {"setter",
           [&] {
             if (accessor_case == AccessorCase::VIEW) return;
             ctx.Emit({},
                      R"rs(
              pub fn set_$raw_field_name$(&mut self, val: impl $pb$::IntoProxied<$proxied_type$>) {
                $setter_impl$
              }
            )rs");
           }},
      },
      R"rs(
        $getter$
        $setter$
      )rs");
}

void SingularString::InExternC(Context& ctx,
                               const FieldDescriptor& field) const {
  if (field.has_presence()) {
    WithPresenceAccessorsInExternC(ctx, field);
  }

  ctx.Emit(
      {
          {"getter_thunk", ThunkName(ctx, field, "get")},
          {"setter_thunk", ThunkName(ctx, field, "set")},
          {"setter",
           [&] {
             if (ctx.is_cpp()) {
               ctx.Emit(R"rs(
                  fn $setter_thunk$(raw_msg: $pbr$::RawMessage, val: $pbr$::CppStdString);
                )rs");
             } else {
               ctx.Emit(R"rs(
                  fn $setter_thunk$(raw_msg: $pbr$::RawMessage, val: $pbr$::PtrAndLen);
                )rs");
             }
           }},
      },
      R"rs(
          fn $getter_thunk$(raw_msg: $pbr$::RawMessage) -> $pbr$::PtrAndLen;
          $setter$
        )rs");
}

void SingularString::InThunkCc(Context& ctx,
                               const FieldDescriptor& field) const {
  if (field.has_presence()) {
    WithPresenceAccessorsInThunkCc(ctx, field);
  }

  ctx.Emit(
      {
          {"field", cpp::FieldName(&field)},
          {"QualifiedMsg", cpp::QualifiedClassName(field.containing_type())},
          {"getter_thunk", ThunkName(ctx, field, "get")},
          {"setter_thunk", ThunkName(ctx, field, "set")},
      },
      R"cc(
        ::google::protobuf::rust::PtrAndLen $getter_thunk$($QualifiedMsg$* msg) {
          absl::string_view val = msg->$field$();
          return ::google::protobuf::rust::PtrAndLen(val.data(), val.size());
        }
        void $setter_thunk$($QualifiedMsg$* msg, std::string* s) {
          msg->set_$field$(std::move(*s));
          delete s;
        }
      )cc");
}

}  // namespace rust
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
