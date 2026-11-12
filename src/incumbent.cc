// Copyright 2026 the Deno authors. All rights reserved. MIT license.
#include <cstdint>
#include <new>

#include <support.h>

using BackupIncumbentScope = v8::Context::BackupIncumbentScope;
static_assert(sizeof(BackupIncumbentScope) == 3 * sizeof(uintptr_t));
static_assert(alignof(BackupIncumbentScope) == alignof(uintptr_t));

extern "C" {
const v8::Context* v8__Isolate__GetIncumbentContext(v8::Isolate* isolate) {
  if (!isolate->InContext()) return nullptr;
  return support::local_to_ptr(isolate->GetIncumbentContext());
}

void v8__BackupIncumbentScope__CONSTRUCT(void* storage,
                                        const v8::Context* context) {
  new (storage) BackupIncumbentScope(support::ptr_to_local(context));
}

void v8__BackupIncumbentScope__DESTRUCT(void* storage) {
  static_cast<BackupIncumbentScope*>(storage)->~BackupIncumbentScope();
}
}
