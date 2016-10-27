// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "RceAddArmy.pb.h"
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>

namespace {

const ::google::protobuf::Descriptor* RceAddArmy_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RceAddArmy_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_RceAddArmy_2eproto() {
  protobuf_AddDesc_RceAddArmy_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "RceAddArmy.proto");
  GOOGLE_CHECK(file != NULL);
  RceAddArmy_descriptor_ = file->message_type(0);
  static const int RceAddArmy_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RceAddArmy, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RceAddArmy, army_),
  };
  RceAddArmy_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RceAddArmy_descriptor_,
      RceAddArmy::default_instance_,
      RceAddArmy_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RceAddArmy, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RceAddArmy, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RceAddArmy));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_RceAddArmy_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RceAddArmy_descriptor_, &RceAddArmy::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_RceAddArmy_2eproto() {
  delete RceAddArmy::default_instance_;
  delete RceAddArmy_reflection_;
}

void protobuf_AddDesc_RceAddArmy_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_Army_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020RceAddArmy.proto\032\nArmy.proto\"/\n\nRceAdd"
    "Army\022\014\n\004type\030\001 \001(\005\022\023\n\004army\030\002 \003(\0132\005.Army", 79);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "RceAddArmy.proto", &protobuf_RegisterTypes);
  RceAddArmy::default_instance_ = new RceAddArmy();
  RceAddArmy::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_RceAddArmy_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_RceAddArmy_2eproto {
  StaticDescriptorInitializer_RceAddArmy_2eproto() {
    protobuf_AddDesc_RceAddArmy_2eproto();
  }
} static_descriptor_initializer_RceAddArmy_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int RceAddArmy::kTypeFieldNumber;
const int RceAddArmy::kArmyFieldNumber;
#endif  // !_MSC_VER

RceAddArmy::RceAddArmy() {
  SharedCtor();
}

void RceAddArmy::InitAsDefaultInstance() {
}

RceAddArmy::RceAddArmy(const RceAddArmy& from) {
  SharedCtor();
  MergeFrom(from);
}

void RceAddArmy::SharedCtor() {
  _cached_size_ = 0;
  type_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RceAddArmy::~RceAddArmy() {
  SharedDtor();
}

void RceAddArmy::SharedDtor() {
  if (this != default_instance_) {
  }
}

const ::google::protobuf::Descriptor* RceAddArmy::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RceAddArmy_descriptor_;
}

const RceAddArmy& RceAddArmy::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_RceAddArmy_2eproto();  return *default_instance_;
}

RceAddArmy* RceAddArmy::default_instance_ = NULL;

RceAddArmy* RceAddArmy::New() const {
  return new RceAddArmy;
}

void RceAddArmy::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    type_ = 0;
  }
  army_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RceAddArmy::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 type = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          goto handle_uninterpreted;
        }
        DO_(::google::protobuf::internal::WireFormatLite::ReadInt32(
              input, &type_));
        _set_bit(0);
        if (input->ExpectTag(18)) goto parse_army;
        break;
      }
      
      // repeated .Army army = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) !=
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          goto handle_uninterpreted;
        }
       parse_army:
        DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
              input, add_army()));
        if (input->ExpectTag(18)) goto parse_army;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void RceAddArmy::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    RceAddArmy::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }
  
  // optional int32 type = 1;
  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }
  
  // repeated .Army army = 2;
  for (int i = 0; i < this->army_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageNoVirtual(
      2, this->army(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* RceAddArmy::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 type = 1;
  if (_has_bit(0)) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }
  
  // repeated .Army army = 2;
  for (int i = 0; i < this->army_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->army(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int RceAddArmy::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->type());
    }
    
  }
  // repeated .Army army = 2;
  total_size += 1 * this->army_size();
  for (int i = 0; i < this->army_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->army(i));
  }
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  _cached_size_ = total_size;
  return total_size;
}

void RceAddArmy::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RceAddArmy* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RceAddArmy*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RceAddArmy::MergeFrom(const RceAddArmy& from) {
  GOOGLE_CHECK_NE(&from, this);
  army_.MergeFrom(from.army_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from._has_bit(0)) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RceAddArmy::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RceAddArmy::CopyFrom(const RceAddArmy& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RceAddArmy::IsInitialized() const {
  
  return true;
}

void RceAddArmy::Swap(RceAddArmy* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    army_.Swap(&other->army_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RceAddArmy::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RceAddArmy_descriptor_;
  metadata.reflection = RceAddArmy_reflection_;
  return metadata;
}
