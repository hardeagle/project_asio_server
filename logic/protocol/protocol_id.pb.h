// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol_id.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protocol_5fid_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protocol_5fid_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3010000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3010000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protocol_5fid_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protocol_5fid_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_protocol_5fid_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

enum MsgId : int {
  C2S_SYSTEM_BASE = 0,
  C2S_SYSTEM_TICK = 1,
  S2C_SYSTEM_TICK = 2,
  C2S_SYSTEM_TOP = 99,
  C2S_ACCOUNT_BASE = 100,
  C2S_ACCOUNT_LOGIN = 101,
  S2C_ACCOUNT_LOGIN = 102,
  C2S_ACCOUNT_CREATE = 103,
  S2C_ACCOUNT_CREATE = 104,
  C2S_ACCOUNT_LOAD = 105,
  S2C_ACCOUNT_LOAD = 106,
  C2S_ACCOUNT_ASK_OPENID = 107,
  S2C_ACCOUNT_ASK_OPENID = 108,
  C2S_ACCOUNT_UPDATE = 109,
  S2C_ACCOUNT_UPDATE = 110,
  C2S_ACCOUNT_TOP = 199,
  C2S_SHOP_BASE = 200,
  C2S_SHOP_LOAD = 201,
  S2C_SHOP_LOAD = 202,
  C2S_SHOP_BUY = 203,
  S2C_SHOP_BUY = 204,
  C2S_SHOP_TOP = 299,
  C2S_RANK_BASE = 300,
  C2S_RANK_LOAD = 301,
  S2C_RANK_LOAD = 302,
  C2S_RANK_UPDATE = 303,
  S2C_RANK_UPDATE = 304,
  S2C_RANK_MARQUEE = 306,
  C2S_RANK_TOP = 399,
  MsgId_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  MsgId_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool MsgId_IsValid(int value);
constexpr MsgId MsgId_MIN = C2S_SYSTEM_BASE;
constexpr MsgId MsgId_MAX = C2S_RANK_TOP;
constexpr int MsgId_ARRAYSIZE = MsgId_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MsgId_descriptor();
template<typename T>
inline const std::string& MsgId_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MsgId>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MsgId_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MsgId_descriptor(), enum_t_value);
}
inline bool MsgId_Parse(
    const std::string& name, MsgId* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MsgId>(
    MsgId_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::Protocol::MsgId> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Protocol::MsgId>() {
  return ::Protocol::MsgId_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protocol_5fid_2eproto
