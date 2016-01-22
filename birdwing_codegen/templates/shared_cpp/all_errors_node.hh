#ifndef ALL_ERRORS_NODE_HH
#define ALL_ERRORS_NODE_HH

// Copyright 2016 MakerBot Industries

namespace bwcoreutils{
v8::Local<v8::Object> bwErrorActionsEnum(v8::Isolate * isolate) {
  auto actions = v8::Object::New(isolate);
  {{#error_action_enum}}
  actions->Set(
      v8::String::NewFromUtf8(isolate, "{{name}}"),
      v8::Integer::New(isolate, {{value}}));
  {{/error_action_enum}}

  return actions;
}

v8::Local<v8::Object> bwErrorTypesEnum(v8::Isolate * isolate) {
  auto types = v8::Object::New(isolate);
  {{#error_type_enum}}
  types->Set(
      v8::String::NewFromUtf8(isolate, "{{name}}"),
      v8::Integer::New(isolate, {{value}}));
  {{/error_type_enum}}

  return types;
}

v8::Local<v8::Object> bwErrorsEnum(v8::Isolate * isolate) {
  auto errors = v8::Object::New(isolate);
  {{#machine_errors}}
  errors->Set(
      v8::String::NewFromUtf8(isolate, "{{name}}"),
      v8::Integer::New(isolate, {{id}}));
  {{/machine_errors}}
  {{#toolhead_errors}}
  errors->Set(
      v8::String::NewFromUtf8(isolate, "{{name}}"),
      v8::Integer::New(isolate, {{id}}));
  {{/toolhead_errors}}

  return errors;
}
}  // namespace

#endif // BOT_ERROR_NOQT_HH
