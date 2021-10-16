// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol_shop.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protocol_5fshop_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protocol_5fshop_2eproto

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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protocol_5fshop_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protocol_5fshop_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_protocol_5fshop_2eproto;
namespace Protocol {
class C2S_ShopBuy;
class C2S_ShopBuyDefaultTypeInternal;
extern C2S_ShopBuyDefaultTypeInternal _C2S_ShopBuy_default_instance_;
class C2S_ShopLoad;
class C2S_ShopLoadDefaultTypeInternal;
extern C2S_ShopLoadDefaultTypeInternal _C2S_ShopLoad_default_instance_;
class S2C_ShopBuy;
class S2C_ShopBuyDefaultTypeInternal;
extern S2C_ShopBuyDefaultTypeInternal _S2C_ShopBuy_default_instance_;
class S2C_ShopLoad;
class S2C_ShopLoadDefaultTypeInternal;
extern S2C_ShopLoadDefaultTypeInternal _S2C_ShopLoad_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::C2S_ShopBuy* Arena::CreateMaybeMessage<::Protocol::C2S_ShopBuy>(Arena*);
template<> ::Protocol::C2S_ShopLoad* Arena::CreateMaybeMessage<::Protocol::C2S_ShopLoad>(Arena*);
template<> ::Protocol::S2C_ShopBuy* Arena::CreateMaybeMessage<::Protocol::S2C_ShopBuy>(Arena*);
template<> ::Protocol::S2C_ShopLoad* Arena::CreateMaybeMessage<::Protocol::S2C_ShopLoad>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class C2S_ShopLoad :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.C2S_ShopLoad) */ {
 public:
  C2S_ShopLoad();
  virtual ~C2S_ShopLoad();

  C2S_ShopLoad(const C2S_ShopLoad& from);
  C2S_ShopLoad(C2S_ShopLoad&& from) noexcept
    : C2S_ShopLoad() {
    *this = ::std::move(from);
  }

  inline C2S_ShopLoad& operator=(const C2S_ShopLoad& from) {
    CopyFrom(from);
    return *this;
  }
  inline C2S_ShopLoad& operator=(C2S_ShopLoad&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const C2S_ShopLoad& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const C2S_ShopLoad* internal_default_instance() {
    return reinterpret_cast<const C2S_ShopLoad*>(
               &_C2S_ShopLoad_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(C2S_ShopLoad& a, C2S_ShopLoad& b) {
    a.Swap(&b);
  }
  inline void Swap(C2S_ShopLoad* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline C2S_ShopLoad* New() const final {
    return CreateMaybeMessage<C2S_ShopLoad>(nullptr);
  }

  C2S_ShopLoad* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<C2S_ShopLoad>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const C2S_ShopLoad& from);
  void MergeFrom(const C2S_ShopLoad& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(C2S_ShopLoad* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.C2S_ShopLoad";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_protocol_5fshop_2eproto);
    return ::descriptor_table_protocol_5fshop_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Protocol.C2S_ShopLoad)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_5fshop_2eproto;
};
// -------------------------------------------------------------------

class S2C_ShopLoad :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.S2C_ShopLoad) */ {
 public:
  S2C_ShopLoad();
  virtual ~S2C_ShopLoad();

  S2C_ShopLoad(const S2C_ShopLoad& from);
  S2C_ShopLoad(S2C_ShopLoad&& from) noexcept
    : S2C_ShopLoad() {
    *this = ::std::move(from);
  }

  inline S2C_ShopLoad& operator=(const S2C_ShopLoad& from) {
    CopyFrom(from);
    return *this;
  }
  inline S2C_ShopLoad& operator=(S2C_ShopLoad&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const S2C_ShopLoad& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const S2C_ShopLoad* internal_default_instance() {
    return reinterpret_cast<const S2C_ShopLoad*>(
               &_S2C_ShopLoad_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(S2C_ShopLoad& a, S2C_ShopLoad& b) {
    a.Swap(&b);
  }
  inline void Swap(S2C_ShopLoad* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline S2C_ShopLoad* New() const final {
    return CreateMaybeMessage<S2C_ShopLoad>(nullptr);
  }

  S2C_ShopLoad* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<S2C_ShopLoad>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const S2C_ShopLoad& from);
  void MergeFrom(const S2C_ShopLoad& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(S2C_ShopLoad* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.S2C_ShopLoad";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_protocol_5fshop_2eproto);
    return ::descriptor_table_protocol_5fshop_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Protocol.S2C_ShopLoad)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_5fshop_2eproto;
};
// -------------------------------------------------------------------

class C2S_ShopBuy :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.C2S_ShopBuy) */ {
 public:
  C2S_ShopBuy();
  virtual ~C2S_ShopBuy();

  C2S_ShopBuy(const C2S_ShopBuy& from);
  C2S_ShopBuy(C2S_ShopBuy&& from) noexcept
    : C2S_ShopBuy() {
    *this = ::std::move(from);
  }

  inline C2S_ShopBuy& operator=(const C2S_ShopBuy& from) {
    CopyFrom(from);
    return *this;
  }
  inline C2S_ShopBuy& operator=(C2S_ShopBuy&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const C2S_ShopBuy& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const C2S_ShopBuy* internal_default_instance() {
    return reinterpret_cast<const C2S_ShopBuy*>(
               &_C2S_ShopBuy_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(C2S_ShopBuy& a, C2S_ShopBuy& b) {
    a.Swap(&b);
  }
  inline void Swap(C2S_ShopBuy* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline C2S_ShopBuy* New() const final {
    return CreateMaybeMessage<C2S_ShopBuy>(nullptr);
  }

  C2S_ShopBuy* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<C2S_ShopBuy>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const C2S_ShopBuy& from);
  void MergeFrom(const C2S_ShopBuy& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(C2S_ShopBuy* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.C2S_ShopBuy";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_protocol_5fshop_2eproto);
    return ::descriptor_table_protocol_5fshop_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Protocol.C2S_ShopBuy)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_5fshop_2eproto;
};
// -------------------------------------------------------------------

class S2C_ShopBuy :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.S2C_ShopBuy) */ {
 public:
  S2C_ShopBuy();
  virtual ~S2C_ShopBuy();

  S2C_ShopBuy(const S2C_ShopBuy& from);
  S2C_ShopBuy(S2C_ShopBuy&& from) noexcept
    : S2C_ShopBuy() {
    *this = ::std::move(from);
  }

  inline S2C_ShopBuy& operator=(const S2C_ShopBuy& from) {
    CopyFrom(from);
    return *this;
  }
  inline S2C_ShopBuy& operator=(S2C_ShopBuy&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const S2C_ShopBuy& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const S2C_ShopBuy* internal_default_instance() {
    return reinterpret_cast<const S2C_ShopBuy*>(
               &_S2C_ShopBuy_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(S2C_ShopBuy& a, S2C_ShopBuy& b) {
    a.Swap(&b);
  }
  inline void Swap(S2C_ShopBuy* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline S2C_ShopBuy* New() const final {
    return CreateMaybeMessage<S2C_ShopBuy>(nullptr);
  }

  S2C_ShopBuy* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<S2C_ShopBuy>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const S2C_ShopBuy& from);
  void MergeFrom(const S2C_ShopBuy& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(S2C_ShopBuy* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.S2C_ShopBuy";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_protocol_5fshop_2eproto);
    return ::descriptor_table_protocol_5fshop_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:Protocol.S2C_ShopBuy)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_protocol_5fshop_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// C2S_ShopLoad

// -------------------------------------------------------------------

// S2C_ShopLoad

// -------------------------------------------------------------------

// C2S_ShopBuy

// -------------------------------------------------------------------

// S2C_ShopBuy

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protocol_5fshop_2eproto
