//
// Created by Kenvi Zhu on 2022-01-12.
//

#include "../jni/org_wasmedge_GlobalInstanceContext.h"
#include "GlobalTypeContext.h"
#include "ValueType.h"
#include "common.h"

WasmEdge_GlobalInstanceContext *
getGlobalInstanceContext(JNIEnv *env, jobject jGlobalInstanceContext) {

  if (jGlobalInstanceContext == NULL) {
    return NULL;
  }
  WasmEdge_GlobalInstanceContext *globalInstanceContext =
      (struct WasmEdge_GlobalInstanceContext *)getPointer(
          env, jGlobalInstanceContext);

  return globalInstanceContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalInstanceContext_nativeInit(
    JNIEnv *env, jobject thisObject, jobject jGlobalTypeCxt, jobject jVal) {
  WasmEdge_GlobalTypeContext *globalTypeContext =
      getGlobalTypeContext(env, jGlobalTypeCxt);

  WasmEdge_GlobalInstanceContext *globalInstanceContext =
      WasmEdge_GlobalInstanceCreate(globalTypeContext,
                                    JavaValueToWasmEdgeValue(env, jVal));
  setPointer(env, thisObject, (long)globalInstanceContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalInstanceContext_nativeSetValue(
    JNIEnv *env, jobject thisObject, jobject jVal) {
  WasmEdge_GlobalInstanceContext *globalInstanceContext =
      getGlobalInstanceContext(env, thisObject);

  WasmEdge_Value value = JavaValueToWasmEdgeValue(env, jVal);

  WasmEdge_GlobalInstanceSetValue(globalInstanceContext, value);
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalInstanceContext_delete(
    JNIEnv *env, jobject thisObject) {
  WasmEdge_GlobalInstanceContext *globalInstanceContext =
      getGlobalInstanceContext(env, thisObject);
  WasmEdge_GlobalInstanceDelete(globalInstanceContext);
}

jobject createJGlobalInstanceContext(
    JNIEnv *env, const WasmEdge_GlobalInstanceContext *globInstance) {

  // FIXME add to all instances.
  if (globInstance == NULL) {
    return NULL;
  }

  jclass clazz = (*env)->FindClass(env, "org/wasmedge/GlobalInstanceContext");
  jmethodID constructorId = (*env)->GetMethodID(env, clazz, "<init>", "(J)V");
  return (*env)->NewObject(env, clazz, constructorId, (long)globInstance);
}
