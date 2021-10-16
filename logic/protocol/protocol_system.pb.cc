// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol_system.proto

#include "protocol_system.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace Protocol {
class C2S_SystemTickDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<C2S_SystemTick> _instance;
} _C2S_SystemTick_default_instance_;
class S2C_SystemTickDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<S2C_SystemTick> _instance;
} _S2C_SystemTick_default_instance_;
}  // namespace Protocol
static void InitDefaultsscc_info_C2S_SystemTick_protocol_5fsystem_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Protocol::_C2S_SystemTick_default_instance_;
    new (ptr) ::Protocol::C2S_SystemTick();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Protocol::C2S_SystemTick::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_C2S_SystemTick_protocol_5fsystem_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_C2S_SystemTick_protocol_5fsystem_2eproto}, {}};

static void InitDefaultsscc_info_S2C_SystemTick_protocol_5fsystem_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::Protocol::_S2C_SystemTick_default_instance_;
    new (ptr) ::Protocol::S2C_SystemTick();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::Protocol::S2C_SystemTick::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_S2C_SystemTick_protocol_5fsystem_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_S2C_SystemTick_protocol_5fsystem_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_protocol_5fsystem_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_protocol_5fsystem_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_protocol_5fsystem_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_protocol_5fsystem_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::C2S_SystemTick, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::S2C_SystemTick, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Protocol::C2S_SystemTick)},
  { 5, -1, sizeof(::Protocol::S2C_SystemTick)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_C2S_SystemTick_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Protocol::_S2C_SystemTick_default_instance_),
};

const char descriptor_table_protodef_protocol_5fsystem_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\025protocol_system.proto\022\010Protocol\"\020\n\016C2S"
  "_SystemTick\"\020\n\016S2C_SystemTickb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_protocol_5fsystem_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_protocol_5fsystem_2eproto_sccs[2] = {
  &scc_info_C2S_SystemTick_protocol_5fsystem_2eproto.base,
  &scc_info_S2C_SystemTick_protocol_5fsystem_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_protocol_5fsystem_2eproto_once;
static bool descriptor_table_protocol_5fsystem_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_protocol_5fsystem_2eproto = {
  &descriptor_table_protocol_5fsystem_2eproto_initialized, descriptor_table_protodef_protocol_5fsystem_2eproto, "protocol_system.proto", 77,
  &descriptor_table_protocol_5fsystem_2eproto_once, descriptor_table_protocol_5fsystem_2eproto_sccs, descriptor_table_protocol_5fsystem_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_protocol_5fsystem_2eproto::offsets,
  file_level_metadata_protocol_5fsystem_2eproto, 2, file_level_enum_descriptors_protocol_5fsystem_2eproto, file_level_service_descriptors_protocol_5fsystem_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_protocol_5fsystem_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_protocol_5fsystem_2eproto), true);
namespace Protocol {

// ===================================================================

void C2S_SystemTick::InitAsDefaultInstance() {
}
class C2S_SystemTick::_Internal {
 public:
};

C2S_SystemTick::C2S_SystemTick()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protocol.C2S_SystemTick)
}
C2S_SystemTick::C2S_SystemTick(const C2S_SystemTick& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Protocol.C2S_SystemTick)
}

void C2S_SystemTick::SharedCtor() {
}

C2S_SystemTick::~C2S_SystemTick() {
  // @@protoc_insertion_point(destructor:Protocol.C2S_SystemTick)
  SharedDtor();
}

void C2S_SystemTick::SharedDtor() {
}

void C2S_SystemTick::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const C2S_SystemTick& C2S_SystemTick::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_C2S_SystemTick_protocol_5fsystem_2eproto.base);
  return *internal_default_instance();
}


void C2S_SystemTick::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.C2S_SystemTick)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear();
}

const char* C2S_SystemTick::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      default: {
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* C2S_SystemTick::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.C2S_SystemTick)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.C2S_SystemTick)
  return target;
}

size_t C2S_SystemTick::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.C2S_SystemTick)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void C2S_SystemTick::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.C2S_SystemTick)
  GOOGLE_DCHECK_NE(&from, this);
  const C2S_SystemTick* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<C2S_SystemTick>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.C2S_SystemTick)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.C2S_SystemTick)
    MergeFrom(*source);
  }
}

void C2S_SystemTick::MergeFrom(const C2S_SystemTick& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.C2S_SystemTick)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void C2S_SystemTick::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.C2S_SystemTick)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void C2S_SystemTick::CopyFrom(const C2S_SystemTick& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.C2S_SystemTick)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool C2S_SystemTick::IsInitialized() const {
  return true;
}

void C2S_SystemTick::InternalSwap(C2S_SystemTick* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata C2S_SystemTick::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void S2C_SystemTick::InitAsDefaultInstance() {
}
class S2C_SystemTick::_Internal {
 public:
};

S2C_SystemTick::S2C_SystemTick()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Protocol.S2C_SystemTick)
}
S2C_SystemTick::S2C_SystemTick(const S2C_SystemTick& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Protocol.S2C_SystemTick)
}

void S2C_SystemTick::SharedCtor() {
}

S2C_SystemTick::~S2C_SystemTick() {
  // @@protoc_insertion_point(destructor:Protocol.S2C_SystemTick)
  SharedDtor();
}

void S2C_SystemTick::SharedDtor() {
}

void S2C_SystemTick::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const S2C_SystemTick& S2C_SystemTick::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_S2C_SystemTick_protocol_5fsystem_2eproto.base);
  return *internal_default_instance();
}


void S2C_SystemTick::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.S2C_SystemTick)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear();
}

const char* S2C_SystemTick::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      default: {
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* S2C_SystemTick::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.S2C_SystemTick)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.S2C_SystemTick)
  return target;
}

size_t S2C_SystemTick::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.S2C_SystemTick)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void S2C_SystemTick::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Protocol.S2C_SystemTick)
  GOOGLE_DCHECK_NE(&from, this);
  const S2C_SystemTick* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<S2C_SystemTick>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Protocol.S2C_SystemTick)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Protocol.S2C_SystemTick)
    MergeFrom(*source);
  }
}

void S2C_SystemTick::MergeFrom(const S2C_SystemTick& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Protocol.S2C_SystemTick)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void S2C_SystemTick::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Protocol.S2C_SystemTick)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void S2C_SystemTick::CopyFrom(const S2C_SystemTick& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.S2C_SystemTick)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool S2C_SystemTick::IsInitialized() const {
  return true;
}

void S2C_SystemTick::InternalSwap(S2C_SystemTick* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata S2C_SystemTick::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::C2S_SystemTick* Arena::CreateMaybeMessage< ::Protocol::C2S_SystemTick >(Arena* arena) {
  return Arena::CreateInternal< ::Protocol::C2S_SystemTick >(arena);
}
template<> PROTOBUF_NOINLINE ::Protocol::S2C_SystemTick* Arena::CreateMaybeMessage< ::Protocol::S2C_SystemTick >(Arena* arena) {
  return Arena::CreateInternal< ::Protocol::S2C_SystemTick >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
